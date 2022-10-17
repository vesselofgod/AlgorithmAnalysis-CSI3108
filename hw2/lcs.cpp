#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <fstream>
#define MAX 70000

using namespace std;

int dp[2][MAX+1];
string lcsString[3]={"","",""};

void initString(string filePath){
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

int lcs(){
    int cur;
    for (int i = 0; i <= MAX; i++){
        cur = i % 2;
        for (int j = 0; j <= MAX; j++){
            if (i == 0 || j == 0) dp[cur][j] = 0;
            else if (lcsString[0][i-1] == lcsString[1][j-1]) dp[cur][j] = dp[1 - cur][j - 1] + 1;
            else dp[cur][j] = max(dp[1 - cur][j], dp[cur][j - 1]);
        }
    }
    return dp[cur][MAX];
}


int main()
{
    initString("./Q1");
    cout<<"longest common sequence's length : "<<lcs()<<endl;
}