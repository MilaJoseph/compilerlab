#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10   // maximum number of productions
#define LEN 20   // maximum length of each production

int n;                        // number of productions
char productions[MAX][LEN];   // store productions
char first[26][LEN];          // FIRST sets
char follow[26][LEN];         // FOLLOW sets
char startSymbol;             // starting symbol

// Add element to a set if not already present
void addToSet(char set[], char c) {
    if (!strchr(set, c)) {
        int len = strlen(set);
        set[len] = c;
        set[len+1] = '\0';
    }
}

// Compute FIRST of a symbol
void computeFirst(char symbol, char result[]) {
    if (!isupper(symbol)) { // terminal
        addToSet(result, symbol);
        return;
    }

    for (int i=0; i<n; i++) {
        if (productions[i][0] == symbol) {
            // RHS of production
            char rhs = productions[i][3]; // after "A->"
            if (!isupper(rhs)) {
                addToSet(result, rhs);
            } else {
                computeFirst(rhs, result);
            }
        }
    }
}

// Compute FOLLOW of a symbol
void computeFollow(char symbol, char result[]) {
    if (symbol == startSymbol) {
        addToSet(result, '$'); // end marker
    }

    for (int i=0; i<n; i++) {
        for (int j=3; productions[i][j]!='\0'; j++) {
            if (productions[i][j] == symbol) {
                char next = productions[i][j+1];
                if (next != '\0') {
                    if (!isupper(next)) {
                        addToSet(result, next);
                    } else {
                        char temp[LEN] = "";
                        computeFirst(next, temp);
                        for (int k=0; temp[k]!='\0'; k++) {
                            if (temp[k] != '#') addToSet(result, temp[k]);
                        }
                    }
                } else { // symbol is at the end
                    if (productions[i][0] != symbol) {
                        char temp[LEN] = "";
                        computeFollow(productions[i][0], temp);
                        for (int k=0; temp[k]!='\0'; k++) {
                            addToSet(result, temp[k]);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (like E->E+T):\n");
    for (int i=0; i<n; i++) {
        scanf("%s", productions[i]);
    }

    startSymbol = productions[0][0]; // first LHS is start symbol

    printf("\nFIRST sets:\n");
    for (int i=0; i<n; i++) {
        char lhs = productions[i][0];
        char result[LEN] = "";
        computeFirst(lhs, result);
        printf("FIRST(%c) = { %s }\n", lhs, result);
        strcpy(first[lhs-'A'], result);
    }

    printf("\nFOLLOW sets:\n");
    for (int i=0; i<n; i++) {
        char lhs = productions[i][0];
        char result[LEN] = "";
        computeFollow(lhs, result);
        printf("FOLLOW(%c) = { %s }\n", lhs, result);
    }

    return 0;
}
