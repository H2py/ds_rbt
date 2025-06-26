#include "rbtree.h"
#include <stdlib.h>

// 새로운 노드 생성, 자식은 t->nil로 설정 완료
rbtree *new_rbtree(void) {
  rbtree *t = (rbtree *)calloc(1, sizeof(rbtree));
  if (t == NULL) return NULL;

  t->nil = (node_t *)calloc(1, sizeof(node_t));
  if (t->nil == NULL) {
    free(t);
    return NULL;
  }

  t->nil->color = RBTREE_BLACK;
  t->nil->left = t->nil;
  t->nil->right = t->nil;
  t->nil->parent = t->nil;

  t->root = t->nil;

  return t;
}

node_t *grandparent(rbtree *t, node_t *n)
{
  if(n == t->nil || n->parent == t->nil || n->parent->parent == t->nil)
    return t->nil;
  return n->parent->parent;
}

node_t *uncle(rbtree *t, node_t *n)
{
  node_t *g = grandparent(t, n);
  if(g == t->nil) return t->nil;

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

void delete_recursive(rbtree *t, node_t *cur)
{
  if(cur == t->nil) return;
  
  delete_recursive(t, cur->left);
  delete_recursive(t, cur->right);
  free(cur);
}

void delete_rbtree(rbtree *t) {
  delete_recursive(t, t->root);
  free(t->nil);
  free(t);
}

node_t *rbtree_insert_fixup(rbtree* t, node_t *z)
{

  while(z->parent->color == RBTREE_RED)
  {
    node_t *g = grandparent(t, z);
    node_t *u = uncle(t, z);

    if(z->parent == g->left) {
      if(u->color == RBTREE_RED) {
        z->parent->color = u->color = RBTREE_BLACK;
        g->color = RBTREE_RED;
        z = g;
      }
      else {
        if(z == z->parent->right) {
          z = z->parent;
          left_rotate(t, z);
          // left_rotate(t, z->parent);
        }
        z->parent->color = RBTREE_BLACK;
        g->color = RBTREE_RED;
        right_rotate(t, g);
      }
    }
    else if (z->parent == g->right) {
      if(u->color == RBTREE_RED) {
        z->parent->color = u->color = RBTREE_BLACK;
        g->color = RBTREE_RED;
        z = g;        
      }
      else {
        if(z == z->parent->left) {
          z = z->parent;
          right_rotate(t, z);
          // right_rotate(t, z->parent);
        }
        z->parent->color = RBTREE_BLACK;
        g->color = RBTREE_RED;
        left_rotate(t, g);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
  return z;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *insert_node = (node_t*)malloc(sizeof(node_t));
  if (insert_node == NULL) return NULL;

  insert_node->key = key;
  insert_node->left = insert_node->right = t->nil;
  insert_node->color = RBTREE_RED;

  node_t *cur = t->root;
  node_t *prev = t->nil;

  while(cur != t->nil)
  {
    prev = cur;
    if (cur->key < insert_node->key) 
      cur = cur->right; 
    else
      cur = cur->left;
  }
  insert_node->parent = prev;

  if (prev == t->nil) 
    t->root = insert_node;
  else if (insert_node->key < prev->key)
    prev->left = insert_node;
  else
    prev->right = insert_node;

  rbtree_insert_fixup(t, insert_node);  
  return insert_node;
}


node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *cur = t->root;
  if (cur == t->nil) return NULL;

  while(cur != t->nil)
  {
    if (cur->key == key)
      return cur;
    else if (cur->key < key)
      cur = cur->right;
    else
      cur = cur->left;
  }
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  node_t *cur = t->root;
  if (cur == t->nil) return NULL;

  while(cur->left != t->nil)
  {
    cur = cur->left;
  }

  return cur;
}

node_t *rbtree_max(const rbtree *t) {
  node_t *cur = t->root;
  if (cur == t->nil) return NULL;

  while(cur->right != t->nil)
  {
    cur = cur->right;
  }

  return cur;
}

int rbtree_erase_fixup(rbtree *t, node_t *d)
{
  while(d != t->root && d->color == RBTREE_BLACK)
  {
    if(d == d->parent->left)
    {
      node_t *bro = d->parent->right;
      // Case 1
      if(bro->color == RBTREE_RED)
      {
        left_rotate(t, d->parent);
        color_t temp_color = d->parent->color;
        d->parent->color = bro->color;
        bro->color = temp_color;
        bro = d->parent->right;
      }
      
      // Case 2
      if(bro->color == RBTREE_BLACK && bro->left->color == RBTREE_BLACK && bro->right->color == RBTREE_BLACK)
      {
        bro->color = RBTREE_RED;
        d = d->parent;
      } 
      else
      {
        if(bro->color == RBTREE_BLACK && bro->left->color == RBTREE_RED)
        {
          bro->color = RBTREE_RED;
          bro->left->color = RBTREE_BLACK;
          right_rotate(t, bro);
          bro = d->parent->right;
        }
        
        bro->color = d->parent->color;
        d->parent->color = RBTREE_BLACK;
        bro->right->color = RBTREE_BLACK;
        left_rotate(t, d->parent);
        d = t->root;
      }
    }
    else
    {
      node_t *bro = d->parent->left;

      if(bro->color == RBTREE_RED)
      {
        right_rotate(t, d->parent);
        color_t temp_color = d->parent->color;
        d->parent->color = bro->color;
        bro->color = temp_color;
        bro = d->parent->left;
      }
      
      // Case 2
      if(bro->color == RBTREE_BLACK && bro->left->color == RBTREE_BLACK && bro->right->color == RBTREE_BLACK)
      {
        bro->color = RBTREE_RED;
        d = d->parent;
      } 
      else
      {
        if(bro->color == RBTREE_BLACK && bro->left->color == RBTREE_RED)
        {
          bro->color = RBTREE_RED;
          bro->left->color = RBTREE_BLACK;
          left_rotate(t, bro);
          bro = d->parent->left;
        }
        
        bro->color = d->parent->color;
        d->parent->color = RBTREE_BLACK;
        bro->left->color = RBTREE_BLACK;
        right_rotate(t, d->parent);
        d = t->root;
      }
    }
  }
  d->color = RBTREE_BLACK;
  return 0;
}

int rbtree_erase(rbtree *t, node_t *p) {
  if (p == t->nil) return -1;
  node_t *d = rbtree_find(t, p->key);

  color_t deleted_color = d->color;
  node_t *delete_after_node = t->nil;

  // 자식이 없을 때
  if(d->left == t->nil && d->right == t->nil)
  {
    if(d == d->parent->left)
      d->parent->left = t->nil;
    else
      d->parent->right = t->nil;
    free(d);
    t->root = t->nil;
  } 
  // 자식이 하나 있을 때,
  else if (d->left == t->nil || d->right == t->nil)
  {
    node_t *child = (d->left != t->nil) ? d->left : d->right;

    child->parent = d->parent;

    if (d->parent->left == d)
      d->parent->left = child;
    else
      d->parent->right= child;

    free(d);
    delete_after_node = child;
  }
  // 자식 2개있을 때
  else
  {
    node_t *cur = d->right;

    while(cur->left != t->nil)
      cur = cur->left;
    
    node_t *child = cur->right;
    node_t *parent = cur->parent;
    
    deleted_color = cur->color;
    delete_after_node = child;

    if(child != t->nil)
      child->parent = parent;
    
    if(cur == parent->left)
      parent->left = child;
    else
      parent->right = child;
      
    free(cur);
  }
  if (deleted_color == RBTREE_BLACK)
    rbtree_erase_fixup(t, delete_after_node);
  return 0;
}

void inorder_traversal(const rbtree *t, key_t *arr, const size_t n, node_t *p, int *i) {
  if(p == t->nil || *i >= n) return;

  inorder_traversal(t, arr , n, p->left, i);
  arr[(*i)++] = p->key;
  inorder_traversal(t, arr , n, p->right, i);
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  int i = 0;
  inorder_traversal(t, arr, n, t->root, &i);
  return 0;
}
