#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

#[rustfmt::skip]
#[macro_use]
#[allow(unused_mut)]
mod io {
    macro_rules! with_dollar_sign { ($($body:tt)*) => { macro_rules! __with_dollar_sign { $($body)* } __with_dollar_sign!($); }}
    macro_rules! setup_out {
        ($fn:ident,$fn_s:ident) => {
            use std::io::Write;
            let out = std::io::stdout();
            let mut out = ::std::io::BufWriter::new(out.lock());
            with_dollar_sign! { ($d:tt) => {
                macro_rules! $fn { ($d($format:tt)*) => { let _ = write!(out,$d($format)*); } }
                macro_rules! $fn_s { ($d($format:tt)*) => { let _ = writeln!(out,$d($format)*); } }
            }}
        };
    }
    pub fn readln() -> String {
        let mut line = String::new();
        ::std::io::stdin().read_line(&mut line).unwrap_or_else(|e| panic!("{}", e));
        line
    }
    macro_rules! readlns {
        ($($t:tt),*; $n:expr) => {{ let stdin = ::std::io::stdin();
            ::std::io::BufRead::lines(stdin.lock()).take($n).map(|line| {
                let line = line.unwrap();
                let mut it = line.split_whitespace();
                _read!(it; $($t),*)
            }).collect::<Vec<_>>()
        }};
    }
    macro_rules! readln {
        ($($t:tt),*) => {{ let line = io::readln(); let mut it = line.split_whitespace(); _read!(it; $($t),*) }};
    }
    macro_rules! _read {
        ($it:ident; [char]) => { _read!($it; String).chars().collect::<Vec<_>>() };
        ($it:ident; [u8]) => { Vec::from(_read!($it; String).into_bytes()) };
        ($it:ident; usize1) => { $it.next().unwrap_or_else(|| panic!("input mismatch")).parse::<usize>().unwrap_or_else(|e| panic!("{}", e)) - 1 };
        ($it:ident; [usize1]) => { $it.map(|s| s.parse::<usize>().unwrap_or_else(|e| panic!("{}", e)) - 1).collect::<Vec<_>>() };
        ($it:ident; [$t:ty]) => { $it.map(|s| s.parse::<$t>().unwrap_or_else(|e| panic!("{}", e))).collect::<Vec<_>>() };
        ($it:ident; $t:ty) => { $it.next().unwrap_or_else(|| panic!("input mismatch")).parse::<$t>().unwrap_or_else(|e| panic!("{}", e)) };
        ($it:ident; $($t:tt),+) => { ($(_read!($it; $t)),*) };
    }
    macro_rules! _epr { ($v:expr $(,)?) => {eprint!("{} = {:?}, ", stringify!($v), $v)}; }
    macro_rules! dbgln { ($($val:expr),*) => {{ eprint!("[{}:{}] ", file!(), line!()); ($(_epr!($val)),*); eprintln!(); }}; }
}

// $ rs-cp-batch make_10 | diff make_10.out -
// $ cargo run --bin make_10

///
/// 9/19/2021
///
/// 8:21-8:47 pause
///
/// 9/20/2021
///
/// 8:45-9:48 AC
///
/// https://atcoder.jp/contests/arc126/editorial/2623
///

#[rustfmt::skip]
#[macro_use]
#[allow(unused_mut, dead_code)]
mod dp {
    pub trait SetMinMax {
        fn setmin<'a>(&'a mut self, other: Self) -> (bool, &'a Self);
        fn setmax<'a>(&'a mut self, other: Self) -> (bool, &'a Self);
    }
    macro_rules! _set { ($self:ident, $cmp:tt, $other:ident) => {{
            let update = $other $cmp *$self;
            if update { *$self = $other; }
            (update, $self)
    }}; }
    impl<T> SetMinMax for T where T: PartialOrd {
        fn setmin<'a>(&'a mut self, other: T) -> (bool, &'a Self) { _set!(self, <, other) }
        fn setmax<'a>(&'a mut self, other: T) -> (bool, &'a Self) { _set!(self, >, other) }
    }
    macro_rules! vvec {
        ($v:expr; $n:expr) => { Vec::from(vec![$v; $n]) };
        ($v:expr; $n:expr $(; $ns:expr)+) => { Vec::from(vec![vvec![$v $(; $ns)*]; $n]) };
    }
}
use dp::*;

fn f3(mut n2: i64, mut n3: i64, mut n4: i64) -> i64 {
    //dbg!(n2, n3, n4);
    let x = min(n3 / 2, n4 + n2 / 2);
    n3 -= x * 2;
    let y = min(x, n4);
    n4 -= y;
    n2 -= (x - y) * 2;

    let z = min(n2, n4 / 2);
    n2 -= z;
    n4 -= n4 / 2 * 2;
    let mut a = 0;
    if n4 > 0 && n2 >= 3 {
        assert!(n4 == 1);
        n2 -= 3;
        a += 1;
    }
    dbgln!(n2, n3, n4);
    //dbg!(x, z, n2 / 5);

    x + z + a + n2 / 5
}

#[allow(dead_code)]
const INF: i64 = -1000_000_000;
#[allow(dead_code)]
fn fdp(n2: usize, n3: usize, n4: usize) -> i64 {
    let mut dp = vvec![INF; 11; 11; 11; 11];
    dp[0][0][0][0] = 0;
    let mut res = 0;
    for a in 0..=n2 {
        for b in 0..=n3 {
            for c in 0..=n4 {
                for d in 0..10 {
                    let cur = dp[a][b][c][d];
                    if d + 2 <= 10 && a < n2 {
                        let dd = (d + 2) % 10;
                        dp[a + 1][b][c][dd].setmax(cur + ((d + 2) / 10) as i64);
                        let (u, val) = res.setmax(dp[a + 1][b][c][dd]);
                        if u {
                            dbgln!(a + 1, b, c, dd, val);
                        }
                        dp[a + 1][b][c][d].setmax(cur);
                    }
                    if d + 3 <= 10 && b < n3 {
                        let dd = (d + 3) % 10;
                        dp[a][b + 1][c][dd].setmax(cur + ((d + 3) / 10) as i64);
                        let (u, val) = res.setmax(dp[a][b + 1][c][dd]);
                        if u {
                            dbgln!(a, b + 1, c, dd, val);
                        }
                        dp[a][b + 1][c][d].setmax(cur);
                    }
                    if d + 4 <= 10 && c < n4 {
                        let dd = (d + 4) % 10;
                        dp[a][b][c + 1][dd].setmax(cur + ((d + 4) / 10) as i64);
                        res.setmax(dp[a][b][c + 1][dd]);
                        dp[a][b][c + 1][d].setmax(cur);
                    }
                }
            }
        }
    }
    res
}

#[allow(dead_code)]
fn test() {
    for n2 in 0..=5 {
        for n3 in 0..=5 {
            for n4 in 0..=5 {
                let act = f3(n2, n3, n4);
                let exp = fdp(n2 as usize, n3 as usize, n4 as usize);
                dbgln!(n2, n3, n4);
                println!("{} vs {}", act, exp);
                assert!(act == exp);
            }
        }
    }
}

fn main() {
    setup_out!(put, puts);

    // test();

    let t = readln!(usize);
    for (n2, n3, n4) in readlns!(i64, i64, i64; t) {
        let res1 = f3(n2, n3, n4);

        puts!("{}", res1);
    }
    dbgln!();
}
