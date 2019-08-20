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
// $ cp-batch Coincidence | diff Coincidence.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Coincidence.cpp && ./a.out

/*
 
 8/18/2019
 
 21:27-22:10 OEIS https://oeis.org/search?q=1%2C2%2C4%2C5%2C7%2C9%2C13%2C14%2C16&language=english&go=Search
 22:40 give up
 
 8/19/2019
 
 21:10-22:15 read editorial
 
 8/20/2019
 
 12:30-13:30, 13:45-16:15 read editorial and got AC
 
 https://youtu.be/lWETOlGiuaI?t=4786
 https://twitter.com/hanseilimak/status/1163655989817556992
 
 Two major steps:
  - y%x==y^x <=> MSB(x)==MSB(y) and bitset(x)⊆bitst(y)
  - implement digit dp considering pair of (x,y)
 
 Both steps were way too hard for me 😞😞😞😞😞😞😞😞😞😞😞😞😞😞😞😞
 
 */

string n2bin(long long n) {
  assert(n>=0);
  string res="";
  while(n>0) res+=(n%2LL?'1':'0'),n/=2LL;
  return string(res.rbegin(), res.rend());
}

LL L,R;

ModInt dp[63][2][2][2];
int ith(LL mask, int i) {
  return (mask>>i)&1;
}
void solve() {
  dp[60][0][0][0]=1;
  for(int i=59; i>=0; --i)REP(more,2)REP(less,2)REP(init,2) {
    /*
    if(init==0) {
      int mm=more,ll=less,in=init;
      
      dp[i][more][less][0]+=dp[i+1][more][less][0];
      LL a=1LL<<i;
//      if(L<=a&&a<=R) {
        int mm=__builtin_clzll(a)!=__builtin_clzll(L);
        int ll=__builtin_clzll(a)!=__builtin_clzll(R);
        dp[i][mm][ll][1]+=dp[i+1][more][less][init];
//      }
     */
      /*
      REP(x,2)REP(y,2) {
        if(x==1&&y==0) continue;
        int mm=more,ll=less,in=init;
        if(in==0&&x!=y) continue;
        if(x==1&&y==1) in=1;
        if(more==0&&ith(L,i)==1&&x==0)continue;
        if(x==1&&ith(L,i)==0) mm=1;
        if(less==0&&y==1&&ith(R,i)==0) continue;
        if(y==0&&ith(R,i)==1) ll=1;
        dp[i][mm][ll][in]+=dp[i+1][more][less][init];
      }*/
    /*
    } else {
      int x1=more?0:ith(L,i);
      int x2=1;
      int y1=0;
      int y2=less?1:ith(R,i);
      FORE(x,x1,x2)FORE(y,y1,y2)if(x<=y) {
        int mm=more|(ith(L,i)<x);
        int ll=less|(y<ith(R,i));
        dp[i][mm][ll][init]+=dp[i+1][more][less][init];
      }
    }*/
    int x1=more?0:ith(L,i);
    int x2=1;
    int y1=0;
    int y2=less?1:ith(R,i);
    FORE(x,x1,x2)FORE(y,y1,y2)if(x<=y) {
      if(init==0&&x!=y) continue;
      int init2=init;
      if(init==0&&x==1&&y==1) init2=1;
      int mm=more|(ith(L,i)<x);
      int ll=less|(y<ith(R,i));
      dp[i][mm][ll][init2]+=dp[i+1][more][less][init];
    }
  }
  ModInt res=0;
  REP(m,2)REP(l,2) {
//    dump(m,l,dp[0][m][l][1]);
    res+=dp[0][m][l][1];
  }
  cout<<res<<endl;
}

void test() {
  set<II> S;
  FORE(r,1,1000) {
    LL res=0;
    FORE(y,1,r) FORE(x,1,y) {
      if((y%x)==(y^x)) {
        ++res;
        S.emplace(x,y);
        assert(__builtin_clz(x)==__builtin_clz(y)&&(y-x)==(y^x));
      }
      if(__builtin_clz(x)==__builtin_clz(y)&&(y-x)==(y^x)) {
        assert((y%x)==(y^x));
      }
//      if(y-x==(y^x)) assert((y%x)==(y^x));
    }
//    dump(r,res);
  }
  /*
  FORR(p,S) {
    int x=p.first,y=p.second,xy=p.first^p.second;
    dump(x,y,xy,n2bin(x),n2bin(y),n2bin(xy));
//    dump(p.first,p.second,p.first^p.second);
  }*/
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>L>>R;
  solve();
  
  return 0;
}
