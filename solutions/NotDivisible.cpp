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
  vector<int> divs(int n) {
    vector<int> res={1};
    while(n>1) {
      int p=divp[n],cnt=1,pp=p;
      while(n%p==0) n/=p,++cnt;
      int sz=res.size();
      for(int k=1; k<cnt; ++k) {
        for(int j=0; j<sz; ++j) res.push_back(res[j]*pp);
        pp*=p;
      }
    }
    return res;
  }
  vector<int> P; // list of prime numbers
private:
  int N;
  vector<int> divp;
};
// $ cp-batch NotDivisible | diff NotDivisible.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NotDivisible.cpp && ./a.out

/*

 6/14/2020

 5:11-5:22 AC

 Add solution by the sieve later

 https://img.atcoder.jp/abc170/editorial.pdf
 https://noshi91.hatenablog.com/entry/2018/12/27/121649

 https://twitter.com/kyopro_friends/status/1272166756233039875
 https://twitter.com/tempura_cpp/status/1272175909538115584

 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N;

vector<LL> divisors(LL N) {
  assert(N>=1);
  vector<LL> res;
  for(LL p=1; p*p<=N; ++p) if(N%p==0) {
    res.push_back(p);
    if(p!=N/p) res.push_back(N/p);
  }
  sort(res.begin(),res.end());
  return res;
}

void solve() {
  PrimeFact pf(1e6);
  map<int,int> cnt;
  REP(i,N) cnt[A[i]]++;
  int res=0;
  REP(i,N) {
    int a=A[i];
    cnt[a]--;
    vector<int> ds=pf.divs(a);
    bool ok=true;
    FORR(d,ds) if(cnt.count(d)&&cnt[d]>0) ok=false;
    //if(ok) dump(i,a);
    res+=ok;
    cnt[a]++;
  }
  cout<<res<<endl;
}

void solve_harmonic() {
  VI viz(1e6+1,0);
  map<int,int> cnt;
  REP(i,N) cnt[A[i]]++;
  sort(A,A+N);
  int res=0;

  REP(i,N) {
    int a=A[i];
    if(viz[a]) continue;
    int b=a;
    while(b<SZ(viz)) viz[b]=true,b+=a;
    if(cnt[a]==1)++res;
  }
  cout<<res<<endl;
}

void solve_org() {
  map<int,int> cnt;
  REP(i,N) cnt[A[i]]++;
  int res=0;
  REP(i,N) {
    int a=A[i];
    cnt[a]--;
    vector<LL> ds=divisors(a);
    bool ok=true;
    FORR(d,ds) if(cnt.count(d)&&cnt[d]>0) ok=false;
    //if(ok) dump(i,a);
    res+=ok;
    cnt[a]++;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>A[i];
  solve();

  return 0;
}
