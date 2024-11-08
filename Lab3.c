#include <stdio.h>

typedef struct
{
     int value;
     int row;
     int column;
} SparseElement;

void simpleTranspose(SparseElement elements[], int totalElements)
{
     for (int i = 0; i < totalElements; i++)
     {
          int tempRow = elements[i].row;
          elements[i].row = elements[i].column;
          elements[i].column = tempRow;
     }
}

void fastTranspose(SparseElement elements[], int totalElements)
{
     SparseElement transposed[totalElements];
     int rowCounts[100] = {0}; // This line is removed
     int rowOffsets[100];

     // Count the number of elements in each row (removed initialization)
     for (int i = 0; i < totalElements; i++)
     {
          rowCounts[elements[i].row]++;
     }

     // Compute the starting offset for each row
     rowOffsets[0] = 0;
     for (int i = 1; i < 100; i++)
     {
          rowOffsets[i] = rowOffsets[i - 1] + rowCounts[i - 1];
     }

     // Fill the transposed array with elements in their new positions
     for (int i = 0; i < totalElements; i++)
     {
          int j = elements[i].row;
          transposed[rowOffsets[j]] = elements[i];
          rowOffsets[j]++;
     }

     // Copy the transposed array back to the original elements array
     for (int i = 0; i < totalElements; i++)
     {
          elements[i] = transposed[i];
     }
}

int main()
{
     int rows, columns, maxElements;
     printf("Enter the number of rows and columns: ");
     scanf("%d %d", &rows, &columns);

     printf("Enter the maximum number of non-zero elements: ");
     scanf("%d", &maxElements);

     SparseElement elements[maxElements];
     int totalElements = 0;

     printf("Enter the sparse matrix elements (row, column, value):\n");
     for (int i = 0; i < maxElements; i++)
     {
          printf("Element %d: ", i + 1);
          scanf("%d %d %d", &elements[i].row, &elements[i].column, &elements[i].value);
          if (elements[i].row == -1 && elements[i].column == -1 && elements[i].value == -1)
          {
               break;
          }
          totalElements++;
     }

     printf("\nSparse Matrix Representation:\n");
     for (int i = 0; i < totalElements; i++)
     {
          printf("Row: %d, Column: %d, Value: %d\n", elements[i].row, elements[i].column, elements[i].value);
     }

     int matrix[rows][columns];
     for (int i = 0; i < rows; i++)
     {
          for (int j = 0; j < columns; j++)
          {
               matrix[i][j] = 0;
          }
     }

     for (int i = 0; i < totalElements; i++)
     {
          matrix[elements[i].row][elements[i].column] = elements[i].value;
     }

     printf("\nMatrix:\n");
     for (int i = 0; i < rows; i++)
     {
          for (int j = 0; j < columns; j++)
          {
               printf("%d ", matrix[i][j]);
          }
          printf("\n");
     }

     simpleTranspose(elements, totalElements);

     printf("\nSparse Matrix after Simple Transpose:\n");
     for (int i = 0; i < totalElements; i++)
     {
          printf("Row: %d, Column: %d, Value: %d\n", elements[i].row, elements[i].column, elements[i].value);
     }

     fastTranspose(elements, totalElements);

     printf("\nSparse Matrix after Fast Transpose:\n");
     for (int i = 0; i < totalElements; i++)
     {
          printf("Row: %d, Column: %d, Value: %d\n", elements[i].row, elements[i].column, elements[i].value);
     }

     return 0;
}