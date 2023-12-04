#include <stdio.h>
#include "backend.h"

/****************************************
Implement Breadth-First Search on the graph constructed in "backend.c" and
use it in the find_path() below.

You can access functions and data structures constructed in "backend.c" via
"backend.h"
*****************************************/

int parent[N];

struct queue
{
    struct node* front;
    struct node* rear;
};

void qinit(struct queue* q)
{
    q->front = NULL;
    q->rear = NULL;
}

void pop(struct queue* q)
{
    if (q->front == NULL)
        return;
    struct node* n = q->front;
    if (q->front == q->rear)
        q->rear = NULL;
    q->front = n->next;
    free_node(n);
    return;
}

void push(struct queue* q,int i)
{
    struct node* n = new_node();
    n->index = i;
    n->next = NULL;
    if (q->front == NULL) {
        q->front = n;
        q->front->next == NULL;
        q->rear = n;
        return;
    }
    q->rear->next = n;
    q->rear = n;
    return;
}

int empty(struct queue* q)
{
    return q->front == NULL;
}

int bfs(char start[5], char goal[5])
{
    char visited[N] = { 0, };
    int s = search_index(start);
    int j = search_index(goal);
    if (s == j)
        return 0;
    parent[s] = -1;
    struct queue q;
    qinit(&q);
    push(&q, s);
    while (!empty(&q)) {
        int cur = q.front->index;
        pop(&q);
        struct node* n = adj_list[cur];
        while (n != NULL) {
            int next = n->index;
            if (!visited[next]) {
                push(&q, next);
                visited[next] = 1;
                parent[next] = cur;
                if (next == j)
                    return 1;
            }
            n = n->next;
        }
    }
    return 0;
}

void find_path(char* start, char* goal)
{
  int i,j,k,l;
  
  i=search_index(start);
  j=search_index(goal);

  if (i<0) {
    printf("Sorry. ");
    print_five_chars(start);
    printf(" is not in the dicitonary.");
  }
  else if (j<0) {
    printf("Sorry. ");
    print_five_chars(goal);
    printf(" is not in the dicitonary.");
  }
  else {
      if (!bfs(start, goal)) {
          printf("Sorry. There is no path from ");
          print_word(i);
          printf(" to ");
          print_word(j);
          printf(".\n");
          return;
      }
      if (bfs(start, goal)) {
          int path[N] = { 0, };
          int k = 0; /*path length*/
          int p = j;
          while (p != i) {
              k++;
              p = parent[p];
          }
          int c = k;
          p = j;
          while (p != i) {
              path[c--] = p;
              p = parent[p];
          }
          path[0] = i;
          for (c = 0; c <= k; c++) {
              if (c >= 10)
                  printf("%13d ", c);
              else
                  printf("%11d ", c);
              print_word(path[c]);
              printf("\n");
          }
          return;
      }
  }
}
  
