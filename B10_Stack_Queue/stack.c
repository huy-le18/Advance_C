#include <stdio.h>
#include <stdlib.h>

typedef struct Stack
{
    int* items;
    int size;
    int top;
}Stack;

void initialize(Stack *stack, int size)
{
    stack -> items = (int*)malloc(sizeof(int) * size);
    stack -> size = size;
    stack -> top = -1;
}

int is_empty( Stack stack) {
    return stack.top == -1;
}

int is_full( Stack stack) {
    return stack.top == stack.size - 1;
}

void push( Stack *stack, int value) {
    if(is_full(*stack) != 1)
    {
        stack -> top ++;
        stack -> items[stack -> top] = value;
    }
    else
    {
        printf("Full stack!\n");
        printf("No add value %d\n", value);
    }
}

int pop( Stack *stack) {
    int value;

    if (is_empty(*stack) == 1)
    {
        printf("Empty stack!\n");
        value = 0;
    }
    else
    {
        value = stack -> items[stack -> top];
        stack -> top --;
    }

    return value;
}

int top(Stack stack) {

    int value;

    if (is_empty(stack) == 1)
    {
        printf("Empty stack!\n");
        value = 0;
    }
    else
    {
        value = stack.items[stack.top];
    }

    return value;
}

int main() {
    Stack stack1;
    initialize(&stack1, 5);

    push(&stack1, 10);
    push(&stack1, 20);
    push(&stack1, 30);
    push(&stack1, 40);
    push(&stack1, 50);
    push(&stack1, 60);
    push(&stack1, 70);
    pop(&stack1);

    printf("Top element: %d\n", top(stack1));
    printf("Pop element: %d\n", pop(&stack1));
    printf("Pop element: %d\n", pop(&stack1));
    printf("Top element: %d\n", top(stack1));
    printf("Pop element: %d\n", pop(&stack1));

    return 0;
}








