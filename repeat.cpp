#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sys/resource.h>
#include <vector>
#include <numeric>
#include <chrono>
#include <cstring>
#include <algorithm>

using namespace std;
using namespace std::chrono;

const int NUM_TESTS = 10; // Number of test iterations
const long SIZE = 10; // Size of the array
const float REPEAT_RATE = 0.25; // Repeat rate for generating numbers

// Function to generate random numbers with a specified repeat rate
void gennum(long dataset[], long size, float repeatRate) {
    long uniqueNumbers[size];
    long numRepeats = static_cast<int>(size * repeatRate);
    long uniqueCount = size - numRepeats;

    // Generate unique random numbers
    for (long i = 0; i < uniqueCount; ++i) {
        long num;
        bool isUnique;
        do {
            isUnique = true;
            num = rand() % 1000;  // Generate random numbers between 0 and 999
            for (long j = 0; j < i; ++j) {
                if (uniqueNumbers[j] == num) {
                    isUnique = false;
                    break;
                }
            }
        } while (!isUnique);
        dataset[i] = num;
        uniqueNumbers[i] = num;
    }

    // Fill the rest of the dataset with repeated numbers
    for (long i = uniqueCount; i < size; ++i) {
        long index = rand() % uniqueCount;
        dataset[i] = uniqueNumbers[index];
    }

    // Shuffle the dataset to randomize the positions of the repeated numbers
    for (long i = size - 1; i > 0; --i) {
        long j = rand() % (i + 1);
        swap(dataset[i], dataset[j]);
    }
}

//-----------------------------Swap Function-----------------------------
void swap(long int *a, long int *b) {
    long int t = *a;
    *a = *b;
    *b = t;
}

//-----------------------------BUBBLE SORT-----------------------------
void bubble(long int arr[], long int size) {
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

    for (long j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(long arr[], long low, long high) {
    if (low < high) {
        long pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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

void testSort(void (*sortFunc)(long[], long), long size, const string& sortName, long datasets[NUM_TESTS][SIZE]) {
    vector<long> memoryUsages;
    vector<double> durations;

    for (int i = 0; i < NUM_TESTS; ++i) {
        long* arr = new long[size];
        memcpy(arr, datasets[i], size * sizeof(long));

        cout << "Dataset before sorting (" << sortName << "): ";
        printarr(arr, size); // Print the first 10 elements of the dataset

        auto start = high_resolution_clock::now();
        sortFunc(arr, size);
        auto end = high_resolution_clock::now();

        double duration = duration_cast<microseconds>(end - start).count() / 1e6;
        durations.push_back(duration);

        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
        memoryUsages.push_back(usage.ru_maxrss);

        delete[] arr;
    }

    double avgDuration = accumulate(durations.begin(), durations.end(), 0.0) / durations.size();
    double avgMemoryUsage = accumulate(memoryUsages.begin(), memoryUsages.end(), 0.0) / memoryUsages.size();
    cout << sortName << " Average Time: " << avgDuration << " seconds" << endl;
    cout << sortName << " Average Memory usage: " << avgMemoryUsage << " KB" << endl;
}

int main() {
    srand(time(0)); // Seed the random number generator

    // Allocate memory for the datasets
    long datasets[NUM_TESTS][SIZE];

    // Generate the datasets
    for (int i = 0; i < NUM_TESTS; ++i) {
        gennum(datasets[i], SIZE, REPEAT_RATE);
    }

    // Run the test for each sorting algorithm
    testSort(bubble, SIZE, "BUBBLE", datasets);
    testSort(insertionSort, SIZE, "INSERTION", datasets);
    testSort(selectionSort, SIZE, "SELECTION", datasets);
    testSort(mergeSortWrapper, SIZE, "MERGE", datasets);
    testSort(quickSortWrapper, SIZE, "QUICK", datasets);

    return 0;
}
