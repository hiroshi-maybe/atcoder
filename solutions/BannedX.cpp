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

// $ cp-batch BannedX | diff BannedX.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BannedX.cpp && ./a.out

/*
 
 4/20/2019
 
 6:12-6:18 give up
 
 4/22/2019
 
 21:00-22:00 read editorials
 
 4/23/2019
 
 9:15-13:15 read editorials and got AC
 
 http://kmjp.hatenablog.jp/entry/2019/04/23/0930
  - very simple combinatorics
 http://drken1215.hatenablog.com/entry/2019/04/21/190800
  - combinatorics
 https://betrue12.hateblo.jp/entry/2019/04/21/170538
  - dp
 https://img.atcoder.jp/tenka1-2019/editorial.pdf
 https://youtu.be/uQvc7k2xamY?t=3616
  - combinatorics
 
 It took tons of time to understand sum>X analysis...😞

 Summary:
  - Pay more attention to hand-made examples. It's just a waste of time if wrong 😡
 
 */

const int MAX_N=3000+1;
int N,X;
ModInt dp[MAX_N][2*MAX_N];
void solve() {
  ModInt res(0);
  dp[0][0]=1;
  REP(i,N)REPE(sum,X) {
    // 1
    if(sum+1<2*MAX_N)dp[i+1][sum+1]+=dp[i][sum];
    // 2
    if(sum+2<2*MAX_N)dp[i+1][sum+2]+=dp[i][sum];
  }
  // less than X (n1>0)
  REPE(cnt,N)REPE(sum,X-1) if(N-cnt>=0) res+=dp[cnt][sum]*choose(N,N-cnt);
  for(int y=1; X+y<=2*N; y+=2) {
    if(y+1<X-1) {
      for(int n=1; n+y+1<=N; ++n) {
        res+=dp[n][X-y-2]*choose(N,n+y+1);
      }
    } else if(X%2==1) {
      res+=choose(N,(X+y)/2);
    }
  }
  cout<<res<<endl;
}

void solve_wrong() {
  ModInt dp[MAX_N][2*MAX_N][2];

  ModInt res(0);
  int N2=X%2==0?X/2-1:N;
  REPE(i,N2) res+=ModInt(choose(N,i)); // all 2
  dump(res);
  dp[0][0][0]=1;
  REP(i,N)REPE(sum,X)REP(j,2) {
    // 1
    if(sum+1<2*MAX_N)dp[i+1][sum+1][1]+=dp[i][sum][j];
    // 2
    if(sum+2<2*MAX_N)dp[i+1][sum+2][j]+=dp[i][sum][j];
  }
  dump(res);
  // less than X (n1>0)
  REPE(cnt,N)REPE(sum,X-1) if(N-cnt>=0) res+=dp[cnt][sum][1]*choose(N,N-cnt);
  dump(res);
  
  // more than X (n1>0)
  FORE(i,1,N) REPE(cnt,N) {
    if(2*i+1>=X) continue;
    if(2*i+1+cnt>N) continue;
    int sum=X-2*i-2;
    if(sum<0) continue;
    ModInt a=dp[cnt][sum][0]+dp[cnt][sum][1];
    ModInt b=choose(N,2*i+1+cnt);
    dump(i,cnt,sum,a,b,a*b);
    res+=a*b;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>X;
  solve();
  
  return 0;
}
