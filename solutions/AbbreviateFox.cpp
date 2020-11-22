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

// $ cp-batch AbbreviateFox | diff AbbreviateFox.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address AbbreviateFox.cpp && ./a.out

/*

 11/21/2020

 21:03-21:15 WA
 21:31 AC

 https://atcoder.jp/contests/arc108/editorial/351

 */

string S;
int N;

void solve() {
  vector<char> st;
  int cnt=0;
  REP(i,N) {
    st.push_back(S[i]);
    while(SZ(st)>2&&st[SZ(st)-1]=='x'&&st[SZ(st)-2]=='o'&&st[SZ(st)-3]=='f') {
      REP(_,3) st.pop_back();
      ++cnt;
    }
  }
  cout<<N-3*cnt<<endl;
}

void solve_() {
  VI viz(N,0);

  auto chk=[&](int i1, int i2, int i3) -> bool {
    if(i1<0||i3>=N) return false;
    if(viz[i1]||viz[i2]||viz[i3]) return false;
    return S[i1]=='f'&&S[i2]=='o'&&S[i3]=='x';
  };

  int res=0;
  queue<II> Q;
  auto push=[&](int i1, int i2, int i3) {
    Q.emplace(i1,i3),viz[i1]=viz[i2]=viz[i3]=1,++res;
  };

  REP(i,N-2) if(chk(i,i+1,i+2)) {
    push(i,i+1,i+2);
  }

  while(SZ(Q)) {
    int l,r; tie(l,r)=Q.front(); Q.pop();
    if(chk(l-2,l-1,r+1)) push(l-2,l-1,r+1);
    if(chk(l-1,r+1,r+2)) push(l-1,r+1,r+2);
  }
  cout<<N-res*3<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>S;
  solve();

  return 0;
}
