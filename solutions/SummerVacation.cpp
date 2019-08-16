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

// $ cp-batch SummerVacation | diff SummerVacation.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SummerVacation.cpp && ./a.out

/*
 
 8/15/2019
 
 14:19-15:19 give up
 17:15-17:35 read editorials and got AC
 
 https://www.youtube.com/watch?v=1Z6ofKN03_Y
 https://twitter.com/nabesan_go/status/1160185148605788162
 https://scrapbox.io/ganariya/AtCoderBeginnerContest137_D%E5%95%8F%E9%A1%8C400%E7%82%B9_%E3%80%8CSummer_Vacation%E3%80%8D
 https://kenkoooo.hatenablog.com/entry/2019/08/11/023455
 http://soto-ohuton.hatenablog.com/entry/2019/08/10/230026
 
 */

const int MAX_N=1e6+1;
int A[MAX_N],B[MAX_N];
int N,M;

VI D[MAX_N];
void solve() {
  REP(i,N) D[A[i]].push_back(i);
  LL res=0;
  priority_queue<int> Q;
  for(int i=M; i>=0; --i) {
    FORR(j,D[M-i]) Q.emplace(B[j]);
    if(SZ(Q)) {
//      dump(Q.top());
      res+=Q.top(), Q.pop();
    }
  }
  cout<<res<<endl;
}

void solve_wrong() {
  vector<tuple<int,int,int>> X;
  REP(i,N) X.emplace_back(A[i]+B[i],B[i],A[i]);
  sort(ALL(X)),reverse(ALL(X));
  LL res=0;
  REP(i,N) {
    int d,v; tie(ignore,v,d)=X[i];
//    dump(d,v);
    if(i+d<=M) res+=v;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,N) cin>>A[i]>>B[i];
  solve();
  
  return 0;
}
