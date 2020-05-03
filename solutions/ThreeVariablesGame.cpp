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

// $ cp-batch ThreeVariablesGame | diff ThreeVariablesGame.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ThreeVariablesGame.cpp && ./a.out

/*
 
 5/3/2020
 
 5:48-6:36 AC
 
 https://img.atcoder.jp/abc166/editorial.pdf
 
 */

const int MAX_N=1e6+1;
int X[MAX_N][2];
LL balls[3];
int N;

void solve() {
  if(balls[X[0][0]]==0&&balls[X[0][1]]==0) {
    cout<<"No"<<endl;
    return;
  }
  VI res;
  REP(i,N) {
    int a=X[i][0],b=X[i][1];
    if(balls[a]==0&&balls[b]==0) {
      cout<<"No"<<endl;
      return;
    }
    if(balls[a]>balls[b]) {
      res.push_back(b);
      balls[b]++,balls[a]--;
    } else if(balls[a]<balls[b]) {
      res.push_back(a);
      balls[a]++,balls[b]--;
    } else if(balls[a]==balls[b]&&i<N-1) {
      int mask=(1<<a)|(1<<b);
      int mask2=(1<<(X[i+1][0]))|(1<<(X[i+1][1]));
      if(mask==mask2) res.push_back(a),balls[a]++,balls[b]--;
      else {
        int x=mask&mask2;
        REP(j,3)if((x>>j)&1) {
          res.push_back(j);
          if(a==j) balls[a]++,balls[b]--;
          else balls[b]++,balls[a]--;
        }
      }
    }
    REP(j,3)if(balls[j]<0) {
      cout<<"No"<<endl;
      return;
    }
  }
  cout<<"Yes"<<endl;
  REP(i,N) cout<<(char)('A'+res[i])<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,3) cin>>balls[i];
  REP(i,N) {
    string S; cin>>S;
    X[i][0]=S[0]-'A';
    X[i][1]=S[1]-'A';
  }
  solve();
  
  return 0;
}
