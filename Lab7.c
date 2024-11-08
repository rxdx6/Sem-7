#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
     char keyword[50];
     char meaning[100];
     struct Node *left;
     struct Node *right;
};

// Create a new node
struct Node *createNode(char *keyword, char *meaning)
{
     struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
     strcpy(newNode->keyword, keyword);
     strcpy(newNode->meaning, meaning);
     newNode->left = newNode->right = NULL;
     return newNode;
}

// Insert a keyword
struct Node *insertNode(struct Node *root, char *keyword, char *meaning)
{
     if (root == NULL)
     {
          return createNode(keyword, meaning);
     }    
     if (strcmp(keyword, root->keyword) < 0)
     {
          root->left = insertNode(root->left, keyword, meaning);
     }
     else if (strcmp(keyword, root->keyword) > 0)
     {
          root->right = insertNode(root->right, keyword, meaning);
     }
     return root;
}

// Find the minimum value node
struct Node *minValueNode(struct Node *node)
{
     struct Node *current = node;
     while (current && current->left != NULL)
          current = current->left;
     return current;
}

// Delete a keyword
struct Node *deleteNode(struct Node *root, char *keyword)
{
     if (root == NULL)
          return root;

     if (strcmp(keyword, root->keyword) < 0)
          root->left = deleteNode(root->left, keyword);
     else if (strcmp(keyword, root->keyword) > 0)
          root->right = deleteNode(root->right, keyword);
     else
     {
          if (root->left == NULL)
          {
               struct Node *temp = root->right;
               free(root);
               return temp;
          }
          else if (root->right == NULL)
          {
               struct Node *temp = root->left;
               free(root);
               return temp;
          }
          struct Node *temp = minValueNode(root->right);
          strcpy(root->keyword, temp->keyword);
          strcpy(root->meaning, temp->meaning);
          root->right = deleteNode(root->right, temp->keyword);
     }
     return root;
}

// Create mirror image
struct Node *mirror(struct Node *root)
{
     if (root == NULL)
          return NULL;
     struct Node *temp = root->left;
     root->left = root->right;
     root->right = temp;
     mirror(root->left);
     mirror(root->right);
     return root;
}

// Level-wise display
void printLevel(struct Node *root, int level)
{
     if (root == NULL)
          return;
     if (level == 1)
          printf("%s: %s\n", root->keyword, root->meaning);
     else if (level > 1)
     {
          printLevel(root->left, level - 1);
          printLevel(root->right, level - 1);
     }
}

int height(struct Node *node)
{
     if (node == NULL)
          return 0;
     int lHeight = height(node->left);
     int rHeight = height(node->right);
     return (lHeight > rHeight) ? (lHeight + 1) : (rHeight + 1);
}

void printLevelOrder(struct Node *root)
{
     int h = height(root);
     for (int i = 1; i <= h; i++)
     {
          printLevel(root, i);
     }
}

// Copy tree
struct Node *copyTree(struct Node *root)
{
     if (root == NULL)
          return NULL;
     struct Node *newNode = createNode(root->keyword, root->meaning);
     newNode->left = copyTree(root->left);
     newNode->right = copyTree(root->right);
     return newNode;
}

int main()
{
     struct Node *root = NULL;
     root = insertNode(root, "apple", "A fruit");
     insertNode(root, "banana", "A yellow fruit");
     insertNode(root, "cat", "A small animal");
     insertNode(root, "dog", "A loyal animal");

     printf("Dictionary:\n");
     printLevelOrder(root);

     root = deleteNode(root, "banana");
     printf("\nAfter deletion:\n");
     printLevelOrder(root);

     printf("\nMirror image:\n");
     mirror(root);
     printLevelOrder(root);

     printf("\nCopy of the tree:\n");
     struct Node *copy = copyTree(root);
     printLevelOrder(copy);

     return 0;
}