#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <time.h>

using namespace std;

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

// counting sort using subroutine for radix sort
void countsort(vector<__int128_t> &arr, __int128_t eval ,int r)
{
    vector<int> count(r, 0);
    vector<__int128_t> result(arr.size()); 

	for (int i = 0; i < arr.size(); i++){
        count[(arr[i]/eval)%r]+=1;
    }
	for (int i = 1; i < r; i++){
        count[i]+=count[i-1];
    }
	for (int i = arr.size() - 1; i >= 0; i--) {
		result[count[(arr[i]/eval)%r]-1]=arr[i];
		count[(arr[i]/eval)%r]-=1;
	}
	for (int i = 0; i < result.size(); i++){
        arr[i]=result[i];
    }
}

// radixsort using counting sort as subroutine and basic r = 10, but you can change it
void radixsort(vector<__int128_t> &arr, int r = 10)
{
    __int128_t key = 1 << r;
	__int128_t maxval =arr[0];

	for (int i = 1; i < arr.size(); i++){
		if (arr[i]>maxval)
			maxval=arr[i];
    }
    //using key value for R by bit calculation
	for (__int128_t eval = 1; maxval / eval > 0; eval <<= r){
		countsort(arr, eval, key);
    }
}

void Rvalue(vector<__int128_t>& arr, vector<int>& r){
    clock_t s,e;

    for(int i=0;i<r.size();i++){
        s = clock();
        radixsort(arr,r[i]);
        e = clock();
        cout<<"r = "<<r[i]<<", runtime : "<<double(e-s)<<" microsecond"<<"\n";
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
    radixsort(q1);
    end = clock();
    cout<<"Q3_1's runtime : "<<double(end-start)<<" microsecond"<<"\n";
    cout<<"Q3_1's number of comparisons : ";
    printint128(cmpcnt);
    cout<<"\n";
    cmpcnt = 0;

    start = clock();
    radixsort(q2);
    end = clock();
    cout<<"Q3_2's runtime : "<<double(end-start)<<" microsecond"<<"\n";
    cout<<"Q3_2's number of comparisons : ";
    printint128(cmpcnt);
    cout<<"\n";
    cmpcnt = 0;

    start = clock();
    radixsort(q3);
    end = clock();
    cout<<"Q3_3's runtime : "<<double(end-start)<<" microsecond"<<"\n";
    cout<<"Q3_3's number of comparisons : ";
    printint128(cmpcnt);
    cout<<"\n";
    cmpcnt = 0;
    

    start = clock();
    radixsort(q4);
    end = clock();
    cout<<"Q3_4's runtime : "<<double(end-start)<<" microsecond"<<"\n";
    cout<<"Q3_4's number of comparisons : ";
    printint128(cmpcnt);
    cout<<"\n";
    cmpcnt = 0;

    start = clock();
    radixsort(q5);
    end = clock();
    cout<<"Q3_5's runtime : "<<double(end-start)<<" microsecond"<<"\n";
    cout<<"Q3_5's number of comparisons : ";
    printint128(cmpcnt);
    cout<<"\n";

    //########### R value ############
    vector<int> rvalues{1,3,5,10,15,18,20,22,25,27};
    cout<<"Q3_1's runtimes according6 to r value "<<endl;
    Rvalue(q1,rvalues);
    cout<<"Q3_2's runtimes according to r value "<<endl;
    Rvalue(q2,rvalues);
    cout<<"Q3_3's runtimes according to r value "<<endl;
    Rvalue(q3,rvalues);
    cout<<"Q3_4's runtimes according to r value "<<endl;
    Rvalue(q4,rvalues);
    cout<<"Q3_5's runtimes according to r value "<<endl;
    Rvalue(q5,rvalues);
    
    //print sorted vector
    //printVector(q3);


	return 0;
}



/*
for (int i = 0; i < n; i++){
    string sint = int128tostr(vec[i]);
    char *ch = (char *)sint.c_str();
    for (int j=0; j < strlen(ch);j++){
        cout<<ch[j];
    }
    cout<<endl;
}
fout.close();
*/