#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node Node;
struct node {
  int SUCC;
  Node *NEXT;
};

void TOPOLOGICAL_SORT(int n);

int main() {
  int n;
  scanf("%d\n", &n);
  TOPOLOGICAL_SORT(n);
}

void TOPOLOGICAL_SORT(int n) {
  int COUNT[n];
  Node *LIST[n];

  // initializations
  for (int k = 0; k < n; k++) {
    COUNT[k] = 0;
    LIST[k] = NULL;
  }
  int m = n;

  // input
  char string[1028];
  int j, k;
  sscanf(fgets(string, 1028, stdin), "%d %d", &j, &k);
  while (j != 0) {
    COUNT[k - 1]++;
    Node *node = malloc(sizeof(Node));
    node->SUCC = k;
    node->NEXT = LIST[j - 1];
    LIST[j - 1] = node;
    sscanf(fgets(string, 1028, stdin), "%d %d", &j, &k);
  }

  // initialize output queue
  int front = 0, rear;
  for (int i = 0; i < n; i++) {
    if (COUNT[i] == 0) {
      if (front == 0) {
        front = i + 1;
        rear = i + 1;
      } else {
        COUNT[rear - 1] = i + 1;
        rear = i + 1;
      }
    }
  }

  // Output objects
  Node *node;
  while (front != 0) {
    printf("%d", front);
    if (m > 1) {
      printf(" ");
    }
    m--;
    node = LIST[front - 1];
    while (node != NULL) {
      k = node->SUCC;
      COUNT[k - 1]--;
      if (COUNT[k - 1] == 0) {
        COUNT[rear - 1] = k;
        rear = k;
      }
      node = node->NEXT;
    }
    front = COUNT[front - 1];
  }
  // Check for loops
  if (m > 0) {
    printf("%s", "Some objects comprise a loop");
  }
}