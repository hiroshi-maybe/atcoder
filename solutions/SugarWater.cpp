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
// $ cp-batch SugarWater | diff SugarWater.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SugarWater.cpp && ./a.out

/*
 
 3/29/2020
 
 16:55-17:18 WA
 17:41 AC
 
 */

LL A,B,C,D,E,F;

void solve() {
  LL ress=0,rest=100*A;
  Frac res(0);
  REPE(p,30)REPE(q,30)REPE(r,1000)REPE(s,1000) {
    LL maxsugar = (A*p+B*q)*E;
//    LL s=(maxsugar-C*r)/D;
//    if(s<0) continue;
    LL water=100*A*p+100*B*q,sugar=C*r+D*s;
    if(sugar>maxsugar) continue;
    LL tot=water+sugar;
    if(tot>F) continue;
    if(tot==0) continue;
    Frac x(sugar,sugar+water);
    if(res<x) {
      res=x,ress=sugar,rest=tot;
    }
  }
  cout<<rest<<" "<<ress<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>A>>B>>C>>D>>E>>F;
  solve();
  
  return 0;
}
