#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 1024  // large Fibonacci numbers

typedef struct {
    char num[MAX_DIGITS];
    short length;
} largest;

void add(largest *first, largest *second, largest *result);
void print_largest_num(largest *num);
void set_num(largest *num, const char *value);

int main() {
    int num;

    //  for input
    printf("Please enter the Fibonacci sequence number: ");
    if (scanf("%d", &num) != 1) {  // Ensure valid input
        puts("Invalid input.");
        return 1;
    }

    if (num == 0) {
        printf("The %dth Fibonacci number is %d\n", num, 0);
        return 0;
    }
    if (num == 1 || num == 2) {
        printf("The %dth Fibonacci number is %d\n", num, 1);
        return 0;
    }


    largest final, first, second;
    
    set_num(&first, "0");  // First Fibonacci number (0)
    set_num(&second, "1");  // Second Fibonacci number (1)

    for (int i = 2; i <= num; i++) {
        add(&first, &second, &final);
        
        // Move second to first, final to second
        first = second;
        second = final;
    }

    printf("The %dth Fibonacci number is ", num);
    print_largest_num(&final);
    return 0;
}

// two large numbers stored 
void add(largest *first, largest *second, largest *result) {
    int carry = 0;
    int first_idx = MAX_DIGITS - 1;
    int second_idx = MAX_DIGITS - 1;
    int result_idx = MAX_DIGITS - 1;

    // Start with the larger of the two lengths
    result->length = (first->length > second->length) ? first->length : second->length;

    // Reset result's num buffer to '0' initially
    memset(result->num, '0', MAX_DIGITS);

    // Loop from the least significant digit to the most significant
    while (first_idx >= MAX_DIGITS - first->length || second_idx >= MAX_DIGITS - second->length) {
        int digit1 = (first_idx >= MAX_DIGITS - first->length) ? first->num[first_idx] - '0' : 0;
        int digit2 = (second_idx >= MAX_DIGITS - second->length) ? second->num[second_idx] - '0' : 0;

        int sum = digit1 + digit2 + carry;
        result->num[result_idx] = (sum % 10) + '0';  // Store the last digit
        carry = sum / 10;  // Carry the remaining part

        first_idx--;
        second_idx--;
        result_idx--;
    }

    // If there is a remaining carry, place it in the result
    if (carry) {
        result->num[result_idx] = carry + '0';
        result->length++;
    } else {
        // Calculate the correct length in case no carry
        result->length = MAX_DIGITS - result_idx - 1;
    }
}

// Prints a large number 
void print_largest_num(largest *num) {
    int start = MAX_DIGITS - num->length;
    for (int i = start; i < MAX_DIGITS; i++) {
        putchar(num->num[i]);
    }
    printf("\n");
}

// Initializes a largest struct 
void set_num(largest *num, const char *value) {
    size_t len = strlen(value);
    memset(num->num, '0', MAX_DIGITS);  // Initialize all digits to '0'

    for (int i = 0; i < len; i++) {
        num->num[MAX_DIGITS - len + i] = value[i];
    }
    num->length = len;
}
