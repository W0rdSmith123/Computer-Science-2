#include <stdio.h>

// Shift elements of the array by 1 using pointer arithmetic
int* ShiftByOne(int* arr, int size) {
    if (size <= 0) {
        return arr; // return the input array if it's empty or has invalid size
    }

    int* last = arr + size - 1;  // Pointing to the last element
    int temp = *last;

    for (int* ptr = last; ptr > arr; ptr--) {
        *ptr = *(ptr - 1);
    }
    *arr = temp;

    return arr;
}

// Return the memory address of the maximum value in the array using pointer arithmetic
int* GetMax(int* arr, int size) {
    int* maxAddress = arr; // Pointing to the first element
    for (int* ptr = arr; ptr < arr + size; ptr++) {
        if (*ptr > *maxAddress) {
            maxAddress = ptr;
        }
    }
    return maxAddress;
}

// Return the size of the given C-String using pointer arithmetic
unsigned int GetSize(char* str) {
    char* ptr = str;
    while (*ptr != '\0') {
        ptr++;
    }
    return ptr - str; // Difference of addresses gives the size
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    ShiftByOne(arr, size);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int* maxValueAddress = GetMax(arr, size);
    printf("Max value: %d at address: %p\n", *maxValueAddress, maxValueAddress);

    char str[] = "Hello, World!";
    printf("Size of string: %u\n", GetSize(str));

    return 0;
}
