// -*- C++ -*-

/**
 * @file alignedmmap.h
 * @author Emery Berger <http://www.cs.umass.edu/~emery>
 */


#ifndef _ALIGNEDMMAP_H_
#define _ALIGNEDMMAP_H_

#if defined(_WIN32)
//#error "You should not include this header on Windows."
#endif

#include "sassert.h"
#include "myhashmap.h"
#include "stlallocator.h"
#include "freelistheap.h"
#include "mmapwrapper.h"
#include "bumpalloc.h"
#include "exactlyone.h"
#include "mmapalloc.h"

using namespace std;

/**
 * @class AlignedMmapInstance
 * @brief Memory allocated from here is aligned with respect to Alignment.
 * @author Emery Berger <http://www.cs.umass.edu/~emery>
 */


template <size_t Alignment_>
class AlignedMmapInstance {
public:

  enum { Alignment = Alignment_ };

  inline void * malloc (size_t sz) {

    // Round up sz to the nearest page.
    sz = (sz + HL::MmapWrapper::Size - 1) & ~(HL::MmapWrapper::Size - 1);

    // If the memory is already suitably aligned, just track size requests.
    if ((size_t) HL::MmapWrapper::Alignment % (size_t) Alignment == 0) {
      void * ptr = HL::MmapWrapper::map (sz);
      MyMap.set (ptr, sz);
      return ptr;
    }

    // Otherwise, we have to align it ourselves. We get memory from
    // mmap, align a pointer in the space, and free the space before
    // and after the aligned segment.

    char * ptr = reinterpret_cast<char *>(HL::MmapWrapper::map (sz + Alignment_));

    if (ptr == NULL) {
      fprintf (stderr, "AlignedMmap::malloc - no memory.\n");
      return NULL;
    }

    char * newptr = align (ptr);

    // Unmap the part before (prolog) and after.

    size_t prolog = (size_t) newptr - (size_t) ptr;

    if (prolog > 0) {
      // Get rid of the prolog.
      HL::MmapWrapper::unmap (ptr, prolog);
    }

    HL::MmapWrapper::unmap ((char *) newptr + sz, Alignment_ - prolog);

    // Now record the size associated with this pointer.

    MyMap.set (newptr, sz);
    assert (MyMap.get (newptr) == sz);

    assert (reinterpret_cast<size_t>(newptr) % Alignment_ == 0);

    return newptr;
  }

  inline void free (void * ptr) {

    // Find the object. If we don't find it, we didn't allocate it.
    // For now, just ignore such an invalid free...

    size_t requestedSize = MyMap.get (ptr);

    if (requestedSize == 0) {
      return;
    }

    HL::MmapWrapper::unmap (ptr, requestedSize);

    // Finally, undo the mapping.
    MyMap.erase (ptr);

    assert (MyMap.get (ptr) == 0);
  }
  
  inline size_t getSize (void * ptr) {
    return MyMap.get (ptr);
  }


private:

  /// Round a pointer up to the next Alignment-rounded chunk.
  inline static char * align (char * buf) {
    return (char *)(((size_t) buf + (Alignment_-1)) & ~(Alignment_-1));
  }

  // Manage information in a map that uses a custom heap for
  // allocation.

  /// The key is an mmapped pointer.
  typedef const void * keyType;

  /// The value is the requested size.
  typedef size_t valType;

  // The heap from which memory comes for the Map's purposes.
  // Objects come from chunks via mmap, and we manage these with a free list.
  class SourceHeap : public HL::FreelistHeap<BumpAlloc<16384, MmapAlloc> > { };

  /// The map type, with all the pieces in place.
  typedef MyHashMap<keyType, valType, SourceHeap> mapType;

  /// The map that maintains the size of each mmapped chunk.
  mapType MyMap;

};


/**
 * @class AlignedMmap
 * @brief Route requests to the one aligned mmap instance.
 * @author Emery Berger <http://www.cs.umass.edu/~emery>
 */

template <size_t Alignment_>
class AlignedMmap : public ExactlyOne<AlignedMmapInstance<Alignment_> > {
public:

  enum { Alignment = Alignment_ };

  inline void * malloc (size_t sz) {
    return (*this)().malloc (sz);
  }
  inline void free (void * ptr) {
    return (*this)().free (ptr);
  }
  inline size_t getSize (void * ptr) const {
    return (*this)().getSize (ptr);
  }
 
};


#endif
