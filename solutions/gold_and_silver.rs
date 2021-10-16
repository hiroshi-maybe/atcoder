#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// region: io
#[rustfmt::skip]
#[macro_use]
#[allow(dead_code)]
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
	macro_rules! _epr { ($v:expr $(,)?) => {eprint!("{} = {:?}, ", stringify!($v), $v)}; }
	macro_rules! dbgln { ($($val:expr),*) => {{ eprint!("[{}:{}] ", file!(), line!()); ($(_epr!($val)),*); eprintln!(); }}; }
	pub fn readln() -> String {
		let mut line = String::new();
		::std::io::stdin().read_line(&mut line).unwrap_or_else(|e| panic!("{}", e));
		line
	}
	macro_rules! readlns {
		($($t:tt),*; $n:expr) => {{ let stdin = ::std::io::stdin();
			::std::io::BufRead::lines(stdin.lock()).take($n).map(|line| {
				let line = line.unwrap(); #[allow(unused_mut)]let mut it = line.split_whitespace(); _read!(it; $($t),*)
			}).collect::<Vec<_>>()
		}};
	}
	macro_rules! readln {
		($($t:tt),*) => {{ let line = io::readln(); #[allow(unused_mut)]let mut it = line.split_whitespace(); _read!(it; $($t),*) }};
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
}
// endregion: io

// $ rs-cp-batch gold_and_silver | diff gold_and_silver.out -
// $ cargo run --bin gold_and_silver

///
/// 10/16/2021
///
/// 5:00-6:23 AC
///
/// https://atcoder.jp/contests/arc128/editorial/2787
/// https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.nyosp5o9kzg3
/// https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.vbnf8dupd17
///
/// https://twitter.com/laycrs/status/1449374631207391233
/// https://twitter.com/kuuso1/status/1449376027759681540
/// https://twitter.com/heno_code/status/1449375992519163908
/// https://twitter.com/kuretchi/status/1449375692794171399
/// https://twitter.com/kzyKT_M/status/1449374983491186692
///

#[allow(dead_code)]
fn solve_v0(n: usize, a: Vec<i64>) -> Vec<i32> {
    let mut res = vec![0; n + 1];
    res[0] = 1;
    for i in 1..n {
        if a[i - 1] < a[i] {
            res[i] = 1
        } else if a[i - 1] > a[i] {
            res[i] = -1;
        }
    }
    res[n] = 1;
    for i in 1..n {
        if res[i] == 0 {
            res[i] = res[i - 1];
        }
    }
    //dbgln!(res);
    let mut pv = vec![-1; n + 1];
    for i in 1..=n {
        if res[i - 1] == 1 && res[i] == -1 {
            pv[i] = 1; // peak
        } else if res[i - 1] == -1 && res[i] == 1 {
            pv[i] = 0; // valley
        }
    }
    //dbgln!(pv);
    let mut cur = 1;
    let mut ans = vec![0; n];
    for i in 1..=n {
        if pv[i] == cur {
            ans[i - 1] = 1;
            cur = 1 - cur;
        }
    }

    ans
}

#[allow(dead_code)]
fn solve_v1(n: usize, a: Vec<i64>) -> Vec<i32> {
    let mut res = vec![0; n];
    for i in 0..n - 1 {
        if a[i] > a[i + 1] {
            res[i] ^= 1;
            res[i + 1] = 1;
        }
    }
    res
}

fn main() {
    setup_out!(put, puts);

    let n = readln!(usize);
    let a = readln!([i64]);

    let ans = solve_v1(n, a);

    for i in 0..n {
        put!("{} ", ans[i]);
    }
    puts!("");
}
