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
template <typename Val>
struct SegmentTree {
  int N_; // adjusted N
  vector<Val> tree;
  Val id;
  using Merge = function<Val(Val,Val)>;
  Merge merge;
public:
  SegmentTree(int N, Val id, Merge merge) { prep(N,id,merge); }
  SegmentTree(vector<Val> A, Val id, Merge merge) { prep(A.size(),id,merge), this->build(A); }
  SegmentTree& prep(int N, Val id, Merge merge) {
    this->id=id,this->merge=merge;
    int n=1; while(n<N) n<<=1; // Init by power of 2
    this->tree=vector<Val>(2*n-1,id), this->N_=n;
    return *this;
  }
  void build(const vector<Val> &ns) {
    for(int i=0; i<ns.size(); ++i) tree[i+N_-1]=ns[i];
    for(int i=N_-2; i>=0; --i) mergeAt(i);
  } // Initialize tree with `ns`
  void update(int i, const Val &x) { i+=N_-1,tree[i]=x; while(i>0) i=(i-1)/2,tree[i]=mergeAt(i); } // Update k-th (0-indexed) value
  Val query(int ql, int qr) { return queryTree(ql,qr,0,0,N_); } // query in range [ql,qr)
private:
  Val mergeAt(int i) { return tree[i]=merge(tree[2*i+1],tree[2*i+2]); }
  Val queryTree(const int ql, const int qr, int i, int tl, int tr) {
    if (tr<=ql||qr<=tl) return id; // out of range
    if (ql<=tl&&tr<=qr) return tree[i]; // all covered
    int mid=tl+(tr-tl)/2; // partially covered
    return merge(queryTree(ql,qr,2*i+1, tl,mid),
                 queryTree(ql,qr,2*i+2,mid, tr));
  }
};
template<typename Val> auto makeRMQ(vector<Val> A, Val id) {
  return SegmentTree<Val>(A,id,[](Val a, Val b) { return max(a,b); });
}
// $ cp-batch BracketSequencing | diff BracketSequencing.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BracketSequencing.cpp && ./a.out

/*
 
 5/10/2020
 
 6:05-6:54 give up
 11:50-12:40, 14:40-17:00 read editorials and got AC by RMQ
 
 https://twitter.com/hanseilimak/status/1259564407803097088
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.djaw3ii7du1k
 
 https://kmjp.hatenablog.jp/entry/2020/05/10/0930
 https://betrue12.hateblo.jp/entry/2020/05/10/224429
 
 Counter example for my wrong greedy
  - https://twitter.com/kusano_k/status/1259486224235913216
 
 https://twitter.com/drken1215/status/1259479942892421120
 https://twitter.com/laycrs/status/1259478425242234883
 https://twitter.com/kzyKT_M/status/1259478566523174915
 https://twitter.com/satanic0258/status/1259479889909972992
 https://twitter.com/tomerun/status/1259479190832705538
 https://twitter.com/ngtkana/status/1259478791207841796
 https://twitter.com/small_onions/status/1259478423438671872
 https://twitter.com/ei1333/status/1259478327850487811
 https://twitter.com/tsutaj/status/1259478320317558784
 
 One sort by @ngtkana
  - https://atcoder.jp/contests/abc167/submissions/13064835
 
 Two sorts by @betrue12
  - https://atcoder.jp/contests/abc167/submissions/13086967
 
 */

const int MAX_N=1e6+1;
string S[MAX_N];
int N;

const int Inf=1e8;
bool solve() {
  vector<II> L,R;
  REP(i,N) {
    string s=S[i];
    int bal=0,d=0;
    REP(j,SZ(s)) bal+=S[i][j]=='('?1:-1,SMIN(d,bal);
    if(bal>=0) L.emplace_back(-d,bal);
    else R.emplace_back(bal-d,bal);
  }
  sort(ALL(L)),sort(R.rbegin(),R.rend());
  int bal=0;
  REP(i,SZ(L)) {
    int d=L[i].first,b=L[i].second;
    if(bal<d) return false;
    bal+=b;
  }
  REP(i,SZ(R)) {
    int x=R[i].first,b=R[i].second;
    int d=x-b;
    if(bal<d) return false;
    bal+=b;
  }
  return bal==0;
}

bool solve_invert2() {
  vector<pair<string,int>> ss[2];
  REP(i,N) {
    int bal=0;
    REP(j,SZ(S[i])) bal+=S[i][j]=='('?1:-1;
    if(bal>=0) ss[0].emplace_back(S[i],i);
    else {
      string s=S[i];
      REP(j,SZ(s)) s[j]=s[j]=='('?')':'(';
      reverse(ALL(s));
      ss[1].emplace_back(s,i);
    }
  }
          
  using IIII=tuple<int,int,int,int>;
  vector<IIII> xs;
  REP(i,2)REP(j,SZ(ss[i])) {
    int bal=0,d=0;
    string s=ss[i][j].first;
    REP(k,SZ(s)) bal+=s[k]=='('?1:-1,SMIN(d,bal);
    if(i==0) bal=-bal,d=-d;
//    dump(i,d,bal,ss[i][j].second);
    xs.emplace_back(i,d,bal,ss[i][j].second);
  }
  sort(ALL(xs));
  int bal=0;
  FORR(x,xs) {
    int i=get<3>(x);
    REP(j,SZ(S[i])) {
      bal+=S[i][j]=='('?1:-1;
      if(bal<0) return false;
    }
//    dump(i,S[i],bal);
  }
  return bal==0;
}

bool solve_org() {
  int bal=0;
  REP(i,N)REP(j,SZ(S[i])) bal+=S[i][j]=='('?1:-1;
  if(bal!=0) return false;

  vector<II> LR[2];
  REP(i,N) {
    int b=0;
    REP(j,SZ(S[i])) b+=S[i][j]=='('?1:-1;
    int lr=0;
    if(b<0) {
      REP(j,SZ(S[i])) S[i][j]=S[i][j]=='('?')':'(';
      reverse(ALL(S[i]));
      lr=1;
    }
    int maxd=0;
    b=0;
    REP(j,SZ(S[i])) {
      b+=S[i][j]=='('?1:-1;
      SMIN(maxd,b);
    }
    LR[lr].emplace_back(-maxd,b);
  }
  
  auto f=[&](vector<II> &X) -> int {
    sort(ALL(X));
    dumpc(X);
    int N=SZ(X);
    VI viz(N,0);
    vector<II> A(N);
    REP(i,N) A[i]={X[i].second,i};
    auto rmq=makeRMQ(A,{-Inf,-1});
    int bal=0;
    while(true) {
      int hb=lower_bound(ALL(X),make_pair(bal,Inf))-X.begin();
      dump(hb);
      auto x=rmq.query(0,hb);
      int delta = x.first;
      dump(bal,delta,bal+delta);
      if(delta==-Inf) break;
      bal+=delta;
      if(bal<0) break;
      rmq.update(x.second,{-Inf,-1});
      viz[x.second]=1;
    }
    return count(ALL(viz),0)==0?bal:Inf;
  };
  
  dumpc(LR[0]);
  dumpc(LR[1]);
    
  int lb=f(LR[0]),rb=f(LR[1]);
  dump(lb,rb);
  if(lb==Inf||rb==Inf) return false;
  return lb==rb;
}

bool solve_wrong() {
  int bal=0;
  REP(i,N)REP(j,SZ(S[i])) bal+=S[i][j]=='('?1:-1;
  if(bal!=0) return false;
  
  vector<II> preq;
  REP(i,N) {
    int b=0,debt=0;
    REP(j,SZ(S[i])) {
      b+=S[i][j]=='('?1:-1;
      SMIN(debt,b);
    }
    dump(i,S[i],debt,b);
    preq.emplace_back(-debt,b);
  }
  sort(ALL(preq));
  dumpc(preq);

  vector<II> A(N);
  REP(i,N) A[i]={preq[i].second,i};
  auto rmq=makeRMQ(A,{-Inf,-1});

  VI viz(N,0);
  bal=0;
  while(true) {
    int hb=lower_bound(ALL(preq),make_pair(bal,Inf))-preq.begin();
    auto x=rmq.query(0,hb);
    int delta = x.first;
    if(delta==-Inf) break;
    dump(bal,delta,bal+delta);
    bal+=delta;
    if(bal<0) break;
    rmq.update(x.second,{-Inf,-1});
    viz[x.second]=1;
  }
  return bal==0&&count(ALL(viz),0)==0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>S[i];
  cout<<(solve()?"Yes":"No")<<endl;
  
  return 0;
}
