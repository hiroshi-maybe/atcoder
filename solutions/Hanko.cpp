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
 
 8/16/2018
 
 18:00-19:01 analysis
 19:30 give up
 
 8/18/2018
 
 16:00-17:10 read editorials and add solution (2WA)
 
 Editorials:
  - https://img.atcoder.jp/bitflyer2018-qual/editorial.pdf
  - http://kmjp.hatenablog.jp/entry/2018/06/08/0900
  - https://www.hamayanhamayan.com/entry/2018/06/02/235536
  - http://betrue12.hateblo.jp/entry/2018/06/03/131350
  - http://drken1215.hatenablog.com/entry/2018/06/03/023000
 
 Idea of imos and coordinate compression was correct.
 However I was not used to 2D imos 😞
 In this case use of map made things complex unnecessarily 😞😞
 
 Summary:
  - I tried to solve by imos. However I got confused about 2 dimensions imos
  - This seemed to be skyline problem. So I tried to reduce to interval with sweep line
  - using map does not improve complexity because points in W-2*N are "compressed". Use just simple array
  - Make extra row or column ONLY when coordinate is compressed
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e3+1;
LL H,W;
int N,M;
string S[MAX_N];

/*
map<LL,int> imos[2*MAX_N];
map<LL,LL> Y;
LL YY[2*MAX_N];
void solve() {
  if(H<2*N) REPE(i,2*N) Y[i]=i;
  else {
    REP(i,N) {
      Y[i]=i,Y[H-N+i]=N+i;
      YY[i]=i,YY[N+i]=H-N+i;
    }
    Y[H]=2*N,YY[2*N]=H;
  }
  
  REP(i,N)REP(j,M) if(S[i][j]=='#') {
    imos[i][j]=1,imos[i][j+W-M]=-1;
    LL y=i*H-N; assert(Y.count(y));
    int ii=Y[y];
    imos[ii][j]=-1,imos[ii][j+W-M]=+1;
  }
  
  LL res=0;
  LL cur=0;
  REPE(i,2*N) {
    if(i>0) res+=cur*(YY[i]-YY[i-1]);
    LL x=0;
    LL l=-1;
    FORR(kvp,imos[i]) {
      cur+=kvp.second;
    }
  }
}*/

int imos[2*MAX_N][2*MAX_N];
void solve() {
  ZERO(imos);
  REP(i,N)REP(j,M)if(S[i][j]=='#') {
    int ii=min(1LL*i+H-N+1,1LL*N+i+2),jj=min(1LL*j+W-M+1,1LL*M+j+2);
    imos[i][j]+=1,imos[ii][j]+=-1,imos[i][jj]+=-1,imos[ii][jj]+=1;
  }
  
  /*
  REPE(i,2*N) {
    REPE(j,2*M) cout<<imos[i][j];
    cout<<endl;
  }*/
  
  REPE(i,2*N) REPE(j,2*M) imos[i][j+1]+=imos[i][j];
  REPE(j,2*M) REPE(i,2*N) imos[i+1][j]+=imos[i][j];
  LL res=0;

/*
  REPE(i,2*N) {
    REPE(j,2*M) cout<<(imos[i][j]?'#':'.');
    cout<<endl;
  }*/
  
  REPE(i,2*N)REPE(j,2*M) if(imos[i][j]>0) {
    LL a=1;
    if(i==N&&H>2*N) a*=1LL*H-2*N;
    if(j==M&&W>2*M) a*=1LL*W-2*M;
//    dump3(i,j,a);
    res+=a;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>H>>W>>N>>M;
  REP(i,N) cin>>S[i];
  solve();
  return 0;
}
