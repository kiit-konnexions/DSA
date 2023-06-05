#include <stdio.h>
#include <stdlib.h>

void merge(int *arr, int l, int m, int r) {
	int n1 = m-l+1;
    int *L = malloc(n1 * sizeof(int));
    for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];

	int n2 = r-m;
	int *R = malloc(n2 * sizeof(int));
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	int i = 0, j = 0, k = l;
	while (i < n1 && j < n2) {
		arr[k++] = L[i] <= R[j] ? L[i++] : R[j++];
	}
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}
void mergeSort(int arr[], int l, int r) {
	if (l < r) {
        int m = l + (r-l) / 2;
        mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
	}
}

void print(int *arr, int size) {
	for (int i=0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int main() {
    printf("Enter no. of elements : ");
    int n; scanf("%d", &n);
    int *ar = malloc(n * sizeof(int));
    printf("Enter Elements : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &ar[i]);
	
    printf("Original array : ");
	print(ar, n);

    mergeSort(ar, 0, n-1);
	printf("Sorted array : ");
	print(ar, n);
	return 0;
}

// Time Complexity: O(nlogn), θ(nlogn), Ω(nlogn)
// Space Complexity: O(n)