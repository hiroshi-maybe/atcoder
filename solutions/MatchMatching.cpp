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

// $ cp-batch MatchMatching | diff MatchMatching.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MatchMatching.cpp && ./a.out

/*
 
 2/28/2019
 
 15:42-16:46 WA
 17:00 give up
 17:41 got AC after including `0` in the dp loop. Very stupid conding mistake 😡
 
 Knapsack dp and transition restoration by greedy
 
 http://drken1215.hatenablog.com/entry/2019/02/16/224100
 https://img.atcoder.jp/abc118/editorial.pdf
 
 Key:
  - Knapsack problem with repeated choices
  - Largest integer <=> 1. longest string, 2. lexicographically largest
 
 */

LL cost[10]={0,2,5,5,4,5,6,3,7,6};

const int MAX_N=1e4+1;
int A[10];
int N,M;


int to[10][MAX_N];
int dp[10][MAX_N];
VI ds;
const int Inf=1e5;

int pre[MAX_N];
int memo[MAX_N];

int f(int i) {
  int nex=pre[i];
  int &res=memo[i];
  if(nex>=0) return memo[i];
  if(i==N) return res=0;
  FORR(d,ds) if(i+cost[d]<=N) {
    int l=f(i+cost[d])+1;
    if(l>res) res=l,pre[i]=d;
  }
  return res;
}
void solve() {
  REP(i,M)ds.push_back(A[i]);
  sort(ds.rbegin(),ds.rend());
  MINUS(pre); REP(i,MAX_N)memo[i]=-Inf;
  int L=f(0);
  assert(L>=0);
  
  string res;
  int i=0;
  while(pre[i]!=-1) {
    int d=pre[i];
    res.push_back('0'+d),i+=cost[d];
  }
  cout<<res<<endl;
}

void solve_org() {
  REP(i,M)ds.push_back(A[i]);
  sort(ds.rbegin(),ds.rend());
  MINUS(to);
  REP(i,10)REP(j,MAX_N) dp[i][j]=-Inf;
  dp[M][0]=0;
  for(int j=M-1; j>=0; --j) for(int i=N; i>=0; --i) {
    int d=ds[j],c=cost[d];
    for(int k=i/c; k>=0; --k) {
      int ii=i-k*c;
      assert(ii>=0);
      if(dp[j+1][ii]>=0&&dp[j+1][ii]+k>dp[j][i]) {
        dp[j][i]=dp[j+1][ii]+k;
        to[j][i]=k;
//        dump(j,d,c,i,k,ii,dp[j][i],dp[j+1][ii]);
      }
    }
  }
  string res;
  int i=N;
  REP(j,M) {
    int cnt=to[j][i];
    assert(cnt>=0);
    int d=ds[j];
    string s(cnt,'0'+d);
    res+=s;
    i=i-cnt*cost[d];
  }
  assert(i==0);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,M) cin>>A[i];
  solve();
  
  return 0;
}
