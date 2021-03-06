/*****************************************************************************
 *  Copyright (C) 2008-2011 Massachusetts Institute of Technology            *
 *                                                                           *
 *  Permission is hereby granted, free of charge, to any person obtaining    *
 *  a copy of this software and associated documentation files (the          *
 *  "Software"), to deal in the Software without restriction, including      *
 *  without limitation the rights to use, copy, modify, merge, publish,      *
 *  distribute, sublicense, and/or sell copies of the Software, and to       *
 *  permit persons to whom the Software is furnished to do so, subject       *
 *  to the following conditions:                                             *
 *                                                                           *
 *  The above copyright notice and this permission notice shall be included  *
 *  in all copies or substantial portions of the Software.                   *
 *                                                                           *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY                *
 *  KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE               *
 *  WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND      *
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE   *
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION   *
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION    *
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE           *
 *                                                                           *
 *  This source code is part of the PetaBricks project:                      *
 *    http://projects.csail.mit.edu/petabricks/                              *
 *                                                                           *
 *****************************************************************************/

#include "remotehost.h"

#include "distributedgc.h"
#include "workerthread.h"

#include "common/jconvert.h"

#include <algorithm>
#include <poll.h>
#include <set>
#include <unistd.h>

static bool theListenersShutdown = false;

namespace _RemoteHostMsgTypes {

  typedef petabricks::EncodedPtr EncodedPtr;

  typedef uint32_t DataLen;
  typedef uint16_t MessageType;
  typedef int16_t ChanNumber;

  extern "C" void token_func() {}

  template<typename T>
  EncodedPtr EncodeTextPtr(T p) {
    return reinterpret_cast<intptr_t>(p)-reinterpret_cast<intptr_t>(&token_func);
  }

  template<typename T>
  T DecodeTextPtr(EncodedPtr p) {
    return reinterpret_cast<T>(p+reinterpret_cast<intptr_t>(&token_func));
  }

  template<typename T>
  EncodedPtr EncodeDataPtr(T* p) {
    return reinterpret_cast<EncodedPtr>(p);
  }

  template<typename T>
  T* DecodeDataPtr(EncodedPtr p) {
    return reinterpret_cast<T*>(p);
  }

  using petabricks::HostPid;
  struct MessageTypes {
    enum {
      HELLO_CONTROL= 0xf0c0,
      HELLO_DATA,
      SETUP_MASTER,
      SETUP_CONNECT,
      SETUP_ACCEPT,
      SETUP_ACK,
      SETUP_END,
      REMOTEOBJECT_CREATE,
      REMOTEOBJECT_CREATE_ACK,
      REMOTEOBJECT_DATA,
      REMOTEOBJECT_SIGNAL,
      REMOTEOBJECT_BROADCAST,
      REMOTEOBJECT_NOTIFY,
      REMOTEOBJECT_MARKCOMPLETE,
      SHUTDOWN_BEGIN,
      SHUTDOWN_ACK,
      SHUTDOWN_END,
    };
    static const char* str(int t) {
      switch(t) {
#define  EXPSTR(s) case s: return #s
        EXPSTR(HELLO_CONTROL);
        EXPSTR(HELLO_DATA);
        EXPSTR(SETUP_MASTER);
        EXPSTR(SETUP_CONNECT);
        EXPSTR(SETUP_ACCEPT);
        EXPSTR(SETUP_ACK);
        EXPSTR(SETUP_END);
        EXPSTR(REMOTEOBJECT_CREATE);
        EXPSTR(REMOTEOBJECT_CREATE_ACK);
        EXPSTR(REMOTEOBJECT_DATA);
        EXPSTR(REMOTEOBJECT_SIGNAL);
        EXPSTR(REMOTEOBJECT_BROADCAST);
        EXPSTR(REMOTEOBJECT_NOTIFY);
        EXPSTR(REMOTEOBJECT_MARKCOMPLETE);
        EXPSTR(SHUTDOWN_BEGIN);
        EXPSTR(SHUTDOWN_ACK);
        EXPSTR(SHUTDOWN_END);
#undef EXPSTR
        default: return "INVALID";
    }
  }
  };

  struct HelloMessage {
    uint16_t    type;
    HostPid     id;
    ChanNumber  chan;
    int         port;
    int         roll;
    char        host[1024];

    friend std::ostream& operator<<(std::ostream& o, const HelloMessage& m) {
      return o << "HelloMessage("
               << MessageTypes::str(m.type) << ", "
               << m.id << ")";
    }
  } PACKED;


  struct SetupMessage {
    uint16_t type;
    char     host[1024];
    int      port;
    int      allocHostNumber;

    friend std::ostream& operator<<(std::ostream& o, const SetupMessage& m) {
      return o << "SetupMessage("
               << MessageTypes::str(m.type) << ", "
               << m.host << ", "
               << m.port << ", "
               << m.allocHostNumber << ")";
    }
  } PACKED;

  struct SetupAckMessage {
    uint16_t type;

    friend std::ostream& operator<<(std::ostream& o, const SetupAckMessage& m) {
      return o << "SetupAckMessage("
               << MessageTypes::str(m.type) << ")";
    }
  } PACKED;

  struct GeneralMessage {
    uint16_t    type;
    uint16_t    chan;
    DataLen     len;
    EncodedPtr  arg;
    EncodedPtr  srcptr;
    EncodedPtr  dstptr;

    friend std::ostream& operator<<(std::ostream& o, const GeneralMessage& m) {
      return o << "GeneralMessage("
               << MessageTypes::str(m.type) << ", "
               << m.len << " bytes, "
               << m.arg << " arg, "
               << std::hex << m.srcptr << " => " << m.dstptr << std::dec << ")";
    }
  } PACKED;

  void* start_listenLoop(void* arg) {
    petabricks::WorkerThread::markUtilityThread();
    ((petabricks::RemoteHostDB*)arg)->listenLoop();
    return NULL;
  }
}
using namespace _RemoteHostMsgTypes;

const HostPid& petabricks::HostPid::self() {
  static HostPid selfObj = { gethostid(), 0 };
  selfObj.pid = getpid();//pid may change with fork()
  return selfObj;
}

void petabricks::RemoteHost::accept(jalib::JServerSocket& s, int listenPort) {
  for(int i=0; i<REMOTEHOST_DATACHANS+1; ++i) {
    _scratchSockets[i].close();
    _scratchSockets[i] = s.accept();
    JASSERT(_scratchSockets[i].isValid());
  }
  _lastchan = 1;
  handshake(listenPort, false);
}

void petabricks::RemoteHost::connect(const jalib::JSockAddr& a, int p, int listenPort) {
  JASSERT(_control.connect(a, p));
  for(int i=0; i<REMOTEHOST_DATACHANS; ++i) {
    JASSERT(_data[i].connect(a, p));
  }
  _lastchan = 0;
  handshake(listenPort, true);
}

void petabricks::RemoteHost::acceptMasterControl(jalib::JServerSocket& s, int /*listenPort*/) {
  _scratchSockets[0].close();
  _scratchSockets[0] = s.accept();
  JASSERT(_scratchSockets[0].isValid());
}

void petabricks::RemoteHost::connectMasterControl(const jalib::JSockAddr& a, int p, int /*listenPort*/) {
  // wait until parent is created (when run using PBS)
  // max wait time = 5 secs
  int count = 0;
  while (!_control.connect(a, p)) {
    JASSERT(count < 100).Text("Timeout: _control.connect(a, p)");
    count++;
    usleep(50000); // 50 ms
  }
}

void petabricks::RemoteHost::acceptMasterData(jalib::JServerSocket& s, int listenPort) {
  for(int i=1; i<REMOTEHOST_DATACHANS+1; ++i) {
    _scratchSockets[i].close();
    _scratchSockets[i] = s.accept();
    JASSERT(_scratchSockets[i].isValid());
  }
  _lastchan = 1;
  handshake(listenPort, false);
}

void petabricks::RemoteHost::connectMasterData(const jalib::JSockAddr& a, int p, int listenPort) {
  for(int i=0; i<REMOTEHOST_DATACHANS; ++i) {
    JASSERT(_data[i].connect(a, p));
  }
  _lastchan = 0;
  handshake(listenPort, true);
}

void petabricks::RemoteHost::handshake(int port, bool isConnect) {
  HostPid self = HostPid::self();

  //mix our pid into the random roll since lrand48 is often not seeded (in debugging modes)
  unsigned short xsubi[] = { lrand48()^self.pid , lrand48()^self.pid, lrand48()^self.pid } ;
  for(int i=0; i<16; ++i) nrand48(xsubi);
  int myRoll = nrand48(xsubi) % 9000;

  if (isConnect) {
    // Send Hello Messages
    HelloMessage msg = { MessageTypes::HELLO_CONTROL,
                         self,
                         REMOTEHOST_DATACHANS,
                         port,
                         myRoll,
                         ""};
    strncpy(msg.host, RemoteHostDB::instance().host(), sizeof msg.host);
    _control.disableNagle();
    JASSERT(_control.writeAll((char*)&msg, sizeof msg) == sizeof msg);

    for(int i=0; i<REMOTEHOST_DATACHANS; ++i) {
      HelloMessage dmsg = { MessageTypes::HELLO_DATA, self, i, port, myRoll, ""};
      _data[i].disableNagle();
      JASSERT(_data[i].writeAll((char*)&dmsg, sizeof dmsg) == sizeof dmsg);
    }

    // Receive Hello Messages
    JASSERT(_control.readAll((char*)&msg, sizeof msg) == sizeof msg);
    JASSERT(msg.type == MessageTypes::HELLO_CONTROL
            && msg.id != self
            && msg.chan == REMOTEHOST_DATACHANS);

    _id = msg.id;
    _remotePort = msg.port;
    std::string hostname(msg.host);
    _connectName = hostname;

    if(myRoll!=msg.roll)
      _shouldGc = myRoll < msg.roll;
    else
      _shouldGc = self < _id;

    for(int i=0; i<REMOTEHOST_DATACHANS; ++i) {
      HelloMessage dmsg = { MessageTypes::HELLO_DATA, self, i, port, myRoll, ""};
      JASSERT(_data[i].readAll((char*)&dmsg, sizeof dmsg) == sizeof dmsg)(i);
      JASSERT(dmsg.type == MessageTypes::HELLO_DATA
              && dmsg.id == _id
              && dmsg.chan == i);
    }

  } else {
    // Receive Hello Messages
    for(int i=0; i<REMOTEHOST_DATACHANS+1; ++i) {
      HelloMessage msg;
      JASSERT(_scratchSockets[i].readAll((char*)&msg, sizeof msg) == sizeof msg);

      // set _id
      if (i == 0) {
        JASSERT(msg.id != self);
        _id = msg.id;
      } else {
        JASSERT(msg.id == _id);
      }

      if (msg.type == MessageTypes::HELLO_CONTROL) {
        _control = _scratchSockets[i];
        std::string hostname(msg.host);
        _connectName = hostname;

        JASSERT(msg.chan == REMOTEHOST_DATACHANS);
        _remotePort = msg.port;

        if(myRoll!=msg.roll)
          _shouldGc = myRoll < msg.roll;
        else
          _shouldGc = self < _id;

      } else if (msg.type == MessageTypes::HELLO_DATA) {
        JASSERT(msg.chan < REMOTEHOST_DATACHANS);
        _data[msg.chan] = _scratchSockets[i];

      } else {
        UNIMPLEMENTED();
      }
    }

    // Send Hello Messages
    HelloMessage msg = { MessageTypes::HELLO_CONTROL,
                         self,
                         REMOTEHOST_DATACHANS,
                         port,
                         myRoll,
                         "" };
    strncpy(msg.host, RemoteHostDB::instance().host(), sizeof msg.host);
    _control.disableNagle();
    JASSERT(_control.writeAll((char*)&msg, sizeof msg) == sizeof msg);

    for(int i=0; i<REMOTEHOST_DATACHANS; ++i) {
      HelloMessage dmsg = { MessageTypes::HELLO_DATA, self, i, port, myRoll, ""};
      _data[i].disableNagle();
      JASSERT(_data[i].writeAll((char*)&dmsg, sizeof dmsg) == sizeof dmsg);
    }
  }

#if 0
  {
    // Check
    JTRACE("Check socket connection");

    HelloMessage msg = { MessageTypes::HELLO_CONTROL,
                         self,
                         REMOTEHOST_DATACHANS,
                         port,
                         myRoll };

    JASSERT(_control.writeAll((char*)&msg, sizeof msg) == sizeof msg);
    JASSERT(_control.readAll((char*)&msg, sizeof msg) == sizeof msg);
    JASSERT(msg.type == MessageTypes::HELLO_CONTROL
            && msg.id == _id
            && msg.chan == REMOTEHOST_DATACHANS);

    for(int i=0; i<REMOTEHOST_DATACHANS; ++i) {
      HelloMessage dmsg = { MessageTypes::HELLO_DATA, self, i, port, myRoll};
      JASSERT(_data[i].writeAll((char*)&dmsg, sizeof dmsg) == sizeof dmsg);
      JASSERT(_data[i].readAll((char*)&dmsg, sizeof dmsg) == sizeof dmsg);
      JASSERT(dmsg.type == MessageTypes::HELLO_DATA
              && dmsg.id == _id
              && dmsg.chan == i);
    }
  }
#endif

}

void petabricks::RemoteHost::setupLoop(RemoteHostDB& db) {
  JLOCKSCOPE(_controlReadmu);
  JLOCKSCOPE(_controlWritemu);

  SetupMessage msg;
  SetupAckMessage ackmsg = { MessageTypes::SETUP_ACK };

  for(msg.type=0; msg.type!=MessageTypes::SETUP_END; ) {
    memset(&msg, 0, sizeof msg);
    _control.readAll((char*)&msg, sizeof msg);

    JTRACE("setup slave")(msg);

    switch(msg.type) {
      case MessageTypes::SETUP_MASTER:
        connectMasterData(msg.host, msg.port, RemoteHostDB::instance().port());
        RemoteHostDB::instance().setAllocHostNumber(msg.allocHostNumber);
        break;
      case MessageTypes::SETUP_CONNECT:
        db.connect(msg.host, msg.port);
        break;
      case MessageTypes::SETUP_ACCEPT:
        db.accept(msg.host);
        break;
      case MessageTypes::SETUP_END:
        break;
      default:
        UNIMPLEMENTED();
    }

    _control.writeAll((char*)&ackmsg, sizeof ackmsg);
  }
}

void petabricks::RemoteHost::setupRemoteConnection(RemoteHost& a, RemoteHost& b) {
  JLOCKSCOPE(a._controlReadmu);
  JLOCKSCOPE(a._controlWritemu);
  JLOCKSCOPE(b._controlReadmu);
  JLOCKSCOPE(b._controlWritemu);

  SetupMessage amsg;
  amsg.type = MessageTypes::SETUP_CONNECT;
  strncpy(amsg.host, a._connectName.c_str(), sizeof amsg.host);
  JASSERT(amsg.host==a._connectName);
  amsg.port = a._remotePort;
  amsg.allocHostNumber = -1;

  SetupMessage bmsg;
  bmsg.type = MessageTypes::SETUP_ACCEPT;
  strncpy(bmsg.host, b._connectName.c_str(), sizeof bmsg.host);
  JASSERT(bmsg.host==b._connectName);
  bmsg.port = b._remotePort;
  bmsg.allocHostNumber = -1;

  //a goes to b, b goes to a
  a._control.writeAll((char*)&bmsg, sizeof bmsg);
  b._control.writeAll((char*)&amsg, sizeof amsg);


  SetupAckMessage aack;
  SetupAckMessage back;
  a._control.readAll((char*)&aack, sizeof aack);
  b._control.readAll((char*)&back, sizeof back);
  JASSERT(aack.type == MessageTypes::SETUP_ACK);
  JASSERT(back.type == MessageTypes::SETUP_ACK);
}

void petabricks::RemoteHost::setupRemoteConnectionWithMaster(int allocHostNumber) {
  JLOCKSCOPE(_controlReadmu);
  JLOCKSCOPE(_controlWritemu);

  SetupMessage msg;
  msg.type = MessageTypes::SETUP_MASTER;
  strncpy(msg.host, RemoteHostDB::instance().host(), sizeof msg.host);
  msg.port = RemoteHostDB::instance().port();
  msg.allocHostNumber = allocHostNumber;

  JASSERT(_scratchSockets[0].writeAll((char*)&msg, sizeof msg) == sizeof msg);

  acceptMasterData(RemoteHostDB::instance().listener(), msg.port);

  SetupAckMessage ack;
  _control.readAll((char*)&ack, sizeof ack);
  JASSERT(ack.type == MessageTypes::SETUP_ACK);
}

void petabricks::RemoteHost::setupEnd() {
  JLOCKSCOPE(_controlReadmu);
  JLOCKSCOPE(_controlWritemu);

  SetupMessage msg;
  memset(&msg, 0, sizeof msg);
  msg.type = MessageTypes::SETUP_END;
  _control.writeAll((char*)&msg, sizeof msg);

  SetupAckMessage ack;
  _control.readAll((char*)&ack, sizeof ack);
  JASSERT(ack.type == MessageTypes::SETUP_ACK);
}



bool petabricks::RemoteHost::recv(const RemoteObject* caller) {
  GeneralMessage msg;

  if(!_controlReadmu.trylock()) {
    //JTRACE("skipping recv, locked");
    return false;
  }

  /*
   * caller!=0 when a worker thread is waiting for a message and is trying to help
   * recv it.  need to make sure that message isn't being processed in parallel.
   */
  if(caller!=0 && caller->pendingMessages()>0) {
    _controlReadmu.unlock();
    return false;
  }

  ssize_t cnt;
  if(caller == 0) {
    // recv thread: has other useful work to do
    cnt = _control.tryReadAll((char*)&msg, sizeof msg);
    if(cnt==0) {
      _controlReadmu.unlock();
      return false;
    }
  } else {
    caller->unlock();
    // worker thread: is waiting for a msg
    cnt = _control.readAll((char*)&msg, sizeof msg);
  }

  if(cnt<0) {
    _controlReadmu.unlock();
    JASSERT(false)(_id).Text("disconnected");
    return false;
  }
  JASSERT(cnt==sizeof msg)(cnt);

  if(msg.len>0){
    JASSERT(msg.chan<REMOTEHOST_DATACHANS);
    _dataReadmu[msg.chan].lock();
  }
  RemoteObjectPtr obj = 0;
  void* buf = 0;

  if(msg.dstptr != 0) {
    obj = DecodeDataPtr<RemoteObject>(msg.dstptr);
    jalib::atomicIncrement(&obj->_pendingMessages);
    obj->_lastMsgGen = _currentGen;
  }

  _controlReadmu.unlock();

  if(obj){
    obj->lock();
    if(!obj->isCreated()){
      obj->setRemoteObjMu(msg.srcptr);
      obj->markCreatedMu();
      obj->onCreated();
    }
  }

  switch(msg.type) {
  case MessageTypes::REMOTEOBJECT_CREATE:
    {
      RemoteObjectGenerator gen;
      gen = DecodeTextPtr<RemoteObjectGenerator>(msg.arg);
      obj = (*gen)();
      obj->_pendingMessages += 1;
      obj->_lastMsgGen = _currentGen;
      obj->lock();
      obj->setHostMu(this);
      obj->setRemoteObjMu(msg.srcptr);
      obj->markCreatedMu();
      if(msg.len>0){
        buf = obj->allocRecvInitial(msg.len);
        _data[msg.chan].readAll((char*)buf, msg.len);
        _dataReadmu[msg.chan].unlock();
        obj->onRecvInitial(buf, msg.len);
        obj->freeRecvInitial(buf, msg.len);
      }
      if(!obj->isSkipCreateAck()) {
        GeneralMessage ackmsg = { MessageTypes::REMOTEOBJECT_CREATE_ACK,
                                  0,
                                  0,
                                  0,
                                  EncodeDataPtr(obj.asPtr()),
                                  msg.srcptr };
        sendMsg(&ackmsg);
      }
      obj->onCreated();
      addObject(obj);
      break;
    }
  case MessageTypes::REMOTEOBJECT_CREATE_ACK:
    {
      JASSERT(msg.len==0);
      break;
    }
  case MessageTypes::REMOTEOBJECT_DATA:
    {
      if(msg.len>0){
        buf = obj->allocRecv(msg.len, msg.arg);
        _data[msg.chan].readAll((char*)buf, msg.len);
        _dataReadmu[msg.chan].unlock();
        obj->onRecv(buf, msg.len, msg.arg);
        obj->freeRecv(buf, msg.len, msg.arg);
      }else{
        char dummy;
        obj->onRecv(&dummy, 0, msg.arg);
      }
      break;
    }
  case MessageTypes::REMOTEOBJECT_SIGNAL:
    {
      JASSERT(msg.len==0);
      obj->signal();
      break;
    }
  case MessageTypes::REMOTEOBJECT_BROADCAST:
    {
      JASSERT(msg.len==0);
      obj->broadcast();
      break;
    }
  case MessageTypes::REMOTEOBJECT_NOTIFY:
    {
      JASSERT(msg.len==0);
      obj->onNotify(msg.arg);
      break;
    }
  case MessageTypes::REMOTEOBJECT_MARKCOMPLETE:
    {
      JASSERT(msg.len==0);
      obj->onComplete();
      obj->markCompleteMu();
      break;
    }
  case MessageTypes::SHUTDOWN_BEGIN:
    {
      JLOCKSCOPE(_controlReadmu);
      JLOCKSCOPE(_controlWritemu);
      { GeneralMessage ackmsg = { MessageTypes::SHUTDOWN_ACK, 0, 0, 0, 0, 0};
        _control.writeAll((const char*)&ackmsg, sizeof(GeneralMessage));
      }
#ifdef COUNT_CONNECTIONS
      RemoteHostDB& hostdb = RemoteHostDB::instance();
      JTRACE("counts")(hostdb._numSends)(hostdb._numBytes);
#endif
      _control.readAll((char*)&msg, sizeof msg);
      JASSERT(msg.type==MessageTypes::SHUTDOWN_END);
      JTRACE("slave exit")(HostPid::self());
      _exit(0);
      break;
    }
  case MessageTypes::SHUTDOWN_ACK:
    {
      _isShuttingDown=true;
      RemoteHostDB::onShutdownEvent();
      break;
    }
  case MessageTypes::SHUTDOWN_END:
    {
      JASSERT(false);
      break;
    }
  default:
    JASSERT(false);
  }

  if(obj) {
    obj->unlock();
    jalib::atomicDecrement(&obj->_pendingMessages);
  }

  if(caller!=0) {
    caller->lock();
  }

  return true;
}

void petabricks::RemoteHost::sendMsg(GeneralMessage* msg, const void* data, size_t len) {
#ifdef COUNT_CONNECTIONS
  RemoteHostDB& hostdb = RemoteHostDB::instance();
  jalib::atomicIncrement(&hostdb._numSends);
  jalib::atomicAdd(&hostdb._numBytes, sizeof(GeneralMessage) + len);
  //JTRACE("1")(*msg);
#endif

  int chan;
  _controlWritemu.lock();
  if(len>0){
    chan = msg->chan = pickChannel();
  }else{
    chan = msg->chan = 0;
  }
  msg->len = len;
  _control.writeAll((const char*)msg, sizeof(GeneralMessage));

  if(msg->srcptr != 0) {
    DecodeDataPtr<RemoteObject>(msg->srcptr)->_lastMsgGen = _currentGen;
  }

  if(len>0){
    _dataWritemu[chan].lock();
    _controlWritemu.unlock();
    _data[chan].writeAll((const char*)data, len);
    _dataWritemu[chan].unlock();
  }else{
    _controlWritemu.unlock();
  }
}

void petabricks::RemoteHost::sendMsg(GeneralMessage* msg, const void* data, size_t len, const void* data2, size_t len2) {
#ifdef COUNT_CONNECTIONS
  RemoteHostDB& hostdb = RemoteHostDB::instance();
  jalib::atomicIncrement(&hostdb._numSends);
  jalib::atomicAdd(&hostdb._numBytes, sizeof(GeneralMessage) + len + len2);
  //JTRACE("2")(*msg);
#endif

  int chan;
  _controlWritemu.lock();
  if(len>0){
    chan = msg->chan = pickChannel();
  }else{
    chan = msg->chan = 0;
  }
  msg->len = len + len2;
  _control.writeAll((const char*)msg, sizeof(GeneralMessage));

  if(msg->srcptr != 0) {
    DecodeDataPtr<RemoteObject>(msg->srcptr)->_lastMsgGen = _currentGen;
  }

  if(len>0){
    _dataWritemu[chan].lock();
    _controlWritemu.unlock();
    _data[chan].writeAll((const char*)data, len);
    _data[chan].writeAll((const char*)data2, len2);
    _dataWritemu[chan].unlock();
  }else{
    _controlWritemu.unlock();
  }
}

void petabricks::RemoteHost::createRemoteObject(const RemoteObjectPtr& local,
                                                RemoteObjectGenerator remote,
                                                const void* data, size_t len) {
  local->markInitiatorMu();
  local->setHostMu(this);
  GeneralMessage msg = { MessageTypes::REMOTEOBJECT_CREATE,
                         0,
                         len,
                         EncodeTextPtr(remote),
                         EncodeDataPtr(local.asPtr()),
                         0 };
  sendMsg(&msg, data, len);
  addObject(local);
}

void petabricks::RemoteHost::sendData(const RemoteObject* local, const void* data, size_t len, int arg) {
  local->waitUntilCreated();
  GeneralMessage msg = { MessageTypes::REMOTEOBJECT_DATA,
                         0,
                         len,
                         arg,
                         EncodeDataPtr(local),
                         local->remoteObj() };
  sendMsg(&msg, data, len);
}

void petabricks::RemoteHost::sendData(const RemoteObject* local, const void* data, size_t len, const void* data2, size_t len2, int arg) {
  local->waitUntilCreated();
  GeneralMessage msg = { MessageTypes::REMOTEOBJECT_DATA,
                         0,
                         len + len2,
                         arg,
                         EncodeDataPtr(local),
                         local->remoteObj() };
  sendMsg(&msg, data, len, data2, len2);
}

void petabricks::RemoteHost::remoteSignal(const RemoteObject* local) {
  local->waitUntilCreated();
  GeneralMessage msg = { MessageTypes::REMOTEOBJECT_SIGNAL,
                         0,
                         0,
                         0,
                         EncodeDataPtr(local),
                         local->remoteObj() };
  sendMsg(&msg);
}
void petabricks::RemoteHost::remoteBroadcast(const RemoteObject* local) {
  local->waitUntilCreated();
  GeneralMessage msg = { MessageTypes::REMOTEOBJECT_BROADCAST,
                         0,
                         0,
                         0,
                         EncodeDataPtr(local),
                         local->remoteObj() };
  sendMsg(&msg);
}
void petabricks::RemoteHost::remoteMarkComplete(const RemoteObject* local) {
  local->waitUntilCreated();
  GeneralMessage msg = { MessageTypes::REMOTEOBJECT_MARKCOMPLETE,
                         0,
                         0,
                         0,
                         EncodeDataPtr(local),
                         local->remoteObj() };
  sendMsg(&msg);
}
void petabricks::RemoteHost::remoteNotify(const RemoteObject* local, int arg) {
  local->waitUntilCreated();
  GeneralMessage msg = { MessageTypes::REMOTEOBJECT_NOTIFY,
                         0,
                         0,
                         arg,
                         0,
                         local->remoteObj() };
  sendMsg(&msg);
}

void petabricks::RemoteHost::shutdownBegin() {
  GeneralMessage msg = { MessageTypes::SHUTDOWN_BEGIN,
                         0,
                         0,
                         0,
                         0,
                         0 };
  sendMsg(&msg);
}

void petabricks::RemoteHost::shutdownEnd() {
  GeneralMessage msg = { MessageTypes::SHUTDOWN_END,
                         0,
                         0,
                         0,
                         0,
                         0 };
  _controlReadmu.lock();
  _controlWritemu.lock();
  _control.writeAll((char*)&msg, sizeof msg);
}

void petabricks::RemoteHost::swapObjects(RemoteObjectList& obj, int& gen) {
  JLOCKSCOPE(_objectsmu);
  ++_currentGen;
  gen = _currentGen;
  _objects.swap(obj);
  _gcLastLiveObjCount = _objects.size();
}


void petabricks::RemoteHost::readdObjects(RemoteObjectList& obj) {
  if(obj.empty()) return;
  {
    JLOCKSCOPE(_objectsmu);
    if(_objects.empty()) {
      _objects.swap(obj);
    }else{
      _objects.insert(_objects.end(), obj.begin(), obj.end());
    }
    _gcLastLiveObjCount += obj.size();
  }
  obj.clear();
}

petabricks::EncodedPtr petabricks::RemoteHost::asEncoded(RemoteObject* obj) const {
  return EncodeDataPtr(obj);
}


void petabricks::RemoteHost::spawnGcTask() {
  createRemoteObject(DistributedGC::gen(), &DistributedGC::gen);
}

void petabricks::RemoteHost::addObject(const RemoteObjectPtr& obj) {
  _objectsmu.lock();
  _objects.push_back(obj);

  if(_shouldGc && _objects.size()-_gcLastLiveObjCount > DISTRIBUTED_GC_FREQ){
    _gcLastLiveObjCount = _objects.size();
    _objectsmu.unlock();
    spawnGcTask();
  }else{
    _objectsmu.unlock();
  }
}

petabricks::RemoteHostDB::RemoteHostDB()
  : _port(LISTEN_PORT_FIRST),
    _listener(jalib::JSockAddr::ANY, LISTEN_PORT_FIRST),
    _nfds(0),
    _ready(0),
    _fds(NULL)
{
  while(!_listener.isValid()) {
    //    JTRACE("trying next port")(_port);
    JASSERT(_port < LISTEN_PORT_FIRST+512)(_port);
    _listener = jalib::JServerSocket(jalib::JSockAddr::ANY, ++_port);
  }
  _listener.enablePortReuse();
  char buf[1024];
  JASSERT(gethostname(buf, sizeof buf) >= 0);
  _host = buf;
#ifdef COUNT_CONNECTIONS
  _numSends = 0;
  _numBytes = 0;
#endif
}

void petabricks::RemoteHostDB::accept(const char* host, bool isMaster){
  JLOCKSCOPE(_mu);
  RemoteHostPtr h = new RemoteHost(host);
  if (isMaster) {
    h->acceptMasterControl(_listener, _port);
  } else {
    h->accept(_listener, _port);
  }
  _hosts.push_back(h);
}

void petabricks::RemoteHostDB::connect(const char* host, int port, bool isMaster){
  JLOCKSCOPE(_mu);
  RemoteHostPtr h = new RemoteHost(host);
  if (isMaster) {
    h->connectMasterControl(host, port, _port);
  } else {
    h->connect(host, port, _port);
  }
  _hosts.push_back(h);
}

void petabricks::RemoteHostDB::remotefork(const char* host, int oargc, const char** oargv, const char* slavehost, const char* slaveport) {
  std::string hoststr = this->host();
  std::string portstr = jalib::XToString(this->port());
  char cwd[1024];
  memset(cwd, 0, sizeof cwd);
  const char** argv = new const char*[oargc+32];
  int i=0;
  int j=0;
  if(host!=NULL) {
    JASSERT(getcwd(cwd, sizeof cwd) != 0);
    argv[i++] = "/usr/bin/ssh";
    argv[i++] = host;
    argv[i++] = "cd";
    argv[i++] = cwd;
    argv[i++] = "&&";
  }
  for(; j<oargc; ++j,++i) argv[i] = oargv[j];
  if(slavehost!=NULL)
    argv[i++] = slavehost;
  argv[i++] = hoststr.c_str();
  if(slaveport!=NULL)
    argv[i++] = slaveport;
  argv[i++] = portstr.c_str();
  argv[i++] = NULL;

  if(fork()==0){
    for(int i=3; i<1024; ++i)
      close(i);
    JTRACE("forked child proc");
    //jalib::JPrintable::printStlList(std::cerr, argv, argv + i, " ");
    execv(argv[0], (char**)argv);
    JASSERT(false);
  }
  delete[] argv;
}

void petabricks::RemoteHostDB::regenPollFds() {
  delete[] _fds;
  _nfds = _hosts.size();
  _fds = new struct pollfd[_nfds];
  struct pollfd *fd;
  RemoteHostList::iterator i;
  for(i=_hosts.begin(), fd=_fds; i!=_hosts.end(); ++i, ++fd) {
    fd->fd = (*i)->fd();
    fd->events = POLLIN;
    fd->revents = 0;
  }
}
void petabricks::RemoteHostDB::listenLoop() {
  JLOCKSCOPE(_mu);
  struct pollfd *fd;
  RemoteHostList::iterator i;
  if (_hosts.size() == 0) {
    return;
  }
  for(bool workDone = true; true; workDone = false) {

    for(i=_hosts.begin(), fd=_fds; i!=_hosts.end() && _ready>0; ++i, ++fd) {
      JASSERT(0 == (fd->revents & ~POLLIN))
      ((*i)->id()).Text("connection closed");
      if(0 != (fd->revents & POLLIN)) {
        fd->revents = 0;
        --_ready;
        _mu.unlock();
        if((*i)->recv()){
          workDone = true;
          while((*i)->recv()){}
        }
        _mu.lock();
      }
    }

    if(!workDone) {
      _mu.unlock();
      if(theListenersShutdown) {
        return;
      }
      pthread_yield();
      _mu.lock();
    }

    if(_ready == 0) {
      _ready=poll(_fds, _nfds, -1);
    }
    JASSERT(_ready>0);
  }

}

void petabricks::RemoteHostDB::setupConnectAllPairs() {
  RemoteHostDB::instance().setAllocHostNumber(0);
  for (unsigned int a = 0; a < _hosts.size(); a++) {
    host(a)->setupRemoteConnectionWithMaster(a+1);
  }
  for (unsigned int a = 0; a < _hosts.size(); a++) {
    for (unsigned int b = a+1; b < _hosts.size(); b++) {
      RemoteHost::setupRemoteConnection(*host(a), *host(b));
    }
  }
  for (unsigned int a = 0; a < _hosts.size(); a++) {
    host(a)->setupEnd();
  }
}

void petabricks::RemoteHostDB::spawnListenThread() {
  static bool firstTime = true;
  if (firstTime) {
    regenPollFds();
    firstTime = false;
  }
  pthread_t t;
  JASSERT(0==pthread_create(&t, 0, start_listenLoop, this));
  JASSERT(0==pthread_detach(t));
}

petabricks::RemoteHostDB& petabricks::RemoteHostDB::instance() {
  static RemoteHostDB db;
  return db;
}

jalib::JCondMutex theShutdownMu;
void petabricks::RemoteHostDB::onShutdownEvent() {
  JLOCKSCOPE(theShutdownMu);
  theShutdownMu.signal();
}
void petabricks::RemoteHostDB::shutdown() {
  JLOCKSCOPE(theShutdownMu);

#ifdef COUNT_CONNECTIONS
  RemoteHostDB& hostdb = RemoteHostDB::instance();
  JTRACE("counts")(hostdb._numSends)(hostdb._numBytes);
#endif

  RemoteHostList::iterator i;
  for(i=_hosts.begin(); i!=_hosts.end(); ++i) {
    (*i)->shutdownBegin();
  }
  for(i=_hosts.begin(); i!=_hosts.end(); ++i) {
    while(!(*i)->isShuttingDown()){
      theShutdownMu.wait();
    }
  }
  for(i=_hosts.begin(); i!=_hosts.end(); ++i) {
    (*i)->shutdownEnd();
  }
}



