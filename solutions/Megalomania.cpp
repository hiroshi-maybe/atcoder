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

// $ cp-batch Megalomania | diff Megalomania.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Megalomania.cpp && ./a.out

/*
 
 6/22/2019
 
 5:18-5:41 WA
 5:49 AC
 
 My original idea by sorting B[i]-A[i] is wrong.
 Suppose we have optimal sequence S_k and my original algorithm gives T_k.
 
 Suppose both S_k and T_k have the same set.
 However S_k is giving `a` as next one while T_k is giving `b`.
 
 tot + A[a]        <= B[a]
 tot + A[a] + A[b] <= B[b] where tot = ∑{A[i] : i∈T_k}
 B[b]-A[b] <= B[a]-A[a] holds
 
 i) B[b] <= B[a]
 
 T_k is taking `b` next.
 tot + A[b] < tot + A[a] + A[b] <= B[b] <= B[a]
 `b` and `a` satisfies ∑{A[i] : i∈T_k} < B[T_k.last]
 
 ii) B[a] < B[b]
 
 tot + A[b] <= tot + A[a] + A[b] <= B[b]. Thus `b` is ok.
 For `a` coming up next, tot + A[a] + A[b] <= B[a] is the proposition we want to prove.
   B[a] - (tot + A[a] + A[b])
 = (B[a] - A[a]) - tot - A[b]
 >= (B[b] - A[b]) - tot - A[b]
 = (B[b] - tot - A[b]) - A[b]
 >= A[a] - A[b]
 
 Thus tot + A[a] + A[b] > B[a] if A[a]-A[b]<0. Our algorithm does not give optimal result (counter example).
 
 Condition that we are trying to hold is ∑{A[i] : i∈S} <= B[S.back()]
 
 This condition implies that processing smaller B[i] gives us optimal algorithm.
 
 Suppose we sort by B[i] and process items with smaller B[i] and get sequence T_k.
 Also we have one of optimal sequence S_k.
 
 From S_k..
   tot + A[a]        <= B[a]
   tot + A[a] + A[b] <= B[b]
 From T_k..
   B[b] <= B[a]
 
 tot + B[b] <= tot + A[a] + A[b] <= B[b]. Thus `b` is ok.
 Also tot + A[a] + A[b] <= B[b] <= B[a]. Thus `a` is ok, too.
 This means T_k is not worse than S_k. T_k gives optimal solution.
 
 https://img.atcoder.jp/abc131/editorial.pdf
 http://drken1215.hatenablog.com/entry/2019/06/22/224800
 https://twitter.com/drken1215/status/1142442953211699201
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N], B[MAX_N];
int N;

void nope() {
  println("No");
  exit(0);
}
void solve() {
  vector<pair<LL,int>> X;
  REP(i,N) X.emplace_back(B[i], i);
  sort(ALL(X));
  LL t=0;
  REP(i,N) {
    int j=X[i].second;
    t=t+A[j];
//    dump(j,t,A[j],B[j]);
    if(t>B[j]) nope();
  }
  println("Yes");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i]>>B[i];
  solve();
  
  return 0;
}
