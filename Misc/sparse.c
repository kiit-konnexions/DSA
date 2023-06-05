#include<stdio.h>
#include<stdlib.h>
void in(int **arr, int m){
    for(int i=0; i<m; i++){
        printf("\nElement %d : \n",i+1);
        printf("Row : ");
        scanf("%d",&arr[i][0]);
        printf("Col : ");
        scanf("%d",&arr[i][1]);
        printf("Val : ");
        scanf("%d",&arr[i][2]);
    }
}

int **matsum(int **mat1, int m, int **mat2, int n, int **sum){
    int r1, r2, c1, c2;
    //the summing part (m<n)
    for(int i=0; i<n; i++){
        if(i<m){
            r1 = mat1[i][0]; c1 = mat1[i][1];
            sum[r1][c1] += mat1[i][2];
        }
        r2 = mat2[i][0]; c2 = mat2[i][1];
        sum[r2][c2] += mat2[i][2];
    }
    return sum;
}

void out(int **ar, int r, int c){
    printf("\nSum : \nRow\tCol\tVal\n");
    for(int i=0; i<r; i++)
        for(int j=0; j<c; j++)
	    if(ar[i][j])
            printf("%d\t%d\t%d\n",i,j,ar[i][j]);
}

int main(){
    int i, r1, r2, c1, c2, n1, n2, **ar, **br;
    printf("Enter no. of rows and column for matrix 1: ");
    scanf("%d%d",&r1,&c1);
    printf("Enter no. of rows and column for matrix 2: ");
    scanf("%d%d",&r2,&c2);
    if(r1!=r2 && c1!=c2){
        printf("Summation not possible.");
        return 0;
    }

    printf("Enter no. of non-0 Elements in matrix 1 : ");
    scanf("%d",&n1);
    printf("Enter no. of non-0 Elements in matrix 2 : ");
    scanf("%d",&n2);
    //Dynamic allocation of memory
    ar=malloc(n1*sizeof(int *));
    for(i=0; i<n1; i++)
        ar[i] = malloc(3*sizeof(int));
    br=malloc(n2*sizeof(int *));
    for(i=0; i<n2; i++)
        br[i] = malloc(3*sizeof(int));
    
    //input
    printf("\nMatrix 1 inputs : ");
    in(ar, n1);
    printf("\nMatrix 2 inputs : ");
    in(br, n2);

    //initialising the sum matrix
    int **s = malloc(r1*sizeof(int *));
    for(i=0; i<r1; i++) 
        s[i] = calloc(c1,sizeof(int));
    
    s = (n1<n2)? matsum(ar,n1,br,n2,s) : matsum(br,n2,ar,n1,s);
    printf("\n");
    out(s, r1, c1);
    return 0;
}