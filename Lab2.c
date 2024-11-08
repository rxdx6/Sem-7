#include <stdio.h>

struct student
{
    int rollNumber;
    char name[20];
    char division;
};

void accept(struct student s[], int n)
{
    printf("Enter student information for %d students\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter Roll Number: ");
        scanf("%d", &s[i].rollNumber);

        printf("Enter Name: ");
        scanf("%s", s[i].name);

        printf("Enter Division: ");
        scanf(" %c", &s[i].division);
    }
}

void bubbleSort(struct student s[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (s[j].rollNumber > s[j + 1].rollNumber)
            {
                struct student temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
}

void selectionSort(struct student s[], int n)
{
    int min;
    struct student temp;
    for (int i = 0; i < n - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (s[j].rollNumber < s[min].rollNumber)
            {
                min = j;
            }
        }
        if (min != i)
        {
            temp = s[i];
            s[i] = s[min];
            s[min] = temp;
        }
    }
}

void insertionSort(struct student s[], int n)
{
    struct student key;
    int j;
    for (int i = 1; i < n; i++)
    {
        key = s[i];
        j = i - 1;
        while (j >= 0 && s[j].rollNumber > key.rollNumber)
        {
            s[j + 1] = s[j];
            j = j - 1;
        }
        s[j + 1] = key;
    }
}

void display(struct student s[], int n)
{
    printf("\nStudent Information \n");
    printf("RN \t Name \t Division \n");
    for (int i = 0; i < n; i++)
    {
        printf("%d \t %s \t %c \n", s[i].rollNumber, s[i].name, s[i].division);
    }
}

int main()
{
    int n;
    int choice;

    printf("Enter number of students: ");
    scanf("%d", &n);
    struct student s[n];

    do
    {
        printf("\nChoose sorting algorithm:\n");
        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            accept(s, n);
            display(s, n);
            bubbleSort(s, n);
            printf("\nAfter bubble sort:\n");
            display(s, n);
            break;
        case 2:
            accept(s, n);
            display(s, n);
            selectionSort(s, n);
            printf("\nAfter selection sort:\n");
            display(s, n);
            break;
        case 3:
            accept(s, n);
            display(s, n);
            insertionSort(s, n);
            printf("\nAfter insertion sort:\n");
            display(s, n);
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    } while (choice != 4);

    return 0;
}
