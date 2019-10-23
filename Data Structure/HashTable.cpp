//Author:skyler2003
//Description: Hash Table Template(can pass Luogu p3370)
//Time: 01:28 2019/10/24

#include <bits/stdc++.h>

using namespace std;

const int base = 13331;
const int sed = 19260817;
const int mo = 1e9 + 7;

int n;
string str;
set<int> s;

inline int hash1(string str) {
    int len = str.size();
    long long ans = 0;
    for(int i = 0; i < len; ++i)
        ans = (ans * base + str[i]) % mo + sed;
    return ans % mo;
}

int main() {
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> str;
        s.insert(hash1(str));
    }
    cout << s.size() << endl;
}