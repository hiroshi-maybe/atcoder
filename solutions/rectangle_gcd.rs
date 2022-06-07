#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch rectangle_gcd | diff rectangle_gcd.out -
// $ cargo run --bin rectangle_gcd

///
/// 6/4/2022
///
/// 12:30-13:00, 21:00-22:00 gave up and read editorial
///
/// 6/6/2022
///
/// 22:20-22:38 AC
///

fn solve() {
    setup_out!(put, puts);

    let (_n, q) = readln!(usize, usize);
    let a = readln!([i64]);
    let b = readln!([i64]);

    let aa = a.windows(2).map(|xs| (xs[1] - xs[0]).abs()).collect_vec();
    let bb = b.windows(2).map(|xs| (xs[1] - xs[0]).abs()).collect_vec();

    let sa = SegmentTree::<Gcd>::from(aa);
    let sb = SegmentTree::<Gcd>::from(bb);

    for (h1, h2, w1, w2) in readlns!(usize1, usize, usize1, usize; q) {
        let mut res = a[h1] + b[w1];
        // dbgln!(h1, h2, w1, w2);
        res = gcd(res, sa.query(h1..h2 - 1));
        res = gcd(res, sb.query(w1..w2 - 1));

        puts!("{}", res);
    }
}

fn main() {
    solve();
}

pub struct Gcd(i64);
impl Monoid for Gcd {
    type V = i64;
    const IDENTITY: i64 = 0;
    fn binary_operation(a: &i64, b: &i64) -> i64 {
        gcd(*a, *b)
    }
}

// region: gcd

#[rustfmt::skip]
#[allow(dead_code)]
mod gcd {
	use std::cmp::PartialEq;
	use std::ops::Rem;
	#[inline(always)] pub fn gcd<T: Gcd>(x: T, y: T) -> T { x.gcd(&y) }
	#[inline(always)] pub fn lcm<T: Gcd>(x: T, y: T) -> T { x.lcm(&y) }
	pub trait Gcd: Copy + Rem<Output = Self> + PartialEq {
		fn gcd(&self, other: &Self) -> Self;
		fn lcm(&self, other: &Self) -> Self;
	}
	macro_rules! impl_gcd {
		($integer:ty) => {
			impl Gcd for $integer {
				#[inline] fn gcd(&self, other: &Self) -> Self {
					let mut m = *self; let mut n = *other;
					while m != 0 { let temp = m; m = n % temp; n = temp; }
					n
				}
				#[inline] fn lcm(&self, other: &Self) -> Self {
					self / gcd(*self, *other) * other
				}
			}
		};
	}
	impl_gcd!(i32);impl_gcd!(i64);impl_gcd!(usize);
}
pub use gcd::*;

// endregion: gcd

// region: segment_tree

#[rustfmt::skip]
#[allow(dead_code)]
mod segment_tree {
	pub struct Min(i64);
	impl Monoid for Min {
		type V = i64;
		const IDENTITY: i64 = i64::max_value();
		fn binary_operation(a: &i64, b: &i64) -> i64 { *a.min(b) }
	}
	pub struct Max(i64);
	impl Monoid for Max {
		type V = i64;
		const IDENTITY: i64 = i64::min_value();
		fn binary_operation(a: &i64, b: &i64) -> i64 { *a.max(b) }
	}
	pub type RangeMinQuery = SegmentTree<Min>;
	pub type RangeMaxQuery = SegmentTree<Max>;

	pub trait Monoid {
		type V: Clone;
		const IDENTITY: Self::V;
		fn binary_operation(a: &Self::V, b: &Self::V) -> Self::V;
	}

	pub struct SegmentTree<M: Monoid> { n: usize, size: usize, dat: Vec<M::V>, }
	impl<M: Monoid> SegmentTree<M> {
		pub fn new(n: usize) -> SegmentTree<M> {
			let size = n.next_power_of_two();
			let dat = vec![M::IDENTITY; 2 * size];
			SegmentTree { n, size, dat }
		}
		pub fn merge_all(&mut self) {
			(1..self.size).rev().for_each(|i| self.merge(i));
		}
		pub fn query(&self, range: std::ops::Range<usize>) -> M::V {
			assert!(range.start <= range.end && range.end <= self.n);
			let (mut l, mut r) = (self.map_index(range.start), self.map_index(range.end));
			if l == r { return M::IDENTITY.clone(); }
			let (mut lval, mut rval) = (M::IDENTITY.clone(), M::IDENTITY.clone());
			while l < r {
				if l & 1 != 0 {
					lval = M::binary_operation(&lval, &self.dat[l]);
					l += 1;
				}
				if r & 1 != 0 {
					r -= 1;
					rval = M::binary_operation(&self.dat[r], &rval);
				}
				l >>= 1; r >>= 1;
			}
			M::binary_operation(&lval, &rval)
		}
		pub fn update(&mut self, i: usize, val: M::V) {
			assert!(i < self.n);
			let mut i = self.map_index(i);
			self.dat[i] = val;
			i >>= 1;
			while i > 0 { self.merge(i); i >>= 1; }
		}
		pub fn max_right<Pred: Fn(&M::V) -> bool>(&self, l: usize, pred: Pred) -> usize {
			assert!(l <= self.n);
			assert!(pred(&M::IDENTITY.clone()));
			if l == self.n { return self.n; }
			let mut l = self.map_index(l);
			let mut sum = M::IDENTITY.clone();
			while {
				// do
				while l % 2 == 0 { l >>= 1; }
				if !pred(&M::binary_operation(&sum, &self.dat[l])) {
					while l < self.size {
						l = 2 * l;
						let res = M::binary_operation(&sum, &self.dat[l]);
						if pred(&res) { sum = res; l += 1; }
					}
					return l - self.size;
				}
				sum = M::binary_operation(&sum, &self.dat[l]);
				l += 1;
				// while
				l.count_ones() > 1
			} {}
			self.n
		}
		pub fn min_left<Pred: Fn(&M::V) -> bool>(&self, r: usize, pred: Pred) -> usize {
			assert!(r <= self.n);
			assert!(pred(&M::IDENTITY.clone()));
			if r == 0 { return 0; }
			let mut r = self.map_index(r);
			let mut sum = M::IDENTITY.clone();
			while {
				// do
				r -= 1;
				while r > 1 && r % 2 == 1 { r >>= 1; }
				if !pred(&M::binary_operation(&self.dat[r], &sum)) {
					while r < self.size {
						r = 2 * r + 1;
						let res = M::binary_operation(&self.dat[r], &sum);
						if pred(&res) { sum = res; r -= 1; }
					}
					return r + 1 - self.size;
				}
				sum = M::binary_operation(&self.dat[r], &sum);
				// while
				r.count_ones() > 1
			} {}
			0
		}
		fn merge(&mut self, i: usize) {
			self.dat[i] = M::binary_operation(&self.dat[2 * i], &self.dat[2 * i + 1]);
		}
		fn map_index(&self, i: usize) -> usize { i + self.size }
	}

	impl<M: Monoid> From<&[M::V]> for SegmentTree<M> {
		fn from(v: &[M::V]) -> Self {
			let mut segtree = SegmentTree::new(v.len());
			segtree.dat[segtree.size..(segtree.size + v.len())].clone_from_slice(v);
			segtree.merge_all();
			segtree
		}
	}
	impl<M: Monoid> From<Vec<M::V>> for SegmentTree<M> {
		fn from(v: Vec<M::V>) -> Self { v[..].into() }
	}
}
pub use segment_tree::{Monoid, RangeMaxQuery, RangeMinQuery, SegmentTree};

// endregion: segment_tree

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
