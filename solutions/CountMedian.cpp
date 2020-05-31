#include <bits/stdc++.h>
using namespace std;
// type alias
typedef long long LL;
typedef pair<int,int> II;
typedef tuple<int,int,int> III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// stdout
#define println(args...) fprintf(stdout, ##args),putchar('\n');
// debug cerr
template<class Iter> void __kumaerrc(Iter begin, Iter end) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; }
void __kumaerr(istream_iterator<string> it) { (void)it; cerr<<endl; }
template<typename T, typename... Args> void __kumaerr(istream_iterator<string> it, T a, Args... args) { cerr<<*it<<"="<<a<<", ",__kumaerr(++it, args...); }
template<typename S, typename T> std::ostream& operator<<(std::ostream& _os, const std::pair<S,T>& _p) { return _os<<"{"<<_p.first<<','<<_p.second<<"}"; }
#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch CountMedian | diff CountMedian.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address CountMedian.cpp && ./a.out

/*

 5/31/2020

 5:21-6:01 AC

 Figured out that binary search is unnecessary after the contest.

 https://twitter.com/hanseilimak/status/1267232632686800896
 https://img.atcoder.jp/abc169/editorial.pdf

 https://twitter.com/maspy_stars/status/1267092108847886340
 https://twitter.com/kuuso1/status/1267091799513808896
 https://maspypy.com/atcoder-%e5%8f%82%e5%8a%a0%e6%84%9f%e6%83%b3-2020-05-31abc-169

 */

const int MAX_N=1e6+1;
LL A[MAX_N],B[MAX_N];
int N;

LL f(LL good, LL bad) {
  while(abs(good-bad)>1) {
    LL m=(good+bad)/2;
    LL a=0,b=0,c=0;
    REP(i,N) {
      if(B[i]<m) ++a;
      else if(A[i]>m) ++b;
      else ++c;
    }
    LL l1=a,r1=N-b,l2=N/2-(1-(N%2)),r2=N/2+1;
    bool res=l2>=l1&&r2<=r1;
    //dump(m,res,a,b,c,l1,r1,l2,r2);
    (res?good:bad)=m;
  }
  return good;
}
void solve() {
  if(N%2==0) REP(i,N)A[i]*=2,B[i]*=2;
  vector<LL> xs(A,A+N),ys(B,B+N);
  sort(ALL(xs)),sort(ALL(ys));
  LL med1=xs[N/2],med2=ys[N/2];
  if(N%2==0) med1=(med1+xs[N/2-1])/2,med2=(med2+ys[N/2-1])/2;
  //LL mina=*min_element(A,A+N),maxb=*max_element(B,B+N);
  LL lb=med1,hb=med2;
  //LL lb=f(med1, mina-1),hb=f(med2, maxb+1);
  //dump(med1,med2,lb,hb);
  cout<<hb-lb+1<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>A[i]>>B[i];
  solve();

  return 0;
}
