#include <bits/stdc++.h>
using namespace std;
// type alias
typedef long long LL;
typedef pair<LL,LL> II;
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
#define __KUMATRACE__ false
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
// $ cp-batch TwoContests | diff TwoContests.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TwoContests.cpp && ./a.out

/*
 
 11/3/2019
 
 7:22-8:49 AC
 
 https://img.atcoder.jp/agc040/editorial.pdf
 https://betrue12.hateblo.jp/entry/2019/11/04/051835
 
 */

//const int MAX_N=1e6+1;
vector<II> P;
int N;

LL f(VI A) {
  LL l=P[A[0]].first,r=P[A[0]].second;
  FORR(i,A) SMAX(l,P[i].first),SMIN(r,P[i].second);
  return max(r-l,0LL);
}

LL solve() {
  sort(ALL(P),[&](const II &l, const II &r) {
    if(l.second!=r.second) return l.second<r.second;
    return l.first<r.first;
  });
//  dumpc(P);
  LL maxl=0; int maxi=0;
  REP(i,N) if(P[i].second-P[i].first>maxl) {
    SMAX(maxl,P[i].second-P[i].first);
    maxi=i;
  }
    
  VI SS; REP(i,N)if(i!=maxi) SS.push_back(i);
  LL res=maxl+f(SS);
  
  vector<II> left(N+1),right(N+1);
  left[0]={-1,1e10},right[N]={-1,1e10};
  FOR(i,1,N) left[i]={max(left[i-1].first,P[i-1].first),min(left[i-1].second,P[i-1].second)};
  for(int i=N-1; i>=0; --i) right[i]={max(right[i+1].first,P[i].first),min(right[i+1].second,P[i].second)};

  FOR(i,1,N) {
    LL l=max(0LL,left[i].second-left[i].first),r=max(0LL,right[i].second-right[i].first);
//    dump(i,l+r);
//    dump(left[i].first,left[i].second,right[i].first,right[i].second);
    SMAX(res,l+r);
  }
  return res;
}

void show(VI is) {
  FORR(i,is) {
    string S(30,' ');
    FOR(j,P[i].first,P[i].second) S[j]='*';
    dump(S);
  }
}

LL solve_() {
  sort(ALL(P),[&](const II &l, const II &r) {
    if(l.second!=r.second) return l.second<r.second;
    return l.first<r.first;
  });
  dumpc(P);
  int res=0;
  VI AA,BB;
  FOR(mask,1,(1<<N)-1) {
    VI A,B;
    REP(i,N){
      if((mask>>i)&1) A.push_back(i);
      else B.push_back(i);
    }
    int ans=f(A)+f(B);
//    int ans=0;
    if(ans>res) res=ans,AA=A,BB=B;
  }
  dumpc(AA);
  dumpc(BB);
  show(AA);
  dump(res);
  show(BB);
  return res;
}

void test() {
  N=10;
  P=vector<II>(N);
  REP(i,N) {
    int l=genRandNum(0,19),r=genRandNum(l+1,20);
    P[i]={l,r};
  }
  LL act=solve_(),exp=solve();
  assert(act==exp);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  /*
  while(true) {
    test();
  }*/
  
  cin>>N;
  P=vector<II>(N);
  REP(i,N) {
    int l,r; cin>>l>>r;
    --l;
    P[i]={l,r};
  }
  cout<<solve()<<endl;
  
  return 0;
}
