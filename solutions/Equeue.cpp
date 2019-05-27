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

// $ cp-batch Equeue | diff Equeue.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Equeue.cpp && ./a.out

/*
 
 5/26/2019
 
 5:14-5:25 WA
 5:51 WA
 6:01 WA
 7:00-7:14 understood that I missunderstood problem statement. No need to perform exactly K times 😡
 
 https://img.atcoder.jp/abc128/editorial.pdf
 
 */

const int MAX_N=1e2+1;
LL V[MAX_N];
int N,K;

void solve() {
  LL res=0;
  REPE(l,K)REPE(r,K) if(l+r<=N&&l+r<=K) {
    vector<LL> X;
    REP(i,l) X.push_back(V[i]);
    REP(i,r) X.push_back(V[N-1-i]);
    sort(ALL(X)),reverse(ALL(X));
    int M=K-l-r;
    int L=SZ(X);

    /*
    LL sum=0;
    REP(i,L) {
      sum+=X[i];
      int rem=L-i-1;
      if(rem>M) continue;
      if((M-rem)%2==0) SMAX(res,sum);
    }*/
    LL ans=0;
    int i=L-1;
    while(i>=0&&X[i]<0&&M--) --i;
    /*
    if(M%2==1) {
      if(i+1<L&&i>=0&&-X[i]>X[i+1]) ++i;
      else --i;
      i=max(i,-1);
    }*/
    ans=accumulate(X.begin(),X.begin()+i+1,0LL);
    SMAX(res,ans);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>K;
  REP(i,N) cin>>V[i];
  solve();
  
  return 0;
}
