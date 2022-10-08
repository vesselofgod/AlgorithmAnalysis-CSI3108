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

__int128_t strtoint128(string & sInt)
{
    size_t i = 0;
    __int128_t result = 0;
    bool flag = false;

    if (sInt[i] == '-'){
        flag = true;
        ++i;
    }

    if (sInt[i] == '+'){
        ++i;
    }

    for (; i < sInt.size(); ++i){
        const char c = sInt[i];
        result *= 10;
        result += c - '0';
    }
    if (flag){
        result *= -1;
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


void quicksort(vector<__int128_t> &arr, int s, int e)
{
    if (s >= e) return; //base case in quick

    __int128_t pivot = arr[s];
 
    int count = 0;

    for (int i = s + 1; i <= e; i++) {
        if (arr[i] <= pivot)
            count++;
            cmpcnt++;
    }
 
    int pivotidx = s + count;
    swap(arr[pivotidx], arr[s]);
 
    int i = s, j = e;
 
    while (i < pivotidx && j > pivotidx) {
        while (arr[i] <= pivot){
            i++;
            cmpcnt++;
        }
        while (arr[j] > pivot) {
            j--;
            cmpcnt++;
        }
        if (i < pivotidx && j > pivotidx) {
            swap(arr[i++], arr[j--]);
        }
    }
 
    quicksort(arr, s, pivotidx - 1);
    quicksort(arr, pivotidx + 1, e);
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