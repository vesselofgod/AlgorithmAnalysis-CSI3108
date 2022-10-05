#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <time.h>

using namespace std;

__int128 cmpcnt =0;

void printint128(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) printint128(x / 10);
    putchar(x % 10 + '0');
}

string int128tostr(__int128 x){
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

__int128_t atoint128_t(std::string const & in)
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


int partition(vector<__int128> &arr, int start, int end)
{
 
    __int128 pivot = arr[start];
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (arr[i] <= pivot) {
            i++;
        }
 
        while (arr[j] > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }
 
    return pivotIndex;
}
 
void quicksort(vector<__int128> &arr, int start, int end)
{
 
    // base case
    if (start >= end)
        return;
 
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
    vector<__int128> vec;
    __int128 num;
    
    ifstream readFile;

    readFile.open("Q3_5");
    ofstream fout("test.out");
    if(readFile.is_open()){
        while (!readFile.eof()) {
            string str;
            getline(readFile, str);
            num = atoint128_t(str);
            vec.push_back(num);
        }
        readFile.close();
    }
    int n = vec.size();

	// sorting
    start = clock();
    quicksort(vec, 0, n-2);
    end = clock();
	//print(vec, n);

    for (int i = 1; i < n; i++){
        printint128(vec[i]);
        cout<<" ";
    }
    cout<<"\n";

    cout<<"runtime : "<<double(end-start)<<" millisecond"<<"\n";
    cout<<"number of comparisons : ";
    printint128(cmpcnt);
    cout<<"\n";
    fout.close();

	return 0;
}
