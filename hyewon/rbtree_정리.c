#include "rbtree.h"

#include <stdlib.h>
// 참 잘했어요
rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nilnode = (node_t *)calloc(1, sizeof(node_t));
  nilnode -> color = RBTREE_BLACK;
  p->nil = nilnode;
  p->root = nilnode; 
  // TODO: initialize struct if needed
  return p;
}
void delete_node(rbtree *t, node_t *p){
  if(p!=t->nil){
    delete_node(t, p->left);    
    delete_node(t, p->right);
    free(p);
    p = NULL;
  }
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  delete_node(t, t->root);
  free(t->nil);
  t->nil=NULL;
  free(t);
  t = NULL;
}

// void delete_node(rbtree *t, node_t *p){
//   if(p!=t->nil){
//     delete_node(t,p->left);
//     delete_node(t,p->right);
//     free(p);
//     p = NULL;
//   }
// }

// void delete_rbtree(rbtree *t){
//   delete_node(t, t->root);
//   free(t->nil);
//   t->nil = NULL;
//   free(t);
//   t = NULL;
// }


// 참 잘했어요
void left_rotate(rbtree *t, node_t *x){

  node_t *y = x->right;

  x->right = y->left; // 이진트리의 규칙을 유지하기 위해 자식 노드를 옮겨줌

  if (y->left != t->nil){
    y->left->parent = x;
  }

  y->parent = x->parent;

  if (x->parent == t->nil){
    t->root = y;
  }
  else if (x->parent->left == x){
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }

  y->left = x;
  x->parent = y;

}
// 참 잘했어요
void right_rotate(rbtree *t, node_t *y){

  node_t *x = y->left; // x는 y의 왼쪽 자식

  y->left = x->right; // 회전하면서 이진 트리 규칙을 지키기 위해 y의 왼쪽 자식은 x의 오른쪽 자식

  if (x->right != t->nil){ // x의 오른쪽 자식이 nil 노드가 아닐 경우
    x->right->parent = y; // x의 오른쪽 자식의 부모와 y를 연결해주어야 함.
  }
  x->parent = y->parent;
  if (y->parent == t->nil){ // y의 부모노드가 nil 노드일 경우 
    t->root = x; // 루트 노드는 x
  } else if (y->parent->left == y) { // y가 부모노드의 왼쪽 자식인지 오른쪽 자식인지 확인
    y->parent->left = x; // 왼쪽 자식이면 y의 부모노드의 왼쪽 자식을 x로 수정함
  } else {
    y->parent->right = x;
  }
  // 재배치된 x와 y의 부모 및 자식 관계 수정
  x->right = y;
  y->parent = x;

}

// void left_rotate(rbtree *t, node_t *x){
//   node_t *y = x->right; //x노드의  오른쪽에 y노드 지정
//   x->right = y->left; //y노드의 왼쪽노드를 x노드의 오른쪽으로 옮긴다.
//   //y노드의 왼쪽노드에 노드가 존재한다면, 그 노드의 부모 값을 x로 지정한다.
//   if(y->left != t->nil){
//     y->left->parent = x;
//   }
//   //y의 부모값을 x의 부모값으로 지정하여 원래 x가 있던자리에 y를 넣어준다.
//   y->parent = x->parent;
//   //만약 x가 트리의 루트였다면?
//   if(x->parent == t->nil){
//     t->root = y; //트리의 루트를 y로 지정해준다.
//   }else if(x == x->parent->left){ //x가 왼쪽노드였다면
//     x->parent->left = y; //x 부모의 왼쪽노드를 y라고 해준다.
//   }else{ // x가 오른쪽 노드였다면,
//     x->parent->right = y; // y 부모의 오른쪽 노드를 x라고 해준다.
//   }
//   y->left = x; //y의 왼쪽노드를 x로 해준다.
//   x->parent = y; //x의 부모를 y로 설정해준다.
// }

// void right_rotate(rbtree *t, node_t *y){
//   node_t *x = y->left;
//   y->left = x->right;
//   if(x->right != t->nil){
//     x->right->parent = y;
//   }
//   x->parent = y->parent;
//   if(y->parent == t->nil){
//     t->root = x;
//   }else if(y==y->parent->right){
//     y->parent->right = x;
//   }else{
//     y->parent->left = x;
//   }
//   x->right = y;
//   y->parent = x;
// }

// 참 잘했어요
void rbtree_insert_fixup(rbtree *t, node_t *z){

// 삽입 노드가 적색일 경우 (루트노드가 검은색이어야 한다는 룰 위반)
// 삽입 노드의 부모 노드가 적색일 경우(적색 노드의 자식 노드는 흑색이어야 하는 룰 위반)
// 1. 모든 노드는 red 혹은 black
// 2. 루트 노드는 black
// 3. 모든 nil(leaf) 노드는 black
// 4. red의 자녀들은 black or red가 연속적으로 존재할 수 없음
// 5. 임의의 노드에서 자손 nil 노드들까지 가는 경로들의 black 수는 같다(자기 자신은 카운트에서 제외)

// 다음의 분류는 자신과 아빠 노드의 색이 동일하다는 것(=red)을 전제로 함.
// case 1. 아빠랑 삼촌이 red고 할아버지가 black
// case 2. 노드에서 할아버지 노드로 가는 경로가 꺾인 경우 && 삼촌 노드가 검은색인 경우
// case 3. 경로가 꺽이지 않은 경우

while (z->parent->color == RBTREE_RED){ // 삽입될 노드(=노드)의 부모 노드가 red인 경우
  if (z->parent == z->parent->parent->left){ // 노드의 부모 노드가 할아버지 노드의 왼쪽 자식인 경우
    node_t *y = z->parent->parent->right; 
    // RB 트리가 #5 속성을 만족하고 있고, 두 자녀가 같은 색을 가질 때 부모와 
    // 두 자녀의 색을 바꿔줘도 #5 속성은 여전히 만족한다.
    if (y->color == RBTREE_RED){ // 삼촌의 color가 레드인 경우, 삼촌과 부모노드의 색을 검은색으로 바꾸고, 할아버지 노드의 색을 빨간색으로 바꾼다.
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent; // 할아버지 노드가 적색이 되었으므로 다시 rule 4번을 위반하지 않는지 확인해야 함.
    } else {

      if (z->parent->right == z){ // 노드가 부모 노드의 오른쪽 자식일 경우
        z = z->parent; // z를 노드의 부모 노드로 업데이트(=> 왼쪽으로 회전하고 나면 height가 한 수준 내려가기 때문)
        left_rotate(t, z); // 노드의 부모노드 기준으로 왼쪽으로 회전
      }
      // 할아버지 노드로 가는 경로가 정방향일 경우 오른쪽으로 회전
      z->parent->color = RBTREE_BLACK;
      z->parent->parent->color = RBTREE_RED;
      right_rotate(t, z->parent->parent); // 부모 노드를 검은색으로 수정 후 할아버지 노드 기준으로 회전시키기 때문에 자연스럽게 4번을 충족함.
      // 현 시점에서 자신의 부모노드가 검은색인데 z를 수정해서 끝내게 되면 초기 while 문 조건에서 걸릴 수 있음.
      // 그래서 rotate 함수에 z의 할아버지 노드를 넣어주는 것임.
    }
    
  } else { // 노드의 부모 노드가 할아버지 노드의 오른쪽 자식인 경우
    node_t *y = z->parent->parent->left;
    if (y->color == RBTREE_RED){
      z->parent->color = RBTREE_BLACK;
      y->color = RBTREE_BLACK;
      z->parent->parent->color = RBTREE_RED;
      z = z->parent->parent;
    } else {
      if (z->parent->left == z){
        z = z->parent;
        right_rotate(t, z);
      }
      z->parent->color = RBTREE_BLACK;
      z->parent->parent->color = RBTREE_RED;
      left_rotate(t, z->parent->parent);
    }
  }
}

t->root->color = RBTREE_BLACK;

}

// 참 잘했어요
node_t *rbtree_insert(rbtree *t, const key_t key) {


  // TODO: implement insert
  node_t *y = t->nil; // 
  node_t *x = t->root; // 탐색 시작할 위치인 루트노드 변수 선언
  
  while (x != t->nil){ // 노드가 삽입될 위치를 찾기 위한 반복문 조건
    y = x; // 삽입될 위치에 도달했을 때의 부모 노드 위치를 기록하기 위함
    if (key < x->key){ // 삽입할 노드의 key 값이 현재 노드의 키 값 보다 작으면 왼쪽 서브트리에 위치함
      x = x -> left; // 다음 탐색 위치를 왼쪽 서브트리로 만들어줌
    } else {
      x = x -> right;
    }
  }

  node_t *z = (node_t *)calloc(1, sizeof(node_t)); // 삽입될 노드 메모리 할당 및 변수 선언

  z->key = key; // 삽입될 노드의 키 값 적용

  z->parent = y; // z의 부모노드를 y로 설정함

  if (y==t->nil){ // y가 nil일 경우 빈트리이므로 루트노드를 삽입노드로 수정
    t->root = z;
  } else if (key < y->key){ // 삽입노드의 key 값이 부모노드의 키 값보다 작을 경우
    y->left = z; // y의 왼쪽 자식노드로 삽입 노드 설정
  } else {
    y->right = z;
  }

  z->left = t->nil; // 삽입 노드는 leaf 노드이므로 왼쪽 및 오른쪽 자식에 nil 노드 설정
  z->right = t->nil;
  z->color = RBTREE_RED; // 삽입 노드는 트리 규칙을 위해 반드시 red로 설정

  rbtree_insert_fixup(t, z); // 노드 삽입 후 트리 규칙에 위반되지 않는지 확인을 위한 함수 호출

  return t->root;
}

// void rbtree_insert_fixup(rbtree *t, node_t *z){
//   while (z->parent->color==RBTREE_RED){
//     if(z->parent == z->parent->parent->left){
//       node_t *y = z->parent->parent->right;
//       if (y->color == RBTREE_RED){
//         z->parent->color = RBTREE_BLACK;
//         y->color = RBTREE_BLACK;
//         z->parent->parent->color = RBTREE_RED;
//         z = z->parent->parent;
//       }else{
//         if(z==z->parent->right){
//           z = z->parent;
//           left_rotate(t,z);
//         }
//         z->parent->color = RBTREE_BLACK;
//         z->parent->parent->color = RBTREE_RED;
//         right_rotate(t,z->parent->parent);
//       }
//     }
//     else{
//       node_t *y = z->parent->parent->left;
//       if (y->color == RBTREE_RED){
//         z->parent->color = RBTREE_BLACK;
//         y->color = RBTREE_BLACK;
//         z->parent->parent->color = RBTREE_RED;
//         z = z->parent->parent;
//       }else{
//         if(z==z->parent->left){
//           z = z->parent;
//           right_rotate(t,z);
//         }
//         z->parent->color = RBTREE_BLACK;
//         z->parent->parent->color = RBTREE_RED;
//         left_rotate(t,z->parent->parent);
//       }
//     }
//   }
//   t->root->color = RBTREE_BLACK;
// }

// node_t *rbtree_insert(rbtree *t, const key_t key) {
//   // 트리의 nil노드에 해당하는 y노드를 생성
//   // y를 nil값으로 하는 이유는 밑에 나올 while문이 애초에 돌아가지 않았을 경우 y값이 nil값으로 고정시켜놓기 위해서이다.
//   // while문이 애초에 돌아가지 않을 경우는 z노드가 최초 삽입될 경우이다.
//   node_t *y = t->nil;
//   // 트리의 루트에 해당하는 x노드를 생성
//   node_t *x = t->root;
//   // 함수파라미터에서 받은 key값을 가진 노드 z를 만든다.
//   node_t *z = (node_t *)calloc(1, sizeof(node_t));
//   z->key = key;
//   // x값이 nil노드가 아닐 때 까지 아래로 탐색하는 while문
//   while(x!=t->nil){
//     // while 문이 마지막 즉, x가 nil을 만나기 전값을 y가 기록하기 위함이다.
//     y = x;
//     // 만약 z의 key값이 x의 key값보다 작다면
//     if(z->key < x->key) {
//       // 루트의 왼쪽으로 보내준다.
//       x = x->left;
//     }else{
//       // 루트의 오른쪽으로 보내준다.
//       x = x->right;
//     }
//   }
//   // while문에서 저장된 y값을 z-parent에 저장한다.
//   z->parent = y;
//   // 만약 while문이 한번도 돌지 않았다면,
//   if(y==t->nil){
//     // 트리의 루트는 z이다
//     t->root = z;
//   }else if(z->key < y->key){ // z-key, y-key를 비교하여 부모의 노드 구조체에 z 주소값을 넣어주기 위함이다.
//     y->left = z;
//   }else{
//     y->right = z;
//   }
//   // 트리의 특성상 insert 된 노드는 트리 가장 아래에 위치하게 될 것이기에
//   z->left = t->nil;
//   z->right = t->nil;
//   z->color = RBTREE_RED;
//   // 트리의 속성을 위반하는지 판단하고 고쳐주기 위한 함수 호출!
//   rbtree_insert_fixup(t, z);
//   return z;
// }




node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *s = t->root;
  // printf("find_root : %d %d\n", s->key, key);
  while(s!=t->nil && s->key != key){
    // printf("while : %d %d\n", s->key, key);
    if(s->key > key){
      s = s->left;
    }else{
      s = s->right;
    }
  }
  if(s->key == key){
    return s;
  }
  // printf("not key : %d\n", key);
  return NULL;
}

// void transplant(rbtree *t, node_t *u, node_t *v){
//   if(u->parent == t->nil){
//     t->root = v;
//   }else if(u == u->parent->left){
//     u->parent->left = v;
//   }else{
//     u->parent->right = v;
//   }
//   v->parent = u->parent;
// }

// node_t *tree_min(rbtree *t, node_t *p){
//   while(p->left != t->nil){
//     p = p->left;
//   }
//   return p;
// }

// void rbtree_erase_fixup(rbtree *t, node_t *x){
//   node_t *u;
//   // fix가 시작되는 조건
//   while(x != t->root && x->color == RBTREE_BLACK){
//     //기준이되는 노드가 왼쪽일 때
//     if(x->parent->left == x){
//       u = x->parent->right;
//       //case1: uncle is red
//       if(u->color == RBTREE_RED){
//         //형제를 검은색으로 부모를 빨간색으로 칠한다. 부모노드를 기준으로 좌회전한다.
//         u->color = RBTREE_BLACK;
//         x->parent->color = RBTREE_RED;
//         left_rotate(t, x->parent);
//         u = x->parent->right;
//       }
//       //case2: uncle is black with two black child
//       if(u->left->color == RBTREE_BLACK && u->right->color == RBTREE_BLACK){
//         //형제노드만 빨간색으로 만들고 타겟을 부모로 변경한다.
//         u->color = RBTREE_RED;
//         x = x->parent;
//       }
//       else { // 자식 중 최소 한개는 빨간색이다.
//         //case3: uncle is black with red color left child and black color right child
//         if(u->right->color == RBTREE_BLACK){
//         // 형제 노드를 빨간색으로, 형제 노드의 왼쪽 자식을 검은색으로 칠하고 형제노드를 기준으로 우회전한다.
//           u->color = RBTREE_RED;
//           u->left->color = RBTREE_BLACK;
//           right_rotate(t, u);
//           u = x->parent->right;
//         }
//         //case4: uncle is black with red color right child
//         // 부모 노드의 색을 형제에게 넘긴다. 부모노드와 형제 노드의 오른쪽 자식을 검은색으로 칠한다. 부모 노드 기준으로 좌회전한다.
//         u->color = x->parent->color;
//         x->parent->color = RBTREE_BLACK;
//         u->right->color = RBTREE_BLACK;
//         left_rotate(t, x->parent);
//         x = t->root;
//       }
//     }
//     //기준이 되는 노드가 오른쪽 일때
//     else{
//       u = x->parent->left;
//       //case1: uncle is red
//       if(u->color == RBTREE_RED){
//         //형제를 검은색으로 부모를 빨간색으로 칠한다. 부모노드를 기준으로 좌회전한다.
//         u->color = RBTREE_BLACK;
//         x->parent->color = RBTREE_RED;
//         right_rotate(t, x->parent);
//         u = x->parent->left;
//       }
//       //case2: uncle is black with two black child
//       if(u->right->color == RBTREE_BLACK && u->left->color == RBTREE_BLACK){
//         //형제노드만 빨간색으로 만들고 타겟을 부모로 변경한다.
//         u->color = RBTREE_RED;
//         x = x->parent;
//       }
//       else { // 자식 중 최소 한개는 빨간색이다.
//         //case3: uncle is black with red color right child and black color left child
//         if(u->left->color == RBTREE_BLACK){
//         // 형제 노드를 빨간색으로, 형제 노드의 왼쪽 자식을 검은색으로 칠하고 형제노드를 기준으로 우회전한다.
//           u->color = RBTREE_RED;
//           u->right->color = RBTREE_BLACK;
//           left_rotate(t, u);
//           u = x->parent->left;
//         }
//         //case4: uncle is black with red color left child
//         // 부모 노드의 색을 형제에게 넘긴다. 부모노드와 형제 노드의 오른쪽 자식을 검은색으로 칠한다. 부모 노드 기준으로 좌회전한다.
//         u->color = x->parent->color;
//         x->parent->color = RBTREE_BLACK;
//         u->left->color = RBTREE_BLACK;
//         right_rotate(t, x->parent);
//         x = t->root;
//       }
//     }
//   }
//   x->color = RBTREE_BLACK;
// }


// int rbtree_erase(rbtree *t, node_t *p) {
//   // TODO: implement erase
//   node_t *y = p;
//   color_t y_original_color = y->color;
//   node_t *x;
//   if(p->left == t->nil){
//     x = p->right;
//     transplant(t,p,p->right);
//   }else if(p->right == t->nil){
//     x= p->left;
//     transplant(t,p,p->left);
//   }else{
//     y = tree_min(t, p->right);
//     y_original_color = y->color;
//     x = y->right;
//     if(y->parent==p){
//       x->parent=y;
//     }else{
//       transplant(t,y,y->right);
//       y->right = p->right;
//       y->right->parent = y;
//     }
//     transplant(t,p,y);
//     y->left = p->left;
//     y->left->parent = y;
//     y->color = p->color;
//   }
//   if(y_original_color == RBTREE_BLACK){
//     rbtree_erase_fixup(t,x);
//   }
//   free(p);
//   return 0;
// }


void rb_transplant(rbtree *t, node_t *u, node_t *v){
  if (u->parent == t->nil) {          // u의 부모가 nil일 때, 즉, 삭제할 노드가 트리의 root 일때
    t->root = v;                      // 트리의 root는 v
  } else if (u == u->parent->left) {  // u가 u의 부모의 왼쪽 자식일 때
    u->parent->left = v;              // u의 부모의 왼쪽 자식 v
  } else {                            // u가 u의 부모의 오른쪽 자식일 때
    u->parent->right = v;             // u의 부모의 오른쪽 자식은 v
  }
  v->parent = u->parent;              // v의 부모는 u의 부모
  return;
}

node_t *tree_minimum(rbtree *t, node_t *z){
  node_t *y = z;              // y는 x
  while (y->left != t->nil) { // y의 왼쪽 자식이 nil이 아닐 때 반복
    y = y->left;              // y는 y의 왼쪽 자식
  }
  return y;                   // y를 반환
}


void rb_delete_fixup(rbtree *t, node_t *x){
    node_t *w;
    while ((x != t->root) && (x->color == RBTREE_BLACK)) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color == RBTREE_RED) {
                w->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;
                left_rotate(t, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
                w->color = RBTREE_RED;
                x = x->parent;
            }  else {
                if (w->right->color == RBTREE_BLACK) {
                    w->left->color = RBTREE_BLACK;
                    w->color = RBTREE_RED;
                    right_rotate(t, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = RBTREE_BLACK;
                w->right->color = RBTREE_BLACK;
                left_rotate(t, x->parent);
                x = t->root;
            }
        } else {
            w = x->parent->left;
            if (w->color == RBTREE_RED) {
                w->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;
                right_rotate(t, x->parent);
                w = x ->parent->left;
            }
            if (w->right ->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
                w->color = RBTREE_RED;
                x = x->parent;
            } else {
                if (w->left->color == RBTREE_BLACK) {
                    w->right->color = RBTREE_BLACK;
                    w->color = RBTREE_RED;
                    left_rotate(t, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = RBTREE_BLACK;
                w->left -> color = RBTREE_BLACK;
                right_rotate(t, x->parent);
                x = t->root;
            }
        }
    }
    x->color = RBTREE_BLACK;
    return;
}

int rbtree_erase(rbtree *t, node_t *p) {
  node_t *x;                              // 노드 x
  node_t *y = p;                          // y는 삭제할 노드
  color_t y_color = y->color;             // y_color는 y의 색
  if (p->left == t->nil) {                // 삭제할 노드의 왼쪽이 nil일때
    x = p->right;                         // x는 삭제할 노드의 오른쪽
    rb_transplant(t, p, p->right);    // 삭제할 노드의 부모와 삭제할 노드의 오른쪽을 연결
  } else if (p->right == t->nil) {        // 삭제할 노드의 오른쪽이 nill일때
    x = p->left;                          // x는 삭제할 노드의 왼쪽
    rb_transplant(t, p, p->left);     // 삭제할 노드의 부모와 삭제할 노드의 왼쪽을 연결
  } else {                                // 삭제할 노드의 왼쪽, 오른쪽 자식이 둘다 있을 때
    y = tree_minimum(t, p->right);    // y는 직후 원소
    y_color = y->color;                   // y_color는 직후 원소의 색
    x = y->right;                         // x는 y의 오른쪽 자식
    if (y->parent == p) {                 // y의 부모가 삭제할 노드일 때
      x->parent = y;                      // x의 부모는 y
    } else {                              // y의 부모가 삭제할 노드가 아닐 때
      rb_transplant(t, y, y->right);  // y의 부모와 y의 오른쪽 자식을 연결
      y->right = p->right;                // y의 오른쪽 자식은 삭제할 노드의 오른쪽 자식
      y->right->parent = y;               // y의 오른쪽 자식의 부모는 y
    }
    rb_transplant(t, p, y);           // 삭제할 노드 부모와 y를 연결
    y->left = p->left;                    // y의 왼쪽 자식은 삭제할 노드의 왼쪽 자식
    y->left->parent = y;                  // y의 왼쪽 자식의 부모는 y
    y->color = p->color;                  // y의 색은 삭제할 노드의 색
  }
  if (y_color == RBTREE_BLACK) {          // y_color가 BLACK 일 때, 즉 삭제한 노드의 색이 BLACK일 때(특성 5 위반)
    rb_delete_fixup(t, x);                // 노드의 색을 바꿈
  }
  free(p);                                // 삭제한 노드가 가리키는 공간 삭제
  p = NULL;                               // 할당 해제 후 삭제한 노드값을 NULL로 초기화
  return 0;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

// 참 잘했어요
int inorder(const rbtree *t, node_t *root, key_t *arr, const size_t n, int idx){
  if (root==t->nil){
    return idx;
  }
  idx = inorder(t, root->left, arr, n, idx);
  arr[idx++] = root->key;
  idx = inorder(t, root->right, arr, n, idx);
  
  return idx;

}

// 참 잘했어요
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // if (t->nil == t->root) {
  //   return 0;
  // }
  inorder(t, t->root, arr, n, 0);
  return 0;
}
