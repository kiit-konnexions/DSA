#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int partition (int *arr, int low, int high) {
	int pivot = arr[high];
	int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(int *arr, int low, int high) {
	if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
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

    quickSort(ar, 0, n-1);
	printf("Sorted array : ");
	print(ar, n);
	return 0;
}

// Time Complexity: O(n^2), θ(nlogn), Ω(nlogn)
// Space Complexity: O(logn) (for recursion)