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
template <typename Val, int MAX_N> struct Com {
  vector<Val> fac,ifac;
  Com() {
    fac.resize(MAX_N+1,0),ifac.resize(MAX_N+1,0);
    fac[0]=1,ifac[0]=1;
    for(int i=1;i<=MAX_N;i++) fac[i]=fac[i-1]*i;
    ifac[MAX_N]=Val(1)/fac[MAX_N];
    for(int i=MAX_N-1; i>=1; --i) ifac[i]=ifac[i+1]*Val(i+1);
  }
  Val choose(int n, int k) {
    if(n<k) return 0;
    assert(0<=k&&k<=MAX_N);
    return fac[n]*ifac[n-k]*ifac[k];
  }
  Val fact(int k) { return fac[k]; }
  Val perm(int n, int k) {
    if(n<k) return 0;
    assert(0<=k&&k<=MAX_N);
    return fac[n]*ifac[n-k];
  }
  Val multichoose(int n, int k) {
    if(n==0&&k==0) return 1;
    return choose(n+k-1,k);
  }
};
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
Com<ModInt,(int)2e6> com;
// $ cp-batch NEQ | diff NEQ.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NEQ.cpp && ./a.out

/*

 6/27/2020

 5:37-5:51, 6:08-6:40 give up
 9:40-10:40 AC

 https://img.atcoder.jp/abc172/editorial.pdf
 https://youtu.be/v8ppNGf49Nk?t=7729
 https://maspypy.com/atcoder-%e5%8f%82%e5%8a%a0%e6%84%9f%e6%83%b3-2020-06-27abc-172
 https://kmjp.hatenablog.jp/entry/2020/06/27/1000
 https://www.hamayanhamayan.com/entry/2020/06/27/224101
 https://ngtkana.growi.cloud/contests/abc_172

 https://twitter.com/drken1215/status/1276873040169537539
 https://twitter.com/laycrs/status/1276873009068834816
 https://twitter.com/kyopro_friends/status/1276876350381383680
 https://twitter.com/ajis_ka/status/1276874096853147648

 */

int N,M;

void solve() {
  ModInt res=0;
  REPE(i,N) {
    //dump(i,perm(M,N),choose(N,i),perm(M-i,N-i));
    ModInt x=com.choose(N,i)*com.perm(M,N)*com.perm(M-i,N-i);
    if(i%2) res-=x;
    else res+=x;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M;
  solve();

  return 0;
}
