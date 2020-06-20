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
template<class T> using VV=vector<vector<T>>;
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
#define ALL(c) (c).begin(),(c).end()
// $ cp-batch FTRobot | diff FTRobot.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address FTRobot.cpp && ./a.out
/*

 7/29/2018

 19:35-20:13 1WA
 20:14-20:23 bugfix and ACC

 Editorials:
  - https://img.atcoder.jp/arc087/editorial.pdf
  - https://youtu.be/GDuzZIuWs2Q?t=1703
  - http://hamayanhamayan.hatenablog.jp/entry/2017/12/16/231529

 Tweets:
  - https://togetter.com/li/1181932
  - https://twitter.com/satanic0258/status/942027011056287744
  - https://twitter.com/catupper/status/942027156237852672
  - https://twitter.com/iwashi31/status/942027348404199424
  - https://twitter.com/torus711/status/942027734489874432

 Key:
  - X coordiante and Y coordinate are independent
  - subset sum DP

 Summary:
  - Analysis was not tough though, WA due to offset

 6/19/2020

 21:02-21:46 solve again

 */

const int MAX_N=8000+1;
string S;
int XT,YT;

bool f(VI ms, int G) {
  //dumpc(ms);
  int L=accumulate(ALL(ms),0);
  int M=SZ(ms);
  int hb=2*L+10;
  VV<int> dp(M+1,VI(hb,0));
  dp[0][L+5]=1,G+=L+5;
  REP(i,M) REP(j,hb) if(dp[i][j]) {
    dp[i+1][j+ms[i]]=true,dp[i+1][j-ms[i]]=true;
  }
  return dp[M][G];
}
void solve() {
  int X=XT,Y=YT;
  VV<int> ms(2);
  int N=SZ(S);
  int i=0;
  while(i<N&&S[i]=='F') --X,i+=1;
  int dir=0;
  //dump(i,X,Y);
  FOR(j,i,N) {
    if(S[j]=='T') {
      dir^=1;
      ms[dir].push_back(0);
    } else {
      ms[dir].back()++;
      //dump(j,ms[dir].back());
    }
  }
  bool xok=f(ms[0],X),yok=f(ms[1],Y);
  cout<<(xok&&yok?"Yes":"No")<<endl;
}

const string yes="Yes",no="No";
int dp1[MAX_N*2+10],dp2[MAX_N*2+10];
void solve_org() {
  VI X,Y;
  bool hr=true;
  int cur=0;
  REP(i,SZ(S)) {
    if(S[i]=='T') {
      (hr?X:Y).push_back(cur);
      cur=0;
      hr=!hr;
    } else {
      ++cur;
    }
  }
  (hr?X:Y).push_back(cur);

  int offset=MAX_N;

  bool xok=false;
  ZERO(dp1);
  if(SZ(X)==0) {
    xok=XT==0;
  } else {
    dp1[offset+X[0]]=true;
    FOR(i,1,SZ(X)) {
      ZERO(dp2);
      FORE(x,-MAX_N,MAX_N) if(dp1[offset+x]) {
        int dt=X[i];
        dp2[offset+x+dt]=1;
        dp2[offset+x-dt]=1;
      }
      swap(dp1,dp2);
    }
//    dump3(offset,offset+XT,dp1[offset+XT]);
    xok=dp1[offset+XT];
  }

  bool yok=false;
  ZERO(dp1);
  dp1[offset+0]=true;
  REP(i,SZ(Y)) {
    ZERO(dp2);
    FORE(y,-MAX_N,MAX_N) if(dp1[offset+y]) {
      int dt=Y[i];
      dp2[offset+y+dt]=1;
      dp2[offset+y-dt]=1;
    }
    swap(dp1,dp2);
  }
  yok=dp1[offset+YT];
//  dump3(offset,offset+YT,dp1[offset+YT]);

  cout<<(xok&&yok?yes:no)<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  cin>>S>>XT>>YT;
  solve_org();
  return 0;
}
