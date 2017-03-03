//workHeap.h
// Author : Sunny M
// University of Bristol

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct heap_node_struct{
  int priority;
  int base_prior;
  int pid_val;
}h_node;
