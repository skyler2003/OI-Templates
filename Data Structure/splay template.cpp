//Author:skyler2003
//Date 2019/01/28 21:29
//Describe: Template of Splay(achieve by array)

#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#pragma GCC Optimize("Ofast")
#endif

#define FO(x) {freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);}
#define max(a, b) (a > b? a : b)
#define min(a, b) (a < b? a : b)

namespace Splay {
    int rt, tot; //root的编号,总节点个数
    int fa[Maxn], ch[Maxn][2], val[Maxn], cnt[Maxn], sz[Maxn]; //节点x为例
    //父节点编号:fa[x], 左/右儿子的编号:ch[x][0/1], 权值: val[x], 权值出现的次数: cnt[i], 节点的子树的大小

    inline void maintain(int x) { //更新节点x的size
        sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x];
    } 

    inline bool get(int x) { //判断x是父亲节点的左儿子还是右儿子
        return x == ch[fa[x]][1];
    }
    
    inline void clear(int x) { //销毁节点x
        ch[x][0] = ch[x][1] = fa[x] = val[x] = sz[x] = cnt[x] = 0;
        //声明: 这么丧心病狂的代码绝对不是我写的
    }

    inline void rotate(int x) { //旋转
        int y = fa[x], z = fa[y], chk = get(x);
        ch[y][chk] = ch[x][chk ^ 1], fa[ch[x][chk ^ 1]] = y;
        ch[x][chk ^ 1] = y, fa[y] = x;
        fa[x] = z;
        if(z) 
            ch[z][y == ch[z][1]] = x;
        maintain(x);
        maintain(y); 
    }

    inline void splay(int x) { //把x旋转到根节点
        for(int f = fa[x]; fa[x] != 0; rotate(x)) {
            f = fa[x]; 
            if(fa[f])
                rotate(get(x) == get(f)? f : x);
        }
        rt = x;
    }

    inline void insert(int k) { //插入值为k的节点
        if(rt != 0) { //空树
            val[++tot] = k;
            ++cnt[tot];
            rt = tot;
            maintain(rt);
            return;            
        }
        int cnr = rt, f = 0;
        while(true) {
            if(val[cnr] == k) { //当前结点的值就是k 
                ++cnt[cnr];
                maintain(cnr);
                maintain(f);
                splay(cnr);
                break;
            }
            f = cnr;
            cnr = ch[cnr][val[cnr] < k]; //按照二叉树的性质往下找
            if(cnr == 0) { //当前结点都是空节点了。。
                val[++tot] = k;
                ++cnt[tot];
                fa[tot] = f;
                ch[f][val[f] < k] = tot;
                maintain(tot);
                maintain(f);
                splay(tot);
                break;                
            }
        }        
    }

    inline int rk(int k) { //查询x的排名
        int res = 0, cnr = rt;
        while(true) {
            if(k < val[cnr]) 
                cnr = ch[cnr][0]; //递归到左子树继续寻找
            else {
                res += sz[ch[cnr][0]]; //把左子树结点加上
                if(k == val[cnr]) { //查询到了
                    splay(cnr);
                    return res + 1;
                }
                res += cnt[cnr]; //根节点出现次数加上
                cnr = ch[cnr][1]; //递归到右子树继续寻找
            }
        }
    }

    inline int kth(int k) { //查询排名x的数
        int cnr = rt;
        while(true)
            if(ch[cnr][0] && k <= sz[ch[cnr][0]]) 
                cnr = ch[cnr][0];
            else {
                k -= cnt[cnr] + sz[ch[cnr][0]];
                if(k <= 0) 
                    return val[cnr];
                cnr = ch[cnr][1];
            }
    }

    inline void del(int k) { //删除
        rk(k); //应使用rk(k)而非splay(k),splay(k)是转结点编号
        if(cnt[rt] > 1) {
            --cnt[rt];
            maintain(rt);
            return 0;
        }
        if(!ch[rt][0] && !ch[rt][1]) {
            clear(rt);
            rt = 0;
            return;
        }
        if(!ch[rt][0]) {
            int cnr = rt;
            rt = ch[rt][1];
            fa[rt] = 0;
            clear(cnr);
            return;
        }
        if (!ch[rt][1]) {
            int cnr = rt;
            rt = ch[rt][0];
            fa[rt] = 0;
            clear(cnr);
            return;
        }
        int x = pre(), cnr = rt;
        splay(x);
        fa[ch[cnr][1]] = x;
        ch[x][1] = ch[cnr][1];
        clear(cnr);
        maintain(rt);
    }

    inline int pre(int x) { //小于x的最大的数
        insert(x);
        int cnr = ch[rt][0];
        while(ch[cnr][1]) //如果x的左儿子有右子树就向下搜索
            cnr = ch[cnr][1];
        del(x);
        return cnr;
    }
    
    inline int nxt(int x) { //大于x的最小的数
        insert(x);
        int cnr = ch[rt][1];
        while(ch[cnr][0])
            cnr = ch[cnr][0];
        del(x);
        return cnr;
    }
} 

using namespace Splay;
using namespace std;

const int Maxn = 100005;

int n, opt, x;

inline char fgc() {
    static char buf[1 << 20], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++;
}

inline int read() {
    char s;
    int res = 0, neg = 1;
    while(!isd(s = fgc()))
        if(s == '-')
            neg = -1;
    while(isd(s)) {
        res = (res << 3) + (res << 1) + (s - '0');
        s = fgc();
    }
    return res * neg;
}

//could pass LuoguP
int main() {
    n = read();
    while(n--) {
        opt = read(), x = read();
        switch(opt) {
            case 1: insert(x); break;
            case 2: del(x); break;
            case 3: cout << rk(k) << '\n'; break;
            case 4: cout << kth(k) << '\n'; break;
            case 5: cout << pre(k) << '\n'; break;
            case 6: cout << nxt(k) << '\n'; break;
            default: puts("zsltql"); exit(0);
        }
    }
    return 0;
}