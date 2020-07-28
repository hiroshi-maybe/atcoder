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
/*

 6/12/2018

 14:00-14:50 AC

 Editorials:
  - http://agc006.contest.atcoder.jp/data/agc/006/editorial.pdf
  - https://youtu.be/VX8cGy7kNTE?t=957
  - https://kimiyuki.net/writeup/algo/atcoder/agc-006-b/
  - http://beet-aizu.hatenablog.com/entry/2016/11/04/001139
  - http://logfiles.hatenablog.com/entry/2016/10/31/181221
  - http://hamko.hatenadiary.jp/entry/2018/01/04/104450

 Key:
  - Force two `X`s at the middle of the array

 Summary:
  - I firstly missed doubled number's win (only N can win in such a case)
  - I found counter-example by myself and got AC

7/27/2020

solve again

9:08-9:26 WA
10:26 AC

 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 14:00-14:50 AC
int N,X;

void solve() {
  if(X==2*N-1||X==1) {
    cout<<"No"<<endl;
    return;
  }
  if(N==2) {
    if(X==2) {
      cout<<"Yes"<<endl;
      cout<<1<<endl<<2<<endl<<3<<endl;
    } else {
      cout<<"No"<<endl;
    }
    return;
  }

  VI res(2*N-1,-1);
  VI viz(2*N);
  auto f=[&](int i, int x) {
    res[i]=x,viz[x]=1;
  };
  f(N-1,X);
  if(X==2) f(N-2,X+1),f(N,X-1),f(N+1,X+2);
  else f(N-2,X-1),f(N,X+1),f(N+1,X-2);

  //dumpc(res);

  int j=0;
  FORE(i,1,2*N-1) if(!viz[i]) {
    //dump(i,j,2*N-1);
    while(j<2*N-1&&res[j]!=-1) ++j;
    f(j,i);
  }
  assert(count(ALL(res),-1)==0);
  cout<<"Yes"<<endl;
  REP(i,2*N-1) cout<<res[i]<<endl;
}
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template <typename Integer>
Integer genRandNum(Integer lb, Integer ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  Integer x = rnd() % (Integer)(ub - lb);
  return x + lb;
}
template <typename Integer>
vector<Integer> shuffle(vector<Integer> &A) {
  int N = A.size();
  vector<Integer> res(N);
  for(int i=0; i<N; ++i) {
    // res[0..i-1] has org[0..i-1]
    res[i] = A[i];
    int r = rnd() % (i+1);
    swap(res[i],res[r]);
  }
  return res;
}
void test() {
  N=genRandNum(10,20);
  VI A(2*N-1); iota(ALL(A),1);
  A=shuffle(A);
  dumpc(A);
  while(SZ(A)>1) {
    VI aa;
    FOR(i,1,SZ(A)-1) {
      int a=A[i-1],b=A[i],c=A[i+1];
      if(a>b) swap(a,b);
      if(b>c) swap(b,c);
      if(a>b) swap(a,b);
      aa.push_back(b);
    }
    A=aa;
    dumpc(A);
  }
  dump(N,A[0]);
  assert(A[0]!=2*N-2);
}

const string yes="Yes",no="No";
const int MAX_N=1e5;
int res[2*MAX_N-1];
int viz[2*MAX_N];
void put(int i, int n) {
  assert(viz[n]==0);
  viz[n]=true;
  res[i]=n;
}

void solve_org() {
  if(X==2*N-1||X==1) {
    cout<<no<<endl;
    return;
  }
  ZERO(viz);
  MINUS(res);
  put(N-1,X);
  if(X==2) {
    put(N,1);
    put(N-2,3);
    put(N+1,4);
  } else {
    put(N,X+1);
    put(N-2,X-1);
    put(N+1,X-2);
  }
  int cur=1;
  REP(i,2*N-1) if(res[i]==-1) {
    while(viz[cur]) ++cur;
    put(i,cur++);
  }
  cout<<yes<<endl;
  REP(i,2*N-1) cout<<res[i]<<endl;
  return;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  cin>>N>>X;
  solve();
  return 0;
}
