#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int row, col;
    float val;
    struct node *link;
}Node;

void newNode(Node **ptr,int row, int col, float val){
    if(val == 0) return; (*ptr)->val++;
    Node *new = malloc(sizeof(Node));
    new->row = row; new->col = col;
    new->val = val; new->link = NULL;
    if(*ptr == NULL)
        *ptr = new;
    else{
        Node *temp = *ptr;
        while(temp->link)
            temp = temp->link;
        temp->link = new;
    }
}
void display(Node *ptr){
    Node *temp = ptr;
    while(temp){
        printf("%d %d %.2f\n", temp->row, temp->col, temp->val);
        temp = temp->link;
    }
}
void remdup(Node **ptr){
    Node *prev, *dup;
    Node *t1 = (*ptr)->link;
    while (t1 && t1->link){
        Node *t2 = t1;
        while (t2->link){
            if (t1->row == t2->link->row
            && t1->col == t2->link->col) {
                t2->link->val += t1->val;
                dup = t1;
                if(t1 == (*ptr)->link)
                    (*ptr)->link = t1->link;
                else
                    prev->link = t1->link;
                t1 = t2 = t1->link;
                (*ptr)->val--;
            }
            else t2 = t2->link;
        }
        prev = t1; t1 = t1->link;
    }
}
void create(Node **ptr){
    check1:
    printf("Enter total row, column & non-zero elements : ");
    *ptr = malloc(sizeof(Node));
    scanf("%d%d%f",&(*ptr)->row,&(*ptr)->col,&(*ptr)->val);
    (*ptr)->link = NULL; 
    if((*ptr)->val > (*ptr)->row * (*ptr)->col){
        printf("Non zero elements exceeded\n");
        goto check1;
    }

    int r, c; float v, val = (*ptr)->val; 
    (*ptr)->val = 0; Node *temp = *ptr;
    printf("Enter Row, Column, Value for :\n");
    for(int i=0; i<val; i++){
        check2:
        printf("Input %d : ",i+1);
        scanf("%d%d%f",&r,&c,&v);
        if(r>(*ptr)->row || c>(*ptr)->col || r<1 || c<1){
            printf("Row or Column Exceeded\n");
            goto check2;
        }
        newNode(ptr, r, c, v);
    }
    printf("\nINPUT :\n");
    remdup(ptr); display(*ptr);
}
void add(Node *ptr1, Node *ptr2, int t){
    if(ptr1->row != ptr2->row && ptr1->col != ptr2->col){
        printf("\nAdd/Sub Not possible\n");
        return;
    }
    Node *sum = malloc(sizeof(Node));
    sum->row = ptr1->row; sum->col = ptr1->col;
    sum->val = 0; sum->link = NULL;
    Node *t1 = ptr1->link, *t2 = ptr2->link, *temp = sum;
    while(t1 && t2){
        if(t1->row == t2->row && t1->col == t2->col){
            newNode(&sum, t1->row, t1->col, t1->val + t*t2->val);
            t1 = t1->link;
            t2 = t2->link;
        }
        else if(t1->row < t2->row ||
        (t1->col<t2->col && t1->row<=t2->row)){
            newNode(&sum, t1->row, t1->col, t1->val);
            t1 = t1->link;
        }
        else{
            newNode(&sum, t2->row, t2->col, t*t2->val);
            t2 = t2->link;
        }
    }
    while(t1 != NULL){
        newNode(&sum, t1->row, t1->col, t1->val);
        t1 = t1->link;
    }
    while(t2 != NULL){
       newNode(&sum, t2->row, t2->col, t*t2->val);
       t2 = t2->link;
    }
    printf((t==1)?"\nSum :\n":"\nDiff :\n");
    display(sum);
}

void mul(Node *ptr1, Node *ptr2){
    if(ptr1->col != ptr2->row){
        printf("\nProduct Not possible\n");
        return;
    }
    Node *prod = malloc(sizeof(Node));
    prod->row = ptr1->row; prod->col = ptr2->col;
    prod->val = 0; prod->link = NULL;
    Node *t1 = ptr1->link, *temp=prod;
    while(t1){
        Node *t2 = ptr2->link;
        while(t2){
            if(t1->col == t2->row)
                newNode(&prod, t1->row, t2->col, (t1->val)*(t2->val));
            t2 = t2->link;
        }
        t1 = t1->link;
    }
    printf("\nProduct :\n");
    remdup(&(prod));
    display(prod);
}
int main(){
    Node *a, *b;
    printf("\nMatrix 1 :\n");
    create(&a);
    printf("\nMatrix 2 :\n");
    create(&b);
    add(a,b,1);
    add(a,b,-1);
    mul(a,b);
    return 0;
}