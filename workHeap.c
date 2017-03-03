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
#define ARRAY_SIZE 300
h_node heap[ARRAY_SIZE];
/////////////////////////////////////
void initHeap(); // Creates the heap structure + initialises the struct created in workHeap.h
void heapify(int sort_point_pid); // Main heapsort function, see readme for reference
int getLeft(int this); // Get's the left child index
int getRight(int this); // Get's the right child index
int getParent(int this); // Get's the parent's index
void swapNodes(int a, int b); // swaps nodes
int getIndexOfUnused(); // gets the index of the last unused part of the heap (this is assuming the heap has a fixed size before adding process)
  // I.e it does not dynamically increase the heap size unless it reaches a size of HEAP_SIZE/2 ~(150 for now)
int getIndexFromPID(int pid); // gets the index of struct from the pid value inside it
void insertNode(int priority,int pid); // "inserts" a node in the heap, actual heap size increase is in getIndexOfUnused()
void delNode(int pid); // "deletes" a node, TODO: maybe call heapify after deleting a node to maintain heap property
void editNode(int pid, int priority); // Changes the values (priority) in a heap struct
int extractMax(); // Get's the max , it also calls heapify
void setBasePrior(int pid,int b_priority); // Specific to my implementation-use for this, can be removed / ignored
void heapify(int sort_point_pid); // Main sortting yo.
////////////////////////////////////////

void main()
{
  initHeap();
}

void initHeap()
{
  HEAP_SIZE = ARRAY_SIZE / 2;
  for(int i=0;i<ARRAY_SIZE;i++) // initialsies ALL of the elements in the heap so there's no problem with getIndexOfUnused
  {
    heap[i].pid_val = -1;
    heap[i].priority = 0;
    heap[i].base_prior = 0;
  }
}

int getLeft(int this)
{
  if(2*this < HEAP_SIZE){return 2*this;}
  else return this;
}

int getRight(int this)
{
  if((2*this)+1 < HEAP_SIZE){return ((2*this)+1);}
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
    if(heap[i].pid_val == -1 ) {return i;}
  }
  HEAP_SIZE++; // Increases heapsize and returns the value it just created
  return HEAP_SIZE-1;
}

int getIndexFromPID(int pid)
{
  for(int i=0;i<HEAP_SIZE;i++)
  {
    if(heap[i].pid_val == pid) { return i;}
  }
  {insertNode(0,pid); // in the case the pid isn't actually part of the heap, it adds a new node
  return getIndexFromPID(pid);}
}

void insertNode(int priority,int pid)
{
  int insert_point = getIndexOfUnused();
  heap[insert_point].pid_val = pid;
  heap[insert_point].priority=priority;
}

void delNode(int pid)
{
  int del_point = getIndexFromPID(pid);
  heap[del_point].pid_val = -1;
  heap[del_point].priority = 0;
  heap[del_point].base_prior = 0;
}

void editNode(int pid, int priority)
{
  int edit_point = getIndexFromPID(pid);
  heap[edit_point].priority = priority;
}

int extractMax()
{
  h_node max = heap[0];
  int pid_to_return = max.pid_val;
  delNode(max.pid_val);
  return pid_to_return;
}

void setBasePrior(int pid,int b_priority)
{
  int edit_point = getIndexFromPID(pid);
  heap[edit_point].base_prior = b_priority;
}

void heapify(int sort_point_pid)
{

  /*
    This would be much faster / easier with pointers to the values as opposed to always referencing the
    heap[] array,
    you could just make a h_node* left_child_ptr = heap[left_child] and use it forward, but since this project does not use / need malloc
    it's been skipped by just referencing the array[] constantly.
  */

  int largestVal = 0;
  int largestPos = 0;

  int sort_point = getIndexFromPID(sort_point_pid);
  int left_child = getLeft(sort_point);
  int right_child = getRight(sort_point);


  int p_left = heap[left_child].priority;
  int p_right = heap[right_child].priority;
  int p_parent = heap[sort_point].priority;


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

}
