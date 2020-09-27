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

template <typename Val, // x∈S (Monoid) for f(x)
  Val (*id)(),  // Identity element for S
  Val (*merge)(Val, Val), // Merge x and y
  typename Delay, // Parameters for f_i∈F
  Delay (*delayId)(), // Identity element for F
  Val (*apply)(Val, Delay), // f_i(x)
  /* mergeDelay(g, f), f(g(x)) */
  Delay (*mergeDelay)(Delay, Delay)> // f_i∘f_j∈F
struct LazySegmentTree {
  int N_/* adjusted N*/,head/* head of leaf */;
  vector<Val> tree;
  vector<Delay> delay;
public:
  LazySegmentTree(int N) { prep(N); }
  LazySegmentTree(vector<Val> A) { prep(A.size()),this->build(A); }
  LazySegmentTree& prep(int N) {
    int n=1; while(n<N) n<<=1; // Init by power of 2
    this->tree=vector<Val>(2*n-1,id()),this->delay=vector<Delay>(2*n-1,delayId());
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
    if(tr<=ql||qr<=tl) return id(); // out of range
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
    if(i<head) pushdownAt(i);
    tree[i]=apply(tree[i],delay[i]),delay[i]=delayId();
  }
  void pushdownAt(int i) { mergeDelayAt(2*i+1,delay[i]),mergeDelayAt(2*i+2,delay[i]); }
  void mergeDelayAt(int i, Delay d) { delay[i]=mergeDelay(delay[i],d); }
};

const int MOD=998244353;
struct ModInt {
  unsigned int val;
  ModInt(): val(0) {}
  ModInt(int v) { norm(v%MOD); }
  ModInt(long long v) { norm(v%MOD); }
  ModInt& norm(long long v) {
    v=v<0?v%MOD+MOD:v; // negative
    v=v>=MOD?v-MOD:v; // mod
    val=(unsigned int)v;
    return *this;
  }
  explicit operator bool() const { return val!=0; }
  ModInt operator-() const { return ModInt(0)-*this; }
  ModInt &operator+=(ModInt that) { return norm((long long)val+that.val); }
  ModInt &operator-=(ModInt that) { return norm((long long)val-that.val); }
  ModInt &operator*=(ModInt that) { val=(unsigned long long)val*that.val%MOD; return *this; }
  ModInt &operator/=(ModInt that) { return *this*=that.inv(); }
  ModInt operator+(ModInt that) const { return ModInt(*this)+=that; }
  ModInt operator-(ModInt that) const { return ModInt(*this)-=that; }
  ModInt operator*(ModInt that) const { return ModInt(*this)*=that; }
  ModInt operator/(ModInt that) const { return ModInt(*this)/=that; }
  ModInt pow(long long n) const {
    ModInt x=*this, res=1;
    while(n>0) {
      if(n&1) res*=x;
      x*=x,n>>=1;
    }
    return res;
  }
  ModInt inv() const { return (*this).pow(MOD-2); }
  bool operator==(ModInt that) const { return val==that.val; }
  bool operator!=(ModInt that) const { return val!=that.val; }
  friend ostream& operator<<(ostream& os, const ModInt& that) { return os<<that.val; }
};

// $ cp-batch ReplaceDigits | diff ReplaceDigits.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ReplaceDigits.cpp && ./a.out

/*

 9/26/2020

 5:27-6:45 give up
 8:50-10:30 read editorials and got AC with ACL
 10:41 AC with my own segment tree with lazy propagation

 https://tiramistercp.hatenablog.com/entry/abl-e
 https://www.youtube.com/watch?v=D0Op33UL_cA&t=4755s

 */

const ModInt inv9=ModInt(1)/9;
int N,Q;

struct S {
    ModInt val,p10;
};

struct F {
    int d;
    //bool operator==(F that) const { return d==that.d; }
};

S op(S a, S b) { return S{a.val*b.p10+b.val, a.p10*b.p10}; }

S e() { return S{0, 1}; }

S mapping(S s, F f) {
  if(f.d==0) return s;
  return S{(s.p10-1)*inv9*f.d, s.p10};
}

F composition(F f, F g) {
  //if(f.d==0) return g;
  //return f;
  if(g.d==0) return f;
  return g;
}

F id() { return F{0}; }

void solve() {
  vector<S> A(N);
  REP(i,N) A[i]=S{1,10};
  LazySegmentTree<S,e,op,F,id,mapping,composition> seg(A);
  //dump(seg.all_prod().val);
  while(Q--) {
    int l,r,d; cin>>l>>r>>d;
    --l;
    //dump(l,r);
    seg.update(l,r,F{d});
    cout<<seg.query(0,N).val<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>Q;
  solve();

  return 0;
}
