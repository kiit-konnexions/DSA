#include <stdio.h>
#include <stdlib.h>
void swap(int *x, int *y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

typedef struct Heap {
	int *harr; // pointer to array of elements in heap
	int capacity; // maximum possible size of min heap
	int size; // Current number of elements in min heap
} heap;

heap *createMaxHeap(){
    heap *root = malloc(sizeof(heap));
    printf("Enter size of the Heap : ");   
    scanf("%d",&root->capacity);
    root->size = 0;
    root->harr = malloc(root->capacity * sizeof(int));
    return root;
}

int parent(int i) { return (i-1)/2; }
// to get index of left child of node at index i
int left(int i) { return (2*i + 1); }
// to get index of right child of node at index i
int right(int i) { return (2*i + 2); }

void insert(heap *root, int k) {
	if (root->size == root->capacity) {
		printf("\nOverflow: Could not insertKey\n");
		return;
	}

	// First insert the new key at the end
	root->size++;
	int i = root->size - 1;
	root->harr[i] = k;

	// Fix the max heap property if it is violated
	while (i != 0 && root->harr[parent(i)] < root->harr[i]) {
        swap(&(root->harr[i]), &(root->harr[parent(i)]));
        i = parent(i);
	}
}

void print(heap* root) {
    for (int i=0; i<root->size; i++) {
        printf("%d ", root->harr[i]);
    }
    printf("\n");
}

void heapify(heap* root, int i) {
    int l = left(i), r = right(i), m = i;
    if (l < root->capacity && root->harr[i] < root->harr[l])
        m = l;
    if (r < root->capacity && root->harr[m] < root->harr[r])
        m = r;
    if (m != i) {
        swap(&(root->harr[m]), &(root->harr[i]));
        heapify(root, m);
    }
}
int extractMax(heap* root) {
    if (!(root->capacity)) return -1;
    int m = root->harr[0];
    root->harr[0] = root->harr[root->capacity-- - 1];
    heapify(root, 0);
    return m;
}
int kThGreatest(heap* root, int k) {
    for (int i = 1; i < k; ++i)
        extractMax(root);
    return extractMax(root);
}

int main() {
    //Max Heap array : 20 15 18 8 10 5 17
    //k = 4, out = 15 
	heap *root = createMaxHeap(); int in;
    printf("Enter Elements : ");
    while(root->size < root->capacity){
        scanf("%d", &in);
        insert(root, in);
	}
    printf("Max Heap : ");
    print(root);
    
    printf("Enter k : ");
    scanf("%d", &in);
    printf("%dth largest element : %d\n",in, kThGreatest(root, in));
	return 0;
}