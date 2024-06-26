#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sys/resource.h>
#include <vector>
#include <numeric>
#include <chrono>
#include <stack>
#include <cstring>

using namespace std;
using namespace std::chrono;

//-----------------------------TO RESET THE ELEMENTS IN ARRAY-----------------------------
void gennum(long int arr[], long size) {
    for(long int i = 0; i < size; i++) arr[i] = size - i;
}

void printMemoryUsage(const string& prefix) {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    #if defined(__linux__)
    cout << prefix << " Memory usage: " << usage.ru_maxrss << " KB" << endl;
    #else
    cout << prefix << " Memory usage: " << usage.ru_maxrss / 1024 << " KB" << endl; // For non-Linux systems
    #endif
}

//-----------------------------Swap Function-----------------------------
void swap(long *a, long *b) {
    long t = *a;
    *a = *b;
    *b = t;
}

//-----------------------------BUBBLE SORT-----------------------------
void bubble(long arr[], long size) {
    for(long i = 0; i < size; i++) {
        for(long j = 0; j < size - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

//-----------------------------INSERTION SORT-----------------------------
void insertionSort(long arr[], long n) {
    long i, key, j;
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
void selectionSort(long arr[], long n) {
    long i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        if(min_idx != i)
            swap(&arr[min_idx], &arr[i]);
    }
}

//-----------------------------MERGE SORT-----------------------------
void merge(long arr[], long l, long m, long r) {
    long i, j, k;
    long n1 = m - l + 1;
    long n2 = r - m;

    long* L = new long[n1];
    long* R = new long[n2];

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
        } else {
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

    delete[] L;
    delete[] R;
}

void mergeSort(long arr[], long l, long r) {
    if (l < r) {
        long m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Wrapper function for mergeSort
void mergeSortWrapper(long arr[], long n) {
    mergeSort(arr, 0, n - 1);
}

//-----------------------------QUICK SORT-----------------------------
long partition(long arr[], long low, long high) {
    long pivot = arr[high];
    long i = (low - 1);
    for (long j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(long arr[], long low, long high) {
    stack<pair<long, long> > stack;
    stack.push(make_pair(low, high));

    while (!stack.empty()) {
        pair<long, long> p = stack.top();
        stack.pop();
        low = p.first;
        high = p.second;

        if (low < high) {
            long pi = partition(arr, low, high);
            if (pi - 1 > low) {
                stack.push(make_pair(low, pi - 1));
            }
            if (pi + 1 < high) {
                stack.push(make_pair(pi + 1, high));
            }
        }
    }
}

// Wrapper function for quickSort
void quickSortWrapper(long arr[], long n) {
    quickSort(arr, 0, n - 1);
}

//-----------------------------PRINT ARRAY-----------------------------
void printarr(long arr[], long size) {
    for(long i = 0; i < size; i++) printf("%ld ", arr[i]);
    printf("\n");
}

void testSort(void (*sortFunc)(long[], long), long arr[], long size, const string& sortName) {
    const int numTests = 10;
    vector<long> memoryUsages;
    vector<double> durations;

    for (int i = 0; i < numTests; ++i) {
        gennum(arr, size);

        auto start = high_resolution_clock::now();
        sortFunc(arr, size);
        auto end = high_resolution_clock::now();

        double duration = duration_cast<microseconds>(end - start).count() / 1e6;
        durations.push_back(duration);

        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
        memoryUsages.push_back(usage.ru_maxrss);
    }

    double avgDuration = accumulate(durations.begin(), durations.end(), 0.0) / durations.size();
    double avgMemoryUsage = accumulate(memoryUsages.begin(), memoryUsages.end(), 0.0) / memoryUsages.size();
    cout << sortName << " Average Time: " << avgDuration << " seconds" << endl;
    cout << sortName << " Average Memory usage: " << avgMemoryUsage << " KB" << endl;
}

int main() {
    const long size = 200000; // ขนาดของอาร์เรย์ที่ใหญ่ขึ้น
    long* arr = (long*)malloc(size * sizeof(long));

    testSort(bubble, arr, size, "BUBBLE");
    testSort(insertionSort, arr, size, "INSERTION");
    testSort(selectionSort, arr, size, "SELECTION");
    testSort(mergeSortWrapper, arr, size, "MERGE");
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    testSort(quickSortWrapper, arr, size, "QUICK");
    delete[] arr;
    return 0;
}
