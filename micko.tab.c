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
#line 58 "micko.y"

	#include <stdio.h>
	#include <stdlib.h>
	#include "defs.h"
	#include "symtab.h"
	#include <string.h> // Za strcmp
	#include "codegen.c" // KT2, mora .c iz nekog razloga kod mene (greska undefined reference, ne ubaci .c kada ubacim .h??)

	#define ARRAY_LIMIT 100
	#define INT_MIN -2147483648

	int yyparse(void);
	int yylex(void);
	int yyerror(char *s);
	void warning(char *s);

	extern int yylineno;
	char char_buffer[CHAR_BUFFER_LENGTH];
	int error_count = 0;
	int warning_count = 0;
	int var_num = 0; // Trenutan broj lokalnih varijabli u funkciji, resetuje se za svaku funkciju
	int fun_idx = -1; // Indeks funkcije u kojoj se trenutno nalazimo
	int fcall_idx = -1; // Indeks funkcije koju pozivamo

	// Dodaci
	int vartype = 0;
	int return_flag = 0;
	int parameter_number = 0; // Brojac parametara pri definisanju funkcije, potreban za atr1 funkcije u tabeli simbola
	int argument_number = 0;
	int block_level = 0; // Brojac nivoa za ugnjezdene blokove koda (atr2 kod VAR-ova)
	int stack_of_loop_starts_indexes [ARRAY_LIMIT] = {0}; // Stek sa indeksima varijabli koje su inicijalizovane u definicijama iteracija, potreban za brisanje simbola iz tabele na kraju loop-a
	int stack_indexer = -1;
	int loop_transferring_type = 0; // (NO_TYPE)
	unsigned switch_type = 0; // unsigned je jer get_type vraca unsigned
	int switch_array[ARRAY_LIMIT]; // Niz literala trenutnog switch-a za proveru koriscenih (ne moze ovde sve da se inicijalizuje na INT_MIN, nego mora u switch-u)
	int switch_array_indexer = 0;

	// KT2
	int out_lin = 0;
	int lab_num = -1;
	FILE *output; // Vidi main() skroz dole, tu se inicijalizuje

	int argument_pusher_array[ARRAY_LIMIT]; // Niz indeksa registra koji imaju vrednosti num_exp-ova koji se prosledjuju u pozivu funkcije, da bi mogao da argumente push-ujem na stackframe u obrnutom redosledu
	int increment_todo_array[ARRAY_LIMIT] = {0}; // Niz indeksa ID-eva koji trebaju da se inkrementuju
	int increment_array_indexer = 0;

#line 117 "micko.tab.c"

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
#ifndef YY_YY_MICKO_TAB_H_INCLUDED
# define YY_YY_MICKO_TAB_H_INCLUDED
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
#line 105 "micko.y"

	int i;
	char *s;

#line 206 "micko.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MICKO_TAB_H_INCLUDED  */



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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   141

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  149

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
       0,   149,   149,   158,   159,   163,   179,   180,   185,   201,
     184,   228,   241,   227,   261,   262,   272,   273,   277,   297,
     296,   312,   313,   318,   317,   330,   349,   363,   364,   368,
     369,   370,   371,   372,   373,   374,   375,   387,   386,   404,
     443,   444,   473,   474,   495,   501,   506,   509,   515,   518,
     526,   525,   566,   572,   596,   606,   619,   624,   632,   638,
     631,   657,   671,   682,   692,   717,   729,   749,   748,   764,
     763,   790,   789,   816,   816,   828,   828,   842,   843,   847,
     848
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
  "ONLY_IF", "$accept", "program", "global_list", "global_var",
  "function_list", "function", "$@1", "$@2", "$@3", "$@4",
  "parameters_full", "parameters", "parameter", "body", "$@5",
  "variable_list", "variables_def_line", "$@6", "variables_only",
  "statement_list", "statement", "compound_statement", "$@7",
  "assignment_statement", "num_exp", "exp", "literal",
  "increment_optional", "function_call", "$@8", "argument_list",
  "arguments", "if_statement", "if_part", "@9", "$@10", "rel_exp",
  "return_statement", "increment_statement", "loop", "loop_first_part",
  "loop_second_part", "$@11", "$@12", "switch_statement", "$@13",
  "case_list", "$@14", "$@15", "finish_optional", "otherwise_optional", YY_NULLPTR
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

#define YYPACT_NINF (-79)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-51)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -79,     5,     8,   -79,     9,    23,   -79,    16,   -79,    21,
     -79,    32,   -79,   -79,    33,    38,   -79,    63,    63,    67,
     -79,    72,   -79,   -79,   -79,    75,    63,    76,    77,   -79,
      77,   -79,   -79,   -79,    85,   -79,   -79,   -79,    87,     0,
     -79,    14,    82,    70,    -6,   -79,   -79,    86,    66,   -79,
     -79,   -79,    83,   -79,    92,   -79,   -79,   -79,    48,   -79,
     -79,    93,   -79,    17,   -79,   -79,    44,   -79,    54,   -79,
     -79,   -79,    44,    84,    91,   -79,    99,    96,   -79,    11,
      88,   -79,   -79,    44,   -79,   -79,    29,   -79,    44,    68,
     -79,    44,    85,    97,   -79,   -79,    48,    47,   -79,   -79,
     -79,   -79,    89,    95,    90,    69,    94,    81,    -1,    44,
     101,   -79,    44,   -79,   -79,   102,   -79,    48,    89,    11,
      89,    98,    11,   104,   -79,    48,    35,   -79,   -79,   -79,
      48,   100,   103,    11,   105,   -79,    11,   -79,   -79,    11,
     106,   -79,    79,    11,   107,   -79,    79,   -79,   -79
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,     4,     2,     6,     8,
      11,     0,     7,     5,     0,     0,     8,    14,    14,     0,
       9,    15,    16,    12,    18,     0,     0,     0,     0,    17,
       0,    21,    10,    13,    19,    23,    27,    22,     0,     0,
      25,     0,     0,     0,    50,    37,    20,     0,     0,    28,
      29,    30,     0,    32,    56,    33,    34,    35,     0,    36,
      24,     0,    58,    48,    46,    47,     0,    63,     0,    40,
      42,    44,     0,     0,     0,    21,     0,     0,    31,     0,
       0,    65,    26,     0,    49,    43,     0,    62,     0,     0,
      64,    52,    27,     0,    71,    57,     0,     0,    59,    45,
      41,    39,    54,     0,    53,     0,     0,     0,     0,     0,
       0,    51,     0,    38,    66,     0,    67,     0,    61,     0,
      55,     0,     0,     0,    60,     0,    79,    68,    69,    73,
       0,     0,     0,     0,     0,    75,     0,    72,    70,     0,
       0,    80,    77,     0,     0,    74,    77,    78,    76
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -79,   -79,   -79,   -79,   -79,   110,   -79,   -79,   -79,   -79,
     109,   -79,   108,   111,   -79,    43,   -79,   -79,   -79,    27,
     -78,   -79,   -79,   -79,   -63,    25,   -58,   -79,   -41,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -26,
     -79
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,     7,     8,    14,    25,    15,    27,
      20,    21,    22,    32,    36,    34,    37,    38,    41,    39,
      49,    50,    75,    51,    68,    69,    70,    85,    52,    74,
     103,   104,    53,    54,    83,   110,    98,    55,    56,    57,
      58,    81,   122,   133,    59,   107,   126,   134,   140,   145,
     132
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      80,    95,    71,    86,    42,     3,    43,    44,    72,    89,
     116,     4,    45,    46,    73,    42,     9,    43,    44,    11,
      97,    47,   117,    45,    48,    71,     5,   -50,   102,    60,
      10,    71,    47,    61,     5,    48,    13,    84,   108,    16,
      99,   124,    71,    17,   127,    88,   118,    71,    18,   120,
      71,    63,    64,    65,    66,   138,    64,    65,   141,   123,
     130,   142,   131,    88,   109,   146,    19,   129,    71,    87,
      88,    71,   135,    42,    24,    43,    44,    63,    64,    65,
      66,    45,   113,   101,    88,    67,    28,    30,    35,    31,
      47,    26,    62,    48,    40,    77,    76,    79,    78,    90,
      82,    91,    93,    94,   106,    88,   111,   144,   114,   112,
      96,   115,   119,   100,   121,   128,   137,    12,    92,   105,
     148,     0,   147,   125,     0,     0,   136,    23,     0,     0,
       0,   139,   143,     0,    29,     0,     0,     0,     0,     0,
       0,    33
};

static const yytype_int16 yycheck[] =
{
      58,    79,    43,    66,     4,     0,     6,     7,    14,    72,
      11,     3,    12,    13,    20,     4,     7,     6,     7,     3,
      83,    21,    23,    12,    24,    66,    18,    10,    91,    15,
       7,    72,    21,    19,    18,    24,    15,    20,    96,     7,
      11,   119,    83,    10,   122,    16,   109,    88,    10,   112,
      91,     7,     8,     9,    10,   133,     8,     9,   136,   117,
      25,   139,    27,    16,    17,   143,     3,   125,   109,    15,
      16,   112,   130,     4,     7,     6,     7,     7,     8,     9,
      10,    12,    13,    15,    16,    15,    11,    11,     3,    12,
      21,    19,    10,    24,     7,    29,    10,     5,    15,    15,
       7,    10,     3,     7,     7,    16,    11,    28,    14,    19,
      22,    30,    11,    88,    12,    11,    13,     7,    75,    92,
     146,    -1,    15,    25,    -1,    -1,    26,    18,    -1,    -1,
      -1,    26,    26,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    30
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    33,    34,     0,     3,    18,    35,    36,    37,     7,
       7,     3,    37,    15,    38,    40,     7,    10,    10,     3,
      42,    43,    44,    42,     7,    39,    19,    41,    11,    44,
      11,    12,    45,    45,    47,     3,    46,    48,    49,    51,
       7,    50,     4,     6,     7,    12,    13,    21,    24,    52,
      53,    55,    60,    64,    65,    69,    70,    71,    72,    76,
      15,    19,    10,     7,     8,     9,    10,    15,    56,    57,
      58,    60,    14,    20,    61,    54,    10,    29,    15,     5,
      58,    73,     7,    66,    20,    59,    56,    15,    16,    56,
      15,    10,    47,     3,     7,    52,    22,    56,    68,    11,
      57,    15,    56,    62,    63,    51,     7,    77,    58,    17,
      67,    11,    19,    13,    14,    30,    11,    23,    56,    11,
      56,    12,    74,    58,    52,    25,    78,    52,    11,    58,
      25,    27,    82,    75,    79,    58,    26,    13,    52,    26,
      80,    52,    52,    26,    28,    81,    52,    15,    81
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    36,    36,    38,    39,
      37,    40,    41,    37,    42,    42,    43,    43,    44,    46,
      45,    47,    47,    49,    48,    50,    50,    51,    51,    52,
      52,    52,    52,    52,    52,    52,    52,    54,    53,    55,
      56,    56,    57,    57,    57,    57,    58,    58,    59,    59,
      61,    60,    62,    62,    63,    63,    64,    64,    66,    67,
      65,    68,    69,    69,    70,    71,    72,    74,    73,    75,
      73,    77,    76,    79,    78,    80,    78,    81,    81,    82,
      82
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     2,     3,     1,     2,     0,     0,
       8,     0,     0,     8,     0,     1,     1,     3,     2,     0,
       5,     0,     2,     0,     4,     1,     3,     0,     2,     1,
       1,     2,     1,     1,     1,     1,     1,     0,     5,     4,
       1,     3,     1,     2,     1,     3,     1,     1,     0,     1,
       0,     5,     0,     1,     1,     3,     1,     3,     0,     0,
       7,     3,     3,     2,     3,     2,     5,     0,     6,     0,
       8,     0,     9,     0,     6,     0,     7,     0,     2,     0,
       3
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
#line 150 "micko.y"
                {  
			// Javlja gresku ako main() uopste ne postoji u tabeli simbola
			if(lookup_symbol("main", FUN) == NO_INDEX)
				err("Undefined reference to 'main'.\n");
		 }
#line 1496 "micko.tab.c"
    break;

  case 5:
#line 164 "micko.y"
        {
		// Dodatna provera, ne mogu globalne promenljive i funkcije da imaju isto ime (ne moze int main; iznad int main(){}), ali moze da se trazi po celoj tabeli
		int idx = lookup_symbol((yyvsp[-1].s), GVAR|FUN); 
		if (idx != NO_INDEX) 
		{
				err("Global variable or function by the name '%s' already exists.", (yyvsp[-1].s));
		} else {
			insert_symbol((yyvsp[-1].s), GVAR, (yyvsp[-2].i), NO_ATR, -1); // block_level za globalne promenljive je -1
			// Generisanje koda za GVAR
			code("\n%s:\n\t\tWORD\t1", (yyvsp[-1].s));
		}
	}
#line 1513 "micko.tab.c"
    break;

  case 8:
#line 185 "micko.y"
                {
			// Trazimo da li postoji funkcija ili globalna promenljiva u tabeli sa istim imenom
			fun_idx = lookup_symbol((yyvsp[0].s), FUN|GVAR);
			if(fun_idx == NO_INDEX){
				// Ako ne postoji, dodaj je, uz inicijalizovanje broja parametara na 0 (tek treba da se puni) (atr2 vise nije nista za funkcije)
				fun_idx = insert_symbol((yyvsp[0].s), FUN, (yyvsp[-1].i), 0, NO_ATR);
				}
			else 
				err("Redefinition of function '%s'.\n", (yyvsp[0].s));

			// Postavljanje labele za funkciju, frame pointer-a i stack pointer-a
			code("\n%s:", (yyvsp[0].s));
        	code("\n\t\tPUSH\t%%14");
        	code("\n\t\tMOV \t%%15,%%14");
		}
#line 1533 "micko.tab.c"
    break;

  case 9:
#line 201 "micko.y"
                {
			// Kada analiziramo sve parametre, update-ujemo broj parametra za simbol funkcije (mada ovo i nema neku svrhu da se postavlja)
			set_atr1(fun_idx, parameter_number);
		}
#line 1542 "micko.tab.c"
    break;

  case 10:
#line 206 "micko.y"
                {
			// Kada se funkcija zavrsi moramo da izbrisemo sve njene lokalne varijable (ne diramo parametre, jer ih koristimo za pozive funkcija) 
			// clear_symbols brise od ovog indeksa pa na dole, pa ce nam ostati samo parametri
			int var_start_index = fun_idx + parameter_number + 1;
			clear_symbols(var_start_index);
			// Resetujemo var_num za sledece funkcije
			var_num = 0;
			// Non-void funkcije moraju imati povratnu vrednost, pa koristimo flag da proverimo da li smo ga iskoristili
			if(return_flag == 0)
				warn("Function '%s' needs to have the 'return' keyword.\n", (yyvsp[-6].s));
			// Resetujemo return flag za nove funkcije
			return_flag = 0;
			// Resetujemo broj parametra za nove funkcije
			parameter_number = 0;

			// Izlaz iz funkcije - exit labela, "brisanje" stackframe-a i ret
			code("\n@%s_exit:", (yyvsp[-6].s));
			code("\n\t\tMOV \t%%14,%%15"); // Podizemo %esp
			code("\n\t\tPOP \t%%14"); // Resetujemo %ebp
			code("\n\t\tRET"); // Povratnu adresu stavljamo u PC
		}
#line 1568 "micko.tab.c"
    break;

  case 11:
#line 228 "micko.y"
                {
			fun_idx = lookup_symbol((yyvsp[0].s), FUN);
			if(fun_idx == NO_INDEX){
				fun_idx = insert_symbol((yyvsp[0].s), FUN, (yyvsp[-1].i), 0, NO_ATR);
			}
			else 
				err("Redefinition of function '%s'.\n", (yyvsp[0].s));

			code("\n%s:", (yyvsp[0].s));
        	code("\n\t\tPUSH\t%%14");
        	code("\n\t\tMOV \t%%15,%%14");
		}
#line 1585 "micko.tab.c"
    break;

  case 12:
#line 241 "micko.y"
                {
			set_atr1(fun_idx, parameter_number);
		}
#line 1593 "micko.tab.c"
    break;

  case 13:
#line 245 "micko.y"
                {
			int var_start_index = fun_idx + parameter_number + 1;
			clear_symbols(var_start_index);
			var_num = 0;
			// Jedina razlika u odnosu na gornju alternativu je sto ovde ne proveravamo return_flag kao gore jer void funkcije nemaju povratnu vrednost
			return_flag = 0;
			parameter_number = 0;

			code("\n@%s_exit:", (yyvsp[-6].s));
			code("\n\t\tMOV \t%%14,%%15");
			code("\n\t\tPOP \t%%14");
			code("\n\t\tRET");
		}
#line 1611 "micko.tab.c"
    break;

  case 18:
#line 278 "micko.y"
                {
			// Pre ubacivanja proveravamo da li je trenutni parametar vec definisan za trenutnu funkciju preko tabele simbola
			// Ne radimo lookup_symbol() da ne bi uzeli parametre neke trece funkcije u razmatranje
			// Gledamo od indeksa trenutne funkcije do kraja tabele, jer varijabli nema
			// Ne ubrajamo simbol funkcije za slucaj int foo(unsigned foo){...}
			for(int j = fun_idx + 1; j <= get_last_element(); j++){
				if(strcmp(get_name(j), (yyvsp[0].s)) == 0){ // Provera za block_level nema smisla ovde
					err("Redifinition of parameter '%s'.\n", (yyvsp[0].s));
				}
			}
			// Za svaki parametar koji prodje moramo da povecamo broj parametara za update-ovanje atr1 funkcije
			parameter_number++;
			// Pri ubacivanju parametra, postavlja mu se indeks funkcije za koji je, kao i nivo, koji je uvek 0 (sluzi za kasniju proveru u operacijama)
			insert_symbol((yyvsp[0].s), PAR, (yyvsp[-1].i), parameter_number, 0);
		}
#line 1631 "micko.tab.c"
    break;

  case 19:
#line 297 "micko.y"
                {
			// Ako je bilo promenljivih definisano u funkciji, napravi mesta za njih na stackframe-u (pomeri %esp na dole) i napravi labelu za statement-e
			if(var_num)
				code("\n\t\tSUBS\t%%15,$%d,%%15", 4 * var_num);
				// Pomeramo %esp na dole da napravimo mesta (jedna promenljiva -> 4 bajta)
				// Lokalne promenljive ce ostati na stackframe-u dok se ne overwrite-uju, pa zato nema ADDS za ovaj SUBS, nema potrebe, jer ce odmah u exit labeli funkcije da se radi MOV %14, %15, sto pomera %esp na gore
			code("\n@%s_body:", get_name(fun_idx)); 
			// Od ove labele krece body koji ce se generisati iz ostalih pojmova koji prave statement_list-u
		}
#line 1645 "micko.tab.c"
    break;

  case 23:
#line 318 "micko.y"
                {
			// Mora u ovoj akciji da se izmeni vartype, da bi mogao da se koristi u variables_only
			vartype = (yyvsp[0].i);
		}
#line 1654 "micko.tab.c"
    break;

  case 24:
#line 323 "micko.y"
                {
			// Kada smo iskoristili vartype, moramo da ga resetujemo (cim se napravi variables_def_line) (ovo je mozda nepotrebno)
			vartype = 0;
		}
#line 1663 "micko.tab.c"
    break;

  case 25:
#line 331 "micko.y"
                {
			// Pri deklarisanju varijable trebamo da proverimo da li vec u toj trenutnoj funkciji postoje varijable ili parametri sa tim imenom
			// To znaci da varijabla moze imati isto ime kao neka prethodna funkcija ili njeni parametri
			// Ne mozemo da gledamo po lookup_symbol(VAR|PAR) jer to gleda celu tabelu (od nazad pa do 13. registra (FUNREG)) 
			// To pravi problem zbog parametara, jer se oni ovde ne brisu iz tabele na kraju funkcije
			// Idemo od indeksa funkcije u kojoj je deklarisana varijabla (fun_idx) do kraja tabele
			// Ne gledamo sam simbol funkcije jer lokalna varijabla moze da ima isto ime kao njena funkcija
			// Poredimo imena sa svakim simbolom (varijable i parametri), i ako se poklopi javljamo gresku, ako ne nadje isto ime dodajemo
			// Za tip varijable koristimo vartype koji je postavljen u variables_def_line
			// Takodje dodajemo proveru za nivo bloka, da na trenutnom nivou ne moze da se definise promenljiva koja je tu vec definisana (bitno je da je definisana, a ne koja tu samo postoji, jer ako smo pre imali int a;, i u novom bloku opet int a;, to moze jer ce se vrednost a overwrite-ovati samo u tom scope-u, vidi compound_statement)
			for(int i = fun_idx + 1; i <= get_last_element(); i++){
				if(strcmp(get_name(i), (yyvsp[0].s)) == 0 && get_atr2(i) == block_level){ // Mora == kada definisemo varijablu
					err("Variable or parameter by the name '%s' already exists on this level.\n", (yyvsp[0].s));
				}
			}
			var_num++;
			insert_symbol((yyvsp[0].s), VAR, vartype, var_num, block_level);
		}
#line 1686 "micko.tab.c"
    break;

  case 26:
#line 350 "micko.y"
                {
			// Ista provera i za ovu alternativu
			for(int i = fun_idx + 1; i <= get_last_element(); i++){
				if(strcmp(get_name(i), (yyvsp[0].s)) == 0 && get_atr2(i) == block_level){
					err("Variable or parameter by the name '%s' already exists on this level.\n", (yyvsp[0].s));
				}
			}
			var_num++;
			insert_symbol((yyvsp[0].s), VAR, vartype, var_num, block_level);
		}
#line 1701 "micko.tab.c"
    break;

  case 37:
#line 387 "micko.y"
                {
			// Na pocetku novog bloka se povecava brojac (prvi novi blok ce biti nivoa 1)
			block_level++;
		}
#line 1710 "micko.tab.c"
    break;

  case 38:
#line 392 "micko.y"
                {
			// Brisemo sve novodefinisane varijable (da bi vratili vrednost starima sa istim imenom)
			// Nadjemo prvi simbol sa trenutnim block_level-om i brisemo sve ispod njega (ukljucujuci i literale)
			for(int j = fun_idx + 1; j <= get_last_element(); j++)
				if(get_atr2(j) == block_level)
					clear_symbols(j);
			// Vracamo se u nivo pre
			block_level--;
		}
#line 1724 "micko.tab.c"
    break;

  case 39:
#line 405 "micko.y"
                {
		int idx = NO_INDEX;
		// Prvo gleda VAR|PAR trenutne funkcije, pa tek onda GVAR, jer VAR ima prednost
		// Razlog zasto gleda VAR|PAR trenutne funkcije je da ne bi slucajno uzeo parametar neke trece funkcije
		for(int j = fun_idx + 1; j <= get_last_element(); j++){
				if(strcmp(get_name(j), (yyvsp[-3].s)) == 0) // U ovoj proveri moze, a i ne mora, da se stavi && get_atr2(j) <= block_level, zato sto svi simboli u tabeli sigurno nece imati block_level veci od trenutnog, zato sto se svaki prethodni novi blok izbrisao, vidi compound_statement (ako smo u nivou 0, nece postojati nista iz nivoa 1)
					idx = j; // Uzece tacno onaj simbol koji nam treba jer je gornji if prosao
			}
		if(idx == NO_INDEX)
			idx = lookup_symbol((yyvsp[-3].s), GVAR);
		if(idx == NO_INDEX)
			err("Local or global variable or parameter by the name '%s' in assignment doesn't exist.\n", (yyvsp[-3].s));
		else if(get_type(idx) != get_type((yyvsp[-1].i)))
			err("Incompatible types in assignment.\n");
		
		// Generisanje koda za dodelu - vrednost num_exp-a ide u ID (treba da ostane ovde)
		gen_mov((yyvsp[-1].i), idx);

		// Inkrementujemo te ID-eve koji su sami inkrementovani
		// TODO: Pretpostavljamo da je svaki ID maksimalno jednom inkrementovan u assign statement-u, jer su oni tako na pdf-u prikazali asembler, zapravo po gcc-u treba da se uveca za 1 ako se ID inkrementovao dvaput u izrazu, ili da se uveza za 3 ako se pojavio triput, etc
		// Takodje, a = a++ nece da inkrementuje po gcc-u ali ovde hoce
		for(int i = 0; i < ARRAY_LIMIT; i++){
			if(increment_todo_array[i] != 0){
				code("\n\t\tADDS\t"); // TODO: ADDU
				gen_sym_name(increment_todo_array[i]);
				code(",$1,");
				gen_sym_name(increment_todo_array[i]);
			}
		}

		// Reset
		increment_array_indexer = 0;
		for(int i = 0; i < ARRAY_LIMIT; i++)
			increment_todo_array[i] = 0;
		}
#line 1764 "micko.tab.c"
    break;

  case 41:
#line 445 "micko.y"
                {
			// Semanticka vrednost num_exp-a je indeks registra u kojem se nalazi njegova vrednost
			// Tip num_exp-a je tip vrednosti koju taj izraz daje, a taj tip je nasledjen od exp-a, i stavljen je kao tip tog registra koji ima njegovu vrednost
			// Zna se i tip poziva funkcije (povratne vrednosti) iz toga sto je semanticka vrednost function_call-a indeks funkcije, 
			// pa ce tu semanticku vrednost imati i exp, pa ce get_type($3) uzeti tacan tip iz simbola kind-a FUN
			if(get_type((yyvsp[-2].i)) != get_type((yyvsp[0].i)))
				err("Invalid operands: arithmetic operation (incompatible types).\n");
			int type = get_type((yyvsp[-2].i));
			// num_exp ce biti npr ADDS %1, %3, %4
			// biramo aritmeticku operaciju na osnovu parsiranog AROP-a i tipa num_exp-a - $2 je vrsta operacije (ADD ili SUB), a ovaj proizvod je ili 0 ili 4 (AROP_NUMBER je makro za 4) i bira signed ili unsigned verziju operacije (ima 4 zbog MUL i DIV)
			code("\n\t\t%s\t", ar_instructions[(yyvsp[-1].i) + (type - 1) * AROP_NUMBER]);
			// Operandi
			gen_sym_name((yyvsp[-2].i)); // Ovo je valjda uvek registar
			code(",");
			gen_sym_name((yyvsp[0].i)); // Ovo ne mora da bude registar
			code(",");
			// Oslobadjamo odmah zauzete registre u obrnutom redosledu
			free_if_reg((yyvsp[0].i));
			free_if_reg((yyvsp[-2].i));
			(yyval.i) = take_reg(); // Semanticka vrednost je indeks registra sa rezultatom
			gen_sym_name((yyval.i)); // Generise asm kod za taj registar kao rezultat operacije
			set_type((yyval.i), type); // Postavljamo tip registra koji sadrzi vrednost num_exp-a na tip samog num_exp-a
		}
#line 1792 "micko.tab.c"
    break;

  case 43:
#line 475 "micko.y"
                {
			int idx = NO_INDEX;
			// Prvo gleda VAR|PAR trenutne funkcije, pa tek onda GVAR, jer VAR ima prednost
			// Razlog zasto gleda VAR|PAR trenutne funkcije je da ne bi slucajno uzeo parametar neke trece funkcije
			for(int j = fun_idx + 1; j <= get_last_element(); j++){
				if(strcmp(get_name(j), (yyvsp[-1].s)) == 0) // Moze i ne mora && get_atr2(j) <= block_level
					idx = j; // Uzece tacno onaj simbol koji nam treba jer je gornji if prosao
			}
			if(idx == NO_INDEX)
				idx = lookup_symbol((yyvsp[-1].s), GVAR);
			if(idx == NO_INDEX)
				err("'%s' undeclared.\n", (yyvsp[-1].s));
			(yyval.i) = idx; // Semanticka vrednost exp-a sa ID-em je indeks ID-a u tabeli simbola

			// Provera da li je bilo inkrementa nad tim ID-em
			if((yyvsp[0].i) == 1){
				increment_todo_array[increment_array_indexer] = idx;
				increment_array_indexer++;
			}
		}
#line 1817 "micko.tab.c"
    break;

  case 44:
#line 496 "micko.y"
                {
			// Kada pozivamo funkciju zelimo da njenu povratnu vrednost prebacimo u registar opste namene
			(yyval.i) = take_reg(); // Zauzima se registar opste namene
			gen_mov(FUN_REG, (yyval.i)); // Prebaca se iz %13 u taj registar
		}
#line 1827 "micko.tab.c"
    break;

  case 45:
#line 502 "micko.y"
                { (yyval.i) = (yyvsp[-1].i); /* exp nasledjuje semanticku vrednost num_exp-a u zagradi */ }
#line 1833 "micko.tab.c"
    break;

  case 46:
#line 507 "micko.y"
                { (yyval.i) = insert_literal((yyvsp[0].s), INT); }
#line 1839 "micko.tab.c"
    break;

  case 47:
#line 510 "micko.y"
                { (yyval.i) = insert_literal((yyvsp[0].s), UINT); }
#line 1845 "micko.tab.c"
    break;

  case 48:
#line 515 "micko.y"
                {
			(yyval.i) = 0; // Nije bilo inkrementa
		}
#line 1853 "micko.tab.c"
    break;

  case 49:
#line 519 "micko.y"
                {
			(yyval.i) = 1; // Bilo je inkrementa
		}
#line 1861 "micko.tab.c"
    break;

  case 50:
#line 526 "micko.y"
                {
			// Ovo je indeks funkcije koju pozivamo u tabeli simbola, koristi se kod argumenata
			fcall_idx = lookup_symbol((yyvsp[0].s), FUN); 
			if(fcall_idx == NO_INDEX)
				err("'%s' is not a function.\n", (yyvsp[0].s));

			// Reset niza na pocetku poziva
			for(int i = 0; i < ARRAY_LIMIT; i++)
				argument_pusher_array[i] = INT_MIN;
		}
#line 1876 "micko.tab.c"
    break;

  case 51:
#line 537 "micko.y"
                {
			// Ovde je pre pisalo samo $$ = lookup_symbol($1, FUN);
			// U micku su koristili semanticku vrednost argument_list-e za broj argumenata, ja imam globalnu varijablu
			// Takodje su ovde radili proveru broja argumenata, ja to radim u argument_list

			// Generisanje koda za argumente - push-ujemo ih na stackframe u obrnutom redosledu, mora pre CALL-a
			for(int i = argument_number - 1; i >= 0; i--){
				free_if_reg(argument_pusher_array[i]);
				code("\n\t\t\tPUSH\t");
				gen_sym_name(argument_pusher_array[i]); // Generisace asm kod za registar u kojem je vrednost num_exp-a
			}

			// Pravi se poziv uz ime funkcije, koje ce biti labela
			code("\n\t\t\tCALL\t%s", get_name(fcall_idx));
			// Nakon poziva, kada funkcija zavrsi sa radom, moramo da izbrisemo mesta za argumente koji su joj prosledjeni (ovaj if nije ni potreban)
			if(argument_number > 0)
				code("\n\t\t\tADDS\t%%15,$%d,%%15", argument_number * 4);
			set_type(FUN_REG, get_type(fcall_idx)); // Postavlja tip za %13
			(yyval.i) = FUN_REG; // Semanticka vrednost poziva je uvek 13

			// Resetujemo broj argumenata za sledeci poziv
			argument_number = 0;
		}
#line 1904 "micko.tab.c"
    break;

  case 52:
#line 566 "micko.y"
                {
			// Ako nismo prosledili argumente, moramo da proverimo da li funkcija zapravo zahteva parametre
			if(get_atr1(fcall_idx) > 0)
				err("Function '%s' requires arguments!\n", get_name(fcall_idx));
			// argument_number ostaje 0
		}
#line 1915 "micko.tab.c"
    break;

  case 53:
#line 573 "micko.y"
                {
			// Moramo ovde da proverimo broj argumenata, jer argumenti mogu da budu svakakvi, pa nema smisla to proveravati u akcijama dole
			// U tim akcijama dole se znaci samo postavlja argument_number, ali se ovde proverava
			if(get_atr1(fcall_idx) > argument_number)
				err("Too few arguments passed to function '%s'.\n", get_name(fcall_idx));
			else if(get_atr1(fcall_idx) < argument_number)
				err("Too many arguments passed to function '%s'.\n", get_name(fcall_idx));
		}
#line 1928 "micko.tab.c"
    break;

  case 54:
#line 597 "micko.y"
                {
			// Cim nadje jedan parametar radice ovu proveru, a ako nadje vise nastavice u sledecoj alternativi
			argument_number = 1;
			// get_type() za num_exp radi, a radice i u GK zbog indeksa registra sa tipom
			if(get_type(fcall_idx + argument_number) != get_type((yyvsp[0].i))) 
        		err("Forwarded argument '%s' of wrong type.\n", get_name((yyvsp[0].i)));
			// Punimo niz indeksa registra num_exp-ova koji su za PUSH na stackframe u obrnutom redosledu (mora -1 jer pocinje od 1)
			argument_pusher_array[argument_number - 1] = (yyvsp[0].i);
		}
#line 1942 "micko.tab.c"
    break;

  case 55:
#line 607 "micko.y"
                {
			// Za prvi argument u listi je vec uradio proveru gore, sad radi za ostale, redom
			argument_number++; // Za svaki argument povecavamo
			if(get_type(fcall_idx + argument_number) != get_type((yyvsp[0].i))){
        		err("Forwarded argument '%s' of wrong type.\n", get_name((yyvsp[0].i)));
			}
			argument_pusher_array[argument_number - 1] = (yyvsp[0].i);
		}
#line 1955 "micko.tab.c"
    break;

  case 56:
#line 620 "micko.y"
                {
			// Na kraju parsiranja celog if_statement-a mora da se napravi labela za izlazak iz if-a, zbog skoka iz druge labele na tu labelu - moramo da stavimo broj labele, a to cemo dobiti iz semanticke vrednosti if_part-a, sto je ustvari broj labele za taj nivo if-a (u ugnjezdenim if-ovima)
			code("\n@exit%d:", (yyvsp[0].i));
		}
#line 1964 "micko.tab.c"
    break;

  case 57:
#line 625 "micko.y"
                {
			code("\n@exit%d:", (yyvsp[-2].i));
		}
#line 1972 "micko.tab.c"
    break;

  case 58:
#line 632 "micko.y"
                {
			// Prva labela je za uslov u zagradama, pravimo labelu uz lab_num
			(yyval.i) = ++lab_num; // Bio je na -1 da bi "stablo ugnjezdenih if-ova" pocelo od nulte labele
        	code("\n@if%d:", lab_num);
		}
#line 1982 "micko.tab.c"
    break;

  case 59:
#line 638 "micko.y"
                {
			// $<i>3 je trenutni lab_num, za taj nivo if-a, odnosno semanticka vrednost prve akcije
			// Koristimo ga ovako a ne preko lab_num jer ce se lab_num menjati kako pravimo if-ove u if-u
			// Znaci ovako ce sigurno ta semanticka vrednost da ostane na istom nivou ($<i>$ je lokalno samo za trenutni pojam, a lab_num je globalna vrednost)
			// lab_num se nigde ne resetuje, tako da ako imamo jednom neke if u if-u u if-u itd, ako izadjemo iz svega toga i ponovo imamo neki if, on nece biti prvi, nego npr sesti (kao sto i treba, ako se resetuje lab_num, onda ce se simulator vracati na pogresan if gore cak, a treba da ide dole)
			// opp_jumps je opposite jumps, i mi koristimo tu enumeraciju jer sa CMP-om hocemo da idemo na false granu if-a, znaci gledamo suprotan uslov
			code("\n\t\t%s\t@false%d", opp_jumps[(yyvsp[0].i)], (yyvsp[-1].i)); // Uslovni skok na false labelu
			// Zna se koji ce se tip skoka koristiti na osnovu rel_exp-a i njegove semanticke vrednosti, a semanticka vrednost rel_exp-a je indeks odgovarajuceg uskovnog skoka u enumeraciji, vidi dole
			code("\n@true%d:", (yyvsp[-1].i));
		}
#line 1997 "micko.tab.c"
    break;

  case 60:
#line 649 "micko.y"
                {
			code("\n\t\tJMP \t@exit%d", (yyvsp[-4].i)); // Bezuslovni skok na kraj na kraju true grane if-a
			code("\n@false%d:", (yyvsp[-4].i)); // Ova labela ce za ONLY_IF alternativu postojati, ali ce biti prazna, pa je napravljena za drugu alternativu, da bi ona mogla samo tu da nastavi sa onim njenim statement-om
			(yyval.i) = (yyvsp[-4].i); // Da bi napravili exit labelu treba nam broj labele za trenutni nivo if-a, pa koristimo semanticku vrednost if_part-a za to (a to se koristi u alternativama if_statement-a)
		}
#line 2007 "micko.tab.c"
    break;

  case 61:
#line 658 "micko.y"
                {
			if(get_type((yyvsp[-2].i)) != get_type((yyvsp[0].i)))
				err("Invalid operands in relational operator.\n");
       		// $2 daje jednu od onih 6 standardnih relop-a
			// Moramo da gledamo tip operanda da bi znali koji tacno skok da uradimo, da li S ili U
			// Pa ce ova zagrada desno biti ili 0 (za S) ili 6 (za U) (jer get_type vraca ili 1 ili 2)
			// Pa ce semanticka vrednost rel_exp-a biti indeks odgovarajuceg uslovnog skoka u enumeraciji
			(yyval.i) = (yyvsp[-1].i) + ((get_type((yyvsp[-2].i)) - 1) * RELOP_NUMBER);
        	gen_cmp((yyvsp[-2].i), (yyvsp[0].i)); // Na primer CMPS %3, %4 (gen_cmp gleda da li su int ili uint pa ce biti ili CMPS ili CMPU)
		}
#line 2022 "micko.tab.c"
    break;

  case 62:
#line 672 "micko.y"
                {
			// Javlja se return, postavljamo flag (cak iako tip povratne vrednosti nije dobar)
			return_flag = 1;
			if(get_type(fun_idx) != get_type((yyvsp[-1].i)))
				err("Incompatible types in return.\n");
			if(get_type(fun_idx) == VOID)
				err("Function of type VOID can't return an expression.\n");
			gen_mov((yyvsp[-1].i), FUN_REG); // Prebaca u %13 za povratnu vrednost
			code("\n\t\tJMP \t@%s_exit", get_name(fun_idx)); // JMP na exit labelu za funkciju za "brisanje" stackframe-a
		}
#line 2037 "micko.tab.c"
    break;

  case 63:
#line 683 "micko.y"
                {
			// Posto void funkcija ne zahteva return, ne moramo postavljati flag
			// Posto je ovo samo za void funkcije, za one koje nisu void moramo da kazemo da mora da vrati neki num_exp
			if(get_type(fun_idx) != VOID)
				warn("Non-void function has to return a value.\n");
		}
#line 2048 "micko.tab.c"
    break;

  case 64:
#line 693 "micko.y"
                {
			int idx = NO_INDEX;
			// Prvo gleda VAR|PAR trenutne funkcije, pa tek onda GVAR, jer VAR ima prednost
			// Razlog zasto gleda VAR|PAR trenutne funkcije je da ne bi slucajno uzeo parametar neke trece funkcije
			for(int j = fun_idx + 1; j <= get_last_element(); j++){
				if(strcmp(get_name(j), (yyvsp[-2].s)) == 0) // Moze i ne mora && get_atr2(j) <= block_level
					idx = j; // Uzece tacno onaj simbol koji nam treba jer je gornji if prosao
			}
			if(idx == NO_INDEX)
				idx = lookup_symbol((yyvsp[-2].s), GVAR);
			if(idx == NO_INDEX)
				err("'%s' undeclared.\n", (yyvsp[-2].s));
			// increment_statement-u se ne postavlja semanticka vrednost (za sad)

			code("\n\t\tADDS\t"); // TODO: Proveri da li radi za GVAR-ove, i valjda treba i da se pravi destinkcija da li je S ili U
			gen_sym_name(idx);
			code(",$1,");
			gen_sym_name(idx);
		}
#line 2072 "micko.tab.c"
    break;

  case 65:
#line 718 "micko.y"
                {
			// Kraj loop-a, bilo da je ugnjezden ili ne
			loop_transferring_type = 0; // Reset
			// Brisanje simbola za loop iz tabele preko steka
			clear_symbols(stack_of_loop_starts_indexes[stack_indexer]);
			stack_indexer--;
			// Zbog ovoga nemamo akciju posle statement-a
		}
#line 2085 "micko.tab.c"
    break;

  case 66:
#line 730 "micko.y"
                {
			loop_transferring_type = (yyvsp[-2].i);
			// TODO: Obrati paznju za GK da se ovde zapravo desava dodela

			// TYPE ID mora da napravi lokalnu promenljivu, i to samo u scope-u iteracije, i ne moze da se koristi ako vec postoji na tom scope-u (nivou) definisana (definisanje -> == block_level)
			// Prekopirano iz variables_only, prva alternativa, samo zamenjeno $n
			for(int i = fun_idx + 1; i <= get_last_element(); i++){
				if(strcmp(get_name(i), (yyvsp[-1].s)) == 0 && get_atr2(i) == block_level){ // Mora == (GVAR ne ubrajamo u proveru za gresku jer moze da ga redefinise)
					err("Variable or parameter by the name '%s' already exists on this level.\n", (yyvsp[-1].s));
				}
			}
			var_num++;
			stack_indexer++; // Za prvi loop sa -1 na 0
			stack_of_loop_starts_indexes[stack_indexer] = insert_symbol((yyvsp[-1].s), VAR, (yyvsp[-2].i), var_num, block_level); // insert_symbol vraca indeks, punimo stek
		}
#line 2105 "micko.tab.c"
    break;

  case 67:
#line 749 "micko.y"
                {
			// Razlog zasto razdavajamo ovde je da bi se iz tabele simbola (u sledecoj akciji) brisali i literali iz inicijalizacije iteracije
			if(loop_transferring_type != get_type((yyvsp[-3].i))
				|| loop_transferring_type != get_type((yyvsp[-1].i))) 
				err("Types of literals in the iteration definition aren't the same.\n");
			
			int lit1 = atoi(get_name((yyvsp[-3].i)));
			int lit2 = atoi(get_name((yyvsp[-1].i)));

			// get_name($n) je vrednost literala (njegovo ime), ali string, mora atoi()
			if(lit1 >= lit2)
				err("Start of the loop isn't smaller than the end.\n");
		}
#line 2123 "micko.tab.c"
    break;

  case 69:
#line 764 "micko.y"
                {
			if(loop_transferring_type != get_type((yyvsp[-5].i))
				|| loop_transferring_type != get_type((yyvsp[-3].i))
				|| loop_transferring_type != get_type((yyvsp[-1].i))) 
				err("Types of literals in the iteration definition aren't the same.\n");

			int lit1 = atoi(get_name((yyvsp[-5].i)));
			int lit2 = atoi(get_name((yyvsp[-3].i)));
			int step = atoi(get_name((yyvsp[-1].i)));

			if(lit1 >= lit2)
				err("Start of the loop isn't smaller than the end.\n");

			// Dodatni uslovi
			if(step <= 0)
				err("Step needs to be a positive integer.\n"); 
			else if(step > (lit2 - lit1))
				err("Step needs to be lesser or equal to the difference in literals.\n");
		}
#line 2147 "micko.tab.c"
    break;

  case 71:
#line 790 "micko.y"
                {
			// Postavljanje svakog elementa na INT_MIN da case 0 ne baci gresku
			// Ovo ce i resetovati niz i indekser sa svaki switch, ne mora da se radi u poslednjoj akciji
			for(int i = 0; i < ARRAY_LIMIT; i++)
				switch_array[i] = INT_MIN;
			switch_array_indexer = 0;

			// Provera da li je ID po kojem se radi switch vec definisana promenljiva, ako jeste ok je
			// Takodje, pamtimo tip te promenljive za proveru u svakom case-u, da li je literal dobrog tipa
			int idx = NO_INDEX;
			// Prvo gleda VAR|PAR trenutne funkcije, pa tek onda GVAR, jer VAR ima prednost
			// Razlog zasto gleda VAR|PAR trenutne funkcije je da ne bi slucajno uzeo parametar neke trece funkcije
			for(int j = fun_idx + 1; j <= get_last_element(); j++){
				if(strcmp(get_name(j), (yyvsp[0].s)) == 0) // Moze i ne mora && get_atr2(j) <= block_level
					idx = j; // Uzece tacno onaj simbol koji nam treba jer je gornji if prosao
					switch_type = get_type(j);
			}
			if(idx == NO_INDEX)
				idx = lookup_symbol((yyvsp[0].s), GVAR);
			if(idx == NO_INDEX)
				err("Variable or parameter '%s' in switch statement not defined.\n", (yyvsp[0].s));
		}
#line 2174 "micko.tab.c"
    break;

  case 73:
#line 816 "micko.y"
                            {
		if(get_type((yyvsp[0].i)) != switch_type)
			err("Type of literal not the same as type of switcher.\n");

		for(int i = 0; i < ARRAY_LIMIT; i++){
			if (switch_array[i] == atoi(get_name((yyvsp[0].i))))
				err("Literal already in use in switch statement.\n");
		}
		// Provere su ok, literal moze da se ubaci
		switch_array[switch_array_indexer] = atoi(get_name((yyvsp[0].i)));
		switch_array_indexer++;
	}
#line 2191 "micko.tab.c"
    break;

  case 75:
#line 828 "micko.y"
                                      {
		if(get_type((yyvsp[0].i)) != switch_type)
			err("Type of literal not the same as type of switcher.\n");

		for(int i = 0; i < ARRAY_LIMIT; i++){
			if (switch_array[i] == atoi(get_name((yyvsp[0].i))))
				err("Literal already in use in switch statement.\n");
		}
		switch_array[switch_array_indexer] = atoi(get_name((yyvsp[0].i)));
		switch_array_indexer++;
	}
#line 2207 "micko.tab.c"
    break;


#line 2211 "micko.tab.c"

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
#line 851 "micko.y"


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
	output = fopen("output.asm", "w+");

	synerr = yyparse();

	clear_symtab();
	fclose(output);
	
	if(warning_count)
		printf("\n%d warning(s).\n", warning_count);

	if(error_count) {
		remove("output.asm");
		printf("\n%d error(s).\n", error_count);
	}

	if(synerr)
    	return -1;  //syntax error
  	else if(error_count)
		return error_count & 127; //semantic errors
	else if(warning_count)
		return (warning_count & 127) + 127; //warnings
	else
		return 0; //OK
}
