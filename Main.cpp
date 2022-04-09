#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <ctime>

std::string readFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in)
    {
        std::cout<<"Cannot find file"<<std::endl;
        return "Cannot find file";
    }
    std::istreambuf_iterator<char> begin(in), end;
    std::string content(begin, end);
    in.close();
    return content;
}

std::vector<std::string> loadFile(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in)
    {
        std::cout << "Cannot find file" << std::endl;
        return std::vector<std::string>();
    }
    std::string s;
    std::vector<std::string> sv;
    while (std::getline(in, s))
    {
        sv.emplace_back(s);
    }
    in.close();
    return sv;
}

int string2time(std::string str)
{
    if (str.empty())
    {
        std::cout << "Empty string" << std::endl;
        return -1;
    }
    std::tm tm;
    std::time_t t;
    int y, mon, d, h, min, s;
    sscanf(str.data(), "%d-%d-%dT%d:%d:%d", &y, &mon, &d, &h, &min, &s);
    tm.tm_isdst = 0;
    tm.tm_year = y - 1900;
    tm.tm_mon = mon - 1;
    tm.tm_mday = d;
    tm.tm_hour = h;
    tm.tm_min = min;
    tm.tm_sec = s;
    t = mktime(&tm);

    return t;
}

void insertionSort(std::vector<int>& times, std::vector<std::string>& sv)
{
    int t;
    int i, j;
    std::string s;
    for (i = 1; i < times.size(); i++)
    {
        t = times[i];
        s = sv[i];
        j = i - 1;

        while (j >= 0 && times[j] > t)
        {
            times[j + 1] = times[j];
            sv[j + 1] = sv[j];
            j = j - 1;
        }
        times[j + 1] = t;
        sv[j + 1] = s;
    }
}


void merge(std::vector<int>& times, std::vector<std::string>& sv, int start, int mid, int end)
{
    int vec1Length = mid - start + 1;
    int vec2Length = end - mid;
   
    std::vector<int> vec1;
    std::vector<int> vec2;
    std::vector < std::string> data1;
    std::vector < std::string> data2;

    // Copy data to temp arrays vec1[] and vec2[]
    for (int i = 0; i < vec1Length; i++)
    {
        vec1.push_back(times[start + i]);
        data1.push_back(sv[start + i]);
    }
        
    for (int j = 0; j < vec2Length; j++)
    {
        vec2.push_back(times[mid + 1 + j]);
        data2.push_back(sv[mid + 1 + j]);
    }

    int vec1i = 0;
    int vec2i = 0; 
    int mergeVeci = start; 

    while (vec1i < vec1Length && vec2i < vec2Length) {
        if (vec1[vec1i] <= vec2[vec2i]) {
            times[mergeVeci] = vec1[vec1i];
            sv[mergeVeci] = data1[vec1i];
            vec1i++;
        }
        else {
            times[mergeVeci] = vec2[vec2i];
            sv[mergeVeci] = data2[vec2i];
            vec2i++;
        }
        mergeVeci++;
    }
    
    while (vec1i < vec1Length) {
        times[mergeVeci] = vec1[vec1i];
        sv[mergeVeci] = data1[vec1i];

        vec1i++;
        mergeVeci++;
    }
   
    while (vec2i < vec2Length) {
        times[mergeVeci] = vec2[vec2i];
        sv[mergeVeci] = data2[vec2i];
        vec2i++;
        mergeVeci++;
    }
}

void mergeSort(std::vector<int>& times, std::vector<std::string>& sv, int start, int end)
{
    if (start >= end)
        return;

    auto mid = start + (end - start) / 2;
    mergeSort(times, sv, start, mid);
    mergeSort(times, sv, mid + 1, end);
    merge(times, sv, start, mid, end);
}

void tiltMerge(std::vector<int>& times, std::vector<std::string>& sv, int start, int mid, int end)
{
    int vec1Length = mid - start + 1;
    int vec2Length = end - mid;
    
    std::vector<int> vec1;
    std::vector<int> vec2;
    std::vector < std::string> data1;
    std::vector < std::string> data2;

    // Copy data to temp arrays vec1[] and vec2[]
    for (int i = 0; i < vec1Length; i++)
    {
        vec1.push_back(times[start + i]);
        data1.push_back(sv[start + i]);
    }

    for (int j = 0; j < vec2Length; j++)
    {
        vec2.push_back(times[mid + 1 + j]);
        data2.push_back(sv[mid + 1 + j]);
    }

    int vec1i = 0;
    int vec2i = 0;
    int mergeVeci = start;

    while (vec1i < vec1Length && vec2i < vec2Length) {
        if (vec1[vec1i] <= vec2[vec2i]) {
            times[mergeVeci] = vec1[vec1i];
            sv[mergeVeci] = data1[vec1i];
            vec1i++;
        }
        else {
            times[mergeVeci] = vec2[vec2i];
            sv[mergeVeci] = data2[vec2i];
            vec2i++;
        }
        mergeVeci++;
    }

    while (vec1i < vec1Length) {
        times[mergeVeci] = vec1[vec1i];
        sv[mergeVeci] = data1[vec1i];

        vec1i++;
        mergeVeci++;
    }

    while (vec2i < vec2Length) {
        times[mergeVeci] = vec2[vec2i];
        sv[mergeVeci] = data2[vec2i];
        vec2i++;
        mergeVeci++;
    }
}

void tileMergeSort(std::vector<int>& times, std::vector<std::string>& sv, int start, int end, int minSize)
{
    if (end - start + 1 <= minSize)
    {
        insertionSort(times, sv);
        return;
    }

    auto mid = start + (end - start) / 2;
    tileMergeSort(times, sv, start, mid, minSize);
    tileMergeSort(times, sv, mid + 1, end, minSize);
    tiltMerge(times, sv, start, mid, end);
}

bool isSorted(std::vector<int>& times)
{
    for (int i = 0; i < times.size() - 1; i++)
    {
        if (times[i] > times[i + 1]) return false;
    }
    return true;
}

int main()
{
    std::vector<std::string> sv = loadFile("./data/Project1/A/2048.log");
    std::vector<int> times;
    for (auto time : sv)
    {
        int t = string2time(time);
        times.emplace_back(t);
    }
    clock_t t1 = clock();
    //insertionSort(times, sv);
    //mergeSort(times, sv, 0, times.size() - 1);
    tileMergeSort(times, sv, 0, times.size() - 1, 4);
    clock_t t2 = clock();
    double timeUsage = (t2 - t1) * 1.0 / CLOCKS_PER_SEC;

    /*for (auto s : sv)
    {
        std::cout << s << std::endl;
    }*/
    if (isSorted(times)) std::cout << "Data is sorted" << std::endl;
    else std::cout << "Data is not sorted" << std::endl;
   
    std::cout << "Elapsed time: " << timeUsage <<"sec"<< std::endl;

	return 0;
}