#include <stdio.h>
#include <string.h>

// Grammar: E -> E+E | E*E | (E) | i
// Note: We’ll only use 4 rules here to keep things simple.
char *productions[] = {"E+E", "E*E", "(E)", "i"};
int num_productions = 4;

char stack[100];
int top = -1;  // stack top

// Function to print parser step
void print_step(const char* action, const char* input, int ip) {
    // print stack
    for (int i = 0; i <= top; i++) {
        printf("%c", stack[i]);
    }
    printf("\t\t");

    // print input
    printf("%s", input + ip);
    printf("\t\t");

    // print action
    printf("%s\n", action);
}

// Shift operation
void shift(char symbol) {
    stack[++top] = symbol;
}

// Reduce operation
int reduce() {
    for (int i = 0; i < num_productions; i++) {
        int len = strlen(productions[i]);

        if (top + 1 >= len) {
            // Check if top of stack matches RHS
            if (strncmp(&stack[top - len + 1], productions[i], len) == 0) {
                // Pop RHS
                top = top - len + 1;
                // Replace with LHS (always 'E' here)
                stack[top] = 'E';
                return 1; // reduced
            }
        }
    }
    return 0; // no reduction
}

int main() {
    char input[100];
    int ip = 0;

    printf("Grammar:\n");
    printf("E -> E+E | E*E | (E) | i\n");
    printf("--------------------------------\n");
    printf("Enter input string: ");
    scanf("%s", input);

    // Initialize stack with $
    stack[++top] = '$';

    printf("\n--- Parsing Steps ---\n");
    printf("Stack\t\tInput\t\tAction\n");
    printf("-----\t\t-----\t\t------\n");
    print_step("Initial", input, ip);

    // Parsing loop
    while (1) {
        if (reduce()) {
            print_step("Reduce", input, ip);
        } else if (input[ip] != '\0') {
            shift(input[ip]);
            ip++;
            print_step("Shift", input, ip);
        } else {
            break;
        }
    }

    // Acceptance check
    if (top == 1 && stack[1] == 'E') {
        printf("\nSUCCESS: Input string accepted.\n");
    } else {
        printf("\nERROR: Input string rejected.\n");
    }

    return 0;
}
