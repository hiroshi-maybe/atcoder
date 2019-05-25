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

// $ cp-batch XORMatching | diff XORMatching.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address XORMatching.cpp && ./a.out

/*
 
 5/19/2019
 
 5:48-6:45 WA
 
 5/25/2019
 
 11:10-12:00 I figured out my original solution had a bug of implementation...
 
 https://img.atcoder.jp/abc126/editorial.pdf
 http://kmjp.hatenablog.jp/entry/2019/05/19/0930
 http://drken1215.hatenablog.com/entry/2019/05/19/230600
 
 */

int M,K;

void solve_v2() {
//  dump(M,K);
  VI res;
  if(K>=(1<<M)) res.push_back(-1);
  else if(M==1&&K==0) res={0,0,1,1};
  else if(M==1&&K==1) res.push_back(-1);
  else {
    for(int i=(1<<M)-1; i>=0; --i) if(i!=K)res.push_back(i);
    res.push_back(K);
    REP(i,1<<M) if(i!=K)res.push_back(i);
    res.push_back(K);
  }
  
  if(res!=VI(1,-1)) {
    VV<int> ps(1<<M);
    REP(i,SZ(res)) ps[res[i]].push_back(i);
    VI cum((1<<(M+1))+1);
    REP(i,SZ(res)) cum[i+1]=cum[i]^res[i];
    REP(a,1<<M) {
      assert(SZ(ps[a])==2);
      assert((cum[ps[a][1]]^cum[ps[a][0]+1])==K);
    }
    assert(SZ(res)==1<<(M+1));
  }
  
  REP(i,SZ(res)) printf("%d ",res[i]);
  println("");
}

void solve() {
  VI res;
  if(K==0) {
    REP(i,1<<M) res.push_back(i);
    for(int i=(1<<M)-1; i>=0; --i) res.push_back(i);
  } else {
    
    int x=0;
    REP(i,1<<M) if(i!=K) x^=i;
    
    if(x==K) {
      res.push_back(K);
      // WA due to implementation bug...
//      REP(i,1<<M) if(i!=K)res.push_back(i);
      for(int i=(1<<M)-1; i>=0; --i) if(i!=K)res.push_back(i);
      res.push_back(K);
      REP(i,1<<M) if(i!=K)res.push_back(i);
    } else {
      res.push_back(-1);
    }
  }
  REP(i,SZ(res)) printf("%d ",res[i]);
  println("");
}

void test() {
  REP(k,10)REP(m,5) K=k,M=m,solve();
}

void test_old() {
  FORE(m,0,2) FOR(k,0,1<<(m+1)) {
    int N=1<<(m+1);
    VI A(N);
    REP(i,SZ(A)) A[i]=i%(1<<m);
    sort(ALL(A));
//    dumpc(A);
    do {
      MAPII P;
      VI cum(N+1,0);
      REP(i,N) cum[i+1]=cum[i]^A[i];
      bool ok=true;
      REP(i,N) {
        if(P.count(A[i])==0) P[A[i]]=i;
        else {
          int p=P[A[i]];
          int x=0;
          FORE(j,p,i) x^=A[j];
          ok&=(cum[i+1]^cum[p])==k;
//          ok&=(x==k);
        }
      }
      if(k!=0&&ok&&A[0]==k) {
        dump(m,k);
        dumpc(A);
      }
    } while(next_permutation(ALL(A)));
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  test();
  
  cin>>M>>K;
  solve();
  
  return 0;
}
