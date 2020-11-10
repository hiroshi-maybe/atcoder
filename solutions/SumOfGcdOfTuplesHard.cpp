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
//#define __KUMATRACE__ true
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

// $ cp-batch SumOfGcdOfTuplesHard | diff SumOfGcdOfTuplesHard.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SumOfGcdOfTuplesHard.cpp && ./a.out

/*

 4/12/2020

 5:25-6:24 AC

 https://img.atcoder.jp/abc162/editorial.pdf

 11/10/2020

 solve again

 */
const int MAX_N=1e6;
int N,K;

ModInt dp[MAX_N];
void solve() {
  for(int x=K; x>=1; --x) {
    int cnt=K/x;
    ModInt a=ModInt(cnt).pow(N);
    FORE(c,2,cnt) {
      a-=dp[c*x];
    }
    dp[x]=a;
  }

  ModInt res=0;
  FORE(x,1,K) res+=dp[x]*x;
  cout<<res<<endl;
}

LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }
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
void solve_org() {
  vector<LL> ds=divisors(K);
  reverse(ALL(ds));
  ModInt res=0;
  map<LL,ModInt> cnts;
//  ModInt tot=0;
  for(LL k=K; k>=1; --k) {
    ModInt sum=0;
    for(LL p=2; k*p<=K; p++) {
      sum+=cnts[k*p];
    }
    cnts[k]=ModInt(K/k).pow(N)-sum;
//    tot+=cnts[k];
    res+=cnts[k]*k;
    dump(k,cnts[k]);
  }
  cout<<res<<endl;
/*
//  dump(tot);
  REP(i,SZ(ds)) {
    LL d=ds[i];
    ModInt sum=0,muls=1;
    for(LL p=2; d*p<=K; p++) {
      sum+=cnts[d*p];
      muls+=1;
    }
    ModInt cnt=ModInt(muls).pow(N);
    res+=(cnt-sum)*d;
    cnts[d]=cnt-sum;
    dump(d,muls,cnt,sum,cnt-sum,res);
  }
  cout<<res<<endl;*/
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  /*
  int res=0;
  map<LL,int> cnt;
  FORE(a,1,12)FORE(b,1,12) {
    res+=gcd(a,b);
    cnt[gcd(a,b)]++;
  }
  dumpc(cnt);
  dump(res);*/

  cin>>N>>K;
  solve();

  return 0;
}
