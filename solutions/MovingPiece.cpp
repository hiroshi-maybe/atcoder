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

// $ cp-batch MovingPiece | diff MovingPiece.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MovingPiece.cpp && ./a.out

/*

 8/15/2020

 5:20-5:57 WA
 6:16 give up

 11:30-12:30 AC
 13:50-14:35 Look at editorials and add simpler solution

 https://twitter.com/hanseilimak/status/1294741197169164290
 https://youtu.be/auQRcs5JMwE?t=2312
 https://atcoder.jp/contests/abc175/editorial/53

 */

const int MAX_N=5000+1;
LL K,P[MAX_N],C[MAX_N];
int N;

LL const Inf=2e18;

LL f(int st) {
  int p=st;
  vector<LL> cs;
  while(true) {
    cs.push_back(C[p]);
    p=P[p];
    if(p==st) break;
  }
  LL csum=accumulate(ALL(cs),0LL);
  int M=SZ(cs);
  LL cur=0,res=-Inf;
  REP(i,M) {
    cur+=cs[i];
    //dump(cur,i+1,K);
    SMAX(res,cur);
    if(i+1==K) return res;
    LL rem=K-(i+1);
    rem/=M;
    SMAX(res,cur+rem*csum);
  }
  return res;
}

LL f_org(int st) {
  VI viz(N,0);
  LL cur=0,res=-Inf;
  vector<pair<LL,int>> xs;
  int p=st;

  auto go=[&](int i) {
    viz[i]=1,xs.emplace_back(cur,p);
  };

  go(p);
  while(true) {
    p=P[p];
    bool hasviz=viz[p];
    cur+=C[p],go(p);
    dump(p,cur,C[p]);
    if(SZ(xs)<=K+1) SMAX(res,cur);
    if(hasviz) break;
  }

  dump(st,K,cur,p,res);
  dumpc(xs);

  if(SZ(xs)>=K+1) return res;

  int loopst=xs.back().second, i2=SZ(xs)-1;
  int i1=-1;
  REP(i,SZ(xs)) if(xs[i].second==loopst) {
    i1=i;
    break;
  }
  assert(i1!=-1);
  assert(i1!=i2);

  LL cycle=i2-i1;
  LL rem=K-(SZ(xs)-1);

  if(rem>cycle) {
    LL delta=xs[i2].first-xs[i1].first;
    LL cyclet = rem/cycle-1;
    LL cycler = rem%cycle+cycle;
    dump(st,i1,i2,cur,rem,cycle,cyclet,cycler);
    cur+=cyclet*delta,p=loopst;
    rem-=cyclet*cycle;
  }

  SMAX(res,cur);
  dump(p,cur,res);
  while(rem--) {
    p=P[p],cur+=C[p];
    dump(p,cur,res);
    SMAX(res,cur);
  }
  return res;
}
LL solve() {
  LL res=-Inf;
  REP(i,N) {
    LL a=f(i);
    dump(i,a);
    SMAX(res,a);
  }
  return res;
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
vector<Integer> genRandSeq(int size, Integer lb, Integer ub) {
  if (size==0) return {};
  vector<Integer> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}
// tested at https://github.com/hiroshi-maybe/leetcode/blob/master/384-Shuffle-an-Array/ShuffleArray.cpp
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
  N=genRandNum(2,10);
  K=genRandNum(1,10);
  VI ps(N); iota(ALL(ps),0);
  ps=shuffle(ps);
  REP(i,N) P[i]=ps[i];
  VI cs=genRandSeq(N,0,10);
  REP(i,N) {
    if(genRandNum(0,2)) cs[i]=-cs[i];
    C[i]=cs[i];
  }

  cout<<N<<" "<<K<<endl;
  REP(i,N) cout<<P[i]+1<<" ";
  cout<<endl;
  REP(i,N) cout<<C[i]<<" ";
  cout<<endl;

  LL act=solve();

  LL exp=-Inf;
  int st,kk;
  REP(i,N) {
    int p=i;
    LL cur=0;
    int k=K;
    while(k--) {
      p=P[p];
      cur+=C[p];
      if(exp<cur) st=i,kk=k,SMAX(exp,cur);
    }
  }
  dump(act,exp,st,kk);
  assert(act==exp);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //while(true) test();

  cin>>N>>K;
  REP(i,N) cin>>P[i],P[i]--;
  REP(i,N) cin>>C[i];
  cout<<solve()<<endl;

  return 0;
}
