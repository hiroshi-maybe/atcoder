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

// $ cp-batch WhenIHitMyPocket | diff WhenIHitMyPocket.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address WhenIHitMyPocket.cpp && ./a.out

/*
 
 3/3/2019
 
 20:01-20:36 Misunderstood problem statement. Fuck.
 21:00 AC
 
 https://youtu.be/WhDtakdCPg4?t=2159
 https://hewla.hatenablog.com/entry/2019/02/09/231440
 https://betrue12.hateblo.jp/entry/2019/02/10/014031
 https://img.atcoder.jp/yahoo-procon2019-qual/editorial.pdf
 
 Once we reach (1,0)->(A,0)->(0,1)->(B,0), we can always get 1 yen.
 Thus we'll get B-A (K-(A-1))/2 times.
 Solution can be simpler.
 
 */

LL K,A,B;

LL solve() {
  if(B-A<=2) return K+1;
  if(K<=A-1) return K+1;
  LL cycle=(K-(A-1))/2;
  LL res=A+(B-A)*cycle;
  K-=A-1;
  K-=2*cycle;
  return res+K%2;
}

LL solve_org() {
  if(B-A<=2) return K+1;
  if(K<A+1) return K+1;
  LL C=(A+B-2)/(B-1);
//  dump(C,K<(A+1)*C);
  if(K<(A+1)*C) {
    LL cycle=K/(A+1),a=(B-1)*cycle,b=K%(A+1);
//    dump(cycle,a,b)
    return 1+a+b;
  } else {
    LL a=(B-1)*C,rem=K-(A+1)*C,b=rem/2*(B-A),c=rem%2;
    return 1+a+b+c;
  }
}

LL solve_wrong() {
  if(B==1||(A==1&&B==2)) return K+1;
  LL cycle=K/(A+1);
  LL res=cycle*(A*B-1);
  dump(cycle,A*B-1,res);
  K=K%(A+1);
  res+=max(K,B*(K-1)-1);
  dump(K,res);
  
  /*
  if(K==1) res+=K;
  else if(B==2&&K<=3) res+=K;
  else if(B==3&&K<=2) res+=K;
  else res+=B*(K-1)-1;*/
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>K>>A>>B;
  cout<<solve()<<endl;
  
  return 0;
}
