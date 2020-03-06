#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"

#define BILLION 1000000000.0  // For time function

void mergesort(int a[],int i,int j);
void merge(int a[],int i1,int j1,int i2,int j2);



int listSortedOrNot(int arr[], int arrSize){ 
   /* 
     This function used to check if we sorted our list successfuly or not:  
      -The basic idea for this function (recursive approach):
        * If size of array is zero or one, return true. 
        * Check last two elements of array, if they are sorted,
          perform a recursive call with arrSize -1,
          else, return false.
        * If all the elements will be found sorted, arrSize will finally be one, 
          so, satisfying the first note.  
   */
    if (arrSize == 1 || arrSize ==0)
         return 1; 
    if (arr[arrSize-1] < arr[arrSize-2])
         return 0;
   return listSortedOrNot(arr, arrSize -1);
}

int main(int argc,char* argv[])
{
   if(argc <1)
  {
   printf("The prog need at least 1 args\n");
   exit(0);
 }
    int *a,num, i;
    printf("\n Please enter array size _please make array size fit your memory size_ thnx:-      ");
    scanf("%d",&num);

int n =atoi(argv[1]);

   a = (int *)malloc(sizeof(int) * num);
    for(i=0;i<num;i++)
        a[i]=rand()%100;
       //scanf("%d",&a[i]);
        

// Time measuring
 struct timespec startTimeSeq, finishTimeSeq;//variables for compute the execution time.
     double totalTimeSeq; // total execution time. 
     clock_gettime(CLOCK_REALTIME,&startTimeSeq); // start compute real time. 
    #pragma omp parallel num_threads(n)
    mergesort(a, 0, num-1);

 
//time finish
 clock_gettime(CLOCK_REALTIME,&finishTimeSeq); //Finish compute real time.
     // total = finish - start  
     totalTimeSeq = ((finishTimeSeq.tv_sec - startTimeSeq.tv_sec) + ((finishTimeSeq.tv_nsec - startTimeSeq.tv_nsec) / BILLION));
     

 
    if (listSortedOrNot(a,num))
         printf("\n  *Successfully sorted ^_^\n");
      else 
         printf("Not sorted :(\n");
   

printf("\n_Execution time for omp parallel code = %f seconds\n", totalTimeSeq);
   
    double speedup;
     speedup = 1/(1-totalTimeSeq) ;
printf("\n _____Speedup = %f  \n",speedup);

//    printf("\nSorted array :\n");
//    for(i=0;i<num;i++)

        
    return 0;
}
 
void mergesort(int a[],int i,int j)
{
    int mid;
        
    if(i<j)
    {
        mid=(i+j)/2;
        
        #pragma omp parallel sections 
        {

            #pragma omp section
            {
                mergesort(a,i,mid);        //left recursion
            }

            #pragma omp section
            {
                mergesort(a,mid+1,j);    //right recursion
            }
        }

        merge(a,i,mid,mid+1,j);    //merging of two sorted sub-arrays
    }
}
 
void merge(int a[],int i1,int j1,int i2,int j2)
{
    int temp[1000];    //array used for merging
    int i,j,k;
    i=i1;    //beginning of the first list
    j=i2;    //beginning of the second list
    k=0;
    
    while(i<=j1 && j<=j2)    //while elements in both lists
    {
        if(a[i]<a[j])
            temp[k++]=a[i++];
        else
            temp[k++]=a[j++];
    }
    
    while(i<=j1)    //copy remaining elements of the first list
        temp[k++]=a[i++];
        
    while(j<=j2)    //copy remaining elements of the second list
        temp[k++]=a[j++];
        
    //Transfer elements from temp[] back to a[]
    for(i=i1,j=0;i<=j2;i++,j++)
        a[i]=temp[j];
}
