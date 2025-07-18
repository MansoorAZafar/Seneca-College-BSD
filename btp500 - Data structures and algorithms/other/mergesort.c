// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>

void mergesort(int* arr, int n) {
    if(n > 1) {
        const int mid = n / 2;
        const int rmid = n - mid;
        
        int* l = (int*) malloc (sizeof(int) * mid);
        int* r = (int*) malloc (sizeof(int) * rmid);
        
        for(int i = 0; i < mid; ++i) {
            l[i] = arr[i];
        }
        for(int i = mid; i < n; ++i) {
            r[i - mid] = arr[i];
        }
        
        mergesort(l, mid);
        mergesort(r, rmid);
        
        int i = 0, j = 0, k = 0;
        while(i < mid && j < rmid) {
            if(l[i] < r[j]) {
                arr[k] = l[i++];
            } else {
                arr[k] = r[j++];
            }
            ++k;
        }
        
        while(i < mid) {
            arr[k++] = l[i++];
        }
        while(j < rmid) {
            arr[k++] = r[j++];
        }
        
        free(l);
        free(r);
    }
}

void printArr(int* arr, int n) {
    for(int i = 0; i < n; ++i) {
        printf("%d, ", arr[i]);
    }
}

int main() {
    // Write C code here
    // printf("Try programiz.pro");

    int arr[10] = {1,2,3,4,56,7,4,5,6,7};
    printArr(arr, 10);
    
    printf("\n");
    mergesort(arr, 10);

    printArr(arr, 10);
    return 0;
}
