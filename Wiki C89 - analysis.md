---
tags:
  - dev/language/c
---
# Wiki C89 - analysis

---

## ✅ Variables

- single declaration : `type name` (`int fahr`)
- multiple declaration : `type name1, name2` (`int fahr, cels`)
- all variables must be declared (sometimes implicit)
- during declaration a variable can be initialized

Initialization

- initialization : declaration followed by `= <value>` (`int fahr = 5, cels = 0`)
- automatic uninitialized variables contain undefined data
- external and static uninitialized variables contain zero

> [!example]
>
> ```c
> double ratio; /* initialised with 0 */
> 
> {
> 	/* implicit automatic variables */
> 	/* auto */ float x, y, z;  /* garbage values */
> 	/* auto */ short int counter = 10;
> 	/* auto */ long int width = 800, height = 600;
> 	
> 	/* static variable */
> 	static int number;    /* initialised with 0 */
> 	
> 	/* implicit extern variable */
> 	/* extern double ratio; */
> }
> ```

## Operators

Types

- Arithmetic: `+`, `-`, `*`, `/`, `++`, `--`, `%`
- Comparison: `<`, `>`, `<=`, `>=`, `==`, `!=`
- Bitwise: `&`, `|`, `<<`, `>>`, `^`, `~`
- Boolean: `&&`, `||`, `!` (result can only be `1` or `0`)
- Conditional : `?:` (`COND ? true : false`)
- Cast: `(TYPE)EXPR`
- Compile time : `sizeof`

Details

- modulo op cannot be applied to floats
- direction of truncation for division is (impl-defined)
- sign of the modulo is (impl-defined)
- AND, OR ops stop evaluating as soon as a result can be determined
- Shifting can be arithmetic (preserve sign) or logical (impl-defined)
- arithmetic and bitwise ops can be fused with assignment (`+=`, `-=`...)

Precedence

1. `()` `[]` `->` `.`
2. Unary : `!` `~` `++` `--` `&` `(type)` `sizeof` `+` `-` `*`
3. Binary : `*` `/` `%`
4. Binary : `+` `-`
5. `<<` `>>`
6. `<` `<=` `>` `>=`
7. `==` `!=`
8. `&`
9. `^`
10. `|`
11. `&&`
12. `||`
13. Ternary : `?:`
14. `=` `+=` `-=` `*=` `/=` `%=` `&=` `^=` `|=` `<<=` `>>=`
15. `,`

## ✅ Functions

- declaration (prototype) : `type name(params);`
- definition : `type name(params) { declarations statements }`
- pointer function : `RTYP (*NAME)(PRMTs)`
- pointer function call : `(*NAME)(PRMTs)`

> [!example]
>
> ```c
> /* declaration : no parameters or return type */
> void foo(void);
> 
> /* definition : takes 2 integers, return integer */
> int add(int a, int b)
> {
> 	return a + b;
> }
> 
> typedef void (*Func)(float x, float y);
> Func f_ptr = ...;    /* function pointer variable */
> (*f_ptr)(1.0, 2.0);  /* function pointer call */
> ```

Terminology

- `parameter` : variable named in a function definition
- `argument` : actual value used to call a function (gets coerced to parameter type)

Behaviour

- `return` : exits the function
- function arguments are passed "by value" (copied)
- array arguments always decay to the pointer to the first element in the parameter
- empty parameters declaration requires the keyword `void` in place of the parameters list

## Flow Constructs

Common

- `break` : exit from switch / loop
- the condition is true for any non-zero value

### ✅ Loops

- `while(COND) STMT`
- `do STMT while(EXPR)`
- `for(INIT; COND; STEP) STMT`
	- any of the three parts can be omitted
	- if the condition is omitted, it is always true
- `continue` : stop current iteration and move to the next

> [!example]
>
> ```c
> while(0) { /* ... */ }          /* always false*/
> for(i = 0; i < 10; ++i) ;       /* no body */
> for(i = 0;; ++i) { /* ... */ }; /* repeat forever*/
> do {
> 	if(x == y) continue; /* jump to next iteration */
> 	if(x < y) break;     /* break out of the loop */
> } while(x > y);
> ```

### ✅ Jumps

- `if(EXPR) STMT else STMT`
- `switch(EXPR) { CASEs DEFT }`
	- Default: `default: STMT`
	- Case: `case CEXP: STMT`
	- Fall through
- `goto LABEL`, `LABEL:`

> [!example]
>
> ```c
> here:
> 	if(x % 2) printf("odd\n");
> 	else      printf("even\n");
> 	
> there:
> 	switch(letter)
> 	{
> 		case ';':
> 			printf("semi colon\n");
> 			break;
> 		case 'a': /* falltrough */
> 		case 'A':
> 			printf("AAAAAAAAAA\n");
> 		default:
> 			printf("unknown\n");
> 	}
> 	
> 	goto here;
> 	goto there;
> ```

## Constants / Literals

### Characters

- Character : `'a'`
- String : `"hello, world"`
- Wide string : `L"hello, world"`
- Escape characters : `\a`, `\b`, `\f`, `\n`, `\r`, `\t`, `\v`, `\\`, `\?`, `\'`, `\"`, `\ooo`, `\xhh`

### Numbers

- Integer : `1234`, `0x12bf`, `0123`
- Float : `12.34`, `10e2`
- Number flags: long (`l`, `L`), unsigned (`u`, `U`), floating (`f`, `F`)

### ✅ Enumerations

- declaration : `enum name { CNST1, CNSTn }`
- starts from `0` unless otherwise specified
- subsequent element increment by 1 each time
- enumeration constant (constant integer values)
- value correctness not checked at runtime
- an enumerations are of type `int`

> [!example]
>
> ```c
> /* implicit 0    1    2    3    4    5    6 */
> enum Day { MON, TUE, WED, THU, FRI, SAT, SUN };
> 
> /* explicit 1        2    4        5  */
> enum Pin { A_1 = 1, A_2, B_1 = 4, B_2 };
> ```

## Types

Scalar

- Pointer: `TYPE* NAME`
	- Function
	- Other
- Enumeration
- Numeric
	- Integer : `char`, `int`, `size_t`
	- Real : `float`, `double`
	- real to integer truncates fractional part
	- `double` to `float` -> truncated or rounded (impl-defined)

Composite

- Array: `TYPE NAME[SIZE] = { VAL1, ..., VALN }`
- Structures, unions

Qualifiers

- `volatile`, `typedef`
- `const` : the value cannot be changed (impl-defined)
- Sign (only integers): `unsigned`, `signed` (two's compl.)
- Size : `short` (2-B), `long` (8-B, also with real numbers)
- Scope: `auto`, `register`, `extern`, `static`

### ✅ Typedef

Give a nickname to a type

> [!example]
>
> ```c
> typedef char Username[25];
> Username identifier = "Mike";
> ```

### ✅ Arrays

- declaration : `type name[size]` (`int ndigit[10]`)
- declaring a size allocates the required memory
- Initialisation
	- `= { a, b, c, d, ... }`
	- Automatically computed size

> [!example]
>
> ```c
> /* array declaration */
> int array[];  /* equivalent to `int *array;` */
> float xyz[3]; /* allocate memory for 3 float */
> 
> /* array initialisation */
> char string[] = { 'a', 'b', 'c' }; /* automatically computed length */
> short coefficients[4][4] =         /* nested array initialisation */
> {
> 	{    1,   2,     3,    4 },
> 	{   10,   20,   30,   40 },
> 	{  100,  200,  300,  400 },
> 	{ 1000, 2000, 3000, 4000 }
> }
> ```

> [!warning]
>
> ```c
> enum { A = 0, B, C, D, COUNT }
> 
> /* NOT C89 COMPLIANT */ 
> const char alphabet[COUNT] =
> {
> 	[A] = 'a',
> 	[B] = 'b',
> 	[C] = 'c',
> 	[D] = 'd',
> }
> ```

### ✅ Pointers

- Dereference op: `*`
- Addressing op: `&`
- Generic pointer: `void*`
- Arithmetic
	- Legal: Subtraction
	- ILLEGAL: Addition

> [!example]
>
> ```c
> int water = 10;
> int *value = &water; /* `value` = address of `water` */
> printf("%d %d", water, *value); /* get the value at address `value` */
> 
> void *unknown_value = &water;   /* holds no type information */
> 
> int a, b;
> ptrdiff_t distance = &a - &b; /* canNOT add ptrs, only subtract */
> ```

### ✅ Structures

- Declaration: `struct NAME { ... }`
- Member access: `NAME.MMBR`
- Member access: `NAME->MMBR` => `(*NAME).MMBR`
- Recursive pointer declaration
	- `struct NAME { struct NAME* var1; }`

> [!example]
>
> ```c
> typedef struct Vec3f { float x, y, z } Vec3f;
> struct Node
> {
> 	int data;          /* struct member -> variable declaration */
> 	struct Node *next; /* "recursive" call */
> }
> ```
>
> ```c
> Vec3f vec = { 1.0, 2.0, 3.0 }; /* full initialisation */
> 
> struct Node head = { 5 }; /* initialised `data` to 5, the rest to 0 */
> struct Node *curr;        /* garbage value */
> 
> curr = &head;
> printf("%d %d %d", head.data, curr->data, (*curr).data); /* 5 5 5 */
> ```

> [!warning]
>
> ```c
> /* NOT C89 COMPLIANT */
> struct User user = { .password = "Mike" };
> ```

Alignment

- The alignment of a type is the same as its size
	- `char` : size = alignment = 1
	- `short int` : size = alignment = 2
	- ...
- A type needs to be placed on an address that is a multiple of its size

> [!example]
>
> ```c
> struct Node
> {
> /*xxxx oooo*/ int data;   /* 4-B, no align */
> /*oooo !!!!*/ /* 4-B alignment */
> /*xxxx xxxx*/ void *next; /* 8-B, 4-B align */
> /*xxxx oooo*/ int data;   /* 4-B, no align */
> /*oooo xooo*/ char ctrl;  /* 1-B, no align */
> /*oooo o!!!*/ /* 3-B alignment to end */
> }
> ```

Reference : [Pikuma, understanding computer cache](https://pikuma.com/blog/understanding-computer-cache)

### Unions

Unions are struct where each member is overlapped (offset 0)

- Declaration: `union NAME { ... }`
- Member access: `NAME.MMBR`
- Member access: `NAME->MMBR` => `(*NAME).MMBR`
- Members with offset 0

### ✅ Bit-fields

Bitfields are structures that can contain sub-byte members

- Declaration: `struct NAME { ... }`
- Member declaration: `[un]signed int NAME : BITs;`
- Padding declaration: ` : BITs;` (no name, just colon and bits)
- Alignment padding declaration (move to next word boundary): ` : 0;`
- Member access: `NAME.MMBR`
- Member access: `NAME->MMBR` => `(*NAME).MMBR`

> [!example]
>
> ```c
> struct Flags
> {
> 	unsigned int toggle : 1; /* 1 bit */
> 	signed int state    : 2; /* 2 bit signed */
> 	unsigned int flags  : 5; /* 5 bit */
> 	: 2; /* 2 bits padding */
> 	: 0; /* pad to next word boundary */
> }
> ```
>
> ```c
> struct Flags flags = {0};
> flags.is_static = 1;
> ```

# Details

---

## Emerged patterns

- using an `if else` right after an `else` (`if(COND) EXPR else if(COND) EXPR ...`)
- header files to group common declarations
- value `0` being written as octal `\0`
- enumerations replaced symbolic constants
- bitfields replaced symbolic constants and bitwise operations

## Meta programming

File inclusion

- `#include <FILENAME>`
- `#include "FILEPATH"`

Symbolic constants

- `#define ABC xyz`
- `#define ABC(xyz) xyz`
- `#EXPR` -> `"EXPR"`
- `A ## B` -> `AB`
- `#undef NAME`
- `__LINE__`, `__FILE__`, `__DATE__`, `__TIME__`, `__STDC__`

Conditional branching

- `#if ABC #elif XYZ #else FGH #endif`
- `#if defined(NAME)`
- `#if ! defined(NAME)`
- `#ifdef NAME `
- `#ifndef NAME `

Other

- `#line NUMB FNME`
- `#error MESG`
- `#pragma TKNS`
- `#`

## Scope

### Function scope

External

- all functions are _external_ since you can't declare a function inside another function
- _static external_ functions (all functions are external) are limited to the file currently being compiled

### Variable scope

Internal / Local

- _local_ variables exist only inside the brackets (scope) they have been declared in
- allocation
	- _automatic local_ variables are allocated when needed (like in functions)
	- _static local_ variables are allocated once and reused every time, persisting any information

External

- _external_ variables are globally accessible
- definition : local variable definition in global scope (only once)
- declaration : variable declaration prefixed by `extern` (`extern int count`) (must be declared everywhere it's used if the variable has not been defined in the same source file)
- the scope last from the point it is declared to the end of the file
- allocation
	- _static external_ variables are limited to the file currently being compiled

## Mechanisms

- arithmetic op w integers -> integer op, otherwise cast to float -> float op
- Any assignment is an expression that has a value : `name1 = name2 = value`
- Implicit casting
- Integer promotion
- Variadic arguments:
	- `...`
	- `va_args`, `va_list`
- Adjacent string literals are concatenated at compile time
- Local scope variable shadows global scope ones
- Hexadecimal and octal: `0x1F`, `037`
- Comments: `/* ... */`
- Constant expressions evaluated at compile time (only constants)
- Order of operation is not granted `pop() - pop()` may cause the first pop to be executed after the second one already changed the global state
- The compound statement (`{ }`) lets multiple statements be used as one

## Lexical description

- Translation units
- White space: blanks, horizontal and vertical tabs, newlines, form-feeds, comments
- Token classes
	- identifiers
		- sequence of letters and digits
		- First must be a letter
		- Letters: `[a-zA-Z_]`
		- Digits: `[0-9]`
		- Storage classes: `automatic` (local), `extern` (external linkage), `static` (internal linkage)
		- Types: `arithmetic`, `integral`, `floating`
		- Derived types: `arrays`, `functions`, `pointers`, `structures`, `unions`
	- keywords
		- `auto`, `break`, `case`, `char`, `const`, `continue`, `default`, `do`, `double`, `else`, `enum`, `extern`, `float`, `for`, `goto`, `if`, `int`, `long`, `register`, `return`, `short`, `signed`, `sizeof`, `static`, `struct`, `switch`, `typedef`, `union`, `unsigned`, `void`, `volatile`, `while` + `fortran`, `asm`
	- constants
		- integer (dec, hex, oct), character, floating (fixed, exponential), enumeration
	- string literals
		- A string literal is of type `static char*`
		- `wchar_t` written as `L"..."`
	- operators and other separators
