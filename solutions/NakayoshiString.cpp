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

// $ cp-batch NakayoshiString | diff NakayoshiString.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NakayoshiString.cpp && ./a.out

/*
 
 5/9/2020
 
 22:07-23:03 AC
 
 https://kmjp.hatenablog.jp/entry/2014/08/28/0930
 
 */

//const int MAX_N=1e3+1;
string A,B;
int N;

bool solve() {
  N=SZ(A);
  assert(N>=2);
  map<char,int> acnt,bcnt;
  REP(i,N) acnt[A[i]]++,bcnt[B[i]]++;
  if(acnt!=bcnt) return false;

  map<char,int> cs;
  REP(i,N) cs[A[i]]++;
  bool dup=false;
  FORR(kvp,cs) if(kvp.second>1) dup=true;
  
  if(A==B) {
    if(dup) return true;
    return false;
  }
  
  VI dif;
  REP(i,N) if(A[i]!=B[i]) dif.push_back(i);
  if(SZ(dif)>6) return false;
  VI AA,BB;
  FORR(i,dif) AA.push_back(A[i]-'a'),BB.push_back(B[i]-'a');
  
  int M=SZ(AA);
  assert(M>=2);
  REP(j,M)REP(i,j) {
    swap(AA[i],AA[j]);
    if(AA==BB) return true;
    REP(j,M)REP(i,j) {
      swap(AA[i],AA[j]);
      if(dup&&AA==BB) return true;
      REP(j,M)REP(i,j) {
        swap(AA[i],AA[j]);
        if(AA==BB) return true;
        swap(AA[i],AA[j]);
      }
      swap(AA[i],AA[j]);
    }
    swap(AA[i],AA[j]);
  }
  return false;
  
  /*
  REP(j,N)REP(i,j) {
    swap(A[i],A[j]);
    
    int cnt=0;
    REP(i,N) if(A[i]!=B[i]) {
      ++cnt;
    }
    
    if(cnt==0) return true;
    if(cnt==3) return true;
    if(cnt==4) return true;
    if(cnt==2) {
      map<char,int> cs;
      REP(i,N) cs[A[i]]++;
      FORR(kvp,cs) if(kvp.second>1) return true;
    }
    swap(A[i],A[j]);
  }
  return false;*/
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
  VI AA=genRandSeq(N,0,5),BB=genRandSeq(N,0,5);
  A=string(N,'?'),B=string(N,'?');
  REP(i,N) A[i]='a'+AA[i],B[i]='a'+BB[i];
  
  bool exp=false;
  string s=A,t=B;
  REP(j,N)REP(i,j) {
    swap(s[i],s[j]);
    REP(j,N)REP(i,j) {
      swap(s[i],s[j]);
      REP(j,N)REP(i,j) {
        swap(s[i],s[j]);
        if(s==t) exp=true;
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>A>>B;
  cout<<(solve()?"YES":"NO")<<endl;
  
  return 0;
}
