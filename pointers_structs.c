/*******************************************************************************
 * Name          : pointers_structs.c
 * Author        : Brian S. Borowski
 * Version       : 1.0
 * Date          : February 6, 2023
 * Last modified : February 13, 2025
 * Description   : Demonstrates pointers to functions, malloc/free, and struct
 *                 padding.
 ******************************************************************************/

/*******************************************************************************
 Rules for struct padding:
 1. There is no padding at the beginning of a struct.
 2. All elements of the struct need to be aligned according to their size.
 3. All bytes of an element are stored contiguously.
 4. The total size of the struct must be a multiple of the size of the
    largest element.
 ******************************************************************************/
#include <inttypes.h> // for printing pointer addresses in base 10
#include <stdio.h>
#include <stdlib.h>

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int do_math(int (*op)(int, int), int a, int b) {
    return op(a, b);
}

/*******************************************************************************
  +---+---+---+---+---+---+---+---+
 0| first                         |
  +---+---+---+---+---+---+---+---+
 8| age           | - | - | - | - |
  +---+---+---+---+---+---+---+---+
16| last                          |
  +---+---+---+---+---+---+---+---+
24| id    | - | - | - | - | - | - |
  +---+---+---+---+---+---+---+---+
  Total: 32 bytes
 ******************************************************************************/
typedef struct person1 {
    char *first;
    int age;
    char *last;
    short id;
} person1;

/*******************************************************************************
  +---+---+---+---+---+---+---+---+
 0| first                         |
  +---+---+---+---+---+---+---+---+
 8| last                          |
  +---+---+---+---+---+---+---+---+
16| age           | id    | - | - |
  +---+---+---+---+---+---+---+---+
  Total: 24 bytes
 ******************************************************************************/
typedef struct person2 {
    char *first;
    char *last;
    int age;
    short id;
} person2;

/*******************************************************************************
  +---+---+---+---+
 0| i             |
  +---+---+---+---+
 4| c | - | - | - |
  +---+---+---+---+
  Total: 8 bytes
 ******************************************************************************/
typedef struct obj1 {
    int i;
    char c;
} obj1;

/*******************************************************************************
  +---+---+---+---+---+---+---+---+
 0| c | - | s     | c | - | - | - |
  +---+---+---+---+---+---+---+---+
 8| l                             |
  +---+---+---+---+---+---+---+---+
  Total: 16 bytes
 ******************************************************************************/
typedef struct obj2 {
    char c;
    short s;
    char c1;
    long l;
} obj2;

/*******************************************************************************
  +---+---+---+---+
 0| c1| - | - | - |
  +---+---+---+---+
 4| i             |
  +---+---+---+---+
 8| c | - | - | - |
  +---+---+---+---+
12| c2| - | - | - |
  +---+---+---+---+
16| in            |
  +---+---+---+---+
  Total: 20 bytes
 ******************************************************************************/
typedef struct obj3 {
    char c1;
    obj1 o;
    char c2;
    int in;
} obj3;

/*******************************************************************************
  +---+---+---+---+
 0| c | c | c | c |
  +---+---+---+---+
 4| c | c | c | c |
  +---+---+---+---+
 8| c | - | - | - |
  +---+---+---+---+
12| a             |
  +---+---+---+---+
16| c1| - | - | - |
  +---+---+---+---+
20| i             |
  +---+---+---+---+
24| s     | - | - |
  +---+---+---+---+
  Total: 28 bytes
 ******************************************************************************/
typedef struct obj4 {
    char c[9];
    int a;
    char c1;
    int i;
    short s;
} obj4;

/*******************************************************************************
  +---+---+---+---+---+---+---+---+
 0| c2| - | - | - | - | - | - | - |
  +---+---+---+---+---+---+---+---+
 8| lo                            |
  +---+---+---+---+---+---+---+---+
16| m             | c | c | c | c |
  +---+---+---+---+---+---+---+---+
24| c | c | c | c | c | - | - | - |
  +---+---+---+---+---+---+---+---+
32| a             | c1| - | - | - |
  +---+---+---+---+---+---+---+---+
40| i             | s     | - | - |
  +---+---+---+---+---+---+---+---+
48| n             | - | - | - | - |
  +---+---+---+---+---+---+---+---+
  Total: 56 bytes
 ******************************************************************************/
typedef struct obj5 {
    char c2;
    long lo;
    int m;
    obj4 o;
    int n;
} obj5;

int main(int argc, char **argv) {
    // Declares a pointer, named op, to a function.
    int (*op)(int, int);
    // Make op point to the add function.
    op = add;
    // Pass it to do_math.
    printf("%d\n", do_math(op, 5, 6));
    /* Make op point to the sub function. This time we're using &, though it
       works the same with or without it. */
    op = &sub;
    // Pass it to do_math.
    printf("%d\n", do_math(op, 5, 6));
    // Or you can call it directly here.
    printf("%d\n", op(5, 6));

    printf("person1: %lu bytes\n", sizeof(person1));
    printf("person2: %lu bytes\n", sizeof(person2));
    printf("obj1: %lu bytes\n", sizeof(obj1));
    printf("obj2: %lu bytes\n", sizeof(obj2));
    printf("obj3: %lu bytes\n", sizeof(obj3));
    printf("obj4: %lu bytes\n", sizeof(obj4));
    printf("obj5: %lu bytes\n", sizeof(obj5));

    /* Check the diagram by verifying how many bytes are present from the first
       byte of one field to the first byte of the next field. This includes any
       padding that may be present. */
    obj5 o5;
    printf("c2  : addr, base 10: %" PRIuPTR " - length %" PRIuPTR "\n",
           (uintptr_t)&o5.c2, (uintptr_t)&o5.lo - (uintptr_t)&o5.c2);
    printf("lo  : addr, base 10: %" PRIuPTR " - length %" PRIuPTR "\n",
           (uintptr_t)&o5.lo, (uintptr_t)&o5.m - (uintptr_t)&o5.lo);
    printf("m   : addr, base 10: %" PRIuPTR " - length %" PRIuPTR "\n",
           (uintptr_t)&o5.m, (uintptr_t)&o5.o - (uintptr_t)&o5.m);
    printf("o.c : addr, base 10: %" PRIuPTR " - length %" PRIuPTR "\n",
           (uintptr_t)&o5.o, (uintptr_t)&o5.o.a - (uintptr_t)&o5.o);
    printf("o.a : addr, base 10: %" PRIuPTR " - length %" PRIuPTR "\n",
           (uintptr_t)&o5.o.a, (uintptr_t)&o5.o.c1 - (uintptr_t)&o5.o.a);
    printf("o.c1: addr, base 10: %" PRIuPTR " - length %" PRIuPTR "\n",
           (uintptr_t)&o5.o.c1, (uintptr_t)&o5.o.i - (uintptr_t)&o5.o.c1);
    printf("o.i : addr, base 10: %" PRIuPTR " - length %" PRIuPTR "\n",
           (uintptr_t)&o5.o.i, (uintptr_t)&o5.o.s - (uintptr_t)&o5.o.i);
    printf("o.s : addr, base 10: %" PRIuPTR " - length %" PRIuPTR "\n",
           (uintptr_t)&o5.o.s, (uintptr_t)&o5.n - (uintptr_t)&o5.o.s);
    printf("n   : addr, base 10: %" PRIuPTR " - length %" PRIuPTR "\n",
           (uintptr_t)&o5.n, (uintptr_t)&o5 + sizeof(o5) - (uintptr_t)&o5.n);

    // Allocate enough memory to hold an obj2 struct on the heap.
    obj2 *o_ptr = malloc(sizeof(obj2));
    /* Use the arrow notation on the pointer to a struct allocated on the heap
       to reference the struct's fields. */
    o_ptr->c = 'A';
    /* Do not forget to free up all memory allocated on the heap.
       Use valgrind --leak-check=full ./progname <optional args>
       It must say "All heap blocks were freed -- no leaks are possible" */
    free(o_ptr);

    return EXIT_SUCCESS;
}
