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
const int MOD=1000000007;
//const int MOD=998244353;
struct ModInt {
  unsigned int val;
  ModInt(): val(0) {}
  ModInt(int v) { norm(v%MOD); }
  ModInt(long long v) { norm(v%MOD); }
  ModInt& norm(long long v) {
    v=v<0?v%MOD+MOD:v; // negative
    v=v>=MOD?v-MOD:v; // mod
    val=(unsigned int)v;
    return *this;
  }
  explicit operator bool() const { return val!=0; }
  ModInt operator-() const { return ModInt(0)-*this; }
  ModInt &operator+=(ModInt that) { return norm((long long)val+that.val); }
  ModInt &operator-=(ModInt that) { return norm((long long)val-that.val); }
  ModInt &operator*=(ModInt that) { val=(unsigned long long)val*that.val%MOD; return *this; }
  ModInt &operator/=(ModInt that) { return *this*=that.inv(); }
  ModInt operator+(ModInt that) const { return ModInt(*this)+=that; }
  ModInt operator-(ModInt that) const { return ModInt(*this)-=that; }
  ModInt operator*(ModInt that) const { return ModInt(*this)*=that; }
  ModInt operator/(ModInt that) const { return ModInt(*this)/=that; }
  ModInt pow(long long n) const {
    ModInt x=*this, res=1;
    while(n>0) {
      if(n&1) res*=x;
      x*=x,n>>=1;
    }
    return res;
  }
  ModInt inv() const { return (*this).pow(MOD-2); }
  bool operator==(ModInt that) const { return val==that.val; }
  bool operator!=(ModInt that) const { return val!=that.val; }
  friend ostream& operator<<(ostream& os, const ModInt& that) { return os<<that.val; }
};
// $ cp-batch Multiplication4 | diff Multiplication4.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Multiplication4.cpp && ./a.out

/*

 7/5/2020

 5:42-6:40 give up
 12:05-12:47 AC by `long double` and log2()
 13:00 AC by merge sort
 13:30 read editorials

 https://twitter.com/hanseilimak/status/1279864386341892096
 https://img.atcoder.jp/abc173/editorial.pdf
 https://www.youtube.com/watch?v=IMwigbYzLbI&t=3991s

 https://kmjp.hatenablog.jp/entry/2020/07/06/0900

 https://twitter.com/maspy_stars/status/1279773396125933568
 https://twitter.com/tanakh/status/1279787953447768064
 https://twitter.com/tsutaj/status/1279772999319556098
 https://twitter.com/laycrs/status/1279772134051508235
 https://twitter.com/kzyKT_M/status/1279772302293340162
 https://twitter.com/tsutaj/status/1279772169652690944
 https://twitter.com/small_onions/status/1279772117873995778
 https://twitter.com/satanic0258/status/1279772132566695938
 https://twitter.com/ei1333/status/1279772356966092800

 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N,K;

void solve() {
  if(N==K) {
    ModInt res(1);
    REP(i,N) res*=A[i];
    cout<<res<<endl;
    return;
  }

  vector<LL> ps,ns;
  REP(i,N) (A[i]>0?ps:ns).push_back(A[i]);
  sort(ALL(ps)),sort(ALL(ns));
  int M=SZ(ns);

  vector<ModInt> cuml(M+1,1),cumh(M+1,1);
  REP(i,M) cuml[i+1]=cuml[i]*ns[i];
  REP(i,M) cumh[i+1]=cumh[i]*ns[M-1-i];

  if(ps.empty()) {
    if(K%2==1) cout<<cumh[K]<<endl;
    else cout<<cuml[K]<<endl;
    return;
  }

  ModInt res(1);
  int k=K;
  if(k%2==1) {
    res*=ps.back();
    ps.pop_back();
    k--;
  }
  queue<LL> pq,nq;
  while(SZ(ps)>1) {
    pq.push(ps[SZ(ps)-1]*ps[SZ(ps)-2]);
    ps.pop_back(),ps.pop_back();
  }
  reverse(ALL(ns));
  while(SZ(ns)>1) {
    nq.push(ns[SZ(ns)-1]*ns[SZ(ns)-2]);
    ns.pop_back(),ns.pop_back();
  }

  assert(k%2==0);
  while(k>0) {
    if(pq.empty()||pq.front()<nq.front()) res*=nq.front(),nq.pop();
    else res*=pq.front(),pq.pop();
    k-=2;
  }
  cout<<res<<endl;
}

void solve_longarithm() {
  vector<LL> ps,ns;
  REP(i,N) (A[i]>0?ps:ns).push_back(A[i]);
  sort(ALL(ps)),sort(ALL(ns));
  int M=SZ(ns);

  vector<ModInt> cuml(M+1,1),cumh(M+1,1);
  REP(i,M) cuml[i+1]=cuml[i]*ns[i];
  REP(i,M) cumh[i+1]=cumh[i]*ns[M-1-i];

  //dumpc(ns);
  if(ps.empty()) {
    if(K%2==1) cout<<cumh[K]<<endl;
    else cout<<cuml[K]<<endl;
    return;
  }
  /*
  if(K%2==0) {
    vector<LL> as;
    REP(i,N) as.push_back(abs(A[i]));
    sort(ALL(as)),reverse(ALL(as));
    ModInt res(1);
    REP(i,K) res*=as[i];
    cout<<res<<endl;
    return;
  }*/

  const long double Inf=1e18;
  vector<long double> psl,nsl;
  FORR(p,ps) psl.push_back(log2(p));
  FORR(n,ns) {
    if(n==0) nsl.push_back(-Inf);
    else nsl.push_back(log2(-n));
  }
  vector<long double> cumpl(SZ(psl)+1),cumnl(SZ(nsl)+1);
  REP(i,SZ(psl)) cumpl[i+1]=cumpl[i]+psl[SZ(psl)-i-1];
  REP(i,SZ(nsl)) cumnl[i+1]=cumnl[i]+nsl[i];

  if(N==K) {
    ModInt res(1);
    FORR(p,ps) res*=p;
    FORR(n,ns) res*=n;
    cout<<res<<endl;
    return;
  }

  double mx=-Inf; int maxk=-1;
  //dump(SZ(cumpl),SZ(cumnl));
  for(int k=0; k<=K; k+=2) {
    if(k<SZ(cumnl)&&K-k<SZ(cumpl)&&cumnl[k]+cumpl[K-k]>mx) {
      maxk=k,mx=cumpl[K-k]+cumnl[k];
    }
  }

  //dump(maxk,mx,SZ(cumpl),SZ(cumnl),cumpl.back(),cumnl.back());
  if(mx<=-Inf) {
    cout<<0<<endl;
  } else {
    //dump(maxk);
    ModInt res(1);
    REP(i,maxk) res*=abs(ns[i]);
    REP(i,K-maxk) res*=ps[SZ(ps)-i-1];
    cout<<res<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>K;
  REP(i,N) cin>>A[i];
  solve();

  return 0;
}
