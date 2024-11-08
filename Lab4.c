#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define max 50

int top = -1;
char stack[max];

bool isEmpty()
{
    return top == -1;
}

bool isFull()
{
    return top == max - 1;
}

void push(char element)
{
    if (!isFull())
    {
        top++;
        stack[top] = element;
    }
    else
    {
        printf("Error! Stack full \n");
    }
}

char pop()
{
    if (!isEmpty())
    {
        return stack[top--];
    }
    else
    {
        printf("Error! Stack is empty \n");
        return '\0'; // Return null character for error handling
    }
}

char peek()
{
    if (!isEmpty())
    {
        return stack[top];
    }
    else
    {
        return '\0'; // Return null character if stack is empty
    }
}

int precedence(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    }
    return -1; // For operands and other operators not listed above
}

void infixToPostfix(char *exp)
{
    char result[max]; // This will store the postfix expression
    int i = 0, k = 0;

    for (i = 0; exp[i] != '\0'; ++i)
    {
        if (isalnum(exp[i]))
        { // Check if it's an operand
            result[k++] = exp[i];
        }
        else if (exp[i] == '(')
        {
            push(exp[i]);
        }
        else if (exp[i] == ')')
        {
            while (!isEmpty() && peek() != '(')
            {
                result[k++] = pop();
            }
            if (!isEmpty() && peek() != '(')
            {
                return; // Invalid expression
            }
            else
            {
                pop();
            }
        }
        else
        {
            while (!isEmpty() && precedence(exp[i]) <= precedence(peek()))
            {
                result[k++] = pop();
            }
            push(exp[i]);
        }
    }

    // Pop all the operators from the stack
    while (!isEmpty())
    {
        result[k++] = pop();
    }

    result[k] = '\0'; // Null-terminate the postfix expression
    printf("Postfix expression: %s\n", result);
}

int main()
{
    char exp[] = "1+2-3*4/5";
    infixToPostfix(exp);
    return 0;
}