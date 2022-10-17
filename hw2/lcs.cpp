#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <fstream>
#define MAX 70000

using namespace std;

int dp1[MAX]= {};
int dp2[MAX]= {};
string lcsString[3]={"","",""};

void initString(string filePath){
    for(int i = 0 ; i<MAX;i++){
        dp1[i]=0;
        dp2[i]=0;
    }
    ifstream readFile;
    readFile.open(filePath);
    int idx = 0;
    if(readFile.is_open()){
        while (!readFile.eof()) {
            getline(readFile, lcsString[idx]);
            idx++;
        }
        readFile.close();
    }
    return;
}

void lcs(){
    int lena = lcsString[0].length();//can replace MAX? yes.
    int lenb = lcsString[1].length();
    for(int y = 0; y <= lenb; y++)
        dp1[y] = 0; // assume x == strlenA
    for(int x = lena - 1; x >= 0; x--){
        // x has been decreased
        memcpy(dp2, dp1, sizeof(dp1)); // dp[x + 1] <- dp[x]
        dp1[lenb] = 0;
        for(int y = lenb - 1; y >= 0 ; y--)
            dp1[y] = (lcsString[0][x]==lcsString[1][y]) ? 1 + dp2[y+1] :
                    max(dp2[y], dp1[y+1]);
    }
    return; // assume x == 0
}


int main()
{
    initString("./Q1");
    lcs();
    cout<<"longest common sequence's length : "<<*max_element(dp1, dp1+MAX)<<endl;
}