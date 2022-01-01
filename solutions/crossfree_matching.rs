#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch crossfree_matching | diff crossfree_matching.out -
// $ cargo run --bin crossfree_matching

///
/// 1/1/2022
///
/// 12:02-12:54 give up
/// 15:35 read editorial and got AC
///
/// https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.6y9b2zw0rpv6
/// https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.q12lnxesuljn
///

fn solve(n: usize, m: usize, mut a: Vec<(usize, usize)>) -> usize {
    a.sort_unstable_by_key(|&(a, b)| (a, Reverse(b)));

    let inf = n + 100;
    let mut dp = vec![inf; m + 10];
    let mut res = 0;
    for (_a, b) in a {
        let (mut bad, mut good) = (-1, m as i32 + 1);
        while (good - bad).abs() > 1 {
            let m = (good + bad) / 2;
            if dp[m as usize] >= b {
                good = m;
            } else {
                bad = m;
            }
        }
        let k = good as usize;
        res.setmax(k + 1);
        dp[k] = b;
        //dbgln!(a, b, good, dp);
    }
    res
}

#[allow(dead_code)]
fn solve_v0_shxt_impl(n: usize, m: usize, a: &Vec<(usize, usize)>, rev: bool) -> usize {
    let mut a = a.clone();
    if rev {
        a.sort_by_key(|&(a, b)| (a, Reverse(b)));
    } else {
        a.sort_unstable();
    }

    let inf = (n + 100, n + 100);
    let mut dp = vec![inf; m + 10];
    let mut res = 0;
    for (a, b) in a {
        let (mut bad, mut good) = (-1, m as i32 + 1);
        while (good - bad).abs() > 1 {
            let m = (good + bad) / 2;
            if dp[m as usize].1 >= b {
                good = m;
            } else {
                bad = m;
            }
        }
        let k = good as usize;
        if k == 0 || (dp[k - 1].0 < a && dp[k - 1].1 < b) {
            if b == dp[k].1 && a > dp[k].0 {
                //noop
            } else {
                res.setmax(k + 1);
                dp[k] = (a, b);
            }
        }
        dbgln!(a, b, good, dp);
    }
    res
}

fn main() {
    setup_out!(put, puts);

    let (n, m) = readln!(usize, usize);
    let a = readlns!(usize, usize; m);
    let res = solve(n, m, a);
    puts!("{}", res);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_random() {
        use rand::prelude::*;
        loop {
            let mut rng = thread_rng();
            let n = 5;
            let m = 5;
            let ab = (0..n)
                .map(|_| (rng.gen_range(1, 6), rng.gen_range(1, 6)))
                .collect_vec();

            let exp = solve_v0_shxt_impl(n, m, &ab, true);
            let act = solve_v0_shxt_impl(n, m, &ab, false);
            if act != exp {
                dbgln!(act, exp, ab);
            }
            assert_eq!(act, exp);
        }
    }
}

use crate::cplib::io::*;
use crate::cplib::minmax::*;
use crate::cplib::vec::*;
// region: cplib
#[rustfmt::skip]
#[allow(dead_code)]
pub mod cplib {
pub mod io {
	macro_rules! _with_dollar_sign { ($($body:tt)*) => { macro_rules! __with_dollar_sign { $($body)* } __with_dollar_sign!($); }}
	macro_rules! setup_out {
		($fn:ident,$fn_s:ident) => {
			use std::io::Write;
			let out = std::io::stdout();
			let mut out = ::std::io::BufWriter::new(out.lock());
				_with_dollar_sign! { ($d:tt) => {
				macro_rules! $fn { ($d($format:tt)*) => { let _ = write!(out,$d($format)*); } }
				macro_rules! $fn_s { ($d($format:tt)*) => { let _ = writeln!(out,$d($format)*); } }
			}}
		};
	}
	macro_rules! _epr { ($v:expr $(,)?) => {eprint!("{} = {:?}, ", stringify!($v), $v)}; }
	macro_rules! dbgln { ($($val:expr),*) => {{ eprint!("[{}:{}] ", file!(), line!()); ($(_epr!($val)),*); eprintln!(); }}; }
	pub fn readln_str() -> String {
		let mut line = String::new();
		::std::io::stdin().read_line(&mut line).unwrap_or_else(|e| panic!("{}", e));
		line
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
	macro_rules! readlns {
		($($t:tt),*; $n:expr) => {{ let stdin = ::std::io::stdin();
			::std::io::BufRead::lines(stdin.lock()).take($n).map(|line| {
				let line = line.unwrap(); #[allow(unused_mut)]let mut it = line.split_whitespace(); _read!(it; $($t),*)
			}).collect::<Vec<_>>()
		}};
	}
	macro_rules! readln {
		($($t:tt),*) => {{ let line = cplib::io::readln_str(); #[allow(unused_mut)]let mut it = line.split_whitespace(); _read!(it; $($t),*) }};
	}
	pub(crate) use {readlns, readln, setup_out, dbgln, _with_dollar_sign, _epr, _read};
}
pub mod minmax {
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
}
pub mod vec {
	pub trait CollectVec: Iterator { fn collect_vec(self) -> Vec<Self::Item> where Self: Sized { self.collect() } }
	impl<T> CollectVec for T where T: Iterator {}
	macro_rules! vvec {
		($v:expr; $n:expr) => { Vec::from(vec![$v; $n]) };
		($v:expr; $n:expr $(; $ns:expr)+) => { Vec::from(vec![vvec![$v $(; $ns)*]; $n]) };
	}
	pub(crate) use vvec;
}
}
// endregion: cplib
