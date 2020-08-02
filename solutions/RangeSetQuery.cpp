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
// $ cp-batch RangeSetQuery | diff RangeSetQuery.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address RangeSetQuery.cpp && ./a.out

/*

 8/2/2020

 5:49-6:33 TLE by Segment Tree with merging technique
 6:35 give up

 14:15-15:20 AC after skimming twitter timeline

 https://twitter.com/hanseilimak/status/1290029228793061376
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.st0ljnlzi21v
 https://img.atcoder.jp/abc174/editorial.pdf
 https://www.youtube.com/watch?v=h0MGG8rxrYc&t=7312s

 https://twitter.com/satanic0258/status/1289918972511436800
 https://twitter.com/laycrs/status/1289918974130442241
 https://qiita.com/tanakh/items/a312a9bd684658ab1e7b
 https://twitter.com/ei1333/status/1289918986503610370
 https://drken1215.hatenablog.com/entry/2019/01/01/234400
 https://twitter.com/small_onions/status/1289918942442594305
 https://twitter.com/kzyKT_M/status/1289919034805256193
 https://twitter.com/tsutaj/status/1289919112261451779
 https://twitter.com/kmjp_pc/status/1289919442965499904
 https://twitter.com/ajis_ka/status/1289919455456239618
 https://hama-du-competitive.hatenablog.com/entry/2016/10/01/001418
 https://twitter.com/kyuridenamida/status/1289920591114338304
 https://twitter.com/kyopro_friends/status/1289921223573430274

 */

const int MAX_N=1e6+1;
int C[MAX_N];
III qs[MAX_N];
int N,Q;

void solve() {
  sort(qs,qs+Q);
  BIT<int> bit(N+1);

  VI pos(N+1,-1);
  VI res(Q);
  int curr=0;
  REP(i, Q) {
    int l,r,j; tie(r,l,j)=qs[i];
    while(curr<r) {
      int c=C[curr];
      if(pos[c]!=-1) bit.add(pos[c],-1),pos[c]=-1;
      bit.add(curr,1),pos[c]=curr;
      ++curr;
    }
    res[j]=bit.query(l,r);
  }
  REP(i,Q) cout<<res[i]<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>Q;
  REP(i,N) cin>>C[i];
  REP(i,Q) {
    int l,r; cin>>l>>r;
    --l;
    qs[i]={r,l,i};
  }

  solve();
}

int main_tle() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int Q;
  cin>>N>>Q;
  vector<unordered_set<int>> C(N);
  REP(i,N) {
    int x; cin>>x;
    C[i]=unordered_set<int>({x});
    //dumpc(C[i]);
  }

  SegmentTree<unordered_set<int>> S(N, unordered_set<int>(), [](unordered_set<int> a, unordered_set<int> b) {
    if(SZ(a)>SZ(b)) swap(a,b);
    FORR(x,a) b.emplace(x);
    return b;
  });
  S.build(C);

  while(Q--) {
    int l,r; cin>>l>>r;
    --l;
    //dump(l,r);
    auto res=S.query(l,r);
    //dumpc(res);
    cout<<SZ(res)<<endl;
  }

  return 0;
}
