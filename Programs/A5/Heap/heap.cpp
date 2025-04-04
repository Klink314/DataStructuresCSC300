#include "heap.h"

HEAP::HEAP(int size) {
    capacity = size;
    heapSize = 0;
    array = new int[capacity];
}

HEAP::~HEAP() {
    delete[] array;
}

int HEAP::leftChild(int index) {
    return 2*index + 1;
}
int HEAP::rightChild(int index) {
    return 2*index + 2;
}
int HEAP::parent(int index) {
    return (index - 1) / 2;
}

void HEAP::insertH(int data) {
    if (heapSize == capacity) {
        cout << "Heap overflow - can't insert"<< endl;
        return;
    }

    array[heapSize] = data;
    heapifyUp(heapSize);
    heapSize++;
}

void HEAP::heapifyUp(int index) {
    while(index != 0 && array[parent(index)] < array[index]) {
        swap(array[parent(index)], array[index]);
        index = parent(index);
    }
}

int HEAP::peek() {
    if (heapSize <= 0) {
        cout << "Heap is empty" << endl;
        return -1;
    }

    return array[0];
}

void HEAP::deleteMax() {
    if (heapSize <= 0) {
        cout << "Heap is empty - nothing to delete" << endl;
        return;
    }

    if (heapSize == 1) {
        heapSize--;
        return;
    }

    array[0] = array[heapSize - 1];
    heapSize--;

    heapifyDown(0);
}

void HEAP::deleteH(int data) {
    int index = -1;

    // search for data - linear search :( O(n)
    for (int i = 0; i < heapSize; i++) {
        if (array[i] == data) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Element not found - can't delete"  << endl;
        return;
    }

    array[index] = array[heapSize - 1];
    heapSize--;

    heapifyDown(index);
}

void HEAP::heapifyDown(int index) 
{
    //Klink Task 1 Start
    int largest = index;
    int left = leftChild(index);
    int right = rightChild(index);

    if (left < heapSize && array[left] > array[largest])
        largest = left;

    if (right < heapSize && array[right] > array[largest])
        largest = right;

    if (largest != index) {
        swap(array[index], array[largest]);
        heapifyDown(largest); // Recursively heapify the affected subtree
    }
    //Klink Task 1 End
}

void HEAP::buildH(int arr[], int n)
{
    //Klink Task 2 Start
    heapSize = n;
    for (int i = 0; i < n; i++)
        array[i] = arr[i];

    for (int i = parent(heapSize - 1); i >= 0; i--)
        heapifyDown(i);
    //Klink Task 2 End
}

void HEAP::replace(int oldData, int newData)
{
    //Klink Task 3 Start
    int index = -1;

    // Find the index of the old data
    for (int i = 0; i < heapSize; i++) {
        if (array[i] == oldData) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Element not found - can't replace" << endl;
        return;
    }

    array[index] = newData;
    //Klink Task 3 End
}

void HEAP::heapSort(int arr[], int n)
{
    //Klink Task 4 Start
    bool isMaxHeap = true;

    // Check if the heap is Max-Heap or Min-Heap
    if (heapSize > 1 && array[0] > array[1])
        isMaxHeap = true;
    else if (heapSize > 1 && array[0] < array[1])
        isMaxHeap = false;

    if (isMaxHeap) {
        for (int i = parent(heapSize - 1); i >= 0; i--)
            heapifyDown(i);  // Convert to Max-Heap
    } 
    else {
        for (int i = parent(heapSize - 1); i >= 0; i--)
            heapifyDown(i);  // Convert to Max-Heap
    }
    //Klink Task 4 End
}


void HEAP::printHeap(int index, int depth) {
    if (index >= heapSize)
        return;

    printHeap(rightChild(index), depth + 1);

    for (int i = 0; i < depth; i++) {
        cout << "  "; // indentation based on depth
    }

    cout << array[index] << endl;

    printHeap(leftChild(index), depth + 1);
}


void HEAP::heapifyDownMin(int index)
{
    //Klink Extra-Credit Start Part 1
    int smallest = index;
    int left = leftChild(index);    
    int right = rightChild(index);  

    if (left < heapSize && array[left] < array[smallest])
        smallest = left;

    if (right < heapSize && array[right] < array[smallest])
        smallest = right;

    if (smallest != index) {
        swap(array[index], array[smallest]);
        heapifyDownMin(smallest);  // Recursive call for further adjustments
    }
    //Klink Extra-Credit End Part 1
}


void HEAP::switchMinMax()
{
    //Klink Extra-Credit Start Part 2
    bool isMaxHeap = true;

    // Check if the heap is Max-Heap or Min-Heap
    if (heapSize > 1 && array[0] > array[1])
        isMaxHeap = true;
    else if (heapSize > 1 && array[0] < array[1])
        isMaxHeap = false;

    if (isMaxHeap) {
        for (int i = parent(heapSize - 1); i >= 0; i--)
            heapifyDownMin(i);  // Convert to Min-Heap
        cout << "Heap successfully converted from Max-Heap to Min-Heap." << endl;
    } 
    else {
        for (int i = parent(heapSize - 1); i >= 0; i--)
            heapifyDown(i);  // Convert to Max-Heap
        cout << "Heap successfully converted from Min-Heap to Max-Heap." << endl;
    }
    //Klink Extra-Credit End Part 2
}
