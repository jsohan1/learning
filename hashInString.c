#include<stdio.h>
#include<stdlib.h>

typedef struct listnode listnode;
typedef struct list list;
typedef struct hashString hashString;
int length(char* str){
    int i = 0 ;
    while(str[i]!='\0'){
        i++;
    }
    return i;
}
struct listnode{
    char*key;
    int val;
    listnode* next;
};
struct list{
    listnode* head,*tail;
};
struct hashString{
    list** arr;
    int load,size;
};
int hashFunction(hashString* hp, char* str){
    int sum = 0;
    int i = 0 ;
    while(str[i]!='\0'){
        sum += str[i];
        i++;
    }
    return sum % hp->size;
}

void stringCopy(char* str1,char* str2){
    int i = 0 ;
    while(str2[i]!='\0'){
        str1[i] = str2[i];
        i++;
    }
}
int isEqual(char* str1,char* str2){
    int i = 0 ;
    while(str1[i] != '\0' && str2[i] != '\0'){
        if(str1[i] == str2[i]){
            i++;
        }
        else{
            return 0 ;
        }
    }
    if(str1[i] == '\0' && str2[i] == '\0'){
        return 1;
    }
    else{
        return 0 ;
    }
}
list* CreateList(){
    list* ls = (list*)malloc(sizeof(list));
    ls->head = ls->tail = NULL;
    return ls;
}
listnode* CreateListNode(char *str,int val){
    listnode* newnode = (listnode*)malloc(sizeof(listnode));
    int n = length(str);
    newnode->key = (char*)malloc(sizeof(char)*(n+1));
    stringCopy(newnode->key,str);
    newnode->val = val;
    newnode->next = NULL;
    return newnode;
}
hashString* CreateHashString(){
    hashString* newnode = (hashString*)malloc(sizeof(hashString));
    newnode->arr = (list**)malloc(sizeof(list*)*4);
    for(int i = 0 ; i < 4 ;i++){
        newnode->arr[i] = CreateList();
    }
    newnode->load = 0; 
    newnode->size = 4 ;
    return newnode;
}
void insertInList(list* ls,char* key,int val){
    listnode* newnode = CreateListNode(key,val);
    if(ls->head==NULL){
        ls->head = ls->tail = newnode;
        return;
    }
    ls->tail->next = newnode;
    ls->tail = newnode;
}
void insertInHash(hashString * hp,char* key,int val){   
    int hashkey = hashFunction(hp,key);
    listnode* head = hp->arr[hashkey]->head;
    while(head){
        if(isEqual(head->key,key)){
            head->val = val;
            return;
        }
        head = head->next;
    }
    insertInList(hp->arr[hashkey],key,val);
}
int searchInHash(hashString* hp,char* key){
    int hashkey = hashFunction(hp,key);
    listnode* head = hp->arr[hashkey]->head;
    while(head){
        if(isEqual(head->key,key)){
            return 1;
        }
        head = head->next;
    }
    return 0;
}
void deleteInHash(hashString* hp,char *key){
    int hashkey = hashFunction(hp,key);
    listnode* head = hp->arr[hashkey]->head;
    listnode* par = head;
    while(head){
        if(isEqual(head->key,key)){
            if(par == head){
               hp->arr[hashkey]->head = hp->arr[hashkey]->head->next;
               free(par->key);
               free(par);
               return; 
            }
            else{
                par->next = head->next ;
                free(head->key);
                free(head);
                return;
            }
        }
        par = head;
        head = head->next;
    }
}
int getInHash(hashString*hp, char* key){
    int hashkey = hashFunction(hp,key);
    listnode* head = hp->arr[hashkey]->head;
    while(head){
        if(isEqual(head->key,key)){
            return head->val;
        }
        head = head->next;
    }
    return 0;
}
void printList(list* ls){
    listnode* head = ls->head;
    while(head){
        printf("%s %d",head->key,head->val);
        head = head->next;
    }
    printf("\n");
}
int main(){
    hashString * hp = CreateHashString();
    insertInHash(hp,"sohan",2);
    insertInHash(hp,"jai",4);
    deleteInHash(hp,"jai");
    printf("\n%d\n",getInHash(hp,"jai"));
    printf("\n%d\n",getInHash(hp,"sohan"));
    printf("\n%d\n",searchInHash(hp,"sohan"));
    deleteInHash(hp,"sohan");
    printf("\n%d\n",getInHash(hp,"sohan"));
    printf("\n%d\n",searchInHash(hp,"sohan"));
    return 0 ;
}