//workHeap.h

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct heap_node_struct{
  int priority;
  int base_prior;
  int pid_val;
}h_node;

void insertNode(int priority,int pid);
void delNode(int pid);
void editNode(int pid, int priority);