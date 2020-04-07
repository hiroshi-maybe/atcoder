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

// $ cp-batch Tenka1LIFODataStructure | diff Tenka1LIFODataStructure.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Tenka1LIFODataStructure.cpp && ./a.out

/*
 
 4/7/2020
 
 9:16-9:32 AC
 
 https://tenka1.klab.jp/2013/explain/b_b.html
 
 */

LL L;
LL sz=0;
stack<pair<int,LL>> S;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int Q; cin>>Q>>L;
  while(Q--) {
    string cmd; cin>>cmd;
    if(cmd=="Size") {
      cout<<sz<<endl;
    } else if(cmd=="Top") {
      if(sz==0) {
        cout<<"EMPTY"<<endl;
        return 0;
      }
      cout<<S.top().first<<endl;
    } else if(cmd=="Push") {
      LL cnt; int a; cin>>cnt>>a;
      if(S.empty()||S.top().first!=a) S.emplace(a,0LL);
      S.top().second+=cnt;
      sz+=cnt;
      if(sz>L) {
        cout<<"FULL"<<endl;
        return 0;
      }
    } else if(cmd=="Pop") {
      LL cnt; cin>>cnt;
      if(cnt>sz) {
        cout<<"EMPTY"<<endl;
        return 0;
      }
      while(cnt>0) {
        LL a=min(cnt,S.top().second);
        cnt-=a,S.top().second-=a,sz-=a;
        if(S.top().second==0) S.pop();
      }
    }
  }
  cout<<"SAFE"<<endl;
  
  return 0;
}
