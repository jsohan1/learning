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

int length(char* str){
    int i = 0 ;
    while(str[i]!='\0'){
        i++;
    }
    return i ;
}
int isEqual(char* str1,char*str2){
    int i = 0;
    while(str2[i]!='\0' && str1[i]!='\0'){
        if(str1[i]!=str2[i]){
            return 0 ;
        }
        i++;
    }
    if(str2[i]=='\0' && str1[i]=='\0'){
        return 1;
    }
    else{
        return 0;
    }
}
void stringCopy(char* str1,char*str2){
    int i = 0;
    while(str2[i]!='\0'){
        str1[i]=str2[i];
        i++;
    }
    str1[i] = '\0';
}
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
    nodeForHash**arr;
    int load,size;
};
struct nodeForHash{
    char* key;
    int val;
    nodeForHash* next;
};
char* sortString(char* str){
    int n = length(str);
    char *sortedString = (char*)malloc(sizeof(char)*(n+1));
    for(int i = 0 ; i < n; i++){
        sortedString[i] = str[i];
    }
    int ind;
    for(int i = 0 ; i < n ; i++ ){
        char mn = sortedString[i];
        ind = i ;
        for(int j = i ; j < n ; j++){
            if(mn >= sortedString[j]){   
                ind = j ;
                mn = sortedString[j];
            }
        }
        char ch = sortedString[i];
        sortedString[i] = mn;
        sortedString[ind] = ch ; 
    }
    sortedString[n] = '\0';
    return sortedString;
}
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
nodeForHash* CreateNodeForHash(char* key,int val){
    nodeForHash* newnode = (nodeForHash*)malloc(sizeof(nodeForHash));
    int n = length(key);
    newnode->key = (char*)malloc(sizeof(char)*(n+1));
    stringCopy(newnode->key,key);
    newnode->next = NULL;
    newnode->val = val;
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
    mp->arr = (nodeForHash**)calloc(sizeof(nodeForHash*),30);
    mp->load = 0; 
    mp->size = 30; 
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
void insertAtStringHash(stringHashmap* hp,char*key,int val){
    int hashkey = hashFunction(hp,key);
    nodeForHash* head = hp->arr[hashkey];
    while(head){
        if(isEqual(head->key,key)){
            head->val = val;
            return;
        }
        head = head->next;
    }   
    nodeForHash* newnode = CreateNodeForHash(key,val);
    newnode->next = hp->arr[hashkey];
    hp->arr[hashkey] = newnode;
}
int getAtStringHash(stringHashmap* mp,char* key){
    int hashkey = hashFunction(mp,key);
    nodeForHash* head = mp->arr[hashkey];
    while(head){
        if(isEqual(head->key,key)){
            return head->val;
        }
        head = head->next;
    }  
    return 0 ; 
}
void deleteInStringHash(stringHashmap*mp,char* key){
    int hashkey = hashFunction(mp,key);
    nodeForHash* head = mp->arr[hashkey];
    nodeForHash* par = head;
    while(head){
        if(isEqual(head->key,key)){
            if(par==head){
                mp->arr[hashkey] = mp->arr[hashkey]->next;
                free(par);
                return;
            }
            else{
                par->next = head->next;
                free(head);
                return;
            }
        }
        head = head->next;
    }  
}
void insertCustomHashString(stringHashmap* mp,char* str){
    char* sortedString = sortString(str);
    int hashkey = hashFunction(mp,sortedString);
    // printf("Sorted String :  %s",sortedString);
    nodeForHash* newnode = CreateNodeForHash(str,1);
    // printf("hashkey : %d\n",hashkey);
    for(int i = 0 ;i < mp->size; i++){
        if(mp->arr[(i+hashkey)%mp->size] == NULL){
        //    printf("creating new \n");
            mp->arr[(i+hashkey)%mp->size] = CreateNodeForHash(sortedString,1);
            mp->arr[(i+hashkey)%mp->size]->next =newnode;
            return;
        }
        if(isEqual(mp->arr[(i+hashkey)%mp->size]->key,sortedString)){
            // printf("inserting in same\n");
            newnode ->next = mp->arr[(i+hashkey)%mp->size]->next;
            mp->arr[(i+hashkey)%mp->size]->next = newnode;
            return;
        }
    }
}
void printHashmap(stringHashmap*mp){
    for(int i = 0 ; i < mp->size; i++){
        nodeForHash* head = mp->arr[i];
        if(head){
            nodeForHash* head1 = head->next;
            int flag = 0; 
            while(head1){
                flag = 1;
                printf("%s ",head1->key);
                head1=head1->next;
            }
            if(flag)printf("\n");
        }
    }
}
int main(){
    stringHashmap* mp = CreateStringHashmap();
    char * str ;
    while(1){
        str = (char*)malloc(sizeof(char)*100);
        scanf("%s",str);
        str = (char*)realloc(str,length(str));
        if(isEqual("END",str)){
            break;
        }
        insertCustomHashString(mp,str);
    }
    printHashmap(mp);
    return 0 ;
}