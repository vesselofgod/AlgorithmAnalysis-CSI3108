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


void merge(vector<__int128_t>& divarr,int left,int mid,int right){
	int a = left;
	int b = mid + 1;
	int cur = left;
    int idx;
    int target;

	while (a <= mid && b <= right){
		if (divarr[a] <= divarr[b]){
			sorted[cur] = divarr[a];
			++a;
		}
		else{
			sorted[cur] = divarr[b];
			++b;
		}
		++cur;
        ++cmpcnt;
	}

    if (a > mid) idx=b;
    else idx=a;

    if(a>mid) target=right;
    else target=mid;

	for (int t = idx; t <= target; ++t){
		sorted[cur] = divarr[t];
		cur++;
	}

	for (int t = left; t <= right; ++t) divarr[t] = sorted[t];
}

//divide and combine vector list to sorting.
void mergesort(vector<__int128_t>& arr, int left, int right)
{
	if (sorted.size() == 0) sorted = vector<__int128_t>(arr.size());
	if (left < right){
        // calc mid position and divide array.
		int mid = (left + right) / 2;
		mergesort(arr, left, mid);  
		mergesort(arr, mid + 1, right);
        // combine two sorted subarrays
		merge(arr,left, mid,right);
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