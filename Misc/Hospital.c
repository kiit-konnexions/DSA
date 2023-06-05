#include<stdio.h>
#include<stdlib.h>
struct patient{
    char gender, name[10], disease[10];
    struct patient *link;
}*wmh=NULL,*wmt=NULL,*wfh=NULL,*wft=NULL;
struct cabin{
    int no; char status;
    struct patient *pat;
    struct cabin *link;
}*master=NULL,*temp;

int countm=0, countf=0;
int n, mmax, lmax;
void create(){
    for(int i=1;i<=n;i++){
        struct cabin *new=malloc(sizeof(struct cabin));
        new->no=i; new->status='N';
        new->link=NULL; new->pat=NULL;
        if(!master){
            master=new; temp=new;
        }
        else{
            temp->link=new;
            temp=new;
        }
    }
}

void insert(struct patient **head,struct patient **tail,
            struct patient *new, int *count, int max, int t){
    if(*count<max){
        (*count)++; temp=t?master:master->link;
        while(temp){
            if(temp->status=='N'){
                temp->pat=new;
                temp->status='Y';
                break;
            }
            if(temp->link)
                temp=temp->link->link;
            else break;
        }
    }
    else{
        if(!(*head)){
            *head=new; *tail=new;
        }
        else{
            (*tail)->link=new;
            *tail=new;
        }
    }
}
void admit(){
    struct patient *new=malloc(sizeof(struct patient));
    printf("Enter Name : ");
    scanf("%s",new->name);
    ch:
    getchar();
    printf("Enter Gender : ");
    scanf("%c",&(new->gender));
    if(new->gender!='M' && new->gender!='m'
    && new->gender!='F' && new->gender!='f'){
        printf("Invalid Input\n"); goto ch;
    }
    printf("Enter disease : ");
    scanf("%s",new->disease);
    new->link=NULL;
    if(new->gender=='M'||new->gender=='m')
        insert(&wmh,&wmt,new,&countm,mmax,1);
    else if(new->gender=='F'||new->gender=='f')
        insert(&wfh,&wft,new,&countf,lmax,0);
}

void delete(struct patient **head){
    if(*head){
        temp->pat=*head;
        *head=(*head)->link;
    }
    else temp->status='N';
}
void discharge(){
    int in; temp=master;
    in:
    printf("Enter cabin no. : ");
    scanf("%d",&in);
    if(in>n || in<1){
        printf("Invalid input : ");
        goto in;
    }
    while(temp){
        if(temp->no==in){
            if(temp->status=='N'){
                printf("Already Vacant\n");
                return;
            }
            (in%2)?delete(&wmh):delete(&wfh);
            temp->pat->link=NULL;
            break;
        }
        temp=temp->link;
    }
}

void waiting(struct patient *pat,int t){
    char *s=t?"Male":"Female";
    if(!pat) printf("Waiting List for %s is Empty\n",s);
    else{
        printf("\n%s Waiting List :",s);
        while(pat){
            printf("\nName : %s\n",pat->name);
            printf("Gender : %c\n",pat->gender);
            printf("Disease : %s\n",pat->disease);
            pat=pat->link;
        }
    }
}
void display(){
    temp=master; int flag=1;
    while(temp){
        if(temp->status=='Y'){
            printf("Cabin No. : %d\n",temp->no);
            printf("Name : %s\n",temp->pat->name);
            printf("Gender : %c\n",temp->pat->gender);
            printf("Disease : %s\n",temp->pat->disease);
            printf("\n"); flag=0;
        }
        temp=temp->link;
    }
    if(flag) printf("Cabins are Empty\n");
    waiting(wmh,1);
    waiting(wfh,0);
}

int main(){
    int ch;
    in:
    printf("Enter the value of n : ");
    scanf("%d",&n);
    if(n<1){
        printf("Invalid Input\n");
        goto in;
    }
    mmax=n/2+n%2, lmax=n/2;
    create();
    printf("\nEnter 1. to admit");
    printf("\nEnter 2. to discharge");
    printf("\nEnter 3. to display");
    printf("\nEnter 0. to exit\n");
    while(1){
        printf("\nEnter your choice : ");
        scanf("%d",&ch);
        if(ch==1) admit();
        else if(ch==2) discharge();
        else if(ch==3) display();
        else if(ch==0) break;
        else printf("Wrong Input\n");
    }
    return 0;
}