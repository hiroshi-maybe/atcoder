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

// $ cp-batch Kaburin | diff Kaburin.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Kaburin.cpp && ./a.out

/*

 7/22/2020

 22:19-23:01 WA
 23:26 AC after adding semapho. Don't do read-forces 👎

 */

string S;
int N;

void solve() {
  vector<pair<LL,LL>> imos(N+20);
  LL res=0;
  LL cnt=5,combo=0;
  auto attack=[&](LL a) -> LL {
    LL bonus=combo/10;
    return a+a/10LL*bonus;
  };

  int semapho=0;
  VI ss(N+20,0);
  REP(i,N) {
    cnt+=imos.at(i).first, combo+=imos.at(i).second,semapho-=ss[i];
    //dump(i,cnt,combo);
    char c=S[i];
    if(semapho==0&&c=='N'&&cnt>0) {
      cnt-=1,res+=attack(10),semapho++;
      ss[i+1]+=1,imos.at(i+7).first+=1,imos.at(i+2).second+=1;
      //dump(i,c,attack(10))
    } else if(semapho==0&&c=='C'&&cnt>=3) {
      cnt-=3,res+=attack(50),semapho++;
      ss[i+3]+=1,imos.at(i+9).first+=3,imos.at(i+4).second+=1;
      //dump(i,c,attack(50));
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //S=string(1e2,'C');
  //N=SZ(S);
  //solve();

  //return 0;

  cin>>S;
  //S+=string(20,'-');
  N=SZ(S);
  solve();

  return 0;
}
