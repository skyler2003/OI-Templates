//Author:skyler2003
#include <bits/stdc++.h>

using namespace std;

#define max(a,b) (a>b? a:b)
#define min(a,b) (a<b? a:b)
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}

#pragma GCC Optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma comment (linker,"/stack:200000000")

bool Finish_read;

template<class T>inline void read(T &x){Finish_read=0;x=0;T f=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;if(ch==EOF)return;ch=getchar();}while(isdigit(ch))x=x*10+ch-'0',ch=getchar();x*=f;Finish_read=1;}
template<class T>inline void print(T x){if(x/10!=0)print(x/10);putchar(x%10+'0');}
template<class T>inline void writeln(T x){if(x<0)putchar('-');x=abs(x);print(x);putchar('\n');}
template<class T>inline void write(T x){if(x<0)putchar('-');x=abs(x);print(x);}

typedef long long LL;
//Template

const int MAXN = 100005, INF = 1e9;

//Segment Tree
#define lch o << 1
#define rch (o << 1) | 1
#define mid ((l + r) >> 1)

LL w[MAXN], val[MAXN << 2], tag[MAXN << 2];

//Merge the children's info into root
inline void merge(int o) {
	val[o] = val[lch] + val[rch];
}

//Push the tags down
inline void pushdown(int o, int l, int r) {
	if(tag[o]) {
		tag[lch] += tag[o];
		tag[rch] += tag[o];
		val[lch] += tag[o] * (mid - l + 1);
		val[rch] += tag[o] * (r - mid);
		tag[o] = 0;
	}
}

//Build the tree
inline void build(int o, int l, int r) {
	if(l == r) {
		val[o] = w[l];
		return;
	}
	build(lch, l, mid);
	build(rch, mid + 1, r);
	merge(o);
}

//Add v to elements in [l,r]
inline void add(int o, int l, int r, int ll, int rr, LL v) {
	if(l >= ll && r <= rr) {
		tag[o] += v;
		val[o] += v * (r - l + 1);
		return;
	}
	pushdown(o, l, r);
	if(ll <= mid)
		add(lch, l, mid, ll, rr, v);
	if(rr > mid)
		add(rch, mid + 1, r, ll, rr, v);
	merge(o);
}

//Query the sum of elementsin [l.r]
inline LL query(int o, int l, int r, int ll, int rr) {
	if(l >= ll && r <= rr)
		return val[o];
	pushdown(o, l, r);
	LL res = 0;
	if(ll <= mid)
		res += query(lch, l, mid, ll, rr);
	if(rr > mid)
		res += query(rch, mid + 1, r, ll, rr);
	return res;
}

int n, m, op, x, y;
LL k;

int main() {
	read(n) , read(m);
	for(size_t i = 1; i <= n; ++i)
		read(w[i]);
	build(1, 1, n);
	while(m--) {
		read(op) , read(x) , read(y);
		if(op == 1) {
			read(k);
			add(1, 1, n, x, y, k);
		}
		else
			writeln(query(1, 1, n, x, y));
	}
	return 0;
}
