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

// $ cp-batch \>\< | diff \>\<.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Stringstring.cpp && ./a.out

/*
 
 11/3/2019
 
 7:00-7:17 WA
 7:22 AC
 
 https://img.atcoder.jp/agc040/editorial.pdf
 
 */

int N;
string S;

void solve() {
  N=SZ(S);
  vector<pair<char,LL>> A;
  REP(i,N) {
    if(i==0||A.back().first!=S[i]) A.emplace_back(S[i],0);
    A.back().second++;
  }
  LL res=0;
  int M=SZ(A);
  REP(i,M) {
    if(i==0&&A[0].first=='>') res+=A[0].second*(A[0].second+1)/2;
    else if(i==M-1&&A[M-1].first=='<') res+=A[M-1].second*(A[M-1].second+1)/2;
    else if(i<M-1&&A[i].first=='<'&&A[i+1].first=='>') {
      LL l=A[i].second,r=A[i+1].second;
      res+=l*(l-1)/2+r*(r-1)/2+max(l,r);
    }
  }
  cout<<res<<endl;
}

//const int Inf=1e8;
void solve_org() {
  N=SZ(S);
  VI A(N+1,-1);
  queue<int> Q;
  REP(i,N) {
    if(i==0&&S[i]=='<') {
      Q.emplace(i),A[i]=0;
    } else if(i==N-1&&S[i]=='>') {
      Q.emplace(i+1),A[i+1]=0;
    } else if(S[i]=='>'&&S[i+1]=='<') {
       Q.emplace(i+1),A[i+1]=0;
    }
  }
  dump(SZ(Q));
  while(SZ(Q)) {
    int i=Q.front(); Q.pop();
    int a=A[i];
    if(i>0&&S[i-1]=='>') {
      SMAX(A[i-1],a+1),Q.push(i-1);
    }
    if(i<N&&S[i]=='<') {
      SMAX(A[i+1],a+1),Q.push(i+1);
    }
  }
//    dumpc(A);
  assert(count(ALL(A),-1)==0);

  LL res=accumulate(ALL(A),0LL);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>S;
  solve();
  
  return 0;
}
