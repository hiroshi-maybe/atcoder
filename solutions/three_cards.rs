#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch three_cards | diff three_cards.out -
// $ cargo run --bin three_cards

///
/// 8/20/2022
///
/// 9:14-9:39 WA
/// 13:10-13:49 AC
///
/// https://atcoder.jp/contests/arc146/editorial/4590
///

fn solve(a: &Vec<i64>) -> i64 {
    let mut b = vec![vec![]; 7];
    for &a in a {
        let s = a.to_string();
        b[s.len()].push(a);
    }
    for x in &mut b {
        x.sort_unstable();
    }

    // dbgln!(b);
    let mut res = 0;
    for l1 in 1..b.len() {
        if let Some(x) = b[l1].pop() {
            for l2 in 1..b.len() {
                if let Some(y) = b[l2].pop() {
                    for l3 in 1..b.len() {
                        if let Some(z) = b[l3].pop() {
                            let mut xs = vec![(x, l1), (y, l2), (z, l3)];
                            xs.sort_unstable();
                            for xs in xs.permutations() {
                                let mut ans = xs[0].0;
                                ans = ans * 10i64.pow(xs[1].1 as u32) + xs[1].0;
                                ans = ans * 10i64.pow(xs[2].1 as u32) + xs[2].0;
                                // dbgln!(ans, xs);
                                res.setmax(ans);
                            }
                            b[l3].push(z);
                        }
                    }
                    b[l2].push(y);
                }
            }
            b[l1].push(x);
        }
    }

    res
}

fn main() {
    setup_out!(put, puts);

    let _n = readln!(usize);
    let a = readln!([i64]);
    let res = solve(&a);
    puts!("{}", res);
}

#[test]
fn test_bruteforce() {
    use rand::prelude::*;

    let mut rng = thread_rng();

    let l = 5;

    loop {
        let mut a = (0..l).map(|_| rng.gen_range(1, 100)).collect_vec();

        let act = solve(&a);

        let mut exp = 0;
        a.sort_unstable();
        for a in a.permutations() {
            let mut s = a[0].to_string();
            s.push_str(&a[1].to_string());
            s.push_str(&a[2].to_string());
            let ans = s.parse().unwrap();
            exp.setmax(ans);
        }
        if exp != act {
            dbgln!(exp, act, a);
            assert_eq!(exp, act);
        }
    }
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
