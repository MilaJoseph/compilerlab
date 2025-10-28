#include <stdio.h>
#include <string.h>

#define MAX 100

// Grammar:
// E -> E+E | E*E | E-E | E/E | (E) | i
char *productions[] = {"E+E", "E*E", "E-E", "E/E", "(E)", "i"};
int num_productions = 6;

char stack[MAX];
int top = -1;

// Function to display stack, input, and action in formatted table
void print_step(const char *action, const char *input, int ip) {
    // Print stack content
    for (int i = 0; i <= top; i++)
        printf("%c", stack[i]);
    printf("\t\t");

    // Print remaining input
    printf("%s\t\t", input + ip);

    // Print action
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
                // Pop RHS and replace with LHS 'E'
                top = top - len + 1;
                stack[top] = 'E';

                char action[50];
                sprintf(action, "Reduced by production E->%s", productions[i]);
                print_step(action, "", 0);
                return 1; // Reduced successfully
            }
        }
    }
    return 0; // No reduction
}

int main() {
    char input[MAX];
    int ip = 0;

    printf("Grammar:\n");
    printf("E -> E+E | E*E | E-E | E/E | (E) | i\n");
    printf("--------------------------------------------------\n");
    printf("Enter the input string: ");
    scanf("%s", input);

    // Initialize stack with $
    stack[++top] = '$';

    printf("\nSHIFT-REDUCE PARSING\n");
    printf("Stack\t\tInput\t\tAction\n");
    printf("-----\t\t-----\t\t------\n");

    print_step("Initial", input, ip);

    // Parsing loop
    while (1) {
        if (reduce()) {
            // reduction already printed inside reduce()
        } else if (input[ip] != '\0') {
            char action[30];
            sprintf(action, "Shifted %c to stack", input[ip]);
            shift(input[ip]);
            ip++;
            print_step(action, input, ip);
        } else {
            break;
        }
    }

    // Final acceptance check
    if (top == 1 && stack[1] == 'E') {
        printf("--------------------------------------------------\n");
        printf("Input accepted ✅\n");
    } else {
        printf("--------------------------------------------------\n");
        printf("Input rejected ❌\n");
    }

    return 0;
}
