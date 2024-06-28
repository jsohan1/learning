#include<stdio.h>
#include<stdlib.h>

typedef struct singleListNode singleListNode;
typedef struct doubleListNode doubleListNode;
typedef struct singlyList singlyList;
typedef struct doublyList doublyList;
typedef struct stackInt stackInt;
typedef struct stackDynamic stackDynamic;
int length(char* str){
    int i = 0 ;
    while(str[i]!='\0'){
        i++;
    }
    return i ;
}
struct stackDynamic{
    char *arr;
    int size;
    int top;
};
stackDynamic* CreateStackDynamic(){
    stackDynamic* newstack = (stackDynamic*)malloc(sizeof(stackDynamic));
    newstack->arr = (char*)malloc(sizeof(char)*10);
    newstack->size = 10;
    newstack->top = -1;
    return newstack;
}
void pushInDynamicStack(stackDynamic* stk,char val){
    if(stk->size==stk->top+1){
        stk->arr = (char*)realloc(stk->arr,stk->size * 2);
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
char topInDynamicStack(stackDynamic* stk){
    return stk->arr[stk->top];
}
int isEmptyDynamicStack(stackDynamic*stk){
    return stk->top == -1;
}
int value(char ch){
    switch(ch){
        case '+' : return 1; 
        break;
        case '-' : return 1 ;
        break;
        case '*' : return 2 ; 
        break;
        case '/' : return 2;
        break;
        }
}
char* infixToPostfix(char * infix){
    int n = length(infix);
    // printf("%d",n);
    stackDynamic* stk = CreateStackDynamic();
    char* postfix = (char*)malloc(sizeof(char)*(200));
    int ind = 0 ;
    for(int i = 0; i < n; i ++){
        // printf("at %d",i);
        if(infix[i] >= '0' && infix[i] <='9'){
            while(i<n && ( infix[i] >= '0' && infix[i] <='9')){
                postfix[ind] = infix[i];
                ind++;
                i++;
            }
            postfix[ind] = ' ';
            ind++;
            i--;
        }   
        else{
            if(infix[i]=='('){
                pushInDynamicStack(stk,'(');
            }
            else{
                if(infix[i]==')'){
                    while(!isEmptyDynamicStack(stk) && topInDynamicStack(stk)!='('){
                        postfix[ind] = topInDynamicStack(stk);
                        ind++;
                        postfix[ind]= ' ';
                        ind++;
                        popInDynamicStack(stk);
                    }
                    popInDynamicStack(stk);
                }
                else{
                    while(!isEmptyDynamicStack(stk)  && (topInDynamicStack(stk) != '(' && value(topInDynamicStack(stk)))>=value(infix[i])){
                        postfix[ind] = topInDynamicStack(stk);
                        ind++;
                        postfix[ind]= ' ';
                        ind++;
                        popInDynamicStack(stk);
                    }
                    pushInDynamicStack(stk,infix[i]);
                }
            }
        }
    }
    while(!isEmptyDynamicStack(stk)){
        postfix[ind] = topInDynamicStack(stk);
        postfix[ind+1]=' ';
        ind+=2;
        popInDynamicStack(stk);
    }
    postfix[ind] = '\0';
    int m = length(postfix);
    postfix = (char*)realloc(postfix,m);
    return postfix;
}
int main(){
    char* infix = (char*)malloc(sizeof(char)*100);
    scanf("%s",infix);
    char* postfix = infixToPostfix(infix);
    printf("%s",postfix);
    return 0 ;
}