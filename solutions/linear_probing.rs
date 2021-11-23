#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch linear_probing | diff linear_probing.out -
// $ cargo run --bin linear_probing

///
/// 11/21/2021
///
/// 24:22-25:15 pause
///
/// 11/22/2021
///
/// 12:12-13:46 AC
/// 18:33 Add solution with B-tree set
///
/// https://atcoder.jp/contests/abc228/editorial/2944
///

// region: union_find

#[rustfmt::skip]
#[allow(dead_code)]
mod uf {
	pub struct UnionFind {
		pub group_count: usize,
		par: Vec<usize>, sizes: Vec<usize>,
	}
	impl UnionFind {
		pub fn new(n: usize) -> UnionFind {
			let par = (0..n).map(|i| i).collect::<Vec<_>>();
			UnionFind { group_count: n, par, sizes: vec![1; n], }
		}
		pub fn find(&mut self, x: usize) -> usize {
			if self.par[x] == x { x } else {
				self.par[x] = self.find(self.par[x]);
				self.par[x]
			}
		}
		pub fn same_set(&mut self, x: usize, y: usize) -> bool { self.find(x) == self.find(y) }
		pub fn size(&mut self, x: usize) -> usize {
			let x = self.find(x);
			self.sizes[x]
		}
		pub fn merge(&mut self, x: usize, y: usize) -> usize {
			let (mut p, mut c) = (self.find(x), self.find(y));
			if p == c { return p; }
			if self.sizes[p] < self.sizes[c] { std::mem::swap(&mut p, &mut c); }
			self.group_count -= 1;
			self.sizes[p] += self.sizes[c];
			self.par[c] = p;
			p
		}
	}
}
pub use uf::UnionFind;

// endregion: union_find

#[allow(dead_code)]
fn solve_uf() {
    setup_out!(put, puts);
    let n = 1 << 20;
    let q = readln!(usize);
    let mut a = vec![-1; n];

    let mut uf = UnionFind::new(n);
    let mut ranges: Vec<Option<(usize, usize)>> = vec![None; n];

    for _ in 0..q {
        let (t, x) = readln!(usize, i64);
        match t {
            2 => {
                puts!("{}", a[x as usize % n]);
            }
            1 => {
                let xx = x as usize % n;
                let p = uf.find(xx);
                let i = match ranges[p] {
                    Some((_, r)) => r,
                    None => xx,
                };
                assert_eq!(ranges[i], None);
                ranges[i] = Some((i, (i + 1) % n));
                let mut may_merge = |ll: usize, rr: usize| {
                    let (l, r) = (uf.find(ll), uf.find(rr));
                    if let (Some((l1, _)), Some((_, r2))) = (ranges[l], ranges[r]) {
                        ranges[uf.merge(l, r)] = Some((l1, r2));
                        //dbgln!(p, ranges[p]);
                    }
                };
                may_merge((i + n - 1) % n, i);
                may_merge(i, (i + 1) % n);
                a[i] = x;
            }
            _ => unreachable!(),
        }
    }
}

#[allow(dead_code)]
fn solve_btreeset() {
    setup_out!(put, puts);
    let n = 1 << 20;
    let q = readln!(usize);
    let mut a = vec![-1; n];
    let mut s = BTreeSet::new();
    s.insert((0, n));

    for _ in 0..q {
        let (t, x) = readln!(usize, i64);
        match t {
            2 => {
                puts!("{}", a[x as usize % n]);
            }
            1 => {
                let p = x as usize % n;
                let i = if a[p] == -1 {
                    let mut it = s.range(..(p, n + 1));
                    let r = *it.next_back().unwrap();
                    s.remove(&r);
                    if r.0 < p {
                        s.insert((r.0, p));
                    }
                    if p + 1 < r.1 {
                        s.insert((p + 1, r.1));
                    }
                    p
                } else {
                    let mut it = s.range((p, 0)..);
                    let r = *it.next().unwrap_or(s.iter().next().unwrap());
                    s.remove(&r);
                    if r.0 + 1 < r.1 {
                        s.insert((r.0 + 1, r.1));
                    }
                    r.0
                };
                a[i] = x;
                //dbgln!(p, i, s);
            }
            _ => unreachable!(),
        }
    }
}

fn main() {
    solve_btreeset();
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
