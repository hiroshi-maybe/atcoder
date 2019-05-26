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

// $ cp-batch AbsoluteMinima | diff AbsoluteMinima.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address AbsoluteMinima.cpp && ./a.out

template <typename T> struct BIT {
public:
  int N;
  vector<T> A;
  BIT() {}
  BIT(int N) { init(N); }
  void init(int N) {
    this->N=N;
    A=vector<T>(N+1,0);
  }
  // query ∑ { sum[i] : i=l..<r }
  T query(int l, int r) {
    assert(l<=r&&0<=l&&r<=N);
    return query(r)-query(l);
  }
  // min index s.t. dat[0..i]>x
  int upperbound(T x) {
    int good=N+1,bad=0;
    while(abs(good-bad)>1) {
      int m=(good+bad)/2;
      (query(m)>x?good:bad)=m;
    }
    return good-1;
  }
  // sum[i]+=x
  void add(int i, T x) {
    assert(0<=i&&i<N);
    ++i;
    while(i<=N) A[i]+=x,i+=lsone(i);
  }
  // sum[i]=x
  void update(int i, T v) {
    T pre=query(i+1)-query(i);
    add(i,v-pre);
  }
private:
  int lsone(int i) { return i&-i; }
  // query in [0,r) : ∑ { sum[i] : i=0..r-1 }
  T query(int r) {
    assert(0<=r&&r<=N);
    T res=0;
    while(r>0) res+=A[r],r-=lsone(r);
    return res;
  }
};
#define UNIQUE(A) sort((A).begin(),(A).end()),(A).erase(std::unique((A).begin(), (A).end()), (A).end());

/*
 
 5/25/2019
 
 6:07-6:56, 16:10-16:55 I threw away mentaining two sums. Case work is a hell.
 19:00-19:20, 20:25-20:40 AC by BIT
 
 I figured out below. However implementation messed up 😞
  - median is always optimal
  - median can be found by two priority queues
 
 Eventually BIT with coordinate compression worked well.
 
 https://img.atcoder.jp/abc127/editorial.pdf
 http://kmjp.hatenablog.jp/entry/2019/05/26/0930
 
 */

const LL Inf=1e18;
const int MAX_N=1e6+1;
LL A[MAX_N],B[MAX_N];
int N;

void solve() {
  LL res=0;
  priority_queue<LL> sQ; // c,b,a
  priority_queue<LL,vector<LL>,greater<LL>> lQ; // a',b',c'
  REP(i,N) {
    if(A[i]!=Inf) {
      res+=B[i];
      sQ.emplace(A[i]),lQ.emplace(A[i]);
      if(sQ.top()>lQ.top()) {
        LL a=sQ.top(); sQ.pop();
        LL b=lQ.top(); lQ.pop();
        res+=abs(a-b);
        lQ.emplace(a),sQ.emplace(b);
        assert(sQ.top()<=lQ.top());
      }
    } else {
      cout<<sQ.top()<<" "<<res<<endl;
    }
  }
}

void solve_org() {
  vector<LL> vs;
  REP(i,N) if(A[i]!=Inf) {
    vs.push_back(A[i]);
  }
  UNIQUE(vs);
//  dumpc(vs);
  int M=SZ(vs);
  map<LL,int> comp;
  REP(i,M) comp[vs[i]]=i;
//  dumpc(comp);
  BIT<LL> as(M+1),cnt(M+1);
  priority_queue<LL> sQ; // c,b,a
  priority_queue<LL,vector<LL>,greater<LL>> lQ; // a',b',c'
  LL b=0;
  REP(i,N) {
    if(A[i]==Inf) {
      assert(SZ(sQ));
      LL med=sQ.top();
      LL r=as.query(comp[med],M);
      LL cntr=cnt.query(comp[med],M);
      r-=med*cntr;
      LL l=as.query(0,comp[med]);
      LL cntl=cnt.query(0,comp[med]);
      l=med*cntl-l;
      cout<<med<<" "<<l+r+b<<endl;
    } else {
      b+=B[i];
      LL a=A[i];
      int j=comp[a];
//      dump(i,a,j);
      as.add(j,a);
      cnt.add(j,1);
      if(sQ.empty()||a<=sQ.top()) sQ.push(a);
      else lQ.push(a);
      if(SZ(lQ)>SZ(sQ)) {
        LL x=lQ.top(); lQ.pop();
        sQ.push(x);
      } else if(SZ(sQ)-SZ(lQ)>1) {
        LL x=sQ.top(); sQ.pop();
        lQ.push(x);
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) {
    int t; cin>>t;
    if(t==1) {
      cin>>A[i]>>B[i];
    } else {
      A[i]=Inf;
    }
  }
  solve();
  
  return 0;
}

/*
int main_() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  LL B=0,As=0,Al=0,med=0;
  REP(i,N) {
    int t; cin>>t;
    priority_queue<LL> sQ; // c,b,a
    priority_queue<LL,vector<LL>,greater<LL>> lQ; // a',b',c'
    if(t==1) {
      LL x=sQ.top();
      LL a,b; cin>>a>>b;
      B+=b;
      int n1=SZ(sQ),n2=SZ(lQ);
      if(sQ.empty()||a<=sQ.top()) {
        sQ.emplace(a);
        if(SZ(sQ)-SZ(lQ)>1) {
          assert(SZ(sQ)>1);
          LL x=sQ.top(),sQ.pop();
          LL med2=sQ.top();
          Al+=(med2-med)*n2+x-med2;
          if(x==med) {
            As+=(med2-med)*(n1-1)
          }
        } else {
          LL med2=sQ.top();
          assert(med<=med2);
          As+=(med2-med)*n1;
          As+=med2-a;
          Al+=(med-med2)*n2;
        }
      } else {
        lQ.emplace(a);
        if(SZ(lQ)>SZ(sq)) {
          LL med2=sQ.top(); sQ.pop();
          assert(med<=med2);
          Al-=med2-med;
          lQ.emplace(x);
          Al+=a-med2;
          Al+=(med-med2)*(n2-1);
          As+=(med2-med)*n1;
        } else Al+=a-med;
      }
      med=sQ.top();
    } else {
      LL x=sQ.top();
      assert(x==med);
      cout<<x<<" "<<As+Al+B<<endl;
    }
  }
  solve();
  
  return 0;
}
*/
