/*******************************************************************************************
* This is my attempt at implementing std::sort for cpp standard lib in c for a class report*
********************************************************************************************/
#include <math.h>

static inline void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//use the median value of first middle and last element as pivot
static inline void medianOfThree(int* s, int n) {
    int lo = 0;
    int mid = n/2;
    int hi = n-1;
    if(s[lo] > s[mid]) {swap(&s[lo], &s[mid]);}
    if(s[mid] > s[hi]){swap(&s[mid], &s[hi]);}
    if(s[lo] > s[mid]){swap(&s[lo], &s[mid]);}
}

static inline int* slice(int* s, int start, int stop) {
    return (s + start);
}

void insertionSort(int* s, int n) {
    //j keeps track of the current item we are comparing to
    //we keep track of the key so we can just override the memory
    //of the right element making it seems like we swap it in memory
    for(int i=1; i < n; i++) {
        int key = s[i];
        int j = i - 1;
        while(j>=0 && s[j] > key) {
            s[j+1] = s[j];
            --j;
        }
        s[j+1] = key;
    }
}

//make a sub tree max heap
void heapify(int* s, int n, int i) {
    int parent = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if(leftChild < n && s[leftChild] > s[parent]) {
        parent = leftChild;
    }

    if(rightChild < n && s[rightChild] > s[parent]) {
        parent = rightChild;
    }

    if(parent != i) {
        swap(&s[i], &s[parent]); 
        heapify(s, n, parent);
    }
}

void heapSort(int* s, int n) {
    //start from last parent and work up to create max heap
    for(int i = (n / 2) - 1; i >= 0; i--) {
        heapify(s, n, i); 
    }

    for(int i = n - 1; i > 0; i--) {
        swap(&s[0], &s[i]); //swap largest value(root) with smallest value
        heapify(s, i, 0); //fix max heap
    }
}

//quick sort logic
int partition(int* s, int n) {
    medianOfThree(s, n); //select pivot with median of three
    
    int pivot = s[n/2];
    int i = -1;
    int j = n;
    while(1) {
        do{i++;}while(s[i] < pivot);
        do{j--;}while(s[j] > pivot);
        if(i >= j) {
            return j;
        }
        swap(&s[i], &s[j]);
    }
}

//introsort
void introSort(int* s, int n, int maxDepth) {
    int p;

    if(n < 16) {
        insertionSort(s, n);
        return;
    }
    else if(maxDepth == 0) {
        heapSort(s, n);
        return;
    }
    else {
        p = partition(s, n);
        introSort(slice(s, 0, p), p + 1, maxDepth - 1);
        introSort(slice(s, p + 1, n), n - (p + 1) , maxDepth - 1);
    }

    
}

void mysort(int* s, int n) {
    int maxDepth = 2 * log2(n);
    introSort(s, n, maxDepth);
}


