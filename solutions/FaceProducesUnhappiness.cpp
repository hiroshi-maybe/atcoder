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

// $ cp-batch FaceProducesUnhappiness | diff FaceProducesUnhappiness.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address FaceProducesUnhappiness.cpp && ./a.out

/*
 
 9/7/2019
 
 5:15-6:02 AC
 
 It took tons of time to reduce problem condition to minimize # of boundaries...
 Maximize continuous elements <=> Minimize # of boundaries
 
 In one operation, at most 2 scores increase. If it's doable, just do it. It's optimal.
 It's optimal sequence of operations if individual decision is optimal (greedy).
 
 https://youtu.be/VSeggcnxwrc?t=3544
 https://img.atcoder.jp/abc140/editorial.pdf
 
 */

//const int MAX_N=1e6+1;
int N,K;
string S;

int f_wrong(char c) {
  string T=S;
  vector<II> xs;
  REP(i,N) if(T[i]!=c) {
    if(i==0||T[i-1]!=T[i]) xs.emplace_back(0,i);
    if(xs.back().first==0) xs.back().first++;
    if(i!=N-1)xs.back().first+=1;
  }
  sort(ALL(xs)),reverse(ALL(xs));
  dumpc(xs);
  REP(i,min(SZ(xs),K)) {
    auto p=xs[i];
    int j=p.second;
    assert(T[j]!=c);
    while(j<N&&T[j]!=c) T[j++]=c;
  }
  int res=0;
  dump(c,T);
  REP(i,N-1) res+=T[i+1]==T[i];
  return res;
}
int f(char c) {
  string T=S;
  int cnt=0;
  REP(i,N-1) if(T[i]!=T[i+1]) ++cnt;
  if(T[N-1]!=c) ++cnt;
  cnt-=2*K;
  cnt=max(0,cnt);
  return N-1-cnt;
}
void solve() {
  int res=max(f('L'),f('R'));
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>K>>S;
  solve();
  
  return 0;
}
