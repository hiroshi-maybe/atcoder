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
template<typename integer>
struct ModularLinearEquations {
public:
  ModularLinearEquations() {}
  pair<integer, integer> solve(const vector<integer>& A, const vector<integer>& B,
                       const vector<integer>& M) {
    integer b=0,m=1;
    for(int i=0; i<A.size(); i++) {
      integer p=A[i]*m,q=B[i]-A[i]*b,d=gcd(M[i],p),mi=M[i]/d;
      if (q%d!=0) return make_pair(0,-1); // solution not found
      integer t=(_modinv(p/d,mi)*q/d)%(mi);
      b=b+m*t;
      m*=mi;
    }
    b=(b+m)%m; // ensure that x is non-negative
    return make_pair(b%m,m);
  }

  /*

   compute mod inverse of n, O(lg max(a,m)) time

    - compute x s.t. a*x≡1(mod m)
    - a and m should be co-prime (gcd(a,m)==1)
    - from Ant book 4.1 complex math problems
    - CLRS 31.4 Solving modular linear equations

   a*x≡1(mod m)
   <=> ∃k, a*x=k*m+1
   <=> a*x-k*m=1 // x can be computed by extgcd(a,m)

   Usage:
     int d = modinv(5,11) // d=9

   */
  integer _modinv(integer a, integer m) {
    assert(gcd(a,m)==1);
    integer x,y;
    _extgcd(a,m,x,y);
    return (m+x%m)%m; // ensure mod inverse is non-negative
  }

  /*

   extended GCD, O(lg max(a,b)) time

    - compute (x,y,z) s.t. a*x+b*y=z, z=gcd(a,b)
    - from Ant book 2.6 elementary math techniques
    - CLRS "31.3 Modular arithmetic" and "31.4 Solving modular linear equations"

   Usage:
     int x, y;
     int z = extgcd(99,78,x,y); // (x,y)=(-11,14), z=gcd(99,78)=3

   */
  integer _extgcd(integer a, integer b, integer& x, integer& y) {
    if(b==0) {
      x=1,y=0;
      return a;
    }
    integer d=_extgcd(b, a%b, y, x);
    y-=(a/b)*x;
    return d;
  }
private:
  int gcd(integer a, integer b) {
    return b==0?a:gcd(b,a%b);
  }
};

tuple<LL,LL,LL> extended_euclid(LL a, LL b) {
  if (b==0) return make_tuple(a, 1, 0);

  LL d2,x2,y2;
  tie(d2,x2,y2) = extended_euclid(b, a%b);
  return make_tuple(d2,y2,x2-(a/b)*y2);
}

template<typename integer>
tuple<integer,integer,integer> extended_euclid(integer a, integer b) {
  if (b==0) return make_tuple(a, 1, 0);

  integer d2,x2,y2;
  tie(d2,x2,y2) = extended_euclid(b, a%b);
  return make_tuple(d2,y2,x2-(a/b)*y2);
}

template<typename integer>
pair<integer,integer> crt2(integer a1, integer n1, integer a2, integer n2) {
  integer g,x,y; tie(g,x,y)=extended_euclid(n1,n2);
  if(a1%g!=a2%g) return {0,-1};
  integer lcm=n1/g*n2;

  integer res=a1+(a2-a1)/g*x%(n2/g)*n1;
  res=(res%lcm+lcm)%lcm;

  return {res,lcm};
}


// $ cp-batch Oversleeping | diff Oversleeping.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Oversleeping.cpp && ./a.out

/*

 2/27/2021

 5:18-5:50 give up
 11:25-14:45 read editorials and proof of CRT. Cannot find a bug in my crt2.

 2/28/2021

 9:45-12:10 read CRT articles. figured out overflow and fixed by replacing %lcm with %(n2/gcd) and got AC
 18:20-18:40 watch the editorial video

 https://mathtrain.jp/chinese
 https://mathtrain.jp/remainder
 https://qiita.com/drken/items/ae02240cd1f8edfc86fd

 https://atcoder.jp/contests/abc193/editorial/812
 https://youtu.be/rZG8_snLX5o?t=3387

 https://twitter.com/kzyKT_M/status/1365658182018760707
 https://twitter.com/ajis_ka/status/1365658877614649349
 https://twitter.com/laycrs/status/1365659803188486145
 https://twitter.com/tanakh/status/1365659571616817153
 https://twitter.com/evima0/status/1365658283223093251
 https://twitter.com/kiri8128/status/1365658698991869957
 https://twitter.com/satanic0258/status/1365660780100681731
 https://twitter.com/tanakh/status/1365659000600096776

 */

LL X,Y,P,Q;

const LL Inf=2e18;
void solve() {
  LL res=Inf;
  FOR(x,P,P+Q) FOR(y,X,X+Y) {
    LL t,cycle;
    tie(t,cycle)=crt2((LL)x,P+Q,(LL)y,(X+Y)*2);
    //ModularLinearEquations<LL> mle;
    //tie(t,cycle)=mle.solve({1,1},{x,y},{P+Q,(X+Y)*2});

    if(cycle<0) continue;
    SMIN(res,t);
  }
  if(res==Inf) {
    cout<<"infinity"<<endl;
  } else {
    cout<<res<<endl;
  }
}
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template <typename Integer>
Integer genRandNum(Integer lb, Integer ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  Integer x = rnd() % (Integer)(ub - lb);
  return x + lb;
}
void test() {
  LL ub=1e7;
    LL n1=genRandNum(1LL,ub),n2=genRandNum(1LL,ub),a1=genRandNum(0LL,n1),a2=genRandNum(0LL,n2);
    LL g,x; tie(g,x)=crt2(a1,n1,a2,n2);
    if(g!=1) dump(g,x);
    //dump(a1,a2,n1,n2,g,x);

}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //auto x=crt2(0,2,0,4);
  //dump(x.first,x.second);
  //while(true) test();

  int t; cin>>t;
  while(t--) {
    cin>>X>>Y>>P>>Q;
    solve();
  }

  return 0;
}
