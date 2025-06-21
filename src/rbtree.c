#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  if (p == NULL) return NULL;

  p->nil = (node_t *)calloc(1, sizeof(node_t));
  if (p->nil == NULL) return NULL;

  p->nil->color = RBTREE_BLACK;
  p->root = p->nil;

  return p;
}

node_t* grandparent(rbtree *t, node_t * n)
{
  if(n == t->nil || n->parent == t->nil || n->parent->parent == t->nil)
    return t->nil;
  return n->parent->parent;
}

node_t* uncle(rbtree *t, node_t *n)
{
  node_t *g = grandparent(t, n);
  if (g == t->nil) return t->nil;
  
  if (n->parent == g->left)
    return g->right;
  else
    return g->left;
}

//왼쪽 회전, tree랑 x 포인터를 인자로 받는다
void left_rotate(rbtree *t, node_t *x) {
  node_t *y = x -> right;
  x->right = y->left;

  if (y->left != t->nil) {
    y->left->parent = x;
  }

  y->parent = x->parent;

  if(x->parent == t->nil) {
    t->root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

//오른쪽 회전
void right_rotate(rbtree *t, node_t *y) {
  node_t* x = y->left;
  y->left = x->right;

  if(x->right != t->nil) {
    x->right->parent = y;
  }

  x->parent = y->parent;

  if(y->parent == t->nil) {
    t->root = x;
  }
  else if(y == y->parent->left) {
    y->parent->left = x;
  } else {
    y->parent->right = x;
  }
  x->right = y;
  y->parent = x;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *z = (node_t *)malloc(sizeof(node_t));
  z->key = key;
  z->color = RBTREE_RED;
  z->left = z->right = z->parent = t->nil;

  node_t *x = t->root;
  node_t *y = t->nil;

  while(x != t->nil)
  {
    y = x;
    if (z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }

  z->parent = y;
  if (y== t->nil)
    t->root = z;
  else if (z->key < y->key) 
    y->left = z;
  else
    y->right = z;
  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
