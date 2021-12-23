#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

//function to create array
int gen_array(int size, int arr[]);
//check if array is already sorted
int is_sorted(int length, int arr[]);
//return merge/quick sort array
void merge_sort(int start, int end, int arr[]);
//merge arrays in merge_sort
void merge(int start, int mid, int end, int arr[]);
//find sum
int get_sum(int size, int arr[]);

int main(void) {
  //prompt for # of books, fewer than 100,001
  int num_books;
  if(scanf("%d", &num_books)>MAX){
    //printf("Error.");
    //Kattis just wanted me to have some sort of statement checking the input val
  }
  int* arr;
  arr = (int*)malloc(num_books*sizeof(int));
  //prompt for prices for every book, less than $100,001
  if(gen_array(num_books, arr)==0){
    //printf("Error.");
    //Kattis just wanted me to have some sort of statement checking the input val
  }
  //check if already sorted
  if(!is_sorted(num_books, arr)){
  //merge/quick sort (pick one) the list
  merge_sort(0, num_books-1, arr);
  }
  //get the sum of the prices that aren't eliminated by the deal
  int sum = get_sum(num_books, arr);
  //print sum
  printf("%d", sum);
  //free memory
  free(arr);
  return 0;
}

//function to generate array
int gen_array(int size, int arr[]){
  //for the number of inputs, fill them into the array
  for(int i = 0; i < size; i++){
    int a;
    //if the value is too big, return a value that indicates as such
    if(scanf("%d", &a)>MAX){
      return 0;
    }
    //fill the array index with the user input
    arr[i] = a;
  }
  //return success
  return 1;
}

//function to check if an array is already sorted so we don't unnecessarily sort
int is_sorted(int length, int arr[]){
    //return false if any adjacent pair is out of order.
    for (int i=0; i<length-1; i++){
        if (arr[i] > arr[i+1]){
            return 0;
        }
    }
    return 1;
}

//merge sort function
void merge_sort(int start, int end, int arr[]){
  //int to hold middle
  int mid;
  //only if the start is still less than end (values arent same)
  if(start < end){
    //mid is middle index
    mid = (start+end)/2;
    //merge sort first half
    merge_sort(start, mid, arr);
    //merge sort second half
    merge_sort(mid+1, end, arr);
    //merge arrays together
    merge(start, mid+1, end, arr);
  }
}

//function to merge arrays
void merge(int start, int mid, int end, int arr[]){
  //ints for aux array, length, placeholders, and index
  int *temp, length, count1, count2, mc;
  //length
  length = end - start + 1;
  //declare memory for temp
  temp = (int*)malloc(length*sizeof(int));
  //declare placeholders and index
  count1 = start;
  count2 = mid;
  mc = 0;
  //while start placeholder less than mid OR end placeholder less/equal end
  while((count1 < mid) || (count2 <= end)){
    //if end placeholder now greater than end OR (start placeholder less than mid AND
    //arr[start placeholder] less than arr[end placeholder])
    if(count2 > end || (count1 < mid && arr[count1] < arr[count2])){
      //temp at index filled with arr at start placehold.
      temp[mc] = arr[count1];
      //start plchld. ++
      count1++;
      //temp index ++
      mc++;
    }
    //otherwise, fill temp at mc with arr[end placeholder], increase holder and index
    else{
      temp[mc] = arr[count2];
      count2++;
      mc++;
    }
  }
  //refill arr with temp's data
  for(int i = start; i <= end; i++){
    arr[i] = temp[i - start];
  }
  //we no longer need temp; free it
  free(temp);
}

//get the sum given the counting pattern
int get_sum(int size, int arr[]){
  //ints for sum, counter
  int sum = 0, p = 1;
  //starting at greatest values at end of array, going through array
  for(int i = size-1; i >= 0; i--){
    //if p is a multiple of 3
    if(p%3==0){
      //increase p but do nothing else; continue on
      p++;
      continue;
    }
    //add arr at i to sum, increase p
    sum += arr[i];
    p++;
  }
  //return p
  return sum;
}