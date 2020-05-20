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

 5/19/2020

 9:28-10:00, 9:00-9:46 got AC. But it's incorrect greedy...
 22:00-23:20 read editorial and got AC

 */

//const int MAX_N=1e6+1;
string S,T;
int H,W,N,si,sj;

bool f(string S, string T, int p) {
  dump(p,W);
  dump(S);
  dump(T);
  int cntrT=0;
  REP(i,N) {
    if(S[i]=='R') cntrT++;
  }
  REP(i,N) {
    if(S[i]=='L') --p;
    if(S[i]=='R') cntrT--;
    if(p<=0||p>W) return false;
    if(T[i]=='R'&&p<W) ++p;
    p=min(p,N-cntrT);
    dump(i,p);
    if(p<=0||p>W) return false;
  }
  return true;
}

void swap(string &s, string &t, char x, char y) {
  REP(i,N) {
    if(S[i]==x) S[i]=y;
    else if(S[i]==y) S[i]=x;
    if(T[i]==x) T[i]=y;
    else if(T[i]==y) T[i]=x;
  }
}

bool solve_wrong() {
  VI res;
  res.push_back(f(S,T,sj));
  swap(S,T,'L','R');
  res.push_back(f(S,T,W-sj+1));
  swap(S,T,'L','R');
  swap(S,T,'L','U');
  swap(S,T,'R','D');
  swap(H,W);
  res.push_back(f(S,T,si));
  swap(S,T,'L','R');
  res.push_back(f(S,T,W-si+1));
  dumpc(res);
  bool fall=count(ALL(res),0);
  return !fall;
}

bool g(vector<II> C, int p, int L) {
  int l=1,r=L;
  reverse(ALL(C));
  dumpc(C);
  REP(i,SZ(C)) {
    auto kvp=C[i];
    if(kvp.first) {
      (kvp.second==1?r:l)+=kvp.second;
      l=max(1,l), r=min(L,r);
    } else {
      (kvp.second==1?l:r)+=kvp.second;
    }
    dump(i,kvp.first,kvp.second,l,r);
    if(l>r) return false;
  }
  return l<=p&&p<=r;
}

bool solve() {
  string ss[2]={S,T};
  vector<II> h,v;
  REP(j,N)REP(i,2) {
    int ds[2]={-1,1};
    int delta=(ss[i][j]=='U'||ss[i][j]=='L')?0:1;
    bool vert=ss[i][j]=='U'||ss[i][j]=='D';
    auto &t=vert?v:h;
    t.emplace_back(i,ds[delta^1]);
  }
  bool hres=g(h,sj,W),vres=g(v,si,H);
  if(hres==false||vres==false) return false;
  return true;
}

bool solve_1st() {
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
