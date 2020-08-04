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

// $ cp-batch PowersOfTwo | diff PowersOfTwo.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PowersOfTwo.cpp && ./a.out

/*

 7/29/2020

 22:08-22:52 pause

 8/4/2020

 9:01-9:32 AC

 https://twitter.com/hanseilimak/status/1290691750688743425
 https://img.atcoder.jp/agc029/editorial.pdf
 https://youtu.be/mRWp91Nkn8A?t=1338

 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N;

void solve() {
  int res=0;
  map<int,VI> ps;
  VI viz(N,0);
  sort(A,A+N);
  REP(i,N) ps[A[i]].push_back(i);
  for(int i=N-1; i>=0; --i) if(!viz[i]) {
    REP(k,31) if(A[i]<(1<<k)) {
      int p2=1<<k,rem=p2-A[i];
      //dump(i,A[i],p2,rem);
      assert(ps[A[i]].back()==i);
      ps[A[i]].pop_back();
      if(ps.count(rem)&&SZ(ps[rem])) {
        res++;
        viz[ps[rem].back()]=1;
        ps[rem].pop_back();
      }
      break;
    }
  }

  cout<<res<<endl;
}

void solve_wrong() {
  LL res=0;
  map<LL,int> cnt;
  REP(i,N) cnt[A[i]]++;
  REP(k,31) {
    LL p2=1LL<<k;
    REP(i,N) if(p2-A[i]>0) {
      LL x=p2-A[i];
      if(A[i]>x) continue;
      if(cnt.count(x)) {
        int ans=0;
        if(x==A[i]) ans=cnt[x]-1;
        else ans=cnt[x];
        dump(x,A[i],p2,ans);
        res+=ans;
      }
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>A[i];
  solve();

  return 0;
}
