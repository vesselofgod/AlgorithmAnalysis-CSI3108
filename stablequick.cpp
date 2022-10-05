#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <time.h>

using namespace std;
__int128 cmpcnt = 0;

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
/*
void quick(vector<__int128>& arr, int low, int high){
}
*/
vector<__int128> quickSort(vector<__int128>& arr)
{
    // Base case
    if(arr.size() <= 1){
        return arr;//arr
    }
    else{

    // Let us choose middle element a pivot           
    int mid = arr.size() / 2;
    __int128 pivat = arr[mid];
        
    // key element is used to break the array
    // into 2 halves according to their values
    vector<__int128> smaller ;
    vector<__int128> greater ;
        
    // Put greater elements in greater list,
    // smaller elements in smaller list. Also,
    // compare positions to decide where to put.       
    for(int ind = 0; ind < arr.size(); ind++){
        __int128 val = arr[ind];
        if( ind != mid ){
            if( val < pivat ) smaller.push_back(val);
            else if(val > pivat) greater.push_back(val);
            else{
                // If value is same, then considering
                // position to decide the list.               
                if(ind < mid) smaller.push_back(val);
                else greater.push_back(val);
            }
            cmpcnt++;
        }
    }

        vector<__int128> ans;           
        vector<__int128> sa1 = quickSort(smaller);
        vector<__int128> sa2 = quickSort(greater);
            
        // add all elements of smaller list into ans list
        for(__int128 val1 : sa1)
            ans.push_back(val1);
                
        // add pivat element into ans list
        ans.push_back(pivat);
        
        // add all elements of greater list into ans list
        for(__int128 val2 : sa2)
            ans.push_back(val2);
        // return ans list
        return ans;
    }
}

int main()
{
    clock_t start,end;
    vector<__int128> vec;
    __int128 num;
    
    ifstream readFile;

    readFile.open("Q3_4");
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
    vector<__int128> v = quickSort(vec);
    end = clock();
	//print(vec, n);

    for (int i = 1; i < n; i++){
        printint128(v[i]);
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