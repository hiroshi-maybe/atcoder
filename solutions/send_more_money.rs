#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch send_more_money | diff send_more_money.out -
// $ cargo run --bin send_more_money

///
/// 11/15/2021
///
/// 9:27-10:07, 21:05-21:41 AC
///
/// https://atcoder.jp/contests/abc198/editorial/1050
///

fn maps(ss: &Vec<Vec<usize>>, ds: &Vec<Option<usize>>) -> Vec<Vec<usize>> {
    let mut dsinv = vec![0; 26];
    for i in 0..10 {
        if let Some(d) = ds[i] {
            dsinv[d] = i;
        }
    }

    ss.iter()
        .map(|s| s.iter().map(|d| dsinv[*d]).collect_vec())
        .collect_vec()
}

fn s2n(s: &Vec<usize>) -> i64 {
    let mut res = 0;
    for i in 0..s.len() {
        res = 10 * res + s[i];
    }
    res as i64
}

fn ok(s: &Vec<Vec<usize>>, ds: &mut Vec<Option<usize>>) -> bool {
    let s = maps(s, ds);
    if s.iter().any(|s| s[0] == 0) {
        return false;
    }
    let n = s.iter().map(|s| s2n(s)).collect_vec();
    n[0] + n[1] == n[2]
}

fn dfs(i: usize, s: &Vec<Vec<usize>>, cs: &Vec<usize>, ds: &mut Vec<Option<usize>>) -> bool {
    if i == cs.len() {
        return ok(s, ds);
    }

    for d in 0..10 {
        if ds[d] == None {
            ds[d] = Some(cs[i]);
            if dfs(i + 1, s, cs, ds) {
                return true;
            }
            ds[d] = None;
        }
    }
    return false;
}

fn solve() -> Option<Vec<i64>> {
    let ss = readlns!([char]; 3);
    let mut s = vec![vec![]; 3];
    for i in 0..3 {
        s[i] = ss[i]
            .iter()
            .map(|c| (*c as u8 - b'a') as usize)
            .collect_vec();
    }

    let mut cs = s.iter().flatten().map(|d| *d as usize).collect_vec();
    cs.sort();
    cs.dedup();
    if cs.len() > 10 {
        return None;
    }

    let mut ds = vec![None; 10];
    if dfs(0, &s, &cs, &mut ds) {
        Some(maps(&s, &ds).iter().map(|s| s2n(s)).collect_vec())
    } else {
        None
    }
}

fn main() {
    setup_out!(put, puts);

    let res = solve();
    if let Some(res) = res {
        for s in res {
            puts!("{}", s);
        }
    } else {
        println!("UNSOLVABLE");
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
