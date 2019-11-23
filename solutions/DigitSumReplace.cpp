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

// $ cp-batch DigitSumReplace | diff DigitSumReplace.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DigitSumReplace.cpp && ./a.out

/*
 
 11/23/2019
 
 4:49-5:49 AC
 
 https://img.atcoder.jp/ddcc2020-qual/editorial.pdf
 https://youtu.be/BssyLgQvdcY?t=943
 https://twitter.com/kyopro_friends/status/1198239025011642369?s=20
 https://twitter.com/hanseilimak/status/1198343148973391873
 https://twitter.com/tempura_cpp/status/1198236303281672193?s=20
 
 */

const int MAX_N=1e6+1;
int D[MAX_N];
LL C[MAX_N];
int N;

void solve() {
  LL sum=0;
  REP(i,N) sum+=C[i]*D[i];
  LL D=accumulate(C,C+N,0LL);
  LL res=D-1+(sum-1)/9;
  cout<<res<<endl;
}

void test(int n) {
  string s=to_string(n);
  int sum=0;
  REP(i,SZ(s))sum+=s[i]-'0';
  int res=0;
  while(SZ(s)>1) {
    int N=SZ(s);
    int a=s[N-2]-'0',b=s[N-1]-'0';
    s=s.substr(0,N-2)+to_string(a+b);
//    dump(n,s);
    ++res;
  }
  dump(n,res,sum);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  /*
  vector<tuple<int,int,int,int>> Y;
  FORE(n,100,1000) {
      string s0=to_string(n);
    string s=s0;
      int sum=0;
      REP(i,SZ(s))sum+=s[i]-'0';
      int res=0;
      while(SZ(s)>1) {
        int N=SZ(s);
        int a=s[N-2]-'0',b=s[N-1]-'0';
        s=s.substr(0,N-2)+to_string(a+b);
    //    dump(n,s);
        ++res;
      }
    Y.emplace_back(res,sum,SZ(s0),n);
  }
  sort(ALL(Y));
  REP(i,SZ(Y)) {
    int res,sum,D,n; tie(res,sum,D,n)=Y[i];
    dump(res,D,sum,n);
  }*/
  
  cin>>N;
  REP(i,N) cin>>D[i]>>C[i];
  solve();
  
  return 0;
}
