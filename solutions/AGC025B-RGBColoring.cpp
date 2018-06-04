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

 6/3/2018 AGC025B

 21:10-21:35, 22:00-22:30 give up

 6/4/2018

 22:30-23:50 read editorials and add solution

 Editorial:
  - https://img.atcoder.jp/agc025/editorial.pdf
  - https://youtu.be/Ommfmx2wtuY?t=2158
  - http://naoyat.hatenablog.jp/entry/AGC025
  - http://yosupo.hatenablog.com/entry/2018/06/04/004619
  - http://drken1215.hatenablog.com/entry/2018/06/04/120000_1
 
 Tweets:
  - https://togetter.com/li/1233682
  - https://twitter.com/zunda99999999th/status/1003277679020335104
  - https://twitter.com/tempura_pp/status/1003311059019546624
  - https://twitter.com/_TTJR_/status/1003306850048040960
  - https://twitter.com/_TTJR_/status/1003277771924099077
  - https://twitter.com/drken1215/status/1003278214578360320
  - https://twitter.com/tanakh/status/1003279982544605184
  - https://twitter.com/ei1333/status/1003278396565016576

 Key:
  - Green (A+B) forms unique color. That means duplicated paint is valid
  - Simply choose `x` slots for A and `y` slots for B independently
 
 Summary:
  - I couldn't figure out hidden independence of A and B due to green..
  - My analysis started focusing of how many `A` and `B` happens. However I couldn't reach independence property

 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 21:10-21:35,
const int MAX_N=3e5+1;
LL C[MAX_N];
LL N,A,B,K;
const LL MOD=998244353;

LL powmod(LL a, LL b) {
  assert(0<=a && a<MOD);
  assert(0<=b);

  LL res=1;
  for(LL mask=1; mask<=b; mask<<=1) {
    if(b&mask) res*=a, res%=MOD;
    a*=a; a%=MOD;
  }
  return res;
}
LL modinv(LL a, LL p=MOD) {
  return powmod(a, p-2);
}
void make() {
	C[0]=1;
	C[1]=N;
	for(int i=2;i<=N; ++i) {
		LL a=C[i-1];
		a*=(N-i+1),a%=MOD;
		a*=modinv(i),a%=MOD;
		C[i]=a;
	}
}

LL solve() {
  LL res=0;
  make();
  REPE(x,N) if((K-A*x)%B==0) {
  	LL y=(K-A*x)/B;
    if(y>N||y<0) continue;
//  	dump2(x,y);
    assert(x<=N&&y<=N);
  	LL a=C[x]*C[y];
  	a%=MOD;
  	res+=a,res%=MOD;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>A>>B>>K;
  cout<<solve()<<endl;
  return 0;
}
