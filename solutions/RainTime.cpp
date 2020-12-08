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

// $ cp-batch RainTime | diff RainTime.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address RainTime.cpp && ./a.out

/*

 12/8/2020

 15:16-16:09 AC

 https://www.slideshare.net/chokudai/abc001

 */

const int MAX_N=1e6+1;
string S[MAX_N];
int N;

string tos(int m) {
  //dump(m);
  return string(1,'0'+m/10)+string(1,'0'+m%10);
}
int r1(int m) {
  int mm=m/10*10;
  if(m%10>=5) mm+=5;
  return mm;
}
int r2(int m) {
  if(m%10==0) return m;
  int mm=m/10*10;
  if(m%10<=5) mm+=5;
  else mm+=10;
  return mm;
}

void solve() {
  map<int,int> imos;
  REP(i,N) {
    int sh=stoi(S[i].substr(0,2)),sm=stoi(S[i].substr(2,2)),eh=stoi(S[i].substr(5,2)),em=stoi(S[i].substr(7,2));
    int s=sh*60+r1(sm);
    int e=eh*60+r2(em);
    imos[s]+=1,imos[e+1]-=1;
  }
  vector<II> res;
  res.emplace_back(-1,-1);
  int sum=0;
  FORR(kvp,imos) {
    int sum2=sum+kvp.second;
    if(sum==0&&sum2>0) {
      res.back().first=kvp.first;
    }

    if(sum>0&&sum2==0) {
      res.back().second=kvp.first;
      res.emplace_back(-1,-1);
    }
    sum=sum2;
  }
  assert(sum==0);
  if(res.back().first==-1) res.pop_back();
  REP(i,SZ(res)) {
    int s=res[i].first,e=res[i].second;
    --e;
    cout<<tos(s/60)+tos(s%60)<<"-"<<tos(e/60)+tos(e%60)<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>S[i];
  solve();

  return 0;
}
