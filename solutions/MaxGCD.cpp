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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch MaxGCD | diff MaxGCD.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MaxGCD.cpp && ./a.out

/*
 
 8/6/2019
 
 12:36-13:12 RE
 13:24 AC
 
 The result should be one of divisors of ∑ {A[i]}.
 HCN(1e9)≈1000, which means we can brute-force them.
 To achieve `d`, we want to achieve ∀i, A[i]%d=0 by at most `K` operations.
 If # of operation for `d` is at most `K`, result is `d`.
 
 https://img.atcoder.jp/abc136/editorial.pdf
 
 */

vector<LL> divisors(LL N) {
  assert(N>=1);
  vector<LL> res;
  for(LL p=1; p*p<=N; ++p) if(N%p==0) {
    res.push_back(p);
    if(p!=N/p) res.push_back(N/p);
  }
  sort(res.begin(),res.end());
  return res;
}

const int MAX_N=1e6+1;
LL A[MAX_N],K;
int N;

void solve() {
  LL tot=accumulate(A,A+N,0LL);
  vector<LL> D=divisors(tot);
  reverse(ALL(D));
  dumpc(D);
  FORR(d,D) {
    vector<LL> X(N);
    REP(i,N) X[i]=A[i]%d;
    sort(X.rbegin(),X.rend());
    
    if(accumulate(ALL(X),0LL)==0) {
      cout<<d<<endl;
      return;
    }
    
    LL cnt=0;
    int l=0,r=N-1;
    while(l<r) {
      while(X[l]<d) {
        assert(l<r);
        LL x=min(d-X[l],X[r]);
        X[l]+=x,X[r]-=x;
        cnt+=x;
        if(X[r]==0) --r;
      }
      ++l;
    }
    dumpc(X);
    dump(d,cnt,K)
    if(cnt<=K) {
      cout<<d<<endl;
      return;
    }
  }
  cout<<1<<endl;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
vector<int> genRandSeq(int size, int lb, int ub) {
  if (size==0) return {};
  vector<int> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}

void test() {
  N=genRandNum(2,10);
  VI B=genRandSeq(N,1,10);
  K=genRandNum(0,1000);
  REP(i,N) A[i]=B[i];
  dump(N,K);
  dumpc(B);
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>N>>K;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
