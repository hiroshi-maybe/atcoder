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

// $ cp-batch LevelKPalindrome | diff LevelKPalindrome.out -
// $ g++ -std=c++17 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address LevelKPalindrome.cpp && ./a.out

/*

 4/17/2021

 0:35-1:57 WA
 2:20 give up

 4/18/2021

 21:50-23:50 read editorials, added stress test, found that considering the center character was missing and got AC

 https://atcoder.jp/contests/jsc2021/submissions/21828529
 https://atcoder.jp/contests/jsc2021/editorial/1112

 https://twitter.com/kiri8128/status/1383347143767859202
 https://twitter.com/heno_code/status/1383315908655935491
 https://twitter.com/kzyKT_M/status/1383347076344410123
 https://twitter.com/evima0/status/1383347619955576835
 https://twitter.com/ei1333/status/1383347707029245962
 https://twitter.com/tomerun/status/1383347417462972421
 https://twitter.com/kenkoooo/status/1383348567075553282
 https://twitter.com/laycrs/status/1383349078512181253

 */

int K;
string S;

bool ispalin(string s) {
  /*
  int l=0,r=SZ(s)-1;
  while(l<r) {
    if(s[l]!=s[r]) return false;
    ++l,--r;
  }
  return true;*/
  string t=s;
  reverse(ALL(t));
  return s==t;
}

bool ok=true;
vector<pair<bool,string>> xs;
map<int, VI> cen;
void f(string s, int L, bool dir) {
  //dump(s,L,dir);
  if(SZ(s)==0) {
    if(L!=0) ok=false;
    return;
  }
  if(L==0) {
    if(SZ(s)==1) ok=false;
    xs.emplace_back(dir,s);
    return;
  }

  int N=SZ(s);
  if(N%2==1) {
    cen[L].push_back(s[N/2]-'a');
    f(s.substr(0,N/2),L-1,dir);
    f(s.substr(N/2+1,N/2), L-1,L==1?!dir:dir);
  } else {
    f(s.substr(0,N/2),L-1,dir);
    f(s.substr(N/2,N/2), L-1,L==1?!dir:dir);
  }
}
string solve() {
  ok=true,xs.clear(),cen.clear();
  f(S,K,0);

  //dumpc(xs);
  //dumpc(cen);

  if(!ok) return "impossible";

  int cencen=0;
  FORR(kvp, cen) {
    VI cnts(26);
    FORR(c,kvp.second) cnts[c]++;
    cencen+=SZ(kvp.second)-*max_element(ALL(cnts));
  }

  if(xs.empty()) return to_string(cencen);

  vector<string> ys;
  FORR(x,xs) {
    if(!x.first) ys.emplace_back(x.second);
    else {
      string s=x.second;
      reverse(ALL(s));
      ys.emplace_back(s);
    }
  }

  int N=SZ(ys[0]),M=SZ(ys);
  string x;
  VV<II> cnts(N);
  REP(i,N) {
    vector<II> cnt(26,{0,0});
    REP(i,26) cnt[i].second=i;
    REP(j,M) {
      cnt[ys[j][i]-'a'].first++;
    }
    sort(ALL(cnt)),reverse(ALL(cnt));
    REP(j,26)cnts[i].push_back(cnt[j]);
  }
  int res=0;
  REP(i,N) {
    x.push_back('a'+cnts[i][0].second);
    res+=M-cnts[i][0].first;
  }

  //dumpc(ys);
  //dump(x,ispalin(x),res);

  if(!ispalin(x)) {
    return to_string(res+cencen);
  }

  int ans=1e8;
  REP(i,N) {
    if(N%2==1&&i==N/2) continue;
    int a=res+cencen;
    a-=M-cnts[i][0].first;
    a+=M-cnts[i][1].first;
    //dump(i,cnts[i][1].first,char('a'+cnts[i][1].second),ans);
    //x[i]='a'+cnts[i][1].second;
    //assert(!ispalin(x));
    //x[i]='a'+cnts[i][0].second;
    SMIN(ans,a);
  }
  return to_string(ans);
}

// https://atcoder.jp/contests/jsc2021/submissions/21828529
template <typename T> bool chmin(T &m, const T q) { if (m > q) {m = q; return true;} else return false; }
string expected(){
  bool die=false;
    const int N = S.size();
    int len = N;

    vector<int> D(N);
    int l0 = 0;
    auto rec = [&](auto self, int head, int len, int k, bool rev) -> void {
        if (k and !len) {
          die=true;
          return;
        }
        if (k == 0) {
            l0 = len;
            if (len == 1) {
              die=true;
              return;
            }
            int cnt = K + 1;
            if (rev) for(int i=head + len-1; i>=head; --i) D[i] = cnt++;
            if (!rev) FOR(i, head, head + len) D[i] = cnt++;
        } else {
            if (len % 2) D[head + len / 2] = k;
            self(self, head, len / 2, k - 1, rev);
            self(self, head + (len + 1) / 2, len / 2, k - 1, k == 1 ? !rev : rev);
        }
    };
    rec(rec, 0, N, K, false);
    if(die) return "impossible";

    map<int, vector<int>> mp;
    REP(i, N) {
        if (!mp.count(D[i])) mp[D[i]] = vector<int>(26, 0);
        mp[D[i]][S[i] - 'a']++;
    }

    int ret = 0;
    vector<vector<int>> cnt;
    for (auto [k, v] : mp) {
        if (k <= K) {
            ret += accumulate(ALL(v), 0) - *max_element(ALL(v));
        } else {
            cnt.push_back(v);
        }
    }


    string cum;
    vector<int> argmax;
    cnt.resize(l0);
    int tmp = 0;
    for (auto v : cnt) {
        int c = max_element(ALL(v)) - v.begin();
        cum += 'a' + c;
        argmax.push_back(c);
        tmp += accumulate(ALL(v), 0) - v[c];
    }

    assert(cum.size() == l0);

    {
        auto cr = cum;
        reverse(ALL(cr));
        assert(cr.size() != 1);
        if (cr == cum and cr.size()) {
            int red = 1 << 30;
            REP(i, cum.size()) {
                if (i * 2 + 1 == cum.size()) continue;
                auto sum = accumulate(ALL(cnt[i]), 0);
                REP(d, 26) if (d != argmax[i]) chmin(red, -(sum - cnt[i][argmax[i]]) + (sum - cnt[i][d]));
            }
            tmp += red;
        }
    }


    return to_string(ret + tmp);
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template <typename Integer>
Integer genRandNum(Integer lb, Integer ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  Integer x = rnd() % (Integer)(ub - lb);
  return x + lb;
}
template <typename Integer>
vector<Integer> genRandSeq(int size, Integer lb, Integer ub) {
  if (size==0) return {};
  vector<Integer> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}
void test() {
  K=genRandNum(0,100);
  int N=genRandNum(1,1000);
  VI s=genRandSeq(N,0,26);
  S=string(N,'a'); REP(i,N) S[i]='a'+s[i];

  auto exp=expected(),act=solve();
  if(exp!=act) {
    dump(K,S);
    dump(exp,act);
  }
  assert(exp==act);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //while(true) test();

  cin>>K>>S;
  cout<<solve()<<endl;

  return 0;
}
