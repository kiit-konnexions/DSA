#include <stdio.h>
#include <stdlib.h>
struct Stack {
    int top, *arr;
    unsigned size;
};
struct Stack *createStack(){
    struct Stack *stack = malloc(sizeof(struct Stack));
    printf("Enter size of the stack : ");   
    scanf("%d",&stack->size);
    stack->top = -1;
    stack->arr = (int*)malloc(stack->size * sizeof(int));
    return stack;
}

void push(struct Stack *stack, int k){
    if(stack->top == stack->size-1)
        printf("Overflow\n");
    else stack->arr[++stack->top] = k;
} 
int pop(struct Stack *stack){ 
    if(stack->top == -1)  {
        printf("Underflow\n");
        return -1;
    }
    else return stack->arr[stack->top--];
}
   
int display(struct Stack *stack){
    if(stack->top == -1) printf("Stack is empty");
    for(int i=stack->top; i>=0; i--)  
        printf("%d ",stack->arr[i]);
    printf("\n");
}
int main (){
    struct Stack *stack = createStack(); int ch, val;
    printf("1. Push\n2. Pop\n3. Display\n0. Exit\n");  
    while(1){  
        printf("\nEnter your choice : ");
        scanf("%d",&ch);  
        if(ch == 1) {
            printf("Enter the value : ");
            scanf("%d",&val);
            push(stack, val);
        }
        else if(ch == 2) {
            int val=pop(stack);
            if(val!=-1) printf("%d popped\n",val);
        }
        else if(ch == 3) display(stack);
        else if(ch == 0) break;
        else printf("Please Enter valid choice ");
        printf((stack->top!=-1)?"Element at top : %d\n"
            :"Empty\n",stack->arr[stack->top]);
    }
    return 0;
}