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

// $ cp-batch GrandGarden | diff GrandGarden.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address GrandGarden.cpp && ./a.out

/*
 
 2/19/2019
 
 19:35-19:52 AC
 
 https://img.atcoder.jp/abc116/editorial.pdf
 https://misteer.hatenablog.com/entry/ABC116
 
 */

const int MAX_N=1e6+1;
LL H[MAX_N];
int N;

void solve() {
  int res=0;
  int cur=0;
  REP(i,N) {
    if(H[i]>cur) res+=H[i]-cur;
    cur=H[i];
  }
  cout<<res<<endl;
}

// O(N^2) time
void solve_org() {
  int res=0;
  int l=-1;
  queue<II> Q;
  auto sweep=[&]() {
    dumpC(H,H+N);
    REP(i,N) {
      if((i==0&&H[i]>0)||(H[i-1]==0&&H[i]>0)) {
        l=i;
      }
      if((i==N-1&&H[i]>0)||(H[i]>0&&H[i+1]==0)) {
        dump(l,i);
        if(l!=-1) Q.emplace(l,i+1),l=-1;
      }
    }
  };
  sweep();
  while(SZ(Q)) {
    int t=SZ(Q);
    while(t--) {
      int l,r; tie(l,r)=Q.front(); Q.pop();
      int x=*min_element(H+l,H+r);
      dump(l,r,x);
      assert(x>0);
      res+=x;
      FOR(i,l,r) H[i]-=x;
    }
    sweep();
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>H[i];
  solve();
  
  return 0;
}
