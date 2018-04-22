#include <iostream>
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
 
 4/21/2018 ARC096
 
 21:20-22:30 obtained only 300/500 pt
 
 It was obvious that going to one direction and turning at most once is optimal.
 After the turn, obtained calory by going the other direction is independent.
 I just computed single maximal value in each direction. However this is not optimal as seen in sample #2.
 We cannot take the same sushi twice.
 Suppose we are reaching x[l] and x[r]. We are taking right up to x[r], turn and take left up to x[l].
 The decision of x[r] constrains x[l] because l < r must hold.
 Thus we want to query optimal `l` for position `r` in less than linear time.
 It's easy to query by pre-computing the table with size `N`.
 
 4/22/2018

 9:30-10:00, 13:30-13:42 Read editorials and get ACC
 
 Editorials:
  - https://img.atcoder.jp/arc096/editorial.pdf
  - https://www.youtube.com/watch?v=qOG8pkCP7oI
  - http://ferin-tech.hatenablog.com/entry/2018/04/21/225527
  - https://togetter.com/li/1220212
   - https://twitter.com/beet_aizu/status/987690177169580033
   - https://twitter.com/satanic0258/status/987688074292310016
   - https://twitter.com/kuuso1/status/987690464097722373
   - https://twitter.com/rickytheta/status/987690408577675265
   - https://twitter.com/satanic0258/status/987690381130153984
   - https://twitter.com/beet_aizu/status/987690177169580033
   - https://twitter.com/tanakh/status/987689083064410118
   - https://twitter.com/torus711/status/987688857792532481
   - https://twitter.com/merom686/status/987689705461305344
   - https://twitter.com/ferin_tech15/status/987688342706778112

 Short and simple solution:
  - https://beta.atcoder.jp/contests/arc096/submissions/2391737
 
 Key:
  - Optimal choice of the other side is determined by turning position
  - Optimal choice of the other side can be pre-computed
 
 Summary:
  - I should have figured out that optimal choice of the other side depends on the turning side
  - My first approach to find optimal choice of the other side did not work
   - I did not consider upper-bound of the position (x[l] < x[r] should hold)
   - The upper-bounded position affects optimal choice
 
 */

LL X[100001],V[100001],Q[100002];
LL f(int N, LL C) {
  LL res=0;
  ZERO(Q);
  LL cur=0;
  REP(i,N) {
    LL x=X[i],v=V[i];
    cur+=v;
    LL vv=cur-x;
    Q[i+1]=max(Q[i],vv); // Q[i] for [0,i)
  }
  
  cur=0;
  for(int i=N; i>=0; --i) {
    LL a=Q[i];
    LL b=0;
    if(i<N) {
      LL x=C-X[i],v=V[i];
      cur+=v;
      b=cur-2*x;
    }
    SMAX(res,a+b);
  }
  return res;
}
LL solve(int N, LL C) {
  LL res=0;
  SMAX(res,f(N,C));
  reverse(X,X+N); REP(i,N) X[i]=C-X[i];
  reverse(V,V+N);
  SMAX(res,f(N,C));
  return res;
}

int main() {
  LL N,C;
  cin >> N >> C;
  REP(i,N) {
    LL x,v;
    cin >> x >> v;
    X[i]=x,V[i]=v;
  }
  cout << solve(N,C) << endl;
  return 0;
}

///////////////////////

int maxrighti=-1;
__int128 right(int N, LL C, vector<pair<LL,LL>> &X) {
  __int128 res=0;
  __int128 sum=0;
  REP(i,N) {
    __int128 x=X[i].first,cal=X[i].second;
    sum+=cal;
    if(res<sum-x) {
      res=sum-x;
      maxrighti = i;
    }
  }
  return res;
}

int maxlefti=-1;
__int128 left(int N, LL C, vector<pair<LL,LL>> &X) {
  __int128 res=0;
  __int128 sum=0;
  for(int i=N-1; i>=0; --i) {
    __int128 x=C-X[i].first,cal=X[i].second;
    sum+=cal;
    if(res<sum-x) {
      res=sum-x;
      maxlefti = i;
    }
  }
  return res;
}

__int128 solve_300(int N, LL C, vector<pair<LL,LL>> &X) {
  __int128 res=0;
  __int128 rmax=right(N,C,X);
  __int128 lmax=left(N,C,X);
  
  if(res<rmax) res=rmax;
  if(res<lmax) res=lmax;
  
//  dump4(rmax,lmax,maxrighti,maxlefti);

  /*
  int l=0,r=N-1;
  __int128 lsum=X[0].second,rsum=X[N-1].second,res1=lsum-2*X[0].first+rsum-(C-X[N-1]);
  while(l<r-1) {
    __int128 lsum2=lsum+X[l+1],a=lsum2-2*X[l+1].first+rsum-(C-X[r]);
    __int128 rsum2=rsum+X[r-1],b=rsum-2*X[l].first+rsum2-(C-X[r-1]);

    if(res<a) res=a;
    if(res<b) res=b;
    if(a<b) --r;
    else ++l;
  }
  
  l=0,r=N-1;
  lsum=X[0].second,rsum=X[N-1].second,res1=lsum-X[0].first+rsum-2*(C-X[N-1]);
  while(l<r-1) {
    __int128 lsum2=lsum+X[l+1],a=lsum2-X[l+1].first+rsum-2*(C-X[r]);
    __int128 rsum2=rsum+X[r-1],b=rsum-2*X[l].first+rsum2-(C-X[r-1]);
    
    if(res<a) res=a;
    if(res<b) res=b;
    if(a<b) --r;
    else ++l;
  }*/
  
  __int128 lsum=0;
  REP(l,N) {
    __int128 lx=X[l].first,lcal=X[l].second;
    lsum+=lcal;
    
    __int128 rsum=0;
    for(int r=N-1; r>l; --r) {
      __int128 rx=C-X[r].first,rcal=X[r].second;
      rsum+=rcal;
      
      __int128 a=lsum-2*lx+rsum-rx;
      if(a>res) res=a;
      __int128 b=rsum-2*rx+lsum-lx;
      if(b>res) res=b;
    }
  }

//  if(res<lmax2) res=lmax2;
//  if(res<rmax2) res=rmax2;
  return res;
}
