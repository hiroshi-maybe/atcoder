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
 
 8/24/2018
 
 16:55-17:30 give up
 
 There is optimality for min distance at (i,j).
 Suppose arriving at (i,j) in min time t0.
 There is wait time for either direction {U,D,R,L}.
 Even if arriving at (i,j) in time t1 (>t0), waiting from time t0 is always optimal.
 
 I didn't analyze optimality deeply, or intuitively I thought optimality is broken by wait time constraint.
 Thus my mind was locked by adding another state to (i,j). Sigh...
 
 24:30-25:06 add solution
 
 Editorials:
  - https://img.atcoder.jp/mujin-pc-2018/editorial.pdf
  - https://youtu.be/2ZfEcgV8Sso?t=3113
  - https://kimiyuki.net/writeup/algo/atcoder/mujin-pc-2018-e/
  - http://hamko.hatenadiary.jp/entry/2018/08/05/011711
  - https://www.hamayanhamayan.com/entry/2018/08/05/101350
  - http://betrue12.hateblo.jp/entry/2018/08/05/032043
  - http://kazune-lab.net/contest/2018/08/04/mujin-pc-2018/
   - mentioning to optimality
  - https://yang33-kassa.jp/atcoder/mujin2018/
  - https://31536000.hatenablog.com/entry/2018/08/05/002002
 
 Summary:
  - I had an idea to make 4*K transition table. However I was in stuck because I didn't doubted optimality without analysis
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e3+1;
const int MAX_K=1e5+1;
int N,M,K;
string DD;
string G[MAX_N];
LL nex[MAX_K][4];
vector< pair < int, int > >  moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };

unordered_map<char,int> revmv={
  {'R',0},{'D',1},{'L',2},{'U',3}
};

const long long Inf=1e17;
const int MAX_V=1e6+1;
long long D[MAX_V];
void dijkstra(int V, int st) {
  for(int i=0; i<V; ++i) D[i]=Inf;
  set<pair<long long,int>> Q; Q.emplace(0,st); D[st]=0;
  while(Q.size()>0) {
    auto it=Q.begin(); Q.erase(it);
    int u; long long d;
    tie(d,u)=*it;
    int i=u/M, j=u%M;
    REP(k,4) {
      II m=moves[k];
      int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      if(G[ii][jj]=='#') continue;
      int p=d%K;
      if(nex[p][k]==Inf) continue;
      LL w=nex[p][k]-p+1;
      LL d2=d+w;
      int v=M*ii+jj;
      if(d2<D[v]) {
//        dump4(ii,jj,d,d2);
        auto it2=Q.find({D[v],v});
        if(it2!=Q.end()) Q.erase(it2);
        D[v]=d2; Q.emplace(d2,v);
      }
    }
  }
}

LL solve() {
  string D2=DD+DD;
  LL P[4]={Inf,Inf,Inf,Inf};
  for(int i=2*K-1; i>=0; --i) {
    P[revmv[D2[i]]]=i;
    if(i<K) REP(j,4) nex[i][j]=P[j];
  }
//  REP(i,K)REP(j,4) dump3(i,j,nex[i][j]);
  
  int S=-1,dest=-1;
  REP(i,N) REP(j,M) {
    if(G[i][j]=='S') S=M*i+j;
    if(G[i][j]=='G') dest=M*i+j;
  }
  assert(S>=0&&dest>=0);
  
  dijkstra(N*M,S);
  
//  REP(i,N*M) dump3(i/M,i%M,D[i]);
  
  if(D[dest]==Inf) return -1;
  return D[dest];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M>>K>>DD;
  REP(i,N) cin>>G[i];
  cout<<solve()<<endl;
  return 0;
}
