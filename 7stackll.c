#include <stdio.h>
#include <stdlib.h>
typedef struct SNode{
    int data;
    struct SNode* link;
}Stack;
int popped, count = 0;

void push(Stack **stack, int data){
    Stack *new = malloc(sizeof(Stack));
    new->data = data;  new->link = *stack;
    *stack = new; count++;
}
int pop(Stack **stack){
    if (*stack){
        Stack *temp = *stack;
        int res = temp->data;
        *stack = temp->link;
        free(temp);
        return res;
    }
    printf("Stack Underflow\n");
}

void display(Stack *stack){
    if(stack){
        Stack *temp = stack;
        while(temp){
            printf("%d ",temp->data);
            temp = temp->link;
        }
        printf("\n");
    }
}
void delete(Stack **stack, int i, int pos){
    if(*stack){
        int temp = pop(stack);
        delete(stack,i+1,pos);
        if(i != pos) push(stack, temp);
    }
}

void insbot(Stack **stack, int item){
    if(!*stack)
        push(stack,item);
    else{
        int temp = pop(stack);
        insbot(stack, item);
        push(stack, temp);
    }
}
void reverse(Stack **stack){
    if(*stack){
        int item = pop(stack);
        reverse(stack);
        insbot(stack, item);
    }
}

void sortIns(Stack **stack, int item){
    if(!(*stack) || item>(*stack)->data)
        push(stack, item);
    else{
        int temp = pop(stack);
        sortIns(stack, item);
        push(stack, temp);
    }
}
void sort(Stack **stack){
    if(*stack){
        int x = pop(stack);
        sort(stack);
        sortIns(stack, x);
    }
}

int main(){
    Stack *stack = NULL;
    int ch,in;
    printf("1. Push\n2. Pop\n3. Display\n4. Reverse\n5. Sort\n6. Delete\n0. Exit\n");
    while(1){
        printf("\nEnter your choice : ");
        scanf("%d",&ch);
        if(ch == 1){
            printf("Enter the value : ");
            scanf("%d",&in);
            push(&stack, in);
        }
        else if(ch == 2){
            int del=pop(&stack);
            printf("%d popped\n",del);
        }
        else if(ch == 3) display(stack);
        else if(ch == 4) reverse(&stack);
        else if(ch == 5) sort(&stack);
        else if(ch == 6){
            int ind;
            printf("Enter index to be deleted : ");
            scanf("%d",&ind);
            if(ind<0 || ind>=count)
                printf("Index out of bounds\n");
            delete(&stack,0,ind);
        }
        else if(ch == 0) break;
        else printf("Please Enter valid choice\n");
        if(!stack) printf("Empty\n");
        else printf("Top element is %d\n", stack->data);
    }
    return 0;
}