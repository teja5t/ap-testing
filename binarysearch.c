/*******************************************************************************
 * Name          : binarysearch.c
 * Author        : Brian S. Borowski
 * Version       : 1.0
 * Date          : February 8, 2023
 * Last modified : February 12, 2025
 * Description   : Demonstrates pointer arithmetic, pointers to functions,
 *                 and writing comparators via the binary search.
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/**
 * Integer comparator.
 * Cast const void* to int* and then dereference.
 *  > 0 iff a > b
 *  < 0 iff a < b
 *    0 iff a = b
 */
int int_cmp(const void *a, const void *b) {
    int aa = *(int *)a, bb = *(int *)b;
    if (aa > bb) {
        return 1;
    }
    if (aa < bb) {
        return -1;
    }
    return 0;
}

/**
 * Performs a binary search on any data type as a long as we know the the number
 * of elements and the size of each element, as well as have a comparator
 * function for comparing two values.
 */
void *
binary_search(const void *key, const void *values, const size_t num_elems,
              const size_t elem_sz, int (*cmp)(const void *, const void *)) {
    int low = 0, high = num_elems - 1;
    // We must have another pointer to the address of values. This other pointer
    // must be of char* and not void*. You cannot do pointer arithmetic with
    // void* pointers. char* pointers are incrememented by 1 byte, so they are
    // able to point to any offset within a block of memory, hence they are used
    // frequently when pointer arithmetic is required.
    // Explicit casting is not necessary but can be done.
    const char *base_ptr = values;

    while (low <= high) {
        // Avoid potentional overflow with this formula.
        int mid = low + (high - low) / 2;

        // ptr will contain the address of values[i].
        // Don't forget to multiply mid by elem_sz so that your byte offset is
        // correct.
        const void *ptr = base_ptr + mid * elem_sz;

        // Call the comparator through the function pointer passed in as an
        // argument to binary_search.
        int result = cmp(key, ptr);

        if (result == 0) {
            // key == values[mid]
            return (void *)ptr;
        }
        if (result > 0) {
            // key > values[mid]
            low = mid + 1;
        } else {
            // key < values[mid]
            high = mid - 1;
        }
    }
    return NULL;
}

int main() {
    // Allocate two arrays of the same size on the stack.
    int array[] = { 1, 4, 7, 18, 90 };
    int keys[] =  { 1, 5, 7, 19, 90 };

    // You can get the number of elements for arrays allocated on the stack
    // using the code below. Note this does not work for arrays allocated on the
    // heap with malloc, nor does it work if you pass a pointer to the array
    // to another function and then attempt to take its size. You can use this
    // code only inside the function where the array is declared.
    size_t num_elems = sizeof(array)/sizeof(int);

    for (int i = 0; i < num_elems; i++) {
        printf("Searching for %d...", keys[i]);
        // keys + i is equivalent to &(keys[i])
        int *ptr =
            binary_search(keys + i, array, num_elems, sizeof(int), int_cmp);

        // Check the return value.
        if (ptr == NULL) {
            printf("%d was not found.\n", keys[i]);
        } else {
            printf("%d was found at index %lu!\n", *ptr, ptr - array);
        }
    }
    return EXIT_SUCCESS;
}
