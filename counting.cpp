#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <time.h>
#include <fstream>
#define RANGE 1000

using namespace std;



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

  
void countSort(vector<__int128>& arr)
{
    __int128 max = *max_element(arr.begin(), arr.end());
    __int128 min = *min_element(arr.begin(), arr.end());
    __int128 range = max - min + 1;
  
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
    vector<__int128> vec;
    __int128 num;
    
    ifstream readFile;

    readFile.open("Q3_1");
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
    countSort(vec);
    end = clock();
	//print(vec, n);



    for (int i = 1; i < n; i++){
        printint128(vec[i]);
        cout<<" ";
    }
    cout<<"\n";

    cout<<"runtime : "<<double(end-start)<<" millisecond"<<"\n";
    fout.close();

	return 0;
}