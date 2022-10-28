#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch booster | diff booster.out -
// $ cargo run --bin booster

///
/// 10/23/2022
///
/// 20:46-21:48 AC
///
/// https://atcoder.jp/contests/abc274/editorial/5020
///

fn time(a: (isize, isize), b: (isize, isize), speed: usize) -> f64 {
    let (dx, dy) = ((a.0 - b.0).abs() as f64, (a.1 - b.1).abs() as f64);
    let dist = (dx * dx + dy * dy).sqrt();
    dist / speed as f64
}

fn solve() -> f64 {
    let (mut n, m) = readln!(usize, usize);
    n += 1;
    let mut a = vec![(0, 0)];
    let mut aa = readlns!(isize, isize; n);
    a.append(&mut aa);
    let mut b = readlns!(isize, isize; m);
    a.append(&mut b);

    let inf = 2.0 * 10.0f64.powi(9) * 20.0;
    let nm = n + m;
    let mut dp = vvec!(inf; 1 << nm; nm);
    dp[1][0] = 0.0;
    let mask = BitMask::new(nm);
    for set in mask {
        let speed = 1 << (set.subset(n..nm).ones().count());
        for cur in 0..(n + m) {
            let c = dp[set.val()][cur];
            // if c != inf {
            //     dbgln!(set, cur, c);
            // }
            for next in 0..(nm) {
                if !set.contains(next) {
                    // dbgln!(
                    //     next,
                    //     BitSet::from(set.val() | (1 << next)),
                    //     time(a[cur], a[next], speed)
                    // );
                    let mut newset = set;
                    newset.put(next);
                    dp[newset.val()][next].setmin(c + time(a[cur], a[next], speed));
                }
            }
        }
    }
    let base = BitSet::full_bits(n);
    let mut res = inf;
    for set in BitMask::new(m) {
        let set = set.concat(base);
        for lastp in 0..nm {
            let speed = 1 << (set.subset(n..nm).ones().count());
            res.setmin(dp[set.val()][lastp] + time(a[lastp], a[0], speed));
        }
    }
    res
}

fn main() {
    setup_out!(put, puts);

    let res = solve();
    puts!("{}", res);
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

	#[derive(PartialEq, Copy, Clone)]
	pub struct BitSet(usize);
	impl BitSet {
		#[inline]
		pub fn full_bits(len: usize) -> BitSet { BitSet((1 << len) - 1) }
		#[inline]
		pub fn contains(&self, i: usize) -> bool { (self.0 >> i) & 1 == 1 }
		pub fn ones(&self) -> BitSetBitsIterator { BitSetBitsIterator::new(BitSet(self.0), true) }
		pub fn zeros(&self) -> BitSetBitsIterator { BitSetBitsIterator::new(BitSet(self.0), false) }
		#[inline]
		pub fn val(&self) -> usize { self.0 }
		#[inline]
		pub fn put(&mut self, i: usize) -> bool { if self.contains(i) { false } else { self.0 |= 1 << i; true } }
		pub fn len(&self) -> usize {
			let bits = if usize::max_value() as u64 == u64::max_value() { 64 } else { 32 };
			(0..bits as usize).map(|i| self.contains(i)).rposition(std::convert::identity).map_or(0, |i| i+1)
		}
		#[inline]
		pub fn subset(&self, range: std::ops::Range<usize>) -> BitSet {
			let mut dat = self.0; dat >>= range.start;
			BitSet::from(dat & ((1 << range.len()) -1))
		}
		#[inline]
		pub fn concat<T: Into<BitSet>>(&self, other: T) -> BitSet {
			let other = other.into();
			BitSet::from((self.0 << other.len()) | other.val())
		 }
	}
	impl From<usize> for BitSet {
		fn from(val: usize) -> BitSet { BitSet(val) }
	}
	impl std::fmt::Debug for BitSet {
		fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
			let v = self.0;
			std::fmt::Binary::fmt(&v, f)
		}
	}
	pub struct BitSetBitsIterator { set: BitSet, iter: std::ops::Range<usize>, is_ones: bool }
	impl BitSetBitsIterator {
		pub fn new(set: BitSet, is_ones: bool) -> Self {
			BitSetBitsIterator {
				set: set, iter: 0..set.len(), is_ones: is_ones
			}
		}
	}
	impl Iterator for BitSetBitsIterator {
		type Item = usize;
		fn next(&mut self) -> Option<Self::Item> {
			let is_ones = self.is_ones; let set = self.set;
			self.iter.find(|&i| if is_ones { set.contains(i) } else { !set.contains(i) })
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
