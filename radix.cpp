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



// A utility function to get maximum value in arr[]
__int128 getMax(vector<__int128> &arr, int n)
{
	__int128 mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(vector<__int128> &arr, int n, __int128 exp)
{
	vector<__int128> output(n); // output array
	int i, count[10] = { 0 };

	// Store count of occurrences in count[]
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	// Change count[i] so that count[i] now contains actual
	// position of this digit in output[]
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Build the output array
	for (i = n - 1; i >= 0; i--) {
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	// Copy the output array to arr[], so that arr[] now
	// contains sorted numbers according to current digit
	for (i = 0; i < n; i++)
		arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using
// Radix Sort
void radixsort(vector<__int128> &arr, int n)
{
	// Find the maximum number to know number of digits
	__int128 m = getMax(arr, n);

	// Do counting sort for every digit. Note that instead
	// of passing digit number, exp is passed. exp is 10^i
	// where i is current digit number
	for (__int128 exp = 1; m / exp > 0; exp *= 10)//exp =r
		countSort(arr, n, exp);
}
/*
// A utility function to print an array
void print(vector<__int128> &arr, int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
}
*/

// Driver Code
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
    __int128 lastnum = vec.back();
    vec.pop_back();
    int n = vec.size();

	// sorting
    start = clock();
    radixsort(vec, n);
    end = clock();
	//print(vec, n);

    for (int i = 1; i < n; i++){
        printint128(vec[i]);
        cout<<"\n";
    }
    cout<<"\n";

    cout<<"runtime : "<<double(end-start)<<" millisecond"<<"\n";
    cout<<"number of comparisons : ";
    printint128(cmpcnt);
    cout<<"\n";
    printint128(lastnum);
    cout<<n<<endl;
    fout.close();

	return 0;


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
	return 0;
}
