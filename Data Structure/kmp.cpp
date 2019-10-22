//Author:skyler2003
//Description: KMP's Template (can pass Luogu P3375)
//Time: 16:21 2019/10/22

#include <bits/stdc++.h>

using namespace std;

const int Maxn = 1000005;

int n, m;
string s1, s2;
int nxt[Maxn], f[Maxn];

int main() {
    cin >> s2 >> s1;
    n = s1.size(), m = s2.size();
    nxt[1] = 0;     
    for(int i = 2, j = 0; i <= n; ++i) {
        while(j > 0 && s1[i - 1] != s1[j])
            j = nxt[j];
        if(s1[i - 1] == s1[j])    
            ++j;
        nxt[i] = j;
    }
    for(int i = 1, j = 0; i <= m; ++i) {
        while(j > 0 && (j == n || s2[i - 1] != s1[j]))
            j = nxt[j];
        if(s2[i - 1] == s1[j])
            ++j;
        f[i] = j;
        if(f[i] == n) 
            cout << i - n + 1 << endl;
    }
    for(int i = 1; i <= n; ++i)
        cout << nxt[i] << ' ';
    return 0;
}
