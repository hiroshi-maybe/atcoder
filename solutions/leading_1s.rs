#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

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

// $ rs-cp-batch leading_1s | diff leading_1s.out -
// $ cargo run --bin leading_1s

///
/// 9/25/2021
///
/// 4:00-4:56 AC by digit dp
/// 9:58 read editorial and got AC with counting
///
/// https://atcoder.jp/contests/arc127/editorial/2686
///
/// https://twitter.com/laycrs/status/1441749339282423814?s=20
/// https://twitter.com/kiri8128/status/1441749990951440395?s=20
///

#[allow(dead_code)]
fn dig(s: &Vec<char>, i: usize) -> i32 {
    (s[i] as u8 - b'0') as i32
}
#[allow(dead_code)]
fn solve_dp() -> i64 {
    let n = readln!([char]);
    let l = n.len();

    // i, less, tail1, first dig?, count1
    let mut dp = vvec!(0i64; l+1; 2; 2; 2; l+1);
    for i in 0..l {
        dp[i][if i == 0 { 0 } else { 1 }][1][1][0] = 1;
        let curd = dig(&n, i);
        for less in 0..2 {
            for tail1 in 0..2 {
                for firstdig in 0..2 {
                    for count1 in 0..l {
                        let ld = if firstdig == 1 { 1 } else { 0 };
                        let rd = if less == 1 { 9 } else { curd };
                        for d in ld..=rd {
                            let delta = tail1 & (d == 1) as usize;
                            let less2 = less | ((curd != d) as usize);
                            dp[i + 1][less2][delta][0][count1 + delta] +=
                                dp[i][less][tail1][firstdig][count1];
                        }
                    }
                }
            }
        }
    }

    let mut res = 0;
    for less in 0..2 {
        for tail1 in 0..2 {
            for count1 in 0..=l {
                //dbgln!(less, tail1, dp[l][less][tail1][0]);
                res += dp[l][less][tail1][0][count1] * count1 as i64;
            }
        }
    }
    res
}

fn solve_count() -> i64 {
    let n: i64 = readln!(i64);

    let mut res = 0;

    let mut x = 0i64;
    for _ in 1..=15 {
        x = x * 10 + 1;
        let mut l = x;
        let mut r = x + 1;
        while l < (1i64 << 55) {
            let rr = min(r, n + 1);
            // dbgln!(l, rr, max(0, rr - l));
            res += max(0, rr - l);
            l *= 10;
            r *= 10;
        }
    }

    res
}

fn main() {
    setup_out!(put, puts);

    //let res = solve_dp(&n, l);
    let res = solve_count();

    puts!("{}", res);
}
