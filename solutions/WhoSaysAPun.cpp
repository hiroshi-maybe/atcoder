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

namespace RollingHash {
  template<int MOD> struct ModInt {
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
  };
  const int MOD0=1e9+7,MOD1=1e9+9;
  using M0=ModInt<MOD0>;
  using M1=ModInt<MOD1>;
  M0 p0=rand()%MOD0,pinv0=p0.inv();
  M1 p1=rand()%MOD1,pinv1=p1.inv();
  vector<M0> P0{1}, PINV0{1};
  vector<M1> P1{1}, PINV1{1};
  struct H {
    vector<pair<M0,M1>> hcum;
    string str;
    H(string s) : str(s) {
      int N=(int)s.size();
      while ((int)P0.size()<=N) {
        P0.push_back(P0.back()*p0);
        PINV0.push_back(PINV0.back()*pinv0);
        P1.push_back(P1.back()*p1);
        PINV1.push_back(PINV1.back()*pinv1);
      }
      hcum.resize(N+1);
      hcum[0]={M0(0),M1(0)};
      for(int i=0; i<N; ++i) {
        hcum[i+1]={hcum[i].first+M0(s[i])*P0[i],hcum[i].second+M1(s[i])*P1[i]};
      }
    }
    // half-open range [l,r)
    pair<M0,M1> hash(int r) {
      assert(0<=r&&r<hcum.size());
      return { hcum[r].first, hcum[r].second };
    }
    pair<M0,M1> hash(int l, int r) {
      assert(0<=l&&l<hcum.size()),assert(0<=r&&r<hcum.size());
      return {
        (hcum[r].first-hcum[l].first)*PINV0[l],
        (hcum[r].second-hcum[l].second)*PINV1[l]
      };
    }
  };
}

// $ cp-batch WhoSaysAPun | diff WhoSaysAPun.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address WhoSaysAPun.cpp && ./a.out

/*
 
 9/15/2019
 
 5:33-5:49,6:10-6:36 AC
 
 https://img.atcoder.jp/abc141/editorial.pdf
 http://drken1215.hatenablog.com/entry/2019/09/16/014600
 
 https://twitter.com/tempura_cpp/status/1173230007402975232?s=20
 https://twitter.com/drken1215/status/1173230175649071104?s=20
 https://twitter.com/satanic0258/status/1173230218191896576
 
 */

int N;
string S;

void solve() {
  RollingHash::H hash(S);
  auto ok=[&](int len)->bool {
    map<pair<unsigned int,unsigned int>,int> M;
    for(int i=0; i+len<=N; ++i) {
      auto h=hash.hash(i,i+len);
      pair<unsigned int,unsigned int> p={h.first.val,h.second.val};
      if(M.count(p)) {
        int j=M[p];
        if(j+len<=i) return true;
      } else {
        M[p]=i;
      }
    }
    return false;
  };
  int good=0,bad=1e6;
  while(abs(good-bad)>1) {
    int mid=(good+bad)/2;
    bool res=ok(mid);
    (res?good:bad)=mid;
  }
  cout<<good<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>S;
  solve();
  
  return 0;
}
