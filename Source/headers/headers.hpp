#pragma once
#include <filesystem>
#include <string>
#include <vector>
void bubble_sort(int arr[], size_t n);
void selection_sort(int arr[], size_t n);
void insertion_sort(int arr[], size_t n);
void LomutoQuickSort(int A[], long low, long high, bool mof);
void LomutoQuickSort_rep(int A[], long low, long high);
void HoareQuickSort(int A[], long low, long high);
void BottomUpMergeSort(int A[], size_t n);
void TopDownMergeSort(int A[], size_t n);
void heapsort(int arr[], size_t n, bool siftup);
void BottomUpHeapSort(int arr[], size_t n);

void radix_sort(int arr[], size_t n);
void BucketSortMixed(int arr[], size_t n, bool option = false);
void counting_sort(int arr[], size_t n);

void bubble_sort(long arr[], size_t n);
void selection_sort(long arr[], size_t n);
void insertion_sort(long arr[], size_t n);
void LomutoQuickSort(long A[], long low, long high, bool mof);
void LomutoQuickSort_rep(long A[], long low, long high);
void HoareQuickSort(long A[], long low, long high);
void BottomUpMergeSort(long A[], size_t n);
void TopDownMergeSort(long A[], size_t n);
void heapsort(long arr[], size_t n, bool siftup);
void BottomUpHeapSort(long arr[], size_t n);

void radix_sort(long arr[], size_t n);
void BucketSortMixed(long arr[], size_t n, bool option = false);   // option for sqrt(n)
void counting_sort(long arr[], size_t n);

// generator.cpp
void generate(long amount, char* filename);
void generate(long amount, std::string filename);
void generate_int(long amount, std::string filename);
void sort_arrays_from_files(char* path_s, char* path_d);
void sort_arrays_from_files(std::string path_s, std::string path_d);
void read_array_from_file(std::vector<long>& array, char* filename);
void read_array_from_file(std::vector<long>& array, std::string filename);
void read_array_from_file(std::vector<int>& array, std::string filename);
void write_array_to_file(std::vector<long>& array, char* filename);
void write_array_to_file(std::vector<long>& array, std::string filename);

std::string get_stem(const std::filesystem::path& p);

// tests.cpp
void test(std::string path_unsorted, std::vector<std::vector<double>>& time_matrix, std::vector<std::string>& row_names, void sort_function(long*, size_t), bool verify = true, int limit = 8);
void test(std::string path_unsorted, std::vector<std::vector<double>>& time_matrix, std::vector<std::string>& row_names, void sort_function(long*, long, long), bool verify = true, int limit = 8);
void test(std::string path_unsorted, std::vector<std::vector<double>>& time_matrix, std::vector<std::string>& row_names, void sort_function(long*, long, long, bool), bool mof = false, bool verify = true, int limit = 8);
void test(std::string path_unsorted, std::vector<std::vector<double>>& time_matrix, std::vector<std::string>& row_names, void sort_function(long*, size_t, bool), bool option = false, bool verify = true, int limit = 8);
void test_2(std::string path_unsorted, std::vector<std::vector<double>>& time_array2D, std::vector<std::string>& row_names, void sort_function(int*, size_t), bool verify = true, int limit = 8);
void test_2(std::string path_unsorted, std::vector<std::vector<double>>& time_array2D, std::vector<std::string>& row_names, void sort_function(int*, long, long), bool verify = true, int limit = 8);
void test_2(std::string path_unsorted, std::vector<std::vector<double>>& time_array2D, std::vector<std::string>& row_names, void sort_function(int*, long, long, bool), bool mof = false, bool verify = true, int limit = 8);
void test_2(std::string path_unsorted, std::vector<std::vector<double>>& time_array2D, std::vector<std::string>& row_names, void sort_function(int*, size_t, bool), bool option = false, bool verify = true, int limit = 8);

void write_to_csv(std::string filename, std::vector<std::vector<double>>& matrix, std::vector<std::string>& row_names);

void test1(int mode, std::string path_s, std::string path_d, bool verify = true, int limit = 8);
void test2(int mode, std::string path_s, std::string path_d, bool verify = true, int limit = 5);
void test3(int mode, std::string path_s, std::string path_d, bool verify = true, int limit = 5);
void test4(int mode, std::string path_s, std::string path_d, bool verify = true, int limit = 5);
void test5(int mode, std::string path_s, std::string path_d, bool verify = true, int limit = 8);
void test6(int mode, std::string path_s, std::string path_d, bool verify = true, int limit = 8);
void test7(int mode, std::string path_s, std::string path_d, bool verify = true, int limit = 8);
void test8(int mode, std::string path_s, std::string path_d, bool verify = true, int limit = 5);
void test9(int mode, std::string path_s, std::string path_d, bool verify = true, int limit = 8);
void test10(int mode, std::string path_s, std::string path_d, bool verify = true, int limit = 5);
void test11(int mode, std::string path_s, std::string path_d, bool verify = true, int limit = 5);
void test12(int mode, std::string path_s, std::string path_d, bool verify = true, int limit = 5);
void test13(int mode, std::string path_s, std::string path_d, bool verify = true, int limit = 5);
void test14(int mode, std::string path_s, std::string path_d, bool verify = true, int limit = 5);
void test15(int mode, std::string path_s, std::string path_d, bool verify = true, int limit = 5);
void test16(int mode, std::string path_s, std::string path_d, bool verify = true, int limit = 5);