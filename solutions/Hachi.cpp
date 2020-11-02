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

// $ cp-batch Hachi | diff Hachi.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Hachi.cpp && ./a.out

/*

 11/1/2020

 4:11-4:20 WA
 4:32 give up

 7:30-8:06 AC after 6WA

 https://twitter.com/hanseilimak/status/1323127201005404160
 https://atcoder.jp/contests/abc181/editorial/259

 */

//const int MAX_N=1e6+1;
int N;
string S;

bool is8div(string s) {
  REP(i,SZ(s)) if(s[i]=='0') return false;
  sort(ALL(s));
  do {
    string x=s;
    int y=stoi(x);
    if(y%8==0) return true;
  } while(next_permutation(ALL(s)));
  return false;
}

bool solve() {
  N=SZ(S);
  VI cnt(10);
  REP(i,N) cnt[S[i]-'0']++;
  FOR(a,1,1000) if(a%8==0) {
    //dump(a);
    string s=to_string(a);
    VI c(10); REP(i,SZ(s)) c[s[i]-'0']++;
    if(c[0]>0) continue;
    if(N<=3) {
      if(c==cnt) return true;
      else continue;
    }
    if(N>3&&a<100) continue;

    bool ok=true;
    FOR(i,1,10) ok&=c[i]<=cnt[i];

    /*if(a==400) {
      dump(a);
      dumpc(c);
      dumpc(cnt);
    }*/

    if(ok) {
      dumpc(c);
      dumpc(cnt);
      dump(a);
      return true;
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;


  FOR(a,1,2000) {
    S=to_string(a);

    if(count(ALL(S),'0')) continue;

    bool act=solve();
    bool exp=is8div(S);
    dump(a,act,exp);
    assert(act==exp);
  }

  cin>>S;
  cout<<(solve()?"Yes":"No")<<endl;

  return 0;
}
