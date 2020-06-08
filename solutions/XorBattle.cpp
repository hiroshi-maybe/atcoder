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

// $ cp-batch XorBattle | diff XorBattle.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address XorBattle.cpp && ./a.out
template<class T> void gf2_GE(vector<T>& V) {
  // gaussian elimination in GF(2)
  int N=V.size();
  for(int i=0; i<N; ++i) {
    sort(V.begin()+i,V.end(),greater<T>());
    if(V[i]==0) break;
    T msb=1;
    while((msb<<1)<=V[i]) msb<<=1;
    for(int j=i+1; j<N; ++j) if(V[j]&msb) V[j]^=V[i];
  }
}
template<class T> int gf2_rank(vector<T>& V) {
  gf2_GE<T>(V);
  return (int)V.size()-count(V.begin(),V.end(),0);
}
/*

 6/7/2020

 5:00-7:10 give up

 16:00-18:15, 21:50-23:40 read editorial and got AC

 https://twitter.com/hanseilimak/status/1269799620579692549
 https://img.atcoder.jp/agc045/editorial.pdf

 https://twitter.com/satanic0258/status/1269638393975107587
 https://twitter.com/satanic0258/status/1269654741346217984
 https://twitter.com/chokudai/status/1269662729712750592
 https://twitter.com/ngtkana/status/1269638258486464513
 https://twitter.com/noshi91/status/1269660771086041088
 https://twitter.com/kyort0n/status/1269712783852986368

 */

const int MAX_N=1e3+1;
LL A[MAX_N];
int N;
string S;

int solve() {
  vector<LL> V(1,0);
  for(int i=N-1; i>=0; --i) {
    if(S[i]=='0') {
      V.push_back(A[i]);
      gf2_GE(V);
    } else {
      int rank=gf2_rank(V);
      V.push_back(A[i]);
      int rank2=gf2_rank(V);
      if(rank2>rank) return 1;
    }
  }
  return 0;
}

VI s;
int memo[MAX_N][1<<5];

int f(int i, int cur) {
  int &res=memo[i][cur];
  if(res>=0) return res;
  if(i==N) {
    return cur!=0;
  }

  bool res1=f(i+1,cur);
  bool res2=f(i+1,cur^A[i]);

  if(s[i]==0) {
    res=(!res1||!res2)?false:true;
  } else {
    res=(res1||res2);
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
string n2bin(long long n) {
  assert(n>=0);
  string res="";
  while(n>0) res+=(n%2LL?'1':'0'),n/=2LL;
  return string(res.rbegin(), res.rend());
}
void test() {
  N=8;
  VI as=genRandSeq(N,1,1<<3);
  s=genRandSeq(N,0,2);
  vector<II> states(N);
  REP(i,N) states[i]={s[i],as[i]};
  sort(ALL(states));

  VI ress;
  do {
    MINUS(memo);
    REP(i,N) A[i]=states[i].second,s[i]=states[i].first;
    bool res=f(0,0);
    if(!res){
      vector<pair<int,string>> xs;
      FORR(p,states) xs.emplace_back(p.first,n2bin(p.second));
      dumpc(xs);
    }
    ress.push_back(res);
  } while(next_permutation(ALL(states)));

  set<int> S;
  FORR(s,ress) S.emplace(s);
  int ands[2]={(1<<N)-1,(1<<N)-1},ors[2]={0,0};
  FORR(p,states) ands[p.first]&=p.second,ors[p.first]|=p.second;
  if(SZ(S)==2) {
    dump(n2bin(ands[0]^ors[0]),n2bin(ands[1]^ors[1]));
    dumpc(ress);
    dumpc(states);
  }
  assert(SZ(S)==1);

  dumpc(ress);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //while(true) test();

  int t; cin>>t;
  while(t--) {
    cin>>N;
    REP(i,N) cin>>A[i];
    cin>>S;
    cout<<solve()<<endl;
  }

  return 0;
}
