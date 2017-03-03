//workHeap.c
// Author : Sunny M
// University of Bristol
// 2017
 #include "workHeap.h"

 /*
      A heap would have a fixed size of 300 elements / processes
      have a function that gives the left and right nodes (for the last values ka case)

      have functions
      insertNode()
      delNode()
      heapify()
      extractMax()
      editNode()

 */


int  HEAP_SIZE;
#define ARRAY_SIZE 300;
h_node heap[ARRAY_SIZE];


void initHeap()
{
  HEAP_SIZE = ARRAY_SIZE / 2;
  for(int i=0;i<ARRAY_SIZE;i++) // initialsies ALL of the elements in the heap so there's no problem with getIndexOfUnused
  {
    heap[i]->pid_val = -1;
    heap[i]->priority = 0;
    heap[i]->base_prior = 0;
  }
}

int getLeft(int this)
{
  if(2*this < HEAP_SIZE/2){return 2*this;}
  else return this;
}

int getRight(int this)
{
  if((2*this)+1 < HEAP_SIZE/2){return ((2*this)+1);}
  else return this;
}

int getParent(int this)
{
  return this/2;
}

void swapNodes(int a, int b) // swaps nodes
{
  h_node temp_node = heap[a];
  heap[a] = heap[b];
  heap[b] = temp_node;
}

int getIndexOfUnused()
{
  for(int i= 0; i <HEAP_SIZE;i++)
  {
    if(heap[i]->pid_val == -1 ) {return i;}
  }
  HEAP_SIZE++; // Increases heapsize and returns the value it just created
  return HEAP_SIZE-1;
}

int getIndexFromPID(int pid)
{
  for(int i=0;i<HEAP_SIZE;i++)
  {
    if(heap[i]->pid_val == pid) { return i;}
  }
  {insertNode(0,pid); // in the case the pid isn't actually part of the heap, it adds a new node
  return getIndexFromPID(pid);}
}

void insertNode(int priority,int pid)
{
  int insert_point = getIndexOfUnused();
  heap[insert_point]->pid_val = pid;
  heap[insert_point]->priority=priority;
}

void delNode(int pid)
{
  int del_point = getIndexFromPID(pid);
  heap[del_point]->pid_val = -1;
  heap[del_point]->priority = 0;
  heap[del_point]->base_prior = 0;
}

void editNode(int pid, int priority)
{
  int edit_point = getIndexFromPID(pid);
  heap[edit_point]->priority = priority;
}

int extractMax() // TODO Add heapify here? with swap.
{
  h_node max = heap[0];
  int pid_to_return = max->pid_val;
  delNode(max->pid_val);
  return pid_to_return;
}

void setBasePrior(int pid,int b_priority)
{
  int edit_point = getNodeFromPID(pid);
  heap[edit_point]->base_prior = b_priority;
}

void heapify(int sort_point_pid)
{
  int largestVal = 0;
  int largestPos = 0;

  int sort_point = getIndexFromPID(sort_point_pid);
  int left_child = getLeft(sort_point);
  int right_child = getRight(sort_point);


  int p_left = heap[left_child]->priority;
  int p_right = heap[right_child]->priority;
  int p_parent = heap[sort_point]->priority;


  if(left_child < HEAP_SIZE && p_left > p_parent) {
      largestPos = left_child;
      largestVal = p_left;
  }
    else
    {
      largestVal = p_parent;
      largestPos = sort_point;
    }
  if(right_child < HEAP_SIZE && p_right > largestVal)
  {
    largestVal = p_right;
    largestPos = right_child;
  }
  if(largestPos != sort_point)
  {
    swapNodes(largestPos,sort_point);
    heapify(largestPos);
  }
  // TODO : Basic Values for priorities.
}
