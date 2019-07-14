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

// $ cp-batch XORCircle | diff XORCircle.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address XORCircle.cpp && ./a.out

/*
 
 7/14/2019
 
 5:30-6:30 WA
 7:00-7:24 AC
 
 It was pretty tough problem because I didn't analyze N>5 cases.
 Thus it took tons of time to find {1,1,4,4,5,5} case.
 
 In this problem, analyzing by A[0],A[1],A[2],A[3],.. did not clarify condition.
 Using two variables {`a`,`b`} and getting sequence { a, b, a^b, a, b, .. } makes many things easier.
 If equality condition is the key, using smaller variables should work better. It should make some of groups.
 
 https://img.atcoder.jp/agc035/editorial.pdf
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

bool solve() {
  LL tot=0;
  REP(i,N) tot^=A[i];
  if(tot!=0) return false;
  if(N%3==0) {
    map<LL,int> cnt;
    REP(i,N) cnt[A[i]]++;
    vector<LL> B;
    int n=N/3;
    FORR(kvp, cnt) {
      if(kvp.second%n!=0) return false;
      int x=kvp.second;
      while(x>0) {
        B.push_back(kvp.first);
        x-=n;
      }
    }
    if(SZ(B)!=3) return false;
    tot=0; tot=B[0]^B[1]^B[2];
    return tot==0;
  } else {
    REP(i,N) if(A[i]!=0) return false;
    return true;
  }
}

void rem(int x, map<int,int> &cnt) {
  cnt[x]--;
  if(cnt[x]==0) cnt.erase(x);
}

/*
bool solve() {
  int tot=0;
  REP(i,N) tot^=A[i];
  if(tot!=0) return false;
  REP(i,N) cnt[A[i]]++;
  queue<II> Q;
  FOR(i,1,N) {
    int x=A[0]^A[i];
    cnt[A[0]]--,cnt[A[i]]--;
    rem(A[0],cnt),rem(A[i],cnt);
    if(cnt[x]) {
      rem(A[x],cnt);
      VI P={A[0],A[i],x};
      sort(ALL(P));
      do {
        bool res=f(P[0],P[1],P[2],cnt);
        if(res) return true;
      } while(next_permutation(ALL(P)));
      return false;
    }
    cnt[A[0]]++,cnt[A[i]]++;
  }
  return false;
}*/

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
vector<int> genRandSeq(int size, int lb, int ub) {
  if (size==0) return {};
  vector<int> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}

void test() {
  N=genRandNum(3,7);
  VI B=genRandSeq(N,0,6);
  REP(i,N)A[i]=B[i];
  bool act=solve();
  bool exp=false;
  sort(ALL(B));
  do {
    bool res=true;
    REP(i,N) res&=(B[i]^B[(i+1)%N])==B[(i+2)%N];
    exp|=res;
  }while(next_permutation(ALL(B)));
  if(exp) dumpc(B);
  if(act!=exp) {
    dump(act,exp);
    dumpc(B);
  }
  assert(act==exp);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>N;
  REP(i,N) cin>>A[i];
  cout<<(solve()?"Yes":"No")<<endl;
  
  return 0;
}
