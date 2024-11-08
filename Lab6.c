#include <stdio.h>
#include <stdlib.h>

struct Node
{
     int data;
     struct Node *left;
     struct Node *right;
};

// Creation of binary tree
struct Node *createNode(int data)
{
     struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
     newNode->data = data;
     newNode->left = newNode->right = NULL;
     return newNode;
}

struct Node *insertNode(struct Node *root, int data)
{
     if (root == NULL)
     {
          return createNode(data);
     }
     if (data < root->data)
     {
          root->left = insertNode(root->left, data);
     }
     else if (data > root->data)
     {
          root->right = insertNode(root->right, data);
     }
     return root;
}

// Recursive Inorder Traversal
void inorderRecursive(struct Node *root)
{
     if (root == NULL)
          return;
     inorderRecursive(root->left);
     printf("%d ", root->data);
     inorderRecursive(root->right);
}

// Recursive Preorder Traversal
void preorderRecursive(struct Node *root)
{
     if (root == NULL)
          return;
     printf("%d ", root->data);
     preorderRecursive(root->left);
     preorderRecursive(root->right);
}

// Recursive Postorder Traversal
void postorderRecursive(struct Node *root)
{
     if (root == NULL)
          return;
     postorderRecursive(root->left);
     postorderRecursive(root->right);
     printf("%d ", root->data);
}

// Non-recursive Inorder Traversal
void inorderNonRecursive(struct Node *root)
{
     struct Node *stack[100];
     int top = -1;
     struct Node *curr = root;
     while (curr != NULL || top != -1)
     {
          while (curr != NULL)
          {
               stack[++top] = curr;
               curr = curr->left;
          }
          curr = stack[top--];
          printf("%d ", curr->data);
          curr = curr->right;
     }
}

// Non-recursive Preorder Traversal
void preorderNonRecursive(struct Node *root)
{
     struct Node *stack[100];
     int top = -1;
     if (root != NULL)
          stack[++top] = root;
     while (top != -1)
     {
          struct Node *curr = stack[top--];
          printf("%d ", curr->data);
          if (curr->right)
               stack[++top] = curr->right;
          if (curr->left)
               stack[++top] = curr->left;
     }
}

// Non-recursive Postorder Traversal
void postorderNonRecursive(struct Node *root)
{
     struct Node *stack1[100], *stack2[100];
     int top1 = -1, top2 = -1;
     if (root != NULL)
          stack1[++top1] = root;
     while (top1 != -1)
     {
          struct Node *curr = stack1[top1--];
          stack2[++top2] = curr;
          if (curr->left)
               stack1[++top1] = curr->left;
          if (curr->right)
               stack1[++top1] = curr->right;
     }
     while (top2 != -1)
     {
          printf("%d ", stack2[top2--]->data);
     }
}

int main()
{
     struct Node *root = NULL;
     root = insertNode(root, 40);
     insertNode(root, 30);
     insertNode(root, 60);
     insertNode(root, 20);
     insertNode(root, 35);
     insertNode(root, 50);
     insertNode(root, 70);

     printf("Recursive Inorder: ");
     inorderRecursive(root);
     printf("\nNon-recursive Inorder: ");
     inorderNonRecursive(root);

     printf("\nRecursive Preorder: ");
     preorderRecursive(root);
     printf("\nNon-recursive Preorder: ");
     preorderNonRecursive(root);

     printf("\nRecursive Postorder: ");
     postorderRecursive(root);
     printf("\nNon-recursive Postorder: ");
     postorderNonRecursive(root);

     return 0;
}
