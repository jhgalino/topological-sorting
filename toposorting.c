#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node Node;
struct node {
  int succ;
  Node *next;
};

void set_initial_array(int count[], int n, Node *list[]);

void set_initial_array(int count[], int n, Node *list[]) {
  for (int i = 0; i < n; i++) {
    count[i] = 0;
    list[i] = NULL;
  }
}

int main() {
  int n, j, k;
  char string[32];
  scanf("%d\n", &n);
  int count[n];
  Node *list[n];
  set_initial_array(count, n, list); // fill count with 0 and list with NULL

  // store pairs in count and list
  while (sscanf(fgets(string, 32, stdin), "%d %d", &j, &k)) {
    if (j == 0 && k == 0) {
      break;
    } else {
      count[k - 1]++;
      if (list[j - 1] != NULL) {
        Node *head = malloc(sizeof(Node));
        head->succ = k;
        head->next = list[j - 1];
        list[j - 1] = head;
      } else {
        Node *head = malloc(sizeof(Node));
        head->succ = k;
        head->next = NULL;
        list[j - 1] = head;
      }
    }
  }

  // initialize queue, start is front of queue, end is end of queue
  int previous = 0, start, end;
  for (int i = 0; i < n; i++) {
    if (count[i] == 0) {
      if (previous == 0) {
        start = i + 1;
        previous = i + 1;
      } else {
        count[previous - 1] = i + 1;
        previous = i + 1;
        end = i + 1;
      }
    }
  }

  // output generation
  while (true) {
    Node qlink;
    if (list[start - 1] != NULL) {
      qlink = *list[start - 1];
    } else {
      for (int i = 0; i < n; i++) {
        if (count[i] == 0) {
          start = i + 1;
          qlink = *list[i];
        }
      }
    }
    printf("%d\n", start);
    while (true) { // look through successors
      count[qlink.succ - 1]--;
      if (count[qlink.succ - 1] == 0) {
        count[end - 1] = qlink.succ;
        end = qlink.succ;
      }
      if (qlink.next != NULL) {
        qlink = *qlink.next;
      } else {
        break;
      }
    }
    start = count[start - 1];
    if (start == 0) {
      break;
    }
  }
}