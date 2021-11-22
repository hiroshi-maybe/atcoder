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
///
/// https://atcoder.jp/contests/abc228/editorial/2944
///

struct Unionfind {
    par: Vec<usize>,
    sizes: Vec<usize>,
}

impl Unionfind {
    fn new(n: usize) -> Unionfind {
        let par = (0..n).map(|i| i).collect::<Vec<_>>();
        Unionfind {
            par,
            sizes: vec![1; n],
        }
    }

    fn find(&mut self, i: usize) -> usize {
        if self.par[i] == i {
            i
        } else {
            self.par[i] = self.find(self.par[i]);
            self.par[i]
        }
    }

    fn merge(&mut self, i: usize, j: usize) -> usize {
        let (mut p, mut c) = (self.find(i), self.find(j));
        if p == c {
            return p;
        }
        if self.sizes[p] < self.sizes[c] {
            std::mem::swap(&mut p, &mut c);
        }
        self.sizes[p] += self.sizes[c];
        self.par[c] = p;
        p
    }
}

fn solve() {
    setup_out!(put, puts);
    let n = 1 << 20;
    let q = readln!(usize);
    let mut a = vec![-1; n];

    let mut uf = Unionfind::new(n);
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
                    let l = uf.find(ll);
                    let r = uf.find(rr);
                    if let (Some((l1, _)), Some((_, r2))) = (ranges[l], ranges[r]) {
                        let p = uf.merge(l, r);
                        ranges[p] = Some((l1, r2));
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

fn main() {
    solve();
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
