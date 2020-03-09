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

// $ cp-batch DivisibleSubstring | diff DivisibleSubstring.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DivisibleSubstring.cpp && ./a.out

/*
 
 3/8/2020
 
 20:57-21:34 WA
 22:01 TLE
 22:16 give up
 23:11 read editorials and got AC
 
 https://img.atcoder.jp/abc158/editorial.pdf
 https://youtu.be/sv3l8heocMY?t=2794
 https://twitter.com/hanseilimak/status/1236897404789518336
 
 */

int N,P;
string S;

void solve() {
  if (P==2||P==5) {
    LL res=0;
    REP(i,N) if((S[i]-'0')%P==0) {
      res+=i+1;
    }
    cout<<res<<endl;
    return;
  }
  vector<LL> cnt(P,0);
  cnt[0]=1;
  int cur=0;
  LL res=0;
  int pow10=1;
  for(int i=N-1; i>=0; --i) {
    cur=(pow10*(S[i]-'0')+cur)%P;
//    dump(i,cur,cnt[cur])
    res+=cnt[cur];
    cnt[cur]++;
    pow10=pow10*10%P;
  }
  cout<<res<<endl;
}

void solve_tle() {
  unordered_map<int,LL> cnt;
  cnt[0]=1;
  int cur=0;
  LL res=0;
  REP(i,N) {
    cur=(cur*10+S[i]-'0')%P;
//    if(cur==0) res++;
    res+=cnt[cur];
    cnt[cur]++;
    unordered_map<int,LL> cnt2;
    FORR(kvp,cnt) {
      cnt2[kvp.first*10%P]+=kvp.second;
    }
//    dump(i,cur,cnt[cur]);
    swap(cnt,cnt2);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>P>>S;
  solve();
  
  return 0;
}
