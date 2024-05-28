//-----------------------------INCLUDE LIBRARY-----------------------------
#include<iostream>
#include<cstdlib>
#include<ctime>
#include <sys/resource.h>

using namespace std;
//-----------------------------TO RESET THE ELEMENTS IN ARRAY-----------------------------
void gennum(long int arr[],long size) {
    for(long int i=0;i<size;i++) arr[i] = size-i;
}

void printMemoryUsage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    std::cout << "Memory usage: " << usage.ru_maxrss << " KB" << std::endl;
}

//-----------------------------Swap Function-----------------------------
void swap(long int *a,long int *b) {
    long int t=*a;
    *a = *b;
    *b = t;
}
//-----------------------------BUBBLE SORT-----------------------------
void bubble(long int arr[],long int size) {
    for(long i=0;i<size;i++) {
        for(long j=0;j<size-1;j++) {
            if(arr[j] > arr[j+1]) {
                swap(&arr[j],&arr[j+1]);
            }
        }
    }
}
//-----------------------------INSERTION SORT-----------------------------
void insertionSort(long arr[], long n)
{
    long int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
//-----------------------------SELECTION SORT-----------------------------
void selectionSort(long arr[], long n)
{
    long i, j, min_idx;
    for (i = 0; i < n-1; i++)
    {
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;

           if(min_idx != i)
            swap(&arr[min_idx], &arr[i]);
    }
}
//-----------------------------MERGE SORT-----------------------------
void merge(long arr[], long l, long m, long r)
{
    long i, j, k;
    long n1 = m - l + 1;
    long n2 = r - m;

    long L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(long arr[], long l, long r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}
//-----------------------------QUICK SORT-----------------------------
int partition(long arr[], long low, long high)
{
    long pivot = arr[high];

    long i = (low - 1);

    for (long j = low; j <= high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


void quickSort(long arr[], long low, long high)
{
    if (low < high) {

        long pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
//-----------------------------PRINT ARRAY-----------------------------
void printarr(long arr[],long size ) {
    for(int i=0;i<size;i++) printf("%ld ",arr[i]);
    printf("\n");
}

int main() {
    const long size = 10;
    long arr[size];


    clock_t start,end;
    double duration;

    gennum(arr,size);
    start = clock();
    bubble(arr,size);
    end = clock();
    duration = double(end-start) / CLOCKS_PER_SEC;
    cout << "BUBBLE : " << duration << " seconds" << endl;
    printarr(arr,size);
    printMemoryUsage();

    gennum(arr,size);
    start = clock();
    insertionSort(arr,size);
    end = clock();
    duration = double(end-start) / CLOCKS_PER_SEC;
    cout << "INSERTION : " << duration << " seconds" << endl;
    printarr(arr,size);
    printMemoryUsage();

    gennum(arr,size);
    start = clock();
    selectionSort(arr,size);
    end = clock();
    duration = double(end-start) / CLOCKS_PER_SEC;
    cout << "SELECTION : " << duration << " seconds" << endl;
    printarr(arr,size);
    printMemoryUsage();

    gennum(arr,size);
    start = clock();
    mergeSort(arr, 0, size - 1);
    end = clock();
    duration = double(end-start) / CLOCKS_PER_SEC;
    cout << "MERGE : " << duration << " seconds" << endl;
    printarr(arr,size);
    printMemoryUsage();

    gennum(arr,size);
    start = clock();
    quickSort(arr, 0, size - 1);
    end = clock();
    duration = double(end-start) / CLOCKS_PER_SEC;
    cout << "QUICK : " << duration << " seconds" << endl;
    printarr(arr,size);
    printMemoryUsage();

}