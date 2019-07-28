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

// $ cp-batch Golf | diff Golf.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Golf.cpp && ./a.out

/*
 
 7/27/2019
 
 5:24-5:39 give up
 13:40-18:15, 19:15-20:42 read editorials and got AC
 
 There are tons of things to prove. Look at article by @betrue12
 
 https://betrue12.hateblo.jp/entry/2019/07/28/215024
 https://img.atcoder.jp/abc135/editorial.pdf
 https://www.youtube.com/watch?v=brfeRxmzuKw
 https://twitter.com/satanic0258/status/1155112643478208512?s=20
 https://twitter.com/tempura_cpp/status/1155110639926312961?s=20
 https://twitter.com/tempura_cpp/status/1155127166545190912?s=20
 https://twitter.com/kyort0n/status/1155111222489993222?s=20
 https://twitter.com/uwitenpen/status/1155134645362552832?s=20
 https://twitter.com/hanseilimak/status/1155231668631818240
 
 */

LL K;
LL X,Y;

vector<pair<LL,LL>> f() {
  if(K%2==0&&(X+Y)%2==1) {
    cout<<-1<<endl;
    exit(0);
  }
  if(X+Y==K) return {{X,Y}};
  LL n=(X+Y+K-1)/K;
  if(n<=1) ++n;
  if((n*K-X-Y)%2==1) ++n;
//  dump(n);
  vector<pair<LL,LL>> res;
  if(n==3&&X<K) {
    LL a=min((K*3-X-Y)/2-1,K-1),b=(K*3-X-Y)/2-a;
    res.emplace_back(K-a,-a);
    res.emplace_back(X+b,Y-(K-b));
    res.emplace_back(X,Y);
  } else {
    LL a=(n*K-X-Y)/2,d=0;
    while(d+K<=Y+a) {
      d+=K;
      res.emplace_back(0,d);
    }
    while(d+K<=X+Y+a) {
      d+=K;
      LL x=d-(Y+a);
      res.emplace_back(x,Y+a);
    }
    while(d+K<=n*K) {
      d+=K;
      LL dy=d-X-Y-a;
      res.emplace_back(X,Y+a-dy);
    }
  }
  return res;
}

void solve() {
  bool negx=false,negy=false,xyswap=false;
  if(X<0) negx=true,X=-X;
  if(Y<0) negy=true,Y=-Y;
  if(X<Y) xyswap=true,swap(X,Y);
  assert(X>=Y);
  vector<pair<LL,LL>> res=f();
  if(xyswap) FORR(p,res) swap(p.first,p.second);
  if(negx) FORR(p,res) p.first=-p.first;
  if(negy) FORR(p,res) p.second=-p.second;
  println("%d", SZ(res));
  FORR(p,res) println("%lld %lld",p.first,p.second);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>K>>X>>Y;
  solve();
  
  return 0;
}
