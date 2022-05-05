#include <stdio.h>


typedef struct Treenode{

    int key;
    struct Treenode *left, *right;

} treenode;

treenode* search(treenode *node, int key){
    if (node == NULL) return NULL;

    if (key == node->key) return node;
    else if (node->key < key){
        return search(node->right, key);
    } else {
        return search(node->left, key);
    }
}

void insertnode(treenode **root, int key){
    // *root : treenode 구조체를 가리키는 포인터를 가리키는 포인터
    treenode *n, *t; // n: 새로만드는노드, t: 탐색하는 노드
    treenode *p = NULL; // 부모노드

    t = *root;

    while (t != NULL){
        if (t->key == key) return; // 동일한 key 값을 가질 경우 삽입할 수 없으므로 return
        p = t; // 새로운 노드가 들어갈 자리를 찾고 난 후에 해당 노드의 부모 노드를 저장해놓기 위함
        if (t->key < key){ // 새로운 노드의 key 값이 현재 노드의 key 값보다 클 경우 오른쪽으로 탐색
            t = t->right; // 현재 노드를 오른쪽 자식 노드로 변경
        } else { // 동일한 이유로 왼쪽으로 탐색
            t = t->left;
        }

    }

    // 새로운 노드 생성

    n = (treenode*)malloc(sizeof(treenode));

    n->key = key;
    
    n->right = n->left = NULL; // 리프 노드는 자식 노드가 없으므로 NULL 값으로 초기화 해줌

    if (p != NULL) {
        if (p->key < key){ // 새로운 노드가 들어갈 자리의 부모 노드의 key 값보다 새로운 노드의 key 값이 클 경우 부모 노드의 오른쪽 자식에 새로운 노드 연결
            p->right = n;
        } else {
            p->left = n;
        }
    } else {
        *root = n; // 부모노드를 가리키는 포인터값이 NULL 일 경우 빈트리이므로 새로운 노드를 루트 노드로 설정
    }


}

// 삭제 연산

void deletenode(treenode **root, int key){

    treenode *p, *child, *succ, *succ_p, *t;

    p = NULL;
    t = *root;

    // 삭제할 노드 탐색

    while (t->key != key && t != NULL){
        p = t; // 삭제할 노드의 부모 노드
        if (t->key < key){
            t = t->right;
        } else {
            t = t -> left;
        }
    }

    if (t == NULL) return;

    // 삭제할 노드의 서브트리 상태에 따라 케이스 분류

    if (t->left == NULL && t->right == NULL){
        if (p != NULL) {

            if (p->right == t){
                p->right = NULL;
            } else {
                p->left = NULL;
            }

        } else {
            *root = NULL;
        }


    } else if (t->left == NULL || t->right == NULL){ // 하나의 서브트리를 가진 경우

        child = (t->left == NULL) ? t->right: t->left; // 왼쪽 자식이 없는 경우 오른쪽 자식 노드가 후계자 노드가 됨.

        if (p != NULL){

            if (p->key < t->key){ // 삭제되는 노드의 key 값이 부모노드의 key 값 보다 클 경우 후계자 노드도 부모노드의 오른쪽에 존재함.
                p->right = child; // 부모노드의 오른쪽 자식과 후계자 노드를 연결함.
            } else {
                p->left = child;
            }
        } else {
            *root = child; // 부모노드는 없는데 자식 노드만 있는 경우 삭제되는 노드는 루트 노드
        }

    } else { 
        
        // 두 개의 서브트리를 갖고 있는 경우
        // 오른쪽으로 탐색하는 기준
        succ_p = t; // 후계자 노드의 부모 노드 = 삭제할 노드
        succ = t->right; // 후계자 노드

        while (succ->left != NULL){ // 삭제할 노드의 오른쪽 서브트리 중 가장 왼쪽에 있는 값을 찾기 위함
            // 타겟 노드를 찾을때까지 후계자 노드의 부모 노드 및 후계자 노드를 갱신 
            succ_p = succ;
            succ = succ->left;
        }

        if (succ_p->left == succ){ // 삭제할 노드의 오른쪽 서브트리에 왼쪽 자식이 있는 경우
            succ_p->left = succ->right;
        } else { // 오른쪽 서브트리에 왼쪽 자식이 없을 경우 오른쪽 자식을 가리킬 수 있도록 함
            succ_p->right = succ->right;
        }

        t->key = succ->key; // 삭제할 노드의 key 값에 succ의 key 값을 넣어줌.

        t = succ;

        free(t); 

    }
    
}

int main(){

}
