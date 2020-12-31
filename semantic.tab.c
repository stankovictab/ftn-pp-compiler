/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 7 "semantic.y"

	#include <stdio.h>
	#include <stdlib.h>
	#include "defs.h"
	#include "symtab.h"
	#include <string.h> // Za strcmp

	int yyparse(void);
	int yylex(void);
	int yyerror(char *s);
	void warning(char *s);

	extern int yylineno;
	char char_buffer[CHAR_BUFFER_LENGTH];
	int error_count = 0;
	int warning_count = 0;
	int var_num = 0;
	int fun_idx = -1;
	int fcall_idx = -1;

	// Dodaci
	int vartype = 0;
	int return_flag = 0;
	int current_function = 0; // TODO: Zameni sa fun_idx jer izgleda da je to to vec definisano
	int parameter_number = 0;
	int argument_number = 0;
	unsigned switch_type = 0;
	int switch_number = 0;
	int switch_array[100] = {-2147483648}; // Sve se inicijalizuje na INT_MIN, niz se koristi za proveru vec koriscenih literala u switch_statement

#line 101 "semantic.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_SEMANTIC_TAB_H_INCLUDED
# define YY_YY_SEMANTIC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TYPE = 258,
    IF = 259,
    ELSE = 260,
    RETURN = 261,
    ID = 262,
    INT_NUMBER = 263,
    UINT_NUMBER = 264,
    LPAREN = 265,
    RPAREN = 266,
    LCURLYBRACKET = 267,
    RCURLYBRACKET = 268,
    ASSIGN = 269,
    SEMICOLON = 270,
    AROP = 271,
    RELOP = 272,
    VOIDTYPE = 273,
    COMMA = 274,
    INCREMENT = 275,
    FOR = 276,
    TO = 277,
    STEP = 278,
    SWITCH = 279,
    CASETOKEN = 280,
    ARROW = 281,
    OTHERWISE = 282,
    FINISH = 283,
    LSQUAREBRACKET = 284,
    RSQUAREBRACKET = 285,
    ONLY_IF = 286
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 38 "semantic.y"

	int i;
	char *s;

#line 190 "semantic.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SEMANTIC_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   130

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  135

#define YYUNDEFTOK  2
#define YYMAXUTOK   286


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    82,    82,    93,    94,    99,   112,    98,   130,   143,
     129,   161,   165,   174,   175,   179,   195,   201,   202,   207,
     206,   219,   237,   251,   252,   256,   257,   258,   259,   260,
     261,   262,   263,   267,   273,   285,   286,   294,   295,   302,
     303,   308,   311,   316,   317,   322,   321,   339,   351,   360,
     387,   409,   410,   414,   415,   419,   423,   431,   441,   451,
     459,   473,   487,   486,   511,   511,   524,   524,   536,   537,
     541,   542
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TYPE", "IF", "ELSE", "RETURN", "ID",
  "INT_NUMBER", "UINT_NUMBER", "LPAREN", "RPAREN", "LCURLYBRACKET",
  "RCURLYBRACKET", "ASSIGN", "SEMICOLON", "AROP", "RELOP", "VOIDTYPE",
  "COMMA", "INCREMENT", "FOR", "TO", "STEP", "SWITCH", "CASETOKEN",
  "ARROW", "OTHERWISE", "FINISH", "LSQUAREBRACKET", "RSQUAREBRACKET",
  "ONLY_IF", "$accept", "program", "function_list", "function", "$@1",
  "$@2", "$@3", "$@4", "parameters_full", "parameters", "parameter",
  "body", "variable_list", "variables_def", "$@5", "variables_only",
  "statement_list", "statement", "compound_statement",
  "assignment_statement", "num_exp", "exp", "literal",
  "increment_optional", "function_call", "$@6", "argument_list",
  "arguments", "if_statement", "if_part", "rel_exp", "return_statement",
  "increment_statement", "loop", "switch_statement", "$@7", "case_list",
  "$@8", "$@9", "finish_optional", "otherwise_optional", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286
};
# endif

#define YYPACT_NINF (-77)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-46)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       8,     0,     3,    17,     8,   -77,   -77,   -77,   -77,   -77,
      28,    72,    52,    52,    74,   -77,    64,   -77,   -77,   -77,
      73,    52,    75,    76,   -77,    76,   -77,   -77,   -77,    82,
     -77,   -77,     9,    80,    79,    59,   -11,   -77,    81,    61,
     -77,   -77,   -77,   -77,    77,   -77,    88,   -77,   -77,   -77,
     -77,   -77,    22,    63,    -6,   -77,   -77,    63,   -77,    12,
     -77,   -77,   -77,    63,    83,    84,    92,    89,   -77,    41,
     -77,    90,    26,    91,   -77,   -77,    23,   -77,    63,    45,
     -77,    68,    93,   -77,   -77,   -77,    63,    41,   -77,   -77,
     -77,   -77,   -77,    94,    85,    87,    69,    95,   -77,   -77,
      71,    55,    96,   -77,   -77,    97,    78,    55,    55,    24,
      -3,   -77,    55,    86,   100,    41,    55,    98,   -77,    41,
     -77,   -77,    99,    41,   101,   -77,    41,   102,    41,   -77,
     103,   -77,   102,   -77,   -77
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     2,     3,     5,     8,     1,     4,
       0,     0,    11,    11,     0,     6,    12,    13,     9,    15,
       0,     0,     0,     0,    14,     0,    17,     7,    10,    23,
      19,    18,     0,     0,     0,     0,    45,    16,     0,     0,
      33,    24,    25,    26,     0,    28,    53,    29,    30,    31,
      32,    21,     0,     0,    43,    41,    42,     0,    58,     0,
      35,    37,    39,     0,     0,     0,     0,     0,    27,     0,
      20,     0,     0,     0,    44,    38,     0,    57,     0,     0,
      59,    47,     0,    62,    54,    22,     0,     0,    40,    36,
      34,    49,    51,     0,    48,     0,     0,    56,    55,    46,
       0,     0,     0,    50,    52,     0,     0,     0,     0,    70,
       0,    64,     0,     0,     0,     0,     0,     0,    66,     0,
      63,    60,     0,     0,     0,    71,     0,    68,     0,    61,
       0,    65,    68,    69,    67
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -77,   -77,   -77,   105,   -77,   -77,   -77,   -77,   104,   -77,
     107,    33,   -77,   -77,   -77,   -77,   -77,   -69,   -77,   -77,
     -51,    29,   -76,   -77,   -34,   -77,   -77,   -77,   -77,   -77,
     -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -26,
     -77
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,    10,    20,    11,    22,    15,    16,
      17,    40,    29,    31,    33,    52,    32,    41,    42,    43,
      59,    60,    61,    75,    44,    65,    93,    94,    45,    46,
      73,    47,    48,    49,    50,    96,   109,   117,   124,   131,
     114
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      84,    62,    72,    63,   -45,    92,    76,     6,   115,    64,
       7,     1,    79,    34,    74,    35,    36,     8,    98,    62,
     116,    26,    37,    62,   104,   105,     2,    77,    78,    62,
      38,   110,   111,    39,    88,    97,   118,    70,    12,    78,
     122,    71,    78,    86,    62,    34,   121,    35,    36,   112,
     125,   113,    62,    26,   127,    14,    27,   129,    28,   132,
      90,    78,    38,    55,    56,    39,    54,    55,    56,    57,
      54,    55,    56,    57,    58,    91,    55,    56,   103,    55,
      56,    19,    13,    21,    23,    30,    25,    51,    26,    53,
      67,    66,    68,    69,    81,    82,    83,    85,    80,   102,
      95,   101,    87,   108,   100,    99,   134,    89,   106,     9,
     126,    78,   119,   120,     0,     0,     0,    18,   133,   107,
       0,     0,     0,     0,   123,     0,     0,   128,    24,     0,
     130
};

static const yytype_int16 yycheck[] =
{
      69,    35,    53,    14,    10,    81,    57,     7,    11,    20,
       7,     3,    63,     4,    20,     6,     7,     0,    87,    53,
      23,    12,    13,    57,   100,   101,    18,    15,    16,    63,
      21,   107,   108,    24,    11,    86,   112,    15,    10,    16,
     116,    19,    16,    17,    78,     4,   115,     6,     7,    25,
     119,    27,    86,    12,   123,     3,    23,   126,    25,   128,
      15,    16,    21,     8,     9,    24,     7,     8,     9,    10,
       7,     8,     9,    10,    15,     7,     8,     9,     7,     8,
       9,     7,    10,    19,    11,     3,    11,     7,    12,    10,
      29,    10,    15,     5,    10,     3,     7,     7,    15,    30,
       7,    14,    11,    25,    19,    11,   132,    78,    12,     4,
      11,    16,    26,    13,    -1,    -1,    -1,    13,    15,    22,
      -1,    -1,    -1,    -1,    26,    -1,    -1,    26,    21,    -1,
      28
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    18,    33,    34,    35,     7,     7,     0,    35,
      36,    38,    10,    10,     3,    40,    41,    42,    40,     7,
      37,    19,    39,    11,    42,    11,    12,    43,    43,    44,
       3,    45,    48,    46,     4,     6,     7,    13,    21,    24,
      43,    49,    50,    51,    56,    60,    61,    63,    64,    65,
      66,     7,    47,    10,     7,     8,     9,    10,    15,    52,
      53,    54,    56,    14,    20,    57,    10,    29,    15,     5,
      15,    19,    52,    62,    20,    55,    52,    15,    16,    52,
      15,    10,     3,     7,    49,     7,    17,    11,    11,    53,
      15,     7,    54,    58,    59,     7,    67,    52,    49,    11,
      19,    14,    30,     7,    54,    54,    12,    22,    25,    68,
      54,    54,    25,    27,    72,    11,    23,    69,    54,    26,
      13,    49,    54,    26,    70,    49,    11,    49,    26,    49,
      28,    71,    49,    15,    71
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    34,    34,    36,    37,    35,    38,    39,
      35,    40,    40,    41,    41,    42,    43,    44,    44,    46,
      45,    47,    47,    48,    48,    49,    49,    49,    49,    49,
      49,    49,    49,    50,    51,    52,    52,    53,    53,    53,
      53,    54,    54,    55,    55,    57,    56,    58,    58,    59,
      59,    59,    59,    60,    60,    61,    62,    63,    63,    64,
      65,    65,    67,    66,    69,    68,    70,    68,    71,    71,
      72,    72
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     0,     0,     8,     0,     0,
       8,     0,     1,     1,     3,     2,     4,     0,     2,     0,
       4,     1,     3,     0,     2,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     4,     1,     3,     1,     2,     1,
       3,     1,     1,     0,     1,     0,     5,     0,     1,     1,
       3,     1,     3,     1,     3,     5,     3,     3,     2,     3,
      10,    12,     0,     9,     0,     6,     0,     7,     0,     2,
       0,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
      yychar = yylex ();
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 83 "semantic.y"
                {  
			// Javlja gresku ako main() uopste ne postoji u tabeli simbola
			if(lookup_symbol("main", FUN) == NO_INDEX)
				err("Undefined reference to 'main'.\n");

			print_symtab();
		 }
#line 1470 "semantic.tab.c"
    break;

  case 5:
#line 99 "semantic.y"
                {
			// fun_idx je indeks ove funkcije
			// Trazimo da li postoji funkcija u tabeli
			fun_idx = lookup_symbol((yyvsp[0].s), FUN);
			if(fun_idx == NO_INDEX){
				// Ako ne postoji funkcija, dodaj je (bez atributa), i taj indeks stavi u current_function (indeks funkcije koja se obradjuje, koristi se u proverama za varijable kasnije, etc)
				fun_idx = insert_symbol((yyvsp[0].s), FUN, (yyvsp[-1].i), NO_ATR, NO_ATR);
				current_function = fun_idx;
				}
			else 
				err("Redefinition of function '%s'.\n", (yyvsp[0].s));
		}
#line 1487 "semantic.tab.c"
    break;

  case 6:
#line 112 "semantic.y"
                {
			// Kada analiziramo sve parametre update-ujemo broj parametra za simbol funkcije
			set_atr1(fun_idx, parameter_number);
		}
#line 1496 "semantic.tab.c"
    break;

  case 7:
#line 117 "semantic.y"
                {
			// Kada se funkcija zavrsi, moramo da izbrisemo sve njene varijable (ne diramo parametre, jer ih koristimo za pozive funkcija) - clear_symbols brise od ovog indeksa pa na dole, sto i ostavlja samo varijable, a ovaj indeks je pocetak varijabli
			clear_symbols(fun_idx + parameter_number + 1);
			var_num = 0;
			// Non-void funkcije moraju imati povratnu vrednost, pa koristimo flag da proverimo da li smo ga iskoristili
			if(return_flag == 0)
				warn("Function '%s' needs to have the 'return' keyword.\n", (yyvsp[-6].s));
			// Resetujemo return flag za nove funkcije
			return_flag = 0;
			// Resetujemo broj parametra za nove funkcije
			parameter_number = 0;
		}
#line 1513 "semantic.tab.c"
    break;

  case 8:
#line 130 "semantic.y"
                {
			// fun_idx je indeks ove funkcije
			// Trazimo da li postoji funkcija u tabeli
			fun_idx = lookup_symbol((yyvsp[0].s), FUN);
			if(fun_idx == NO_INDEX){
				// Ako ne postoji funkcija, dodaj je (bez atributa), i taj indeks stavi u current_function (indeks funkcije koja se obradjuje, koristi se u proverama za varijable kasnije, etc)
				fun_idx = insert_symbol((yyvsp[0].s), FUN, (yyvsp[-1].i), NO_ATR, NO_ATR);
				current_function = fun_idx;
			}
			else 
				err("Redefinition of function '%s'.\n", (yyvsp[0].s));
		}
#line 1530 "semantic.tab.c"
    break;

  case 9:
#line 143 "semantic.y"
                {
			// Kada analiziramo sve parametre update-ujemo broj parametra za simbol funkcije
			set_atr1(fun_idx, parameter_number);
		}
#line 1539 "semantic.tab.c"
    break;

  case 10:
#line 148 "semantic.y"
                {
			// Kada se funkcija zavrsi, moramo da izbrisemo sve njene varijable (ne diramo parametre, jer ih koristimo za pozive funkcija) - clear_symbols brise od ovog indeksa pa na dole, sto i ostavlja samo varijable, a ovaj indeks je pocetak varijabli
			clear_symbols(fun_idx + parameter_number + 1);
			var_num = 0;
			// Resetujemo return flag za nove funkcije
			return_flag = 0;
			// Resetujemo broj parametra za nove funkcije
			parameter_number = 0;
		}
#line 1553 "semantic.tab.c"
    break;

  case 11:
#line 161 "semantic.y"
                {
			// Postavljamo broj parametara funkcije na 0 ako nema parametara
			set_atr1(fun_idx, 0);
		}
#line 1562 "semantic.tab.c"
    break;

  case 15:
#line 180 "semantic.y"
                {
			// Za svaki parametar moramo da povecamo broj parametara za tabelu simbola
			parameter_number++;
			// Proveravamo da li je trenutni parametar vec definisan tako sto prolazimo kroz tabelu simbola od indeksa funkcija (nju ne ubrajamo) na nize, i gledamo nazive ostalih simbola do kraja tabele, jer se varijable jos uvek nisu definisale, pa bi uporedjivali samo parametre te funkcije
			for(int j = current_function + 1; j <= get_last_element(); j++){
				if(strcmp(get_name(j), (yyvsp[0].s)) == 0){
					err("Redifinition of parameter '%s'.\n", (yyvsp[0].s));
				}
			}
			// Ako ne dodje do greske znaci da ne postoji parametar sa takvim nazivom. Ovde smo mogli i current_function da stavimo.
			insert_symbol((yyvsp[0].s), PAR, (yyvsp[-1].i), 1, fun_idx);
		}
#line 1579 "semantic.tab.c"
    break;

  case 19:
#line 207 "semantic.y"
                {
			// Mora u ovoj akciji da se izmeni vartype, da bi mogao da se koristi u variables_only
			vartype = (yyvsp[0].i);
		}
#line 1588 "semantic.tab.c"
    break;

  case 20:
#line 212 "semantic.y"
                {
			// Kada smo iskoristili vartype, moramo da ga resetujemo (cim se napravi variables_def)
			vartype = 0;
		}
#line 1597 "semantic.tab.c"
    break;

  case 21:
#line 220 "semantic.y"
                {
			// Mora da proverava $1 sada, i da koristi vartype kao tip simbola
			// Pri deklarisanju varijable trebamo da proverimo da li vec u toj trenutnoj funkciji postoje varijable ili parametri sa tim imenom
			// To znaci da varijabla moze imati isto ime kao neka prethodna funkcija ili njeni parametri
			// Ne mozemo da gledamo po lookup_symbol(VAR|PAR) jer to gleda celu tabelu (od nazad pa do 13. registra (FUNREG)) - pravi problem zbog parametara, jer se oni ne brisu na kraju funkcije
			// Iteriramo od indeksa funkcije u kojoj je deklarisana varijabla (current_function) do kraja tabele simbola (get_last_element)
			// Poredimo imena sa svakim simbolom (varijable i parametri), i ako se poklopi javljamo gresku
			// Ako ne nadjemo nista da se poklapa, dodajemo u tabelu

			for(int i = current_function + 1; i <= get_last_element(); i++){
				// Mozemo da preskocimo prvi jer je to ustvari funkcija
				if(strcmp(get_name(i), (yyvsp[0].s)) == 0){
					err("Variable or parameter by the name '%s' already exists.\n", (yyvsp[0].s));
				}
			}
			insert_symbol((yyvsp[0].s), VAR, vartype, ++var_num, NO_ATR);
		}
#line 1619 "semantic.tab.c"
    break;

  case 22:
#line 238 "semantic.y"
                {
			// Ista provera i za ovu alternativu
			for(int i = current_function + 1; i <= get_last_element(); i++){
				// Mozemo da preskocimo prvi jer je to ustvari funkcija
				if(strcmp(get_name(i), (yyvsp[0].s)) == 0){
					err("Variable or parameter by the name '%s' already exists.\n", (yyvsp[0].s));
				}
			}
			insert_symbol((yyvsp[0].s), VAR, vartype, ++var_num, NO_ATR);
		}
#line 1634 "semantic.tab.c"
    break;

  case 34:
#line 274 "semantic.y"
                {
		int idx = lookup_symbol((yyvsp[-3].s), VAR|PAR);
		if(idx == NO_INDEX)
			err("Invalid lvalue '%s' in assignment.\n", (yyvsp[-3].s));
		else
			if(get_type(idx) != get_type((yyvsp[-1].i)))
			err("Incompatible types in assignment.\n");
		}
#line 1647 "semantic.tab.c"
    break;

  case 36:
#line 287 "semantic.y"
                {
		if(get_type((yyvsp[-2].i)) != get_type((yyvsp[0].i)))
			err("Invalid operands: arithmetic operation (incompatible types).\n");
		}
#line 1656 "semantic.tab.c"
    break;

  case 38:
#line 296 "semantic.y"
                {
			// Moglo je i da se odvoji na ID i ID INCREMENT ovde, mozda preglednije
			(yyval.i) = lookup_symbol((yyvsp[-1].s), VAR|PAR);
			if((yyval.i) == NO_INDEX)
				err("'%s' undeclared.\n", (yyvsp[-1].s));
		}
#line 1667 "semantic.tab.c"
    break;

  case 40:
#line 304 "semantic.y"
                { (yyval.i) = (yyvsp[-1].i); }
#line 1673 "semantic.tab.c"
    break;

  case 41:
#line 309 "semantic.y"
                { (yyval.i) = insert_literal((yyvsp[0].s), INT); }
#line 1679 "semantic.tab.c"
    break;

  case 42:
#line 312 "semantic.y"
                { (yyval.i) = insert_literal((yyvsp[0].s), UINT); }
#line 1685 "semantic.tab.c"
    break;

  case 45:
#line 322 "semantic.y"
                {
			// Ovo je indeks funkcije koju pozivamo u tabeli simbola, koristi se kod argumenata
			fcall_idx = lookup_symbol((yyvsp[0].s), FUN); 
			if(fcall_idx == NO_INDEX)
				err("'%s' is not a function.\n", (yyvsp[0].s));
		}
#line 1696 "semantic.tab.c"
    break;

  case 46:
#line 329 "semantic.y"
                {
			// Resetujemo broj argumenata za neki drugi poziv funkcije
			argument_number = 0;
			// function_call dobija semanticku vrednost
			(yyval.i) = lookup_symbol((yyvsp[-4].s), FUN);
		}
#line 1707 "semantic.tab.c"
    break;

  case 47:
#line 339 "semantic.y"
                {
			// current_function nije ono sto nam treba, treba da nadjemo atr1 (broj parametara) funkcije koje pozivamo
			// To radimo tako sto idemo od trenutne funkcije u tabeli simbola na gore i gledamo atr1 od simbola funkcije koju pozivamo
			// Ili samo uzmemo fcall_idx koji bas za to sluzi
			for(int j = current_function; j > FUN_REG; j--){ // FUN_REG je makro za 13
				//int argument = lookup_symbol(get_name(j), FUN);
				if(fcall_idx == j){
					if(get_atr1(fcall_idx) > 0)
						err("Function doesn't require any arguments.\n");
				}
			}
		}
#line 1724 "semantic.tab.c"
    break;

  case 49:
#line 361 "semantic.y"
                {
			// Ovo je samo za pozive funkcija koje imaju 1 parametar
			// Argument u pozivu funkcije moze da bude varijabla i parametar trenutne funkcije, pa njih trazimo
			// Ne mozemo da trazimo po VAR|PAR po celoj tabeli kao pre jer bi to uzelo i parametre drugih funkcija, tako da moramo samo za trenutnu
			int flag = 0;
			for(int j = current_function + 1; j <= get_last_element(); j++){
				int argument = lookup_symbol(get_name(j), VAR|PAR); 
				// Treba za else if, ok je ovde da stoji VAR|PAR jer ne moze ispod indeksa funkcije da nadje parametar neke druge
				if(strcmp(get_name(j), (yyvsp[0].s)) == 0){
					flag = 1;
					// Pronasao varijablu ili parametar te funkcije sa istim imenom
					argument_number = 1; // Sa 0 na 1
					// Ovo proverava broj parametara funkcije koja je pozvana
					if ((get_atr1(fcall_idx) == 1) && (argument_number != get_atr1(fcall_idx)))
						err("Wrong number of arguments sent over to function '%s'", get_name(fcall_idx));
					// Ako smo ovde dospeli, to znaci da funkcija ima tacno jedan parametar
					// Proveravamo da li je tip argumenta isti kao tip parametra
					// Taj parametar je na prvom indeksu ispod funkcije u tabeli simbola, pa je umesto ovog argument_number moglo da stoji i 1
					if (get_type(argument) != get_type(fcall_idx + argument_number)) 
						err("Forwarded argument '%s' of wrong type.\n", (yyvsp[0].s));
				}
			}
			if(flag == 0)
			// Ako ne nadje znaci da nije definisan
			err("Argument '%s' is not defined.\n", (yyvsp[0].s));
		}
#line 1755 "semantic.tab.c"
    break;

  case 50:
#line 388 "semantic.y"
                {
			// Za prvi argument u listi je vec uradio proveru gore, sad radi za ostale
			int flag = 0;
			for(int j = current_function + 1; j <= get_last_element(); j++){
				int argument = lookup_symbol(get_name(j), VAR|PAR); 
				// Treba za else if, ok je ovde da stoji VAR|PAR jer ne moze ispod indeksa funkcije da nadje parametar neke druge
				if(strcmp(get_name(j), (yyvsp[0].s)) == 0){
					flag = 1;
					// Pronasao varijablu ili parametar te funkcije sa istim imenom
					argument_number++; // Sa 1 na n
					// Ovo proverava broj parametara funkcije koja je pozvana
					if (argument_number > get_atr1(fcall_idx)) // Mora da bude > !
						err("Wrong number of arguments sent over to function '%s'", get_name(fcall_idx));
					if (get_type(argument) != get_type(fcall_idx + argument_number)) 
						err("Forwarded argument '%s' of wrong type.\n", (yyvsp[0].s));
				}
			}
			if(flag == 0)
			// Ako ne nadje znaci da nije definisan
			err("Argument '%s' is not defined.\n", (yyvsp[0].s));
		}
#line 1781 "semantic.tab.c"
    break;

  case 56:
#line 424 "semantic.y"
                {
			if(get_type((yyvsp[-2].i)) != get_type((yyvsp[0].i)))
				err("Invalid operands: relational operator.\n");
		}
#line 1790 "semantic.tab.c"
    break;

  case 57:
#line 432 "semantic.y"
                {
			// Javlja se return, postavljamo flag (cak iako tip povratne vrednosti nije dobar)
			return_flag = 1;
			if(get_type(fun_idx) != get_type((yyvsp[-1].i)))
				err("Incompatible types in return.\n");

			if(get_type(fun_idx) == VOID)
				err("Function of type VOID can't return an expression.\n");
		}
#line 1804 "semantic.tab.c"
    break;

  case 58:
#line 442 "semantic.y"
                {
			// Posto void funkcija ne zahteva return, ne moramo postavljati flag
			// Posto je ovo samo za void funkcije, za one koje nisu void moramo da kazemo da mora da vrati neki num_exp
			if(get_type(fun_idx) != VOID)
				warn("Non-void function has to return a value.\n");
		}
#line 1815 "semantic.tab.c"
    break;

  case 59:
#line 452 "semantic.y"
                {
			if(lookup_symbol((yyvsp[-2].s), VAR|PAR) == NO_INDEX)
        		err("'%s' is not declared.\n", (yyvsp[-2].s));
		}
#line 1824 "semantic.tab.c"
    break;

  case 60:
#line 461 "semantic.y"
                {
			// Literal moze da bude i INT i UINT
			if((yyvsp[-7].i) != get_type((yyvsp[-4].i))
				|| (yyvsp[-7].i) != get_type((yyvsp[-2].i))) 
				err("Types of literals aren't the same in loop.\n");
			
			// get_name($n) je vrednost literala (njegovo ime), ali string, mora atoi()
			if(atoi(get_name((yyvsp[-4].i))) >= atoi(get_name((yyvsp[-2].i))))
				err("Start of loop isn't smaller than the end.\n");
			
			// TODO: Deo za izvrsavanje je za sledecu kontrolnu tacku
		}
#line 1841 "semantic.tab.c"
    break;

  case 61:
#line 474 "semantic.y"
                {
			if((yyvsp[-9].i) != get_type((yyvsp[-6].i))
				|| (yyvsp[-9].i) != get_type((yyvsp[-4].i))
				|| (yyvsp[-9].i) != get_type((yyvsp[-2].i))) 
				err("Types of literals aren't the same in loop.\n");

			if(atoi(get_name((yyvsp[-6].i))) >= atoi(get_name((yyvsp[-4].i))))
				err("Start of loop isn't smaller than the end.\n");
		}
#line 1855 "semantic.tab.c"
    break;

  case 62:
#line 487 "semantic.y"
                {
			// Provera da li je ID po kojem se radi switch vec definisana promenljiva, ako jeste ok je
			// Takodje, pamtimo tip te promenljive za proveru u svakom case-u da li je literal dobrog tipa
			int switcher = 0;
			int flag = 0;
			for(int i = current_function + 1; i <= get_last_element(); i++){
				// Mozemo da preskocimo prvi jer je to ustvari funkcija
				if(strcmp(get_name(i), (yyvsp[0].s)) == 0){
					// Nadjen, postavljamo flag za gresku i switcher za tip
					flag = 1;
					switcher = i;
				}
			}
			if(flag == 0) err("Variable or parameter '%s' in switch statement not defined.\n", (yyvsp[0].s));
			switch_type = get_type(switcher);
			// Vracamo za sledeci switch
			for(int i = 0; i < 100; i++)
				switch_array[i] = -2147483648;
			// TODO: Deo za izvrsavanje je za sledecu tacku
		}
#line 1880 "semantic.tab.c"
    break;

  case 64:
#line 511 "semantic.y"
                            {
		// Posto bi $2 bio indeks u tabeli, moramo lookup_symbol da dobijemo vrednost
		// get_type($2) bi vratilo tip literala, jer je $2 indeks
		
		if(get_type((yyvsp[0].i)) != switch_type)
			err("Type of literal not the same as type of switcher.\n");

		for(int i = 0; i < 100; i++){
			if (switch_array[i] == atoi(get_name((yyvsp[0].i))))
				err("Literal already in use in switch statement.\n");
		}

	}
#line 1898 "semantic.tab.c"
    break;

  case 66:
#line 524 "semantic.y"
                                      {
		if(get_type((yyvsp[0].i)) != switch_type)
			err("Type of literal not the same as type of switcher.\n");

		for(int i = 0; i < 100; i++){
			if (switch_array[i] == atoi(get_name((yyvsp[0].i))))
				err("Literal already in use in switch statement.\n");
		}
	}
#line 1912 "semantic.tab.c"
    break;


#line 1916 "semantic.tab.c"

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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
  return yyresult;
}
#line 545 "semantic.y"


int yyerror(char *s) {
	fprintf(stderr, "\nline %d: ERROR: %s", yylineno, s);
	error_count++;
	return 0;
}

void warning(char *s) {
	fprintf(stderr, "\nline %d: WARNING: %s", yylineno, s);
	warning_count++;
}

int main() {
	int synerr;
	init_symtab();

	synerr = yyparse();

	clear_symtab();
	
	if(warning_count)
	printf("\n%d warning(s).\n", warning_count);

	if(error_count)
	printf("\n%d error(s).\n", error_count);

	if(synerr)
	return -1; //syntax error
	else
	return error_count; //semantic errors
}
