#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <time.h>
#include <fstream>
#define RANGE 1000

using namespace std;

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



void countSort(vector<__int128_t>& arr)
{
    __int128_t max = *max_element(arr.begin(), arr.end());
    __int128_t min = *min_element(arr.begin(), arr.end());
    __int128_t range = max - min + 1;
  
    vector<int> count(range), output(arr.size());
    for (int i = 0; i < arr.size(); i++)
        count[arr[i] - min]++;
  
    for (int i = 1; i < count.size(); i++)
        count[i] += count[i - 1];
  
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }
  
    for (int i = 0; i < arr.size(); i++)
        arr[i] = output[i];
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
    countSort(q1);
    end = clock();
    cout<<"Q3_1's runtime : "<<double(end-start)<<" microsecond"<<"\n";

    start = clock();
    countSort(q2);
    end = clock();
    cout<<"Q3_2's runtime : "<<double(end-start)<<" microsecond"<<"\n";

    //############## ERROR OCCUR. ##############
    //terminate called after throwing an instance of 'std::bad_alloc'
    //what():  std::bad_alloc
    //Aborted (core dumped)

    start = clock();
    countSort(q3);
    end = clock();
    cout<<"Q3_3's runtime : "<<double(end-start)<<" microsecond"<<"\n";

    start = clock();
    countSort(q4);
    end = clock();
    cout<<"Q3_4's runtime : "<<double(end-start)<<" microsecond"<<"\n";

    start = clock();
    countSort(q5);
    end = clock();
    cout<<"Q3_5's runtime : "<<double(end-start)<<" microsecond"<<"\n";

    //print sorted vector
    //printVector(q1);

	return 0;
}