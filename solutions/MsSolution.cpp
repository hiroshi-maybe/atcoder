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

// $ cp-batch MsSolution | diff MsSolution.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MsSolution.cpp && ./a.out

/*

 7/25/2020

 5:42-6:45 give up

 10:40-11:40 AC by O(N*3^N) solution with pre-computation

 https://twitter.com/hanseilimak/status/1287100497682300930
 https://img.atcoder.jp/m-solutions2020/editorial.pdf
 https://youtu.be/z6SeLXdwVhA?t=3168
 https://kmjp.hatenablog.jp/entry/2020/07/25/0900

 https://twitter.com/small_onions/status/1287019790905663488
 https://twitter.com/ei1333/status/1287019918517350400
 https://twitter.com/laycrs/status/1287019881729126401
 https://twitter.com/kzyKT_M/status/1287020014680170497
 https://twitter.com/xuzijian629/status/1287021135750553601
 https://twitter.com/satanic0258/status/1287021488659247105
 https://twitter.com/ymatsux_ac/status/1287022973304442880

 */
#define UNIQUE(A) sort((A).begin(),(A).end()),(A).erase(std::unique((A).begin(), (A).end()), (A).end());
const int MAX_N=1e6+1;
LL X[MAX_N],Y[MAX_N],P[MAX_N];
int N;

bool ith(int mask, int i) { return (mask>>i)&1; }
const LL Inf=1e17;
LL f(LL x, vector<LL> &xs) {
  int p=lower_bound(ALL(xs),x)-xs.begin();
  LL res=Inf;
  if(p<SZ(xs)) SMIN(res, abs(xs[p]-x));
  if(p>0) SMIN(res, abs(xs[p-1]-x));
  return res;
}
VV<LL> precomp(vector<LL> &X) {
  VV<LL> xcosts(1<<N,vector<LL>(N,Inf));
  REP(mask,1<<N) {
    vector<LL> xs={0};
    REP(i,N) if(ith(mask,i)) {
      xs.push_back(X[i]);
    }
    sort(ALL(xs));
    REP(i,N) xcosts[mask][i]=f(X[i],xs);
  }
  return xcosts;
}
void solve() {
  vector<LL> xx(X,X+N),yy(Y,Y+N);
  VV<LL> xcosts=precomp(xx),ycosts=precomp(yy);

  vector<LL> res(N+1,Inf);
  int fmask=1;
  REP(_,N) fmask*=3;
  //dump(fmask);
  REP(mask, fmask) {
    int m=mask;
    vector<LL> xs={0},ys={0};
    int cnt=0;
    int xmask=0,ymask=0;
    REP(i,N) {
      int a=m%3; m/=3;
      if(a>0) ++cnt;
      if(a==1) xmask|=1<<i;
      if(a==2) ymask|=1<<i;
    }

    LL cost=0;
    REP(i,N) {
      cost+=min(xcosts[xmask][i],ycosts[ymask][i])*P[i];
    }
    SMIN(res[cnt], cost);
  }
  REP(i,N+1) cout<<res[i]<<endl;
}

void solve_tle() {
  vector<LL> res(N+1,Inf);
  int fmask=1;
  REP(_,N) fmask*=3;
  dump(fmask);
  REP(mask, fmask) {
    int m=mask;
    vector<LL> xs={0},ys={0};
    int cnt=0;
    REP(i,N) {
      int a=m%3; m/=3;
      if(a>0) ++cnt;
      if(a==1) xs.push_back(X[i]);
      if(a==2) ys.push_back(Y[i]);
    }
    UNIQUE(xs); UNIQUE(ys);

    LL cost=0;
    REP(i,N) {
      cost+=min(f(X[i],xs),f(Y[i],ys))*P[i];
    }
    SMIN(res[cnt], cost);
  }
  REP(i,N+1) cout<<res[i]<<endl;
}

void solve_wrong() {
  vector<LL> xs,ys;
  REP(i,N) xs.push_back(X[i]),ys.push_back(Y[i]);
  UNIQUE(xs); UNIQUE(ys);
  REPE(k,N) {
    LL res=Inf;
    REPE(a,min(k,SZ(xs))) {
      int b=min(k-a,SZ(ys));
      REP(mask,1<<a) {
        vector<LL> xsxs={0};
        REP(i,SZ(xs)) if(ith(mask,i)) xsxs.push_back(xs[i]);
        sort(ALL(xsxs));
        vector<LL> xcost(N);
        REP(i,N) {
          int p=lower_bound(ALL(xsxs),X[i])-xsxs.begin();
          xcost[i]=abs(xsxs[p]-X[i])*P[i];
          if(p>0) SMIN(xcost[i],abs(xsxs[p-1]-X[i])*P[i]);
        }

        vector<LL> cost(N);
        REP(i,N) {
          cost[i]=min(xcost[i],abs(Y[i])*P[i]);
        }

        vector<pair<LL,LL>> bonus(N);
        REP(yi,SZ(ys)) {
          vector<LL> cc=cost;
          bonus[yi]={0LL,ys[yi]};
          LL y=ys[yi];
          REP(i,N) {
            cc[i]=min(xcost[i],min(abs(Y[i]),abs(Y[i]-y))*P[i]);
            bonus[i].first+=cost[i]-cc[i];
          }
        }
        sort(ALL(bonus)),reverse(ALL(bonus));

      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>X[i]>>Y[i]>>P[i];
  solve();

  return 0;
}
