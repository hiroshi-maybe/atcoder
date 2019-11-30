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

// $ cp-batch Roadwork | diff Roadwork.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Roadwork.cpp && ./a.out

/*
 
 5/26/2019
 
 6:04-6:54 REx2
 6:56 AC
 
 5/27/2019
 
 read editorials and added more solutions
 
 https://img.atcoder.jp/abc128/editorial.pdf
 http://kmjp.hatenablog.jp/entry/2019/05/26/1300
 http://kazune-lab.net/contest/2019/05/26/abc128/
 https://twitter.com/knshnb/status/1132664716889690112
 
 Coordinate compression along with queries is easier.
 
 11/29/2019
 
 Replace lazy RMQ with lazy segment tree library.
 
 */

const int MAX_N=1e6+1;
LL S[MAX_N],T[MAX_N],X[MAX_N],D[MAX_N];
int N,Q;
template <typename Val, typename Delay>
struct LazySegmentTree {
  int N_/* adjusted N*/,head/* head of leaf */;
  vector<Val> tree;
  vector<Delay> delay;
  Val id;
  Delay delayId;
  using Merge = function<Val(Val,Val)>;
  using Apply = function<Val(Val,Delay)>;
  using MergeDelay = function<Delay(Delay,Delay)>;
  Merge merge;
  Apply apply;
  MergeDelay mergeDelay;
public:
  LazySegmentTree(int N, Val id, Delay delayId, Merge merge, Apply apply, MergeDelay mergeDelay) { prep(N,id,delayId,merge,apply,mergeDelay); }
  LazySegmentTree(vector<Val> A, Val id, Delay delayId, Merge merge, Apply apply, MergeDelay mergeDelay) { prep(A.size(),id,delayId,merge,apply,mergeDelay),this->build(A); }
  LazySegmentTree& prep(int N, Val id, Delay delayId, Merge merge, Apply apply, MergeDelay mergeDelay) {
    this->id=id,this->delayId=delayId;
    this->merge=merge,this->apply=apply,this->mergeDelay=mergeDelay;
    int n=1; while(n<N) n<<=1; // Init by power of 2
    this->tree=vector<Val>(2*n-1,id),this->delay=vector<Delay>(2*n-1,delayId);
    this->N_=n,this->head=N_-1;
    return *this;
  }
  void build(const vector<Val> &ns) {
    for(int i=0; i<ns.size(); ++i) tree[i+N_-1]=ns[i];
    for(int i=N_-2; i>=0; --i) mergeAt(i);
  } // Initialize tree with `ns`
  void update(int ql, int qr, const Delay &delay) { updateTree(ql,qr,delay,0,0,N_); }
  Val query(int ql, int qr) { return queryTree(ql,qr,0,0,N_); } // query in range [ql,qr)
private:
  Val mergeAt(int i) { return tree[i]=merge(tree[2*i+1],tree[2*i+2]); }
  Val queryTree(const int ql, const int qr, int i, int tl, int tr) {
    if(tr<=ql||qr<=tl) return id; // out of range
    applyDelay(i);
    if(ql<=tl&&tr<=qr) return tree[i]; // all covered
    int mid=tl+(tr-tl)/2; // partially covered
    return merge(queryTree(ql,qr,2*i+1, tl,mid),
                 queryTree(ql,qr,2*i+2,mid, tr));
  }
  void updateTree(const int ql, const int qr, Delay d, int i, int tl, int tr) {
    if(ql<=tl&&tr<=qr) mergeDelayAt(i,d),applyDelay(i); // all covered
    else if(ql<tr&&tl<qr) { // partially coverd
      int mid=tl+(tr-tl)/2;
      applyDelay(i),updateTree(ql,qr,d,2*i+1,tl,mid),updateTree(ql,qr,d,2*i+2,mid,tr),mergeAt(i);
    } else applyDelay(i);
  }
  void applyDelay(int i) {
    if(delay[i]==delayId) return;
    if(i<head) pushdownAt(i);
    tree[i]=apply(tree[i],delay[i]),delay[i]=delayId;
  }
  void pushdownAt(int i) { mergeDelayAt(2*i+1,delay[i]),mergeDelayAt(2*i+2,delay[i]); }
  void mergeDelayAt(int i, Delay d) { delay[i]=mergeDelay(delay[i],d); }
};
template<typename Val, typename Delay> auto makeLazyRmQ(vector<Val> A, Val id, Delay delayId) {
  auto mina = [](Val a, Val b) { return min(a,b); };
  auto seta = [](Val , Delay b) { return b; };
  auto setb = [](Delay _, Delay b) { return b; };
  return LazySegmentTree<Val,Val>(A,id,delayId,mina,seta,setb);
}

const LL Inf=1e18;
void solve() {
  vector<LL> xs;
  REP(i,N) {
    LL s=S[i],t=T[i],x=X[i];
    xs.push_back(s-x),xs.push_back(t-x);
  }
  REP(i,Q) xs.push_back(D[i]);
  sort(ALL(xs));
  xs.erase(unique(ALL(xs)),xs.end());
//  dumpc(xs);
  int M=SZ(xs);
  auto mina=[](LL a, LL b) { return min(a,b); };
  auto rmq=LazySegmentTree<LL,LL>(vector<LL>(M,Inf),Inf,Inf,mina,mina,mina);
  REP(i,N) {
    LL s=S[i],t=T[i],x=X[i];
    int l=lower_bound(ALL(xs),s-x)-xs.begin();
    int r=lower_bound(ALL(xs),t-x)-xs.begin();
    rmq.update(l,r,x);
  }
  REP(i,Q) {
    int p=lower_bound(ALL(xs),D[i])-xs.begin();
    LL res=rmq.query(p,p+1);
//    dump(i,D[i],p,res);
    if(res>=Inf) res=-1;
    cout<<res<<endl;
  }
}

void solve_simplecordcomp() {
  vector<tuple<LL,int,LL>> es;
  REP(i,N) {
    LL s=S[i],t=T[i],x=X[i];
    es.emplace_back(s-x,0,x);
    es.emplace_back(t-x,1,x);
  }
  REP(i,Q) es.emplace_back(D[i],2,-1);
  sort(ALL(es));
  multiset<LL> Q;
  REP(i,SZ(es)) {
    LL t,x; int type; tie(t,type,x)=es[i];
    if(type==0) Q.emplace(x);
    if(type==1) {
      assert(Q.count(x));
      Q.erase(Q.find(x));
    }
    if(type==2) {
      LL res=-1;
      if(SZ(Q)) res=*Q.begin();
      cout<<res<<endl;
    }
  }
}

void solve_org() {
  map<LL,vector<LL>> imos;
  REP(i,N) {
    LL s=S[i],t=T[i],x=X[i];
    imos[s-x].push_back(x);
    imos[t-x].push_back(-x);
  }
  vector<pair<LL,LL>> X;
  X.emplace_back(-Inf,Inf);
  multiset<LL> cur;
  FORR(kvp,imos) {
    LL d=kvp.first;
    vector<LL> xs=kvp.second;
    FORR(x,xs) {
      if(x>0) {
        cur.emplace(x);
      } else {
        x=-x;
        assert(cur.count(x));
        cur.erase(cur.find(x));
      }
    }
    LL xx=Inf;
    if(SZ(cur)) xx=*cur.begin();
    X.emplace_back(d,xx);
  }
  X.emplace_back(Inf,Inf);
//  dumpc(X);
  REP(i,Q) {
    auto p=upper_bound(ALL(X),make_pair(D[i],Inf))-X.begin();
    assert(p<SZ(X));
    --p;
    assert(p>=0);
    LL d,x; tie(d,x)=X[p];
    LL res=-1;
    if(x!=Inf) res=x;
//        dump(i,D[i],p,res);
    cout<<res<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>Q;
  REP(i,N) cin>>S[i]>>T[i]>>X[i];
  REP(i,Q) cin>>D[i];
  solve();
  
  return 0;
}
