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
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ' '; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch Triangles | diff Triangles.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Triangles.cpp && ./a.out

/*
 
 10/19/2019
 
 5:08-5:31 WA
 5:40 WA
 6:04 AC
 
 */

const int MAX_N=2e3+1;
LL L[MAX_N];
int N;

//const int Inf=1e4;
LL solve() {
  LL res=0;
  sort(L,L+N);
//  VI U(L,L+N);
//  U.erase(std::unique(U.begin(), U.end()), U.end());
//  dumpc(U);
//  set<II> S;
  REP(j,N)REP(i,j) if(j<N-1) {
//    if(S.count({L[i],L[j]})) continue;
    LL ab=L[i]+L[j];
    int ub=lower_bound(L,L+N,ab)-L;
    int lb=j+1;
//    if(L[lb]==L[i]) lb+=1;
//    if(L[lb]==L[j]) lb+=1;
    res+=max(0,ub-lb);
//    dump(i,j,ab,lb,ub);
//    S.emplace(L[i],L[j]);
  }
  return res;
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
  N=10;
  VI A=genRandSeq(N,1,10);
  REP(i,N)L[i]=A[i];
  
  int exp=0;
  sort(ALL(A));
  REP(k,N)REP(j,k)REP(i,j) {
    int a=A[i],b=A[j],c=A[k];
    if(a+b>c&&c+a>b&&b+c>a) {
        ++exp;
      dump(i,j,k,a,b,c);
    }
  }
  LL act=solve();
  if(exp!=act) {
    dump(N);
    dumpc(A);
    dump(exp,act);
/*    FORR(x,exp) {
      int a,b,c; tie(a,b,c)=x;
      printf("%d %d %d,",a,b,c);
    }*/
  }
  assert(exp==act);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>N;
  REP(i,N) cin>>L[i];
  cout<<solve()<<endl;;
  
  return 0;
}
