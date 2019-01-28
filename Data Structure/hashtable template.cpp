//Author:skyler2003
//Descripe: Template of string hash
//Time: 2019/01/09 22:04

//hasn't test

#include <bits/stdc++.h>

using namespace std;

const int Maxn = ;//data size
const double alpha = 0.75;//alpha = n/maxl
const int Maxl = Maxn / alpha; //hash table size
const int seed = 107; // hashseed
const int mo = 19260817; //prime mod

string hasht[Maxl]; // hashtable
bool ffull; //whether the hash table is full

inline int hash(string a) {
    int hashval = 0;
    for(int i = 0; i < a.size(); ++i) 
        hashval = (hashval * seed + str[i]) % mo;
    return hashval % Maxl;
}

inline bool find(string a) {
    int pos = hash(a);
    while(hasht[pos] != a) {
        if(hasht == "")
            return false;
        ++pos;
        if(pos == Maxl)
            return false;
    }
    return true;
}

inline void insert(string a) {
    int pos = hash(a), tmp = pos;
    while(hasht[pos] != "") {
        if(hasht[pos] == a)
            return;
        ++pos;
        if(pos == tmp) {
            ffull = true;
            return;
        }
        if(pos == Maxl)
            pos = 0;
    }
    hasht[pos] = a;
}

int main() {

}