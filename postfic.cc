#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  // For isdigit function

// Stack structure to hold integer values
#define MAX 100

struct Stack {
    int items[MAX];
    int top;
};

// Function to initialize the stack
void initstack(struct Stack *s) {
    s->top = -1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack *s) {
    return s->top == -1;
}

// Function to check if the stack is full
int isFull(struct Stack *s) {
    return s->top == MAX - 1;
}

// Function to push into the stack
void push(struct Stack *s, int item) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->items[++(s->top)] = item;
}

// Function to pop an item from the stack
int pop(struct Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return s->items[(s->top)--];
}

// Function to evaluate a postfix expression
int evaluatePostfix(char* expression) {
    struct Stack s;
    initstack(&s);

    // Traverse the postfix expression
    for (int i = 0; expression[i] != '\0'; i++) {
        char token = expression[i];

        // If the token is a digit, push it into the stack
        if (isdigit(token)) {
            push(&s, token - '0');
        }
        // If the token is an operator, pop two operands and apply the operator
        else if (token == '+' || token == '-' || token == '*' || token == '/') {
            int operand2 = pop(&s);
            int operand1 = pop(&s);
            int result;

            switch (token) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': result = operand1 / operand2; break;
                default:
                    printf("Invalid operator\n");
                    return -1;
            }

            push(&s, result);  // Push the result back into the stack
        } else {
            printf("Invalid character in the expression\n");
            return -1;
        }
    }

    // The final result will be the only item in the stack
    return pop(&s);
}

int main() {
    char expression[] = "53+12-*";
    int result = evaluatePostfix(expression);

    if (result != -1) {
        printf("Result of postfix expression '%s' is: %d\n", expression, result);
    }

    return 0;
}

