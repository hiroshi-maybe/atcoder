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

// $ cp-batch AB | diff AB.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address AB.cpp && ./a.out

/*

 11/21/2020

 22:04-22:42 give up

 11/22/2020

 13:50-17:00 read editorials and got AC

 https://twitter.com/hanseilimak/status/1330405607539691521
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.yype7povttps

 https://youtu.be/s4r2AJRagjs?t=1513
 https://atcoder.jp/contests/arc108/editorial/347

 https://twitter.com/camypaper/status/1330145552303067137
 https://twitter.com/camypaper/status/1330144573478277121

 https://twitter.com/tsutaj/status/1330144196523601921
 https://twitter.com/gzlcp/status/1330144910511644673
 https://twitter.com/kiri8128/status/1330145282579976199
 https://twitter.com/maspy_stars/status/1330145476797210626
 https://twitter.com/hotpepsi/status/1330145879412584453
 https://twitter.com/satanic0258/status/1330145323830964225
 https://twitter.com/beet_aizu/status/1330144689396310019
 https://twitter.com/kyopro_friends/status/1330148004783910919
 https://twitter.com/kiri8128/status/1330154435062927362
 https://twitter.com/Rubikun_pro/status/1330153883193274373

 */

const int MAX_N=1e3+10;
char C[4];
int N;

int AB=1,AA=0,BA=2,BB=3;
ModInt dp[MAX_N][2];
char inv(char c) {
  int cur=c-'A';
  cur=1-cur;
  return 'A'+cur;
}
ModInt solve() {
  if(N==2) return 1;
  if(C[AB]=='B') {

    C[AB]='A',C[BA]=inv(C[BA]);
    swap(C[BB],C[AA]);
    C[AA]=inv(C[AA]),C[BB]=inv(C[BB]);
  }
  //dumpC(C,C+4);
  assert(C[AB]=='A');

  if(C[AA]=='A') return 1;
  if(C[BA]=='B') return ModInt(2).pow(N-3);
  else {
    ZERO(dp);
    dp[0][0]=1;
    REP(i,N)REP(c,2) {
      if(c==0) dp[i+1][0]+=dp[i][c],dp[i+1][1]+=dp[i][c];
      else dp[i+1][0]+=dp[i][c];
    }
    return dp[N-1][1];
  }
}

ModInt memo[MAX_N][MAX_N][2][2];
int viz[MAX_N][MAX_N][2][2];
ModInt f(int l, int r, int lc, int rc) {
  if(viz[l][r][lc][rc]) return memo[l][r][lc][rc];
  viz[l][r][lc][rc]=1;
  ModInt res=memo[l][r][lc][rc];
  if(r==l+1||r==l+2) return res=1;

  int newc=C[(1<<lc)+rc]-'A';
  res=f(l+1,r,newc,rc)+f(l,r-1,lc,newc);
  //dump(l,r,lc,rc,res);
  return res;
}

void solve_wrong() {
  ZERO(viz);
  cout<<f(0,N-1,0,1)<<endl;
}

void test() {
  N=5;
  REP(mask,1<<4) {
    REP(i,4) C[i]=(char)('A'+((mask>>i)&1));

    set<string> S;
    auto f=[&](auto &&self, string &s) {
      if(SZ(s)==N) {
        S.emplace(s);
        return;
      }
      REP(i,SZ(s)-1) {
        int j=(s[i]-'A')*2+s[i+1]-'A';
        assert(j<4);
        string t=s.substr(0,i+1)+string(1,C[j])+s.substr(i+1);
        self(self,t);
      }
    };
    string base="AB";
    f(f,base);
    dumpC(C,C+4);
    dump(SZ(S));

    ModInt act=solve(); int exp=SZ(S);
    dump(N);
    dumpC(C,C+4);
    dump(act,exp);
    assert(act.val==exp);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //while(true) test();

  cin>>N;
  REP(i,4) cin>>C[i];
  cout<<solve()<<endl;

  return 0;
}
