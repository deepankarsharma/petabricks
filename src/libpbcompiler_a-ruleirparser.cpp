/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         ruleirparse
#define yylex           ruleirlex
#define yyerror         ruleirerror
#define yylval          ruleirlval
#define yychar          ruleirchar
#define yydebug         ruleirdebug
#define yynerrs         ruleirnerrs
#define yylloc          ruleirlloc

/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 27 "ruleirparser.ypp"


#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif

#include "ruleir.h"
#include "formula.h"
#include "common/jconvert.h"
#include "common/srcpos.h"
#include <stdio.h>
#include <map>

#include "libpbcompiler_a-ruleirparser.h"

using namespace petabricks;

extern int ruleirlineno;
extern std::string ruleirfilename;

extern int yylex (void);
static int yyerror(const RIRBlockCopyRef&, const char* msg){ 
  JASSERT(false)(ruleirfilename)
                (ruleirlineno)
                (msg)
                .Text("parse error"); 
  return 0;
}

//   template<typename T>
//   T* debugtagpos(T* t) {
//     JTRACE("TAGPOS")(t->srcPos())(ruleirlineno)(ruleirfilename);
//     return t;
//   }

static jalib::JRefPool theRefPool;
#define P(A) (TAGPOS(A, yylloc))
#define REFALLOC(args...) P(theRefPool.add(new args))


static void clearParserCaches(){
  theRefPool.clear();
}
void ruleirparser_addRefPoolItem(jalib::JRefCounted* i){
  theRefPool.add(i);
}

#define YYLEX_PARAM &yylval, &yylloc
extern int ruleirlex(YYSTYPE * yylval_param,YYLTYPE * yylloc_param);

/* Line 371 of yacc.c  */
#line 128 "libpbcompiler_a-ruleirparser.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_RULEIR_Y_TAB_H_INCLUDED
# define YY_RULEIR_Y_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int ruleirdebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOK_SPAWN = 258,
     TOK_FORENOUGH = 259,
     TOK_DEFAULT = 260,
     TOK_CASE = 261,
     TOK_SWITCH = 262,
     TOK_RAW = 263,
     TOK_CONTINUE = 264,
     TOK_BREAK = 265,
     TOK_RETURN = 266,
     TOK_DO = 267,
     TOK_WHILE = 268,
     TOK_FOR = 269,
     TOK_ELSE = 270,
     TOK_THEN = 271,
     TOK_IF = 272,
     TOK_IDENT = 273,
     TOK_LIT = 274,
     TOK_OP = 275
   };
#endif
/* Tokens.  */
#define TOK_SPAWN 258
#define TOK_FORENOUGH 259
#define TOK_DEFAULT 260
#define TOK_CASE 261
#define TOK_SWITCH 262
#define TOK_RAW 263
#define TOK_CONTINUE 264
#define TOK_BREAK 265
#define TOK_RETURN 266
#define TOK_DO 267
#define TOK_WHILE 268
#define TOK_FOR 269
#define TOK_ELSE 270
#define TOK_THEN 271
#define TOK_IF 272
#define TOK_IDENT 273
#define TOK_LIT 274
#define TOK_OP 275



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 79 "ruleirparser.ypp"

  const char* str;
  petabricks::RIRExpr*  expr;
  petabricks::RIRStmt*  stmt;
  petabricks::RIRBlock* block;


/* Line 387 of yacc.c  */
#line 219 "libpbcompiler_a-ruleirparser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE ruleirlval;
extern YYLTYPE ruleirlloc;
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int ruleirparse (void *YYPARSE_PARAM);
#else
int ruleirparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int ruleirparse (petabricks::RIRBlockCopyRef& ret);
#else
int ruleirparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_RULEIR_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 260 "libpbcompiler_a-ruleirparser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   328

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  28
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNRULES -- Number of states.  */
#define YYNSTATES  110

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   275

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      22,    23,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    26,    21,
       2,     2,     2,    27,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    24,     2,    25,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    13,    16,    18,    20,
      22,    24,    26,    28,    30,    32,    38,    46,    52,    60,
      63,    73,    79,    87,    93,    97,   101,   104,   107,   110,
     113,   116,   118,   120,   122,   125,   127,   130,   132,   134,
     136,   138,   140,   142,   144,   146,   148,   153,   159,   163,
     165,   167,   169,   171,   173,   175
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      29,     0,    -1,    30,    -1,    30,    31,    -1,    52,    -1,
      42,    21,    -1,    52,    21,    -1,    32,    -1,    34,    -1,
      33,    -1,    38,    -1,    36,    -1,    37,    -1,    35,    -1,
      39,    -1,    17,    22,    41,    23,    31,    -1,    17,    22,
      41,    23,    31,    15,    31,    -1,     7,    22,    41,    23,
      31,    -1,     4,    22,    41,    21,    41,    23,    31,    -1,
       4,    31,    -1,    14,    22,    40,    21,    40,    21,    40,
      23,    31,    -1,    13,    22,    41,    23,    31,    -1,    12,
      31,    13,    22,    41,    23,    21,    -1,    42,    24,    42,
      25,    21,    -1,    24,    30,    25,    -1,    11,    41,    21,
      -1,    11,    21,    -1,    10,    21,    -1,     9,    21,    -1,
       6,    41,    -1,     5,    26,    -1,     8,    -1,    41,    -1,
      52,    -1,    41,    43,    -1,    43,    -1,    42,    43,    -1,
      43,    -1,    49,    -1,    44,    -1,    50,    -1,    51,    -1,
      45,    -1,    46,    -1,    27,    -1,    26,    -1,    51,    22,
      48,    23,    -1,     3,    51,    22,    48,    23,    -1,    22,
      41,    23,    -1,    41,    -1,    52,    -1,    47,    -1,    20,
      -1,    19,    -1,    18,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   108,   108,   112,   113,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   126,   131,   136,   141,   145,
     149,   156,   163,   168,   176,   180,   186,   190,   194,   199,
     205,   213,   218,   219,   221,   222,   224,   225,   227,   228,
     229,   230,   231,   232,   234,   235,   237,   242,   249,   256,
     258,   259,   261,   262,   263,   265
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_SPAWN", "TOK_FORENOUGH",
  "TOK_DEFAULT", "TOK_CASE", "TOK_SWITCH", "TOK_RAW", "TOK_CONTINUE",
  "TOK_BREAK", "TOK_RETURN", "TOK_DO", "TOK_WHILE", "TOK_FOR", "TOK_ELSE",
  "TOK_THEN", "TOK_IF", "TOK_IDENT", "TOK_LIT", "TOK_OP", "';'", "'('",
  "')'", "'{'", "'}'", "':'", "'?'", "$accept", "Start", "Block", "Stmt",
  "IfStmt", "SwitchStmt", "LoopStmt", "IntlzrStmt", "BlockStmt",
  "ReturnStmt", "CaseStmt", "RawStmt", "OptExpr", "Expr", "RootExpr",
  "ExprElement", "ExtraOps", "Call", "Paren", "Args", "OptArgs", "Op",
  "Lit", "Ident", "Nil", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,    59,    40,    41,   123,   125,    58,    63
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    28,    29,    30,    30,    31,    31,    31,    31,    31,
      31,    31,    31,    31,    31,    32,    32,    33,    34,    34,
      34,    34,    34,    35,    36,    37,    37,    37,    37,    38,
      38,    39,    40,    40,    41,    41,    42,    42,    43,    43,
      43,    43,    43,    43,    44,    44,    45,    45,    46,    47,
      48,    48,    49,    50,    51,    52
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     7,     5,     7,     2,
       9,     5,     7,     5,     3,     3,     2,     2,     2,     2,
       2,     1,     1,     1,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     5,     3,     1,
       1,     1,     1,     1,     1,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      55,     0,     2,     4,     1,     0,    55,     0,     0,     0,
      31,     0,     0,     0,    55,     0,     0,     0,    54,    53,
      52,     0,    55,    45,    44,     3,     7,     9,     8,    13,
      11,    12,    10,    14,     0,    37,    39,    42,    43,    38,
      40,    41,     0,     0,     0,    19,    30,    29,    35,     0,
      28,    27,    26,     0,     0,     0,    55,     0,     0,    55,
       5,     0,    36,    55,     6,    55,     0,    34,     0,    25,
       0,     0,     0,    32,    33,     0,    48,    24,     0,    49,
      51,     0,    50,     0,     0,    55,     0,    55,    55,    55,
       0,    46,    47,     0,    17,     0,    21,     0,    15,    23,
      55,     0,    55,    55,    18,    22,     0,    16,    55,    20
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    72,    73,    34,    48,    36,    37,    38,    80,
      81,    39,    40,    41,    42
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -88
static const yytype_int16 yypact[] =
{
     -88,     5,   151,   -88,   -88,   -12,   201,   -19,   301,   -14,
     -88,    -5,    -4,    99,   226,    -1,     0,     1,   -88,   -88,
     -88,   301,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,
     -88,   -88,   -88,   -88,     7,   -88,   -88,   -88,   -88,   -88,
     -88,     8,    20,    24,   301,   -88,   -88,   -13,   -88,   301,
     -88,   -88,   -88,   120,     6,   301,   301,   301,   238,   176,
     -88,   301,   -88,   301,   -88,   301,    17,   -88,   248,   -88,
      25,   259,    21,   301,   -88,   269,   -88,   -88,   109,   301,
     -88,    26,   -88,    27,   301,   226,   301,   226,   301,   226,
      31,   -88,   -88,   280,   -88,   290,   -88,    32,     3,   -88,
     226,    33,   301,   226,   -88,   -88,    37,   -88,   226,   -88
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -88,   -88,    39,    -3,   -88,   -88,   -88,   -88,   -88,   -88,
     -88,   -88,   -87,    67,    -6,    -2,   -88,   -88,   -88,   -88,
     -17,   -88,   -88,    57,     2
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -56
static const yytype_int8 yytable[] =
{
      35,    97,     3,    45,    35,     4,    18,    46,    49,    21,
       5,    54,    35,    23,    24,   106,    50,    51,   103,    70,
       5,    55,    56,    57,     3,    18,    19,    20,    60,    21,
      63,    61,    62,    23,    24,    18,    19,    20,    84,    21,
      76,    64,    88,    23,    24,    67,    65,    86,    83,    91,
      92,    67,    99,   102,   105,    78,    67,    35,    74,    35,
     108,    59,    43,     0,    67,    82,    67,    82,     0,    67,
       0,    67,     0,    67,     0,    47,    62,    67,     0,     0,
      53,     0,    94,    35,    96,    35,    98,    35,    58,     0,
      74,    67,     0,    67,     0,     0,     0,   104,    35,     0,
     107,    35,     5,     0,    74,   109,    35,     0,     0,     0,
       0,    66,     5,     0,     0,     0,    68,    18,    19,    20,
      52,    21,    71,     5,    75,    23,    24,    18,    19,    20,
      79,    21,    79,     0,    90,    23,    24,     0,    18,    19,
      20,    69,    21,     0,     0,     0,    23,    24,     0,     0,
       0,    93,     0,    95,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,     0,     0,    17,    18,
      19,    20,   -55,    21,     0,    22,     0,    23,    24,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,     0,     0,    17,    18,    19,    20,     0,    21,     0,
      22,    77,    23,    24,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,     0,     0,    17,    18,
      19,    20,     0,    44,     0,    22,     0,    23,    24,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,     5,     0,    17,    18,    19,    20,     0,    21,     0,
      22,     5,    23,    24,     0,     0,    18,    19,    20,     0,
      21,    76,     5,     0,    23,    24,    18,    19,    20,     0,
      21,    85,     5,     0,    23,    24,     0,    18,    19,    20,
       0,    21,    87,     5,     0,    23,    24,    18,    19,    20,
       0,    21,    89,     5,     0,    23,    24,     0,    18,    19,
      20,     0,    21,   100,     5,     0,    23,    24,    18,    19,
      20,     0,    21,   101,     0,     0,    23,    24,     0,    18,
      19,    20,     0,    21,     0,     0,     0,    23,    24
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-88)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       2,    88,     0,     6,     6,     0,    18,    26,    22,    22,
       3,    14,    14,    26,    27,   102,    21,    21,    15,    13,
       3,    22,    22,    22,    22,    18,    19,    20,    21,    22,
      22,    24,    34,    26,    27,    18,    19,    20,    21,    22,
      23,    21,    21,    26,    27,    47,    22,    22,    65,    23,
      23,    53,    21,    21,    21,    61,    58,    59,    56,    61,
      23,    22,     5,    -1,    66,    63,    68,    65,    -1,    71,
      -1,    73,    -1,    75,    -1,     8,    78,    79,    -1,    -1,
      13,    -1,    85,    85,    87,    87,    89,    89,    21,    -1,
      88,    93,    -1,    95,    -1,    -1,    -1,   100,   100,    -1,
     103,   103,     3,    -1,   102,   108,   108,    -1,    -1,    -1,
      -1,    44,     3,    -1,    -1,    -1,    49,    18,    19,    20,
      21,    22,    55,     3,    57,    26,    27,    18,    19,    20,
      63,    22,    65,    -1,    25,    26,    27,    -1,    18,    19,
      20,    21,    22,    -1,    -1,    -1,    26,    27,    -1,    -1,
      -1,    84,    -1,    86,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    -1,    -1,    17,    18,
      19,    20,    21,    22,    -1,    24,    -1,    26,    27,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    -1,    -1,    17,    18,    19,    20,    -1,    22,    -1,
      24,    25,    26,    27,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    -1,    -1,    17,    18,
      19,    20,    -1,    22,    -1,    24,    -1,    26,    27,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,     3,    -1,    17,    18,    19,    20,    -1,    22,    -1,
      24,     3,    26,    27,    -1,    -1,    18,    19,    20,    -1,
      22,    23,     3,    -1,    26,    27,    18,    19,    20,    -1,
      22,    23,     3,    -1,    26,    27,    -1,    18,    19,    20,
      -1,    22,    23,     3,    -1,    26,    27,    18,    19,    20,
      -1,    22,    23,     3,    -1,    26,    27,    -1,    18,    19,
      20,    -1,    22,    23,     3,    -1,    26,    27,    18,    19,
      20,    -1,    22,    23,    -1,    -1,    26,    27,    -1,    18,
      19,    20,    -1,    22,    -1,    -1,    -1,    26,    27
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    29,    30,    52,     0,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    17,    18,    19,
      20,    22,    24,    26,    27,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    42,    43,    44,    45,    46,    49,
      50,    51,    52,    51,    22,    31,    26,    41,    43,    22,
      21,    21,    21,    41,    31,    22,    22,    22,    41,    30,
      21,    24,    43,    22,    21,    22,    41,    43,    41,    21,
      13,    41,    40,    41,    52,    41,    23,    25,    42,    41,
      47,    48,    52,    48,    21,    23,    22,    23,    21,    23,
      25,    23,    23,    41,    31,    41,    31,    40,    31,    21,
      23,    23,    21,    15,    31,    21,    40,    31,    23,    31
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (ret, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

__attribute__((__unused__))
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
#else
static unsigned
yy_location_print_ (yyo, yylocp)
    FILE *yyo;
    YYLTYPE const * const yylocp;
#endif
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += fprintf (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += fprintf (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += fprintf (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += fprintf (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += fprintf (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location, ret); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, petabricks::RIRBlockCopyRef& ret)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, ret)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    petabricks::RIRBlockCopyRef& ret;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (ret);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, petabricks::RIRBlockCopyRef& ret)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, ret)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    petabricks::RIRBlockCopyRef& ret;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, ret);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, petabricks::RIRBlockCopyRef& ret)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, ret)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    petabricks::RIRBlockCopyRef& ret;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , ret);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, ret); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, petabricks::RIRBlockCopyRef& ret)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, ret)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    petabricks::RIRBlockCopyRef& ret;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (ret);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;


/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (petabricks::RIRBlockCopyRef& ret)
#else
int
yyparse (ret)
    petabricks::RIRBlockCopyRef& ret;
#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1787 of yacc.c  */
#line 108 "ruleirparser.ypp"
    {
  ret=(yyvsp[(1) - (1)].block);
}
    break;

  case 3:
/* Line 1787 of yacc.c  */
#line 112 "ruleirparser.ypp"
    {((yyval.block)=(yyvsp[(1) - (2)].block))->addStmt((yyvsp[(2) - (2)].stmt));}
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 113 "ruleirparser.ypp"
    {(yyval.block)=REFALLOC(RIRBlock());}
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 115 "ruleirparser.ypp"
    {((yyval.stmt)=REFALLOC(RIRBasicStmt()))->addExpr((yyvsp[(1) - (2)].expr));}
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 116 "ruleirparser.ypp"
    {((yyval.stmt)=REFALLOC(RIRBasicStmt()));}
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 117 "ruleirparser.ypp"
    {(yyval.stmt)=(yyvsp[(1) - (1)].stmt);}
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 118 "ruleirparser.ypp"
    {(yyval.stmt)=(yyvsp[(1) - (1)].stmt);}
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 119 "ruleirparser.ypp"
    {(yyval.stmt)=(yyvsp[(1) - (1)].stmt);}
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 120 "ruleirparser.ypp"
    {(yyval.stmt)=(yyvsp[(1) - (1)].stmt);}
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 121 "ruleirparser.ypp"
    {(yyval.stmt)=(yyvsp[(1) - (1)].stmt);}
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 122 "ruleirparser.ypp"
    {(yyval.stmt)=(yyvsp[(1) - (1)].stmt);}
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 123 "ruleirparser.ypp"
    {(yyval.stmt)=(yyvsp[(1) - (1)].stmt);}
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 124 "ruleirparser.ypp"
    {(yyval.stmt)=(yyvsp[(1) - (1)].stmt);}
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 126 "ruleirparser.ypp"
    {
  (yyval.stmt)=REFALLOC(RIRIfStmt((yyvsp[(5) - (5)].stmt)));
  (yyval.stmt)->addExpr((yyvsp[(3) - (5)].expr));
}
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 131 "ruleirparser.ypp"
    {
  (yyval.stmt)=REFALLOC(RIRIfStmt((yyvsp[(5) - (7)].stmt), (yyvsp[(7) - (7)].stmt)));
  (yyval.stmt)->addExpr((yyvsp[(3) - (7)].expr));
}
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 136 "ruleirparser.ypp"
    {
  (yyval.stmt)=REFALLOC(RIRSwitchStmt((yyvsp[(5) - (5)].stmt)));
  (yyval.stmt)->addExpr((yyvsp[(3) - (5)].expr));
}
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 141 "ruleirparser.ypp"
    {
  (yyval.stmt)=REFALLOC(RIRLoopStmt((yyvsp[(7) - (7)].stmt)))->initForEnough((yyvsp[(3) - (7)].expr), (yyvsp[(5) - (7)].expr));
}
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 145 "ruleirparser.ypp"
    {
  (yyval.stmt)=REFALLOC(RIRLoopStmt((yyvsp[(2) - (2)].stmt)))->initForEnough();
}
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 149 "ruleirparser.ypp"
    {
  (yyval.stmt)=REFALLOC(RIRLoopStmt((yyvsp[(9) - (9)].stmt)));
  (yyval.stmt)->addExpr((yyvsp[(3) - (9)].expr));
  (yyval.stmt)->addExpr((yyvsp[(5) - (9)].expr));
  (yyval.stmt)->addExpr((yyvsp[(7) - (9)].expr));
}
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 156 "ruleirparser.ypp"
    {
  (yyval.stmt)=REFALLOC(RIRLoopStmt((yyvsp[(5) - (5)].stmt)));
  (yyval.stmt)->addExpr(REFALLOC(RIRNilExpr()));
  (yyval.stmt)->addExpr((yyvsp[(3) - (5)].expr));
  (yyval.stmt)->addExpr(REFALLOC(RIRNilExpr()));
}
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 163 "ruleirparser.ypp"
    {
  (yyval.stmt)=REFALLOC(RIRLoopStmt((yyvsp[(2) - (7)].stmt)));
  UNIMPLEMENTED();
}
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 168 "ruleirparser.ypp"
    {
  (yyval.stmt)=REFALLOC(RIRBasicStmt());
  (yyval.stmt)->addExpr((yyvsp[(1) - (5)].expr));
  (yyval.stmt)->addExpr(REFALLOC(RIROpExpr("{")));
  (yyval.stmt)->addExpr((yyvsp[(3) - (5)].expr));
  (yyval.stmt)->addExpr(REFALLOC(RIROpExpr("}")));
}
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 176 "ruleirparser.ypp"
    {
  (yyval.stmt)=REFALLOC(RIRBlockStmt((yyvsp[(2) - (3)].block)));
}
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 180 "ruleirparser.ypp"
    {
  (yyval.stmt)=REFALLOC(RIRReturnStmt());
  (yyval.stmt)->addExpr(REFALLOC(RIRKeywordExpr("return")));
  (yyval.stmt)->addExpr((yyvsp[(2) - (3)].expr));
}
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 186 "ruleirparser.ypp"
    {
  (yyval.stmt)=REFALLOC(RIRReturnStmt());
  (yyval.stmt)->addExpr(REFALLOC(RIRKeywordExpr("return")));
}
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 190 "ruleirparser.ypp"
    {
  (yyval.stmt)=REFALLOC(RIRBreakStmt());
  (yyval.stmt)->addExpr(REFALLOC(RIRKeywordExpr("break")));
}
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 194 "ruleirparser.ypp"
    {
  (yyval.stmt)=REFALLOC(RIRContinueStmt());
  (yyval.stmt)->addExpr(REFALLOC(RIRKeywordExpr("continue")));
}
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 199 "ruleirparser.ypp"
    {
  (yyval.stmt)=REFALLOC(RIRCaseStmt());
  (yyval.stmt)->addExpr(REFALLOC(RIRKeywordExpr("case")));
  (yyval.stmt)->addExpr((yyvsp[(2) - (2)].expr));
}
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 205 "ruleirparser.ypp"
    {
  (yyval.stmt)=REFALLOC(RIRCaseStmt());
  (yyval.stmt)->addExpr(REFALLOC(RIRKeywordExpr("default")));
  (yyval.stmt)->addExpr(REFALLOC(RIROpExpr(":")));
}
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 213 "ruleirparser.ypp"
    {
  (yyval.stmt)=REFALLOC(RIRRawStmt((yyvsp[(1) - (1)].str)));
}
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 218 "ruleirparser.ypp"
    {((yyval.expr)=(yyvsp[(1) - (1)].expr));}
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 219 "ruleirparser.ypp"
    {((yyval.expr)=REFALLOC(RIRChainExpr()));}
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 221 "ruleirparser.ypp"
    {((yyval.expr)=(yyvsp[(1) - (2)].expr))->addSubExpr((yyvsp[(2) - (2)].expr));}
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 222 "ruleirparser.ypp"
    {((yyval.expr)=REFALLOC(RIRChainExpr()))->addSubExpr((yyvsp[(1) - (1)].expr));}
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 224 "ruleirparser.ypp"
    {((yyval.expr)=(yyvsp[(1) - (2)].expr))->addSubExpr((yyvsp[(2) - (2)].expr));}
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 225 "ruleirparser.ypp"
    {((yyval.expr)=REFALLOC(RIRChainExpr()))->addSubExpr((yyvsp[(1) - (1)].expr));}
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 227 "ruleirparser.ypp"
    {(yyval.expr)=(yyvsp[(1) - (1)].expr);}
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 228 "ruleirparser.ypp"
    {(yyval.expr)=(yyvsp[(1) - (1)].expr);}
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 229 "ruleirparser.ypp"
    {(yyval.expr)=(yyvsp[(1) - (1)].expr);}
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 230 "ruleirparser.ypp"
    {(yyval.expr)=(yyvsp[(1) - (1)].expr);}
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 231 "ruleirparser.ypp"
    {(yyval.expr)=(yyvsp[(1) - (1)].expr);}
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 232 "ruleirparser.ypp"
    {(yyval.expr)=(yyvsp[(1) - (1)].expr);}
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 234 "ruleirparser.ypp"
    {(yyval.expr)=REFALLOC(RIROpExpr("?"));}
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 235 "ruleirparser.ypp"
    {(yyval.expr)=REFALLOC(RIROpExpr(":"));}
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 237 "ruleirparser.ypp"
    { 
  (yyval.expr)=REFALLOC(RIRCallExpr()); 
  (yyval.expr)->addSubExpr((yyvsp[(1) - (4)].expr));
  (yyval.expr)->addSubExpr((yyvsp[(3) - (4)].expr));
}
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 242 "ruleirparser.ypp"
    { 
  (yyval.expr)=REFALLOC(RIRCallExpr()); 
  (yyval.expr)->addSubExpr(REFALLOC(RIRKeywordExpr("spawn")));
  (yyval.expr)->addSubExpr((yyvsp[(2) - (5)].expr));
  (yyval.expr)->addSubExpr((yyvsp[(4) - (5)].expr));
}
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 249 "ruleirparser.ypp"
    {
  (yyval.expr)=REFALLOC(RIRChainExpr());
  (yyval.expr)->addSubExpr(REFALLOC(RIROpExpr("(")));
  (yyval.expr)->addSubExpr((yyvsp[(2) - (3)].expr));
  (yyval.expr)->addSubExpr(REFALLOC(RIROpExpr(")")));
}
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 256 "ruleirparser.ypp"
    { ((yyval.expr)=REFALLOC(RIRArgsExpr()))->addSubExpr((yyvsp[(1) - (1)].expr)); }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 258 "ruleirparser.ypp"
    {(yyval.expr)=REFALLOC(RIRArgsExpr());}
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 259 "ruleirparser.ypp"
    {(yyval.expr)=(yyvsp[(1) - (1)].expr);}
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 261 "ruleirparser.ypp"
    {(yyval.expr)=REFALLOC(RIROpExpr((yyvsp[(1) - (1)].str)));}
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 262 "ruleirparser.ypp"
    {(yyval.expr)=REFALLOC(RIRLitExpr((yyvsp[(1) - (1)].str)));}
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 263 "ruleirparser.ypp"
    {(yyval.expr)=REFALLOC(RIRIdentExpr((yyvsp[(1) - (1)].str)));}
    break;


/* Line 1787 of yacc.c  */
#line 2087 "libpbcompiler_a-ruleirparser.cpp"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (ret, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (ret, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc, ret);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, ret);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (ret, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, ret);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, ret);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2050 of yacc.c  */
#line 267 "ruleirparser.ypp"


void _ruleirlexer_scan_string( const std::string& str, const jalib::SrcPosTaggable* pos);

RIRBlockCopyRef parseRuleBody(const std::string& str, const jalib::SrcPosTaggable* pos){
  //JTRACE("Parsing rule body")(str);
  _ruleirlexer_scan_string(str, pos);
  RIRBlockCopyRef ret;
  ruleirparse(ret);
  clearParserCaches();
  return ret;
}


