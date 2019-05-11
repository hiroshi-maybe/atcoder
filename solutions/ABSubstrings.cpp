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

// $ cp-batch ABSubstrings | diff ABSubstrings.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ABSubstrings.cpp && ./a.out

/*
 
 5/11/2019
 
 5:25-5:35 WA
 6:06 AC
 
 https://img.atcoder.jp/diverta2019/editorial.pdf
 http://drken1215.hatenablog.com/entry/2019/05/12/002400
 
 It's optimal to put B**A in the middle.
 
 */

const int MAX_N=1e4+1;
string S[MAX_N];
int N;

int solve() {
  int res=0;
  REP(i,N)REP(j,SZ(S[i])-1) if(S[i][j]=='A'&&S[i][j+1]=='B') ++res;
  int A=0,B=0,BA=0;
  REP(i,N) {
    bool x=S[i].back()=='A',y=S[i].front()=='B';
    if(x&&y) ++BA;
    else if(x)++A;
    else if(y)++B;
  }
//  dump(res,A,B,BA);
  if(BA) {
    res+=BA-1;
    if(A!=0||B!=0)B++,A++;
  }
  res+=min(A,B);
  
  /*
  while(A) {
    if(B) --A,--B,++res;
    else if(BA) --BA,++res;
    else break;
  }
  while(B) {
    if(A) --B,--A,++res;
    else if(BA) --BA,++res;
    else break;
  }
  if(BA) res+=BA-1;*/
  /*
  int a=min(A,B);
  A-=a,B-=a;
  int b=0;
  if(A) {
    b=min(A,BA);
    A-=b,BA-=b;
  } else if(B) {
    b=min(B,BA);
    B-=b,BA-=b;
  }
  int c=0;
  if(BA) c+=BA-1;
  dump(res,A,B,BA,a,b,c);
  res+=a+b+c;*/
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
  N=8;
  REP(i,N) {
    int len=genRandNum(1,3);
    VI A=genRandSeq(len,0,2);
    S[i]=string(len,'?');
    REP(j,len) S[i][j]=A[j]?'A':'B';
  }
  
  int a=solve();
  
  VI perm(N); REP(i,N) perm[i]=i;
  int res=0;
  do {
    string s;
    REP(i,N) s+=S[perm[i]];
    int ans=0;
    REP(i,SZ(s)-1) ans+=s[i]=='A'&&s[i+1]=='B';
    SMAX(res,ans);
  }while(next_permutation(ALL(perm)));
  if(a!=res) {
    dump(a,res);
    dumpC(S,S+N);
  }
  assert(a==res);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true)test();
  
  cin>>N;
  REP(i,N) cin>>S[i];
  cout<<solve()<<endl;;
  
  return 0;
}
