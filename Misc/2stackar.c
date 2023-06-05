#include <stdio.h>
#include <stdlib.h>
struct Stack {
    int t1,t2, *arr;
    unsigned m,n;
}*stack;
 
void create(){
    stack = malloc(sizeof(struct Stack));
    printf("Enter capacity of the 2 stacks : ");   
    scanf("%d%d",&stack->m,&stack->n);
    stack->t1 = -1; stack->t2 = stack->m-1;
    stack->arr = (int*)malloc((stack->m+stack->n) * sizeof(int));
}
void push(int x){
    if((x==1 && stack->t1 == stack->m-1) ||
    (x==2 && stack->t2 == stack->m+stack->n-1))
        printf("stack %d Overflow\n",(x==1)?1:2);
    else{  
        printf("Enter the value : ");
        if(x==1) scanf("%d",&stack->arr[++stack->t1]);
        else scanf("%d",&stack->arr[++stack->t2]);
    }
} 
void pop(int x){ 
    if((x==1 && stack->t1 == -1) ||
    (x==2 && stack->t2 == stack->m-1))
        printf("stack %d Underflow\n",(x==1)?1:2);
    else{
        if(x==1) printf("%d popped\n",stack->arr[stack->t1--]);
        else printf("%d popped\n",stack->arr[stack->t2--]);
    }
}
void peek(int x){
    if(x==1) printf((stack->t1!=-1)?"Element at top of stack 1 : %d\n"
            :"Stack 1 Empty\n",stack->arr[stack->t1]);
    else
    printf((stack->t2!=stack->m-1)?"Element at top of stack 2 : %d\n"
            :"Stack 2 Empty\n",stack->arr[stack->t2]);
}
void display(int x){
    if((x==1 && stack->t1 == -1) ||
    (x==2 && stack->t2 == stack->m-1))  printf("Underflow");
    int top=(x==1)?stack->t1:stack->t2;
    int bot=(x==1)?0:stack->m;
    for(int i=top;i>=bot;i--)  
        printf("%d ",stack->arr[i]);
    printf("\n");
}
int main (){
    create(); int ch,x;
    printf("1. Push\n2. Pop\n3. Peek\n4. Display\n5. Exit\n");
    printf("Enter function no and stack (1 or 2) as Input\n");
    while(1){  
        choice:
        printf("\nEnter your choice : ");
        scanf("%d%d",&ch,&x);
        if(x>2 || x<1){
            printf("Enter 1 or 2\n"); 
            goto choice;
        }
        if(ch==1) push(x);
        else if(ch==2) pop(x);
        else if(ch==3) peek(x);
        else if(ch==4) display(x);
        else if(ch==5) break;
        else printf("Please Enter valid choice ");
    }
    return 0;
}