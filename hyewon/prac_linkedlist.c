

typedef struct node
{
    /* data */
    int data;
    struct node *next;
}Node;

typedef struct list
{   
    /* data */
    Node *head;
    Node *tail;
    int size;
}List;

void createlist(List *list){
    list->head = (Node*)malloc(sizeof(Node));
    // 노드의 주소를 담을 노드 크기만큼의 메모리 할당?
    list->tail = (Node*)malloc(sizeof(Node));
    // 머리꼬리 둘다 
    list->head->next = list->tail;
    // 머리가 꼬리를 가리키도록, next도 tail도 포인터
    list->tail->next = list->tail;
    // 자기자신을 가리킴, 마지막이라서?
    list->size = 0;
    // 머리-꼬리니까 아직 0
}

void addFirst(List *list, int data){
    // head가 가리키는 노드(데이터중에 첫번째) 추가
    // head가 가리키던 노드를 새 노드가 가리키고 
    // head가 새 노드를 가리키도록  
    // + 할당부터 해줘야하고, 받은 data도 넣어줘야함
    // + 포인터로 선언해줘야하고, <- 그래야 next로 주지(&써도 될거같긴해)
    // + 사이즈 증가시켜줘야함
    Node *new_node = (Node*)malloc(sizeof(Node));
    // 구조체 포인터로 새 노드 들어갈 메모리 할당
    new_node->data = data;
    // 새 노드에 인자로 들어온 data 대입
    new_node->next = list->head->next;
    // 새 노드의 next에 원래 head가 가리키던 next 대입
    list->head->next = new_node;
    // 리스트 헤드가 가리키는 next에 새 노드(포인터) 대입
    list->size++;
    // 사이즈 증가
}

void addLast(List *list, int data){
    // tail을 가리키는 노드(데이터중에 마지막) 추가
    // 새노드 할당해주고 데이터 넣어주고
    // tail 전까지 탐색해야하나..? next가 tail인걸 찾아서?
    // 찾고나면 걔가 가리키던 tail을 새 노드가 가리키고
    // 걔가 새 노드를 가리키도록 
    // 사이즈 증가
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = list->tail;

    Node *last = list->head;
    while(last->next!=list->tail){
        last = last->next;
    }

    last->next = new_node;
    list->size++;

}

void addAfter(List *list, Node *node, int data){
    // 중간에 노드 추가
    // 새노드 할당, 데이터 넣어줌
    // 
}

