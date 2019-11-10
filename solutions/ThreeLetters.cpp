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

// $ cp-batch ThreeLetters | diff ThreeLetters.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ThreeLetters.cpp && ./a.out

/*
 
 11/9/2019
 
 16:05-16:34, 16:42-18:00 give up
 
 11/10/2019
 
 12:50-15:30 read editorials
 
 https://img.atcoder.jp/code-festival-2018-final/editorial.pdf
 http://kmjp.hatenablog.jp/entry/2018/12/05/0900
 https://kimiyuki.net/writeup/algo/atcoder/code-festival-2018-final-d/
 https://betrue12.hateblo.jp/entry/2018/11/19/205052
 
 */

const int MAX_N=3e4+1;
string S[MAX_N];
int N;

int id(char c) {
  if(islower(c)) return 26+c-'a';
  else return c-'A';
}
char toc(int a) {
  if(a>=26) return 'a'+(a-26);
  else return 'A'+a;
}
int enc(int a, int b, int c) {
  return a*52*52+b*52+c;
}
string dec(int x) {
  int c=x%52; x/=52;
  int b=x%52; x/=52;
  int a=x%52;
  string t(3,'?');
  t[0]=toc(a),t[1]=toc(b),t[2]=toc(c);
  return t;
}

bool ith(LL mask, int i) {
  return (mask>>i)&1;
}

void solve() {
  VI cnt(52*52*52,0);
  REP(i,N) {
    string s=S[i];
    int L=SZ(s);
    vector<LL> R(L,0);
    for(int j=L-1; j>0; --j) {
      int a=id(s[j]);
      R[j-1]=R[j]|(1LL<<a);
    }
    LL lmask=1LL<<id(s[0]);
    VI viz(52*52*52,0);
    FOR(j,1,L) {
      REP(l,52) REP(r,52) if(ith(lmask,l)&&ith(R[j],r)) {
        int x=enc(l,id(s[j]),r);
        if(!viz[x]) cnt[x]++,viz[x]=1;
      }
      lmask|=(1LL<<id(s[j]));
    }
  }
  vector<II> X;
//  dumpc(cnt);
  REP(i,52*52*52) if(cnt[i]>0) {
    X.emplace_back(-cnt[i],i);
//    dump(dec(i),cnt[i]);
  }
  int x=min_element(ALL(X))->second;
  cout<<dec(x)<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>S[i];
  solve();
  
  return 0;
}
