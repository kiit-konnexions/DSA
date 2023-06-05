#include<stdio.h>
#include<stdlib.h>
int *create(int *ar, int n){
    printf("Enter elements : ");
    for(int i=0; i<n; i++)
        scanf("%d",ar+i);
    return ar;
}
void print(int *ar, int n){
    for(int i=0; i<n; i++)
        printf("%d ",*(ar+i));
}
void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}
void insert(int *ar, int n){
    ar = realloc(ar, (++n)*sizeof(int));
    printf("Enter the index and element : ");
    int pos; scanf("%d",&pos);
    int new; scanf("%d",&new);
    for(int i=0; i<n; i++)
        if(i >= pos)
            swap(&new, ar+i);
    printf("After Insertion : ");
    print(ar, n);
}
void delete(int *ar, int n){
    printf("Enter the index : ");
    int pos; scanf("%d",&pos);
    for(int i=0; i<n-1; i++)
        if(i >= pos)
            swap(ar+i,ar+i+1);
    ar = realloc(ar, (--n)*sizeof(int));;
    printf("After Deletion : ");
    print(ar, n);
}
void search(int *ar, int n){
    printf("Enter element to be searched : ");
    int pos; scanf("%d",&pos);
    for(int i=0; i<n; i++)
        if(*(ar+i) == pos){
            printf("Found at index : %d",i);
            return;
        }
    printf("Element Not Found");
}
void update(int *ar, int n){
    printf("Enter the index and updated value : ");
    int pos; scanf("%d",&pos);
    int new; scanf("%d",&new);
    *(ar+pos) = new;
    printf("Updated Array : ");
    print(ar, n);
}
void reverse(int *ar, int n){
    for(int i=0; i<n/2; i++)
        swap(ar+i, ar+n-1-i);
    printf("Reverse Array : ");
    print(ar, n);
}
void sort(int *ar, int n){
    for(int i=0; i<n; i++){
        int flag = 0;
        for(int j=0; j<n-i-1; j++){
            if(ar+j > ar+j+1){
                swap(ar+j, ar+j+1);
                flag = 1;
            }
        }
        if(flag==0) break;
    }
    printf("Sorted Array : ");
    print(ar, n);
}
int merge(int *ar, int n){
    printf("Enter no. of elements : ");
    int m; scanf("%d",&m);
    int *arr1 = malloc(m*sizeof(int));
    arr1 = create(arr1,m);
    int i = n; n += m; 
    ar = realloc(ar,n*sizeof(int));
    for(int j=0; i<n; i++, j++)
        *(ar+i) = *(arr1+j);
    printf("Merged Array : ");
    print(ar, n);
}
int main(){
    printf("Enter no. of elements : ");
    int n; scanf("%d",&n);
    int ch, *arr = malloc(n*sizeof(int));
    arr = create(arr,n);
    print(arr, n);
    printf("\n1. Insert an element");
    printf("\n2. Delete an element");
    printf("\n3. Search an element");
    printf("\n4. Update an element");
    printf("\n5. Reverse the array");
    printf("\n6. Sort the array");
    printf("\n7. Merge the array");
    printf("\n0. Exit program");
    while(1){
        printf("\n\nEnter Choice : ");getchar();
        scanf("%d",&ch);
        if(ch == 1) insert(arr, n);
        else if(ch == 2) delete(arr, n);
        else if(ch == 3) search(arr, n);
        else if(ch == 4) update(arr, n);
        else if(ch == 5) reverse(arr, n);
        else if(ch == 6) sort(arr, n);
        else if(ch == 7) merge(arr, n);
        else if(ch == 0) break;
        else printf("Wrong Input\n");
    }
    return 0;
}