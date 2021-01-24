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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif
template <typename T> struct MX {
  int N,M;
  MX(int N, int M) : N(N), M(M) {
    assert(N>0&&M>0);
    dat=vector<vector<T>>(N, vector<T>(M, 0));
  }
  MX(vector<vector<T>> &d) : dat(d) {
    assert(dat.size()>0&&dat[0].size()>0);
    N=dat.size(),M=dat[0].size();
  }
  inline vector<T>& operator [] (int i) {return dat[i]; }
  MX<T> &operator+=(MX<T> that) { dat=add(dat,that.dat); return *this; }
  MX<T> &operator-=(MX<T> that) { that*=-1,dat=add(dat,that.dat); return *this; }
  MX<T> &operator*=(MX<T> that) { dat=mult(dat,that.dat); return *this; }
  MX<T> &operator*=(T k) { dat=mult(dat,k); return *this; }
  MX<T> operator + (const MX<T> &that) const { return MX<T>(*this)+=that; }
  MX<T> operator - (const MX<T> &that) const { return MX<T>(*this)-=that; }
  MX<T> operator * (const MX<T> &that) const { return MX<T>(*this)*=that; }
  MX<T> operator * (const T &k) const { return MX<T>(*this)*=k; }
  bool operator==(MX<T> that) const { return dat==that.dat; }
  bool operator!=(MX<T> that) const { return dat!=that.dat; }
  // res = A^n, O(N^3*lg n) time
  MX<T> pow (long long n) const {
    assert(N==M);
    MX<T> res(N,N); for(int i=0; i<N; ++i) res.dat[i][i]=1;
    MX<T> a=MX<T>(*this);
    while(n>0) {
      if(n%2) res*=a;
      a*=a,n>>=1;
    }
    return res;
  }
  T det() {
    assert(N==M);
    T res=1;
    MX B(N,N);
    for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) B[i][j] = (*this)[i][j];
    for(int i=0; i<N; ++i) for(int j=i+1; j<N; ++j) {
      for (; B[j][i]!=0; res=-res) {
        T tm=B[i][i]/B[j][i];
        for(int k=i; k<N; ++k) {
          T t = B[i][k]-tm*B[j][k];
          B[i][k]=B[j][k];
          B[j][k]=t;
        }
      }
      res*=B[i][i];
    }
    return res;
  }
  MX inverse() {
    assert(N==N);
    MX B(N,2*N);
    for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) B[i][j] = (*this)[i][j];
    for(int i=0; i<N; ++i) B[i][N+i]=1;
    for(int i=0; i<N; ++i) {
      int pivot = i;
      for(int j=i; j<N; ++j) if(B[j][i]!=B[pivot][i]) pivot=j;
      assert(B[pivot][i]!=0); // regular?
      swap(B[i],B[pivot]);
      for(int j=i+1; j<=2*N; ++j) B[i][j]/=B[i][i];
      for(int j=0; j<N; ++j) if(i!=j) for(int k=i+1; k<=2*N; ++k) {
        B[j][k] -= B[j][i] * B[i][k];
      }
    }
    MX res(N,N);
    for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) res[i][j]=B[i][N+j];
    return res;
  }
  friend ostream& operator<<(ostream& os, const MX<T>& that) {
    for(int i=0; i<that.N; ++i) for(int j=0; j<that.M; ++j) os<<that.dat[i][j]<<",\n"[j==that.M-1];
    return os;
  }
private:
  vector<vector<T>> dat;
  // O(N^2) time
  vector<vector<T>> add(vector<vector<T>> &A, vector<vector<T>> &B) {
    assert(A.size()==B.size()&&A[0].size()==B[0].size());
    int N=A.size(),M=A[0].size();
    vector<vector<T>> res=vector<vector<T>>(N,vector<T>(M));
    for(int i=0; i<N; ++i) for(int j=0; j<M; ++j) res[i][j]=A[i][j]+B[i][j];
    return res;
  }
  // O(N^3) time
  vector<vector<T>> mult(vector<vector<T>> &A, vector<vector<T>> &B) {
    assert(A[0].size()==B.size());
    int NN=A.size(),MM=B[0].size(),L=A[0].size();
    vector<vector<T>> res=vector<vector<T>>(NN,vector<T>(MM));
    for(int i=0; i<NN; ++i) for(int j=0; j<MM; ++j) for(int k=0; k<L; ++k) res[i][j]+=A[i][k]*B[k][j];
    return res;
  }
  vector<vector<T>> mult(vector<vector<T>> &A, T k) {
    int N=A.size(),M=A[0].size();
    vector<vector<T>> res=vector<vector<T>>(N,vector<T>(M));
    for(int i=0; i<N; ++i) for(int j=0; j<M; ++j) res[i][j]=k*A[i][j];
    return res;
  }
};

namespace Affine2d {
  template<typename T> MX<T> point(T x, T y);
  template<typename T> T x(MX<T> mx);
  template<typename T> T y(MX<T> mx);
  template<typename T> MX<T> identity();
  template<typename T> MX<T> scale(T sx, T sy);
  template<typename T> MX<T> rotateCounterClockwise(T rad);
  template<typename T> MX<T> rotateCounterClockwise90();
  template<typename T> MX<T> rotateClockwise90();
  template<typename T> MX<T> translation(T dx, T dy);
  template<typename T> MX<T> translation(T dx, T dy);
  template<typename T> MX<T> reflectXaxis();
  template<typename T> MX<T> reflectYaxis();
}

template<typename T> MX<T> Affine2d::point(T x, T y) {
  vector<vector<T>> dat({
    {x},
    {y},
    {1}
  });
  return MX<T>(dat);
}
template<typename T> T Affine2d::x(MX<T> mx) { return mx[0][0]; }
template<typename T> T Affine2d::y(MX<T> mx) { return mx[1][0]; }
template<typename T> MX<T> Affine2d::identity() {
  vector<vector<T>> dat({
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
  });
  return MX<T>(dat);
}
template<typename T> MX<T> Affine2d::scale(T sx, T sy) {
  vector<vector<T>> dat({
    {sx, 0, 0},
    {0, sy, 0},
    {0,  0, 1}
  });
  return MX<T>(dat);
}
template<typename T> MX<T> Affine2d::rotateCounterClockwise(T rad) {
  vector<vector<T>> dat({
    {cos(rad), -sin(rad), 0},
    {sin(rad),  cos(rad), 0},
    {0,               0,  1}
  });
  return MX<T>(dat);
}
template<typename T> MX<T> Affine2d::rotateCounterClockwise90() {
  vector<vector<T>> dat({
    {0, -1, 0},
    {1,  0, 0},
    {0,  0, 1}
  });
  return MX<T>(dat);
}
template<typename T> MX<T> Affine2d::rotateClockwise90() {
  vector<vector<T>> dat({
    { 0, 1, 0},
    {-1, 0, 0},
    { 0, 0, 1}
  });
  return MX<T>(dat);
}
template<typename T> MX<T> Affine2d::translation(T dx, T dy) {
  vector<vector<T>> dat({
    {1, 0, dx},
    {0, 1, dy},
    {0, 0,  1}
  });
  return MX<T>(dat);
}
template<typename T> MX<T> Affine2d::reflectXaxis() {
  return Affine2d::scale(T(1),T(-1));
}
template<typename T> MX<T> Affine2d::reflectYaxis() {
  return Affine2d::scale(T(-1),T(1));
}

// $ cp-batch RotateAndFlip | diff RotateAndFlip.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address RotateAndFlip.cpp && ./a.out

/*

 1/23/2021

 4:21-5:38 AC

 https://youtu.be/u2woAs3M1c0?t=4964
 https://atcoder.jp/contests/abc189/editorial/539

 19:00-22:25 Add solution with Affine transform

 */

const int MAX_N=1e6+1;
LL X[MAX_N],Y[MAX_N];
int N,M;

void solve() {
  cin>>M;
  vector<MX<LL>> cum(M+1,MX<LL>(3,3));
  MX<LL> id=Affine2d::identity<LL>();
  cum[0]=id;

  REP(i,M) {
    int op; cin>>op;
    if(op==1) {
      cum[i+1]=Affine2d::rotateClockwise90<LL>()*cum[i];
    } else if (op==2) {
      cum[i+1]=Affine2d::rotateCounterClockwise90<LL>()*cum[i];
    } else if(op==3) {
      LL p; cin>>p;
      cum[i+1]=Affine2d::translation<LL>(2LL*p,0)*Affine2d::reflectYaxis<LL>()*cum[i];
    } else if(op==4) {
      LL p; cin>>p;
      cum[i+1]=Affine2d::translation<LL>(0,2LL*p)*Affine2d::reflectXaxis<LL>()*cum[i];
    }
  }

  int Q; cin>>Q;
  while(Q--) {
    int a,b; cin>>a>>b;
    --b;
    LL x=X[b],y=Y[b];
    auto p=Affine2d::point<LL>(x,y);
    auto res=cum[a]*p;
    cout<<res[0][0]<<" "<<res[1][0]<<endl;
  }
}

void solve_org() {
  cin>>M;
  vector<LL> xsum(M+1),ysum(M+1),xnegate(M+1),ynegate(M+1),flip(M+1);
  REP(i,M) {
    int op; cin>>op;
    xnegate[i+1]=xnegate[i];
    ynegate[i+1]=ynegate[i];

    if(op==1) {
      flip[i+1]=flip[i]^1;
      if(flip[i]) ynegate[i+1]^=1;
      else xnegate[i+1]^=1;
      ysum[i+1]=-xsum[i],xsum[i+1]=ysum[i];
    } else if (op==2) {
      flip[i+1]=flip[i]^1;
      if(flip[i]) xnegate[i+1]^=1;
      else ynegate[i+1]^=1;
      ysum[i+1]=xsum[i],xsum[i+1]=-ysum[i];
    } else if(op==3) {
      flip[i+1]=flip[i];
      LL p; cin>>p;
      xsum[i+1]=-xsum[i]+p*2;
      ysum[i+1]=ysum[i];
      if(!flip[i]) xnegate[i+1]^=1;
      else ynegate[i+1]^=1;
    } else if(op==4) {
      flip[i+1]=flip[i];
      LL p; cin>>p;
      xsum[i+1]=xsum[i];
      ysum[i+1]=-ysum[i]+p*2;
      if(!flip[i]) ynegate[i+1]^=1;
      else xnegate[i+1]^=1;
    }
  }

  int Q; cin>>Q;
  dump(Q);
  while(Q--) {
    int a,b; cin>>a>>b;
    dump(a,b);
    --b;
    LL x=X[b],y=Y[b];
    dump(x,y,xnegate[a],ynegate[a],flip[a],xsum[a],ysum[a]);
    if(xnegate[a]) x=-x;
    if(ynegate[a]) y=-y;
    if(flip[a]) swap(x,y);
    x+=xsum[a],y+=ysum[a];
    cout<<x<<" "<<y<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>X[i]>>Y[i];
  solve();

  return 0;
}
