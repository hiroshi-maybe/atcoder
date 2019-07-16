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

// $ cp-batch LRUDGame | diff LRUDGame.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address LRUDGame.cpp && ./a.out

/*
 
 7/16/2019
 
 9:03-9:50 give up
 11:50-13:55 read editorials
 14:30-15:50 read editorials and got AC
 
 https://img.atcoder.jp/agc033/editorial.pdf
 https://atcoder.jp/contests/exawizards2019/tasks/exawizards2019_c
 https://betrue12.hateblo.jp/entry/2019/05/14/222544
 http://drken1215.hatenablog.com/entry/2019/05/07/000200
 
 Basic idea comes from game dp. Naiive dp exceeds TL.
 Thus we want to skip computation.
 One property of this problem is that WIN of P2 state stays in some consecutive range because of monotonic property.
 
 The base case of dp is...
 
 0123....W{W+1}
 LWWW....WL
 
 Left boundary or right boundary changes at most 1 in each step.
 P1 wants to minimize `W` range while P2 wants to maximize `W` range.
 Thus state transition in backward goes as below:
 
 P1 L
 
 LLW...WL (l+1,r)
 LWW...WL (l,r)

 P1 R
 
 LW...WLL (l,r-1)
 LW...WWL (l,r)

 P2 L
 
 LW...WWL (l,r+1)
 LW...WLL (l,r)
 
 P2 R
 
 LWW...WL (l-1,r)
 LLW...WL (l,r)
 
 If we get LL....LL at some moment, P2 never wins.
 
 */

//const int MAX_N=1e6+1;
string S,T;
int H,W,N,si,sj;

bool solve() {
  int minx=1,maxx=W,miny=1,maxy=H;
  for(int i=N-1; i>=0; --i) {
    if(i<N-1) {
      if(T[i]=='U') ++maxy;
      if(T[i]=='D') --miny;
      if(T[i]=='L') ++maxx;
      if(T[i]=='R') --minx;
    }
    
    minx=max(1,minx);
    miny=max(1,miny);
    maxx=min(W,maxx);
    maxy=min(H,maxy);

    if(S[i]=='U') ++miny;
    if(S[i]=='D') --maxy;
    if(S[i]=='L') ++minx;
    if(S[i]=='R') --maxx;
    
    if(minx>maxx) return false;
    if(miny>maxy) return false;
  }
  
  if(sj<minx||sj>maxx) return false;
  if(si<miny||si>maxy) return false;
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>H>>W>>N>>si>>sj>>S>>T;
  cout<<(solve()?"YES":"NO")<<endl;
  
  return 0;
}
