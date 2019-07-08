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

// $ cp-batch RemainderMinimization2019 | diff RemainderMinimization2019.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address RemainderMinimization2019.cpp && ./a.out

/*
 
 7/7/2019
 
 5:07-5:28 AC
 
 https://img.atcoder.jp/abc133/editorial.pdf
 
 I went through unnecessarily complex staff by focuding on 0<=a*b<2019.
 I should have focused on 0<=a%2019<2019 and 0<=b%2019<2019.
 
 */

LL L,R;

void solve() {
  LL res=2019;
  if(R-L>=5000) res=0;
  else {
    FORE(a,L,R)FOR(b,L,a) SMIN(res,(LL)a*b%2019);
  }
  cout<<res<<endl;
}

LL f(LL x) {
  if(x<0) return 0;
  return x/2019+1;
}
void solve_org() {
  map<LL,LL> cnt;
  REP(r,2019) {
    LL x=f(R-r)-f(L-1-r);
    if(x>0)cnt[r]=x;
  }
//  dumpc(cnt);
  map<LL,vector<pair<LL,LL>>> pairs;
  REP(a,2019) pairs[a*a%2019].emplace_back(a,a);
  REP(b,2019)REP(a,b) pairs[a*b%2019].emplace_back(a,b);
  LL res=-1;
  FORR(kvp,pairs) FORR(p,kvp.second) {
    LL a,b; tie(a,b)=p;
    if(cnt.count(a)==0||cnt.count(b)==0) continue;
    cnt[a]--,cnt[b]--;
    if(cnt[a]>=0&&cnt[b]>=0) {
      res=kvp.first;
      goto fin;
    }
    cnt[a]++,cnt[b]++;
  }
fin:
  assert(res!=-1);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>L>>R;
  solve();
  
  return 0;
}
