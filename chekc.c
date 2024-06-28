#include<stdio.h>
#include<stdlib.h>

typedef struct singleListNode singleListNode;
typedef struct doubleListNode doubleListNode;
typedef struct singlyList singlyList;
typedef struct doublyList doublyList;
typedef struct stackInt stackInt;
typedef struct stackDynamic stackDynamic;
typedef struct stringHashmap stringHashmap;
typedef struct nodeForHash nodeForHash;

struct singleListNode{
    int val;
    singleListNode*next;
};
struct doubleListNode{
    int val;
    doubleListNode*next,*prev;
};
struct singlyList{
    singleListNode* head,*tail;
};
struct doublyList{
    doubleListNode* head,*tail;
};
struct stackInt{
    singlyList* ls;
};
struct stackDynamic{
    int *arr;
    int size;
    int top;
};
struct stringHashmap{
    char**arr;
    int load,size;
};
struct nodeForHash{
    char* key;
    int val;
    nodeForHash* next;
};

stackDynamic* CreateStackDynamic(){
    stackDynamic* newstack = (stackDynamic*)malloc(sizeof(stackDynamic));
    newstack->arr = (int*)malloc(sizeof(int)*10);
    newstack->size = 10;
    newstack->top = -1;
}

singleListNode* CreateSingleListNode(int val){
    singleListNode* newnode = (singleListNode*)malloc(sizeof(singleListNode));
    newnode->val = val;
    newnode->next = NULL;
    return newnode;
}
doubleListNode* CreateDoubleListNode(int val){
    doubleListNode* newnode = (doubleListNode*)malloc(sizeof(doubleListNode));
    newnode->val = val;
    newnode->next = newnode->prev = NULL;
    return newnode;
}
singlyList* CreateSinglyList(){
    singlyList* ls = (singlyList*)malloc(sizeof(singlyList));
    ls->head = ls->tail = NULL;
    return ls;
}
doublyList* CreateDoublyList(){
    doublyList* ls = (doublyList*)malloc(sizeof(doublyList));
    ls->head = ls->tail = NULL;
    return ls;
}
stackInt* CreateStackInt(){
    stackInt* stk = (stackInt*)malloc(sizeof(stackInt));
    stk->ls = CreateSinglyList();
    return stk;
}
stringHashmap* CreateStringHashmap(){
    stringHashmap* mp = (stringHashmap*)malloc(sizeof(stringHashmap));
    mp->arr = (char**)malloc(sizeof(char*)*5);
    mp->load = 0; 
    mp->size = 5; 
    return mp;
}
int hashFunction(stringHashmap* hp,char*str){
    int sum = 0 ;
    int i = 0;
    while(str[i]!='\0'){
        sum += str[i];
        i++;
    }
    return sum % hp->size;
}
void insertAtHeadInSinglyList(singlyList* ls,int val){
    singleListNode* newnode = CreateSingleListNode(val);
    if(ls->head==NULL){
        ls->head = ls->tail = newnode;
        return;
    }
    newnode->next = ls->head;
    ls->head = newnode;
}
void insertAtTailInSinglyList(singlyList* ls,int val){
    singleListNode* newnode = CreateSingleListNode(val);
    if(ls->head==NULL){
        ls->head = ls->tail = newnode;
        return;
    }
    ls->tail->next = newnode;
    ls->tail = newnode;
}
void insertAtHeadInDoublyList(doublyList* ls,int val){
    doubleListNode* newnode = CreateDoubleListNode(val);
    if(ls->head==NULL){
        ls->head = ls->tail = newnode;
        return;
    }
    newnode->next = ls->head;
    ls->head->prev = newnode;
    ls->head = newnode;
}
void insertAtTailInDoublyList(doublyList* ls,int val){
    doubleListNode* newnode = CreateDoubleListNode(val);
    if(ls->head==NULL){
        ls->head = ls->tail = newnode;
        return;
    }
    ls->tail->next = newnode;
    newnode->prev = ls->tail;
    ls->tail = newnode;
}
void deleteAtHeadInSinglyList(singlyList*ls){
    if(!ls->head){
        return;
    }
    if(ls->head == ls->tail){
        singleListNode* del = ls->head;
        ls->head = ls->tail = NULL;
        free(del);
        return;
    }
    singleListNode* del = ls->head;
    ls->head = ls->head->next;
    free(del);
}
void deleteAtTailInSinglyList(singlyList*ls){
    if(!ls->head){
        return;
    }
    if(ls->head == ls->tail){
        singleListNode* del = ls->head;
        ls->head = ls->tail = NULL;
        free(del);
        return;
    }
    singleListNode* del = ls->tail;
    singleListNode* temp = ls->head;
    while(temp->next->next){
        temp = temp->next;
    }
    temp->next = NULL;
    free(del);
}
void deleteAtHeadInDoublyList(doublyList*ls){
    if(!ls->head){
        return;
    }
    if(ls->head == ls->tail){
        doubleListNode* del = ls->head;
        ls->head = ls->tail = NULL;
        free(del);
        return;
    }
    doubleListNode* del = ls->head;
    ls->head = ls->head->next;
    ls->head->prev = NULL;
    free(del);
}
void deleteAtTailInDoublyList(doublyList*ls){
    if(!ls->head){
        return;
    }
    if(ls->head == ls->tail){
        doubleListNode* del = ls->head;
        ls->head = ls->tail = NULL;
        free(del);
        return;
    }
    doubleListNode* del = ls->tail;
    ls->tail = ls->tail->prev;
    ls->tail->next = NULL;
    free(del);
}
void pushInStackInt(stackInt* stk,int val){
    insertAtHeadInSinglyList(stk->ls,val);
}
void popInStackInt(stackInt* stk){
    deleteAtHeadInSinglyList(stk->ls);
}
int peek(stackInt*stk){
    return stk->ls->head->val;
}
int isEmpty(stackInt* stk){
    return stk->ls->head == NULL;
}
void pushInDynamicStack(stackDynamic* stk,int val){
    if(stk->size==stk->top+1){
        stk->arr = (int*)realloc(stk->arr,stk->size * 2);
        stk->size *= 2;
    }
    stk->top ++;
    stk->arr[stk->top] = val;
}
void popInDynamicStack(stackDynamic* stk){
    if(stk->top==-1){
        return;
    }
    stk->top--;
}
int topInDynamicStack(stackDynamic* stk){
    return stk->arr[stk->top];
}
int isEmptyDynamicStack(stackDynamic*stk){
    return stk->top == -1;
}
void printList(singlyList* ls){
    singleListNode* head = ls->head;
    while(head){
        printf("%d ",head->val);
        head = head->next;
    }
    printf("\n");
}
void printDoubleList(doublyList* ls){
    doubleListNode* head = ls->head;
    while(head){
        printf("%d ",head->val);
        head = head->next;
    }
    printf("\n");
}
void insertAtStringHash(stringHashmap* hp,char*str){
    int hashkey = hashFunction(hp,str);

}
int main(){

    // singlyList *ls = CreateSinglyList();
    // insertAtHeadInSinglyList(ls,10);
    // insertAtTailInSinglyList(ls,89);
    // insertAtTailInSinglyList(ls,100);
    // insertAtHeadInSinglyList(ls,1000);
    // deleteAtTailInSinglyList(ls);
    // printList(ls);
    // doublyList* ls1 = CreateDoublyList();
    // insertAtTailInDoublyList(ls1,100);
    // insertAtTailInDoublyList(ls1,1000);
    // insertAtHeadInDoublyList(ls1,100);
    // deleteAtTailInDoublyList(ls1);
    // deleteAtHeadInDoublyList(ls1);
    // printDoubleList(ls1);
    // stackInt *stk = CreateStackInt();
    // pushInStackInt(stk,100);
    // printf("%d\n",peek(stk));
    // pushInStackInt(stk,2);
    // printf("%d\n",peek(stk));
    // popInStackInt(stk);
    // printf("%d\n",peek(stk));
    // printf("%d\n",isEmpty(stk));
    // popInStackInt(stk);
    // printf("%d\n",isEmpty(stk));
    // stackDynamic* stk = CreateStackDynamic();
    // pushInDynamicStack(stk,1);
    // printf("%d\n",topInDynamicStack(stk));
    // pushInDynamicStack(stk,2);
    // printf("%d\n",topInDynamicStack(stk));
    // pushInDynamicStack(stk,11);
    // printf("%d\n",topInDynamicStack(stk));
    // pushInDynamicStack(stk,12);
    // printf("%d\n",topInDynamicStack(stk));
    // popInDynamicStack(stk);
    // printf("%d\n",topInDynamicStack(stk));
    // popInDynamicStack(stk);
    // printf("%d\n",topInDynamicStack(stk));
    // printf("%d\n",isEmptyDynamicStack(stk));
    // popInDynamicStack(stk);
    // printf("%d\n",topInDynamicStack(stk));
    // popInDynamicStack(stk);
    // printf("%d\n",isEmptyDynamicStack(stk));
    return 0 ;
}