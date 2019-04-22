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

// $ cp-batch ThreeColors | diff ThreeColors.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ThreeColors.cpp && ./a.out

/*
 
 4/20/2019
 
 5:13-6:05, 6:20-6:35 give up
 8:20-8:55 read editorials
 
 I tried to go with complement condition: a+b<=c.
 However I didn't figure out S/2<=c...
 
 4/21/2019
 
 18:20-19:15, 21:00-21:40 read editorials and got AC

 https://betrue12.hateblo.jp/entry/2019/04/21/150214
 https://youtu.be/uQvc7k2xamY?t=2327
 https://img.atcoder.jp/tenka1-2019/editorial.pdf
 http://drken1215.hatenablog.com/entry/2019/04/21/021300
 
 Triangle inequality:
  a<=b<=c, a>0,b>0,c>0 and a+b>c
 
 S:=a+b+c then a+b>c <=> S-c>c <=> c<S/2
 Even if we do dp with condition c<S/2, it's hard to count with condition a<=b<=c.
 
 If we look at complement set by c>=S/2, it's easier.
 a<=c and b<=c is satisfied by itself.
 
   res
 = |U|
   - {R>=S/2} - {G>=S/2} - {B>=S/2}
   + {R>=S/2 and G>=S/2} + {G>=S/2 and B>=S/2} + {B>=S/2 and R>=S/2}
   - {R>=S/2 and G>=S/2 and B>=S/2}
 = A - 3*B + 3*C - D
 
 A = |U| = 3^N
 B = |{C>=S/2}| = ∑ {dp[N][x] : x=S/2..N }
 C = |{C0>=S/2 and C1>=S/2}|
   = |{C0=S/2 and C1=S/2}|
   = 0 if S is odd
     dp[N][S/2] if S is even
 D = 0
 
 I spent tons of time due to misunderstanding of dp for `B`.
 We do distinguish how to color not only `c` but also `a` and `b`.
 Thus dp transition is...
 dp1[i+1][j+a]+=dp1[i][j] <= color for `c`
 dp1[i+1][j]+=2*dp1[i][j] <= ⚠️ *2 shows distinguishing color for `a` or `b`
 
 */

const int MAX_N=300+1;
int A[MAX_N];
int N;

ModInt dp1[MAX_N][MAX_N*MAX_N],dp2[MAX_N][MAX_N*MAX_N];
void solve() {
  REPE(i,N)REPE(j,MAX_N*MAX_N) dp1[i][j]=0,dp2[i][j]=0;
  int tot=accumulate(A,A+N,0);
  dp1[0][0]=dp2[0][0]=1;
  REP(i,N)REP(j,MAX_N*MAX_N) {
    int a=A[i];
    dp1[i+1][j+a]+=dp1[i][j];
    dp1[i+1][j]+=dp1[i][j]*2;

    dp2[i+1][j+a]+=dp2[i][j];
    dp2[i+1][j]+=dp2[i][j];
  }
//  dumpC(dp1[N],dp1[N]+7);
  ModInt res=ModInt(3).pow(N);
  ModInt s1,s2;
  FORE(a,(tot+1)/2,tot) {
//    dump(a,dp[N][a]);
    s1+=dp1[N][a];
  }
  s2=tot%2==0?dp2[N][tot/2]:0;
//  dump(tot,res,s1,s2);
  res-=s1*3;
  res+=s2*3;
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
