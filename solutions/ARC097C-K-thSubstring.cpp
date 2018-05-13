#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
using namespace std;
// type alias
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 5/12/2018 AtCoder Beginner Contest 097
 
 21:00-21:18 200/300 ACC. However I couldn't solve |S|<=5000 constraint
 
 5/13/2018
 
 16:30-17:43 read editorials and add solution
 
 Editorials:
  - https://img.atcoder.jp/arc097/editorial.pdf
 
 Tweets:
  - togetter
   - https://togetter.com/li/1226806
  - solution
   - https://twitter.com/tempura_pp/status/995297625338343424
   - https://twitter.com/togatoga_/status/995297772872990720
   - https://twitter.com/rickytheta/status/995297864891883520
   - https://twitter.com/torus711/status/995298291821654016
   - https://twitter.com/blue_jam/status/995298507715047431
   - https://twitter.com/_TTJR_/status/995300529952600065
  - proof
   - https://twitter.com/merom686/status/995299829940015104
   - https://twitter.com/tanakh/status/995302093618466816
 
 Lemma: Length of K-th substring is at most `K`
 
 Suppose K=5. Look at string "aaaaa".
 This string has 5 unique substring because prefix or suffix is distinct in terms of its length.
 
 S5="aaaaa"
 S4="aaaa"
 S3="aaa"
 S2="aa"
 S1="a"
 
 From this lemma, we can iterate all the substrings of K-length substrings.
 The result is K-th of them.

 Summary:
  - I thought that we wouldn't use 5000 length substring though, enumerating K length substrings did not come up with me
  - Looks like I'm not good at deep analysis of problem constraint. The given constraint may not upper-bound search space
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 21:18 200/300
int K;
string S;
string res="";
class TrieNode {
public:
  bool hasWord = false;
  vector<TrieNode *> children;
  // Initialize your data structure here.
  TrieNode() {
    this->children = vector < TrieNode * > (26, NULL);
  }
};

class Trie {
public:
  Trie() {
    root = new TrieNode();
  }
  
  // Inserts a word into the trie.
  void insert(string word) {
    TrieNode *n = root;
    for(int i=0; i<word.size(); i++) {
      int w = word[i]-'a';
      TrieNode *next = n->children[w];
      if (next==NULL) {
        next = new TrieNode();
        n->children[w] = next;
      }
      next->hasWord=true;
      n = next;
    }
    n->hasWord = true;
  }
  
  void dfs() {
    string x="";
    f(root, x);
  }
  
  void f(TrieNode *n, string &cur) {
    if(n==nullptr) return;
    if(n->hasWord) {
      --K;
      if(K==0) {
        res=cur;
        return;
      }
    }
    REP(i,26) {
      cur.push_back('a'+i);
      f(n->children[i], cur);
      cur.pop_back();
    }
  }
  
  void release() {
    releaseNode(root);
  }
private:
  TrieNode* root;
  void releaseNode(TrieNode* n) {
    if (!n) return;
    for(auto &c : n->children) releaseNode(c);
    delete n;
  }
};

string solve_small() {
  Trie T=Trie();
  int N=SZ(S);
  REP(i,N) T.insert(S.substr(i));
  
  T.dfs();
  
  T.release();
  
  assert(!res.empty());
  
  return res;
}

/*
string solve() {
  set<string> viz;
  queue<pair<string,int>> Q;
  int N=SZ(S);
  REP(ci,26) {
    char c='a'+ci;
    string x=to_string(c);
    REP(i,N) if(S[i]==c) {
      Q.emplace(x,i+1);
      viz.emplace(x);
    }
    while(SZ(Q)) {
      int M=SZ(Q);
      while(M--) {
        auto p=Q.front(); Q.pop();
        string s=p.first;
        int i=p.second;
        if(i<N) {
          s+=S[i];
          viz.emplace(s);
          Q.emplace(s,i+1);
        }
      }
      if(SZ(viz)>=K) {
        vector<string> y(viz.begin(),viz.end());
        return y[K];
      }
    }
  }
  return "";
}*/

string solve() {
  int N=SZ(S);
//  dump2(S,N-K);
  set<string> X;
  REP(i,N) {
//    dump(i);
    string s=S.substr(i,min(K,N-i));
//    dump2(i,s);
    int M=SZ(s);
    REP(l,M) FORE(r,l+1,M) {
      string t=s.substr(l,r-l);
//      dump(t);
      if(!t.empty()) X.emplace(t);
    }
  }
  vector<string> Y(X.begin(),X.end());
//  dumpAR(Y);
  return Y[K-1];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>S>>K;
  cout<<solve()<<endl;
  return 0;
}
