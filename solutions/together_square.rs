#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch together_square | diff together_square.out -
// $ cargo run --bin together_square

///
/// 6/4/2022
///
/// 11:18-12:09 AC
///
/// https://atcoder.jp/contests/abc254/editorial/4065
///

fn solve() -> i64 {
    let n = readln!(usize);

    let mut sqcnt = vec![0; n + 1];
    for (cnt, x) in (1..=n).take_while(|x| x * x <= n).enumerate() {
        for i in (x * x..(x + 1) * (x + 1)).take_while(|&i| i <= n) {
            sqcnt[i] = cnt + 1;
        }
    }

    let s = LinearSieve::new(n);

    let mut res = 0i64;
    for i in 1..=n {
        let ps = s.fact(i);
        let mut map = HashMap::new();
        for p in ps {
            *map.entry(p).or_insert(0) += 1;
        }
        let mut jj = 1;
        for (k, cnt) in map {
            if cnt % 2 == 1 {
                jj *= k;
            }
        }
        res += sqcnt[n / jj] as i64;
    }

    res
}

fn main() {
    setup_out!(put, puts);

    let res = solve();
    puts!("{}", res);
}

// region: sieve

#[rustfmt::skip]
#[allow(dead_code)]
mod sieve {
	pub struct LinearSieve { n: usize, divp: Vec<usize>, }
	impl LinearSieve {
		pub fn new(n: usize) -> Self {
			let mut sieve = LinearSieve { n, divp: vec![0; n + 1], };
			for p in 2..=n {
				if sieve.divp[p] != 0 { continue; }
				sieve.divp[p] = p;
				for q in (p * p..).step_by(p).take_while(|q| q <= &n) {
					if sieve.divp[q] == 0 { sieve.divp[q] = p; }
				}
			}
			sieve
		}
		pub fn fact(&self, mut x: usize) -> Vec<usize> {
			let mut res = vec![];
			while x > 1 { res.push(self.divp[x]); x /= self.divp[x]; }
			res.sort_unstable();
			res
		}
		pub fn is_prime(&self, n: usize) -> bool {
			if n >= self.n { panic!("argument exceeds sieve table size") }
			n != 0 && self.divp[n] == n
		}
	}
}
pub use sieve::*;

// endregion: sieve

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
		fn setmin(&mut self, other: Self) -> bool;
		fn setmax(&mut self, other: Self) -> bool;
	}
	macro_rules! _set { ($self:ident, $cmp:tt, $other:ident) => {{
			let update = $other $cmp *$self;
			if update { *$self = $other; }
			update
	}}; }
	impl<T> SetMinMax for T where T: PartialOrd {
		fn setmin(&mut self, other: T) -> bool { _set!(self, <, other) }
		fn setmax(&mut self, other: T) -> bool { _set!(self, >, other) }
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
