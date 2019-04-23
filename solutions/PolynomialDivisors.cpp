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

// $ cp-batch PolynomialDivisors | diff PolynomialDivisors.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PolynomialDivisors.cpp && ./a.out

/*
 
 4/22/2019
 
 14:00-14:30 give up
 
 polynomial <=> ? (How can we use this conditin?)
 ∀x s.t. pred(x) <=> ? (How can we use ∀x condition?)
 
 14:30-17:40 read editorials and got AC
 
 http://drken1215.hatenablog.com/entry/2019/04/21/004100
 https://qiita.com/drken/items/6b4031ccbb2cab7436f3
 https://img.atcoder.jp/tenka1-2019/editorial.pdf
  - Explanation by @rng_58 is pretty impressive
  - The only necessary knowledge is Fermat's little theorem
 
 It turns out that first step is a|b <=> b≡0 (mod a)
 
 # Official editorial
 
 ∀x p|f(x) <=> ∀x f(x)≡0 (mod p)
 Because (x+p)^n≡x^n (mod p), f(x+p)≡f(x) (mod p)
 Now we can focus on x=0..p-1.
 Thus f(0)≡f(1)≡..f(p-1)≡0 (mod p)
 
 Generally f(x)=(x-a)*g(x)+r => f(a)=r
 f(a)=(x-a)*g(a)+r=r≡0 (mod p)
 That means f(x) is divisible by (x-a) (mod p)
 This condition holds for x=0,..,p-1
 f(x) is divisible by x(x-1)..(x-(p-1)) (mod p)
 
 By the way...
 x(x-1)..(x-(p-1))≡x^p-x (mod p)
 
 Proof:
 g(x):=x^p-x≡0 (mod p) because of Fermat's little theorem x^p≡x (mod p)
 This is generally true for x=0..p-1
 That means x^p-x≡x(x-1)..(x-(p-1))≡x(x-1)..(x-(p-1)) (mod p)
 
 Now we know x^p-x divides f(x) (mod p).
 
 f(x) id reduced to h(x) which is (p-1)-degree polynomial by x^p≡x (mod p)
 If h(x)=p*(B[p-1]*x^(p-1)+B[p-2]*x^(p-2)+..+B[0]), f(x) is divisible by `p`.
 We can test `p`<=N if it satisfies above.
 
 On the other hand, f(x)=p*(A[N]*x^n+..A[0]) may hold.
 Such `p` is gcd {A}
 
 # @rng_58's editorial
 
 ∀x p|f(x) <=> ∀x f(x)≡0 (mod p)
 By Fermat's little theorem, x^p≡x (mod p)
 
   f(x)
 = A[0]+A[1]*x..+A[N-1]*x^(N-1)+A[N]*x^N
 ≡ A[0]
  + (A[1]+A[p]+..)*x
  + (A[2]+A[p+1]+..)*x^2
  ..
  + (A[p-1]+A[2p-1]+..)*x^(p-1) = h(x) ≡ 0 (mod p)
 
 <=> A[0]≡(A[1]+A[p]+..)≡..≡(A[p-1]+A[2p-1]+..)≡0 (mod p) ...(A)
 
 1) p<=N
 
 Because f(x)!=h(x), we can check (A) for each `p`.
 This is easy to brute-force because p<=N<=1000
 
 2) p>N
 
 In this case, f(x)=h(x). We can just compute prime factors of gcd{A}
 
 @rng_58 is truly legend 🤔
 
 Summary:
  - Very tough problem. Tons of proof in number theory is needed 😞
  - divisible <=> b≡0 (mod a) is typical 😡
  - Reducing to limited search space by modular arithmetic is typical 😡
  - Polynomial congruent to `p` was first for me
 
 */

const int MAX_N=1e4+1;
LL A[MAX_N];
int N;

LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }
vector<int> sieve(int N) {
  if(N<=0) return {};
  vector<int> fs(N+1, true);
  fs[0]=fs[1]=false;
  for(int p=2; p*p<=N; ++p) if(fs[p]) {
    for(int q=p*p; q<=N; q+=p) fs[q]=false;
  }
  vector<int> res;
  for(int n=2; n<=N; ++n) if(fs[n]) res.push_back(n);
  return res;
}

vector<LL> primeFactors(LL n) {
  assert(n>=1);
  vector<LL> res;
  for(LL p=2; p*p<=n; ++p) while(n%p==0) {
    res.push_back(p);
    n/=p;
  }
  if(n>1) res.push_back(n);
  return res;
}
void solve() {
  set<LL> res;
  LL g=A[0];
  REP(i,N+1) g=gcd(abs(g),abs(A[i]));
  vector<LL> X=primeFactors(g);
  FORR(a,X) res.emplace(a);
  
  vector<int> P=sieve(N);
//  dumpc(P);
  FORR(p,P) {
    vector<LL> C(p);
    REP(n,p) C[n]=A[n]%p;
    FORE(n,p,N) {
      int nn=n%(p-1);
      if(nn==0) nn=p-1;
      C[nn]=(C[nn]+A[n]%p)%p;
    }
    bool ok=true;
    REP(i,p) ok&=(C[i]%p==0);
    if(ok) res.emplace(p);
  }
  FORR(p,res) cout<<p<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N+1) cin>>A[i];
  reverse(A,A+N+1);
  solve();
  
  return 0;
}
