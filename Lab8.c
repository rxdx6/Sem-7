#include <stdio.h>
#include <stdlib.h>

typedef struct tbtnode
{
     char data;
     int rbit, lbit;
     struct tbtnode *rightc, *leftc;
} tbtnode;

tbtnode *createNode(char data)
{
     tbtnode *node = (tbtnode *)malloc(sizeof(tbtnode));
     node->data = data;
     node->rbit = 1;
     node->lbit = 1;
     node->rightc = node->leftc = NULL;
     return node;
}

void create(tbtnode *head)
{
     tbtnode *root, *temp, *curr;
     char ch1, ch;
     int flag;

     root = createNode('A'); // Initial root node
     head->lbit = 1;
     root->leftc = root->rightc = head;
     root->lbit = root->rbit = 0;
     head->leftc = root;

     do
     {
          flag = 0;
          temp = root;

          curr = createNode(' '); // Allocate new node
          printf("Enter data for new node: ");
          scanf(" %c", &curr->data);
          curr->lbit = curr->rbit = 0;

          while (flag == 0)
          {
               printf("Enter choice (l/r): ");
               scanf(" %c", &ch1);

               if (ch1 == 'l')
               {
                    if (temp->lbit == 0)
                    {
                         curr->rightc = temp;
                         curr->leftc = temp->leftc;
                         temp->leftc = curr;
                         temp->lbit = 1;
                         flag = 1;
                    }
                    else
                    {
                         temp = temp->leftc;
                    }
               }
               else if (ch1 == 'r')
               {
                    if (temp->rbit == 0)
                    {
                         curr->leftc = temp;
                         curr->rightc = temp->rightc;
                         temp->rightc = curr;
                         temp->rbit = 1;
                         flag = 1;
                    }
                    else
                    {
                         temp = temp->rightc;
                    }
               }
          }
          printf("Continue (y/n)? ");
          scanf(" %c", &ch);
     } while (ch == 'y');
}

tbtnode *inordersucc(tbtnode *temp)
{
     tbtnode *x = temp->rightc;
     if (temp->rbit == 1)
     {
          while (x->lbit == 1)
          {
               x = x->leftc;
          }
     }
     return x;
}

void inorder(tbtnode *head)
{
     tbtnode *temp = head;
     while (1)
     {
          temp = inordersucc(temp);
          if (temp == head)
               break;
          printf("%c ", temp->data);
     }
     printf("\n");
}

void preorder(tbtnode *head)
{
     tbtnode *temp = head->leftc;
     while (temp != head)
     {
          printf("%c ", temp->data);
          while (temp->lbit != 0)
          {
               temp = temp->leftc;
               printf("%c ", temp->data);
          }
          while (temp->rbit == 0)
          {
               temp = temp->rightc;
          }
          temp = temp->rightc;
     }
     printf("\n");
}

int main()
{
     tbtnode *head = (tbtnode *)malloc(sizeof(tbtnode));
     head->rbit = 1;
     head->lbit = 0;
     head->leftc = head->rightc = head;

     create(head);
     printf("Inorder Traversal: ");
     inorder(head);

     printf("Preorder Traversal: ");
     preorder(head);

     return 0;
}