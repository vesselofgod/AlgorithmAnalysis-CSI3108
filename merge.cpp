#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <time.h>

using namespace std;

vector<__int128_t> sorted;
__int128_t cmpcnt = 0;

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
    vec.pop_back(); //remove zero value due to EOF
    return vec;
}


void merge(vector<__int128_t>& divarr,int start,int mid,int end){
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

void mergesort(vector<__int128_t>& arr, int start, int end)
{
	if (sorted.size() == 0) sorted = vector<__int128_t>(arr.size());
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

    vector<__int128_t> q1 = initVector("Q3_1");
    vector<__int128_t> q2 = initVector("Q3_2");
    vector<__int128_t> q3 = initVector("Q3_3");
    vector<__int128_t> q4 = initVector("Q3_4");
    vector<__int128_t> q5 = initVector("Q3_5");

	// sorting
    start = clock();
    mergesort(q1,0,q1.size()-1);
    end = clock();
    cout<<"Q3_1's runtime : "<<double(end-start)<<" microsecond"<<"\n";
    cout<<"Q3_1's number of comparisons : ";
    printint128(cmpcnt);
    cout<<"\n";
    cmpcnt = 0;

    start = clock();
    mergesort(q2,0,q2.size()-1);
    end = clock();
    cout<<"Q3_2's runtime : "<<double(end-start)<<" microsecond"<<"\n";
    cout<<"Q3_2's number of comparisons : ";
    printint128(cmpcnt);
    cout<<"\n";
    cmpcnt = 0;

    start = clock();
    mergesort(q3,0,q3.size()-1);
    end = clock();
    cout<<"Q3_3's runtime : "<<double(end-start)<<" microsecond"<<"\n";
    cout<<"Q3_3's number of comparisons : ";
    printint128(cmpcnt);
    cout<<"\n";
    cmpcnt = 0;

    start = clock();
    mergesort(q4,0,q4.size()-1);
    end = clock();
    cout<<"Q3_4's runtime : "<<double(end-start)<<" microsecond"<<"\n";
    cout<<"Q3_4's number of comparisons : ";
    printint128(cmpcnt);
    cout<<"\n";
    cmpcnt = 0;

    start = clock();
    mergesort(q5,0,q5.size()-1);
    end = clock();
    cout<<"Q3_5's runtime : "<<double(end-start)<<" microsecond"<<"\n";
    cout<<"Q3_5's number of comparisons : ";
    printint128(cmpcnt);
    cout<<"\n";

    //print sorted vector
    //printVector(q4);

	return 0;
}