#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum { INT_TYPE, STRING_TYPE } ValueType;

typedef struct {
    ValueType type;
    union {
        int intValue;
        char wordValue[100];
    } data;
} StackElement;

StackElement *stack;
int top = -1;
int capacity;

// Initialize stack
void initStack(int size) {
    capacity = size;
    stack = (StackElement *)malloc(capacity * sizeof(StackElement));
    if (stack == NULL) {
        printf("Memory allocation failed. Exiting.\n");
        exit(1);
    }
}

// Resize stack when full
void resizeStack() {
    capacity *= 2;
    stack = (StackElement *)realloc(stack, capacity * sizeof(StackElement));
    if (stack == NULL) {
        printf("Memory reallocation failed. Exiting.\n");
        exit(1);
    }
    printf("Stack resized to capacity %d\n", capacity);
}

// Check if stack is empty
int isEmpty() {
    return top == -1;
}

// Push integer
void pushInt(int value) {
    if (top == capacity - 1) {
        resizeStack();
    }
    stack[++top].type = INT_TYPE;
    stack[top].data.intValue = value;
    printf("%d pushed onto the stack\n", value);
}

// Push string
void pushString(const char *word) {
    if (top == capacity - 1) {
        resizeStack();
    }
    stack[++top].type = STRING_TYPE;
    strncpy(stack[top].data.wordValue, word, sizeof(stack[top].data.wordValue) - 1);
    stack[top].data.wordValue[sizeof(stack[top].data.wordValue) - 1] = '\0';
    printf("\"%s\" pushed onto the stack\n", word);
}

// Pop element
StackElement pop() {
    StackElement error;
    error.type = INT_TYPE;
    error.data.intValue = -9999;

    if (isEmpty()) {
        printf("Stack Underflow! Cannot pop\n");
        return error;
    } else {
        return stack[top--];
    }
}

// Peek at top element
StackElement peek() {
    StackElement error;
    error.type = INT_TYPE;
    error.data.intValue = -9999;

    if (isEmpty()) {
        printf("Stack is empty\n");
        return error;
    } else {
        return stack[top];
    }
}

// Display stack
void display() {
    if (isEmpty()) {
        printf("Stack is empty\n");
    } else {
        printf("Stack elements are:\n");
        for (int i = top; i >= 0; i--) {
            if (stack[i].type == INT_TYPE)
                printf("%d\n", stack[i].data.intValue);
            else
                printf("\"%s\"\n", stack[i].data.wordValue);
        }
    }
}

// Free memory
void cleanup() {
    free(stack);
}
// Check if stack is full
int isFull() {
    return top == capacity - 1;
}

int main() {
    int choice, size;
    char input[100];

    printf("Enter the initial size of the stack: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        printf("Invalid size. Exiting.\n");
        return 1;
    }

    initStack(size);

    while (1) {
        printf("\n--- Stack Menu ---\n");
        printf("1. Push (Integer or Word)\n2. Pop\n3. Peek\n4. Display\n5. IS EMPTY OR NOT\n6. STACK FULL OR NOT\n7. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case 1:
            printf("Enter an integer or word to push: ");
            while (getchar() != '\n'); // Clear buffer
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0'; // Remove newline

            // Check if input is an integer
            int isNumber = 1;
            for (int i = 0; input[i] != '\0'; i++) {
                if (!isdigit(input[i]) && !(i == 0 && input[i] == '-')) {
                    isNumber = 0;
                    break;
                }
            }

            if (isNumber) {
                pushInt(atoi(input));
            } else {
                pushString(input);
            }
            break;

        case 2: {
            StackElement popped = pop();
            if (popped.type == INT_TYPE)
                printf("Popped value: %d\n", popped.data.intValue);
            else
                printf("Popped value: \"%s\"\n", popped.data.wordValue);
            break;
        }

        case 3: {
            StackElement topElem = peek();
            if (topElem.type == INT_TYPE)
                printf("Top value: %d\n", topElem.data.intValue);
            else
                printf("Top value: \"%s\"\n", topElem.data.wordValue);
            break;
        }

        case 4:
            display();
            break;
        case 5: {
            if (isEmpty())
                printf("Yes, the stack is empty.\n");
            else
                printf("No, the stack is not empty.\n");
            break;
        }

        case 6: {
            if (isFull())
                printf("Yes, the stack is full.\n");
            else
                printf("No, the stack is not full.\n");
            break;
        }  
        case 7: {
            printf("Exiting program.\n");
            cleanup();
            return 0;
        }

        default:
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
