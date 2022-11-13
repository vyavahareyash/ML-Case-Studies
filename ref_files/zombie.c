#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>	// For fork() systemcall and pid_t data type
#define MAX 20

void quicksort(int a[],int,int);		//prototype of Quick sort
void merge(int a[], int low, int mid, int high);	//prototype of Merge sort
void divide(int a[], int low, int high);

int main()

{
	pid_t pid;	// Decleration of pid which will store process ID
	int a[MAX],n;
	int i;

	// Accepting Elements of an array

	printf("\n\tEnter the no. of elements: ");
	scanf("%d",&n);
	printf("\n\tEnter the elements: \n");
	for(i=0;i<n;i++)
	{
		printf("\t");
		scanf("%d",&a[i]);
	}

	/* =====Performing fork() system call==== */
	pid=fork();
if(pid<0)		// If Process not created successfully

	{
		printf("Error While creating a new process.....!!!!!!");
	}
	
else if(pid==0)		// For Child process

	{
		printf("\n\t==============Child process started=============");
		printf("\n\tI am a child process with pid=%d and ppid=%d",getpid(),getppid());
		quicksort(a,0,n-1);	//Performing quick sort in child process
		printf("\n\n\tSorted array by quick sort:\n\t");
		
		for(i=0;i<n;i++)

			printf("%d\t",a[i]);
			printf("\n");
	
		printf("\n\t==============Child process terminated=============\n");
	}

	else			// For Parent process
	
	{
	        // For Zombie process
		printf("\n\t==============Parent process started=============");
		printf("\n\n\tI am a parent process with pid=%d ",getpid());

		divide(a, 0, n-1);	//Performing merge sort in parent process
		printf("\n\n\tSorted array by merge sort:\n\t");
		for(i=0;i<n;i++)
			printf("%d\t",a[i]);
		printf("\n");
		printf("\n\t==============Parent process terminated=============\n");

	}
execl("/bin/ps","ps",NULL);
return 0;
}
	/* ==== Definition of Quick Sort ====*/

void quicksort(int a[MAX],int first,int last)
{
	int pivot,j,i,temp;
	if(first<last)
	{
		i=first;
		j=last;
		pivot=first;
		while(i<j)
		{
			while(a[i]<=a[pivot] && i<last)
				i++;
			while(a[j]>a[pivot])
				j--;
			if(i<j)
			{
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
		temp=a[j];
		a[j]=a[pivot];
		a[pivot]=temp;
		quicksort(a,first,j-1);
		quicksort(a,j+1,last);
	}

}
	/* ==== Definition of Merge Sort ====*/

void divide(int a[MAX], int low, int high)
{
	if(low<high) // The array has atleast 2 elements
	{
		int mid = (low+high)/2;
		divide(a, low, mid);     // Recursion chain to sort first half of the array
		divide(a, mid+1, high);  // Recursion chain to sort second half of the array
		merge(a, low, mid, high);
	}
}
void merge(int a[MAX], int low, int mid, int high)
{
	int i, j, k, m = mid-low+1, n = high-mid;
	int first_half[m], second_half[n];

	for(i=0; i<m; i++)  // Extract first half (already sorted)
	first_half[i] = a[low+i];

	for(i=0; i<n; i++)  // Extract second half (already sorted)
		second_half[i] = a[mid+i+1];
	i=j=0;
	k = low;

	while(i<m || j<n)  // Merge the two halves
	{
		if(i >= m)
		{
			a[k++] = second_half[j++];
			continue;
		}
		if(j >= n)
		{
			a[k++] = first_half[i++];
			continue;
		}
		if(first_half[i] < second_half[j])
			a[k++] = first_half[i++];
		else
			a[k++] = second_half[j++];
	}
}
