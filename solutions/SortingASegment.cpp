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

// $ cp-batch SortingASegment | diff SortingASegment.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SortingASegment.cpp && ./a.out

/*

 12/13/2020

 20:46-20:56 pause

 12/14/2020

 10:20-10:45, 17:10-17:15 WA
 20:10-21:00 WA

 12/15/2020

 16:40-17:36 AC after fixin the last bug

 https://img.atcoder.jp/agc038/editorial.pdf
 https://youtu.be/RXYksUjlPD4?t=2027
 https://maspypy.com/atcoder-%E5%8F%82%E5%8A%A0%E6%84%9F%E6%83%B3-2019-09-21agc-038#toc2
 https://betrue12.hateblo.jp/entry/2019/09/22/004049

 */

const int MAX_N=1e6+1;
int P[MAX_N];
int N,K;

int solve() {
  set<int> S;
  deque<int> Q;
  auto add=[&](int i) {
    while(SZ(Q)&&Q.back()>P[i]) Q.pop_back();
    Q.emplace_back(P[i]);
  };
  REP(i,K) add(i),S.emplace(P[i]);
  int cnt=SZ(Q)==K,res=1;
  FOR(i,K,N) {
    if(Q.front()==P[i-K]) Q.pop_front();
    add(i);
    cnt+=SZ(Q)==K;
    dumpc(Q);
    bool dup=(SZ(Q)==K)&&(cnt>1);
    dump(i,dup);

    bool a=(P[i-K]==*S.begin());
    S.erase(P[i-K]);
    S.emplace(P[i]);

    if(dup) continue;

    bool b=P[i]==*S.rbegin();
    bool dif=!(a&&b);
    if(dif) res+=1;
    //if(SZ(Q)==K&&cnt>1&&dif) res-=1;
    dump(i,a,b,dif,cnt,res);
  }

  dump(cnt);

  //assert(res>0);
  return res;
}

void solve_wrong() {
  set<int> S;
  REP(i,K) S.emplace(P[i]);

  int res=1;
  FOR(i,K,N) {
    bool a=(P[i-K]==*S.begin());
    S.erase(P[i-K]);
    S.emplace(P[i]);
    bool b=P[i]==*S.rbegin();
    dump(i,a,b);
    res+=!(a&&b);
  }
  cout<<res<<endl;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template <typename Integer>
Integer genRandNum(Integer lb, Integer ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  Integer x = rnd() % (Integer)(ub - lb);
  return x + lb;
}
void test() {
  N=5;
  FORE(k,2,N) {
    K=k;
    REP(i,N) P[i]=i;
    do {
      int act=solve();
      set<VI> S;
      REPE(s,N-K) {
        VI ps(P,P+N);
        sort(ps.begin()+s,ps.begin()+s+K);
        S.emplace(ps);
      }

      int exp=SZ(S);
      cout<<N<<" "<<K<<endl;
      REP(i,N) cout<<P[i]<<" ";
      cout<<endl;

      //FORR(a,S) dumpc(a);
      dump(exp,act);
      assert(exp==act);

    } while(next_permutation(P,P+N));

  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //while(true) test();

  cin>>N>>K;
  REP(i,N) cin>>P[i];
  cout<<solve()<<endl;

  return 0;
}
