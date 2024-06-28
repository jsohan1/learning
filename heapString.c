#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct heapString heapString;
struct heapString{
    char* * arr;
    int size, capacity;
    int (*camp)(char*,char*);
};
int length(char *str){
    int i = 0 ;
    while(str[i]!='\0'){
        i++;
    }
    return i; 
}
heapString * CreateHeapString(int (*camp)(char*,char*)){
    heapString* hp = (heapString*)malloc(sizeof(heapString));
    hp->arr = (char**)calloc(sizeof(char*),1);
    hp->size = 0; 
    hp->capacity = 1 ;
    hp->camp = camp;
    return hp ; 
}
int minString(char* str1,char *str2){
    int i = 0 ;
    while(1){
        if(str1[i]=='\0'||str2[i]=='\0'){
            break;
        }
        if(str1[i]==str2[i]){
            i++;
        }
        else{
            if(str1[i]<str2[i]){
                return 1; 
            }
            else{
                return 0 ;
            }
        }
    }
    if(str1[i]=='\0'&&str2[i]=='\0'){
        return 1; 
    }
    else{
        if(str1[i]=='\0'){
            return 1 ;
        }
        else{
            return 0 ;
        }
    }
}
void heapSort(char** arr,int n){
    // printf("Called\n");
    for(int i = 0 ; i < n; i++){
        int j = i ; 
        while(j>=1){
            if(minString(arr[(j-1)/2],arr[j])){
                char * temp = arr[(j-1)/2];
                arr[(j-1)/2] = arr[j];
                arr[j] = temp;
                j = (j-1)/2;
            }
            else{
                break;
            }
        }
    }
    // printf("heap : ");
    for(int i = 0;i < n ; i++){
        printf("%s ",arr[i]);
    }
    int size = n ;
    for(int i  = 0 ; i < n ;i++){
        char * temp = arr[0];
        arr[0] = arr[size-1];
        arr[size-1] = temp;
        int j = 0;
        size--;
        // printf("For %s\n",arr[0]);
        while( 2*j+1 < size){
            int cn;
            if(2*j+2 < size && minString(arr[2*j+1],arr[2*j+2])){
                cn = 2*j+2;
            }
            else{
                cn = 2*j+1;
            }
            // printf("At %d cpmparing with %d so ",j,cn);
            // printf("comparing %s and %s \n",arr[j],arr[cn]);
            if(minString(arr[j],arr[cn])){
                // printf("yes so sawping\n");
                char * temp = arr[j];
                arr[j] = arr[cn];
                arr[cn] = temp; 
                j = cn;
            }
            else{
                break;
            }
        }
    }
    printf("\nSorted  : ");
    for(int i = 0;i < n ; i++){
        printf("%s ",arr[i]);
    }
}

void stringCopy(char* str1, char* str2){
    int i = 0 ; 
    while(str2[i]!='\0'){
        str1[i] = str2[i];
        i++;
    }
    str1[i] = '\0';
}
void insertInHeapString(heapString * hp,char *str){
    if(hp->size==hp->capacity){
        hp->arr = (char**)realloc(hp->arr,hp->capacity*2);
        hp->capacity*=2;
    }
    int n = length(str);
    hp->arr[hp->size] = (char*)malloc(sizeof(char)*(n+1));
    stringCopy(hp->arr[hp->size],str);
    int i = hp->size;
    while(i>=1){
        if(hp->camp(hp->arr[i],hp->arr[(i-1)/2])){
            char * temp = hp->arr[i] ;
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
void delete(heapString* hp){
    char * str1 = hp->arr[hp->size-1];
    hp->arr[hp->size-1] = hp->arr[0];
    hp->arr[0] = str1;
    free(hp->arr[hp->size-1]);
    hp->size -= 1;
    int i = 0 ;
    while(2*i+1<hp->size){
        int cn ;
        if(2*i+2 < hp->size && hp->camp(hp->arr[2*i+2],hp->arr[2*i+1])){
            cn = 2*i+2;
        }
        else{
            cn = 2*i+1;
        }
        if(hp->camp(hp->arr[cn],hp->arr[i])){
            char * str1 = hp->arr[cn];
            hp->arr[cn] = hp->arr[i];
            hp->arr[i] = str1;
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
int main(){
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
    heapSort(arr,n);
    return 0 ;
}