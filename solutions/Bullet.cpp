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
struct Frac {
public:
  // numerator / denominator
  long long n,d;
  Frac(): n(0),d(1) {}
  Frac(int nn) : n(nn), d(1) {}
  Frac(long long nn, long long dd) { norm(nn,dd); }
  Frac(int nn, int dd) { norm(nn,dd); }
  Frac& norm(long long nn, long long dd) {
    assert(dd!=0);
    if(dd<0) nn*=-1,dd*=-1;
    bool neg=nn<0;
    nn=neg?-nn:nn;
    long long g=gcd(nn,dd);
    nn/=g,dd/=g;
    this->n=nn;
    if(neg) this->n=-1*this->n;
    this->d=dd;
    return *this;
  }
  Frac abs() { return Frac(n<0?-n:n,d); }
  Frac inv() { return Frac(d,n); }
  Frac &operator -() { n=-n; return *this; }
  Frac &operator += (Frac that) { long long nn=(long long)n*that.d+(long long)that.n*d,dd=(long long)d*that.d; return norm(nn,dd); }
  Frac &operator -= (Frac that) { *this+=-that; return *this; }
  Frac &operator *=(Frac that) { long long nn=(long long)n*that.n,dd=(long long)d*that.d; return norm(nn,dd); }
  Frac &operator /= (Frac that) { *this*=Frac(that.d,that.n); return *this; }
  Frac operator+(Frac that) const { return Frac(*this)+=that; }
  Frac operator-(Frac that) const { return Frac(*this)-=that; }
  Frac operator*(Frac that) const { return Frac(*this)*=that; }
  Frac operator/(Frac that) const { return Frac(*this)/=that; }
  bool operator < (Frac that) { return (long long)n*that.d<(long long)that.n*d; }
  bool operator > (Frac that) { return that<Frac(*this); }
  bool operator == (Frac that) { return n==that.n&&d==that.d; }
  bool operator <= (Frac that) { return Frac(*this)<that||Frac(*this)==that; }
  bool operator >= (Frac that) { return Frac(*this)>that||Frac(*this)==that; }
  friend ostream& operator<<(ostream& os, const Frac& that) { return os<<that.n<<"/"<<that.d; }
private:
  long long gcd(long long a, long long b) {
    return b==0?a:gcd(b,a%b);
  }
};
// $ cp-batch Bullet | diff Bullet.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Bullet.cpp && ./a.out

/*

 5/17/2020

 5:26-7:21 give up
 11:33-12:40 read editorial and got AC

 https://img.atcoder.jp/abc168/editorial.pdf
 https://twitter.com/hanseilimak/status/1262089919226187778
 https://twitter.com/kyopro_friends/status/1262016483053338626

 */

const int MAX_N=1e6+1;
LL A[MAX_N],B[MAX_N];
int N;

void solve_bf() {
  ModInt res=0;
  VI added(N);
  FOR(mask,1,1<<N) {
    VI xs;
    REP(i,N) if((mask>>i)&1) {
      xs.push_back(i);
    }
    bool ok=true;
    int M=SZ(xs);
    REP(j,M)REP(i,j) if(A[xs[i]]*A[xs[j]]+B[xs[i]]*B[xs[j]]==0) {
      ok=false;
    }
    res+=ok;
    if(ok) FORR(i,xs) added[i]++;
  }
  dumpc(added);
  cout<<res<<endl;
}

pair<LL,LL> other(pair<LL,LL> a) {
  if(a.first==0) return {1,0};
  if(a.second==0) return {0,1};
  Frac x(-a.second,a.first);
  return {x.n,x.d};
}
ModInt f(pair<LL,LL> a, map<pair<LL,LL>,int> &cnt) {
  pair<LL,LL> b=other(a);
  int cnta=cnt[a],cntb=cnt[b];
  //dump(cnta,cntb);
  return ModInt(2).pow(cnta)+ModInt(2).pow(cntb)-1;
}

void solve() {
  map<pair<LL,LL>,int> cnt;
  int abzero=0;
  REP(i,N) {
    pair<LL,LL> a;
    if(A[i]==0&&B[i]==0) {
      abzero++;
      continue;
    } else if(A[i]==0) {
      a={0,1};
    } else if(B[i]==0) {
      a={1,0};
    } else {
      Frac f=Frac(A[i],B[i]);
      a={f.n,f.d};
    }
    cnt[a]++;
  }

  set<pair<LL,LL>> viz;
  ModInt res=1;
  FORR(kvp, cnt) if(viz.count(kvp.first)==0) {
    res*=f(kvp.first, cnt);
    viz.emplace(kvp.first),viz.emplace(other(kvp.first));
  }
  res+=abzero-1;
  cout<<res<<endl;
}

void solve_org() {
  ModInt tot=1;
  map<pair<LL,LL>,int> cnt;
  int abzero=0;
  REP(i,N) {
    pair<LL,LL> a;
    if(A[i]==0&&B[i]==0) {
      abzero++;
      continue;
    } else if(A[i]==0) {
      a={0,1};
    } else if(B[i]==0) {
      a={1,0};
    } else {
      Frac f=Frac(A[i],B[i]);
      a={f.n,f.d};
    }
    ModInt old=f(a,cnt);
    dump(i,tot,old);
    ModInt x=tot/old;
    cnt[a]++;
    ModInt y=f(a,cnt);
    tot=x*y;
    dump(i,a.first,a.second,x,y,tot);
  }
  ModInt res=tot+abzero-1;
  cout<<res<<endl;
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
