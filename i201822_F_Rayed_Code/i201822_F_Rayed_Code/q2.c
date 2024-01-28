//Rayed Muhammad Saeed
//20i-1822
//CS-F
//Task1
//PDC

#define _GNU_SOURCE //Libraries
#include <mpich/mpi.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include<math.h>

#define MAXLINE 1000

int *arr1; //declaration of the arrays
int *arr2;
int *arr3;
int *arr4;
int *arr5;
int *arr;
int *result;

void populateArray(int * ar,int size){ //to populate the arrays with random values
        int i=0;
        for (i=0;i<size;i++){
                ar[i]=rand() % 9999 +1;
        }
}

void writeInputFile(FILE *fp, int *ar,int size){ //to write to input file all the arrays
        fprintf(fp, "\n");
        int i=0;
        for(i=0;i<size;i++)
                fprintf(fp, "%d,",ar[i]);         // write text to file
        // fprintf(fp, "\n");
}

void writeLast(FILE *fp,int *ar,int size){ //to write the last 5 elements in the file 
        fprintf(fp, "\n");
        int i=0;
        for(i=size-5;i<size;i++)
                fprintf(fp, "%d,",ar[i]);         // write text to file
}

int* readInputFile(FILE *fp,int *arr,int c,int size){
        // int bufsize=size*2;
        // int bufsize=174080;
        int bufsize=999999;

        char buffer[bufsize];
        char *token;
        int *values=calloc(size,sizeof(int));
        int i = 0;
        int count=0;

        // printf("%d\n",size);

        fp = fopen("input.txt", "r");   // open file for reading

        while (fgets(buffer, sizeof(buffer), fp)){
                
                if(count==c)
                {
                        int j=0;
                        for(j=0;j<size;j++){
                                fscanf(fp, "%d,",&values[j]);
                        }
                        break;
                }
                count++;
        }
        
        return values;
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  
    // Create temp arrays
    int L[n1], R[n2];
  
    // Copy data to temp arrays 
    // L[] and R[] 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
  
    // Merge the temp arrays back 
    // into arr[l..r]
    // Initial index of first subarray
    i = 0; 
  
    // Initial index of second subarray
    j = 0; 
  
    // Initial index of merged subarray
    k = l; 
    while (i < n1 && j < n2) 
    {
        if (L[i] <= R[j]) 
        {
            arr[k] = L[i];
            i++;
        }
        else 
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
  
    // Copy the remaining elements 
    // of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
  
    // Copy the remaining elements of 
    // R[], if there are any 
    while (j < n2) 
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
  
// l is for left index and r is 
// right index of the sub-array 
// of arr to be sorted 
void mergeSort(int arr[],int l, int r)
{
    if (l < r) 
    {
        // Same as (l+r)/2, but avoids 
        // overflow for large l and h
        int m = l + (r - l) / 2;
  
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
  
        merge(arr, l, m, r);
    }
}

// function to swap elements
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

// function to find the partition position
int partition(int array[], int low, int high) {
  
  // select the rightmost element as pivot
  int pivot = array[high];
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  int j=0;
  for (j = low; j < high; j++) {
    if (array[j] <= pivot) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }

  // swap the pivot element with the greater element at i
  swap(&array[i + 1], &array[high]);
  
  // return the partition point
  return (i + 1);
}

void quickSort(int array[], int low, int high) {
  if (low < high) {
    
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    int pi = partition(array, low, high);
    
    // recursive call on the left of pivot
    quickSort(array, low, pi - 1);
    
    // recursive call on the right of pivot
    quickSort(array, pi + 1, high);
  }
}
  
// UTILITY FUNCTIONS 
// Function to print an array 
void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void writeSortFile(FILE *fp,int *ar,int size){ //to write into the output file
        int i=0;
        for(i=0;i<size;i++)
                fprintf(fp, "%d,",ar[i]);         // write text to file
        fprintf(fp, "\n");
}

int main( int argc, char **argv ) //Main function
{	
    int nproc,rank,i,*recvArray,*irecv;
    MPI_Init( &argc , &argv );
    MPI_Comm_size(MPI_COMM_WORLD,&nproc);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    int arraySize=0;
    double operation_count=0.0;
    struct timeval start, end,start2,end2;
    FILE *fp; //file object being made
	srand(time(0));
    int leafSize=atoi(argv[2]);
    leafSize=pow(2,leafSize+1);
	int ret=atoi(argv[1]); //taking the size as input from terminal to read specific array from file.
    
    int count=0;
        if(ret==11){
        count=0;
        arraySize=(int)pow(2,11);
        }
        else if(ret==13){
        count=1;
        arraySize=(int)pow(2,13);
        }
        else if(ret==15){
        count=2;
        arraySize=(int)pow(2,15);
        }
        else if(ret==17){
        count=3;
        arraySize=(int)pow(2,17);
        }
        else if(ret==5){
        count=4;
        arraySize=(int)pow(2,5);
        }
    
    MPI_Barrier(MPI_COMM_WORLD);
        if(rank==0)
        {
            if(ret ==0) //to store the arrays in the input file
            {
                arr1= calloc(2048, sizeof( int)); //dynamically allocating memory to the array
                populateArray(arr1,2048); //call to the populate function to fill array with random values
                arr2= calloc(8192, sizeof( int)); 
                populateArray(arr2,8192);
                arr3= calloc(32768, sizeof( int)); 
                populateArray(arr3,32768);
                arr4= calloc(131072, sizeof( int)); 
                populateArray(arr4,131072);

                arr5= calloc(32, sizeof( int)); 
                populateArray(arr5,32);

                // arr5= calloc(32, sizeof( int)); //self made array only for testing
                // populateArray(arr5,32);

                fp=fopen("input.txt", "w");   // open file for writing

                writeInputFile(fp,arr1,2048); //call to the write file function that writes array into the file
                writeInputFile(fp,arr2,8192);
                writeInputFile(fp,arr3,32768);
                writeInputFile(fp,arr4,131072);
                writeInputFile(fp,arr5,32);

                // writeInputFile(fp,arr5,32);

                fclose(fp); // close file

                fp=fopen("first.txt", "w");   // open file for writing

                writeLast(fp,arr1,2048); //call to the write file function that writes array into the file
                writeLast(fp,arr2,8192);
                writeLast(fp,arr3,32768);
                writeLast(fp,arr4,131072);
                writeLast(fp,arr5,32);

                // writeLast(fp,arr5,32);

                fclose(fp); // close file
            }
            else//to read size 2 power 11 array from file and perform sort on it
            { 
                    printf("Array to be sorted is of 2 power %d\n",ret);
                

                //     irecv=calloc(arraySize, sizeof( int)); //initilize new array
                    arr=calloc(arraySize, sizeof( int)); //initilize new array 
                    fp = fopen("input.txt", "r");   // open file for reading
                    
                    // arr=readInputFile(fp,arr,count,arraySize);
                    arr=readInputFile(fp,arr,count,arraySize);

                    fclose(fp);                     // close file

                    printf("The returned first 5 elements are: \n");
                    int i=0;
                    for(i=0;i<5;i++){
                            printf("%d ",arr[i]);
                    }
                    printf("\n");

                    printf("The returned array last 5 elements are: \n");
                    for(i=arraySize-5;i<arraySize;i++){
                            printf("%d ",arr[i]);
                    }
                    printf("\n");
            }
            }
        MPI_Barrier(MPI_COMM_WORLD);
        // arraySize=(int)pow(2,ret);clear
        irecv= calloc(leafSize, sizeof( int)); 
        result=calloc(arraySize,sizeof(int)); //for merge sort result
        recvArray=calloc(arraySize,sizeof(int)); //for quick sort result
        int count2=0;
        int j=0;
        int *recvCounts = (int*)malloc(nproc * sizeof(int));
        int *displs= (int*)malloc(nproc * sizeof(int));
        
        for(i=0;i<nproc;i++){
                recvCounts[i]=leafSize;
                displs[i]=leafSize*i;
        }

        struct timeval startQuick, startMerge, endQuick, endMerge;

        gettimeofday( &startMerge, NULL );
        for(i=0;i<arraySize/(leafSize*nproc);i++){
                MPI_Scatter(arr+i*leafSize*nproc,leafSize,MPI_INT,irecv,leafSize,MPI_INT,0,MPI_COMM_WORLD);

                mergeSort(irecv,0,leafSize-1);

                MPI_Gatherv(irecv,leafSize,MPI_INT,result+i*leafSize*nproc,recvCounts,displs,MPI_INT,0,MPI_COMM_WORLD);
        }
        MPI_Barrier(MPI_COMM_WORLD);

        if(rank==0){
                // printf("The merged gathered array is: \n");
                // for(i=0;i<arraySize;i++){
                //         printf("%d ",result[i]);
                // }
                // printf("\n");

                mergeSort(result,0,arraySize-1);
        }
        gettimeofday( &endMerge, NULL );

        if(rank==0){
                if(ret==11){
                fp=fopen("sorted11.txt", "w");   // open file for writing
                writeSortFile(fp,result,arraySize); //call to the write file function that writes array into the file
        }
        else if(ret==13){
                fp=fopen("sorted13.txt", "w");   // open file for writing
                writeSortFile(fp,result,arraySize); //call to the write file function that writes array into the file
        }
        else if(ret==15){
                fp=fopen("sorted15.txt", "w");   // open file for writing
                writeSortFile(fp,result,arraySize); //call to the write file function that writes array into the file
        }
        else if(ret==17){
                fp=fopen("sorted17.txt", "w");   // open file for writing
                writeSortFile(fp,result,arraySize); //call to the write file function that writes array into the file
        }
        operation_count=arraySize*log(arraySize);
        // fp=fopen("sorted11.txt", "w");   // open file for writing
        //         writeSortFile(fp,result,arraySize); //call to the write file function that writes array into the file
                /* convert time to Gflop/s */
                printf("The time taken for sorting using mergeSort is: \n");
                double seconds = (endMerge.tv_sec - startMerge.tv_sec) + 1.0e-6 * (endMerge.tv_usec - startMerge.tv_usec);
                double Gflops = 2e-9*operation_count/seconds;
                printf( " Performance in Gflops %.8f Gflop/s\n\n", Gflops );
        }
        MPI_Barrier(MPI_COMM_WORLD);

        gettimeofday( &startQuick, NULL );
        for(i=0;i<arraySize/(leafSize*nproc);i++){
                MPI_Scatter(arr+i*leafSize*nproc,leafSize,MPI_INT,irecv,leafSize,MPI_INT,0,MPI_COMM_WORLD);

                quickSort(irecv,0,leafSize-1);

                MPI_Gatherv(irecv,leafSize,MPI_INT,result+i*leafSize*nproc,recvCounts,displs,MPI_INT,0,MPI_COMM_WORLD);
        }
        MPI_Barrier(MPI_COMM_WORLD);

        if(rank==0){
                // printf("The merged gathered array is: \n");
                // for(i=0;i<arraySize;i++){
                //         printf("%d ",result[i]);
                // }
                // printf("\n");

                mergeSort(result,0,arraySize-1);
        }
        gettimeofday( &endQuick, NULL );

        if(rank==0){
                if(ret==11){
                fp=fopen("sorted11.txt", "w");   // open file for writing
                writeSortFile(fp,result,arraySize); //call to the write file function that writes array into the file
        }
        else if(ret==13){
                fp=fopen("sorted13.txt", "w");   // open file for writing
                writeSortFile(fp,result,arraySize); //call to the write file function that writes array into the file
        }
        else if(ret==15){
                fp=fopen("sorted15.txt", "w");   // open file for writing
                writeSortFile(fp,result,arraySize); //call to the write file function that writes array into the file
        }
        else if(ret==17){
                fp=fopen("sorted17.txt", "w");   // open file for writing
                writeSortFile(fp,result,arraySize); //call to the write file function that writes array into the file
        }
        // operation_count=arraySize*log(arraySize);
        // fp=fopen("sorted11.txt", "w");   // open file for writing
        //         writeSortFile(fp,result,arraySize); //call to the write file function that writes array into the file
                /* convert time to Gflop/s */
                printf("The time taken for sorting using QuickSort is: \n");
                double seconds = (endQuick.tv_sec - startQuick.tv_sec) + 1.0e-6 * (endQuick.tv_usec - startQuick.tv_usec);
                double Gflops = 2e-9*operation_count/seconds;
                printf( " Performance in Gflops %.8f Gflop/s\n\n", Gflops );
        fclose(fp);
        }

        
        
        MPI_Barrier(MPI_COMM_WORLD);





        MPI_Finalize();
        
	
	return 0;
}


