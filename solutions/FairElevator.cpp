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

// $ cp-batch FairElevator | diff FairElevator.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address FairElevator.cpp && ./a.out

/*

 10/3/2020

 5:13-5:49, 6:05-7:00 give up

 11:35-12:31 Read @kmjp's editorial and got AC
 12:32-12:57 Watch editorial video

 https://twitter.com/hanseilimak/status/1312431706159243264

 https://kmjp.hatenablog.jp/entry/2020/10/04/0900
 https://youtu.be/xYO1qBL61ew?t=808
 https://atcoder.jp/contests/arc104/editorial/158

 https://twitter.com/kzyKT_M/status/1312392205508648961
 https://twitter.com/tsutaj/status/1312392297577771008
 https://twitter.com/Rubikun_pro/status/1312392702554632192
 https://twitter.com/ngtkana/status/1312393473140555777

 */

const int MAX_N=1e2+1;
int N,A[MAX_N],B[MAX_N];

bool solve() {
  VI cnt(2*N);
  REP(i,N) if(B[i]>=0&&A[i]>B[i]) return false;
  REP(i,N) {
    if(A[i]>=0) cnt[A[i]]++;
    if(B[i]>=0) cnt[B[i]]++;
  }
  REP(i,2*N) if(cnt[i]>1) return false;

  const int Inf=1e9;
  VI sts(2*N,Inf),ends(2*N,Inf);
  int wc=0;
  REP(i,N) {
    if(A[i]>=0) sts[A[i]]=B[i];
    if(B[i]>=0) ends[B[i]]=A[i];
    if(A[i]==-1&&B[i]==-1) wc++;
  }
  //dumpc(sts);
  //dumpc(ends);

  VI viz(N,0);
  VV<int> memo(2*N+1,VI(2*N+1,-1));
  auto f=[&](auto &&self, int s, int wc) -> int {
    if(s==2*N) return true;
    int &res=memo[s][wc];
    if(res>=0) return res;
    res=false;
    FORE(L,1,N) {
      int curw=wc;
      bool ok=true;
      REP(o,L) {
        int l=s+o,r=l+L;
        if(r>=2*N) {
          ok=false;
          break;
        }
        if(sts[l]<Inf) {
          ok&=(sts[l]==-1)|(sts[l]==r);
        } else if(ends[r]<Inf) ok&=(ends[r]==l)||(ends[r]==-1);
        else curw--;
        //dump(s,wc,L,o,l,r,curw,ok);
      }
      ok&=(curw>=0);
      //dump(s,wc,curw,L,res,ok);
      if(ok) res|=self(self,s+2*L,curw);
    }
    return res;
  };

  return f(f,0,wc);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) {
    cin>>A[i]>>B[i];
    if(A[i]>0)A[i]--;
    if(B[i]>0)B[i]--;
  }
  cout<<(solve()?"Yes":"No")<<endl;

  return 0;
}
