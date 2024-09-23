//
// Created by Adrian Hwang on 2024-09-13.
//

#ifndef INVERSENUMBER_H
#define INVERSENUMBER_H
int merge_sort_count(int[],int,int);
int merge(int[],int,int,int);
int count_inversion(int arr[],int size){
    //sizeof(arr) is the size of the pointer, not the size of the array, if arr is an argument of a function
    return merge_sort_count(arr,0,size-1);
}

int merge_sort_count(int arr[], int start, int end){
    //termination condition
    if(start>=end)
        return 0;
    int mid=start+(end-start)/2;
    //recursion
    int left_count=merge_sort_count(arr,start,mid); //left region's inversion count
    int right_count=merge_sort_count(arr,mid+1,end); //right region's inversion count
    //merge
    int cross_count=merge(arr,start,mid,end); //cross region's inversion count
    return left_count+right_count+cross_count;
}

int merge(int arr[], int start, int mid, int end) {
    int tmp[end - start + 1]; // temporary array to hold merged results
    int i = start, j = mid + 1, k = 0, count = 0;

    // Merge the two halves
    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
            tmp[k++] = arr[i++];
        } else {
            tmp[k++] = arr[j++];
            count += (mid - i + 1); // Count inversions
        }
    }

    // Copy remaining elements from left half
    while (i <= mid) {
        tmp[k++] = arr[i++];
    }

    // Copy remaining elements from right half
    while (j <= end) {
        tmp[k++] = arr[j++];
    }

    // Copy sorted elements back into original array
    for (i = start, k = 0; i <= end; i++, k++) {
        arr[i] = tmp[k];
    }

    return count;
}

// int merge(int arr[],int start,int mid,int end){
//     int tmp[end-start+1];
//     int count=0;
//     for(int i=start,j=mid+1,k=0;k<end-start+1;k++){
//         if(i>mid || (arr[i]>arr[j]  && i<=mid))
//         {
//             tmp[k]=arr[j++];
//             //left and right neither running out
//             if(i<=mid)
//             {
//                 count+=mid-i+1;
//             }
//         }else
//         {
//             tmp[k]=arr[i++];
//         }
//     }
//     for (int i = 0; i < end-start+1; i++) {
//         arr[start+i]=tmp[i];
//     }
//     return count;
// }
#endif //INVERSENUMBER_H
