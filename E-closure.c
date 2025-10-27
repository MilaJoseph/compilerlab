#include <stdio.h>
#include <stdbool.h>

#define MAX 20

// ε-transition table (adjacency matrix)
bool eps[MAX][MAX] = {false};
int numStates, numTrans;

// Function to read only ε-transitions
void getENFA() {
    printf("Enter number of states (states will be q0 to q(n-1)): ");
    scanf("%d", &numStates);

    printf("Enter total number of transitions: ");
    scanf("%d", &numTrans);

    printf("\nEnter transitions in the form q<from>#q<to>\n");
    printf("Example: q0#q1 (means q0 --ε--> q1)\n\n");

    for (int t = 0; t < numTrans; t++) {
        int from, to;
        char symbol;
        
        printf("Transition %d: ", t + 1);
        scanf(" q%d%cq%d", &from, &symbol, &to);

        if (symbol == '#') { // only store ε-transitions
            eps[from][to] = true;
        }
    }
}

// Recursive function to find ε-closure
void findEclosure(int state, bool visited[]) {
    visited[state] = true; // include the state itself

    for (int i = 0; i < numStates; i++) {
        if (eps[state][i] && !visited[i]) {
            findEclosure(i, visited); // recursively visit reachable states
        }
    }
}

// Function to print ε-closures for all states
void printEclosures() {
    printf("\nε-closures of all states:\n");

    for (int s = 0; s < numStates; s++) {
        bool visited[MAX] = {false};

        findEclosure(s, visited);

        printf("ε-closure(q%d) = { ", s);
        for (int j = 0; j < numStates; j++) {
            if (visited[j])
                printf("q%d ", j);
        }
        printf("}\n");
    }
}

// Main function
int main() {
    getENFA();
    printEclosures();
    return 0;
}
