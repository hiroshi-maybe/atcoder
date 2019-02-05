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

// $ cp-batch DifferentStrokes | diff DifferentStrokes.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DifferentStrokes.cpp && ./a.out

/*
 
 2/4/2019
 
 17:23-17:57 WA
 19:06 give up
 
 It seemed to be hard without greedy approach.
 Sorted A and B independently and tried to take max A or max B so far. However it hit WA.
 
 2/5/2019
 
 14:20-15:40 read editorials and add solution
 
 https://img.atcoder.jp/nikkei2019-qual/editorial.pdf
 https://youtu.be/x5x2Xg_gVWY?t=1872
 https://www.hamayanhamayan.com/entry/2019/02/02/000029
 http://kazune-lab.net/contest/2019/01/27/nikkei2019-qual/#c---different-strokes
 https://hewla.hatenablog.com/entry/2019/01/27/231056
 https://betrue12.hateblo.jp/entry/2019/01/28/215129

 I had an idea of formula transformation. However I had no idea how to change it.
 It's not easy to process two independent parameters in single evaluation function.
 Transform evaluation function so that single criteria (parameter) is shared by both.
 
 Summary:
  - I should have observed small test case A0,A1,B0,B1 not with a,b,c,d so that relation gets clear
  - Formally define evaluation function if sort or greedy approach is plausible
  - sort by something <=> observe formula and transform it
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N][2];
int N;

void solve() {
  vector<pair<LL,LL>> X;
  REP(i,N) X.emplace_back(A[i][0],A[i][1]);
  sort(X.rbegin(),X.rend(), [&](pair<LL,LL> a, pair<LL,LL> b) {
    return a.first+a.second<b.first+b.second;
  });
  LL Y[2]={0};
  REP(i,N) Y[i%2]+=(i%2==0?X[i].first:X[i].second);
  cout<<Y[0]-Y[1]<<endl;
}

void solve_wrong() {
  set<pair<LL,int>> Q[2];
  REP(i,N) REP(j,2) Q[j].emplace(A[i][j],i);
  int t=0;
  LL sum[2]={0};
  auto rem=[&](int i) {
//    dump(i);
    REP(t,2) Q[t].erase({A[i][t],i});
  };
  while(SZ(Q[0])||SZ(Q[1])) {
    int tt=t^1;
//    dump(t,tt);
    if(SZ(Q[t])==0) break;
    LL v1=0,v2=0; int i1=-1,i2=-1;
    tie(v1,i1)=*Q[t].rbegin();
    if(SZ(Q[tt])<N) tie(v2,i2)=*Q[tt].rbegin();
    if(i1==i2||i2==-1) {
      sum[t]+=v1,rem(i1);
    } else {
      LL a=v1-v2,b=A[i2][t]-A[i1][tt];
      if(a>=b) sum[t]+=A[i1][t],rem(i1);
      else sum[t]+=A[i2][t],rem(i2);
    }
    t^=1;
  }
  cout<<sum[0]-sum[1]<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i][0]>>A[i][1];
  solve();
  
  return 0;
}
