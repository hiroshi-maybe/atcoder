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

// $ cp-batch IntervalRunning | diff IntervalRunning.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address IntervalRunning.cpp && ./a.out

/*

 12/1/2019

 5:07-5:40 give up
 10:20-11:45 read editorial and got AC

 https://img.atcoder.jp/sumitrust2019/editorial.pdf
 https://twitter.com/hanseilimak/status/1201206923032285184
 https://twitter.com/kyopro_friends/status/1201135159552004096
 https://twitter.com/maspy_stars/status/1201134357513031685?s=20
 https://twitter.com/ngtkana/status/1201136252050821120?s=20

 6/30/2020 9:58-10:44 pause
 7/2/2020 13:25-14:35 AC after looking at the failed test case (3WA)
 https://youtu.be/vVOwtLuh60U?t=4831

 */

LL T[2],A[2],B[2];

string solve() {
  LL a1=T[0]*A[0],a2=T[1]*A[1],b1=T[0]*B[0],b2=T[1]*B[1];
  if(a1<b1) swap(a1,b1),swap(a2,b2);
  if(a1+a2>b1+b2) return "0";
  if(a1+a2==b1+b2) return "infinity";
  LL L=a1-b1,M=b1+b2-(a1+a2);
  LL k=L/M;
  LL res=2*k+1;
  //dump(a1,a2,b1,b2,L,M,k);
  if(L%M==0) --res;
  return to_string(res);
}

string solve_binarysearch() {
  LL a1=T[0]*A[0],a2=T[1]*A[1],b1=T[0]*B[0],b2=T[1]*B[1];
  if(a1<b1) swap(a1,b1),swap(a2,b2);
  if(a1+a2>b1+b2) return "0";
  if(a1+a2==b1+b2) return "infinity";
  const LL Inf=1e18;
  LL good=Inf+10,bad=0;

  auto f=[&](__int128_t x) -> int {
    __int128_t t1=(x+1)/2,t2=x-t1;
    auto res=t1*b1+t2*b2-(t1*a1+t2*a2);
    if(res==0) return 0;
    return res>0?1:-1;
  };

  while(abs(good-bad)>1) {
    LL x=(good+bad)/2;
    bool res=f(x+1)>0&&f(x)>0;
    (res?good:bad)=x;
  }
  //dump(a1,a2,b1,b2,a1+a2,b1+b2);
  //dump(good,f(good+2),f(good+1),f(good),f(good-1),f(good-2),f(good-3));

  LL res=good-1-(f(good-1)==0);
  return to_string(res);

/*
  if(A1*T1+A2*T2>B1*T1+B2*T2) return 0;
  if(T1*(A1-B1)==T2*(B2-A2)) return Inf;
  LL good=1,bad=Inf+10;
  while(abs(good-bad)>1) {
    LL mid=(good+bad)/2;
    LL a=T1*(A1-B1)+T2*(A2-B2);
    LL b=T1*(B1-A1);
    bool res=a>=b/mid;
    dump(mid,res,a,b,b/mid);
    (res?good:bad)=mid;
  }

  LL a=T1*(B1-A1)/(T1*(A1-B1)+T2*(A2-B2));
  dump(a);

  dump(good);
  return good;*/
}

string solve_org() {
  LL P=(A[0]-B[0])*T[0],Q=(A[1]-B[1])*T[1];
  if(P>0) P*=-1,Q*=-1;
  if(P+Q<0) return "0";
  if(P+Q==0) return "infinity";
//  dump(P,Q,P+Q);
  LL k=abs(P/(P+Q));
  LL res=2LL*k;
  if((P+Q)*k!=-P) ++res;
  return to_string(res);
}

void solve_wrong() {
  int res=0;
  LL a=0,b=0;
  int sign=-100;
  FOR(i,0,1e6) {
    a+=T[i%2]*A[i%2];
    b+=T[i%2]*B[i%2];
    LL x=min(a,b);
    a-=x,b-=x;
    int sign2=a==b?0:a>b;
    if(sign2==0||sign2!=sign) ++res;
    sign=sign2;
  }
  if(res>1e5) cout<<"infinity"<<endl;
  else cout<<res-1<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>T[0]>>T[1]>>A[0]>>A[1]>>B[0]>>B[1];
  cout<<solve()<<endl;

  return 0;
}
