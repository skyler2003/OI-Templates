#include <bits/stdc++.h>

#define max(a, b) (a > b? a : b)
#define min(a, b) (a < b? a : b)

using namespace std;

const int Maxn = 1e5 + 1;
const int Maxk = log(Maxn) / log(2) + 1;
int n, m, a[Maxn], k[Maxn], f[Maxn][Maxk];

inline char fgc() {
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline int readint() {
    int res = 0, neg = 1;
    char c = fgc();
    while(!isdigit(c)) {
        if(c == '-') 
            neg = -1;
        c = fgc();
    }
    while(isdigit(c)) {
        res = res * 10 + c - '0';
        c = fgc();
    }
    return res * neg;
}

inline void StTableInit() {
    for(int i = 1; i <= n; ++i)
        f[i][0] = a[i];
    int t = log(n) / log(2) + 1;
    for(int j = 1; j < t; ++j) 
        for(int i = 1; i <= n - (1 << j) + 1; ++i)
            f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    for(int i = 1; i <= n; ++i) 
        k[i] = log(i) / log(2);
}

inline int StTableQuery(int l, int r) {
    return min(f[l][k[r - l + 1]], f[r - (1 << k[r - l + 1]) + 1][k[r - l + 1]]);
}

int main() {
    n = readint(), m = readint();
    for(int i = 1; i <= n; ++i)
        a[i] = readint();
    StTableInit();
    for(int i = 1, l, r; i <= m; ++i) {
        l = readint(), r = readint();
        printf("%d ", StTableQuery(l, r));
    }
    return 0;
}

//经典RMQ问题(区间最小值)
//可通过LuoguP1816忠诚