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

// $ cp-batch DifferBy1Bit | diff DifferBy1Bit.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DifferBy1Bit.cpp && ./a.out

/*
 
 3/16/2019
 
 21:48-23:00 give up
 
 After experiment, I couldn't figure out even condition to build A->B path..
 
 3/25/2019
 
 14:40-17:11 AC
 
 Let's solve 0->A^B and apply XOR to integers.
 Length of the path is 2^N-1 = odd.
 Hamming distance between consecutive integres is exactly `1`.
 Necessary condition is that # of different bit of A^B is odd.
 
 We need to come up with construction step by induction.
 The proof is the step that we should actually implement!
 
 http://drken1215.hatenablog.com/entry/2019/03/21/184000
 https://img.atcoder.jp/agc031/editorial.pdf
 https://betrue12.hateblo.jp/entry/2019/03/17/164731
 https://babcs2035.hateblo.jp/entry/2019/03/17/161106
 https://www.hamayanhamayan.com/entry/2019/03/17/002957
 
    P + 00101
 => P + 01001
         ^
 
 Align to left most bit and restore later
 
     P + 00101
 *-> P + 10001
         ^
 
 Construct by left-most and right-most bit as a working bit
 
     P + 00101
 *-> P + 00100
             ^
  -> P + 10101
         ^
 *-> P + 10001

 This construction step can be verified by induction by looking at # of different bit.
 
 Summary:
  - Find necessary condition and show that it's sufficient
  - Prove by induction and implement it
   - divide and conquer works if induction step solves a problem from subproblem
 
 */

const int MAX_N=(1<<17)+10;
int N,A,B,C;

int ith(int x, int i) {
  return (x>>i)&1;
}

int iswap(int i, int j, int a) {
  int res=a,ia=ith(a,i),ja=ith(a,j);
  res^=ia<<i,res^=ja<<j;
  res|=ja<<i,res|=ia<<j;
  return res;
}
VI f(int p, int a, int b) {
  if(p==1) {
    assert(ith(a,0)!=ith(b,0));
    return {a,b};
  }
  for(int i=p-1; i>=0; --i) if(ith(a,i)!=ith(b,i)) {
    int aa=iswap(p-1,i,a),bb=iswap(p-1,i,b);
    int s=aa^1,t=s^(1<<(p-1));
    VI X=f(p-1,aa,s),Y=f(p-1,t,bb);
    VI res;
    FORR(x,X) res.push_back(iswap(p-1,i,x));
    FORR(y,Y) res.push_back(iswap(p-1,i,y));
    return res;
  }
  assert(false);
}

void solve() {
  C=A^B;
  if(__builtin_popcount(C)%2==0) {
    println("NO");
    return;
  }
  VI res=f(N,0,C);
  FORR(x,res) x^=A;
  
  assert(res.front()==A);
  assert(res.back()==B);
  REP(i,N-1) assert(__builtin_popcount(res[i]^res[i+1])==1);

  println("YES");
  REP(i,SZ(res)) printf("%d ", res[i]);
  println("");
}

int viz[MAX_N];
VI G[MAX_N];
SETI S;
void dfs(int u, VI &cur) {
  if(SZ(cur)==(1<<N)) {
//    dumpc(cur);
    S.emplace(cur.back());
    assert(SZ(cur)==(1<<N));
    return;
  }
  FORR(v,G[u]) if(viz[v]==0) {
    cur.push_back(v);
    viz[v]=1;
    dfs(v,cur);
    viz[v]=0;
    cur.pop_back();
  }
}
void test() {
  N=3;
  REP(mask,1<<N) {
    REP(i,N) if(!ith(mask,i)) {
      int u=mask|(1<<i);
      G[mask].push_back(u);
      G[u].push_back(mask);
    }
  }
  VI cur;
  REP(i,1<<N) if(i==0) {
    cur.push_back(i);
    viz[i]=1;
    dfs(i,cur);
    viz[i]=0;
    cur.pop_back();
    dumpc(S);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  test();
  
  cin>>N>>A>>B;
  solve();
  
  return 0;
}
