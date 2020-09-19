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
const int MOD=998244353;
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
template <typename T> struct BIT {
public:
  int N;
  vector<T> A;
  BIT() {}
  BIT(int N) { init(N); }
  void init(int N) {
    this->N=N;
    A=vector<T>(N+1,0);
  }
  // query ∑ { sum[i] : i=l..<r }
  T query(int l, int r) {
    assert(l<=r&&0<=l&&r<=N);
    return query(r)-query(l);
  }
  // min index s.t. dat[0..i]>x
  int upperbound(T x) {
    int good=N+1,bad=0;
    while(abs(good-bad)>1) {
      int m=(good+bad)/2;
      (query(m)>x?good:bad)=m;
    }
    return good-1;
  }
  // sum[i]+=x
  void add(int i, T x) {
    assert(0<=i&&i<N);
    ++i;
    while(i<=N) A[i]+=x,i+=lsone(i);
  }
  // sum[i]=x
  void update(int i, T v) {
    T pre=query(i+1)-query(i);
    add(i,v-pre);
  }
private:
  int lsone(int i) { return i&-i; }
  // query in [0,r) : ∑ { sum[i] : i=0..r-1 }
  T query(int r) {
    assert(0<=r&&r<=N);
    T res=0;
    while(r>0) res+=A[r],r-=lsone(r);
    return res;
  }
};
// $ cp-batch LeapingTak | diff LeapingTak.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address LeapingTak.cpp && ./a.out

/*

 9/19/2020

 5:08-5:24 AC

 https://atcoder.jp/contests/abc179/editorial/121
 https://youtu.be/1BlDPBKtKKE?t=1654

 */

const int MAX_N=1e6+1;
II J[MAX_N];
int N,K;

void solve() {
  BIT<ModInt> bit(N+1);
  bit.add(0,1);

  FOR(i,1,N) {
    REP(j,K) {
      auto p=J[j];
      int l2=i-p.second,r2=i-p.first+1;
      int l1=0,r1=i;
      int l=max(l1,l2),r=min(r1,r2);
      if(l<r) {
        //dump(i,l,r,bit.query(l,r));
        bit.add(i,bit.query(l,r));
      }
    }
  }
  cout<<bit.query(N-1,N)<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>K;
  REP(i,K) {
    int l,r; cin>>l>>r;
    J[i]={l,r};
  }
  solve();

  return 0;
}
