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

 8/9/2018

 14:00-14:25 analysis
 14:51 redesign algorithm
 15:02 1WA and gave up

 18:10-18:42 read editorials and add solution

 Editorials:
  - https://youtu.be/VJntQuR2zNI?t=1988
  - https://img.atcoder.jp/abc075/editorial.pdf
  - https://www.hamayanhamayan.com/entry/2017/10/15/002250
  - http://tatanaideyo.hatenablog.com/entry/2017/10/16/125741
   - O(N^3) solution
  - http://what-alnk.hatenablog.com/entry/2017/10/15/070000

 Left side or right side of rectangle should be picked from N points.
 Top/bottom side should be picked from N points as well.
 We can run N^4 loops to select them.

 |-------------| <- y[i]
 |             |
 |             |
 |-------------| <- y[j]

 ^            ^
 X[i]         X[j]

 We don't need to specify edge points to calculate area.
 What we need to compute area is max/min X and max/min Y.

  area = (max X - min X) * (max Y - min Y)

 Thus selection of X-coordinate and Y-coordinate is independent!!
 It's possible to count number of points inside the rectangle in O(N).
 O(N^5) algorithm should work.

 Key:
  - brute-force
  - we select x-coordinate and y-coordinate independently

 Summary:
  - It's typical that X-coordinate and Y-coordinate are independent
  - I haven't even looked for O(N^5) algorithm...

 5/25/2020

 22:28-23:01 solve again

 */

// $ cp-batch  Axis-ParallelRectangle | diff  Axis-ParallelRectangle.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address  Axis-ParallelRectangle.cpp && ./a.out

const int MAX_N=50+1;
int N,K;
pair<LL,LL> P[MAX_N];

void solve_second() {
  LL res=4e18;
  sort(P,P+N);
  VI xs;
  REP(i,N) xs.push_back(P[i].first);
  sort(ALL(xs)),xs.erase(unique(ALL(xs)), xs.end());
  int M=SZ(xs);
  REP(i,M)FOR(j,i,M) {
    VI ys;
    REP(k,N) if(xs[i]<=P[k].first&&P[k].first<=xs[j]) {
      ys.push_back(P[k].second);
    }
    sort(ALL(ys));
    //dump(xs[i],xs[j]);
    //dumpc(ys);
    int L=SZ(ys);
    LL dx=xs[j]-xs[i];
    REP(k,L-K+1) {
      SMIN(res,dx*(ys[k+K-1]-ys[k]));
    }
  }
  cout<<res<<endl;
}

void solve_wrong() {
  LL res=4e18+10;
  sort(P,P+N);
  REP(i,N) {
    priority_queue<LL> Q1,Q2;
    LL x0,y0; tie(x0,y0)=P[i];
    FOR(j,i,N) {
      LL x,y; tie(x,y)=P[j];
      (y<y0?Q2:Q1).emplace(abs(y0-y));
      if(SZ(Q1)+SZ(Q2)>K) (Q2.empty()||Q1.top()>Q2.top()?Q1:Q2).pop();
      if(SZ(Q1)+SZ(Q2)==K) {
        LL dx=x-x0,dy=(SZ(Q1)?Q1.top():0)+(SZ(Q2)?Q2.top():0);
        SMIN(res,dx*dy);
      }
    }
  }
  cout<<res<<endl;
}

LL X[MAX_N],Y[MAX_N];
void solve() {
  LL res=4e18+10;
  REP(i1,N)REP(i2,N)if(X[i1]<=X[i2])REP(j1,N)REP(j2,N)if(Y[j1]<=Y[j2]) {
    LL x1=X[i1],x2=X[i2],y1=Y[j1],y2=Y[j2];
    int cnt=0;
    REP(i,N) cnt+=(x1<=X[i]&&X[i]<=x2&&y1<=Y[i]&&Y[i]<=y2);
    if(cnt>=K) SMIN(res,(x2-x1)*(y2-y1));
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  cin>>N>>K;
  REP(i,N) {
    LL x,y; cin>>x>>y;
    P[i]={x,y};
    X[i]=x,Y[i]=y;
  }
  solve();
  return 0;
}
