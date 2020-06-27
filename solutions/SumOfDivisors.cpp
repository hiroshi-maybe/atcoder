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
struct PrimeFact {
public:
  PrimeFact(int N): N(N) {
    // make prime table by sieve
    divp.resize(N+1,0);
    for(int p=2; p<=this->N; ++p) if(divp[p]==0) {
      P.push_back(p);
      divp[p]=p;
      for(long long q=1LL*p*p; q<=N; q+=p) if(divp[q]==0) divp[q]=p;
    }
  }
  vector<int> fact(int n) {
    vector<int> res;
    while(n>1) res.push_back(divp[n]), n/=divp[n];
    sort(res.begin(),res.end());
    return res;
  }
  LL divs(int n) {
    LL res=1;
    while(n>1) {
      int p=divp[n],cnt=1;
      while(n%p==0) n/=p,++cnt;
      res*=(cnt);
    }
    return res;
  }
  vector<int> P; // list of prime numbers
private:
  int N;
  vector<int> divp;
};
// $ cp-batch SumOfDivisors | diff SumOfDivisors.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SumOfDivisors.cpp && ./a.out

/*

 6/27/2020

 5:19-5:37 AC

 12:55 add solution by harmony sequence.
 14:38 Add O(sqrt(N)) solution

 https://img.atcoder.jp/abc172/editorial.pdf
 https://twitter.com/kyopro_friends/status/1276873988010995712
 https://maspypy.com/atcoder-%e5%8f%82%e5%8a%a0%e6%84%9f%e6%83%b3-2020-06-27abc-172
 https://ngtkana.growi.cloud/contests/abc_172

 */

LL N;

LL S(LL n) { return n*(n+1)/2; }
LL solve() {
  LL res=0;
  for(LL p=1; p*p<=N; ++p) {
    LL q=N/p;
    res+=p*S(q);
    //dump(p,S(q),p*S(q));
    if(p==q) continue;
    LL lb=(LL)N/(p+1)+1,hb=(LL)N/p;
    LL x=(lb+hb)*(hb-lb+1)/2*S(p);
    //dump(p,lb,hb,x);
    res+=x;
  }
  return res;
}

LL solve_() {
  LL res=0;
  FORE(k,1,N) {
    LL cnt=N/k;
    LL x=((LL)k+(LL)N/k*k)*cnt/2;
    res+=x;
    //dump(k,x);
  }
  return res;
}

// 1440(ms)->78(ms) without the array
void solve_harmonyseq() {
  //vector<LL> cnt(N+1,0);
  LL res=0;
  FORE(k,1,N) {
    for(int kk=k; kk<=N; kk+=k) res+=kk;//cnt[kk]++;
  }
  //LL res=0;
  //FORE(k,1,N) res+=(LL)k*cnt[k];
  cout<<res<<endl;
}

void solve_sieve() {
  PrimeFact pf(N);
  LL res=0;
  FORE(k,1,N) {
    res+=(LL)k*pf.divs(k);
  }
  //dump(measure());
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

/*
  FORE(i,1,87617) {
    N=i;
    dump(i,solve(),solve_());
    assert(solve()==solve_());
  }*/

  cin>>N;
  LL res=solve();
  //assert(res==res_);

  cout<<res<<endl;

  return 0;
}
