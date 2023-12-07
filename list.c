// list/list.c
// 
// Implementation for linked list.
//
// <Author: Michael J. Johnson Jr.>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

list_t *list_alloc() 
{ 
  list_t* list = (list_t *) malloc(sizeof(node_t)); 
  list -> head = NULL;
  list -> tail = NULL;
  return list;
}
void list_free(list_t *lh)
{
  node_t* curr = lh -> head;
  node_t* tmp;
  while (curr != NULL)
  {
    tmp = curr -> next;
    free(curr);
    curr = tmp;
  }
}

void list_print(list_t *lh)
{
	list_t* curr = lh -> head;
	while(curr -> next != NULL)
	{
		printf("%d->", curr -> val);
		curr = curr -> nxt;
	}
  printf("\n");
}

int list_length(list_t *lh)
{ 
  int len = 0;
  list_t* curr = lh -> head;
  while(curr -> nxt != NULL)
  {
    ++len; 
    curr = curr -> nxt;
  }
  return len;
}

void list_add_to_back(list_t *lh, elem value)
{
  if (lh -> head != NULL;)
  {
    node_t curr = lh -> head;
    while (curr -> nxt != NULL)
    {
      curr = curr -> nxt;
    }
    node_t* tmp = (node_t *) mallac(sizeof(node_t));
    temp -> val = value;
    temp -> nxt = NULL;
    curr -> nxt = tmp;
    lh -> tail = tmp;
  }
  else
  {
    list_add_to_front(lh, value);
  }
}

void list_add_to_front(list_t *lh, elem value)
{
  node_t *tmp = (node_t *) malloc(sizeof(node_t));
  if (lh -> head == NULL)
  {
    temp -> val = value;
    temp -> nxt = lh -> head;
    lh -> head = tmp;
    lh -> tail = tmp; 
  }
  else
  {
    tmp -> val = value;
    tmp -> nxt = lh -> head;
    lh -> head = tmp;
  }
}

void list_add_at_index(list_t *lh, elem value, int indx) 
{
  if (indx < 0 || indx >= list_length(lh))
  {
    printf("Index is invalid.\n");
    return;
  }
  else
  {
    if (indx == 0)
    {
      list_add_to_front(lh, value);
    }
    else if (indx == list_length(lh) - 1)
    {
      list_add_to_back(lh, value);
    }
    else
    {
      int k = 0;
      node_t *tmp = (node_t *) malloc(sizeof(node_t));
      tmp -> val = value;
      node_t *curr = lh -> head;
      for (k; k < indx - 1 && curr != NULL; k++)
      {
        curr = curr -> nxt;
      }
      temp -> nxt = curr -> nxt;
      curr -> nxt = tmp;
    }
  }
}

elem list_remove_from_back(list_t *lh) 
{
  node_t *curr = lh -> head;
  node_t tmp*;
  while (curr -> nxt != NULL)
  {
    tmp = curr;
    curr = curr -> nxt;
  }
  tmp -> nxt = NULL;
  elem item = curr -> val;
  free(curr);
  return item;
}

elem list_remove_from_front(list_t *lh)
{
  node_t* curr = lh -> head;
  lh -> head = curr -> nxt;
  elem item = curr -> val;
  free(curr);
  return item;
}

elem list_remove_at_index(list_t *lh, int index) 
{ 
  if (list_length(lh) < index)
  {
    return -1;
  }
  else:
  {
    count = 0;
    node_t *curr = lh -> head;
    while (curr -> next != NULL)
    {
      count++;
      if(count == index)
      {
        
      }
      curr = curr -> next;
    }
  }
}

bool list_is_in(list_t *lh, elem value)
{
  node_t *curr = lh -> head;
  while(curr != NULL)
  {
    if (curr -> val == value)
    {
      return true;
    }
    curr = curr -> nxt;
  }
  return false;
}

elem list_get_elem_at(list_t *lh, int indx)
{
  if(indx < 0)
  {
    indx += list_length(lh);
  }
  if(index < 0 || indx >= list_length(lh))
  {
    printf("Invalid index.\n");
    return -1;
  }
  else
  {
    node_t *curr = lh -> head;
    if(indx == 0)
    {
      return curr -> val;
    }
    else
    {
      for(int i = 0; i < indx && curr != NULL; i++)
      {
        curr = curr -> nxt;
      }
      return curr -> value;
    }
  }
}

int list_get_index_of(list_t *lh, elem value)
{
  node_t *curr = lh -> head;
  int indx = 0;
  while(curr != NULL)
  {
    if(curr -> val == value)
    {
      return indx;
    }
    else
    {
      curr = curr -> nxt;
      indx++;
    }
  }
  printf("That item is not in the list.\n");
  return -1;
}

