/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
   2009, 2010 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1

/* Substitute the variable and function names.  */
#define yyparse         _mesa_glsl_parse
#define yylex           _mesa_glsl_lex
#define yyerror         _mesa_glsl_error
#define yylval          _mesa_glsl_lval
#define yychar          _mesa_glsl_char
#define yydebug         _mesa_glsl_debug
#define yynerrs         _mesa_glsl_nerrs
#define yylloc          _mesa_glsl_lloc

/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "glsl_parser.ypp"

/*
 * Copyright © 2008, 2009 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
    
#include "ast.h"
#include "glsl_parser_extras.h"
#include "glsl_types.h"

#define YYLEX_PARAM state->scanner



/* Line 189 of yacc.c  */
#line 117 "glsl_parser.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ATTRIBUTE = 258,
     CONST_TOK = 259,
     BOOL_TOK = 260,
     FLOAT_TOK = 261,
     INT_TOK = 262,
     UINT_TOK = 263,
     BREAK = 264,
     CONTINUE = 265,
     DO = 266,
     ELSE = 267,
     FOR = 268,
     IF = 269,
     DISCARD = 270,
     RETURN = 271,
     SWITCH = 272,
     CASE = 273,
     DEFAULT = 274,
     BVEC2 = 275,
     BVEC3 = 276,
     BVEC4 = 277,
     IVEC2 = 278,
     IVEC3 = 279,
     IVEC4 = 280,
     UVEC2 = 281,
     UVEC3 = 282,
     UVEC4 = 283,
     VEC2 = 284,
     VEC3 = 285,
     VEC4 = 286,
     CENTROID = 287,
     IN_TOK = 288,
     OUT_TOK = 289,
     INOUT_TOK = 290,
     UNIFORM = 291,
     VARYING = 292,
     NOPERSPECTIVE = 293,
     FLAT = 294,
     SMOOTH = 295,
     MAT2X2 = 296,
     MAT2X3 = 297,
     MAT2X4 = 298,
     MAT3X2 = 299,
     MAT3X3 = 300,
     MAT3X4 = 301,
     MAT4X2 = 302,
     MAT4X3 = 303,
     MAT4X4 = 304,
     SAMPLER1D = 305,
     SAMPLER2D = 306,
     SAMPLER3D = 307,
     SAMPLERCUBE = 308,
     SAMPLER1DSHADOW = 309,
     SAMPLER2DSHADOW = 310,
     SAMPLERCUBESHADOW = 311,
     SAMPLER1DARRAY = 312,
     SAMPLER2DARRAY = 313,
     SAMPLER1DARRAYSHADOW = 314,
     SAMPLER2DARRAYSHADOW = 315,
     ISAMPLER1D = 316,
     ISAMPLER2D = 317,
     ISAMPLER3D = 318,
     ISAMPLERCUBE = 319,
     ISAMPLER1DARRAY = 320,
     ISAMPLER2DARRAY = 321,
     USAMPLER1D = 322,
     USAMPLER2D = 323,
     USAMPLER3D = 324,
     USAMPLERCUBE = 325,
     USAMPLER1DARRAY = 326,
     USAMPLER2DARRAY = 327,
     STRUCT = 328,
     VOID_TOK = 329,
     WHILE = 330,
     IDENTIFIER = 331,
     FLOATCONSTANT = 332,
     INTCONSTANT = 333,
     UINTCONSTANT = 334,
     BOOLCONSTANT = 335,
     FIELD_SELECTION = 336,
     LEFT_OP = 337,
     RIGHT_OP = 338,
     INC_OP = 339,
     DEC_OP = 340,
     LE_OP = 341,
     GE_OP = 342,
     EQ_OP = 343,
     NE_OP = 344,
     AND_OP = 345,
     OR_OP = 346,
     XOR_OP = 347,
     MUL_ASSIGN = 348,
     DIV_ASSIGN = 349,
     ADD_ASSIGN = 350,
     MOD_ASSIGN = 351,
     LEFT_ASSIGN = 352,
     RIGHT_ASSIGN = 353,
     AND_ASSIGN = 354,
     XOR_ASSIGN = 355,
     OR_ASSIGN = 356,
     SUB_ASSIGN = 357,
     INVARIANT = 358,
     LOWP = 359,
     MEDIUMP = 360,
     HIGHP = 361,
     SUPERP = 362,
     PRECISION = 363,
     VERSION = 364,
     EXTENSION = 365,
     LINE = 366,
     COLON = 367,
     EOL = 368,
     INTERFACE = 369,
     OUTPUT = 370,
     PRAGMA_DEBUG_ON = 371,
     PRAGMA_DEBUG_OFF = 372,
     PRAGMA_OPTIMIZE_ON = 373,
     PRAGMA_OPTIMIZE_OFF = 374,
     PRAGMA_INVARIANT_ALL = 375,
     LAYOUT_TOK = 376,
     ASM = 377,
     CLASS = 378,
     UNION = 379,
     ENUM = 380,
     TYPEDEF = 381,
     TEMPLATE = 382,
     THIS = 383,
     PACKED_TOK = 384,
     GOTO = 385,
     INLINE_TOK = 386,
     NOINLINE = 387,
     VOLATILE = 388,
     PUBLIC_TOK = 389,
     STATIC = 390,
     EXTERN = 391,
     EXTERNAL = 392,
     LONG_TOK = 393,
     SHORT_TOK = 394,
     DOUBLE_TOK = 395,
     HALF = 396,
     FIXED_TOK = 397,
     UNSIGNED = 398,
     INPUT_TOK = 399,
     OUPTUT = 400,
     HVEC2 = 401,
     HVEC3 = 402,
     HVEC4 = 403,
     DVEC2 = 404,
     DVEC3 = 405,
     DVEC4 = 406,
     FVEC2 = 407,
     FVEC3 = 408,
     FVEC4 = 409,
     SAMPLER2DRECT = 410,
     SAMPLER3DRECT = 411,
     SAMPLER2DRECTSHADOW = 412,
     SIZEOF = 413,
     CAST = 414,
     NAMESPACE = 415,
     USING = 416,
     ERROR_TOK = 417,
     COMMON = 418,
     PARTITION = 419,
     ACTIVE = 420,
     SAMPLERBUFFER = 421,
     FILTER = 422,
     IMAGE1D = 423,
     IMAGE2D = 424,
     IMAGE3D = 425,
     IMAGECUBE = 426,
     IMAGE1DARRAY = 427,
     IMAGE2DARRAY = 428,
     IIMAGE1D = 429,
     IIMAGE2D = 430,
     IIMAGE3D = 431,
     IIMAGECUBE = 432,
     IIMAGE1DARRAY = 433,
     IIMAGE2DARRAY = 434,
     UIMAGE1D = 435,
     UIMAGE2D = 436,
     UIMAGE3D = 437,
     UIMAGECUBE = 438,
     UIMAGE1DARRAY = 439,
     UIMAGE2DARRAY = 440,
     IMAGE1DSHADOW = 441,
     IMAGE2DSHADOW = 442,
     IMAGEBUFFER = 443,
     IIMAGEBUFFER = 444,
     UIMAGEBUFFER = 445,
     ROW_MAJOR = 446
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 52 "glsl_parser.ypp"

   int n;
   float real;
   char *identifier;

   union {
      struct ast_type_qualifier q;
      unsigned i;
   } type_qualifier;

   ast_node *node;
   ast_type_specifier *type_specifier;
   ast_fully_specified_type *fully_specified_type;
   ast_function *function;
   ast_parameter_declarator *parameter_declarator;
   ast_function_definition *function_definition;
   ast_compound_statement *compound_statement;
   ast_expression *expression;
   ast_declarator_list *declarator_list;
   ast_struct_specifier *struct_specifier;
   ast_declaration *declaration;

   struct {
      ast_node *cond;
      ast_expression *rest;
   } for_rest_statement;

   struct {
      ast_node *then_statement;
      ast_node *else_statement;
   } selection_rest_statement;



/* Line 214 of yacc.c  */
#line 379 "glsl_parser.cpp"
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


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 404 "glsl_parser.cpp"

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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3923

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  216
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  88
/* YYNRULES -- Number of rules.  */
#define YYNRULES  275
/* YYNRULES -- Number of states.  */
#define YYNSTATES  411

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   446

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   200,     2,     2,     2,   204,   207,     2,
     192,   193,   202,   198,   197,   199,   196,   203,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   211,   213,
     205,   212,   206,   210,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   194,     2,   195,   208,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   214,   209,   215,   201,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     9,    10,    14,    17,    20,    23,
      26,    29,    30,    33,    39,    41,    44,    46,    48,    50,
      52,    54,    56,    60,    62,    67,    69,    73,    76,    79,
      81,    83,    85,    89,    92,    95,    98,   100,   103,   107,
     110,   112,   114,   116,   118,   121,   124,   127,   129,   131,
     133,   135,   137,   141,   145,   149,   151,   155,   159,   161,
     165,   169,   171,   175,   179,   183,   187,   189,   193,   197,
     199,   203,   205,   209,   211,   215,   217,   221,   223,   227,
     229,   233,   235,   241,   243,   247,   249,   251,   253,   255,
     257,   259,   261,   263,   265,   267,   269,   271,   275,   277,
     280,   283,   288,   291,   293,   295,   298,   302,   306,   309,
     315,   319,   322,   326,   329,   330,   332,   334,   336,   338,
     340,   344,   350,   357,   365,   374,   380,   382,   385,   390,
     396,   403,   411,   416,   419,   421,   424,   425,   427,   432,
     434,   438,   440,   442,   444,   446,   448,   450,   453,   456,
     458,   460,   463,   466,   469,   471,   474,   477,   479,   481,
     484,   486,   490,   495,   497,   499,   501,   503,   505,   507,
     509,   511,   513,   515,   517,   519,   521,   523,   525,   527,
     529,   531,   533,   535,   537,   539,   541,   543,   545,   547,
     549,   551,   553,   555,   557,   559,   561,   563,   565,   567,
     569,   571,   573,   575,   577,   579,   581,   583,   585,   587,
     589,   591,   593,   595,   597,   599,   601,   603,   605,   607,
     609,   615,   620,   622,   625,   629,   631,   635,   637,   642,
     644,   646,   648,   650,   652,   654,   656,   658,   660,   662,
     664,   667,   671,   673,   675,   678,   682,   684,   687,   689,
     692,   698,   702,   704,   706,   711,   717,   721,   724,   730,
     738,   745,   747,   749,   751,   752,   755,   759,   762,   765,
     768,   772,   775,   777,   779,   781
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     217,     0,    -1,    -1,   219,   221,   218,   223,    -1,    -1,
     109,    78,   113,    -1,   116,   113,    -1,   117,   113,    -1,
     118,   113,    -1,   119,   113,    -1,   120,   113,    -1,    -1,
     221,   222,    -1,   110,    76,   112,    76,   113,    -1,   302,
      -1,   223,   302,    -1,    76,    -1,   224,    -1,    78,    -1,
      79,    -1,    77,    -1,    80,    -1,   192,   251,   193,    -1,
     225,    -1,   226,   194,   227,   195,    -1,   228,    -1,   226,
     196,    76,    -1,   226,    84,    -1,   226,    85,    -1,   251,
      -1,   229,    -1,   230,    -1,   226,   196,   230,    -1,   232,
     193,    -1,   231,   193,    -1,   233,    74,    -1,   233,    -1,
     233,   249,    -1,   232,   197,   249,    -1,   234,   192,    -1,
     273,    -1,    76,    -1,    81,    -1,   226,    -1,    84,   235,
      -1,    85,   235,    -1,   236,   235,    -1,   198,    -1,   199,
      -1,   200,    -1,   201,    -1,   235,    -1,   237,   202,   235,
      -1,   237,   203,   235,    -1,   237,   204,   235,    -1,   237,
      -1,   238,   198,   237,    -1,   238,   199,   237,    -1,   238,
      -1,   239,    82,   238,    -1,   239,    83,   238,    -1,   239,
      -1,   240,   205,   239,    -1,   240,   206,   239,    -1,   240,
      86,   239,    -1,   240,    87,   239,    -1,   240,    -1,   241,
      88,   240,    -1,   241,    89,   240,    -1,   241,    -1,   242,
     207,   241,    -1,   242,    -1,   243,   208,   242,    -1,   243,
      -1,   244,   209,   243,    -1,   244,    -1,   245,    90,   244,
      -1,   245,    -1,   246,    92,   245,    -1,   246,    -1,   247,
      91,   246,    -1,   247,    -1,   247,   210,   251,   211,   249,
      -1,   248,    -1,   235,   250,   249,    -1,   212,    -1,    93,
      -1,    94,    -1,    96,    -1,    95,    -1,   102,    -1,    97,
      -1,    98,    -1,    99,    -1,   100,    -1,   101,    -1,   249,
      -1,   251,   197,   249,    -1,   248,    -1,   254,   213,    -1,
     262,   213,    -1,   108,   277,   274,   213,    -1,   255,   193,
      -1,   257,    -1,   256,    -1,   257,   259,    -1,   256,   197,
     259,    -1,   264,    76,   192,    -1,   273,    76,    -1,   273,
      76,   194,   252,   195,    -1,   270,   260,   258,    -1,   260,
     258,    -1,   270,   260,   261,    -1,   260,   261,    -1,    -1,
      33,    -1,    34,    -1,    35,    -1,   273,    -1,   263,    -1,
     262,   197,    76,    -1,   262,   197,    76,   194,   195,    -1,
     262,   197,    76,   194,   252,   195,    -1,   262,   197,    76,
     194,   195,   212,   283,    -1,   262,   197,    76,   194,   252,
     195,   212,   283,    -1,   262,   197,    76,   212,   283,    -1,
     264,    -1,   264,    76,    -1,   264,    76,   194,   195,    -1,
     264,    76,   194,   252,   195,    -1,   264,    76,   194,   195,
     212,   283,    -1,   264,    76,   194,   252,   195,   212,   283,
      -1,   264,    76,   212,   283,    -1,   103,    76,    -1,   273,
      -1,   271,   273,    -1,    -1,   266,    -1,   121,   192,   267,
     193,    -1,   268,    -1,   267,   197,   268,    -1,    76,    -1,
      40,    -1,    39,    -1,    38,    -1,     4,    -1,   272,    -1,
     269,   271,    -1,   103,   271,    -1,     4,    -1,     3,    -1,
     265,    37,    -1,    32,    37,    -1,   265,    33,    -1,    34,
      -1,    32,    33,    -1,    32,    34,    -1,    36,    -1,   274,
      -1,   277,   274,    -1,   275,    -1,   275,   194,   195,    -1,
     275,   194,   252,   195,    -1,   276,    -1,   278,    -1,    76,
      -1,    74,    -1,     6,    -1,     7,    -1,     8,    -1,     5,
      -1,    29,    -1,    30,    -1,    31,    -1,    20,    -1,    21,
      -1,    22,    -1,    23,    -1,    24,    -1,    25,    -1,    26,
      -1,    27,    -1,    28,    -1,    41,    -1,    42,    -1,    43,
      -1,    44,    -1,    45,    -1,    46,    -1,    47,    -1,    48,
      -1,    49,    -1,    50,    -1,    51,    -1,   155,    -1,    52,
      -1,    53,    -1,    54,    -1,    55,    -1,   157,    -1,    56,
      -1,    57,    -1,    58,    -1,    59,    -1,    60,    -1,    61,
      -1,    62,    -1,    63,    -1,    64,    -1,    65,    -1,    66,
      -1,    67,    -1,    68,    -1,    69,    -1,    70,    -1,    71,
      -1,    72,    -1,   106,    -1,   105,    -1,   104,    -1,    73,
      76,   214,   279,   215,    -1,    73,   214,   279,   215,    -1,
     280,    -1,   279,   280,    -1,   273,   281,   213,    -1,   282,
      -1,   281,   197,   282,    -1,    76,    -1,    76,   194,   252,
     195,    -1,   249,    -1,   253,    -1,   287,    -1,   286,    -1,
     284,    -1,   291,    -1,   292,    -1,   295,    -1,   296,    -1,
     297,    -1,   301,    -1,   214,   215,    -1,   214,   290,   215,
      -1,   289,    -1,   286,    -1,   214,   215,    -1,   214,   290,
     215,    -1,   285,    -1,   290,   285,    -1,   213,    -1,   251,
     213,    -1,    14,   192,   251,   193,   293,    -1,   285,    12,
     285,    -1,   285,    -1,   251,    -1,   264,    76,   212,   283,
      -1,    17,   192,   251,   193,   287,    -1,    18,   251,   211,
      -1,    19,   211,    -1,    75,   192,   294,   193,   288,    -1,
      11,   285,    75,   192,   251,   193,   213,    -1,    13,   192,
     298,   300,   193,   288,    -1,   291,    -1,   284,    -1,   294,
      -1,    -1,   299,   213,    -1,   299,   213,   251,    -1,    10,
     213,    -1,     9,   213,    -1,    16,   213,    -1,    16,   251,
     213,    -1,    15,   213,    -1,   303,    -1,   253,    -1,   220,
      -1,   254,   289,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   215,   215,   214,   221,   223,   248,   249,   250,   251,
     252,   264,   266,   270,   279,   287,   298,   302,   309,   316,
     323,   330,   337,   344,   345,   351,   355,   362,   368,   377,
     381,   385,   386,   395,   396,   400,   401,   405,   411,   423,
     427,   433,   440,   451,   452,   458,   464,   474,   475,   476,
     477,   481,   482,   488,   494,   503,   504,   510,   519,   520,
     526,   535,   536,   542,   548,   554,   563,   564,   570,   579,
     580,   589,   590,   599,   600,   609,   610,   619,   620,   629,
     630,   639,   640,   649,   650,   659,   660,   661,   662,   663,
     664,   665,   666,   667,   668,   669,   673,   677,   693,   697,
     701,   705,   719,   723,   724,   728,   733,   741,   752,   762,
     777,   784,   789,   800,   812,   813,   814,   815,   819,   823,
     824,   833,   842,   851,   860,   869,   882,   893,   902,   911,
     920,   929,   938,   947,   961,   968,   979,   980,   984,   991,
     992,   999,  1033,  1034,  1035,  1039,  1043,  1044,  1048,  1056,
    1057,  1058,  1059,  1060,  1061,  1062,  1063,  1064,  1068,  1069,
    1077,  1078,  1084,  1093,  1099,  1105,  1114,  1115,  1116,  1117,
    1118,  1119,  1120,  1121,  1122,  1123,  1124,  1125,  1126,  1127,
    1128,  1129,  1130,  1131,  1132,  1133,  1134,  1135,  1136,  1137,
    1138,  1139,  1140,  1141,  1142,  1143,  1144,  1145,  1146,  1147,
    1148,  1149,  1150,  1151,  1152,  1153,  1154,  1155,  1156,  1157,
    1158,  1159,  1160,  1161,  1162,  1163,  1164,  1168,  1178,  1188,
    1201,  1207,  1216,  1221,  1229,  1244,  1249,  1257,  1263,  1272,
    1276,  1282,  1283,  1287,  1288,  1289,  1290,  1291,  1292,  1293,
    1297,  1303,  1312,  1313,  1317,  1323,  1332,  1342,  1354,  1360,
    1369,  1378,  1383,  1391,  1395,  1409,  1413,  1414,  1418,  1425,
    1432,  1442,  1443,  1447,  1449,  1455,  1460,  1469,  1475,  1481,
    1487,  1493,  1502,  1503,  1504,  1508
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ATTRIBUTE", "CONST_TOK", "BOOL_TOK",
  "FLOAT_TOK", "INT_TOK", "UINT_TOK", "BREAK", "CONTINUE", "DO", "ELSE",
  "FOR", "IF", "DISCARD", "RETURN", "SWITCH", "CASE", "DEFAULT", "BVEC2",
  "BVEC3", "BVEC4", "IVEC2", "IVEC3", "IVEC4", "UVEC2", "UVEC3", "UVEC4",
  "VEC2", "VEC3", "VEC4", "CENTROID", "IN_TOK", "OUT_TOK", "INOUT_TOK",
  "UNIFORM", "VARYING", "NOPERSPECTIVE", "FLAT", "SMOOTH", "MAT2X2",
  "MAT2X3", "MAT2X4", "MAT3X2", "MAT3X3", "MAT3X4", "MAT4X2", "MAT4X3",
  "MAT4X4", "SAMPLER1D", "SAMPLER2D", "SAMPLER3D", "SAMPLERCUBE",
  "SAMPLER1DSHADOW", "SAMPLER2DSHADOW", "SAMPLERCUBESHADOW",
  "SAMPLER1DARRAY", "SAMPLER2DARRAY", "SAMPLER1DARRAYSHADOW",
  "SAMPLER2DARRAYSHADOW", "ISAMPLER1D", "ISAMPLER2D", "ISAMPLER3D",
  "ISAMPLERCUBE", "ISAMPLER1DARRAY", "ISAMPLER2DARRAY", "USAMPLER1D",
  "USAMPLER2D", "USAMPLER3D", "USAMPLERCUBE", "USAMPLER1DARRAY",
  "USAMPLER2DARRAY", "STRUCT", "VOID_TOK", "WHILE", "IDENTIFIER",
  "FLOATCONSTANT", "INTCONSTANT", "UINTCONSTANT", "BOOLCONSTANT",
  "FIELD_SELECTION", "LEFT_OP", "RIGHT_OP", "INC_OP", "DEC_OP", "LE_OP",
  "GE_OP", "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "XOR_OP", "MUL_ASSIGN",
  "DIV_ASSIGN", "ADD_ASSIGN", "MOD_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN",
  "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "SUB_ASSIGN", "INVARIANT",
  "LOWP", "MEDIUMP", "HIGHP", "SUPERP", "PRECISION", "VERSION",
  "EXTENSION", "LINE", "COLON", "EOL", "INTERFACE", "OUTPUT",
  "PRAGMA_DEBUG_ON", "PRAGMA_DEBUG_OFF", "PRAGMA_OPTIMIZE_ON",
  "PRAGMA_OPTIMIZE_OFF", "PRAGMA_INVARIANT_ALL", "LAYOUT_TOK", "ASM",
  "CLASS", "UNION", "ENUM", "TYPEDEF", "TEMPLATE", "THIS", "PACKED_TOK",
  "GOTO", "INLINE_TOK", "NOINLINE", "VOLATILE", "PUBLIC_TOK", "STATIC",
  "EXTERN", "EXTERNAL", "LONG_TOK", "SHORT_TOK", "DOUBLE_TOK", "HALF",
  "FIXED_TOK", "UNSIGNED", "INPUT_TOK", "OUPTUT", "HVEC2", "HVEC3",
  "HVEC4", "DVEC2", "DVEC3", "DVEC4", "FVEC2", "FVEC3", "FVEC4",
  "SAMPLER2DRECT", "SAMPLER3DRECT", "SAMPLER2DRECTSHADOW", "SIZEOF",
  "CAST", "NAMESPACE", "USING", "ERROR_TOK", "COMMON", "PARTITION",
  "ACTIVE", "SAMPLERBUFFER", "FILTER", "IMAGE1D", "IMAGE2D", "IMAGE3D",
  "IMAGECUBE", "IMAGE1DARRAY", "IMAGE2DARRAY", "IIMAGE1D", "IIMAGE2D",
  "IIMAGE3D", "IIMAGECUBE", "IIMAGE1DARRAY", "IIMAGE2DARRAY", "UIMAGE1D",
  "UIMAGE2D", "UIMAGE3D", "UIMAGECUBE", "UIMAGE1DARRAY", "UIMAGE2DARRAY",
  "IMAGE1DSHADOW", "IMAGE2DSHADOW", "IMAGEBUFFER", "IIMAGEBUFFER",
  "UIMAGEBUFFER", "ROW_MAJOR", "'('", "')'", "'['", "']'", "'.'", "','",
  "'+'", "'-'", "'!'", "'~'", "'*'", "'/'", "'%'", "'<'", "'>'", "'&'",
  "'^'", "'|'", "'?'", "':'", "'='", "';'", "'{'", "'}'", "$accept",
  "translation_unit", "$@1", "version_statement", "pragma_statement",
  "extension_statement_list", "extension_statement",
  "external_declaration_list", "variable_identifier", "primary_expression",
  "postfix_expression", "integer_expression", "function_call",
  "function_call_or_method", "function_call_generic",
  "function_call_header_no_parameters",
  "function_call_header_with_parameters", "function_call_header",
  "function_identifier", "unary_expression", "unary_operator",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_xor_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "assignment_operator", "expression",
  "constant_expression", "declaration", "function_prototype",
  "function_declarator", "function_header_with_parameters",
  "function_header", "parameter_declarator", "parameter_declaration",
  "parameter_qualifier", "parameter_type_specifier",
  "init_declarator_list", "single_declaration", "fully_specified_type",
  "opt_layout_qualifier", "layout_qualifier", "layout_qualifier_id_list",
  "layout_qualifier_id", "interpolation_qualifier",
  "parameter_type_qualifier", "type_qualifier", "storage_qualifier",
  "type_specifier", "type_specifier_no_prec", "type_specifier_nonarray",
  "basic_type_specifier_nonarray", "precision_qualifier",
  "struct_specifier", "struct_declaration_list", "struct_declaration",
  "struct_declarator_list", "struct_declarator", "initializer",
  "declaration_statement", "statement", "simple_statement",
  "compound_statement", "statement_no_new_scope",
  "compound_statement_no_new_scope", "statement_list",
  "expression_statement", "selection_statement",
  "selection_rest_statement", "condition", "switch_statement",
  "case_label", "iteration_statement", "for_init_statement",
  "conditionopt", "for_rest_statement", "jump_statement",
  "external_declaration", "function_definition", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,    40,    41,    91,    93,    46,    44,    43,    45,
      33,   126,    42,    47,    37,    60,    62,    38,    94,   124,
      63,    58,    61,    59,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   216,   218,   217,   219,   219,   220,   220,   220,   220,
     220,   221,   221,   222,   223,   223,   224,   225,   225,   225,
     225,   225,   225,   226,   226,   226,   226,   226,   226,   227,
     228,   229,   229,   230,   230,   231,   231,   232,   232,   233,
     234,   234,   234,   235,   235,   235,   235,   236,   236,   236,
     236,   237,   237,   237,   237,   238,   238,   238,   239,   239,
     239,   240,   240,   240,   240,   240,   241,   241,   241,   242,
     242,   243,   243,   244,   244,   245,   245,   246,   246,   247,
     247,   248,   248,   249,   249,   250,   250,   250,   250,   250,
     250,   250,   250,   250,   250,   250,   251,   251,   252,   253,
     253,   253,   254,   255,   255,   256,   256,   257,   258,   258,
     259,   259,   259,   259,   260,   260,   260,   260,   261,   262,
     262,   262,   262,   262,   262,   262,   263,   263,   263,   263,
     263,   263,   263,   263,   264,   264,   265,   265,   266,   267,
     267,   268,   269,   269,   269,   270,   271,   271,   271,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   273,   273,
     274,   274,   274,   275,   275,   275,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,   276,   276,   277,   277,   277,
     278,   278,   279,   279,   280,   281,   281,   282,   282,   283,
     284,   285,   285,   286,   286,   286,   286,   286,   286,   286,
     287,   287,   288,   288,   289,   289,   290,   290,   291,   291,
     292,   293,   293,   294,   294,   295,   296,   296,   297,   297,
     297,   298,   298,   299,   299,   300,   300,   301,   301,   301,
     301,   301,   302,   302,   302,   303
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     4,     0,     3,     2,     2,     2,     2,
       2,     0,     2,     5,     1,     2,     1,     1,     1,     1,
       1,     1,     3,     1,     4,     1,     3,     2,     2,     1,
       1,     1,     3,     2,     2,     2,     1,     2,     3,     2,
       1,     1,     1,     1,     2,     2,     2,     1,     1,     1,
       1,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     5,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     2,
       2,     4,     2,     1,     1,     2,     3,     3,     2,     5,
       3,     2,     3,     2,     0,     1,     1,     1,     1,     1,
       3,     5,     6,     7,     8,     5,     1,     2,     4,     5,
       6,     7,     4,     2,     1,     2,     0,     1,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     2,     2,     1,
       1,     2,     2,     2,     1,     2,     2,     1,     1,     2,
       1,     3,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     4,     1,     2,     3,     1,     3,     1,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     3,     1,     1,     2,     3,     1,     2,     1,     2,
       5,     3,     1,     1,     4,     5,     3,     2,     5,     7,
       6,     1,     1,     1,     0,     2,     3,     2,     2,     2,
       3,     2,     1,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,     0,    11,     0,     1,     2,     5,     0,   136,
      12,     0,   150,   149,   170,   167,   168,   169,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   171,   172,   173,
       0,   154,   157,   144,   143,   142,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   195,   196,   197,
     198,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,     0,   166,
     165,   136,   219,   218,   217,     0,     0,     0,     0,     0,
       0,     0,   194,   199,   274,   136,   273,     0,     0,   104,
     114,     0,   119,   126,     0,   137,   136,     0,   146,   134,
     158,   160,   163,     0,   164,    14,   272,     0,   155,   156,
     152,     0,     0,   133,   136,   148,     0,     6,     7,     8,
       9,    10,     0,    15,    99,   136,   275,   102,   114,   145,
     115,   116,   117,   105,     0,   114,     0,   100,   127,   153,
     151,   147,   135,     0,   159,     0,     0,     0,     0,   222,
       0,   141,     0,   139,     0,     0,   136,     0,     0,     0,
       0,     0,     0,     0,     0,    16,    20,    18,    19,    21,
      42,     0,     0,     0,    47,    48,    49,    50,   248,   136,
     244,    17,    23,    43,    25,    30,    31,     0,     0,    36,
       0,    51,     0,    55,    58,    61,    66,    69,    71,    73,
      75,    77,    79,    81,    83,    96,     0,   230,     0,   134,
     233,   246,   232,   231,   136,   234,   235,   236,   237,   238,
     239,   106,   111,   113,   118,     0,   120,   107,     0,     0,
     161,    51,    98,     0,    40,    13,     0,   227,     0,   225,
     221,   223,   101,   138,     0,   268,   267,     0,   136,     0,
     271,   269,     0,     0,     0,   257,   136,    44,    45,     0,
     240,   136,    27,    28,     0,     0,    34,    33,     0,   166,
      37,    39,    86,    87,    89,    88,    91,    92,    93,    94,
      95,    90,    85,     0,    46,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   249,   245,   247,   108,
     110,   112,     0,     0,   128,     0,   229,   132,   162,   220,
       0,     0,   224,   140,     0,   262,   261,   136,     0,   270,
       0,   256,   253,     0,     0,    22,   241,     0,    29,    26,
      32,    38,    84,    52,    53,    54,    56,    57,    59,    60,
      64,    65,    62,    63,    67,    68,    70,    72,    74,    76,
      78,    80,     0,    97,     0,   121,     0,   125,     0,   129,
       0,   226,     0,   263,     0,     0,   136,     0,     0,   136,
      24,     0,     0,     0,   122,   130,     0,   228,     0,   265,
     136,   252,   250,   255,     0,   243,   258,   242,    82,   109,
     123,     0,   131,     0,   266,   260,   136,   254,   124,   259,
     251
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     9,     3,    84,     6,    10,    85,   181,   182,
     183,   337,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   283,   206,   233,   207,   208,    88,
      89,    90,   222,   133,   134,   223,    91,    92,    93,    94,
      95,   152,   153,    96,   135,    97,    98,   234,   100,   101,
     102,   103,   104,   148,   149,   238,   239,   317,   210,   211,
     212,   213,   396,   397,   214,   215,   216,   392,   334,   217,
     218,   219,   327,   374,   375,   220,   105,   106
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -307
static const yytype_int16 yypact[] =
{
     -56,   -46,    80,  -307,   -30,  -307,   -32,  -307,    16,  3505,
    -307,   -14,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
      78,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,   -71,  -307,
    -307,    10,  -307,  -307,  -307,    17,   -13,    -4,     4,    15,
      20,   -48,  -307,  -307,  -307,  3385,  -307,   -78,   -44,   -20,
       0,  -157,  -307,    99,    48,  -307,   369,  3694,  -307,  -307,
    -307,     2,  -307,  3766,  -307,  -307,  -307,   105,  -307,  -307,
    -307,   -10,  3694,  -307,   369,  -307,  3766,  -307,  -307,  -307,
    -307,  -307,   141,  -307,  -307,   281,  -307,  -307,    35,  -307,
    -307,  -307,  -307,  -307,  3694,   150,   143,  -307,  -147,  -307,
    -307,  -307,  -307,  2475,  -307,    81,  3694,   144,  1860,  -307,
       9,  -307,   -79,  -307,    11,    12,  1133,    34,    36,    18,
    2094,    37,  3021,    21,    41,   -60,  -307,  -307,  -307,  -307,
    -307,  3021,  3021,  3021,  -307,  -307,  -307,  -307,  -307,   494,
    -307,  -307,  -307,   -22,  -307,  -307,  -307,    43,   -73,  3203,
      42,   -72,  3021,    -1,    -7,   116,   -76,   118,    30,    32,
      29,   151,   152,   -84,  -307,  -307,  -156,  -307,    33,    50,
    -307,  -307,  -307,  -307,   707,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,   167,  3694,  -140,  -307,  2657,  3021,
    -307,  -307,  -307,    53,  -307,  -307,  1977,    51,  -146,  -307,
    -307,  -307,  -307,  -307,   141,  -307,  -307,   174,  1544,  3021,
    -307,  -307,  -142,  3021,  -145,  -307,  2293,  -307,  -307,   -59,
    -307,   920,  -307,  -307,  3021,  3622,  -307,  -307,  3021,    57,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  3021,  -307,  3021,  3021,  3021,  3021,  3021,
    3021,  3021,  3021,  3021,  3021,  3021,  3021,  3021,  3021,  3021,
    3021,  3021,  3021,  3021,  3021,  3021,  -307,  -307,  -307,    59,
    -307,  -307,  2839,  3021,    44,    60,  -307,  -307,  -307,  -307,
    3021,   144,  -307,  -307,    62,  -307,  -307,  1743,   -52,  -307,
     -51,  -307,    61,   181,    66,  -307,  -307,    65,    61,    69,
    -307,  -307,  -307,  -307,  -307,  -307,    -1,    -1,    -7,    -7,
     116,   116,   116,   116,   -76,   -76,   118,    30,    32,    29,
     151,   152,  -137,  -307,  3021,    52,    67,  -307,  3021,    54,
      68,  -307,  3021,  -307,    55,    72,  1133,    56,    63,  1345,
    -307,  3021,    74,  3021,    64,  -307,  3021,  -307,   -17,  3021,
    1345,   255,  -307,  -307,  3021,  -307,  -307,  -307,  -307,  -307,
    -307,  3021,  -307,    58,    61,  -307,  1133,  -307,  -307,  -307,
    -307
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,     7,  -307,  -307,  -307,  -307,  -134,
    -307,   -77,   -81,  -105,   -83,   -25,   -21,   -26,   -24,   -23,
      13,  -307,  -141,  -186,  -307,  -154,  -216,     6,    22,  -307,
    -307,  -307,    89,   153,   145,   138,  -307,  -307,  -238,  -307,
    -307,  -307,    38,  -307,  -307,   -35,  -307,    -9,   -39,  -307,
    -307,   208,  -307,   147,  -131,  -307,    47,  -293,   121,  -155,
    -306,    -6,   -16,   277,   196,   128,  -307,  -307,    71,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,   292,  -307
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -265
static const yytype_int16 yytable[] =
{
      99,   247,   232,   270,   129,   111,   252,   303,   254,   231,
     292,   293,   315,    12,    13,    86,  -165,   241,   333,   259,
     367,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,    87,     4,   130,   131,   132,   115,   257,   258,   129,
     136,   305,    30,   316,    31,   227,    32,   228,    33,    34,
      35,   321,   305,     1,   312,   305,   137,   306,   284,   308,
     305,   141,   262,   263,   144,   229,   331,   322,   130,   131,
     132,   329,   313,   395,   381,   385,    99,   150,     8,   115,
       5,   139,   341,     7,   395,   140,   113,   232,   142,   333,
     400,    86,    11,   402,   231,   328,   366,   342,   107,   330,
     117,   407,   332,   147,   370,   241,   308,    87,   408,   118,
     338,   108,   109,   114,   243,   110,   209,   119,   244,   363,
     267,    72,    73,    74,   268,   224,   304,   316,   120,   294,
     295,    81,   -41,   121,   335,   124,   125,   147,   305,   147,
     282,   376,   377,   112,   122,   305,   305,   209,   382,   127,
     362,   343,   344,   345,   231,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   231,   231,   231,   231,   231,   231,
     209,   232,   264,   332,   265,   138,   403,   128,   231,   232,
     305,   145,   316,   130,   131,   132,   231,   350,   351,   352,
     353,   288,   289,  -103,   235,   398,   143,   316,   290,   291,
     316,   285,   286,   287,   146,   209,   296,   297,   316,   348,
     349,   346,   347,   354,   355,   316,   224,   151,   388,   226,
     237,   391,   242,   232,   245,   246,   248,   147,   249,   253,
     231,   250,   255,   256,   271,   404,   266,   298,   300,   209,
     299,   301,   -40,   309,   302,   320,   124,   209,   318,   324,
     -35,   410,   209,   364,   372,   369,   368,   378,   305,   379,
     380,   -41,   384,   387,   383,   390,   386,   406,   389,   399,
     179,   409,   340,   356,   358,   394,   401,   359,   357,   360,
     225,   221,   323,   116,    12,    13,    14,    15,    16,    17,
     154,   155,   156,   236,   157,   158,   159,   160,   161,   162,
     163,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,   310,    31,   361,    32,   209,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,   164,   165,   166,   167,
     168,   169,   170,   311,   126,   171,   172,   209,   371,   325,
     209,   393,    12,    13,   405,   261,   326,   123,     0,     0,
       0,   209,     0,     0,    71,    72,    73,    74,     0,    75,
       0,     0,     0,     0,     0,     0,     0,   209,   373,     0,
       0,    30,    81,    31,     0,    32,     0,    33,    34,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    82,     0,    83,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   114,   173,     0,     0,     0,     0,     0,   174,
     175,   176,   177,     0,     0,     0,     0,     0,     0,     0,
      81,     0,     0,     0,   178,   179,   180,    12,    13,    14,
      15,    16,    17,   154,   155,   156,     0,   157,   158,   159,
     160,   161,   162,   163,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,     0,    31,     0,
      32,     0,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,   164,
     165,   166,   167,   168,   169,   170,     0,     0,   171,   172,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    71,    72,    73,
      74,     0,    75,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    81,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    82,
       0,    83,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   173,     0,     0,     0,
       0,     0,   174,   175,   176,   177,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   178,   179,   260,
      12,    13,    14,    15,    16,    17,   154,   155,   156,     0,
     157,   158,   159,   160,   161,   162,   163,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
       0,    31,     0,    32,     0,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,   164,   165,   166,   167,   168,   169,   170,     0,
       0,   171,   172,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      71,    72,    73,    74,     0,    75,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    81,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    82,     0,    83,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   173,
       0,     0,     0,     0,     0,   174,   175,   176,   177,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     178,   179,   307,    12,    13,    14,    15,    16,    17,   154,
     155,   156,     0,   157,   158,   159,   160,   161,   162,   163,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,     0,    31,     0,    32,     0,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,   164,   165,   166,   167,   168,
     169,   170,     0,     0,   171,   172,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    71,    72,    73,    74,     0,    75,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    81,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    82,     0,    83,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   173,     0,     0,     0,     0,     0,   174,   175,
     176,   177,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   178,   179,   336,    12,    13,    14,    15,
      16,    17,   154,   155,   156,     0,   157,   158,   159,   160,
     161,   162,   163,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,     0,    31,     0,    32,
       0,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,   164,   165,
     166,   167,   168,   169,   170,     0,     0,   171,   172,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    71,    72,    73,    74,
       0,    75,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    81,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    82,     0,
      83,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   173,     0,     0,     0,     0,
       0,   174,   175,   176,   177,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   178,   179,    12,    13,
      14,    15,    16,    17,   154,   155,   156,     0,   157,   158,
     159,   160,   161,   162,   163,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,     0,    31,
       0,    32,     0,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
     164,   165,   166,   167,   168,   169,   170,     0,     0,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    71,    72,
      73,    74,     0,    75,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    81,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      82,     0,    83,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   173,     0,     0,
       0,     0,     0,   174,   175,   176,   177,    12,    13,    14,
      15,    16,    17,     0,     0,     0,     0,     0,   178,   125,
       0,     0,     0,     0,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,     0,    31,     0,
      32,     0,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,     0,
     165,   166,   167,   168,   169,   170,     0,     0,   171,   172,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    71,    72,    73,
      74,     0,    75,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    81,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    82,
       0,    83,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   173,     0,     0,     0,
       0,     0,   174,   175,   176,   177,    12,    13,    14,    15,
      16,    17,     0,     0,     0,     0,     0,   178,     0,     0,
       0,     0,     0,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,     0,    31,     0,    32,
       0,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,     0,   165,
     166,   167,   168,   169,   170,     0,     0,   171,   172,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   114,    72,    73,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    81,    14,    15,    16,    17,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,     0,     0,     0,     0,     0,     0,    82,     0,
      83,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,   173,    70,     0,     0,     0,
       0,   174,   175,   176,   177,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -264,     0,     0,     0,
       0,     0,     0,     0,    72,    73,    74,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    14,    15,    16,    17,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,     0,
       0,     0,     0,     0,     0,    82,     0,    83,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,     0,    70,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   240,     0,     0,     0,     0,
       0,    72,    73,    74,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    14,
      15,    16,    17,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,     0,     0,     0,     0,
       0,     0,    82,     0,    83,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,     0,
     165,   166,   167,   168,   169,   170,     0,     0,   171,   172,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   319,     0,     0,     0,     0,     0,    72,    73,
      74,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    82,
       0,    83,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   173,     0,     0,     0,
       0,     0,   174,   175,   176,   177,    12,    13,    14,    15,
      16,    17,     0,     0,     0,     0,     0,   251,     0,     0,
       0,     0,     0,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,     0,    31,     0,    32,
       0,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,     0,   165,
     166,   167,   168,   169,   170,     0,     0,   171,   172,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   114,    72,    73,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    81,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    82,     0,
      83,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      14,    15,    16,    17,     0,   173,     0,     0,     0,     0,
       0,   174,   175,   176,   177,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
       0,   165,   166,   167,   168,   169,   170,     0,     0,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    72,
      73,    74,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      82,     0,    83,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    14,    15,    16,    17,     0,   173,     0,     0,
     230,     0,     0,   174,   175,   176,   177,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,     0,   165,   166,   167,   168,   169,   170,     0,
       0,   171,   172,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    72,    73,    74,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    82,     0,    83,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    14,    15,    16,    17,     0,   173,
       0,     0,   314,     0,     0,   174,   175,   176,   177,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,     0,   165,   166,   167,   168,   169,
     170,     0,     0,   171,   172,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    72,    73,    74,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    82,     0,    83,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    14,    15,    16,    17,
       0,   173,     0,     0,   365,     0,     0,   174,   175,   176,
     177,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,     0,   165,   166,   167,
     168,   169,   170,     0,     0,   171,   172,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    72,    73,    74,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    82,     0,    83,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    14,    15,
      16,    17,     0,   173,     0,     0,     0,     0,     0,   174,
     175,   176,   177,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,   269,     0,   165,
     166,   167,   168,   169,   170,     0,     0,   171,   172,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    72,    73,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    82,     0,
      83,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    -3,     0,     0,    12,    13,
      14,    15,    16,    17,     0,   173,     0,     0,     0,     0,
       0,   174,   175,   176,   177,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,     0,    31,
       0,    32,     0,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
       0,    70,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    71,    72,
      73,    74,     0,    75,     0,     0,     0,     0,     0,     0,
       0,    76,    77,    78,    79,    80,    81,     0,    12,    13,
      14,    15,    16,    17,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,     0,    31,
      82,    32,    83,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
       0,    70,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    71,    72,
      73,    74,     0,    75,     0,     0,     0,     0,     0,     0,
       0,    76,    77,    78,    79,    80,    81,    14,    15,    16,
      17,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,     0,     0,     0,     0,     0,     0,
      82,     0,    83,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,     0,   339,    14,
      15,    16,    17,   170,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    72,    73,    74,     0,
       0,     0,     0,     0,     0,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,     0,
      70,    14,    15,    16,    17,     0,     0,    82,     0,    83,
       0,     0,     0,     0,     0,     0,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    72,    73,
      74,     0,     0,     0,     0,     0,     0,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,     0,    70,     0,     0,     0,     0,     0,     0,    82,
       0,    83,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    82,     0,    83
};

static const yytype_int16 yycheck[] =
{
       9,   156,   143,   189,     4,    76,   160,    91,   162,   143,
      86,    87,   228,     3,     4,     9,    76,   148,   256,   173,
     313,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,     9,    78,    33,    34,    35,    71,   171,   172,     4,
     197,   197,    32,   229,    34,   192,    36,   194,    38,    39,
      40,   197,   197,   109,   194,   197,   213,   213,   192,   214,
     197,    96,    84,    85,   103,   212,   211,   213,    33,    34,
      35,   213,   212,   379,   211,   368,    85,   116,   110,   114,
       0,    33,   268,   113,   390,    37,    76,   228,    97,   327,
     383,    85,    76,   386,   228,   249,   312,   283,   112,   253,
     113,   394,   256,   112,   320,   236,   261,    85,   401,   113,
     264,    33,    34,   103,   193,    37,   125,   113,   197,   305,
     193,   104,   105,   106,   197,   134,   210,   313,   113,   205,
     206,   121,   192,   113,   193,   213,   214,   146,   197,   148,
     212,   193,   193,   214,   192,   197,   197,   156,   364,   193,
     304,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     179,   312,   194,   327,   196,    76,   193,   197,   312,   320,
     197,    76,   368,    33,    34,    35,   320,   292,   293,   294,
     295,   198,   199,   193,   113,   381,   194,   383,    82,    83,
     386,   202,   203,   204,   214,   214,    88,    89,   394,   290,
     291,   288,   289,   296,   297,   401,   225,    76,   372,    76,
      76,   376,   213,   364,   213,   213,   192,   236,   192,   192,
     364,   213,   211,   192,   192,   389,   193,   207,   209,   248,
     208,    90,   192,    76,    92,   194,   213,   256,   195,    75,
     193,   406,   261,   194,   192,   195,   212,    76,   197,   193,
     195,   192,   195,   195,   212,   193,   212,    12,   213,   195,
     214,   213,   265,   298,   300,   212,   212,   301,   299,   302,
     135,   128,   244,    75,     3,     4,     5,     6,     7,     8,
       9,    10,    11,   146,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,   225,    34,   303,    36,   327,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,   225,    87,    84,    85,   376,   321,   248,
     379,   377,     3,     4,   390,   179,   248,    85,    -1,    -1,
      -1,   390,    -1,    -1,   103,   104,   105,   106,    -1,   108,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   406,   327,    -1,
      -1,    32,   121,    34,    -1,    36,    -1,    38,    39,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   155,    -1,   157,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   103,   192,    -1,    -1,    -1,    -1,    -1,   198,
     199,   200,   201,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     121,    -1,    -1,    -1,   213,   214,   215,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    -1,
      36,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    -1,    -1,    84,    85,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,   104,   105,
     106,    -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   155,
      -1,   157,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   192,    -1,    -1,    -1,
      -1,    -1,   198,   199,   200,   201,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   213,   214,   215,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    -1,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    -1,    36,    -1,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    -1,
      -1,    84,    85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     103,   104,   105,   106,    -1,   108,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   121,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   155,    -1,   157,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   192,
      -1,    -1,    -1,    -1,    -1,   198,   199,   200,   201,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     213,   214,   215,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    -1,    34,    -1,    36,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   103,   104,   105,   106,    -1,   108,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   121,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   155,    -1,   157,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   192,    -1,    -1,    -1,    -1,    -1,   198,   199,
     200,   201,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   213,   214,   215,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    -1,    36,
      -1,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    -1,    -1,    84,    85,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   103,   104,   105,   106,
      -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   155,    -1,
     157,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   192,    -1,    -1,    -1,    -1,
      -1,   198,   199,   200,   201,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   213,   214,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      -1,    36,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    -1,    -1,    84,
      85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,   104,
     105,   106,    -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     155,    -1,   157,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   192,    -1,    -1,
      -1,    -1,    -1,   198,   199,   200,   201,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,   213,   214,
      -1,    -1,    -1,    -1,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    34,    -1,
      36,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    -1,
      76,    77,    78,    79,    80,    81,    -1,    -1,    84,    85,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,   104,   105,
     106,    -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   155,
      -1,   157,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   192,    -1,    -1,    -1,
      -1,    -1,   198,   199,   200,   201,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,   213,    -1,    -1,
      -1,    -1,    -1,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    -1,    36,
      -1,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    -1,    76,
      77,    78,    79,    80,    81,    -1,    -1,    84,    85,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   103,   104,   105,   106,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   121,     5,     6,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,   155,    -1,
     157,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,   192,    76,    -1,    -1,    -1,
      -1,   198,   199,   200,   201,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   213,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,   155,    -1,   157,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   215,    -1,    -1,    -1,    -1,
      -1,   104,   105,   106,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,
      -1,    -1,   155,    -1,   157,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    -1,
      76,    77,    78,    79,    80,    81,    -1,    -1,    84,    85,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   215,    -1,    -1,    -1,    -1,    -1,   104,   105,
     106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   155,
      -1,   157,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   192,    -1,    -1,    -1,
      -1,    -1,   198,   199,   200,   201,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,   213,    -1,    -1,
      -1,    -1,    -1,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    -1,    36,
      -1,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    -1,    76,
      77,    78,    79,    80,    81,    -1,    -1,    84,    85,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   103,   104,   105,   106,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   121,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   155,    -1,
     157,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       5,     6,     7,     8,    -1,   192,    -1,    -1,    -1,    -1,
      -1,   198,   199,   200,   201,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    76,    77,    78,    79,    80,    81,    -1,    -1,    84,
      85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,
     105,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     155,    -1,   157,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     5,     6,     7,     8,    -1,   192,    -1,    -1,
     195,    -1,    -1,   198,   199,   200,   201,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    76,    77,    78,    79,    80,    81,    -1,
      -1,    84,    85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,   105,   106,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   155,    -1,   157,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     5,     6,     7,     8,    -1,   192,
      -1,    -1,   195,    -1,    -1,   198,   199,   200,   201,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    -1,    76,    77,    78,    79,    80,
      81,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   104,   105,   106,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   155,    -1,   157,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     5,     6,     7,     8,
      -1,   192,    -1,    -1,   195,    -1,    -1,   198,   199,   200,
     201,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    76,    77,    78,
      79,    80,    81,    -1,    -1,    84,    85,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   104,   105,   106,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   155,    -1,   157,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,     6,
       7,     8,    -1,   192,    -1,    -1,    -1,    -1,    -1,   198,
     199,   200,   201,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    -1,    76,
      77,    78,    79,    80,    81,    -1,    -1,    84,    85,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,   105,   106,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   155,    -1,
     157,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     0,    -1,    -1,     3,     4,
       5,     6,     7,     8,    -1,   192,    -1,    -1,    -1,    -1,
      -1,   198,   199,   200,   201,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      -1,    36,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,   104,
     105,   106,    -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   116,   117,   118,   119,   120,   121,    -1,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
     155,    36,   157,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,   104,
     105,   106,    -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   116,   117,   118,   119,   120,   121,     5,     6,     7,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
     155,    -1,   157,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    -1,    76,     5,
       6,     7,     8,    81,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,   104,   105,   106,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    -1,
      76,     5,     6,     7,     8,    -1,    -1,   155,    -1,   157,
      -1,    -1,    -1,    -1,    -1,    -1,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,   104,   105,
     106,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,   155,
      -1,   157,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   155,    -1,   157
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   109,   217,   219,    78,     0,   221,   113,   110,   218,
     222,    76,     3,     4,     5,     6,     7,     8,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    34,    36,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      76,   103,   104,   105,   106,   108,   116,   117,   118,   119,
     120,   121,   155,   157,   220,   223,   253,   254,   255,   256,
     257,   262,   263,   264,   265,   266,   269,   271,   272,   273,
     274,   275,   276,   277,   278,   302,   303,   112,    33,    34,
      37,    76,   214,    76,   103,   271,   277,   113,   113,   113,
     113,   113,   192,   302,   213,   214,   289,   193,   197,     4,
      33,    34,    35,   259,   260,   270,   197,   213,    76,    33,
      37,   271,   273,   194,   274,    76,   214,   273,   279,   280,
     274,    76,   267,   268,     9,    10,    11,    13,    14,    15,
      16,    17,    18,    19,    75,    76,    77,    78,    79,    80,
      81,    84,    85,   192,   198,   199,   200,   201,   213,   214,
     215,   224,   225,   226,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   251,   253,   254,   273,
     284,   285,   286,   287,   290,   291,   292,   295,   296,   297,
     301,   259,   258,   261,   273,   260,    76,   192,   194,   212,
     195,   235,   248,   252,   273,   113,   279,    76,   281,   282,
     215,   280,   213,   193,   197,   213,   213,   285,   192,   192,
     213,   213,   251,   192,   251,   211,   192,   235,   235,   251,
     215,   290,    84,    85,   194,   196,   193,   193,   197,    74,
     249,   192,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   212,   250,   235,   202,   203,   204,   198,   199,
      82,    83,    86,    87,   205,   206,    88,    89,   207,   208,
     209,    90,    92,    91,   210,   197,   213,   215,   285,    76,
     258,   261,   194,   212,   195,   252,   249,   283,   195,   215,
     194,   197,   213,   268,    75,   284,   291,   298,   251,   213,
     251,   211,   251,   264,   294,   193,   215,   227,   251,    76,
     230,   249,   249,   235,   235,   235,   237,   237,   238,   238,
     239,   239,   239,   239,   240,   240,   241,   242,   243,   244,
     245,   246,   251,   249,   194,   195,   252,   283,   212,   195,
     252,   282,   192,   294,   299,   300,   193,   193,    76,   193,
     195,   211,   252,   212,   195,   283,   212,   195,   251,   213,
     193,   285,   293,   287,   212,   286,   288,   289,   249,   195,
     283,   212,   283,   193,   251,   288,    12,   283,   283,   213,
     285
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

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (&yylloc, state, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc, scanner)
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
		  Type, Value, Location, state); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct _mesa_glsl_parse_state *state)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, state)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    struct _mesa_glsl_parse_state *state;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (state);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct _mesa_glsl_parse_state *state)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, state)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    struct _mesa_glsl_parse_state *state;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, state);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, struct _mesa_glsl_parse_state *state)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, state)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    struct _mesa_glsl_parse_state *state;
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
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , state);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, state); \
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, struct _mesa_glsl_parse_state *state)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, state)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    struct _mesa_glsl_parse_state *state;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (state);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (struct _mesa_glsl_parse_state *state);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
yyparse (struct _mesa_glsl_parse_state *state)
#else
int
yyparse (state)
    struct _mesa_glsl_parse_state *state;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

/* User initialization code.  */

/* Line 1251 of yacc.c  */
#line 41 "glsl_parser.ypp"
{
   yylloc.first_line = 1;
   yylloc.first_column = 1;
   yylloc.last_line = 1;
   yylloc.last_column = 1;
   yylloc.source = 0;
}

/* Line 1251 of yacc.c  */
#line 2679 "glsl_parser.cpp"
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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;
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

/* Line 1464 of yacc.c  */
#line 215 "glsl_parser.ypp"
    {
	   _mesa_glsl_initialize_types(state);
	;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 224 "glsl_parser.ypp"
    {
	   switch ((yyvsp[(2) - (3)].n)) {
	   case 100:
	      state->es_shader = true;
	   case 110:
	   case 120:
	   case 130:
	      /* FINISHME: Check against implementation support versions. */
	      state->language_version = (yyvsp[(2) - (3)].n);
	      state->version_string =
		 talloc_asprintf(state, "GLSL%s %d.%02d",
				 state->es_shader ? " ES" : "",
				 state->language_version / 100,
				 state->language_version % 100);
	      break;
	   default:
	      _mesa_glsl_error(& (yylsp[(2) - (3)]), state, "Shading language version"
			       "%u is not supported\n", (yyvsp[(2) - (3)].n));
	      break;
	   }
	;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 253 "glsl_parser.ypp"
    {
	   if (state->language_version < 120) {
	      _mesa_glsl_warning(& (yylsp[(1) - (2)]), state,
				 "pragma `invariant(all)' not supported in %s",
				 state->version_string);
	   } else {
	      state->all_invariant = true;
	   }
	;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 271 "glsl_parser.ypp"
    {
	   if (!_mesa_glsl_process_extension((yyvsp[(2) - (5)].identifier), & (yylsp[(2) - (5)]), (yyvsp[(4) - (5)].identifier), & (yylsp[(4) - (5)]), state)) {
	      YYERROR;
	   }
	;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 280 "glsl_parser.ypp"
    {
	   /* FINISHME: The NULL test is only required because 'precision'
	    * FINISHME: statements are not yet supported.
	    */
	   if ((yyvsp[(1) - (1)].node) != NULL)
	      state->translation_unit.push_tail(& (yyvsp[(1) - (1)].node)->link);
	;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 288 "glsl_parser.ypp"
    {
	   /* FINISHME: The NULL test is only required because 'precision'
	    * FINISHME: statements are not yet supported.
	    */
	   if ((yyvsp[(2) - (2)].node) != NULL)
	      state->translation_unit.push_tail(& (yyvsp[(2) - (2)].node)->link);
	;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 303 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_identifier, NULL, NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	   (yyval.expression)->primary_expression.identifier = (yyvsp[(1) - (1)].identifier);
	;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 310 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_int_constant, NULL, NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	   (yyval.expression)->primary_expression.int_constant = (yyvsp[(1) - (1)].n);
	;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 317 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_uint_constant, NULL, NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	   (yyval.expression)->primary_expression.uint_constant = (yyvsp[(1) - (1)].n);
	;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 324 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_float_constant, NULL, NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	   (yyval.expression)->primary_expression.float_constant = (yyvsp[(1) - (1)].real);
	;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 331 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_bool_constant, NULL, NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	   (yyval.expression)->primary_expression.bool_constant = (yyvsp[(1) - (1)].n);
	;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 338 "glsl_parser.ypp"
    {
	   (yyval.expression) = (yyvsp[(2) - (3)].expression);
	;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 346 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_array_index, (yyvsp[(1) - (4)].expression), (yyvsp[(3) - (4)].expression), NULL);
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 352 "glsl_parser.ypp"
    {
	   (yyval.expression) = (yyvsp[(1) - (1)].expression);
	;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 356 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_field_selection, (yyvsp[(1) - (3)].expression), NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	   (yyval.expression)->primary_expression.identifier = (yyvsp[(3) - (3)].identifier);
	;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 363 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_post_inc, (yyvsp[(1) - (2)].expression), NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 369 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_post_dec, (yyvsp[(1) - (2)].expression), NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 387 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_field_selection, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), NULL);
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 406 "glsl_parser.ypp"
    {
	   (yyval.expression) = (yyvsp[(1) - (2)].expression);
	   (yyval.expression)->set_location(yylloc);
	   (yyval.expression)->expressions.push_tail(& (yyvsp[(2) - (2)].expression)->link);
	;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 412 "glsl_parser.ypp"
    {
	   (yyval.expression) = (yyvsp[(1) - (3)].expression);
	   (yyval.expression)->set_location(yylloc);
	   (yyval.expression)->expressions.push_tail(& (yyvsp[(3) - (3)].expression)->link);
	;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 428 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_function_expression((yyvsp[(1) - (1)].type_specifier));
	   (yyval.expression)->set_location(yylloc);
   	;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 434 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   ast_expression *callee = new(ctx) ast_expression((yyvsp[(1) - (1)].identifier));
	   (yyval.expression) = new(ctx) ast_function_expression(callee);
	   (yyval.expression)->set_location(yylloc);
   	;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 441 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   ast_expression *callee = new(ctx) ast_expression((yyvsp[(1) - (1)].identifier));
	   (yyval.expression) = new(ctx) ast_function_expression(callee);
	   (yyval.expression)->set_location(yylloc);
   	;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 453 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_pre_inc, (yyvsp[(2) - (2)].expression), NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 459 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_pre_dec, (yyvsp[(2) - (2)].expression), NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 465 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].expression), NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 474 "glsl_parser.ypp"
    { (yyval.n) = ast_plus; ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 475 "glsl_parser.ypp"
    { (yyval.n) = ast_neg; ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 476 "glsl_parser.ypp"
    { (yyval.n) = ast_logic_not; ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 477 "glsl_parser.ypp"
    { (yyval.n) = ast_bit_not; ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 483 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_mul, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 489 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_div, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 495 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_mod, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 505 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_add, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 511 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_sub, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 521 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_lshift, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 527 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_rshift, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 537 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_less, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 543 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_greater, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 549 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_lequal, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 555 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_gequal, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 565 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_equal, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 571 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_nequal, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 581 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_bit_or, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 591 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_bit_xor, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 601 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_bit_or, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 611 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_logic_and, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 621 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_logic_xor, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 631 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_logic_or, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 641 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_conditional, (yyvsp[(1) - (5)].expression), (yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].expression));
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 651 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression((yyvsp[(2) - (3)].n), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), NULL);
	   (yyval.expression)->set_location(yylloc);
	;}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 659 "glsl_parser.ypp"
    { (yyval.n) = ast_assign; ;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 660 "glsl_parser.ypp"
    { (yyval.n) = ast_mul_assign; ;}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 661 "glsl_parser.ypp"
    { (yyval.n) = ast_div_assign; ;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 662 "glsl_parser.ypp"
    { (yyval.n) = ast_mod_assign; ;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 663 "glsl_parser.ypp"
    { (yyval.n) = ast_add_assign; ;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 664 "glsl_parser.ypp"
    { (yyval.n) = ast_sub_assign; ;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 665 "glsl_parser.ypp"
    { (yyval.n) = ast_ls_assign; ;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 666 "glsl_parser.ypp"
    { (yyval.n) = ast_rs_assign; ;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 667 "glsl_parser.ypp"
    { (yyval.n) = ast_and_assign; ;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 668 "glsl_parser.ypp"
    { (yyval.n) = ast_xor_assign; ;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 669 "glsl_parser.ypp"
    { (yyval.n) = ast_or_assign; ;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 674 "glsl_parser.ypp"
    {
	   (yyval.expression) = (yyvsp[(1) - (1)].expression);
	;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 678 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   if ((yyvsp[(1) - (3)].expression)->oper != ast_sequence) {
	      (yyval.expression) = new(ctx) ast_expression(ast_sequence, NULL, NULL, NULL);
	      (yyval.expression)->set_location(yylloc);
	      (yyval.expression)->expressions.push_tail(& (yyvsp[(1) - (3)].expression)->link);
	   } else {
	      (yyval.expression) = (yyvsp[(1) - (3)].expression);
	   }

	   (yyval.expression)->expressions.push_tail(& (yyvsp[(3) - (3)].expression)->link);
	;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 698 "glsl_parser.ypp"
    {
	   (yyval.node) = (yyvsp[(1) - (2)].function);
	;}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 702 "glsl_parser.ypp"
    {
	   (yyval.node) = (yyvsp[(1) - (2)].declarator_list);
	;}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 706 "glsl_parser.ypp"
    {
	   if (((yyvsp[(3) - (4)].type_specifier)->type_specifier != ast_float)
	       && ((yyvsp[(3) - (4)].type_specifier)->type_specifier != ast_int)) {
	      _mesa_glsl_error(& (yylsp[(3) - (4)]), state, "global precision qualifier can "
			       "only be applied to `int' or `float'\n");
	      YYERROR;
	   }

	   (yyval.node) = NULL; /* FINISHME */
	;}
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 729 "glsl_parser.ypp"
    {
	   (yyval.function) = (yyvsp[(1) - (2)].function);
	   (yyval.function)->parameters.push_tail(& (yyvsp[(2) - (2)].parameter_declarator)->link);
	;}
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 734 "glsl_parser.ypp"
    {
	   (yyval.function) = (yyvsp[(1) - (3)].function);
	   (yyval.function)->parameters.push_tail(& (yyvsp[(3) - (3)].parameter_declarator)->link);
	;}
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 742 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.function) = new(ctx) ast_function();
	   (yyval.function)->set_location(yylloc);
	   (yyval.function)->return_type = (yyvsp[(1) - (3)].fully_specified_type);
	   (yyval.function)->identifier = (yyvsp[(2) - (3)].identifier);
	;}
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 753 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.parameter_declarator) = new(ctx) ast_parameter_declarator();
	   (yyval.parameter_declarator)->set_location(yylloc);
	   (yyval.parameter_declarator)->type = new(ctx) ast_fully_specified_type();
	   (yyval.parameter_declarator)->type->set_location(yylloc);
	   (yyval.parameter_declarator)->type->specifier = (yyvsp[(1) - (2)].type_specifier);
	   (yyval.parameter_declarator)->identifier = (yyvsp[(2) - (2)].identifier);
	;}
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 763 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.parameter_declarator) = new(ctx) ast_parameter_declarator();
	   (yyval.parameter_declarator)->set_location(yylloc);
	   (yyval.parameter_declarator)->type = new(ctx) ast_fully_specified_type();
	   (yyval.parameter_declarator)->type->set_location(yylloc);
	   (yyval.parameter_declarator)->type->specifier = (yyvsp[(1) - (5)].type_specifier);
	   (yyval.parameter_declarator)->identifier = (yyvsp[(2) - (5)].identifier);
	   (yyval.parameter_declarator)->is_array = true;
	   (yyval.parameter_declarator)->array_size = (yyvsp[(4) - (5)].expression);
	;}
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 778 "glsl_parser.ypp"
    {
	   (yyvsp[(1) - (3)].type_qualifier).i |= (yyvsp[(2) - (3)].type_qualifier).i;

	   (yyval.parameter_declarator) = (yyvsp[(3) - (3)].parameter_declarator);
	   (yyval.parameter_declarator)->type->qualifier = (yyvsp[(1) - (3)].type_qualifier).q;
	;}
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 785 "glsl_parser.ypp"
    {
	   (yyval.parameter_declarator) = (yyvsp[(2) - (2)].parameter_declarator);
	   (yyval.parameter_declarator)->type->qualifier = (yyvsp[(1) - (2)].type_qualifier).q;
	;}
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 790 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyvsp[(1) - (3)].type_qualifier).i |= (yyvsp[(2) - (3)].type_qualifier).i;

	   (yyval.parameter_declarator) = new(ctx) ast_parameter_declarator();
	   (yyval.parameter_declarator)->set_location(yylloc);
	   (yyval.parameter_declarator)->type = new(ctx) ast_fully_specified_type();
	   (yyval.parameter_declarator)->type->qualifier = (yyvsp[(1) - (3)].type_qualifier).q;
	   (yyval.parameter_declarator)->type->specifier = (yyvsp[(3) - (3)].type_specifier);
	;}
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 801 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.parameter_declarator) = new(ctx) ast_parameter_declarator();
	   (yyval.parameter_declarator)->set_location(yylloc);
	   (yyval.parameter_declarator)->type = new(ctx) ast_fully_specified_type();
	   (yyval.parameter_declarator)->type->qualifier = (yyvsp[(1) - (2)].type_qualifier).q;
	   (yyval.parameter_declarator)->type->specifier = (yyvsp[(2) - (2)].type_specifier);
	;}
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 812 "glsl_parser.ypp"
    { (yyval.type_qualifier).i = 0; ;}
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 813 "glsl_parser.ypp"
    { (yyval.type_qualifier).i = 0; (yyval.type_qualifier).q.in = 1; ;}
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 814 "glsl_parser.ypp"
    { (yyval.type_qualifier).i = 0; (yyval.type_qualifier).q.out = 1; ;}
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 815 "glsl_parser.ypp"
    { (yyval.type_qualifier).i = 0; (yyval.type_qualifier).q.in = 1; (yyval.type_qualifier).q.out = 1; ;}
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 825 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(3) - (3)].identifier), false, NULL, NULL);
	   decl->set_location(yylloc);

	   (yyval.declarator_list) = (yyvsp[(1) - (3)].declarator_list);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	;}
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 834 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(3) - (5)].identifier), true, NULL, NULL);
	   decl->set_location(yylloc);

	   (yyval.declarator_list) = (yyvsp[(1) - (5)].declarator_list);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	;}
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 843 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(3) - (6)].identifier), true, (yyvsp[(5) - (6)].expression), NULL);
	   decl->set_location(yylloc);

	   (yyval.declarator_list) = (yyvsp[(1) - (6)].declarator_list);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	;}
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 852 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(3) - (7)].identifier), true, NULL, (yyvsp[(7) - (7)].expression));
	   decl->set_location(yylloc);

	   (yyval.declarator_list) = (yyvsp[(1) - (7)].declarator_list);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	;}
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 861 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(3) - (8)].identifier), true, (yyvsp[(5) - (8)].expression), (yyvsp[(8) - (8)].expression));
	   decl->set_location(yylloc);

	   (yyval.declarator_list) = (yyvsp[(1) - (8)].declarator_list);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	;}
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 870 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(3) - (5)].identifier), false, NULL, (yyvsp[(5) - (5)].expression));
	   decl->set_location(yylloc);

	   (yyval.declarator_list) = (yyvsp[(1) - (5)].declarator_list);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	;}
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 883 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   if ((yyvsp[(1) - (1)].fully_specified_type)->specifier->type_specifier != ast_struct) {
	      _mesa_glsl_error(& (yylsp[(1) - (1)]), state, "empty declaration list\n");
	      YYERROR;
	   } else {
	      (yyval.declarator_list) = new(ctx) ast_declarator_list((yyvsp[(1) - (1)].fully_specified_type));
	      (yyval.declarator_list)->set_location(yylloc);
	   }
	;}
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 894 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(2) - (2)].identifier), false, NULL, NULL);

	   (yyval.declarator_list) = new(ctx) ast_declarator_list((yyvsp[(1) - (2)].fully_specified_type));
	   (yyval.declarator_list)->set_location(yylloc);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	;}
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 903 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(2) - (4)].identifier), true, NULL, NULL);

	   (yyval.declarator_list) = new(ctx) ast_declarator_list((yyvsp[(1) - (4)].fully_specified_type));
	   (yyval.declarator_list)->set_location(yylloc);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	;}
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 912 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(2) - (5)].identifier), true, (yyvsp[(4) - (5)].expression), NULL);

	   (yyval.declarator_list) = new(ctx) ast_declarator_list((yyvsp[(1) - (5)].fully_specified_type));
	   (yyval.declarator_list)->set_location(yylloc);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	;}
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 921 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(2) - (6)].identifier), true, NULL, (yyvsp[(6) - (6)].expression));

	   (yyval.declarator_list) = new(ctx) ast_declarator_list((yyvsp[(1) - (6)].fully_specified_type));
	   (yyval.declarator_list)->set_location(yylloc);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	;}
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 930 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(2) - (7)].identifier), true, (yyvsp[(4) - (7)].expression), (yyvsp[(7) - (7)].expression));

	   (yyval.declarator_list) = new(ctx) ast_declarator_list((yyvsp[(1) - (7)].fully_specified_type));
	   (yyval.declarator_list)->set_location(yylloc);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	;}
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 939 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(2) - (4)].identifier), false, NULL, (yyvsp[(4) - (4)].expression));

	   (yyval.declarator_list) = new(ctx) ast_declarator_list((yyvsp[(1) - (4)].fully_specified_type));
	   (yyval.declarator_list)->set_location(yylloc);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	;}
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 948 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(2) - (2)].identifier), false, NULL, NULL);

	   (yyval.declarator_list) = new(ctx) ast_declarator_list(NULL);
	   (yyval.declarator_list)->set_location(yylloc);
	   (yyval.declarator_list)->invariant = true;

	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	;}
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 962 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.fully_specified_type) = new(ctx) ast_fully_specified_type();
	   (yyval.fully_specified_type)->set_location(yylloc);
	   (yyval.fully_specified_type)->specifier = (yyvsp[(1) - (1)].type_specifier);
	;}
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 969 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.fully_specified_type) = new(ctx) ast_fully_specified_type();
	   (yyval.fully_specified_type)->set_location(yylloc);
	   (yyval.fully_specified_type)->qualifier = (yyvsp[(1) - (2)].type_qualifier).q;
	   (yyval.fully_specified_type)->specifier = (yyvsp[(2) - (2)].type_specifier);
	;}
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 979 "glsl_parser.ypp"
    { (yyval.type_qualifier).i = 0; ;}
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 985 "glsl_parser.ypp"
    {
	  (yyval.type_qualifier) = (yyvsp[(3) - (4)].type_qualifier);
	;}
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 993 "glsl_parser.ypp"
    {
	   (yyval.type_qualifier).i = (yyvsp[(1) - (3)].type_qualifier).i | (yyvsp[(3) - (3)].type_qualifier).i;
	;}
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 1000 "glsl_parser.ypp"
    {
	   (yyval.type_qualifier).i = 0;

	   if (state->ARB_fragment_coord_conventions_enable) {
	      bool got_one = false;

	      if (strcmp((yyvsp[(1) - (1)].identifier), "origin_upper_left") == 0) {
		 got_one = true;
		 (yyval.type_qualifier).q.origin_upper_left = 1;
	      } else if (strcmp((yyvsp[(1) - (1)].identifier), "pixel_center_integer") == 0) {
		 got_one = true;
		 (yyval.type_qualifier).q.pixel_center_integer = 1;
	      }

	      if (state->ARB_fragment_coord_conventions_warn && got_one) {
		 _mesa_glsl_warning(& (yylsp[(1) - (1)]), state,
				    "GL_ARB_fragment_coord_conventions layout "
				    "identifier `%s' used\n", (yyvsp[(1) - (1)].identifier));
	      }
	   }

	   /* If the identifier didn't match any known layout identifiers,
	    * emit an error.
	    */
	   if ((yyval.type_qualifier).i == 0) {
	      _mesa_glsl_error(& (yylsp[(1) - (1)]), state, "unrecognized layout identifier "
			       "`%s'\n", (yyvsp[(1) - (1)].identifier));
	      YYERROR;
	   }
	;}
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 1033 "glsl_parser.ypp"
    { (yyval.type_qualifier).i = 0; (yyval.type_qualifier).q.smooth = 1; ;}
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 1034 "glsl_parser.ypp"
    { (yyval.type_qualifier).i = 0; (yyval.type_qualifier).q.flat = 1; ;}
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 1035 "glsl_parser.ypp"
    { (yyval.type_qualifier).i = 0; (yyval.type_qualifier).q.noperspective = 1; ;}
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 1039 "glsl_parser.ypp"
    { (yyval.type_qualifier).i = 0; (yyval.type_qualifier).q.constant = 1; ;}
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 1045 "glsl_parser.ypp"
    {
	   (yyval.type_qualifier).i = (yyvsp[(1) - (2)].type_qualifier).i | (yyvsp[(2) - (2)].type_qualifier).i;
	;}
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 1049 "glsl_parser.ypp"
    {
	   (yyval.type_qualifier) = (yyvsp[(2) - (2)].type_qualifier);
	   (yyval.type_qualifier).q.invariant = 1;
	;}
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 1056 "glsl_parser.ypp"
    { (yyval.type_qualifier).i = 0; (yyval.type_qualifier).q.constant = 1; ;}
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 1057 "glsl_parser.ypp"
    { (yyval.type_qualifier).i = 0; (yyval.type_qualifier).q.attribute = 1; ;}
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 1058 "glsl_parser.ypp"
    { (yyval.type_qualifier).i = (yyvsp[(1) - (2)].type_qualifier).i; (yyval.type_qualifier).q.varying = 1; ;}
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 1059 "glsl_parser.ypp"
    { (yyval.type_qualifier).i = 0; (yyval.type_qualifier).q.centroid = 1; (yyval.type_qualifier).q.varying = 1; ;}
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 1060 "glsl_parser.ypp"
    { (yyval.type_qualifier).i = 0; (yyval.type_qualifier).q.in = 1; ;}
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 1061 "glsl_parser.ypp"
    { (yyval.type_qualifier).i = 0; (yyval.type_qualifier).q.out = 1; ;}
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 1062 "glsl_parser.ypp"
    { (yyval.type_qualifier).i = 0; (yyval.type_qualifier).q.centroid = 1; (yyval.type_qualifier).q.in = 1; ;}
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 1063 "glsl_parser.ypp"
    { (yyval.type_qualifier).i = 0; (yyval.type_qualifier).q.centroid = 1; (yyval.type_qualifier).q.out = 1; ;}
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 1064 "glsl_parser.ypp"
    { (yyval.type_qualifier).i = 0; (yyval.type_qualifier).q.uniform = 1; ;}
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 1070 "glsl_parser.ypp"
    {
	   (yyval.type_specifier) = (yyvsp[(2) - (2)].type_specifier);
	   (yyval.type_specifier)->precision = (yyvsp[(1) - (2)].n);
	;}
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 1079 "glsl_parser.ypp"
    {
	   (yyval.type_specifier) = (yyvsp[(1) - (3)].type_specifier);
	   (yyval.type_specifier)->is_array = true;
	   (yyval.type_specifier)->array_size = NULL;
	;}
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 1085 "glsl_parser.ypp"
    {
	   (yyval.type_specifier) = (yyvsp[(1) - (4)].type_specifier);
	   (yyval.type_specifier)->is_array = true;
	   (yyval.type_specifier)->array_size = (yyvsp[(3) - (4)].expression);
	;}
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 1094 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.type_specifier) = new(ctx) ast_type_specifier((yyvsp[(1) - (1)].n));
	   (yyval.type_specifier)->set_location(yylloc);
	;}
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 1100 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.type_specifier) = new(ctx) ast_type_specifier((yyvsp[(1) - (1)].struct_specifier));
	   (yyval.type_specifier)->set_location(yylloc);
	;}
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 1106 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.type_specifier) = new(ctx) ast_type_specifier((yyvsp[(1) - (1)].identifier));
	   (yyval.type_specifier)->set_location(yylloc);
	;}
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 1114 "glsl_parser.ypp"
    { (yyval.n) = ast_void; ;}
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 1115 "glsl_parser.ypp"
    { (yyval.n) = ast_float; ;}
    break;

  case 168:

/* Line 1464 of yacc.c  */
#line 1116 "glsl_parser.ypp"
    { (yyval.n) = ast_int; ;}
    break;

  case 169:

/* Line 1464 of yacc.c  */
#line 1117 "glsl_parser.ypp"
    { (yyval.n) = ast_uint; ;}
    break;

  case 170:

/* Line 1464 of yacc.c  */
#line 1118 "glsl_parser.ypp"
    { (yyval.n) = ast_bool; ;}
    break;

  case 171:

/* Line 1464 of yacc.c  */
#line 1119 "glsl_parser.ypp"
    { (yyval.n) = ast_vec2; ;}
    break;

  case 172:

/* Line 1464 of yacc.c  */
#line 1120 "glsl_parser.ypp"
    { (yyval.n) = ast_vec3; ;}
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 1121 "glsl_parser.ypp"
    { (yyval.n) = ast_vec4; ;}
    break;

  case 174:

/* Line 1464 of yacc.c  */
#line 1122 "glsl_parser.ypp"
    { (yyval.n) = ast_bvec2; ;}
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 1123 "glsl_parser.ypp"
    { (yyval.n) = ast_bvec3; ;}
    break;

  case 176:

/* Line 1464 of yacc.c  */
#line 1124 "glsl_parser.ypp"
    { (yyval.n) = ast_bvec4; ;}
    break;

  case 177:

/* Line 1464 of yacc.c  */
#line 1125 "glsl_parser.ypp"
    { (yyval.n) = ast_ivec2; ;}
    break;

  case 178:

/* Line 1464 of yacc.c  */
#line 1126 "glsl_parser.ypp"
    { (yyval.n) = ast_ivec3; ;}
    break;

  case 179:

/* Line 1464 of yacc.c  */
#line 1127 "glsl_parser.ypp"
    { (yyval.n) = ast_ivec4; ;}
    break;

  case 180:

/* Line 1464 of yacc.c  */
#line 1128 "glsl_parser.ypp"
    { (yyval.n) = ast_uvec2; ;}
    break;

  case 181:

/* Line 1464 of yacc.c  */
#line 1129 "glsl_parser.ypp"
    { (yyval.n) = ast_uvec3; ;}
    break;

  case 182:

/* Line 1464 of yacc.c  */
#line 1130 "glsl_parser.ypp"
    { (yyval.n) = ast_uvec4; ;}
    break;

  case 183:

/* Line 1464 of yacc.c  */
#line 1131 "glsl_parser.ypp"
    { (yyval.n) = ast_mat2; ;}
    break;

  case 184:

/* Line 1464 of yacc.c  */
#line 1132 "glsl_parser.ypp"
    { (yyval.n) = ast_mat2x3; ;}
    break;

  case 185:

/* Line 1464 of yacc.c  */
#line 1133 "glsl_parser.ypp"
    { (yyval.n) = ast_mat2x4; ;}
    break;

  case 186:

/* Line 1464 of yacc.c  */
#line 1134 "glsl_parser.ypp"
    { (yyval.n) = ast_mat3x2; ;}
    break;

  case 187:

/* Line 1464 of yacc.c  */
#line 1135 "glsl_parser.ypp"
    { (yyval.n) = ast_mat3; ;}
    break;

  case 188:

/* Line 1464 of yacc.c  */
#line 1136 "glsl_parser.ypp"
    { (yyval.n) = ast_mat3x4; ;}
    break;

  case 189:

/* Line 1464 of yacc.c  */
#line 1137 "glsl_parser.ypp"
    { (yyval.n) = ast_mat4x2; ;}
    break;

  case 190:

/* Line 1464 of yacc.c  */
#line 1138 "glsl_parser.ypp"
    { (yyval.n) = ast_mat4x3; ;}
    break;

  case 191:

/* Line 1464 of yacc.c  */
#line 1139 "glsl_parser.ypp"
    { (yyval.n) = ast_mat4; ;}
    break;

  case 192:

/* Line 1464 of yacc.c  */
#line 1140 "glsl_parser.ypp"
    { (yyval.n) = ast_sampler1d; ;}
    break;

  case 193:

/* Line 1464 of yacc.c  */
#line 1141 "glsl_parser.ypp"
    { (yyval.n) = ast_sampler2d; ;}
    break;

  case 194:

/* Line 1464 of yacc.c  */
#line 1142 "glsl_parser.ypp"
    { (yyval.n) = ast_sampler2drect; ;}
    break;

  case 195:

/* Line 1464 of yacc.c  */
#line 1143 "glsl_parser.ypp"
    { (yyval.n) = ast_sampler3d; ;}
    break;

  case 196:

/* Line 1464 of yacc.c  */
#line 1144 "glsl_parser.ypp"
    { (yyval.n) = ast_samplercube; ;}
    break;

  case 197:

/* Line 1464 of yacc.c  */
#line 1145 "glsl_parser.ypp"
    { (yyval.n) = ast_sampler1dshadow; ;}
    break;

  case 198:

/* Line 1464 of yacc.c  */
#line 1146 "glsl_parser.ypp"
    { (yyval.n) = ast_sampler2dshadow; ;}
    break;

  case 199:

/* Line 1464 of yacc.c  */
#line 1147 "glsl_parser.ypp"
    { (yyval.n) = ast_sampler2drectshadow; ;}
    break;

  case 200:

/* Line 1464 of yacc.c  */
#line 1148 "glsl_parser.ypp"
    { (yyval.n) = ast_samplercubeshadow; ;}
    break;

  case 201:

/* Line 1464 of yacc.c  */
#line 1149 "glsl_parser.ypp"
    { (yyval.n) = ast_sampler1darray; ;}
    break;

  case 202:

/* Line 1464 of yacc.c  */
#line 1150 "glsl_parser.ypp"
    { (yyval.n) = ast_sampler2darray; ;}
    break;

  case 203:

/* Line 1464 of yacc.c  */
#line 1151 "glsl_parser.ypp"
    { (yyval.n) = ast_sampler1darrayshadow; ;}
    break;

  case 204:

/* Line 1464 of yacc.c  */
#line 1152 "glsl_parser.ypp"
    { (yyval.n) = ast_sampler2darrayshadow; ;}
    break;

  case 205:

/* Line 1464 of yacc.c  */
#line 1153 "glsl_parser.ypp"
    { (yyval.n) = ast_isampler1d; ;}
    break;

  case 206:

/* Line 1464 of yacc.c  */
#line 1154 "glsl_parser.ypp"
    { (yyval.n) = ast_isampler2d; ;}
    break;

  case 207:

/* Line 1464 of yacc.c  */
#line 1155 "glsl_parser.ypp"
    { (yyval.n) = ast_isampler3d; ;}
    break;

  case 208:

/* Line 1464 of yacc.c  */
#line 1156 "glsl_parser.ypp"
    { (yyval.n) = ast_isamplercube; ;}
    break;

  case 209:

/* Line 1464 of yacc.c  */
#line 1157 "glsl_parser.ypp"
    { (yyval.n) = ast_isampler1darray; ;}
    break;

  case 210:

/* Line 1464 of yacc.c  */
#line 1158 "glsl_parser.ypp"
    { (yyval.n) = ast_isampler2darray; ;}
    break;

  case 211:

/* Line 1464 of yacc.c  */
#line 1159 "glsl_parser.ypp"
    { (yyval.n) = ast_usampler1d; ;}
    break;

  case 212:

/* Line 1464 of yacc.c  */
#line 1160 "glsl_parser.ypp"
    { (yyval.n) = ast_usampler2d; ;}
    break;

  case 213:

/* Line 1464 of yacc.c  */
#line 1161 "glsl_parser.ypp"
    { (yyval.n) = ast_usampler3d; ;}
    break;

  case 214:

/* Line 1464 of yacc.c  */
#line 1162 "glsl_parser.ypp"
    { (yyval.n) = ast_usamplercube; ;}
    break;

  case 215:

/* Line 1464 of yacc.c  */
#line 1163 "glsl_parser.ypp"
    { (yyval.n) = ast_usampler1darray; ;}
    break;

  case 216:

/* Line 1464 of yacc.c  */
#line 1164 "glsl_parser.ypp"
    { (yyval.n) = ast_usampler2darray; ;}
    break;

  case 217:

/* Line 1464 of yacc.c  */
#line 1168 "glsl_parser.ypp"
    {
		     if (!state->es_shader && state->language_version < 130)
			_mesa_glsl_error(& (yylsp[(1) - (1)]), state,
				         "precision qualifier forbidden "
					 "in %s (1.30 or later "
					 "required)\n",
					 state->version_string);

		     (yyval.n) = ast_precision_high;
		  ;}
    break;

  case 218:

/* Line 1464 of yacc.c  */
#line 1178 "glsl_parser.ypp"
    {
		     if (!state->es_shader && state->language_version < 130)
			_mesa_glsl_error(& (yylsp[(1) - (1)]), state,
					 "precision qualifier forbidden "
					 "in %s (1.30 or later "
					 "required)\n",
					 state->version_string);

		     (yyval.n) = ast_precision_medium;
		  ;}
    break;

  case 219:

/* Line 1464 of yacc.c  */
#line 1188 "glsl_parser.ypp"
    {
		     if (!state->es_shader && state->language_version < 130)
			_mesa_glsl_error(& (yylsp[(1) - (1)]), state,
					 "precision qualifier forbidden "
					 "in %s (1.30 or later "
					 "required)\n",
					 state->version_string);

		     (yyval.n) = ast_precision_low;
		  ;}
    break;

  case 220:

/* Line 1464 of yacc.c  */
#line 1202 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.struct_specifier) = new(ctx) ast_struct_specifier((yyvsp[(2) - (5)].identifier), (yyvsp[(4) - (5)].node));
	   (yyval.struct_specifier)->set_location(yylloc);
	;}
    break;

  case 221:

/* Line 1464 of yacc.c  */
#line 1208 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.struct_specifier) = new(ctx) ast_struct_specifier(NULL, (yyvsp[(3) - (4)].node));
	   (yyval.struct_specifier)->set_location(yylloc);
	;}
    break;

  case 222:

/* Line 1464 of yacc.c  */
#line 1217 "glsl_parser.ypp"
    {
	   (yyval.node) = (ast_node *) (yyvsp[(1) - (1)].declarator_list);
	   (yyvsp[(1) - (1)].declarator_list)->link.self_link();
	;}
    break;

  case 223:

/* Line 1464 of yacc.c  */
#line 1222 "glsl_parser.ypp"
    {
	   (yyval.node) = (ast_node *) (yyvsp[(1) - (2)].node);
	   (yyval.node)->link.insert_before(& (yyvsp[(2) - (2)].declarator_list)->link);
	;}
    break;

  case 224:

/* Line 1464 of yacc.c  */
#line 1230 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   ast_fully_specified_type *type = new(ctx) ast_fully_specified_type();
	   type->set_location(yylloc);

	   type->specifier = (yyvsp[(1) - (3)].type_specifier);
	   (yyval.declarator_list) = new(ctx) ast_declarator_list(type);
	   (yyval.declarator_list)->set_location(yylloc);

	   (yyval.declarator_list)->declarations.push_degenerate_list_at_head(& (yyvsp[(2) - (3)].declaration)->link);
	;}
    break;

  case 225:

/* Line 1464 of yacc.c  */
#line 1245 "glsl_parser.ypp"
    {
	   (yyval.declaration) = (yyvsp[(1) - (1)].declaration);
	   (yyvsp[(1) - (1)].declaration)->link.self_link();
	;}
    break;

  case 226:

/* Line 1464 of yacc.c  */
#line 1250 "glsl_parser.ypp"
    {
	   (yyval.declaration) = (yyvsp[(1) - (3)].declaration);
	   (yyval.declaration)->link.insert_before(& (yyvsp[(3) - (3)].declaration)->link);
	;}
    break;

  case 227:

/* Line 1464 of yacc.c  */
#line 1258 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.declaration) = new(ctx) ast_declaration((yyvsp[(1) - (1)].identifier), false, NULL, NULL);
	   (yyval.declaration)->set_location(yylloc);
	;}
    break;

  case 228:

/* Line 1464 of yacc.c  */
#line 1264 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.declaration) = new(ctx) ast_declaration((yyvsp[(1) - (4)].identifier), true, (yyvsp[(3) - (4)].expression), NULL);
	   (yyval.declaration)->set_location(yylloc);
	;}
    break;

  case 231:

/* Line 1464 of yacc.c  */
#line 1282 "glsl_parser.ypp"
    { (yyval.node) = (ast_node *) (yyvsp[(1) - (1)].compound_statement); ;}
    break;

  case 236:

/* Line 1464 of yacc.c  */
#line 1290 "glsl_parser.ypp"
    { (yyval.node) = NULL; ;}
    break;

  case 237:

/* Line 1464 of yacc.c  */
#line 1291 "glsl_parser.ypp"
    { (yyval.node) = NULL; ;}
    break;

  case 240:

/* Line 1464 of yacc.c  */
#line 1298 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.compound_statement) = new(ctx) ast_compound_statement(true, NULL);
	   (yyval.compound_statement)->set_location(yylloc);
	;}
    break;

  case 241:

/* Line 1464 of yacc.c  */
#line 1304 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.compound_statement) = new(ctx) ast_compound_statement(true, (yyvsp[(2) - (3)].node));
	   (yyval.compound_statement)->set_location(yylloc);
	;}
    break;

  case 242:

/* Line 1464 of yacc.c  */
#line 1312 "glsl_parser.ypp"
    { (yyval.node) = (ast_node *) (yyvsp[(1) - (1)].compound_statement); ;}
    break;

  case 244:

/* Line 1464 of yacc.c  */
#line 1318 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.compound_statement) = new(ctx) ast_compound_statement(false, NULL);
	   (yyval.compound_statement)->set_location(yylloc);
	;}
    break;

  case 245:

/* Line 1464 of yacc.c  */
#line 1324 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.compound_statement) = new(ctx) ast_compound_statement(false, (yyvsp[(2) - (3)].node));
	   (yyval.compound_statement)->set_location(yylloc);
	;}
    break;

  case 246:

/* Line 1464 of yacc.c  */
#line 1333 "glsl_parser.ypp"
    {
	   if ((yyvsp[(1) - (1)].node) == NULL) {
	      _mesa_glsl_error(& (yylsp[(1) - (1)]), state, "<nil> statement\n");
	      assert((yyvsp[(1) - (1)].node) != NULL);
	   }

	   (yyval.node) = (yyvsp[(1) - (1)].node);
	   (yyval.node)->link.self_link();
	;}
    break;

  case 247:

/* Line 1464 of yacc.c  */
#line 1343 "glsl_parser.ypp"
    {
	   if ((yyvsp[(2) - (2)].node) == NULL) {
	      _mesa_glsl_error(& (yylsp[(2) - (2)]), state, "<nil> statement\n");
	      assert((yyvsp[(2) - (2)].node) != NULL);
	   }
	   (yyval.node) = (yyvsp[(1) - (2)].node);
	   (yyval.node)->link.insert_before(& (yyvsp[(2) - (2)].node)->link);
	;}
    break;

  case 248:

/* Line 1464 of yacc.c  */
#line 1355 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.node) = new(ctx) ast_expression_statement(NULL);
	   (yyval.node)->set_location(yylloc);
	;}
    break;

  case 249:

/* Line 1464 of yacc.c  */
#line 1361 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.node) = new(ctx) ast_expression_statement((yyvsp[(1) - (2)].expression));
	   (yyval.node)->set_location(yylloc);
	;}
    break;

  case 250:

/* Line 1464 of yacc.c  */
#line 1370 "glsl_parser.ypp"
    {
	   (yyval.node) = new(state) ast_selection_statement((yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].selection_rest_statement).then_statement,
						   (yyvsp[(5) - (5)].selection_rest_statement).else_statement);
	   (yyval.node)->set_location(yylloc);
	;}
    break;

  case 251:

/* Line 1464 of yacc.c  */
#line 1379 "glsl_parser.ypp"
    {
	   (yyval.selection_rest_statement).then_statement = (yyvsp[(1) - (3)].node);
	   (yyval.selection_rest_statement).else_statement = (yyvsp[(3) - (3)].node);
	;}
    break;

  case 252:

/* Line 1464 of yacc.c  */
#line 1384 "glsl_parser.ypp"
    {
	   (yyval.selection_rest_statement).then_statement = (yyvsp[(1) - (1)].node);
	   (yyval.selection_rest_statement).else_statement = NULL;
	;}
    break;

  case 253:

/* Line 1464 of yacc.c  */
#line 1392 "glsl_parser.ypp"
    {
	   (yyval.node) = (ast_node *) (yyvsp[(1) - (1)].expression);
	;}
    break;

  case 254:

/* Line 1464 of yacc.c  */
#line 1396 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(2) - (4)].identifier), false, NULL, (yyvsp[(4) - (4)].expression));
	   ast_declarator_list *declarator = new(ctx) ast_declarator_list((yyvsp[(1) - (4)].fully_specified_type));
	   decl->set_location(yylloc);
	   declarator->set_location(yylloc);

	   declarator->declarations.push_tail(&decl->link);
	   (yyval.node) = declarator;
	;}
    break;

  case 258:

/* Line 1464 of yacc.c  */
#line 1419 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.node) = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_while,
	   					    NULL, (yyvsp[(3) - (5)].node), NULL, (yyvsp[(5) - (5)].node));
	   (yyval.node)->set_location(yylloc);
	;}
    break;

  case 259:

/* Line 1464 of yacc.c  */
#line 1426 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.node) = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_do_while,
						    NULL, (yyvsp[(5) - (7)].expression), NULL, (yyvsp[(2) - (7)].node));
	   (yyval.node)->set_location(yylloc);
	;}
    break;

  case 260:

/* Line 1464 of yacc.c  */
#line 1433 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.node) = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_for,
						    (yyvsp[(3) - (6)].node), (yyvsp[(4) - (6)].for_rest_statement).cond, (yyvsp[(4) - (6)].for_rest_statement).rest, (yyvsp[(6) - (6)].node));
	   (yyval.node)->set_location(yylloc);
	;}
    break;

  case 264:

/* Line 1464 of yacc.c  */
#line 1449 "glsl_parser.ypp"
    {
	   (yyval.node) = NULL;
	;}
    break;

  case 265:

/* Line 1464 of yacc.c  */
#line 1456 "glsl_parser.ypp"
    {
	   (yyval.for_rest_statement).cond = (yyvsp[(1) - (2)].node);
	   (yyval.for_rest_statement).rest = NULL;
	;}
    break;

  case 266:

/* Line 1464 of yacc.c  */
#line 1461 "glsl_parser.ypp"
    {
	   (yyval.for_rest_statement).cond = (yyvsp[(1) - (3)].node);
	   (yyval.for_rest_statement).rest = (yyvsp[(3) - (3)].expression);
	;}
    break;

  case 267:

/* Line 1464 of yacc.c  */
#line 1470 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.node) = new(ctx) ast_jump_statement(ast_jump_statement::ast_continue, NULL);
	   (yyval.node)->set_location(yylloc);
	;}
    break;

  case 268:

/* Line 1464 of yacc.c  */
#line 1476 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.node) = new(ctx) ast_jump_statement(ast_jump_statement::ast_break, NULL);
	   (yyval.node)->set_location(yylloc);
	;}
    break;

  case 269:

/* Line 1464 of yacc.c  */
#line 1482 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.node) = new(ctx) ast_jump_statement(ast_jump_statement::ast_return, NULL);
	   (yyval.node)->set_location(yylloc);
	;}
    break;

  case 270:

/* Line 1464 of yacc.c  */
#line 1488 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.node) = new(ctx) ast_jump_statement(ast_jump_statement::ast_return, (yyvsp[(2) - (3)].expression));
	   (yyval.node)->set_location(yylloc);
	;}
    break;

  case 271:

/* Line 1464 of yacc.c  */
#line 1494 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.node) = new(ctx) ast_jump_statement(ast_jump_statement::ast_discard, NULL);
	   (yyval.node)->set_location(yylloc);
	;}
    break;

  case 272:

/* Line 1464 of yacc.c  */
#line 1502 "glsl_parser.ypp"
    { (yyval.node) = (yyvsp[(1) - (1)].function_definition); ;}
    break;

  case 273:

/* Line 1464 of yacc.c  */
#line 1503 "glsl_parser.ypp"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 274:

/* Line 1464 of yacc.c  */
#line 1504 "glsl_parser.ypp"
    { (yyval.node) = NULL; ;}
    break;

  case 275:

/* Line 1464 of yacc.c  */
#line 1509 "glsl_parser.ypp"
    {
	   void *ctx = state;
	   (yyval.function_definition) = new(ctx) ast_function_definition();
	   (yyval.function_definition)->set_location(yylloc);
	   (yyval.function_definition)->prototype = (yyvsp[(1) - (2)].function);
	   (yyval.function_definition)->body = (yyvsp[(2) - (2)].compound_statement);
	;}
    break;



/* Line 1464 of yacc.c  */
#line 5021 "glsl_parser.cpp"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, state, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (&yylloc, state, yymsg);
	  }
	else
	  {
	    yyerror (&yylloc, state, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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
		      yytoken, &yylval, &yylloc, state);
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
      if (yyn != YYPACT_NINF)
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
		  yystos[yystate], yyvsp, yylsp, state);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, state, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc, state);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, state);
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



