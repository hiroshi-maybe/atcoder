#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch sum_of_maximum_weights | diff sum_of_maximum_weights.out -
// $ cargo run --bin sum_of_maximum_weights

///
/// 12/16/2021
///
/// 9:52-10:09 AC
///
/// https://atcoder.jp/contests/abc214/editorial/2434
///

// region: union_find

#[rustfmt::skip]
#[allow(dead_code)]
mod uf {
	pub struct UnionFind {
		pub group_count: usize,
		par_or_size: Vec<isize>,
	}
	impl UnionFind {
		pub fn new(n: usize) -> UnionFind {
			UnionFind { group_count: n, par_or_size: vec![-1; n], }
		}
		pub fn root(&mut self, x: usize) -> usize {
			if self.par_or_size[x] < 0 as isize { x } else {
				self.par_or_size[x] = self.root(self.par_or_size[x] as usize) as isize;
				self.par_or_size[x] as usize
			}
		}
		pub fn same_set(&mut self, x: usize, y: usize) -> bool { self.root(x) == self.root(y) }
		pub fn size(&mut self, x: usize) -> usize {
			let root = self.root(x); -self.par_or_size[root] as usize
		}
		pub fn merge(&mut self, x: usize, y: usize) -> usize {
			let (mut p, mut c) = (self.root(x), self.root(y));
			if p == c { return p; }
			if -self.par_or_size[p] < -self.par_or_size[c] { std::mem::swap(&mut p, &mut c); }
			self.group_count -= 1;
			self.par_or_size[p] += self.par_or_size[c];
			self.par_or_size[c] = p as isize;
			p
		}
		pub fn roots(&mut self) -> Vec<usize> {
			(0..self.par_or_size.len()).filter(|&u| self.root(u) == u).collect::<Vec<_>>()
		}
	}
}
pub use uf::UnionFind;

// endregion: union_find

fn solve() -> i64 {
    let n = readln!(usize);
    let mut uvw = readlns!(usize1, usize1, i64; n-1);
    uvw.sort_unstable_by_key(|&(_, _, w)| w);

    let mut res = 0;
    let mut uf = UnionFind::new(n);
    for (u, v, w) in uvw {
        let (a, b) = (uf.size(u), uf.size(v));
        res += w * a as i64 * b as i64;
        uf.merge(u, v);
    }
    res
}

fn main() {
    setup_out!(put, puts);

    let res = solve();
    puts!("{}", res);
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
