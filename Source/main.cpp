#include "headers.hpp"
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sys/resource.h>

void print(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        {
            std::cout << arr[i] << " ";
        }
}

void generate_and_sort(bool mode, std::string path_s, std::string path_d)
{
    for (int i = 1; i < 9; i++)
        {
            long int    number = std::pow(10, i);
            std::string temp = path_s + "10^" + std::to_string(i) + "/10^" + std::to_string(i);
            if (mode)
                generate_int(number, temp);
            else
                generate(number, temp);
        }

    for (int i = 1; i < 9; i++)
        {
            sort_arrays_from_files(path_s + "10^" + std::to_string(i), path_d + "10^" + std::to_string(i));
        }
}

void test_all(int mode, std::string path_s, std::string results_path, bool verify = true, int limit = 8)
{
    test1(mode, path_s, results_path, verify, limit);
    test2(mode, path_s, results_path, verify, 5);
    test3(mode, path_s, results_path, verify, 5);
    test4(mode, path_s, results_path, verify, 5);
    test5(mode, path_s, results_path, verify, limit);
    test6(mode, path_s, results_path, verify, limit);
    test7(mode, path_s, results_path, verify, limit);
    test8(mode, path_s, results_path, verify, 5);
    test9(mode, path_s, results_path, verify, limit);
    test10(mode, path_s, results_path, verify, limit);
    test11(mode, path_s, results_path, verify, limit);
    test12(mode, path_s, results_path, verify, limit);
    test13(mode, path_s, results_path, verify, limit);
    test14(mode, path_s, results_path, verify, limit);
    test15(mode, path_s, results_path, verify, limit);
    test16(mode, path_s, results_path, verify, limit);
}

void generate_sort_test(bool int_type = true, bool long_type = true, int times_to_generate = 1)
{
    for (int i = 1; i <= times_to_generate; i++)
        {
            if (int_type)
                {
                    std::string path_s = "Generated/dataset/unsorted/int/";
                    std::string path_d = "Generated/dataset/sorted/int/";
                    std::string results_path = "Generated/results/int/" + std::to_string(i) + "/";
                    std::cout << "Generating int set...\n";
                    generate_and_sort(true, path_s, path_d);
                    std::cout << "Generated set.\n";
                    test_all(1, path_s, results_path);
                }
            if (long_type)
                {
                    std::string path_s = "Generated/dataset/unsorted/long_int/";
                    std::string path_d = "Generated/dataset/sorted/long_int/";
                    std::string results_path = "Generated/results/long_int/" + std::to_string(i) + "/";
                    std::cout << "Generating long int set...\n";
                    generate_and_sort(false, path_s, path_d);
                    std::cout << "Generated set.\n";
                    test_all(0, path_s, results_path);
                }
        }
}

int main()
{
    // Increase stack size for recursion algorithms
    const rlim_t  kStackSize = 64 * 1024 * 1024;   // min stack size = 64 MB
    struct rlimit rl;
    int           result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
        {
            if (rl.rlim_cur < kStackSize)
                {
                    rl.rlim_cur = kStackSize;
                    result = setrlimit(RLIMIT_STACK, &rl);
                    if (result != 0)
                        {
                            fprintf(stderr, "setrlimit returned result = %d\n", result);
                        }
                }
        }

    // Begin
    std::string path_s = "Generated/dataset/unsorted/int/";
    std::string path_d = "Generated/dataset/sorted/int/";
    std::string results_path = "Generated/results/int/";
    // generate_and_sort(true, path_s, path_d);
    // generate_sort_test(false);

    // mode of a function defines whether it handles sorting values of type int (1) or long int (0)
    // test1(1, path_s, results_path);
    // test2(1, path_s, results_path, true, 8);
    // test3(1, path_s, results_path);
    // test4(1, path_s, results_path);
    // test5(1, path_s, results_path);
    // test6(1, path_s, results_path);
    // test7(1, path_s, results_path);
    // test8(1, path_s, results_path);
    // test9(1, path_s, results_path);
    // test10(1, path_s, results_path, true, 8);
    // test11(1, path_s, results_path, true, 7);
    // test12(1, path_s, results_path, false, 5);
    // test13(1, path_s, results_path);
    // test14(1, path_s, results_path, true, 7);
    // test10(0, "Generated/dataset/unsorted/long_int/", "Generated/results/long_int/", true, 5);
    // test11(0, "Generated/dataset/unsorted/long_int/", "Generated/results/long_int/", true, 5);
    // test15(0, "Generated/dataset/unsorted/long_int/", "Generated/results/long_int/1", true, 8); //fails
    // test16(0, "Generated/dataset/unsorted/long_int/", "Generated/results/long_int/1", true, 8); //fails

    // TODO(CHECK): Implement a variant of lomuto quicksort for repeated elements that fixes the huge stack blowup
    // TODO: Make sure the final tests are made with the Release build and not the Debug one
    // TODO: Try to make use of templates to handle int (16bit), long (32bit) and long long (64bit) values to test the differences in compute
    // TODO: Test for each dataset (int, long, long long) at least 3 times and then average the result. Then generate 5 datasets for each type (15 total datasets) and test for each. Write code to do this automatically.
    return 0;
}