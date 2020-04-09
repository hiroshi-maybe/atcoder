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

// $ cp-batch RenkinJyutsushi | diff RenkinJyutsushi.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address RenkinJyutsushi.cpp && ./a.out

/*
 
 4/9/2020
 
 8:49-9:27 AC
 
 https://www.slideshare.net/chokudai/codefestival2014qual-b
 http://kmjp.hatenablog.jp/entry/2014/10/27/0900
 
 */

string S1,S2,S3;

void nope() {
  cout<<"NO"<<endl;
  exit(0);
}
void solve() {
  int N=SZ(S1);
  map<int,int> cnt1,cnt2,cnt3;
  REP(i,N) cnt1[S1[i]-'A']++,cnt2[S2[i]-'A']++,cnt3[S3[i]-'A']++;
  int l1=0,r1=0,l2=0,r2=0;
  FORR(kvp,cnt3) {
    int key=kvp.first;
    int c=kvp.second,a=cnt1[key],b=cnt2[key];
    int lb1=max(0,c-b),hb1=min(c,a);
    if(lb1>hb1) nope();
    l1+=lb1,r1+=hb1;
    int lb2=max(0,c-a),hb2=min(c,b);
    if(lb2>hb2) nope();
    l2+=lb2,r2+=hb2;
  }
  int half=N/2;
  if(half<l1||half>r1) nope();
  if(half<l2||half>r2) nope();
  cout<<"YES"<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>S1>>S2>>S3;
  solve();
  
  return 0;
}
