#include<stdio.h>
#include<stdlib.h>

typedef struct hashmap hashmap;
typedef struct node node;
typedef struct pair pair;
typedef struct heap heap;
struct heap{
    pair**arr;
    int size;
};
struct pair{
    int first,second;
};
struct node{
    int key,val;
    node*next;
};
struct hashmap{
    node**arr;
    int load,size;
};
heap* CreateHeap(){
    heap* mp = (heap*)malloc(sizeof(heap));
    mp->arr = (pair**)malloc(sizeof(pair*)*50);
    for(int i = 0 ; i < 50 ; i++){
        mp->arr[i]=NULL;
    }
    mp->size = 0 ;
    return mp;
}
pair* CreatePair(int first,int second){
    pair* pr = (pair*)malloc(sizeof(pair));
    pr->first = first;
    pr->second = second;
    return pr;
}
hashmap* CreateMap(){
    hashmap* mp = (hashmap*)malloc(sizeof(hashmap));
    mp->arr = (node**)malloc(sizeof(node*)*50);
    for(int i = 0 ; i < 50 ; i++){
        mp->arr[i]=NULL;
    }
    mp->load = 0 ;
    mp->size = 50;
    return mp;
}
int isLess(pair* pr1,pair* pr2){
    if(pr1->first<pr2->first){
        return 1; 
    }
    else{
        if(pr1->first==pr2->first && pr1->second <pr2->second){
            return 1; 
        }
        else{
            return 0 ;
        }
    }
}
void insertInHeap(heap* hp,int first,int second){
    pair* val = CreatePair(first,second);
    hp->arr[hp->size] = val;    
    int i = hp->size;
    while(i>=1){
        if(!isLess(hp->arr[(i-1)/2],hp->arr[i])){
            pair* temp = hp->arr[(i-1)/2];
            hp->arr[(i-1)/2] = hp->arr[i];
            hp->arr[i] = temp;
            i = (i-1)/2;
        }
        else{
            break;
        }
    }
    hp->size+=1;
}
void deleteInHeap(heap* hp){
    pair* temp = hp->arr[0];
    hp->arr[0] = hp->arr[hp->size-1];
    hp->arr[hp->size-1] = temp;
    free(hp->arr[hp->size-1]);
    hp->size -= 1; 
    int i = 0;
    while(2*i+1<hp->size){
        int cn;
        if( 2*i+2<hp->size && !isLess(hp->arr[2*i+1],hp->arr[2*i+2])){
            cn = 2*i+2;
        }
        else{
            cn = 2*i+1;
        }
        if(!isLess(hp->arr[i],hp->arr[cn])){
            pair* temp = hp->arr[i];
            hp->arr[i] = hp->arr[cn];
            hp->arr[cn] = temp;
            i = cn;
        }
        else{
            break;
        }
    }
}
pair top(heap* hp){
    return *(hp->arr[0]);
}

void insertInMap(hashmap*mp,int key){
    int val  =key;
    if(val<0){
        val = -key;
    }
    // printf("inserting in map\n");
    int hashkey = val % mp->size;
    node* head = mp->arr[hashkey];
    // printf("At hasheky %d\n",hashkey);
    while(head){
        if(head->key == key){
            // printf("found\n");
            head->val ++;
            return;
        }
        head = head->next;
    }
    node* newnode = (node*)malloc(sizeof(node));
    newnode->key = key;
    newnode->val = 1; 
    newnode->next = mp->arr[hashkey];
    mp->arr[hashkey] = newnode;
}
int getInMap(hashmap* mp,int key){
    if(key<0){
        key = -key;
    }
    int hashkey = key % mp->size;
    node* head = mp->arr[hashkey];
    while(head){
        if(head->key == key){
            return head->val;
        }
        head = head->next;
    }
    return 0;
}
void printHeap(heap* hp){
    for(int i = 0 ; i < hp->size; i++){
        printf("%d %d -- ",hp->arr[i]->first,hp->arr[i]->second);
    }
    printf("\n");
}
void findKmostFrequent(int *arr,int n ,int k){
    hashmap* mp = CreateMap();
    for(int i = 0 ; i < n ; i ++){
        insertInMap(mp,arr[i]);
        // printf("inserting\n");
    }
    heap *hp = CreateHeap();
    int j = 0 ; 
    for(int i = 0 ; i < mp->size; i++){
        node* head = mp->arr[i];
        // printf("in map at %d\n",i);
        while(head){
            // printf("inserting %d %d \n",head->val,head->key);
            insertInHeap(hp,head->val,head->key);
            j++;
            if(j==k+1){
                j--;
                deleteInHeap(hp);
            }
            head = head->next;
        }
    } 
    printf("K most frequent elemnt : ");
    for(int i = 0 ; i < hp->size ; i++){
        printf("%d ",hp->arr[i]->second);
    }
}
int main(){
    hashmap*mp =CreateMap();
    // insertInMap(mp,1);
    // insertInMap(mp,3);
    // insertInMap(mp,3);
    // printf("%d",getInMap(mp,3));
    int n ;
    printf("no. of elements : ");
    scanf("%d",&n);
    printf("Values : ");
    int *arr = (int*)malloc(sizeof(int)*n);
    for(int i = 0 ; i < n ; i ++){
        scanf("%d",arr+i);
    }
    int k ;
    printf("how many frequent no. you want to know : ");
    scanf("%d",&k);
    findKmostFrequent(arr,n,k);
    return 0 ;
}