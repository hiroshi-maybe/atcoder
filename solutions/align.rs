#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch align | diff align.out -
// $ cargo run --bin align

///
/// 2/9/2022
///
/// 9:30-10:20 give up
/// 10:31 read editorial and AC
///
/// https://img.atcoder.jp/tenka1-2018/editorial.pdf
///

fn f(mut sign: bool, a: &Vec<i64>) -> i64 {
    let n = a.len();
    let mut cs = (0..n)
        .map(|i| {
            let c = if i == 0 || i == n - 1 { 1 } else { 2 };
            let res = if sign { c } else { -c };
            sign = !sign;
            res
        })
        .collect_vec();

    cs.sort_unstable();
    cs.iter().zip(a.iter()).map(|(&c, &a)| c * a).sum::<i64>()
}

fn solve() -> i64 {
    let n = readln!(usize);
    let mut a = readlns!(i64; n);
    a.sort_unstable();

    max(f(true, &a), f(false, &a))
}

#[allow(dead_code)]
fn solve_wa() -> i64 {
    let n = readln!(usize);
    let mut a = readlns!(i64; n);
    a.sort_unstable();

    // let mut res = 0;
    // let mut ps = vec![];
    // for p in a.permutations() {
    //     let sum = p.windows(2).map(|xs| (xs[1] - xs[0]).abs()).sum::<i64>();
    //     if res < sum {
    //         res = sum;
    //         ps.clear();
    //     }
    //     if res <= sum {
    //         ps.push(p.iter().copied().collect_vec());
    //     }
    // }

    // dbgln!(res);
    // dbgln!(ps);

    let mut res = 0;
    let mut q = a.iter().copied().collect::<VecDeque<_>>();
    let init = *q.front().unwrap();
    let mut cur = (init, init);
    q.pop_front();
    let mut back = true;
    while !q.is_empty() {
        let (x1, x2) = if back {
            (q.pop_back().unwrap(), q.pop_back())
        } else {
            (q.pop_front().unwrap(), q.pop_front())
        };
        if let Some(x2) = x2 {
            res += (cur.0 + cur.1 - (x1 + x2)).abs();
            cur = (x1, x2);
        } else {
            res += max((x1 - cur.0).abs(), (x1 - cur.1).abs());
            break;
        }
        back = !back;
    }

    res
}

fn main() {
    setup_out!(put, puts);

    let res = solve();
    puts!("{}", res);
}

// region: next_permutation

#[rustfmt::skip]
#[allow(dead_code)]
mod permutation {
	pub fn next_permutation<T>(xs: &mut [T]) -> bool where T: std::cmp::Ord {
		let asc_i = match xs.windows(2).rposition(|w| w[0] < w[1]) {
			Some(i) => i,
			None => { return false; }
		};
		let min_larger_offset = xs[asc_i + 1..]
			.binary_search_by(|x| match xs[asc_i].cmp(x) {
				std::cmp::Ordering::Equal => std::cmp::Ordering::Greater,
				ord => ord,
			})
			.unwrap_err();
		xs.swap(asc_i, asc_i + min_larger_offset);
		xs[asc_i + 1..].reverse();
		true
	}
	pub trait Permutations<T> { fn permutations(&self) -> Permutation<'_, T> where Self: Sized; }
	impl<T> Permutations<T> for Vec<T> where T: std::cmp::Ord {
		fn permutations(&self) -> Permutation<'_, T> { Permutation::new(&self[..]) }
	}
	pub struct Permutation<'a, T> { next_perm: Option<Vec<&'a T>>, }
	impl<'a, T: std::cmp::Ord> Permutation<'a, T> {
		fn new(dat: &'a [T]) -> Permutation<'a, T> {
			Permutation { next_perm: Some(dat.iter().map(|x| x).collect::<Vec<_>>()) }
		}
	}

	impl<'a, T: std::cmp::Ord> Iterator for Permutation<'a, T> {
		type Item = Vec<&'a T>;
		fn next(&mut self) -> Option<Self::Item> {
			if let Some(perm) = &mut self.next_perm {
				let res = perm.clone();
				if !next_permutation(perm) { self.next_perm = None; }
				Some(res)
			} else {
				None
			}
		}
	}
}
pub use permutation::{next_permutation, Permutations};

// endregion: next_permutation

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
