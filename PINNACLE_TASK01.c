#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void menu() {
    printf("\n===== Basic Arithmetic Operations =====\n\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Exponentiation\n");
    printf("6. Exit\n\n");
    printf("===================================\n");
}

int main() {
    int choice;
    double num1, num2, result;
    
    do {
        system("clear");
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        if (choice >= 1 && choice <= 5) {
            printf("Enter first number: ");
            scanf("%lf", &num1);
            printf("Enter second number: ");
            scanf("%lf", &num2);
        }
        
        switch (choice) {
            case 1:
                result = num1 + num2;
                printf("Result: %.3lf\n", result);
                break;
            case 2:
                result = num1 - num2;
                printf("Result: %.3lf\n", result);
                break;
            case 3:
                result = num1 * num2;
                printf("Result: %.3lf\n", result);
                break;
            case 4:
                if (num2 != 0)
                    printf("Result: %.3lf\n", num1 / num2);
                else
                    printf("Error: Division by zero is not allowed!\n");
                break;
            case 5:
                result = pow(num1, num2);
                printf("Result: %.3lf\n", result);
                break;
            case 6:
                printf("Exiting the program. Thank you!\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    } while (choice != 6);
    
    return 0;
}
