#include <limits.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
    long int a =(long)INT_MAX;
    long long int c = (long long)a*a;
    printf("%ld\n",INT_MAX);
    printf("%lld\n",c);
    if (c>a)
        printf("overflow");
    else
        printf("NO overflow");
    return 0;
}

// #include <stdio.h>

// int main() {
//     int a = INT_MAX - 10;
//     // int b = 20;
//     long long sum = (long long)a * (long long)a;

//     if (sum > INT_MAX || sum < INT_MIN) {
//         printf("Integer overflow occurred.\n");
//     } else {
//         printf("Sum: %lld\n", sum);
//     }
//     return 0;
// }