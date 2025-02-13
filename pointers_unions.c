/*******************************************************************************
 * Name          : pointers.c
 * Author        : Brian S. Borowski
 * Version       : 1.0
 * Date          : February 6, 2023
 * Last modified : May 31, 2024
 * Description   : Demonstrates how unions and pointers work.
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef union my_union {
    char c;
    short s;
    int i;
} my_union;

/**
 * Displays a header/footer line in ASCII art for num_bytes bytes of memory.
 */
void display_line(const unsigned int num_bytes) {
    if (num_bytes > 0) {
        putc('+', stdout);
        for (int i = 0; i < num_bytes; i++) {
            printf("--------+");
        }
        printf("\n");
    }
}

/**
 * Displays the contents of a sequence of num_bytes bytes.
 * The bytes can be of any data type, since this function accepts
 * a void * parameter. The sequence is broken down into 1-byte unsigned
 * characters, and the decimal value of each unsigned character is printed
 * in each memory cell.
 */
void byteprintf(void *p, const unsigned int num_bytes) {
    int bytes = num_bytes;
    unsigned char *data = (unsigned char *)p + num_bytes - 1;
    display_line(num_bytes);
    putc('|', stdout);
    while (bytes--) {
        printf("%8u", *data--);
        putc('|', stdout);
    }
    printf("\n");
    display_line(num_bytes);
}

/**
 * Prints an array of num_elements elements using pointer arithmetic.
 */
void print_array_pt(int *array, const int num_elements) {
    putc('[', stdout);
    if (num_elements >= 1) {
        printf("%d", *array++);
    }
    for (int *end = array + num_elements - 1; array < end; ) {
        printf(", %d", *array++);
    }
    putc(']', stdout);
    printf("\n");
}

/**
 * Prints an array of num_elements elements using indexing.
 */
void print_array(int array[], const int num_elements) {
    putc('[', stdout);
    if (num_elements >= 1) {
        printf("%d", array[0]);
    }
    for (int i = 1; i < num_elements; i++) {
        printf(", %d", array[i]);
    }
    putc(']', stdout);
    printf("\n");
}

int main(int argc, char **argv) {
    my_union u;
    int var0;

    u.i = 0;
    u.c = 'A';
    u.s = 16383;
    var0 = u.c;

    printf("%d\n", u.c);  // Why is u.c -1?
    printf("%d\n", var0); // Why is var0 -1?
    byteprintf(&u, sizeof(u));
	// Best way to shift more than 31 bits: 1 should be 1UL for unsigned long.
    unsigned long r = 1UL << 31;
    byteprintf(&r, sizeof(r));

    // u.c will contain eight '1' bits. That's -1 as a signed char.
    // That -1 is assigned to var0, which now contains 32 '1' bits, and is -1
    // as a signed int.

    int x = 5, y = 6;
    int *p = &x, *q = &y;
    printf("x = %d, y = %d\n", x, y);
    printf("*p = %d, *q = %d\n", *p, *q);
    printf("&x = %p, &y = %p\n", (void *)&x, (void *)&y);
    printf("p = %p, q = %p\n", (void *)p, (void *)q);

    int array[10];
    for (int i = 0; i < 10; i++) {
        array[i] = i;
    }
    print_array(array, 10);
    print_array_pt(array, 10);

	return EXIT_SUCCESS;
}
