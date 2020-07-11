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
template<class T> using VVV=vector<VV<T>>;
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

// $ cp-batch CamelTrain | diff CamelTrain.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address CamelTrain.cpp && ./a.out

/*

 7/11/2020

 6:03-6:40 give up
 14:25-15:53 read editorial and got AC
 16:38 add proof in https://twitter.com/hanseilimak/status/1282071734888230913

 https://img.atcoder.jp/aising2020/editorial.pdf

 https://twitter.com/Rubikun_pro/status/1281950249494343682
 https://twitter.com/small_onions/status/1281946717705756683
 https://twitter.com/satanic0258/status/1281950548955066370
 https://twitter.com/kzyKT_M/status/1281946505604001793
 https://twitter.com/tomerun/status/1281947039476011014
 https://twitter.com/ajis_ka/status/1281946922559795200
 https://twitter.com/tsutaj/status/1281946796487348226
 https://twitter.com/laycrs/status/1281947414354485249
 https://twitter.com/camypaper/status/1281948324048723973
 https://twitter.com/maspy_stars/status/1281949260162846720
 https://twitter.com/kyopro_friends/status/1281950431237660673
 https://twitter.com/tanakh/status/1281950796083429377

 */

const int MAX_N=1e6+1;
int K[MAX_N];
LL L[MAX_N],R[MAX_N];
int N;

void solve() {
  LL res=0;
  VV<int> xs(2);
  VVV<int> ps(2,VV<int>(N+1));
  REP(i,N) {
    res+=min(L[i],R[i]);
    if(L[i]>=R[i]) xs[0].push_back(i),ps[0][K[i]].push_back(i);
    else {
      xs[1].push_back(i);
      if(N-K[i]-2>=0) ps[1][N-K[i]-2].push_back(i);
    }
  }

  REP(i,2) {
    priority_queue<LL> Q;
    for(int j=N; j>=0; --j) {
      FORR(k,ps[i][j]) Q.emplace(abs(L[k]-R[k]));
      if(j<SZ(xs[i])&&SZ(Q)) {
        res+=Q.top(),Q.pop();
      }
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N;
    REP(i,N) cin>>K[i]>>L[i]>>R[i],K[i]--;
    solve();
  }

  return 0;
}
