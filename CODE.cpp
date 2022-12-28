#include <iostream>
#include <pthread.h>
#include <time.h>
#define size 20 // Number of elements in array 
#define thread_size 2 // Number of threads according to my pc's core 
using namespace std;


int Array[size];
int temp = 0;

void merge_array(int first, int mid_val, int end) // Merge function for merging two parts
{
   int* start = new int[mid_val - first + 1];
   int* last = new int[end - mid_val];
   
   int temp_1 = mid_val - first + 1;           // Temp 1 has size of left part 
   int temp_2 = end - mid_val;                 // Temp 2 has size of right part 
   int i, j;
   int k = first;
   
   for(i = 0; i < temp_1; i++)                 // Sorting values in left part 
   {
      start[i] = Array[i + first];
   }
   
   for (i = 0; i < temp_2; i++)                // Sorting values in right part 
   {
      last[i] = Array[i + mid_val + 1];
   }
   
   i = j = 0;                                    // Merging left and right part in ascending order 
   while(i < temp_1 && j < temp_2)
   {
      if(start[i] <= last[j])
	  {
         Array[k++] = start[i++];
      }
      else
	  {
         Array[k++] = last[j++];
      }
   }
   while (i < temp_1)                          	// Inserting remaining values from left 	
   {
      Array[k++] = start[i++];
   }
   
   while (j < temp_2)                          	// Inserting remaining values from right
   {
      Array[k++] = last[j++];
   }
}


void Merge_Sort(int first, int end)            // MERGE FUNCTION 
{
   int mid_val = first + (end - first) / 2;    // Calculating middle point of array
   if(first < end)
   {
      Merge_Sort(first, mid_val);              // First Half 
      Merge_Sort(mid_val + 1, end);            // Second Half 
      merge_array(first, mid_val, end);        // Merging Both Halves 
   }
}

void* Merge_Sort(void* arg)                   // THREAD FUNCTION FOR MULTI THREADING 
{
   int set_val = temp++;                      // Calculating first and end 
   int first = set_val * (size / 4);
   int end = (set_val + 1) * (size / 4) - 1;
   int mid_val = first + (end - first) / 2;   // Evalute middle point 
   if (first < end)
   {
      Merge_Sort(first, mid_val);
      Merge_Sort(mid_val + 1, end);
      merge_array(first, mid_val, end);
   }
}

int main()                                   // MAIN FUNCTION 
{
   for(int i = 0; i < size; i++)
   {
      Array[i] = rand() % 100;                // Generating random array values using rand()
   }
   pthread_t P_TH[thread_size];               // Creating threads according to my pc's core 

   for(int i = 0; i < thread_size; i++)
   {
      pthread_create(&P_TH[i], NULL, Merge_Sort, (void*)NULL);
   }
   
  
   for(int i = 0; i < 3 ; i++)                // Joining Threads 
   {
      pthread_join(P_TH[i], NULL);
   }
   merge_array(0, (size / 2 - 1) / 2, size / 2 - 1);
   merge_array(size / 2, size/2 + (size-1-size/2)/2, size - 1);
   merge_array(0, (size - 1)/2, size - 1);
   
   cout<<"200901005 - Mahnoor Sadiq - Multi Threading Using Merge Sort"<<endl;
   cout<<"Sorted Array is : ";
   for (int i = 0; i < size; i++)
   {
      cout << Array[i] << " | ";
   }
   return 0;
}

