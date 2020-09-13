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
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
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
// $ cp-batch Contrast | diff Contrast.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Contrast.cpp && ./a.out

/*

 9/13/2020

 5:39-6:20 TLE
 6:40 give up

 12:10-13:35 read editorials and got AC with @Tiramister's solution

 https://youtu.be/yLkJZXkB6D0?t=5057
 https://atcoder.jp/contests/abc178/editorial/84

 https://maspypy.com/atcoder-%e5%8f%82%e5%8a%a0%e6%84%9f%e6%83%b3-2020-09-13abc-178
 https://twitter.com/maspy_stars/status/1305140071234859009

 https://tiramistercp.hatenablog.com/entry/abc178-f

 https://twitter.com/heno_code/status/1305140432989372416
 https://twitter.com/small_onions/status/1305139229257732098
 https://twitter.com/laycrs/status/1305139415115735043
 https://twitter.com/ei1333/status/1305139674575302659
 https://twitter.com/ngtkana/status/1305140525759045632
 https://twitter.com/ngtkana/status/1305141121756966918

 swap:
  - https://twitter.com/tomerun/status/1305139434958905345
  - https://twitter.com/masutech_compro/status/1305139922936815624


 */

const int MAX_N=1e6+1;
int A[MAX_N],B[MAX_N];
int N;

void solve() {
  VI rpos(N+1,-1),lpos(N+1,-1);
  REP(i,N) rpos[A[i]]=i;
  for(int i=N-1; i>=0; --i) lpos[B[i]]=i;

  int maxd=0;
  REPE(i,N) if(lpos[i]!=-1&&rpos[i]!=-1) {
    SMAX(maxd, rpos[i]-lpos[i]+1);
  }
  VI res(N);
  REP(i,N) res[(i+maxd)%N]=B[i];

  REP(i,N) if(res[i]==A[i]) {
    cout<<"No"<<endl;
    return;
  }
  cout<<"Yes"<<endl;
  REP(i,N) cout<<res[i]<<" ";
  cout<<endl;
}

void solve_wrong() {
  VI cnt1(N+1),cnt2(N+1);
  REP(i,N) cnt1[A[i]]++,cnt2[B[i]]++;
  REP(i,SZ(cnt1)) {
    int x=min(cnt1[i],cnt2[i]);
    if(2*x>N) {
      cout<<"No"<<endl;
      return;
    }
  }

  VI res(B,B+N);
  while(true) {
    res=shuffle(res);
    bool ok=true;
    REP(i,N) if(A[i]==res[i]) {
      ok=false;
      break;
    }
    if(!ok) continue;
    break;
  }

  cout<<"Yes"<<endl;
  REP(i,N) cout<<res[i]<<" ";
  cout<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>A[i];
  REP(i,N) cin>>B[i];
  solve();

  return 0;
}
