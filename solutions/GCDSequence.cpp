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

// $ cp-batch GCDSequence | diff GCDSequence.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address GCDSequence.cpp && ./a.out

/*

 2/4/2021

 8:35-8:45 pause

 2/28/2021

 22:30-23:00 give up

 5/1/2021

 24:10-25:35 read editorial and got AC

 https://img.atcoder.jp/agc022/editorial.pdf
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.1ctw8bp5qwib

 */

vector<int> sieve(int N) {
  assert(N>=1);
  vector<int> fs(N+1, true);
  fs[0]=fs[1]=false;
  for(long long p=2; p*p<=N; ++p) if(fs[p]) {
    for(long long q=p*p; q<=N; q+=p) fs[q]=false;
  }
  vector<int> res;
  for(int n=2; n<=N; ++n) if(fs[n]) res.push_back(n);
  return res;
}

int N;

void solve() {
  //VI ps=sieve(30000);
  //dump(SZ(ps));
  VI res;
  if(N==3) {
    res={2,5,63};
  } else if(N==4) {
    res={2,5,20,63};
  } else if(N==5) {
    res={2,5,20,30,63};
  } else {
    VV<int> xs(6);
    FORE(n,2,3e4) if(n%6==0||n%6==2||n%6==3||n%6==4) {
      xs[n%6].push_back(n);
    }
    REP(i,6) reverse(ALL(xs[i]));
    int sum=0,yi=0;
    VI ys={2,3,4,0};
    while(SZ(res)<N) {
      int y=ys[yi%4]; yi+=1;
      sum+=xs[y].back();
      res.push_back(xs[y].back()), xs[y].pop_back();
    }
    //dump(sum%6);
    if(sum%6==2) {
      VI temp;
      while(res.back()%6!=2) temp.push_back(res.back()), res.pop_back();
      res.pop_back();
      FORR(a,temp) res.push_back(a);
      res.push_back(xs[0].back());
    } else if(sum%6==3) {
      VI temp;
      while(res.back()%6!=3) temp.push_back(res.back()), res.pop_back();
      res.pop_back();
      FORR(a,temp) res.push_back(a);
      res.push_back(xs[0].back());
    } else if(sum%6==5) {
      VI temp;
      while(res.back()%6!=3) temp.push_back(res.back()), res.pop_back();
      res.pop_back();
      FORR(a,temp) res.push_back(a);
      res.push_back(xs[4].back());
    } else {
      assert(sum%6==0);
    }
  }
  FORR(a,res) cout<<a<<" ";
  cout<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  solve();

  return 0;
}
