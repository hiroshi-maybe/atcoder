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
LL choose(LL n, LL k) {
  if(n<k) return 0;
  
  const int MAX_N = 1e6+1;
  assert(0<=k&&k<=MAX_N);
  static LL fact[MAX_N+1],revfact[MAX_N+1],rev[MAX_N+1];
  
  if(rev[1]==0) {
    rev[1]=1;
    for(int i=2;i<=MAX_N;i++) rev[i]=rev[MOD%i]*(MOD-MOD/i)%MOD;
    fact[0]=1,revfact[0]=1;
    for(int i=1;i<=MAX_N;i++) {
      fact[i]=fact[i-1]*i%MOD;
      revfact[i]=revfact[i-1]*rev[i]%MOD;
    }
  }
  return fact[n]*revfact[n-k]%MOD*revfact[k]%MOD;
}

// $ cp-batch BlackOrWhite | diff BlackOrWhite.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BlackOrWhite.cpp && ./a.out

/*
 
 5/9/2019
 
 21:39-22:24 give up
 
 Even manual calculation is wrong.
 Once all the white/black ones consumed, probability does not follow binomial distribution...
 
 5/10/2019
 
 21:15-22:15 read editorials
 
 5/12/2019
 
 15:55-18:10, 19:10-19:45 read editorials and got AC

 https://kamojirobrothers.hatenablog.com/entry/2019/03/31/004856
 http://smijake3.hatenablog.com/entry/2019/04/01/213254
 http://kmjp.hatenablog.jp/entry/2019/04/01/0930
 https://betrue12.hateblo.jp/entry/2019/03/31/095833
 https://img.atcoder.jp/exawizards2019/editorial.pdf
 
 res[i] = probability where i-th is B
 
 There are two cases:
 a) i-th is B (W is not remaining)
 b) i-th is B or W
 
 a) W is used in 1..i-1 th trials
 
 P_b[i]=pw[i-1] where pw[j]: all W is used at 1..j-th
 
   pw[j]
 = 0                          (j<W)
   pw[j-1]+C(j-1,W-1)*(1/2)^j (j>=W)
 
 Similarly...
   pb[j]
 = 0                          (j<B)
   pb[j-1]+C(j-1,B-1)*(1/2)^j (j>=B)

 b) i-th is B or W
 
 P_bw[i]=1-pw[i-1]-pb[i-1]
 
 From a) and b)....

   res[i]
 = P_bw[i]/2 + P_b[i]
 = (1-pw[i-1]-pb[i-1])/2 + pw[i-1]
 
 It's very tough to start the first step.
 In probability problem, we should compute exhaustively.
 If we analyze a situation of i-th `B`, we can decompose to above #a and #b cases.
 
 */

const int MAX_N=1e6+1;
int B,W;

ModInt pw[MAX_N],pb[MAX_N];
void solve() {
  ZERO(pw),ZERO(pb);
  FORE(i,1,W+B) {
    if(i>=W) pw[i]=pw[i-1]+ModInt(choose(i-1,W-1))/(ModInt(2).pow(i));
    if(i>=B) pb[i]=pb[i-1]+ModInt(choose(i-1,B-1))/(ModInt(2).pow(i));
//    dump(i,pw[i-1],pb[i-1]);
    ModInt a=ModInt(1)-pw[i-1]-pb[i-1],b=pw[i-1];
    ModInt res=a/2+b;
    cout<<res<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>B>>W;
  solve();
  
  return 0;
}
