#include "headers.hpp"
#include <algorithm>
#include <chrono>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

std::vector<std::vector<double>> transpose(std::vector<std::vector<double>>& array2d)
{
    std::vector<std::vector<double>> transposed;
    for (size_t i = 0; i < array2d[0].size(); i++)
        {
            transposed.push_back(std::vector<double>());
            for (size_t j = 0; j < array2d.size(); j++)
                {
                    transposed[i].push_back(0.0);
                }
        }
    for (size_t i = 0; i < array2d.size(); i++)
        {
            for (size_t j = 0; j < array2d[0].size(); j++)
                {
                    transposed[j][i] = array2d[i][j];
                }
        }

    return transposed;
}

void write_to_csv(std::string filename, std::vector<std::vector<double>>& array2D, std::vector<std::string>& row_names)
{
    std::ofstream file;
    file.open(filename);
    if (!file)
        std::cout << "File not created!\n";
    file << "lists,10^1,10^2,10^3,10^4,10^5,10^6,10^7,10^8\n";
    std::vector<std::vector<double>> transposed;
    transposed = transpose(array2D);
    for (size_t i = 0; i < transposed.size(); i++)
        {
            file << row_names[i] << ",";
            for (size_t j = 0; j < transposed[0].size(); j++)
                {
                    if (j != array2D.size() - 1)
                        file << transposed[i][j] << ",";
                    else
                        file << transposed[i][j] << "\n";
                }
        }

    file.close();
}

bool verify_sort(std::vector<long>& array, std::string path_sorted)
{
    std::vector<long> array2;

    read_array_from_file(array2, path_sorted);
    if (array != array2)
        {
            std::cout << "Warning: arrays not equal!\n";
            return false;
        }
    else
        return true;
}

bool verify_sort(std::vector<int>& array, std::string path_sorted)
{
    std::vector<int> array2;

    read_array_from_file(array2, path_sorted);
    if (array != array2)
        {
            std::cout << "Warning: arrays not equal!\n";
            return false;
        }
    else
        return true;
}

std::vector<std::filesystem::directory_entry> get_directory_content(std::string path, bool files_only = false, bool directories_only = false)
{
    if (!files_only && !directories_only)
        throw std::invalid_argument("Error:get_directory_content: function useless due to all bool parameters set to false");

    std::vector<std::filesystem::directory_entry> entries;
    // Iterate over the directory and store entries
    for (const auto& entry : std::filesystem::directory_iterator(path))
        {
            if ((files_only && entry.is_regular_file()) || (directories_only && entry.is_directory()))
                {
                    entries.push_back(entry);
                }
        }

    std::sort(entries.begin(), entries.end(), [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b) {
        return a.path().filename().string() < b.path().filename().string();   // Sorting alphabetically
    });

    return entries;
}

void test(std::string path_unsorted, std::vector<std::vector<double>>& time_array2D, std::vector<std::string>& row_names, void sort_function(long*, size_t), bool verify, int limit)
{
    std::vector<std::filesystem::directory_entry> directories = get_directory_content(path_unsorted, false, true);
    std::vector<long>                             array;
    int                                           i = 0;
    bool                                          stop = false;
    for (auto& p : directories)
        {
            std::vector<std::filesystem::directory_entry> files = get_directory_content(p.path().string(), true);
            int                                           j = 0;
            time_array2D.push_back(std::vector<double>());
            for (auto& entry : files)
                {
                    std::string s = entry.path().string();
                    read_array_from_file(array, s);
                    long* arr = array.data();
                    // std::copy(array.begin(), array.end(), arr);
                    std::cout << "At step " << j << " in " << get_stem(p) << "\n";
                    auto time_start = std::chrono::system_clock::now();
                    sort_function(arr, array.size());
                    auto time_end = std::chrono::system_clock::now();

                    std::chrono::duration<double> time_difference = time_end - time_start;
                    time_array2D[i].push_back(time_difference.count());
                    if (time_difference.count() > 10.0)
                        {
                            stop = true;
                        }
                    if (verify)
                        verify_sort(array, s.replace(s.find("unsorted"), 8, "sorted"));
                    if (i == 0)
                        {
                            s = get_stem(entry.path());
                            s.erase(0, 5);   // get rid of the first 5 characters in the name of the file
                            row_names.push_back(s);
                        }
                    array.erase(array.begin(), array.end());
                    j++;
                }
            i++;
            if (i == limit || stop)   // stop if it hits the limit for maximum array size to sort (e.g. 10^5, i is the exponent)
                break;   // or stop if the previous sort exceeded 60 seconds
        }
}

void test(std::string path_unsorted, std::vector<std::vector<double>>& time_array2D, std::vector<std::string>& row_names, void sort_function(long*, long, long), bool verify, int limit)
{
    std::vector<std::filesystem::directory_entry> directories = get_directory_content(path_unsorted, false, true);
    std::vector<long>                             array;
    int                                           i = 0;
    bool                                          stop = false;
    for (auto& p : directories)
        {
            std::vector<std::filesystem::directory_entry> files = get_directory_content(p.path().string(), true);
            int                                           j = 0;
            time_array2D.push_back(std::vector<double>());
            for (auto& entry : files)
                {
                    std::string s = entry.path().string();
                    read_array_from_file(array, s);
                    long* arr = array.data();
                    // std::copy(array.begin(), array.end(), arr);
                    std::cout << "At step " << j << " in " << get_stem(p) << "\n";
                    auto time_start = std::chrono::system_clock::now();
                    sort_function(arr, 0, array.size() - 1);
                    auto time_end = std::chrono::system_clock::now();

                    std::chrono::duration<double> time_difference = time_end - time_start;
                    time_array2D[i].push_back(time_difference.count());
                    if (time_difference.count() > 10.0)
                        {
                            stop = true;
                        }

                    if (verify)
                        verify_sort(array, s.replace(s.find("unsorted"), 8, "sorted"));
                    if (i == 0)
                        {
                            s = get_stem(entry.path());
                            s.erase(0, 5);
                            row_names.push_back(s);
                        }
                    array.erase(array.begin(), array.end());
                    j++;
                }
            i++;
            if (i == limit || stop)   // stop if it hits the limit for maximum array size to sort (e.g. 10^5, i is the exponent)
                break;   // or stop if the previous sort exceeded 60 seconds
        }
}

void test(std::string path_unsorted, std::vector<std::vector<double>>& time_array2D, std::vector<std::string>& row_names, void sort_function(long*, long, long, bool), bool mof, bool verify, int limit)
{
    std::vector<std::filesystem::directory_entry> directories = get_directory_content(path_unsorted, false, true);
    std::vector<long>                             array;
    int                                           i = 0;
    bool                                          stop = false;
    for (auto& p : directories)
        {
            std::vector<std::filesystem::directory_entry> files = get_directory_content(p.path().string(), true);
            int                                           j = 0;
            time_array2D.push_back(std::vector<double>());
            for (auto& entry : files)
                {
                    std::string s = entry.path().string();
                    read_array_from_file(array, s);
                    long* arr = array.data();
                    // std::copy(array.begin(), array.end(), arr);
                    std::cout << "At step " << j << " in " << get_stem(p) << "\n";
                    auto time_start = std::chrono::system_clock::now();
                    sort_function(arr, 0, array.size() - 1, mof);
                    auto time_end = std::chrono::system_clock::now();

                    std::chrono::duration<double> time_difference = time_end - time_start;
                    time_array2D[i].push_back(time_difference.count());
                    if (time_difference.count() > 10.0)
                        {
                            stop = true;
                        }

                    if (verify)
                        verify_sort(array, s.replace(s.find("unsorted"), 8, "sorted"));
                    if (i == 0)
                        {
                            s = get_stem(entry.path());
                            s.erase(0, 5);
                            row_names.push_back(s);
                        }
                    array.erase(array.begin(), array.end());
                    j++;
                }
            i++;
            if (i == limit || stop)   // stop if it hits the limit for maximum array size to sort (e.g. 10^5, i is the exponent)
                break;   // or stop if the previous sort exceeded 60 seconds
        }
}

void test(std::string path_unsorted, std::vector<std::vector<double>>& time_array2D, std::vector<std::string>& row_names, void sort_function(long*, size_t, bool), bool option, bool verify, int limit)
{
    std::vector<std::filesystem::directory_entry> directories = get_directory_content(path_unsorted, false, true);
    std::vector<long>                             array;
    int                                           i = 0;
    bool                                          stop = false;
    for (auto& p : directories)
        {
            std::vector<std::filesystem::directory_entry> files = get_directory_content(p.path().string(), true);
            int                                           j = 0;
            time_array2D.push_back(std::vector<double>());
            for (auto& entry : files)
                {
                    std::string s = entry.path().string();
                    read_array_from_file(array, s);
                    long* arr = array.data();
                    // std::copy(array.begin(), array.end(), arr);
                    std::cout << "At step " << j << " in " << get_stem(p) << "\n";
                    auto time_start = std::chrono::system_clock::now();
                    sort_function(arr, array.size(), option);
                    auto time_end = std::chrono::system_clock::now();

                    std::chrono::duration<double> time_difference = time_end - time_start;
                    time_array2D[i].push_back(time_difference.count());
                    if (time_difference.count() > 10.0)
                        {
                            stop = true;
                        }

                    if (verify)
                        verify_sort(array, s.replace(s.find("unsorted"), 8, "sorted"));
                    if (i == 0)
                        {
                            s = get_stem(entry.path());
                            s.erase(0, 5);
                            row_names.push_back(s);
                        }
                    array.erase(array.begin(), array.end());
                    j++;
                }
            i++;
            if (i == limit || stop)   // stop if it hits the limit for maximum array size to sort (e.g. 10^5, i is the exponent)
                break;   // or stop if the previous sort exceeded 60 seconds
        }
}

void test_2(std::string path_unsorted, std::vector<std::vector<double>>& time_array2D, std::vector<std::string>& row_names, void sort_function(int*, size_t), bool verify, int limit)
{
    std::vector<std::filesystem::directory_entry> directories = get_directory_content(path_unsorted, false, true);
    std::vector<int>                              array;
    int                                           i = 0;
    bool                                          stop = false;
    for (auto& p : directories)
        {
            std::vector<std::filesystem::directory_entry> files = get_directory_content(p.path().string(), true);
            int                                           j = 0;
            time_array2D.push_back(std::vector<double>());
            for (auto& entry : files)
                {
                    std::string s = entry.path().string();
                    read_array_from_file(array, s);
                    int* arr = array.data();
                    // std::copy(array.begin(), array.end(), arr);
                    std::cout << "At step " << j << " in " << get_stem(p) << "\n";
                    auto time_start = std::chrono::system_clock::now();
                    sort_function(arr, array.size());
                    auto time_end = std::chrono::system_clock::now();

                    std::chrono::duration<double> time_difference = time_end - time_start;
                    time_array2D[i].push_back(time_difference.count());
                    if (time_difference.count() > 10.0)
                        {
                            stop = true;
                        }
                    if (verify)
                        verify_sort(array, s.replace(s.find("unsorted"), 8, "sorted"));
                    if (i == 0)
                        {
                            s = get_stem(entry.path());
                            s.erase(0, 5);
                            row_names.push_back(s);
                        }
                    array.erase(array.begin(), array.end());
                    j++;
                }
            i++;
            if (i == limit || stop)   // stop if it hits the limit for maximum array size to sort (e.g. 10^5, i is the exponent)
                break;   // or stop if the previous sort exceeded 60 seconds
        }
}

void test_2(std::string path_unsorted, std::vector<std::vector<double>>& time_array2D, std::vector<std::string>& row_names, void sort_function(int*, long, long), bool verify, int limit)
{
    std::vector<std::filesystem::directory_entry> directories = get_directory_content(path_unsorted, false, true);
    std::vector<int>                              array;
    int                                           i = 0;
    bool                                          stop = false;
    for (auto& p : directories)
        {
            std::vector<std::filesystem::directory_entry> files = get_directory_content(p.path().string(), true);
            int                                           j = 0;
            time_array2D.push_back(std::vector<double>());
            for (auto& entry : files)
                {
                    std::string s = entry.path().string();
                    read_array_from_file(array, s);
                    int* arr = array.data();
                    // std::copy(array.begin(), array.end(), arr);
                    std::cout << "At step " << j << " in " << get_stem(p) << "\n";
                    auto time_start = std::chrono::system_clock::now();
                    sort_function(arr, 0, array.size() - 1);
                    auto time_end = std::chrono::system_clock::now();

                    std::chrono::duration<double> time_difference = time_end - time_start;
                    time_array2D[i].push_back(time_difference.count());
                    if (time_difference.count() > 10.0)
                        {
                            stop = true;
                        }

                    if (verify)
                        verify_sort(array, s.replace(s.find("unsorted"), 8, "sorted"));
                    if (i == 0)
                        {
                            s = get_stem(entry.path());
                            s.erase(0, 5);
                            row_names.push_back(s);
                        }
                    array.erase(array.begin(), array.end());
                    j++;
                }
            i++;
            if (i == limit || stop)   // stop if it hits the limit for maximum array size to sort (e.g. 10^5, i is the exponent)
                break;   // or stop if the previous sort exceeded 60 seconds
        }
}

void test_2(std::string path_unsorted, std::vector<std::vector<double>>& time_array2D, std::vector<std::string>& row_names, void sort_function(int*, long, long, bool), bool mof, bool verify, int limit)
{
    std::vector<std::filesystem::directory_entry> directories = get_directory_content(path_unsorted, false, true);
    std::vector<int>                              array;
    int                                           i = 0;
    bool                                          stop = false;
    for (auto& p : directories)
        {
            std::vector<std::filesystem::directory_entry> files = get_directory_content(p.path().string(), true);
            int                                           j = 0;
            time_array2D.push_back(std::vector<double>());
            for (auto& entry : files)
                {
                    std::string s = entry.path().string();
                    read_array_from_file(array, s);
                    int* arr = array.data();
                    // std::copy(array.begin(), array.end(), arr);
                    std::cout << "At step " << j << " in " << get_stem(p) << "\n";
                    auto time_start = std::chrono::system_clock::now();
                    sort_function(arr, 0, array.size() - 1, mof);
                    auto time_end = std::chrono::system_clock::now();

                    std::chrono::duration<double> time_difference = time_end - time_start;
                    time_array2D[i].push_back(time_difference.count());
                    if (time_difference.count() > 10.0)
                        {
                            stop = true;
                        }

                    if (verify)
                        verify_sort(array, s.replace(s.find("unsorted"), 8, "sorted"));
                    if (i == 0)
                        {
                            s = get_stem(entry.path());
                            s.erase(0, 5);
                            row_names.push_back(s);
                        }
                    array.erase(array.begin(), array.end());
                    j++;
                }
            i++;
            if (i == limit || stop)   // stop if it hits the limit for maximum array size to sort (e.g. 10^5, i is the exponent)
                break;   // or stop if the previous sort exceeded 60 seconds
        }
}

void test_2(std::string path_unsorted, std::vector<std::vector<double>>& time_array2D, std::vector<std::string>& row_names, void sort_function(int*, size_t, bool), bool option, bool verify, int limit)
{
    std::vector<std::filesystem::directory_entry> directories = get_directory_content(path_unsorted, false, true);
    std::vector<int>                              array;
    int                                           i = 0;
    bool                                          stop = false;
    for (auto& p : directories)
        {
            std::vector<std::filesystem::directory_entry> files = get_directory_content(p.path().string(), true);
            int                                           j = 0;
            time_array2D.push_back(std::vector<double>());
            for (auto& entry : files)
                {
                    std::string s = entry.path().string();
                    read_array_from_file(array, s);
                    int* arr = array.data();
                    // std::copy(array.begin(), array.end(), arr);
                    std::cout << "At step " << j << " in " << get_stem(p) << "\n";
                    auto time_start = std::chrono::system_clock::now();
                    sort_function(arr, array.size(), option);
                    auto time_end = std::chrono::system_clock::now();

                    std::chrono::duration<double> time_difference = time_end - time_start;
                    time_array2D[i].push_back(time_difference.count());
                    if (time_difference.count() > 10.0)
                        {
                            stop = true;
                        }

                    if (verify)
                        verify_sort(array, s.replace(s.find("unsorted"), 8, "sorted"));
                    if (i == 0)
                        {
                            s = get_stem(entry.path());
                            s.erase(0, 5);
                            row_names.push_back(s);
                        }
                    array.erase(array.begin(), array.end());
                    j++;
                }
            i++;
            if (i == limit || stop)   // stop if it hits the limit for maximum array size to sort (e.g. 10^5, i is the exponent)
                break;   // or stop if the previous sort exceeded 60 seconds
        }
}

void test1(int mode, std::string path_s, std::string path_d, bool verify, int limit)
{
    std::cout << "BottomUpMergeSort\n";
    std::vector<std::vector<double>> matrix;
    std::vector<std::string>         row_names;
    if (mode == 0)
        test(path_s, matrix, row_names, &BottomUpMergeSort, verify, limit);
    else
        test_2(path_s, matrix, row_names, &BottomUpMergeSort, verify, limit);
    write_to_csv(path_d + "BottomUpMergeSort.csv", matrix, row_names);
}
void test2(int mode, std::string path_s, std::string path_d, bool verify, int limit)
{
    std::cout << "bubblesort\n";
    std::vector<std::vector<double>> matrix;
    std::vector<std::string>         row_names;
    if (mode == 0)
        test(path_s, matrix, row_names, &bubble_sort, verify, limit);
    else
        test_2(path_s, matrix, row_names, &bubble_sort, verify, limit);
    write_to_csv(path_d + "bubblesort.csv", matrix, row_names);
}
void test3(int mode, std::string path_s, std::string path_d, bool verify, int limit)
{
    std::cout << "selection_sort\n";
    std::vector<std::vector<double>> matrix;
    std::vector<std::string>         row_names;
    if (mode == 0)
        test(path_s, matrix, row_names, &selection_sort, verify, limit);
    else
        test_2(path_s, matrix, row_names, &selection_sort, verify, limit);
    write_to_csv(path_d + "selection_sort.csv", matrix, row_names);
}
void test4(int mode, std::string path_s, std::string path_d, bool verify, int limit)
{
    std::cout << "insertion_sort\n";
    std::vector<std::vector<double>> matrix;
    std::vector<std::string>         row_names;
    test(path_s, matrix, row_names, &insertion_sort, verify, limit);
    write_to_csv(path_d + "insertion_sort.csv", matrix, row_names);
}
void test5(int mode, std::string path_s, std::string path_d, bool verify, int limit)
{
    std::cout << "HoareQuickSort\n";
    std::vector<std::vector<double>> matrix;
    std::vector<std::string>         row_names;
    if (mode == 0)
        test(path_s, matrix, row_names, &HoareQuickSort, verify, limit);
    else
        test_2(path_s, matrix, row_names, &HoareQuickSort, verify, limit);
    write_to_csv(path_d + "HoareQuickSort.csv", matrix, row_names);
}
void test6(int mode, std::string path_s, std::string path_d, bool verify, int limit)
{
    std::cout << "TopDownMergeSort\n";
    std::vector<std::vector<double>> matrix;
    std::vector<std::string>         row_names;
    if (mode == 0)
        test(path_s, matrix, row_names, &TopDownMergeSort, verify, limit);
    else
        test_2(path_s, matrix, row_names, &TopDownMergeSort, verify, limit);
    write_to_csv(path_d + "TopDownMergeSort.csv", matrix, row_names);
}
void test7(int mode, std::string path_s, std::string path_d, bool verify, int limit)
{
    std::cout << "heapsort\n";
    std::vector<std::vector<double>> matrix;
    std::vector<std::string>         row_names;
    if (mode == 0)
        test(path_s, matrix, row_names, &heapsort, false, verify, limit);
    else
        test_2(path_s, matrix, row_names, &heapsort, false, verify, limit);
    write_to_csv(path_d + "heapsort.csv", matrix, row_names);
}
void test8(int mode, std::string path_s, std::string path_d, bool verify, int limit)
{
    std::cout << "heapsort_siftup\n";
    std::vector<std::vector<double>> matrix;
    std::vector<std::string>         row_names;
    if (mode == 0)
        test(path_s, matrix, row_names, &heapsort, true, verify, limit);
    else
        test_2(path_s, matrix, row_names, &heapsort, true, verify, limit);
    write_to_csv(path_d + "heapsort_siftup.csv", matrix, row_names);
}
void test9(int mode, std::string path_s, std::string path_d, bool verify, int limit)
{
    std::cout << "BottomUpHeapSort\n";
    std::vector<std::vector<double>> matrix;
    std::vector<std::string>         row_names;
    if (mode == 0)
        test(path_s, matrix, row_names, &BottomUpHeapSort, verify, limit);
    else
        test_2(path_s, matrix, row_names, &BottomUpHeapSort, verify, limit);
    write_to_csv(path_d + "BottomUpHeapSort.csv", matrix, row_names);
}
void test10(int mode, std::string path_s, std::string path_d, bool verify, int limit)
{
    std::cout << "BucketSortMixed\n";
    std::vector<std::vector<double>> matrix;
    std::vector<std::string>         row_names;
    if (mode == 0)
        test(path_s, matrix, row_names, &BucketSortMixed, false, verify, limit);
    else
        test_2(path_s, matrix, row_names, &BucketSortMixed, false, verify, limit);
    write_to_csv(path_d + "BucketSortMixed.csv", matrix, row_names);
}
void test11(int mode, std::string path_s, std::string path_d, bool verify, int limit)
{
    std::cout << "BucketSortMixed_opt\n";
    std::vector<std::vector<double>> matrix;
    std::vector<std::string>         row_names;
    if (mode == 0)
        test(path_s, matrix, row_names, &BucketSortMixed, true, verify, limit);
    else
        test_2(path_s, matrix, row_names, &BucketSortMixed, true, verify, limit);
    write_to_csv(path_d + "BucketSortMixed_opt.csv", matrix, row_names);
}
void test12(int mode, std::string path_s, std::string path_d, bool verify, int limit)
{
    std::cout << "LomutoQuickSort\n";
    std::vector<std::vector<double>> matrix;
    std::vector<std::string>         row_names;
    if (mode == 0)
        test(path_s, matrix, row_names, &LomutoQuickSort, false, verify, limit);
    else
        test_2(path_s, matrix, row_names, &LomutoQuickSort, false, verify, limit);
    write_to_csv(path_d + "LomutoQuickSort.csv", matrix, row_names);
}
void test13(int mode, std::string path_s, std::string path_d, bool verify, int limit)
{
    std::cout << "LomutoQuickSort_mof\n";
    std::vector<std::vector<double>> matrix;
    std::vector<std::string>         row_names;
    if (mode == 0)
        test(path_s, matrix, row_names, &LomutoQuickSort, true, verify, limit);
    else
        test_2(path_s, matrix, row_names, &LomutoQuickSort, true, verify, limit);
    write_to_csv(path_d + "LomutoQuickSort_mof.csv", matrix, row_names);
}
void test14(int mode, std::string path_s, std::string path_d, bool verify, int limit)
{
    std::cout << "LomutoQuickSort_rep\n";
    std::vector<std::vector<double>> matrix;
    std::vector<std::string>         row_names;
    if (mode == 0)
        test(path_s, matrix, row_names, &LomutoQuickSort_rep, verify, limit);
    else
        test_2(path_s, matrix, row_names, &LomutoQuickSort_rep, verify, limit);
    write_to_csv(path_d + "LomutoQuickSort_rep.csv", matrix, row_names);
}
void test15(int mode, std::string path_s, std::string path_d, bool verify, int limit)
{
    std::cout << "radix_sort\n";
    std::vector<std::vector<double>> matrix;
    std::vector<std::string>         row_names;
    if (mode == 0)
        test(path_s, matrix, row_names, &radix_sort, verify, limit);
    else
        test_2(path_s, matrix, row_names, &radix_sort, verify, limit);
    write_to_csv(path_d + "radix_sort.csv", matrix, row_names);
}   // rip doesn't work on long numbers
void test16(int mode, std::string path_s, std::string path_d, bool verify, int limit)
{
    std::cout << "counting_sort\n";
    std::vector<std::vector<double>> matrix;
    std::vector<std::string>         row_names;
    if (mode == 0)
        test(path_s, matrix, row_names, &counting_sort, verify, limit);
    else
        test_2(path_s, matrix, row_names, &counting_sort, verify, limit);
    write_to_csv(path_d + "counting_sort.csv", matrix, row_names);
}   // rip as well
