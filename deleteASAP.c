#include<stdio.h>
#include<stdlib.h>

typedef struct heapString heapString;

struct heapString{
    char** arr;
    int size;
    int capacity;
};
int length(char* str){
    int i = 0; 
    while(str[i]!='\0'){
        i++;
    }
    return i;
}
void stringCopy(char* str1,char* str2){
    int i = 0; 
    // printf("cpying\n");
    while(str2[i]!='\0'){
        str1[i] = str2[i];
        // printf("%c ",str2[i]);
        i++;
    }
    str1[i]='\0';
    // printf("\n");
}
heapString* CreateHeapString(){
    heapString *hp = (heapString*)malloc(sizeof(heapString));
    hp->arr = (char**)malloc(sizeof(char*)*10);
    hp->size = 0 ;
    hp->capacity = 10; 
    return hp;
}

int isLess(char* str1,char* str2){
    int i = 0;
    while(str1[i]!='\0' && str2[i]!='\0'){
        if(str1[i]==str2[i]){
            i++;
        }
        else{
            if(str1[i]<str2[i]){
                return 1 ;
            }
            else{
                return 0 ;
            }
        }
    }
    if(str1[i]=='\0' && str2[i]=='\0'){
        return 1 ;
    }
    else{
        if(str1[i]=='\0'){
            return 1; 
        }
        else{
            return 0;
        }
    }
}
void insertInHeap(heapString* hp,char* str){
    int n = length(str);
    // printf("len : %d\n",n);
    hp->arr[hp->size] = (char*)malloc(sizeof(char)*(n+1));
    int i = hp->size;
    stringCopy(hp->arr[hp->size],str);
    // printf("%s %s\n",hp->arr[hp->size],str);
    // printf("comparing for %s\n",str);
    while(i>=1){
        // printf("compared %s %s\n",hp->arr[i],hp->arr[(i-1)/2]);
        if(isLess(hp->arr[i],hp->arr[(i-1)/2])){
            // printf("swaped\n");
            char * temp = hp->arr[i];
            hp->arr[i] = hp->arr[(i-1)/2];
            hp->arr[(i-1)/2] = temp;
            i = (i-1)/2;
        }
        else{
            break;
        }
    }
    hp->size+=1;
}
void deleteInHeapString(heapString* hp){
    char * temp = hp->arr[0];
    hp->arr[0] = hp->arr[hp->size-1];
    hp->arr[hp->size-1] = temp;
    hp->size-=1;
    int i = 0 ;
    while(2*i+1<hp->size){
        int cn ;
        if(2*i+2<hp->size && isLess(hp->arr[2*i+2],hp->arr[2*i+1])){
            cn = 2*i+2;
        }
        else{
            cn = 2*i+1;
        }
        if(isLess(hp->arr[cn],hp->arr[i])){
            char * temp = hp->arr[cn];
            hp->arr[cn] = hp->arr[i];
            hp->arr[i] = temp;
            i = cn;
        }
        else{
            break;
        }
    }
}
char* top(heapString* hp){
    return hp->arr[0];
}
void printHeap(heapString * hp){
    printf("the heap : ");
    for(int i = 0 ; i < hp -> size; i++){
        printf("%s ",hp->arr[i]);
    }
    printf("\n");
}
void heapSortString(char**arr,int n){
    for(int i = 0 ; i < n ; i++){
        int j = i; 
        while(i>=1){
            // printf("compared %s %s\n",hp->arr[i],hp->arr[(i-1)/2]);
            if(!isLess(arr[i],arr[(i-1)/2])){
                // printf("swaped\n");
                char * temp = arr[i];
                arr[i] = arr[(i-1)/2];
                arr[(i-1)/2] = temp;
                i = (i-1)/2;
            }
            else{
                break;
            }
        }
        i = j;
    }
    printf("heap : ");
    for(int i = 0; i < n; i++){
        printf("%s ",arr[i]);
    }
    printf("\n");
    int size = n; 
    for(int i = 0 ; i < n ; i++){
        char * temp = arr[0];
        arr[0] = arr[size-1];
        arr[size-1] = temp;
        size-=1;
        int j = i ;
        i = 0 ;
        while(2*i+1<size){
            int cn ;
            if(2*i+2<size && !isLess(arr[2*i+2],arr[2*i+1])){
                cn = 2*i+2;
            }
            else{
                cn = 2*i+1;
            }
            if(!isLess(arr[cn],arr[i])){
                char * temp = arr[cn];
                arr[cn] = arr[i];
                arr[i] = temp;
                i = cn;
            }
            else{
                break;
            }
        }
        i = j ;
    }
    printf("Sorted v : ");
    for(int i = 0; i < n; i++){
        printf("%s ",arr[i]);
    }
}
int main(){
    // heapString* hp = CreateHeapString();
    // insertInHeap(hp,"s");
    // printHeap(hp);
    // insertInHeap(hp,"axyz");
    // printHeap(hp);
    // insertInHeap(hp,"a");
    // printHeap(hp);
    // insertInHeap(hp,"bcd");
    // printHeap(hp);
    // insertInHeap(hp,"ba");
    // printHeap(hp);
    // deleteInHeapString(hp);
    // printHeap(hp);
    // deleteInHeapString(hp);
    // printHeap(hp);
    int n ;
    scanf("%d",&n);
    char** arr;
    arr = (char**)malloc(sizeof(char*)*n);
    for(int i = 0 ; i < n ; i++){
        arr[i] = (char*)malloc(sizeof(char)*100);
    }
    for(int i = 0 ; i < n ; i++){
        scanf("%s",arr[i]);
    }
    heapSortString(arr,n);
    return 0 ;
}