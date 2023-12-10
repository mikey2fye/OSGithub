// list/list.h
// 
// Interface definition for linked list.
//
// <Author>

#include <stdbool.h>

typedef struct block {
    int pid;   // pid
	int start;
  int end;
}block_t;

/* Defines the node structure. Each node contains its element, and points to the
 * next node in the list. The last element in the list should have NULL as its
 * next pointer. */
typedef struct node {
  block_t *blk;
	struct node *next;
}node_t;

/* Defines the list structure, which simply points to the first node in the
 * list. */
struct list {
	node_t *head;
};
typedef struct list list_t;

/* Functions for allocating and freeing lists. By using only these functions,
 * the user should be able to allocate and free all the memory required for
 * this linked list library. */
list_t *list_alloc();
node_t *node_alloc(block_t *blk);

void list_free(list_t *l);

/* Prints the list in some format. */
void list_print(list_t *l);

/* Returns the length of the list. */
int list_length(list_t *l);

/* Methods for adding to the list. */
void list_add_to_back(list_t *l, block_t *blk);
void list_add_to_front(list_t *l, block_t *blk);
void list_add_at_index(list_t *l, block_t *blk, int index);
void list_remove_node(list_t *l, node_t *node);
void list_add_ascending_by_address(list_t *l, block_t *blk);
void list_add_ascending_by_blocksize(list_t *l, block_t *blk);
void list_add_descending_by_blocksize(list_t *l, block_t *blk);

/* Methods for removing from the list. Returns the removed element. */
block_t* list_remove_from_back(list_t *l);
block_t* list_remove_from_front(list_t *l);
block_t* list_remove_at_index(list_t *l, int index);

/* Checks to see if block of Size exists in the list. */
bool list_is_in(list_t *l, block_t *blk);

/* Checks to see if block of Size or greater exists in the list. */
bool list_is_in_by_size(list_t *l, int Size);
                   
/* Checks to see if pid of block exists in the list. */
bool list_is_in_by_pid(list_t *l, int pid);

/* Returns the element at location index. */
block_t* list_get_elem_at(list_t *l, int index);

/* Returns the index at which the given block of Size appears. */
int list_get_index_of(list_t *l, block_t * blk);

/* Returns the index at which the given block of Size appears. */
int list_get_index_of_by_Size(list_t *l, int Size);
                   
/* Returns the index at which the pid appears. */
int list_get_index_of_by_Pid(list_t *l, int pid);

/*return element in front or NULL if empty */
block_t* list_get_from_front(list_t *l);

/* compare if two blocks are equal */
bool compareBlks(block_t* a, block_t *b);

/* join adjacent nodes who blocks are physically next to each other */
void list_coalese_nodes(list_t *l);
