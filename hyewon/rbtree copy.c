#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  // TODO: initialize struct if needed
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nilnode = (node_t *)calloc(1, sizeof(node_t));
  // RBTREE_RED, RBTREE_BLACK
  nilnode->color = RBTREE_BLACK;
  p->root = nilnode;
  p->nil = nilnode;  
  return p;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

void left_rotate(rbtree *t, node_t *x){
  
}


// node_t *rbtree_insert(rbtree *t, const key_t key) {
//   // TODO: implement insert
  
//   return t->root;
// }

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert

  return t->root;
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

void rbtree_transplant(rbtree *t, node_t *u, node_t *v);
node_t *rbtree_minimum(node_t *t);
void rbtree_erase_fixup(rbtree *t, node_t *x);

int rbtree_erase(rbtree *t, node_t *z) {
  // TODO: implement erase
  node_t *y = z;  
  node_t *x;
  color_t y_oringnal = y->color;
  if(z->left==t->nil){  // 왼쪽 자식이 없을 때 -> 자식이 없거나 오른쪽만 있는 경우
    x = z->right;
    rbtree_transplant(t, z, z->right);
  }
  else if(z->right==t->nil){  // 왼쪽자식만 있는 경우
    x = z->left;
    rbtree_transplant(t, z, z->left);
  }
  else{ // 자식이 둘 다 있는 경우
    y = rbtree_minimum(z->right); // 오른쪽 서브트리의 최솟값 = 후계자
    y_oringnal = y->color;
    x = y->right;
    if(y->parent==z){
      x->parent = y;
    }
    else{
      rbtree_transplant(t, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    rbtree_transplant(t, z, y);
    y->left = z->left;
    z->left->parent = y;
    y->color = z->color;
    
  }
  if (y_oringnal==RBTREE_BLACK){
    rbtree_erase_fixup(t, x);
  }
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
