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

// $ cp-batch Camelcase | diff Camelcase.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Camelcase.cpp && ./a.out

/*

 7/2/2020

 15:43-16:10 WA
 16:24 AC

 */

string S;

int pr(string &S) {
  reverse(ALL(S));
  int res=0;
  while(SZ(S)&&S.back()=='_') ++res,S.pop_back();
  return res;
}
string solve() {
  if(count(ALL(S),'_')==SZ(S)) return S;
  string s=S;
  int pref=pr(s);
  int suf=pr(s);

  dump(pref,s,suf);
  assert(SZ(s));

  if(!islower(s[0])) return S;

  if(count(ALL(s),'_')) {
    vector<string> ws={""};
    REP(i,SZ(s)) {
      if(isupper(s[i])) return S;
      if(s[i]=='_') ws.push_back("");
      else ws.back().push_back(s[i]);
    }
    bool ok=true;
    FORR(w,ws) if(w.empty()||!islower(w[0])) ok=false;
    if(!ok) return S;
    FORR(w,ws) w[0]=toupper(w[0]);
    ws[0][0]=tolower(ws[0][0]);
    string res(pref,'_');
    FORR(w,ws) res+=w;
    res+=string(suf,'_');
    return res;
  } else {
    vector<string> ws={""};
    REP(i,SZ(s)) {
      if(isupper(s[i])) ws.push_back(""),s[i]=tolower(s[i]);
      ws.back().push_back(s[i]);
    }
    dumpc(ws);
    string res(pref,'_');
    FORR(w,ws) res+=w,res.push_back('_');
    if(res.back()=='_') res.pop_back();
    res+=string(suf,'_');
    return res;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>S;
  cout<<solve()<<endl;

  return 0;
}
