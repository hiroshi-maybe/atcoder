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

// $ cp-batch SuperRyuma | diff SuperRyuma.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SuperRyuma.cpp && ./a.out

/*

 11/22/2020

 21:03-21:31 AC

 https://youtu.be/iWS5WCvMMak?t=697
 https://atcoder.jp/contests/abc184/editorial/339

 https://drken1215.hatenablog.com/entry/2020/11/22/224600

 https://twitter.com/torus711/status/1330506728882880512
 https://twitter.com/satanic0258/status/1330506496942096384
 https://twitter.com/kyopro_friends/status/1330509358921342976
 https://twitter.com/satanic0258/status/1330508417337724928
 https://twitter.com/armeria_betrue/status/1330510249380487172

 */

int r1,c1,r2,c2;
int par(int a, int b) {
  int res=(a+b)%2;
  res+=2;
  res%=2;
  return res;
}
int mv(int r1, int c1, int r2, int c2) {
  int p1=par(r1,c1),p2=par(r2,c2);
  assert(p1==p2);
  if((r1+c1==r2+c2)||(r1-c1==r2-c2)||(abs(r1-r2)+abs(c1-c2)<=3)) {
    return 1;
  } else {
    return 2;
  }
}

int solve() {
  if(r1==r2&&c1==c2) return 0;
  if((r1+c1==r2+c2)||(r1-c1==r2-c2)||(abs(r1-r2)+abs(c1-c2)<=3)) {
    return 1;
  }

  int p1=par(r1,c1),p2=par(r2,c2);
  if(p1==p2) {
    return mv(r1,c1,r2,c2);
  } else {
    int res=3;
    FORE(dr,-3,3)FORE(dc,-3,3) {
      int r=r1+dr,c=c1+dc;
      /*if(r==1&&c==2) {
        dump(r,c);
        dump(p1,(r+c)%2);
        dump(abs(r-r1)+abs(c-c1)>3);
      }*/
      if(par(r,c)==p1) continue;
      if(abs(r-r1)+abs(c-c1)>3) continue;

      //dump(r,c);
      SMIN(res,mv(r,c,r2,c2)+1);
    }

    return res;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>r1>>c1>>r2>>c2;
  cout<<solve()<<endl;

  return 0;
}
