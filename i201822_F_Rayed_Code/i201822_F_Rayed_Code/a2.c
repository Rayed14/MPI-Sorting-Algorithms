//Rayed Muhammad Saeed
//20i-1822
//CS-F
//Task1
//PDC

#define _GNU_SOURCE //Libraries
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
        //fprintf(fp, "\n");
}

void writeLast(FILE *fp,int *ar,int size){ //to write the last 5 elements in the file 
        fprintf(fp, "\n");
        int i=0;
        for(i=size-5;i<size;i++)
                fprintf(fp, "%d,",ar[i]);         // write text to file
}

int* readInputFile(FILE *fp,int *arr,int c,int size){
        // int bufsize=size*2;
        int bufsize=174080;
        // int bufsize=174112;

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

        // while (fgets(buffer, sizeof(buffer), fp)) {
        //         token = strtok(buffer, ",");
        //         if(c==count){
        //                 while (token != NULL && i < size) {
        //                         values[i] = atoi(token);
        //                         token = strtok(NULL, ",");
        //                         i++;
        //                 }
        //         }
        //         count++;
        // }
        
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
        int arraySize=0;
        double operation_count=0.0;
        struct timeval start, end,start2,end2;
        FILE *fp; //file object being made
	srand(time(0));
	int ret=atoi(argv[1]); //taking the size as input from terminal to read specific array from file.
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

                // arr5= calloc(32, sizeof( int)); //self made array only for testing
                // populateArray(arr5,32);

                fp=fopen("input.txt", "w");   // open file for writing

                writeInputFile(fp,arr1,2048); //call to the write file function that writes array into the file
                writeInputFile(fp,arr2,8192);
                writeInputFile(fp,arr3,32768);
                writeInputFile(fp,arr4,131072);

                // writeInputFile(fp,arr5,32);

                fclose(fp); // close file

                fp=fopen("first.txt", "w");   // open file for writing

                writeLast(fp,arr1,2048); //call to the write file function that writes array into the file
                writeLast(fp,arr2,8192);
                writeLast(fp,arr3,32768);
                writeLast(fp,arr4,131072);

                // writeLast(fp,arr5,32);

                fclose(fp); // close file
        }
        else if(ret==11){ //to read size 2 power 11 array from file and perform sort on it
                printf("Array to be sorted is of 2 power %d\n",ret);
                arraySize=(int)pow(2,11);
                // printf("Array size is: %d\n",arraySize);

                //int *arr=calloc(arraySize, sizeof( int)); //initilize new array
                int *arr1=calloc(arraySize, sizeof( int)); //initilize new array 
                fp = fopen("input.txt", "r");   // open file for reading
                int count=0;
                // arr=readInputFile(fp,arr,count,arraySize);
                arr1=readInputFile(fp,arr1,count,arraySize);

                fclose(fp);                     // close file

                printf("The returned first 5 elements are: \n");
                int i=0;
                for(i=0;i<5;i++){
                        printf("%d ",arr1[i]);
                }
                printf("\n");

                printf("The returned array last 5 elements are: \n");
                for(i=arraySize-5;i<arraySize;i++){
                        printf("%d ",arr1[i]);
                }
                printf("\n");

                operation_count=2048*log(2048);//number of op
                //arr1=arr;
                // for(int i=0;i<arraySize;i++){
                //         printf("%d ",arr1[i]);
                // }
                gettimeofday( &start, NULL );

                mergeSort(arr1,0,2048); //calling function that will populate and compute with use of affinity

                gettimeofday( &end, NULL );

                fp=fopen("sorted11.txt", "w");   // open file for writing
                writeSortFile(fp,arr1,2048); //call to the write file function that writes array into the file
                /* convert time to Gflop/s */
                printf("The time taken for sorting using mergeSort is: \n");
                double seconds = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
                double Gflops = 2e-9*operation_count/seconds;
                printf( " Performance in Gflops %.8f Gflop/s\n\n", Gflops );
                // arr1=arr;
                arr1=readInputFile(fp,arr1,count,arraySize);
                gettimeofday( &start2, NULL );

                quickSort(arr1,0,2048); //calling function that will populate and compute with use of affinity

                gettimeofday( &end2, NULL );
                // printArray(arr1,arraySize);
                writeSortFile(fp,arr1,2048); //call to the write file function that writes array into the file
                printf("The time taken for sorting using quickSort is: \n");
                seconds = (end2.tv_sec - start2.tv_sec) + 1.0e-6 * (end2.tv_usec - start2.tv_usec);
                Gflops = 2e-9*operation_count/seconds;
                printf( " Performance in Gflops %.8f Gflop/s\n\n", Gflops );
                
                fclose(fp); // close file                
        }
        else if(ret==13){ //to read size 2 power 13 array from file and perform sort on it
                printf("Array to be sorted is of 2 power %d\n",ret);
                arraySize=(int)pow(2,13);
                int *arr2=calloc(arraySize, sizeof( int)); //initilize new array 
                fp = fopen("input.txt", "r");   // open file for reading
                int count=1;
                arr2=readInputFile(fp,arr2,count,arraySize);

                fclose(fp);                     // close file

                printf("The returned first 5 elements are: \n");
                int i=0;
                for(i=0;i<5;i++){
                        printf("%d ",arr2[i]);
                }
                printf("\n");

                printf("The returned array last 5 elements are: \n");
                for(i=arraySize-5;i<arraySize;i++){
                        printf("%d ",arr2[i]);
                }
                printf("\n");

                operation_count=8192*log(8192);//number of op
                // arr2=arr;
                // for(int i=0;i<arraySize;i++){
                //         printf("%d ",arr1[i]);
                // }
                gettimeofday( &start, NULL );

                mergeSort(arr2,0,8192); //calling function that will populate and compute with use of affinity

                gettimeofday( &end, NULL );

                fp=fopen("sorted13.txt", "w");   // open file for writing
                writeSortFile(fp,arr2,8192); //call to the write file function that writes array into the file
                /* convert time to Gflop/s */
                printf("The time taken for sorting using mergeSort is: \n");
                double seconds = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
                double Gflops = 2e-9*operation_count/seconds;
                printf( " Performance in Gflops %.8f Gflop/s\n\n", Gflops );
                // arr2=arr;
                arr2=readInputFile(fp,arr2,count,arraySize);
                gettimeofday( &start2, NULL );

                quickSort(arr2,0,8192); //calling function that will populate and compute with use of affinity

                gettimeofday( &end2, NULL );
                // printArray(arr1,arraySize);
                writeSortFile(fp,arr2,8192); //call to the write file function that writes array into the file
                printf("The time taken for sorting using quickSort is: \n");
                seconds = (end2.tv_sec - start2.tv_sec) + 1.0e-6 * (end2.tv_usec - start2.tv_usec);
                Gflops = 2e-9*operation_count/seconds;
                printf( " Performance in Gflops %.8f Gflop/s\n\n", Gflops );
                
                fclose(fp); // close file  
        }
        else if(ret==15){ //to read size 2 power 15 array from file and perform sort on it
                printf("Array to be sorted is of 2 power %d\n",ret);
                arraySize=(int)pow(2,15);
                int *arr3=calloc(arraySize, sizeof( int)); //initilize new array 
                fp = fopen("input.txt", "r");   // open file for reading
                int count=2;
                arr3=readInputFile(fp,arr3,count,arraySize);

                fclose(fp);                     // close file

                printf("The returned first 5 elements are: \n");
                int i=0;
                for(i=0;i<5;i++){
                        printf("%d ",arr3[i]);
                }
                printf("\n");

                printf("The returned array last 5 elements are: \n");
                for(i=arraySize-5;i<arraySize;i++){
                        printf("%d ",arr3[i]);
                }
                printf("\n");

                operation_count=32768*log(32768);//number of op
                // arr3=arr;
                // for(int i=0;i<arraySize;i++){
                //         printf("%d ",arr1[i]);
                // }
                gettimeofday( &start, NULL );

                mergeSort(arr3,0,32768); //calling function that will populate and compute with use of affinity

                gettimeofday( &end, NULL );

                fp=fopen("sorted15.txt", "w");   // open file for writing
                writeSortFile(fp,arr3,32768); //call to the write file function that writes array into the file
                /* convert time to Gflop/s */
                printf("The time taken for sorting using mergeSort is: \n");
                double seconds = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
                double Gflops = 2e-9*operation_count/seconds;
                printf( " Performance in Gflops %.8f Gflop/s\n\n", Gflops );
                // arr3=arr;
                arr3=readInputFile(fp,arr2,count,arraySize);
                gettimeofday( &start2, NULL );

                quickSort(arr3,0,32768); //calling function that will populate and compute with use of affinity

                gettimeofday( &end2, NULL );
                // printArray(arr1,arraySize);
                writeSortFile(fp,arr3,32768); //call to the write file function that writes array into the file
                printf("The time taken for sorting using quickSort is: \n");
                seconds = (end2.tv_sec - start2.tv_sec) + 1.0e-6 * (end2.tv_usec - start2.tv_usec);
                Gflops = 2e-9*operation_count/seconds;
                printf( " Performance in Gflops %.8f Gflop/s\n\n", Gflops );
                
                fclose(fp); // close file  
        }
        else if(ret==17){ //to read size 2 power 17 array from file and perform sort on it
                printf("Array to be sorted is of 2 power %d\n",ret);
                arraySize=(int)pow(2,17);
                int *arr4=calloc(arraySize, sizeof( int)); //initilize new array 
                fp = fopen("input.txt", "r");   // open file for reading
                int count=3;
                arr4=readInputFile(fp,arr4,count,arraySize);

                fclose(fp);                     // close file

                printf("The returned first 5 elements are: \n");
                int i=0;
                for(i=0;i<5;i++){
                        printf("%d ",arr4[i]);
                }
                printf("\n");

                printf("The returned array last 5 elements are: \n");
                for(i=arraySize-5;i<arraySize;i++){
                        printf("%d ",arr4[i]);
                }
                printf("\n");

                operation_count=131072*log(131072);//number of op
                // arr4=arr;
                // for(int i=0;i<arraySize;i++){
                //         printf("%d ",arr1[i]);
                // }
                gettimeofday( &start, NULL );

                mergeSort(arr4,0,131072); //calling function that will populate and compute with use of affinity

                gettimeofday( &end, NULL );

                fp=fopen("sorted17.txt", "w");   // open file for writing
                writeSortFile(fp,arr4,131072); //call to the write file function that writes array into the file
                /* convert time to Gflop/s */
                printf("The time taken for sorting using mergeSort is: \n");
                double seconds = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
                double Gflops = 2e-9*operation_count/seconds;
                printf( " Performance in Gflops %.8f Gflop/s\n\n", Gflops );
                // arr4=arr;
                arr4=readInputFile(fp,arr2,count,arraySize);
                gettimeofday( &start2, NULL );

                quickSort(arr4,0,131072); //calling function that will populate and compute with use of affinity

                gettimeofday( &end2, NULL );
                // printArray(arr1,arraySize);
                writeSortFile(fp,arr4,131072); //call to the write file function that writes array into the file
                printf("The time taken for sorting using quickSort is: \n");
                seconds = (end2.tv_sec - start2.tv_sec) + 1.0e-6 * (end2.tv_usec - start2.tv_usec);
                Gflops = 2e-9*operation_count/seconds;
                printf( " Performance in Gflops %.8f Gflop/s\n\n", Gflops );
                
                fclose(fp); // close file  
        }
        // else if(ret==5){ //to read size 2 power 11 array from file and perform sort on it
        //         printf("Array to be sorted is of 2 power %d\n",ret);
        //         arraySize=(int)pow(2,5);
        //         // printf("Array size is: %d\n",arraySize);

        //         //int *arr=calloc(arraySize, sizeof( int)); //initilize new array
        //         int *arr5=calloc(arraySize, sizeof( int)); //initilize new array 
        //         fp = fopen("input.txt", "r");   // open file for reading
        //         int count=4;
        //         // arr=readInputFile(fp,arr,count,arraySize);
        //         arr5=readInputFile(fp,arr5,count,arraySize);

        //         fclose(fp);                     // close file

        //         printf("The returned first 5 elements are: \n");
        //         for(int i=0;i<5;i++){
        //                 printf("%d ",arr5[i]);
        //         }
        //         printf("\n");

        //         printf("The returned array last 5 elements are: \n");
        //         for(int i=arraySize-5;i<arraySize;i++){
        //                 printf("%d ",arr5[i]);
        //         }
        //         printf("\n");

        //         operation_count=32*log(32);//number of op
        //         //arr1=arr;
        //         // for(int i=0;i<arraySize;i++){
        //         //         printf("%d ",arr1[i]);
        //         // }
        //         gettimeofday( &start, NULL );

        //         mergeSort(arr5,0,32); //calling function that will populate and compute with use of affinity

        //         gettimeofday( &end, NULL );

        //         fp=fopen("sorted11.txt", "w");   // open file for writing
        //         writeSortFile(fp,arr5,32); //call to the write file function that writes array into the file
        //         /* convert time to Gflop/s */
        //         printf("The time taken for sorting using mergeSort is: \n");
        //         double seconds = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
        //         double Gflops = 2e-9*operation_count/seconds;
        //         printf( " Performance in Gflops %.8f Gflop/s\n\n", Gflops );
        //         // arr1=arr;
        //         arr5=readInputFile(fp,arr5,count,arraySize);
        //         gettimeofday( &start2, NULL );

        //         quickSort(arr5,0,32); //calling function that will populate and compute with use of affinity

        //         gettimeofday( &end2, NULL );
        //         // printArray(arr1,arraySize);
        //         writeSortFile(fp,arr5,32); //call to the write file function that writes array into the file
        //         printf("The time taken for sorting using quickSort is: \n");
        //         seconds = (end2.tv_sec - start2.tv_sec) + 1.0e-6 * (end2.tv_usec - start2.tv_usec);
        //         Gflops = 2e-9*operation_count/seconds;
        //         printf( " Performance in Gflops %.8f Gflop/s\n\n", Gflops );
                
        //         fclose(fp); // close file                
        // }
	
	return 0;
}


