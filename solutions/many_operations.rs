#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch many_operations | diff many_operations.out -
// $ cargo run --bin many_operations

///
/// 7/24/2022
///
/// 22:39-23:19 give up
/// 24:08 read editorial and got AC
///
/// https://atcoder.jp/contests/abc261/editorial/4451
///

fn solve() -> Vec<usize> {
    let (n, c) = readln!(usize, usize);
    let qs = readlns!(usize, usize; n);

    let mut res = vec![0; n];

    for k in 0..30 {
        let mut cur = BitSet::from(c).ith(k) as usize;
        let mut f = [0, 1];
        for (i, &(t, a)) in qs.iter().enumerate() {
            let a = BitSet::from(a).ith(k) as usize;
            match t {
                1 => {
                    f[0] &= a;
                    f[1] &= a;
                }
                2 => {
                    f[0] |= a;
                    f[1] |= a;
                }
                3 => {
                    f[0] ^= a;
                    f[1] ^= a;
                }
                _ => unreachable!(),
            };
            cur = f[cur];
            res[i] |= cur << k;
        }
    }

    res
}

fn main() {
    setup_out!(put, puts);

    let res = solve();
    for r in res {
        puts!("{}", r);
    }
}

// region: bitmask
#[rustfmt::skip]
#[allow(dead_code)]
mod bitmask {
	#[derive(Debug, Copy, Clone)]
	pub struct BitMask(usize);
	impl BitMask {
		pub fn new(max_power_of_two: usize) -> BitMask { BitMask(max_power_of_two) }
		pub fn iter(&self) -> BitMaskIterator { BitMaskIterator(0..1<<self.0) }
	}
	impl IntoIterator for BitMask {
		type Item = BitSet; type IntoIter = BitMaskIterator;
		fn into_iter(self) -> Self::IntoIter { self.iter() }
	}

	//#[derive(IntoItarator)]
	pub struct BitMaskIterator(std::ops::Range<usize>);
	impl Iterator for BitMaskIterator {
		type Item = BitSet;
		fn next(&mut self) -> Option<Self::Item> {
			self.0.next().map(|m| BitSet(m))
		}
	}

	#[derive(Debug, PartialEq, Copy, Clone)]
	pub struct BitSet(usize);
	impl BitSet {
		pub fn ith(&self, i: usize) -> bool { (self.0 >> i) & 1 == 1 }
		pub fn ones(&self) -> BitSetOnesIterator {
			BitSetOnesIterator { set: BitSet(self.0), iter: 0..(self.0.count_ones() + self.0.count_zeros()) as usize }
		 }
	}
	impl From<usize> for BitSet {
		fn from(val: usize) -> BitSet { BitSet(val) }
	}
	pub struct BitSetOnesIterator { set: BitSet, iter: std::ops::Range<usize> }
	impl Iterator for BitSetOnesIterator {
		type Item = usize;
		fn next(&mut self) -> Option<Self::Item> {
			let set = self.set; self.iter.find(|&i| set.ith(i))
		}
	}
}
pub use bitmask::{BitMask, BitSet};
// endregion: bitmask

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
