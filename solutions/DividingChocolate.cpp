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
struct TwoDimCumSum {
public:
  int R,C;
  TwoDimCumSum() {}
  TwoDimCumSum(vector<vector<int>> &X) { init(X); }
  void init(vector<vector<int>> &X) {
    this->R=X.size();
    if(R==0) return;
    this->C=X[0].size();
    this->cum=vector<vector<int>>(R+1,vector<int>(C+1,0));
    
    for(int i=0; i<R; ++i) for(int j=0; j<C; ++j) {
      cum[i+1][j+1]=cum[i][j+1]+cum[i+1][j]-cum[i][j]+X[i][j];
    }
  }
  // query of sum in rectangle r in [i1,i2), c in [j1,j2)
  int query(int i1, int j1, int i2, int j2) {
//    dump(i1,j1,i2,j2,C,R);
    assert(0<=i1&&0<=i2);
    assert(i1<R&&i2<=R);
    assert(0<=j1&&0<=j2);
    assert(j1<C&&j2<=C);
    return cum[i2][j2]-cum[i1][j2]-cum[i2][j1]+cum[i1][j1];
  }
private:
  vector<vector<int>> cum;
};
// $ cp-batch DividingChocolate | diff DividingChocolate.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DividingChocolate.cpp && ./a.out

/*
 
 3/22/2020
 
 5:26-6:36 AC
 
 https://img.atcoder.jp/abc159/editorial.pdf
 https://youtu.be/lTjWiIRyIdg?t=3733
 http://kmjp.hatenablog.jp/entry/2020/03/22/0900
 https://twitter.com/satanic0258/status/1241721428132507648
 https://twitter.com/ei1333/status/1241721403457409029
 https://twitter.com/laycrs/status/1241721381202493442
 https://twitter.com/kzyKT_M/status/1241721347144736768
 
 5/8/2020
 
 17:34-17:50 solve again
 
 */

const int MAX_N=10+1;
string S[MAX_N];
int H,W,K;

vector<vector<int>> A;
TwoDimCumSum cum;

const int Inf=1e8;
void solve() {
  int res=H*W;
  REP(mask,1<<(H-1)) {
    VI gs(H,0);
    REP(i,H-1) {
      gs[i+1]=gs[i]+((mask>>i)&1);
    }
    int G=gs[H-1]+1;
    int w=0;
    VI cnt(G);
    int ans=__builtin_popcount(mask);
    REP(j,W) {
      VI cnt2(G);
      REP(i,H) cnt2[gs[i]]+=S[i][j]-'0';
      bool ok=true;
      REP(i,G) if(cnt[i]+cnt2[i]>K) {
        ok=false;
      }
      if(!ok) {
        if(w==0) {
          ans=Inf;
          break;
        } else {
          w=1;
          cnt=cnt2;
          ++ans;
        }
      } else {
        REP(i,G) cnt[i]+=cnt2[i];
        ++w;
      }
    }
    SMIN(res,ans);
  }
  cout<<res<<endl;
}


bool f(int D) {
  bool res=false;
  REP(mask,1<<(H-1)) {
    VI ds={0};
    REP(i,H-1) if((mask>>i)&1) ds.push_back(i+1);
    ds.push_back(H);
    int cnt=SZ(ds)-2;
    int lj=0,rj=0;
    while(lj<W&&rj<=W) {
      bool ok=true;
      REP(k,SZ(ds)-1) {
        int li=ds[k],ri=ds[k+1];
        if(cum.query(li,lj,ri,rj)>K) {
          ok=false;
          break;
        }
      }
      if(ok) {
        ++rj;
      } else {
        if(rj==lj+1) { cnt=Inf; break; }
        lj=rj-1;
        ++cnt;
      }
    }
//    if(D==1) dump(D,mask,cnt);
    if(cnt<=D) {
//      if(D==1) dump(D,mask,cnt);
      res=true;
      break;
    }
  }
  return res;
}

void solve_old() {
  A=VV<int>(H,VI(W));
  REP(i,H)REP(j,W) A[i][j]=S[i][j]-'0';
  cum.init(A);
//  dump(cum.R,cum.C);
    
  int good=1e4,bad=-1;
  while(abs(good-bad)>1) {
    int mid=(good+bad)/2;
    bool res=f(mid);
//    dump(mid,res);
    (res?good:bad)=mid;
  }
  cout<<good<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>H>>W>>K;
  REP(i,H) cin>>S[i];
  solve();
  
  return 0;
}
