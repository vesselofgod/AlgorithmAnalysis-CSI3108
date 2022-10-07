#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <time.h>

using namespace std;

__int128_t cmpcnt =0;

void printint128(__int128_t x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) printint128(x / 10);
    putchar(x % 10 + '0');
}

__int128_t strtoint128(std::string const & in)
{
    __int128_t res = 0;
    size_t i = 0;
    bool sign = false;

    if (in[i] == '-'){
        ++i;
        sign = true;
    }

    if (in[i] == '+'){
        ++i;
    }

    for (; i < in.size(); ++i){
        const char c = in[i];
        if (not std::isdigit(c)) 
            throw std::runtime_error(std::string("Non-numeric character: ") + c);
        res *= 10;
        res += c - '0';
    }
    if (sign){
        res *= -1;
    }
    return res;
}


string int128tostr(__int128_t x){
    string result = "";
    if (x < 0) {
        result = "-"+result;
    }
    if (x > 9){
        int s = x % 10;
        result = result+to_string(s);
        printint128(x / 10);
    }
    return result;
}

void printVector(vector<__int128_t>& arr){
    for (int i = 0; i < arr.size(); i++){
        printint128(arr[i]);
        cout<<"\n";
    }
}

vector<__int128_t> initVector(string filePath){
    ifstream readFile;

    vector<__int128_t> vec;
    __int128_t num;

    readFile.open(filePath);
    if(readFile.is_open()){
        while (!readFile.eof()) {
            string str;
            getline(readFile, str);
            num = strtoint128(str);
            vec.push_back(num);
        }
        readFile.close();
    }
    vec.pop_back();
    return vec;
}


int partition(vector<__int128_t> &arr, int start, int end)
{
    __int128_t pivot = arr[start];
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
            cmpcnt++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
        while (arr[i] <= pivot) {
            i++;
            cmpcnt++;
        }
        while (arr[j] > pivot) {
            j--;
            cmpcnt++;
        }
        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }
    return pivotIndex;
}
 
void quicksort(vector<__int128_t> &arr, int start, int end)
{
 
    // base case
    if (start >= end) return;
 
    // partitioning the array
    int p = partition(arr, start, end);
 
    // Sorting the left part
    quicksort(arr, start, p - 1);
 
    // Sorting the right part
    quicksort(arr, p + 1, end);
}

int main()
{
    clock_t start,end;

    vector<__int128_t> q1 = initVector("Q3_1");
    vector<__int128_t> q2 = initVector("Q3_2");
    vector<__int128_t> q3 = initVector("Q3_3");
    vector<__int128_t> q4 = initVector("Q3_4");
    vector<__int128_t> q5 = initVector("Q3_5");

	// sorting
    start = clock();
    quicksort(q1,0,q1.size()-1);
    end = clock();
    cout<<"Q3_1's runtime : "<<double(end-start)<<" microsecond"<<"\n";
    cout<<"Q3_1's number of comparisons : ";
    printint128(cmpcnt);
    cout<<"\n";
    cmpcnt = 0;

    start = clock();
    quicksort(q2,0,q2.size()-1);
    end = clock();
    cout<<"Q3_2's runtime : "<<double(end-start)<<" microsecond"<<"\n";
    cout<<"Q3_2's number of comparisons : ";
    printint128(cmpcnt);
    cout<<"\n";
    cmpcnt = 0;

    start = clock();
    quicksort(q3,0,q3.size()-1);
    end = clock();
    cout<<"Q3_3's runtime : "<<double(end-start)<<" microsecond"<<"\n";
    cout<<"Q3_3's number of comparisons : ";
    printint128(cmpcnt);
    cout<<"\n";
    cmpcnt = 0;

    start = clock();
    quicksort(q4,0,q4.size()-1);
    end = clock();
    cout<<"Q3_4's runtime : "<<double(end-start)<<" microsecond"<<"\n";
    cout<<"Q3_4's number of comparisons : ";
    printint128(cmpcnt);
    cout<<"\n";
    cmpcnt = 0;

    start = clock();
    quicksort(q5,0,q5.size()-1);
    end = clock();
    cout<<"Q3_5's runtime : "<<double(end-start)<<" microsecond"<<"\n";
    cout<<"Q3_5's number of comparisons : ";
    printint128(cmpcnt);
    cout<<"\n";

    //print sorted vector
    //printVector(q3);

	return 0;
}