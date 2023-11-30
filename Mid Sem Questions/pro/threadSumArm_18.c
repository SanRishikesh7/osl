#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

// Function to compute the sum of digits of a number
int sumOfDigits(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

// Function to check if a number is an Armstrong number
bool isArmstrong(int num) {
    int original = num;
    int sum = 0;
    int n = 0;
    
    while (num > 0) {
        int digit = num % 10;
        sum += digit * digit * digit; // Cube of the digit
        num /= 10;
    }
    
    return sum == original;
}

// Thread function to compute the sum of digits
void* computeSum(void* arg) {
    int num = *((int*)arg);
    int result = sumOfDigits(num);
    printf("Sum of digits of %d is: %d\n", num, result);
    return NULL;
}

// Thread function to check if a number is an Armstrong number
void* checkArmstrong(void* arg) {
    int num = *((int*)arg);
    if (isArmstrong(num)) {
        printf("%d is an Armstrong number.\n", num);
    } else {
        printf("%d is not an Armstrong number.\n", num);
    }
    return NULL;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    pthread_t threadSum, threadArmstrong;

    // Create threads to perform the operations
    pthread_create(&threadSum, NULL, computeSum, &num);
    pthread_create(&threadArmstrong, NULL, checkArmstrong, &num);

    // Wait for threads to finish
    pthread_join(threadSum, NULL);
    pthread_join(threadArmstrong, NULL);

    return 0;
}
