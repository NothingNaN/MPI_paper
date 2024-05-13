#include "headers.hpp"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
// unmodified sorting functions

// modified sorting function for analysis

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

int pivot(int arr[], long low, long high)
{
    long mid = (low + high) / 2;
    if (arr[mid] < arr[low])
        {
            swap(arr[low], arr[mid]);
        }
    if (arr[high] < arr[low])
        {
            swap(arr[low], arr[high]);
        }
    if (arr[mid] < arr[high])
        {
            swap(arr[mid], arr[high]);
        }
    return arr[high];
}

int lomuto_partition(int arr[], long low, long high, int pivot)
{
    long i = low;

    for (long j = low; j < high; j++)
        {
            if (arr[j] < pivot)
                {
                    swap(arr[i], arr[j]);
                    i++;
                }
        }
    swap(arr[i], arr[high]);
    return i;
}

pair<long, long> lomuto_part_rep(int arr[], long low, long high)
{
    int  pivot = arr[(low + high) / 2];
    long eq = low;

    while (eq <= high)
        {
            if (arr[eq] < pivot)
                {
                    swap(arr[eq], arr[low]);
                    low += 1;
                    eq += 1;
                }
            else if (arr[eq] > pivot)
                {
                    swap(arr[eq], arr[high]);
                    high -= 1;
                }
            else
                eq += 1;
        }
    return make_pair(low, high);
}

int hoare_partition(int arr[], long low, long high)
{
    int  pivot = arr[(low + high) / 2];
    long i = low - 1;
    long j = high + 1;

    while (true)
        {
            do
                {
                    i += 1;
            } while (arr[i] < pivot);
            do
                {
                    j -= 1;
            } while (arr[j] > pivot);
            if (i >= j)
                {
                    return j;
                }
            swap(arr[i], arr[j]);
        }
}

void HoareQuickSort(int A[], long low, long high)
{
    if (low >= 0 && high >= 0 && low < high)
        {
            int p = hoare_partition(A, low, high);
            HoareQuickSort(A, low, p);
            HoareQuickSort(A, p + 1, high);
        }
}

void LomutoQuickSort(int A[], long low, long high, bool mof = true)
{
    if (low >= 0 && low < high)
        {
            int p = (mof == true) ? pivot(A, low, high) : A[high];
            int part = lomuto_partition(A, low, high, p);
            LomutoQuickSort(A, low, part - 1, mof);
            LomutoQuickSort(A, part + 1, high, mof);
        }
}

void LomutoQuickSort_rep(int A[], long low, long high)
{
    if (low >= 0 && low < high)
        {
            auto [lt, gt] = lomuto_part_rep(A, low, high);
            LomutoQuickSort_rep(A, low, lt - 1);
            LomutoQuickSort_rep(A, gt + 1, high);
        }
}

void TopDownMerge(int A[], size_t iBegin, size_t iMiddle, size_t iEnd, int B[])
{
    size_t i = iBegin, j = iMiddle;

    for (size_t k = iBegin; k < iEnd; k++)
        {
            // If left run head exists and is <= existing right run head.
            if (i < iMiddle && (j >= iEnd || A[i] <= A[j]))
                {
                    B[k] = A[i];
                    i = i + 1;
                }
            else
                {
                    B[k] = A[j];
                    j = j + 1;
                }
        }
}

void TopDownSplitMerge(int B[], size_t iBegin, size_t iEnd, int A[])
{
    if (iEnd - iBegin <= 1)   // if run size == 1
        return;   //   consider it sorted
    size_t iMiddle = (iEnd + iBegin) / 2;
    TopDownSplitMerge(A, iBegin, iMiddle, B);
    TopDownSplitMerge(A, iMiddle, iEnd, B);
    TopDownMerge(B, iBegin, iMiddle, iEnd, A);
}

void TopDownMergeSort(int A[], size_t n)
{
    int* B = new int[n];
    memcpy(B, A, n * sizeof(A[0]));   // one time copy of A[] to B[]
    TopDownSplitMerge(B, 0, n, A);   // sort data from B[] into A[]
    delete[] B;
}

void BottomUpMerge(int A[], size_t iLeft, size_t iRight, size_t iEnd, int B[])
{
    size_t i = iLeft, j = iRight;
    // While there are elements in the left or right runs...
    for (size_t k = iLeft; k < iEnd; k++)
        {
            // If left run head exists and is <= existing right run head.
            if (i < iRight && (j >= iEnd || A[i] <= A[j]))
                {
                    B[k] = A[i];
                    i = i + 1;
                }
            else
                {
                    B[k] = A[j];
                    j = j + 1;
                }
        }
}

void BottomUpMergeSort(int A[], size_t n)
{
    int* B = new int[n];
    for (size_t width = 1; width < n; width = 2 * width)
        {
            for (size_t i = 0; i < n; i = i + 2 * width)
                {
                    BottomUpMerge(A, i, min(i + width, n), min(i + 2 * width, n), B);
                }
            memcpy(A, B, n * sizeof(int));
        }
    delete[] B;
}

void bubble_sort(int arr[], size_t n)
{
    while (true)
        {
            bool swapped = false;
            for (size_t j = 0; j < n - 1; j++)
                {
                    if (arr[j] > arr[j + 1])
                        {
                            swap(arr[j], arr[j + 1]);
                            swapped = true;
                        }
                }
            if (swapped == false)
                break;
        }
}

void selection_sort(int arr[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        {
            size_t min_index = i;
            for (size_t j = i + 1; j < n; j++)
                {
                    if (arr[j] < arr[min_index])
                        min_index = j;
                }
            if (min_index != i)
                swap(arr[i], arr[min_index]);
        }
}

void insertion_sort(int arr[], size_t n)
{
    for (size_t i = 1; i < n; i++)
        {
            int  x = arr[i];
            long j;
            for (j = i - 1; j >= 0 && arr[j] > x; j--)
                {
                    arr[j + 1] = arr[j];
                }
            arr[j + 1] = x;
        }
}

void siftDown(int arr[], size_t start, size_t end)
{
    size_t root = start, left, swp;
    while (2 * root + 1 <= end)
        {
            left = 2 * root + 1;
            swp = root;
            // root = start;
            if (arr[swp] < arr[left])
                {
                    swp = left;
                }
            if (left + 1 <= end && arr[swp] < arr[left + 1])
                {
                    swp = left + 1;
                }
            if (swp == root)
                {
                    return;
                }
            else
                {
                    swap(arr[root], arr[swp]);
                    root = swp;
                }
        }
}

void heapify(int arr[], size_t n)
{
    for (long start = n / 2 - 1; start >= 0; start--)
        siftDown(arr, start, n - 1);
}

void siftUp(int arr[], size_t start, size_t end)
{
    // end becomes the child
    size_t parent;
    while (end > start)
        {
            parent = end != 0 ? (end + 1) / 2 - 1 : 0;
            if (arr[parent] < arr[end])
                {
                    swap(arr[parent], arr[end]);
                    end = parent;
                }
            else
                return;
        }
}

void heapify2(int arr[], size_t n)
{
    for (size_t end = 1; end < n; end++)
        {
            siftUp(arr, 0, end);
        }
}

void heapsort(int arr[], size_t n, bool siftup = false)
{
    if (siftup == false)
        {
            heapify(arr, n);
            size_t end = n - 1;

            while (end > 0)
                {
                    swap(arr[0], arr[end]);
                    end--;
                    siftDown(arr, 0, end);
                }
        }
    else
        {
            heapify2(arr, n);
            for (size_t end = n - 1; end > 0; end--)
                {
                    swap(arr[0], arr[end]);
                    heapify2(arr, end);
                }
        }
}

size_t leafSearch(int arr[], size_t i, size_t end)
{
    size_t j = i;
    size_t left = 2 * j + 1;
    size_t right = left + 1;
    while (right <= end)
        {
            if (arr[right] > arr[left])
                {
                    j = right;
                }
            else
                {
                    j = left;
                }
            left = 2 * j + 1;
            right = left + 1;
        }
    if (left <= end)
        {
            j = left;
        }
    return j;
}

void siftDown2(int arr[], size_t i, size_t end)
{
    size_t j = leafSearch(arr, i, end);
    while (arr[i] > arr[j])
        {
            j = (j + 1) / 2 - 1;
        }
    int x = arr[j];
    arr[j] = arr[i];
    while (j > i)
        {
            swap(x, arr[(j + 1) / 2 - 1]);
            j = (j + 1) / 2 - 1;
        }
}

void BottomUpHeapSort(int arr[], size_t n)
{
    heapify(arr, n);
    size_t end = n - 1;

    while (end > 0)
        {
            swap(arr[0], arr[end]);
            end--;
            siftDown2(arr, 0, end);
        }
}

void STL_insertion_sort(vector<int>& arr)
{
    for (size_t i = 1; i < arr.size(); i++)
        {
            int  x = arr[i];
            long j;
            for (j = i - 1; j >= 0 && arr[j] > x; j--)
                {
                    arr[j + 1] = arr[j];
                }
            arr[j + 1] = x;
        }
}

void bucket_sort(vector<int>& arr, size_t n, bool option)
{
    size_t bn = n;
    if (option)
        {
            bn = (long) sqrt(n);
        }

    // find max element
    int max_e = arr[0];
    for (size_t i = 1; i < n; i++)
        {
            max_e = max(max_e, arr[i]);
        }
    if (max_e < bn)
        {
            bn = max_e;
        }

    vector<vector<int>> b(bn);

    for (size_t i = 0; i < n; i++)
        {
            b[(bn - 1) * arr[i] / max_e].push_back(arr[i]);
        }

    for (size_t i = 0; i < bn; i++)
        STL_insertion_sort(b[i]);

    size_t index = 0;
    for (size_t i = 0; i < bn; i++)
        for (size_t j = 0; j < b[i].size(); j++)
            arr[index++] = b[i][j];
}

void counting_sort(int arr[], size_t n)
{
    unsigned int* output = new unsigned int[n];
    unsigned int* positive_arr = new unsigned int[n];
    unsigned int  max_e = arr[0] + INT32_MAX + 1, min_e = arr[0] + INT32_MAX + 1;

    for (size_t i = 0; i < n; i++)
        {
            positive_arr[i] = (unsigned int) arr[i] + INT32_MAX + 1;
        }

    for (size_t i = 1; i < n; i++)
        {
            max_e = max(max_e, positive_arr[i]);
            min_e = min(min_e, positive_arr[i]);
        }

    unsigned int* count = new unsigned int[max_e - min_e + 1]();

    for (size_t i = 0; i < n; i++)
        {
            count[positive_arr[i] - min_e]++;
        }
    for (size_t i = 1; i <= max_e - min_e; i++)
        {
            count[i] += count[i - 1];
        }
    for (long i = n - 1; i >= 0; i--)
        {
            output[count[positive_arr[i] - min_e] - 1] = positive_arr[i];
            count[positive_arr[i] - min_e]--;
        }
    for (size_t i = 0; i < n; i++)
        {
            arr[i] = (int) output[i] - INT32_MAX - 1;
        }
    delete[] output;
    delete[] count;
    delete[] positive_arr;
}

void radix_counting_sort(int arr[], size_t n, size_t exp)
{
    int* output = new int[n];
    int  max_e = arr[0], min_e = arr[0];

    for (size_t i = 1; i < n; i++)
        {
            max_e = max(max_e, arr[i]);
            min_e = min(min_e, arr[i]);
        }

    int* count = new int[max_e - min_e + 1]();

    for (size_t i = 0; i < n; i++)
        {
            count[((arr[i] - min_e) / exp) % 10]++;
        }
    for (size_t i = 1; i <= max_e - min_e; i++)
        {
            count[i] += count[i - 1];
        }
    for (long i = n - 1; i >= 0; i--)
        {
            output[count[((arr[i] - min_e) / exp) % 10] - 1] = arr[i];
            count[((arr[i] - min_e) / exp) % 10]--;
        }
    for (size_t i = 0; i < n; i++)
        {
            arr[i] = output[i];
        }
    delete[] output;
    delete[] count;
}

void BucketSortMixed(int arr[], size_t n, bool option)
{
    vector<int> Neg;
    vector<int> Pos;

    // traverse array elements
    for (size_t i = 0; i < n; i++)
        {
            if (arr[i] < 0)
                Neg.push_back(-1 * arr[i]);
            else
                Pos.push_back(arr[i]);
        }
    if (Neg.size() > 1)
        bucket_sort(Neg, (size_t) Neg.size(), option);
    if (Pos.size() > 1)
        bucket_sort(Pos, (size_t) Pos.size(), option);

    // First store elements of Neg[] array
    // by converting into -ve
    for (size_t i = 0; i < Neg.size(); i++)
        arr[i] = -1 * Neg[Neg.size() - 1 - i];

    // store +ve element
    for (size_t j = Neg.size(); j < n; j++)
        arr[j] = Pos[j - Neg.size()];
}

void radix_sort(int arr[], size_t n)
{
    vector<int> Neg;
    vector<int> Pos;

    // traverse array elements
    for (size_t i = 0; i < n; i++)
        {
            if (arr[i] < 0)
                Neg.push_back(-1 * arr[i]);
            else
                Pos.push_back(arr[i]);
        }
    if (Neg.size() > 1)
        {
            int max_e = Neg[0];
            for (size_t i = 1; i < Neg.size(); i++)
                {
                    max_e = max(max_e, Neg[i]);
                }
            for (size_t exp = 1; max_e / exp > 0; exp *= 10)
                radix_counting_sort(Neg.data(), Neg.size(), exp);
        }
    if (Pos.size() > 1)
        {
            int max_e2 = Pos[0];
            for (size_t i = 1; i < Pos.size(); i++)
                {
                    max_e2 = max(max_e2, Pos[i]);
                }
            for (size_t exp = 1; max_e2 / exp > 0; exp *= 10)
                radix_counting_sort(Pos.data(), Pos.size(), exp);
        }

    // First store elements of Neg[] array
    // by converting longo -ve
    for (size_t i = 0; i < Neg.size(); i++)
        arr[i] = -1 * Neg[Neg.size() - 1 - i];

    // store +ve element
    for (size_t j = Neg.size(); j < n; j++)
        arr[j] = Pos[j - Neg.size()];
}

// OVERLOADS

void swap(long& a, long& b)
{
    long temp = a;
    a = b;
    b = temp;
}

long pivot(long arr[], long low, long high)
{
    long mid = (low + high) / 2;
    if (arr[mid] < arr[low])
        {
            swap(arr[low], arr[mid]);
        }
    if (arr[high] < arr[low])
        {
            swap(arr[low], arr[high]);
        }
    if (arr[mid] < arr[high])
        {
            swap(arr[mid], arr[high]);
        }
    return arr[high];
}

long lomuto_partition(long arr[], long low, long high, long pivot)
{
    long i = low;

    for (long j = low; j < high; j++)
        {
            if (arr[j] < pivot)
                {
                    swap(arr[i], arr[j]);
                    i++;
                }
        }
    swap(arr[i], arr[high]);
    return i;
}

pair<long, long> lomuto_part_rep(long arr[], long low, long high)
{
    long pivot = arr[(low + high) / 2];
    long eq = low;

    while (eq <= high)
        {
            if (arr[eq] < pivot)
                {
                    swap(arr[eq], arr[low]);
                    low += 1;
                    eq += 1;
                }
            else if (arr[eq] > pivot)
                {
                    swap(arr[eq], arr[high]);
                    high -= 1;
                }
            else
                eq += 1;
        }
    return make_pair(low, high);
}

long hoare_partition(long arr[], long low, long high)
{
    long pivot = arr[(low + high) / 2];
    long i = low - 1;
    long j = high + 1;

    while (true)
        {
            do
                {
                    i += 1;
            } while (arr[i] < pivot);
            do
                {
                    j -= 1;
            } while (arr[j] > pivot);
            if (i >= j)
                {
                    return j;
                }
            swap(arr[i], arr[j]);
        }
}

void HoareQuickSort(long A[], long low, long high)
{
    if (low >= 0 && high >= 0 && low < high)
        {
            long p = hoare_partition(A, low, high);
            HoareQuickSort(A, low, p);
            HoareQuickSort(A, p + 1, high);
        }
}

void LomutoQuickSort(long A[], long low, long high, bool mof = true)
{
    if (low >= 0 && low < high)
        {
            long p = (mof == true) ? pivot(A, low, high) : A[high];
            long part = lomuto_partition(A, low, high, p);
            LomutoQuickSort(A, low, part - 1, mof);
            LomutoQuickSort(A, part + 1, high, mof);
        }
}

void LomutoQuickSort_rep(long A[], long low, long high)
{
    if (low >= 0 && low < high)
        {
            auto [lt, gt] = lomuto_part_rep(A, low, high);
            LomutoQuickSort_rep(A, low, lt - 1);
            LomutoQuickSort_rep(A, gt + 1, high);
        }
}

void TopDownMerge(long A[], size_t iBegin, size_t iMiddle, size_t iEnd, long B[])
{
    size_t i = iBegin, j = iMiddle;

    for (size_t k = iBegin; k < iEnd; k++)
        {
            // If left run head exists and is <= existing right run head.
            if (i < iMiddle && (j >= iEnd || A[i] <= A[j]))
                {
                    B[k] = A[i];
                    i = i + 1;
                }
            else
                {
                    B[k] = A[j];
                    j = j + 1;
                }
        }
}

void TopDownSplitMerge(long B[], size_t iBegin, size_t iEnd, long A[])
{
    if (iEnd - iBegin <= 1)   // if run size == 1
        return;   //   consider it sorted
    size_t iMiddle = (iEnd + iBegin) / 2;
    TopDownSplitMerge(A, iBegin, iMiddle, B);
    TopDownSplitMerge(A, iMiddle, iEnd, B);
    TopDownMerge(B, iBegin, iMiddle, iEnd, A);
}

void TopDownMergeSort(long A[], size_t n)
{
    long* B = new long[n];
    memcpy(B, A, n * sizeof(A[0]));   // one time copy of A[] to B[]
    TopDownSplitMerge(B, 0, n, A);   // sort data from B[] longo A[]
    delete[] B;
}

void BottomUpMerge(long A[], size_t iLeft, size_t iRight, size_t iEnd, long B[])
{
    size_t i = iLeft, j = iRight;
    // While there are elements in the left or right runs...
    for (size_t k = iLeft; k < iEnd; k++)
        {
            // If left run head exists and is <= existing right run head.
            if (i < iRight && (j >= iEnd || A[i] <= A[j]))
                {
                    B[k] = A[i];
                    i = i + 1;
                }
            else
                {
                    B[k] = A[j];
                    j = j + 1;
                }
        }
}

void BottomUpMergeSort(long A[], size_t n)
{
    long* B = new long[n];
    for (size_t width = 1; width < n; width = 2 * width)
        {
            for (size_t i = 0; i < n; i = i + 2 * width)
                {
                    BottomUpMerge(A, i, min(i + width, n), min(i + 2 * width, n), B);
                }
            memcpy(A, B, n * sizeof(long));
        }
    delete[] B;
}

void bubble_sort(long arr[], size_t n)
{
    while (true)
        {
            bool swapped = false;
            for (size_t j = 0; j < n - 1; j++)
                {
                    if (arr[j] > arr[j + 1])
                        {
                            swap(arr[j], arr[j + 1]);
                            swapped = true;
                        }
                }
            if (swapped == false)
                break;
        }
}

void selection_sort(long arr[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        {
            size_t min_index = i;
            for (size_t j = i + 1; j < n; j++)
                {
                    if (arr[j] < arr[min_index])
                        min_index = j;
                }
            if (min_index != i)
                swap(arr[i], arr[min_index]);
        }
}

void insertion_sort(long arr[], size_t n)
{
    for (size_t i = 1; i < n; i++)
        {
            long x = arr[i], j;
            for (j = i - 1; j >= 0 && arr[j] > x; j--)
                {
                    arr[j + 1] = arr[j];
                }
            arr[j + 1] = x;
        }
}

void siftDown(long arr[], size_t start, size_t end)
{
    size_t root = start, left, swp;
    while (2 * root + 1 <= end)
        {
            left = 2 * root + 1;
            swp = root;
            // root = start;
            if (arr[swp] < arr[left])
                {
                    swp = left;
                }
            if (left + 1 <= end && arr[swp] < arr[left + 1])
                {
                    swp = left + 1;
                }
            if (swp == root)
                {
                    return;
                }
            else
                {
                    swap(arr[root], arr[swp]);
                    root = swp;
                }
        }
}

void heapify(long arr[], size_t n)
{
    for (long start = n / 2 - 1; start >= 0; start--)
        siftDown(arr, start, n - 1);
}

void siftUp(long arr[], size_t start, size_t end)
{
    // end becomes the child
    size_t parent;
    while (end > start)
        {
            parent = end != 0 ? (end + 1) / 2 - 1 : 0;
            if (arr[parent] < arr[end])
                {
                    swap(arr[parent], arr[end]);
                    end = parent;
                }
            else
                return;
        }
}

void heapify2(long arr[], size_t n)
{
    for (size_t end = 1; end < n; end++)
        {
            siftUp(arr, 0, end);
        }
}

void heapsort(long arr[], size_t n, bool siftup = false)
{
    if (siftup == false)
        {
            heapify(arr, n);
            size_t end = n - 1;

            while (end > 0)
                {
                    swap(arr[0], arr[end]);
                    end--;
                    siftDown(arr, 0, end);
                }
        }
    else
        {
            heapify2(arr, n);
            for (size_t end = n - 1; end > 0; end--)
                {
                    swap(arr[0], arr[end]);
                    heapify2(arr, end);
                }
        }
}

size_t leafSearch(long arr[], size_t i, size_t end)
{
    size_t j = i;
    size_t left = 2 * j + 1;
    size_t right = left + 1;
    while (right <= end)
        {
            if (arr[right] > arr[left])
                {
                    j = right;
                }
            else
                {
                    j = left;
                }
            left = 2 * j + 1;
            right = left + 1;
        }
    if (left <= end)
        {
            j = left;
        }
    return j;
}

void siftDown2(long arr[], size_t i, size_t end)
{
    size_t j = leafSearch(arr, i, end);
    while (arr[i] > arr[j])
        {
            j = (j + 1) / 2 - 1;
        }
    long x = arr[j];
    arr[j] = arr[i];
    while (j > i)
        {
            swap(x, arr[(j + 1) / 2 - 1]);
            j = (j + 1) / 2 - 1;
        }
}

void BottomUpHeapSort(long arr[], size_t n)
{
    heapify(arr, n);
    size_t end = n - 1;

    while (end > 0)
        {
            swap(arr[0], arr[end]);
            end--;
            siftDown2(arr, 0, end);
        }
}

void STL_insertion_sort(vector<long>& arr)
{
    for (size_t i = 1; i < arr.size(); i++)
        {
            long x = arr[i], j;
            for (j = i - 1; j >= 0 && arr[j] > x; j--)
                {
                    arr[j + 1] = arr[j];
                }
            arr[j + 1] = x;
        }
}

void bucket_sort(vector<long>& arr, size_t n, bool option)
{
    size_t bn = n;
    if (option)
        {
            bn = (long) sqrt(n);
        }

    // find max element
    long max_e = arr[0];
    for (size_t i = 1; i < n; i++)
        {
            max_e = max(max_e, arr[i]);
        }
    if (max_e < bn)
        {
            bn = max_e;
        }

    vector<vector<long>> b(bn);

    for (size_t i = 0; i < n; i++)
        {
            b[(bn - 1) * arr[i] / max_e].push_back(arr[i]);
        }

    for (size_t i = 0; i < bn; i++)
        STL_insertion_sort(b[i]);

    size_t index = 0;
    for (size_t i = 0; i < bn; i++)
        for (size_t j = 0; j < b[i].size(); j++)
            arr[index++] = b[i][j];
}

void counting_sort(long arr[], size_t n)
{
    unsigned long* output = new unsigned long[n];
    unsigned long* positive_arr = new unsigned long[n];
    unsigned long  max_e = arr[0] + INT64_MAX + 1, min_e = arr[0] + INT64_MAX + 1;

    for (size_t i = 0; i < n; i++)
        {
            positive_arr[i] = (unsigned long) arr[i] + INT64_MAX + 1;
        }

    for (size_t i = 1; i < n; i++)
        {
            max_e = max(max_e, positive_arr[i]);
            min_e = min(min_e, positive_arr[i]);
        }

    long* count = new long[max_e - min_e + 1]();

    for (size_t i = 0; i < n; i++)
        {
            count[positive_arr[i] - min_e]++;
        }
    for (size_t i = 1; i <= max_e - min_e; i++)
        {
            count[i] += count[i - 1];
        }
    for (long i = n - 1; i >= 0; i--)
        {
            output[count[positive_arr[i] - min_e] - 1] = positive_arr[i];
            count[positive_arr[i] - min_e]--;
        }
    for (size_t i = 0; i < n; i++)
        {
            arr[i] = (long) output[i] - INT64_MAX - 1;
        }
    delete[] output;
    delete[] count;
    delete[] positive_arr;
}

void radix_counting_sort(long arr[], size_t n, size_t exp)
{
    long* output = new long[n];
    long  max_e = arr[0], min_e = arr[0];

    for (size_t i = 1; i < n; i++)
        {
            max_e = max(max_e, arr[i]);
            min_e = min(min_e, arr[i]);
        }

    long* count = new long[max_e - min_e + 1]();

    for (size_t i = 0; i < n; i++)
        {
            count[((arr[i] - min_e) / exp) % 10]++;
        }
    for (size_t i = 1; i <= max_e - min_e; i++)
        {
            count[i] += count[i - 1];
        }
    for (long i = n - 1; i >= 0; i--)
        {
            output[count[((arr[i] - min_e) / exp) % 10] - 1] = arr[i];
            count[((arr[i] - min_e) / exp) % 10]--;
        }
    for (size_t i = 0; i < n; i++)
        {
            arr[i] = output[i];
        }
    delete[] output;
    delete[] count;
}

void BucketSortMixed(long arr[], size_t n, bool option)
{
    vector<long> Neg;
    vector<long> Pos;

    // traverse array elements
    for (size_t i = 0; i < n; i++)
        {
            if (arr[i] < 0)
                Neg.push_back(-1 * arr[i]);
            else
                Pos.push_back(arr[i]);
        }
    if (Neg.size() > 1)
        bucket_sort(Neg, (size_t) Neg.size(), option);
    if (Pos.size() > 1)
        bucket_sort(Pos, (size_t) Pos.size(), option);

    // First store elements of Neg[] array
    // by converting longo -ve
    for (size_t i = 0; i < Neg.size(); i++)
        arr[i] = -1 * Neg[Neg.size() - 1 - i];

    // store +ve element
    for (size_t j = Neg.size(); j < n; j++)
        arr[j] = Pos[j - Neg.size()];
}

void radix_sort(long arr[], size_t n)
{
    vector<long> Neg;
    vector<long> Pos;

    // traverse array elements
    for (size_t i = 0; i < n; i++)
        {
            if (arr[i] < 0)
                Neg.push_back(-1 * arr[i]);
            else
                Pos.push_back(arr[i]);
        }
    if (Neg.size() > 1)
        {
            long max_e = Neg[0];
            for (size_t i = 1; i < Neg.size(); i++)
                {
                    max_e = max(max_e, Neg[i]);
                }
            for (size_t exp = 1; max_e / exp > 0; exp *= 10)
                radix_counting_sort(Neg.data(), Neg.size(), exp);
        }
    if (Pos.size() > 1)
        {
            long max_e2 = Pos[0];
            for (size_t i = 1; i < Pos.size(); i++)
                {
                    max_e2 = max(max_e2, Pos[i]);
                }
            for (size_t exp = 1; max_e2 / exp > 0; exp *= 10)
                radix_counting_sort(Pos.data(), Pos.size(), exp);
        }

    // First store elements of Neg[] array
    // by converting longo -ve
    for (size_t i = 0; i < Neg.size(); i++)
        arr[i] = -1 * Neg[Neg.size() - 1 - i];

    // store +ve element
    for (size_t j = Neg.size(); j < n; j++)
        arr[j] = Pos[j - Neg.size()];
}