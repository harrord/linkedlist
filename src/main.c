/*******************************************************************************
 * Copyright (c) 2021, Initialsoft, Inc.
 * All rights reserved.
 *
 * main : [description]
 *
 * filename : main.cc
 * author   : hunt978(hunt978@initialsoft.com)
 * create   : 2021-03-15 03:15:35 UTC
 * modified : 2021-03-17 16:24:15 UTC
\******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Headers
//
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////
// Typedefs & Constants
//
#define nullptr NULL

////////////////////////////////////////////////////////////////////////////////
// Inner Scope Objects
//
struct Node {
  uint32_t fid;
  uint32_t tid;

  struct Node* prev;
  struct Node* next;
};

/**
 * @brief      insert a node into list
 *
 *             there are 4 strains for the container :
 *
 *               1) from id and to id **CANNOT** be the same
 *               2) it should **NOT** hold duplicated node
 *               3) it should **NOT** hold circled link
 *               4) fan-out is allowed while fan-in is **NOT**.
 *
 * @param      head  The head
 * @param[in]  fid   The fid
 * @param[in]  tid   The tid
 *
 * @return     new head
 */
struct Node* insert_node(struct Node* head, uint32_t fid, uint32_t tid)
{
  // \TODO add your code here
  const int max = 1000;
  static int note[max];
  if ((tid == fid) || (tid == note[fid]) || (0 != note[tid]) || (0 != note[fid])){ 
      /* strain 1) || 2) || 3) || 4) */
    return head;
  } else {
    /*do nothing*/
  }
  if (nullptr == head) {
    struct Node* p = (Node*)malloc(sizeof(Node));
    if (nullptr == p) { return head; }
    p->fid = fid;
    p->tid = tid;
    p->prev = nullptr;
    p->next = nullptr;
    note[fid] = tid;
    return p;
  } else {
    struct Node* p_tracker = (Node*)malloc(sizeof(Node));
    if (nullptr == p_tracker) { return head; }
    p_tracker = head;
    while (nullptr != p_tracker->next) {
        p_tracker = p_tracker->next;
    }
    if (fid == p_tracker->tid) {
        struct Node* p = (Node*)malloc(sizeof(Node));
        if (nullptr == p) { return head; }
        p_tracker->next = p;
        p->prev = p_tracker;
        p->next = nullptr;
        p->fid = fid;
        p->tid = tid;
        note[fid] = tid;
        return head;
    } else {
        return head;
    }
  }
  return nullptr;
}

/**
 * @brief      remove a node from list
 *
 * @param      head  The head
 * @param[in]  fid   The fid
 * @param[in]  tid   The tid
 *
 * @return     new head
 */
struct Node* remove_node(struct Node* head, uint32_t fid, uint32_t tid)
{
  // \TODO add your code here
  if ((fid == head->fid) && (tid == head->tid)){    //head node
    head = head->next;
    if (nullptr == head) {
      return nullptr;
    } else {
      return head;
    }
  } else {
    //do nothing
  }
  struct Node *p = head->next;
  while (!((fid == p->fid) && (tid == p->tid)) && (nullptr != p->next)){
    p = p->next;
  }
  if((fid == p->fid) && (tid == p->tid)){
   if (nullptr == p->next){                         //tail node
      p->prev->next = nullptr;
      p->prev = nullptr;
    } else {                                        //not tail or head
      p->prev->next = p->next;
      p->next->prev = p->prev;
    }
    return head;
  } else {
    return head;
  }
  return nullptr;
}

/**
 * @brief      Dumps a list.
 *
 * @param      head  The head
 */
void dump_list(struct Node* head)
{
  printf("---------------------------\n");
  struct Node* node = head;
  while (node) {
    printf("  %d -> %d\n", node->fid, node->tid);
    node = node->next;
  }
}

/**
 * @brief      Does a test.
 */
void do_test()
{
  struct Node* head = nullptr;

  head = insert_node(head, 1, 2);
  dump_list(head);
  head = insert_node(head, 2, 4);
  dump_list(head);
  head = insert_node(head, 2, 3);
  dump_list(head);
  head = insert_node(head, 3, 4);
  dump_list(head);
  head = insert_node(head, 4, 1);
  dump_list(head);
  head = insert_node(head, 1, 2);
  dump_list(head);

  while (head) {
    head = remove_node(head, head->fid, head->tid);
  }
}

////////////////////////////////////////////////////////////////////////////////
// Classes
//

////////////////////////////////////////////////////////////////////////////////
// Functions
//
int main(int argc, char const* argv[])
{
  do_test();

  return 0;
}

////////////////////////////////// EOF /////////////////////////////////////////
