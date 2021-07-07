#include <cstdio>
#include "include/string.h"

int main() {
    String str(3);

    printf("value : %s\n", str.mPtr);
    printf("length : %d \n", str.getLength());
    printf("size : %d \n", str.mSize);
    printf("address : %x \n\n", str.mPtr);

    str.append('a');

    printf("value : %s\n", str.mPtr);
    printf("length : %d \n", str.getLength());
    printf("size : %d \n", str.mSize);
    printf("address : %x \n\n", str.mPtr);

    str.append('b');

    printf("value : %s\n", str.mPtr);
    printf("length : %d \n", str.getLength());
    printf("size : %d \n", str.mSize);
    printf("address : %x \n\n", str.mPtr);

    str.append('c');

    printf("value : %s\n", str.mPtr);
    printf("length : %d \n", str.getLength());
    printf("size : %d \n", str.mSize);
    printf("address : %x \n\n", str.mPtr);

    return 0;
}