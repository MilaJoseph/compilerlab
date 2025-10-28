#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

char opStack[MAX];       // Stack for operators (+, -, *, /, =)
char opdStack[MAX][MAX]; // Stack for operands (a, b, t1, etc.)
int topOp = -1, topOpd = -1;

int priority(char c) {
    // Returns priority of operators
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '=') return 0; // lowest precedence
    return -1;
}

void generateICG(char exp[]) {
    int i = 0, tempCount = 1;

    while (exp[i] != '\0') {
        // If it's an operand (letter or digit)
        if (isalnum(exp[i])) {
            char opd[10] = "";
            int j = 0;
            // Read the entire operand (like 'abc' or 'x1')
            while (isalnum(exp[i])) {
                opd[j++] = exp[i++];
            }
            opd[j] = '\0';
            strcpy(opdStack[++topOpd], opd); // Push operand to stack
        }

        // If it's an operator
        if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '=') {
            // While stack not empty and top operator has higher or equal priority
            while (topOp >= 0 && priority(opStack[topOp]) >= priority(exp[i])) {
                char op = opStack[topOp--]; // Pop operator
                char opd2[10], opd1[10];
                strcpy(opd2, opdStack[topOpd--]);
                strcpy(opd1, opdStack[topOpd--]);

                // Generate temporary variable
                printf("t%d = %s %c %s\n", tempCount, opd1, op, opd2);
                sprintf(opdStack[++topOpd], "t%d", tempCount++);
            }
            opStack[++topOp] = exp[i]; // Push current operator
            i++;
        } else {
            i++;
        }
    }

    // Pop remaining operators
    while (topOp >= 0) {
        char op = opStack[topOp--];
        char opd2[10], opd1[10];
        strcpy(opd2, opdStack[topOpd--]);
        strcpy(opd1, opdStack[topOpd--]);

        if (op != '=') {
            printf("t%d = %s %c %s\n", tempCount, opd1, op, opd2);
            sprintf(opdStack[++topOpd], "t%d", tempCount++);
        } else {
            printf("%s = %s\n", opd1, opd2);
        }
    }
}

int main() {
    char exp[50];
    printf("Enter an expression (no spaces): ");
    scanf("%s", exp);
    generateICG(exp);
    return 0;
}
