#include "headers.hpp"
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <random>
#include <string>
namespace fs = std::filesystem;

std::vector<long> rand_uniform_distribution(long l_bound, long u_bound, long amount)
{
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::default_random_engine         generator(seed);
    std::uniform_int_distribution<int> distribution(l_bound, u_bound);
    std::vector<long>                  array;

    for (long i = 0; i < amount; i++)
        {
            array.push_back(distribution(generator));
        }

    return array;
}

std::vector<int> rand_uniform_distribution2(int l_bound, int u_bound, long amount)
{
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::default_random_engine         generator(seed);
    std::uniform_int_distribution<int> distribution(l_bound, u_bound);
    std::vector<int>                   array;

    for (long i = 0; i < amount; i++)
        {
            array.push_back(distribution(generator));
        }

    return array;
}

std::vector<long> batch_gen(int batches, long l_bound, long u_bound, long amount)
{
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::default_random_engine          generator(seed);
    std::uniform_int_distribution<long> distribution(l_bound, u_bound);
    std::vector<long>                   array;
    long                                batch;

    for (int i = 1; i <= batches; i++)
        {
            batch = distribution(generator);
            for (long j = 0; j < amount / batches; j++)
                {
                    array.push_back(batch);
                }
        }
    return array;
}

std::vector<int> batch_gen2(int batches, int l_bound, int u_bound, long amount)
{
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::default_random_engine         generator(seed);
    std::uniform_int_distribution<int> distribution(l_bound, u_bound);
    std::vector<int>                   array;
    long                               batch;

    for (int i = 1; i <= batches; i++)
        {
            batch = distribution(generator);
            for (long j = 0; j < amount / batches; j++)
                {
                    array.push_back(batch);
                }
        }
    return array;
}

long positive_rand(long u_bound = 0)
{
    std::srand(std::chrono::system_clock::now().time_since_epoch().count());
    if (u_bound == 0)
        return std::rand();
    else
        return std::rand() % u_bound;
}

long negative_rand(long u_bound = 0)
{
    std::srand(std::chrono::system_clock::now().time_since_epoch().count());
    if (u_bound == 0)
        return std::rand() - RAND_MAX;
    else
        return std::rand() % u_bound - u_bound;
}

void unsorted_gen(long amount, char* filename, long randomf(long), long param = 0)
{
    std::ofstream file;
    file.open(filename);
    for (long i = 0; i < amount; i++)
        {
            if (i != amount - 1)
                file << randomf(param) << " ";
            else
                file << randomf(param);
        }
    file.close();
}

void unsorted_gen(long amount, std::string filename, long randomf(long), long param = 0)
{
    std::ofstream file;
    file.open(filename);
    for (long i = 0; i < amount; i++)
        {
            if (i != amount - 1)
                file << randomf(param) << " ";
            else
                file << randomf(param);
        }
    file.close();
}

void read_array_from_file(std::vector<long>& array, char* filename)
{
    long          temp;
    std::ifstream file;
    file.open(filename);

    while (!file.eof())
        {
            file >> temp;
            array.push_back(temp);
        }
    file.close();
}

void read_array_from_file(std::vector<long>& array, std::string filename)
{
    long          temp;
    std::ifstream file;
    file.open(filename);

    while (!file.eof())
        {
            file >> temp;
            array.push_back(temp);
        }
    file.close();
}

void read_array_from_file(std::vector<int>& array, std::string filename)
{
    int           temp;
    std::ifstream file;
    file.open(filename);

    while (!file.eof())
        {
            file >> temp;
            array.push_back(temp);
        }
    file.close();
}

void write_array_to_file(std::vector<long>& array, char* filename)
{
    std::ofstream file;
    file.open(filename);
    for (size_t i = 0; i < array.size(); i++)
        {
            if (i != array.size() - 1)
                file << array[i] << " ";
            else
                file << array[i];
        }
    file.close();
}

void write_array_to_file(std::vector<long>& array, std::string filename)
{
    std::ofstream file;
    file.open(filename);
    for (size_t i = 0; i < array.size(); i++)
        {
            if (i != array.size() - 1)
                file << array[i] << " ";
            else
                file << array[i];
        }
    file.close();
}

void write_array_to_file(std::vector<int>& array, std::string filename)
{
    std::ofstream file;
    file.open(filename);
    for (size_t i = 0; i < array.size(); i++)
        {
            if (i != array.size() - 1)
                file << array[i] << " ";
            else
                file << array[i];
        }
    file.close();
}

void half_sort(char* filename, bool reverse = false)
{
    std::vector<long> array;
    read_array_from_file(array, filename);
    std::sort(array.begin(), array.begin() + array.size() / 2);
    if (reverse)
        {
            std::reverse(array.begin(), array.begin() + array.size() / 2);
        }
    write_array_to_file(array, filename);
}

void generate(long amount, char* filename)
{
    std::vector<long> array;
    char              temp[100];

    // positive list
    std::sprintf(temp, "%s_p.txt", filename);
    unsorted_gen(amount, temp, &positive_rand);
    // negative list
    std::sprintf(temp, "%s_n.txt", filename);
    unsorted_gen(amount, temp, &negative_rand);
    // negative and positive list (default)
    std::sprintf(temp, "%s_n&p.txt", filename);
    array = rand_uniform_distribution(INT64_MIN, INT64_MAX, amount);
    write_array_to_file(array, temp);
    // sorted list
    std::sprintf(temp, "%s_sorted.txt", filename);
    std::sort(array.begin(), array.end());
    write_array_to_file(array, temp);
    // reverse sorted list
    std::sprintf(temp, "%s_r_sorted.txt", filename);
    std::reverse(array.begin(), array.end());
    write_array_to_file(array, temp);
    // half sorted list
    std::sprintf(temp, "%s_half_sorted.txt", filename);
    array = rand_uniform_distribution(INT64_MIN, INT64_MAX, amount);
    std::sort(array.begin(), array.begin() + array.size() / 2);
    write_array_to_file(array, temp);
    // reverse half sorted list
    std::sprintf(temp, "%s_r_half_sorted.txt", filename);
    std::reverse(array.begin(), array.begin() + array.size() / 2);
    write_array_to_file(array, temp);
    // only 3 numbers list
    std::sprintf(temp, "%s_only3.txt", filename);
    array = rand_uniform_distribution(1, 3, amount);
    write_array_to_file(array, temp);
    // sorted only 3 numbers list
    std::sprintf(temp, "%s_sorted_only3.txt", filename);
    std::sort(array.begin(), array.end());
    write_array_to_file(array, temp);
    // reverse sorted only 3 numbers list
    std::sprintf(temp, "%s_r_sorted_only3.txt", filename);
    std::reverse(array.begin(), array.end());
    write_array_to_file(array, temp);
    // batch like repeating numbers list
    std::sprintf(temp, "%s_10batch.txt", filename);
    array = batch_gen(10, INT64_MIN, INT64_MAX, amount);
    write_array_to_file(array, temp);
    // sorted batch like repeated numbers
    std::sprintf(temp, "%s_sorted_10batch.txt", filename);
    std::sort(array.begin(), array.end());
    write_array_to_file(array, temp);
    // reversed sorted batch
    std::sprintf(temp, "%s_r_sorted_10batch.txt", filename);
    std::reverse(array.begin(), array.end());
    write_array_to_file(array, temp);
}

void generate(long amount, std::string filename)
{
    std::vector<long> array;
    std::string       temp;

    // positive list
    temp = filename + "_p.txt";
    unsorted_gen(amount, temp, &positive_rand);
    // negative list
    temp = filename + "_n.txt";
    unsorted_gen(amount, temp, &negative_rand);
    // negative and positive list (default)
    temp = filename + "_n&p.txt";
    array = rand_uniform_distribution(INT64_MIN, INT64_MAX, amount);
    write_array_to_file(array, temp);
    // sorted list
    temp = filename + "_sorted.txt";
    std::sort(array.begin(), array.end());
    write_array_to_file(array, temp);
    // reverse sorted list
    temp = filename + "_r_sorted.txt";
    std::reverse(array.begin(), array.end());
    write_array_to_file(array, temp);
    // half sorted list
    temp = filename + "_half_sorted.txt";
    array = rand_uniform_distribution(INT64_MIN, INT64_MAX, amount);
    std::sort(array.begin(), array.begin() + array.size() / 2);
    write_array_to_file(array, temp);
    // reverse half sorted list
    temp = filename + "_r_half_sorted.txt";
    std::reverse(array.begin(), array.begin() + array.size() / 2);
    write_array_to_file(array, temp);
    // only 3 numbers list
    temp = filename + "_only3.txt";
    array = rand_uniform_distribution(1, 3, amount);
    write_array_to_file(array, temp);
    // sorted only 3 numbers list
    temp = filename + "_sorted_only3.txt";
    std::sort(array.begin(), array.end());
    write_array_to_file(array, temp);
    // reverse sorted only 3 numbers list
    temp = filename + "_r_sorted_only3.txt";
    std::reverse(array.begin(), array.end());
    write_array_to_file(array, temp);
    // batch like repeating numbers list
    temp = filename + "_10batch.txt";
    array = batch_gen(10, INT64_MIN, INT64_MAX, amount);
    write_array_to_file(array, temp);
    // sorted batch like repeated numbers
    temp = filename + "_sorted_10batch.txt";
    std::sort(array.begin(), array.end());
    write_array_to_file(array, temp);
    // reversed sorted batch
    temp = filename + "_r_sorted_10batch.txt";
    std::reverse(array.begin(), array.end());
    write_array_to_file(array, temp);
}

void generate_int(long amount, std::string filename)
{
    std::vector<int> array;
    std::string      temp;

    // positive list
    temp = filename + "_p.txt";
    unsorted_gen(amount, temp, &positive_rand, INT32_MAX);
    // negative list
    temp = filename + "_n.txt";
    unsorted_gen(amount, temp, &negative_rand, INT32_MAX);
    // negative and positive list (default)
    temp = filename + "_n&p.txt";
    array = rand_uniform_distribution2(INT32_MIN, INT32_MAX, amount);
    write_array_to_file(array, temp);
    // sorted list
    temp = filename + "_sorted.txt";
    std::sort(array.begin(), array.end());
    write_array_to_file(array, temp);
    // reverse sorted list
    temp = filename + "_r_sorted.txt";
    std::reverse(array.begin(), array.end());
    write_array_to_file(array, temp);
    // half sorted list
    temp = filename + "_half_sorted.txt";
    array = rand_uniform_distribution2(INT32_MIN, INT32_MAX, amount);
    std::sort(array.begin(), array.begin() + array.size() / 2);
    write_array_to_file(array, temp);
    // reverse half sorted list
    temp = filename + "_r_half_sorted.txt";
    std::reverse(array.begin(), array.begin() + array.size() / 2);
    write_array_to_file(array, temp);
    // only 3 numbers list
    temp = filename + "_only3.txt";
    array = rand_uniform_distribution2(1, 3, amount);
    write_array_to_file(array, temp);
    // sorted only 3 numbers list
    temp = filename + "_sorted_only3.txt";
    std::sort(array.begin(), array.end());
    write_array_to_file(array, temp);
    // reverse sorted only 3 numbers list
    temp = filename + "_r_sorted_only3.txt";
    std::reverse(array.begin(), array.end());
    write_array_to_file(array, temp);
    // batch like repeating numbers list
    temp = filename + "_10batch.txt";
    array = batch_gen2(10, INT32_MIN, INT32_MAX, amount);
    write_array_to_file(array, temp);
    // sorted batch like repeated numbers
    temp = filename + "_sorted_10batch.txt";
    std::sort(array.begin(), array.end());
    write_array_to_file(array, temp);
    // reversed sorted batch
    temp = filename + "_r_sorted_10batch.txt";
    std::reverse(array.begin(), array.end());
    write_array_to_file(array, temp);
}

std::string get_stem(const fs::path& p) { return (p.stem().string()); }

void sort_arrays_from_files(char* path_s, char* path_d)
{
    std::string dest(path_d);
    for (auto& entry : fs::directory_iterator(path_s))
        {
            std::vector<long> array;
            std::string       temp = get_stem(entry.path());
            read_array_from_file(array, entry.path().string());
            std::sort(array.begin(), array.end());
            temp = dest + '/' + temp + ".txt";
            write_array_to_file(array, temp);
        }
}

void sort_arrays_from_files(std::string path_s, std::string path_d)
{
    std::string dest(path_d);
    for (auto& entry : fs::directory_iterator(path_s))
        {
            std::vector<long> array;
            std::string       temp = get_stem(entry.path());
            read_array_from_file(array, entry.path().string());
            std::sort(array.begin(), array.end());
            temp = dest + '/' + temp + ".txt";
            write_array_to_file(array, temp);
        }
}