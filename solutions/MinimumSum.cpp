#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
using namespace std;
// type alias
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 6/13/2018
 
 11:30-12:30 AC
 15:00-15:11 add solution without segment tree
 
 Editorials:
  - http://agc005.contest.atcoder.jp/data/agc/005/editorial.pdf
  - https://youtu.be/jT5HYYmrmMY?t=749
  - http://wk1080id.hatenablog.com/entry/2017/02/11/154313
   - set
  - https://kimiyuki.net/writeup/algo/atcoder/agc-005-b/
   - set with sentinel
  - http://hamko.hatenadiary.jp/entry/2018/01/04/105152
   - segment tree
  - https://pekempey.hatenablog.com/entry/2016/10/02/042213
   - union-find
 
 @tourist's solution:
  - https://beta.atcoder.jp/contests/agc005/submissions/904878
  - O(N) solution by enumerating from N to 1
  - Simulating doubly linked list. Very impressive implementation 👏
  - Double linked list works when removing one by one and modifying links 😅
 
 Summary:
  - I solved by myself though, segment tree was not necessary for permutation
  - Iterating from N to 1 is typical design to solve a problem of permutation
   - For either left or right, we are interested in positions of smaller values
   - Enumerationg from smaller to larger should be straightforward
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
// 11:30-12:30 AC
const int MAX_N=2e5+10;
struct Node {
  static const int Inf=1e9;
  int val;
  Node(int val=Inf): val(val) {}
  static Node IDE; // Identity element in monoid
};
// Merge operation should be associative A`op`(B`op`C) == (A`op`B)`op`C
Node Node::IDE=Node();
Node merge(const Node &a, const Node &b) {
  return Node(min(a.val,b.val));
}
// 🛠 Customize node of segment tree

struct SegmentTree {
public:
  int N__;
  // Put tree array outside the struct to avoid seg fault due to memory allocation of large size array
  Node Tree[4*MAX_N]; // Tree[0..2*N__-1] has values (Tree[0]: all, Tree[1]: left half, Tree[2]: right half, ..)
  SegmentTree(int N) {
    int n=1;
    // Init by power of 2
    while(n<N) n<<=1;
    for(int i=0; i<2*n-1; ++i) Tree[i]=Node::IDE;
    this->N__=n;
  }
  
  // Initialize tree with `ns`
  void build(const vector<Node> &ns) {
    buildTree(ns,0,0,N__);
  }
  
  // Update k-th (0-indexed) value
  void update(int i, const Node &x) {
    updateTree(i,x,0,0,N__);
  }
  
  // query in range [L,R)
  Node query(int L, int R) {
    return queryTree(L,R,0,0,N__);
  }
private:
  void buildTree(const vector<Node> &ns, int i, int l, int r) {
    if (l==r-1) { Tree[i]=ns[l]; return; }
    
    int mid=l+(r-l)/2;
    buildTree(ns,2*i+1,  l,mid); // left child
    buildTree(ns,2*i+2,mid,  r); // right child
    
    Tree[i]=merge(Tree[2*i+1],Tree[2*i+2]);
  }
  
  void updateTree(int p, const Node &x, int i, int l, int r) {
    if (l==r-1) { Tree[i]=x; return; }
    
    int mid=l+(r-l)/2;
    if(p<mid) updateTree(p,x,2*i+1,  l,mid);
    else      updateTree(p,x,2*i+2,mid,  r);
    
    Tree[i]=merge(Tree[2*i+1],Tree[2*i+2]);
  }
  
  Node queryTree(int L, int R, int i, int l, int r) {
    // out of range
    if (r<=L||R<=l) return Node::IDE;
    
    // all covered
    if (L<=l&&r<=R) return Tree[i];
    
    // partially covered
    int mid=l+(r-l)/2;
    Node a=queryTree(L,R,2*i+1,  l,mid);
    Node b=queryTree(L,R,2*i+2,mid,  r);
    Node res=merge(a,b);
    return res;
  }
};

const int MAX_NN=200000;
int N;
int A[MAX_NN+2];
int L[MAX_NN+2];
int R[MAX_NN+2];

void solve() {
  REP(i,N) {
    int n;
    cin>>n;
    A[n-1]=i;
  }
  
  LL res=0;
  set<int> S;
  REP(i,N) {
    int p=A[i];
    auto rit=S.upper_bound(p);
    int l,r;
    if(rit==S.end()) r=N-p;
    else r=*rit-p;
    if(S.empty()||rit==S.begin()) l=p+1;
    else l=p-*(--rit);
//    dump4(i,p,l,r);
    res+=1LL*(i+1)*l*r;
    S.emplace(p);
  }
  cout<<res<<endl;
}

void solve_org() {
  REP(i,N) cin>>A[i+1];
  A[0]=0,A[N+1]=0;
  ZERO(L),ZERO(R);
  SegmentTree LT(N+2);
  LT.update(0,0);
  FORE(i,1,N) {
    L[i]=i+LT.query(0,A[i]).val;
//    dump3(i,LT.query(0,A[i]).val,L[i]);
    Node x(-i);
    LT.update(A[i],x);
  }
  
  SegmentTree RT(N+2);
  RT.update(0,N+1);
  for(int i=N; i>0; --i) {
    R[i]=RT.query(0,A[i]).val-i;
//    dump3(i,RT.query(0,A[i]).val,R[i]);
    Node x(i);
    RT.update(A[i],x);
  }
  
  LL res=0;
  FORE(i,1,N) res+=1LL*A[i]*L[i]*R[i];
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  solve();
  return 0;
}
