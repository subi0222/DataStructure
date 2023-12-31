#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend-bst.h"
#include "memory.h"

void print_name(struct record *);
void print_number(struct record *);

// comparison function for records
int compare(char key[3], struct record *);

// data
struct record * data = NULL; // Initially NULL.

/***********************
Address Book by binary search tree
**************************/

void init()
{
  init_pool();
}


void search(char name[3])  
{
  struct record *r; // Pointer to record being compared.
                    //data or left/right field of a node.
  int result;
  r=data;

  while (r!=NULL) {
    if ((result=compare(name,r))<0)
      r=r->left;
    else if (result==0) {
      print_name(r);
      printf(" : ");
      print_number(r);
      printf(" was found.\n");
      return;
    }
    else // case >0
      r=r->right;
  }
  printf("Couldn't find the name.\n");
}


void add(char *name, char *number)
{
    struct record** t = &data;
    struct record* r = data;
    if (data == NULL) {
        data = new_node();
        data->name[0] = name[0]; 
        data->name[1] = name[1]; 
        data->name[2] = name[2]; 
        data->number[0] = number[0]; 
        data->number[1] = number[1];
        data->number[2] = number[2];
        data->number[3] = number[3];
        data->left = NULL;
        data->right = NULL;
        printf("The name was successfully added!\n"); 
        return;
    }
    while (r != NULL) {
        if (compare(name, r) <= 0) {
            t = &(r->left);
            r = r->left;
        }
        else {
            t = &(r->right);
            r = r->right;
        }
    }
    struct record* newOne = new_node();
    if (newOne == NULL) {
        printf("Can't add. The pool is empty!\n");
        return;
    }
    newOne->name[0] = name[0];
    newOne->name[1] = name[1];
    newOne->name[2] = name[2];
    newOne->number[0] = number[0];
    newOne->number[1] = number[1];
    newOne->number[2] = number[2];
    newOne->number[3] = number[3];
    newOne->left = NULL;
    newOne->right = NULL;
    *t = newOne;
    printf("The name was successfully added!\n");
    return;
  // Messages to print
  //  printf("Can't add.  The pool is empty!\n");
  //  printf("The name was successfully added!\n");
}


// The most complicated.
void delete(char name[3])
{
  // Messages to print
  //  printf("The name was deleted.\n");  
  //  printf("Couldn't find the name.\n");
}


/* Just a wrapper of strncmp().
Regard strncmp(a,b) as a-b.
Negative value if key is less than r.
​0​ if key and r are equal.
Positive value if key is greater than r. */
int compare(char key[3], struct record *r)
{
    return strncmp(key, r->name, 3);
}


void print_data(char * s, int n)
{
  int i;
  for (i=0; i<n; i++)
    putchar(s[i]);
}

void print_name(struct record *r)
{
  print_data(r->name, 3);
}

void print_number(struct record *r)
{
  print_data(r->number, 4);
}

void print_inorder(struct record *t)
{
    if (t == NULL)
        return;
    print_inorder(t->left);
    print_name(t);
    printf(" : ");
    print_number(t);
    printf("\n");
    print_inorder(t->right);
}

void print_list()  
{
  print_inorder(data);
}


// returns the height of the BST.
int height(struct record *t)
{
    if (t == NULL)
        return -1;
    int r = height(t->right);
    int l = height(t->left);
    return (r >= l) ? r + 1 : l + 1;
}

void print_height()  
{
  printf("The Address Book BST's height is %d.\n", height(data));
}
