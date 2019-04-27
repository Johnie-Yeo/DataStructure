#pragma warning(disable: 4996)

#include<stdio.h>

#define MAX 100

int binarySearch(int data[], int target, int begin, int end);

int main()
{
	int result_idx;
	int target;
	int data[MAX];
	int size;

	printf("Size: ");
	scanf("%d", &size);
	printf("Data: ");
	for (int i = 0;i < size;i++)
		scanf("%d", &data[i]);
	printf("Target: ");
	scanf("%d", &target);
	result_idx = binarySearch(data, target, 0, size - 1);
	if (result_idx == -1)
		printf("Failed.\n");
	printf("Result: %d\n", result_idx+1);

	return 0;
}
int binarySearch(int data[], int target, int begin, int end) {
	if (begin>end){
		if (data[end] < target)
			return end;
		else
			return -1;
	}  
	else {
		int middle = (begin + end) / 2;
		if (data[middle] == target)      
			return middle;    
		else if (data[middle] > target)
			return binarySearch(data, target, begin, middle - 1);
		else      
			return binarySearch(data, target, middle + 1, end);
	}
}