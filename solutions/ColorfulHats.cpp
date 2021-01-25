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

// $ cp-batch ColorfulHats | diff ColorfulHats.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ColorfulHats.cpp && ./a.out

/*

 11/10/2020

 14:35-15:10, 19;45-20:00 pause

 11/11/2020

 2:43-3:00, 15:10-15:50 WA
 15:56 AC

 https://img.atcoder.jp/agc016/editorial.pdf
 https://youtu.be/kdQtQSgIYPI?t=1347

 1/24/2021

 22:02-22:49 WA on test case 13
 23:34 AC

 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N;

bool solve() {
  int maxa=*max_element(A,A+N),mina=*min_element(A,A+N);
  if(maxa==mina) return maxa==N-1||2*maxa<=N;
  if(maxa-mina>1) return false;
  int cntmina=count(A,A+N,mina);
  //dump(maxa,mina,cntmina,N,(maxa-cntmina)*2,N-cntmina);
  return (maxa-cntmina)>0&&(maxa-cntmina)*2<=(N-cntmina);
}

bool solve_v1() {
  sort(A,A+N);
  VI as(A,A+N);
  as.erase(unique(as.begin(),as.end()), as.end());
  if(SZ(as)>2) return false;
  if(SZ(as)==1&&as[0]==N-1) return true;
  if(SZ(as)==2&&as[1]-as[0]>1) return false;
  int cntuniq=SZ(as)==1?0:count(A,A+N,as[0]);
  int C=SZ(as)==1?as[0]:as[1];
  int rem=N-cntuniq;
  if(C-cntuniq<=0) return false;
  return rem>=2*(C-cntuniq);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>A[i];
  cout<<(solve()?"Yes":"No")<<endl;

  return 0;
}
