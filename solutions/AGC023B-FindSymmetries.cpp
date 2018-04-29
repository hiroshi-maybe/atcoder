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
 
 4/28/2018 AGC023
 
 21:40-23:20 time up 😞
 
 Editorials:
  - https://img.atcoder.jp/agc023/editorial.pdf
  - https://youtu.be/8BHBFMrZ8VM?t=780
  - http://hamko.hatenadiary.jp/entry/2018/04/29/000328
 
 Tweets:
  - process
   - https://twitter.com/evima0/status/990235557841154048
   - https://twitter.com/evima0/status/990235829036462080
   - https://twitter.com/satanic0258/status/990249515935399936
  - solutions
   - https://twitter.com/kuuso1/status/990235875752660992
   - https://twitter.com/iwashi31/status/990247602326130688
   - https://twitter.com/rickytheta/status/990234331065991171
   - https://twitter.com/rickytheta/status/990234654451023872
   - https://twitter.com/satanic0258/status/990234655826763776
   - https://twitter.com/kjuner8/status/990234726383239168
    - rolling hash
 
 15:00-15:21 add solution
 
 Key:
  - (A+x,B+x) makes same board as (A,B)
  - Saying that depending on only A-B is interesting
   - We can fix B=0 and only iterate A from 0 to N-1
 
 Summary:
  - Symmetry is a strong constraint. I thought I could reduce to different condition though, no luck
  - I had an idea of (rolling) hash. However I didn't think it's appropriate for 500 pt problem
  - I played around an experiment with 3x3 matrix though, I didn't notice that (A+x,B+x) == (A,B) 😞
  - It turns out this is a grouping problem
  - Analyzing between (A,B), (A+1,B+1) may have been helpful.
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=301;
int N;
string S[MAX_N];
LL solve() {
  LL res=0;
  REP(a,N) {
    vector<string> SS(N,string(N,'#'));
    REP(i,N)REP(j,N) SS[i][j]=S[(i+a)%N][j];
    
    bool ok=true;
    REP(j,N)REP(i,j) ok&=(SS[i][j]==SS[j][i]);
    res+=ok*N;
  }
  return res;
}

void test() {
  REP(mask1,1<<4)REP(mask2,1<<4)REP(mask3,1<<4)REP(mask4,1<<4) {
    vector<int> X={mask1,mask2,mask3,mask4};
    bool B[4][4];
    REP(i,4)REP(j,4)B[i][j]=(X[i]>>j)&1;
    bool BB[4][4]={};
    
    int res=0;
    REP(a,4)REP(b,4) {
      REP(i,4)REP(j,4)BB[i][j]=B[(i+a)%4][(j+b)%4];
      bool ok=true;
      REP(j,4)REP(i,j) ok&=BB[i][j]==BB[j][i];
      res+=ok;
    }
    if(res) dump(res);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>S[i];
  cout<<solve()<<endl;
  
//  test();
  
  return 0;
}
