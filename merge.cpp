#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <time.h>

using namespace std;
__int128 cmpcnt = 0;

vector<__int128> sorted;

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


void merge(vector<__int128>& divarr,int start,int mid,int end){
	int i = start;
	int j = mid + 1;
	int k = start;
	//분할 정렬된 리스트 합병
	while (i <= mid && j <= end){
		if (divarr[i] <= divarr[j]){
			sorted[k] = divarr[i];
			i++;
		}
		else{
			sorted[k] = divarr[j];
			j++;
		}
		k++;
        cmpcnt++;
	}

    int entry;
    int target;

    if (i > mid)
        entry=j;
    else
        entry=i;

    if(i>mid)
        target=end;
    else
        target=mid;

	//남아 있는 값들 복사 
	for (int t = entry; t <= target; ++t){
		sorted[k] = divarr[t];
		k++;
	}

	//정렬된 임시 리스트를  원래 리스트에 복사 
	for (int t = start; t <= end; ++t){
		divarr[t] = sorted[t];
	}
}

void mergesort(vector<__int128>& arr, int start, int end)
{
	if (sorted.size() == 0) sorted = vector<__int128>(arr.size());
	if (start < end){
        // calc mid position and divide array.
		int mid = (start + end) / 2;
		mergesort(arr, start, mid);  
		mergesort(arr, mid + 1, end);
        // combine two sorted subarrays
		merge(arr,start, mid,end);
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
    int n = vec.size()-1;

	// sorting
    start = clock();
    mergesort(vec, 0,n-1);
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