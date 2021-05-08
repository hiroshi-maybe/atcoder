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

// $ cp-batch HappyBirthday2 | diff HappyBirthday2.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address HappyBirthday2.cpp && ./a.out

/*

 5/8/2021

 5:09-5:43 AC

 https://atcoder.jp/contests/abc200/editorial/1246

 */

const int MAX_N=200+1;
LL A[MAX_N];
int N;

void pr(VI S) {
  cout<<SZ(S)<<" ";
  REP(j,SZ(S)) cout<<S[j]+1<<" ";
  cout<<endl;
}
void solve() {
  VV<int> S(200);
  REP(i,N) {
    int a=A[i]%200;
    REP(x,200) if(SZ(S[x])&&S[x].back()!=i) {
      int y=(x+a)%200;
      VI s=S[x]; s.push_back(i);
      if(SZ(S[y])>0) {
        cout<<"Yes"<<endl;
        pr(s);
        pr(S[y]);

        int s1=0,s2=0;
        FORR(i,s) s1=(s1+A[i])%200;
        FORR(i,S[y]) s2=(s2+A[i])%200;
        //dump(s1,s2);
        assert(s1==s2);

        return;
      } else {
        S[y]=s;
      }
    }


    if(S[a].empty()) {
      S[a]={i};
    } else {
      cout<<"Yes"<<endl;
      pr(S[a]);
      pr({i});
      return;
    }
  }
  cout<<"No"<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>A[i];
  solve();

  return 0;
}
