#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;
use std::io::{BufWriter, Write};

macro_rules! with_dollar_sign { ($($body:tt)*) => {
	macro_rules! __with_dollar_sign { $($body)* }
	__with_dollar_sign!($);
}}
macro_rules! setup_out {
    ($fn:ident,$fn_s:ident) => {
        let out = std::io::stdout();
        let mut out = BufWriter::new(out.lock());
        with_dollar_sign! { ($d:tt) => {
            macro_rules! $fn { ($d($format:tt)*) => { let _ = write!(out,$d($format)*); } }
            macro_rules! $fn_s { ($d($format:tt)*) => { let _ = writeln!(out,$d($format)*); } }
        }}
    };
}
fn readln() -> String {
    let mut line = String::new();
    ::std::io::stdin()
        .read_line(&mut line)
        .unwrap_or_else(|e| panic!("{}", e));
    line
}
macro_rules! readlns {
	($($t:tt),*; $n:expr) => {{
		let stdin = ::std::io::stdin();
		let ret = ::std::io::BufRead::lines(stdin.lock()).take($n).map(|line| {
			let line = line.unwrap();
			let mut it = line.split_whitespace();
			_read!(it; $($t),*)
		}).collect::<Vec<_>>();
		ret
	}};
}
macro_rules! readln {
	($($t:tt),*) => {{
		let line = readln();
		#[allow(unused_mut)]
		let mut it = line.split_whitespace();
		_read!(it; $($t),*)
	}};
}
macro_rules! _read {
	($it:ident; [char]) => { _read!($it; String).chars().collect::<Vec<_>>() };
	($it:ident; [u8]) => { Vec::from(_read!($it; String).into_bytes()) };
	($it:ident; usize1) => { it.next().unwrap_or_else(|| panic!("input mismatch")).parse::<usize>().unwrap_or_else(|e| panic!("{}", e)) - 1 };
	($it:ident; [usize1]) => { $it.map(|s| s.parse::<usize>().unwrap_or_else(|e| panic!("{}", e)) - 1).collect::<Vec<_>>() };
	($it:ident; [$t:ty]) => { $it.map(|s| s.parse::<$t>().unwrap_or_else(|e| panic!("{}", e))).collect::<Vec<_>>() };
	($it:ident; $t:ty) => { $it.next().unwrap_or_else(|| panic!("input mismatch")).parse::<$t>().unwrap_or_else(|e| panic!("{}", e)) };
	($it:ident; $($t:tt),+) => { ($(_read!($it; $t)),*) };
}

// $ rs-cp-batch strange_lunchbox | diff strange_lunchbox.out -
// $ cargo run --bin strange_lunchbox

///
/// 9/18/2021
///
/// 6:01-6:14 AC
///

fn main() {
    setup_out!(put, puts);

    let n = readln!(usize);
    let (x, y) = readln!(usize, usize);
    let ab = readlns!(usize, usize; n);

    let inf = 1000;

    /*
    let mut dp = vec![vec![vec![inf; y + 1]; x + 1]; n + 1];
    dp[0][0][0] = 0;

    for i in 0..n {
        for a in 0..=x {
            for b in 0..=y {
                dp[i + 1][a][b] = min(dp[i + 1][a][b], dp[i][a][b]);
                let aa = min(a + ab[i].0, x);
                let bb = min(b + ab[i].1, y);
                dp[i + 1][aa][bb] = min(dp[i + 1][aa][bb], dp[i][a][b] + 1);
            }
        }
    }
    let mut res = dp[n][x][y] as i32;
    */

    let mut dp = vec![vec![inf; y + 1]; x + 1];
    dp[0][0] = 0;
    for (a, b) in ab {
        for aa in (0..=x).rev() {
            for bb in (0..=y).rev() {
                let a = min(aa + a, x);
                let b = min(bb + b, y);
                dp[a][b] = min(dp[a][b], dp[aa][bb] + 1);
            }
        }
    }
    let mut res = dp[x][y] as i32;
    if res == inf {
        res = -1;
    }

    puts!("{}", res);
}
