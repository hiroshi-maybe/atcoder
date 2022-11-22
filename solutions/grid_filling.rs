#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch grid_filling | diff grid_filling.out -
// $ cargo run --bin grid_filling

///
/// 11/20/2022
///
/// 21:16-21:40 pause
///
/// 11/21/2022
///
/// 21:10-21:27 AC
///

fn solve() -> Vec<Vec<usize>> {
    let (h, w, n, hh, ww) = readln!(usize, usize, usize, usize, usize);
    let a = readlns!([usize1]; h);

    let mut cums = vec![];
    for v in 0..n {
        let mut mx = vec![vec![0; w]; h];
        for i in 0..h {
            for j in 0..w {
                if a[i][j] == v {
                    mx[i][j] = 1;
                }
            }
        }
        cums.push(PrefixSum2d::from(&mx));
    }

    let mut res = vec![];
    for i1 in 0..=h - hh {
        let mut ans = vec![];
        for j1 in 0..=w - ww {
            let mut cnt = 0;
            for v in 0..n {
                let tot = cums[v].query((0, 0), (h, w));
                let x = cums[v].query((i1, j1), (i1 + hh, j1 + ww));
                if tot - x > 0 {
                    cnt += 1;
                }
            }
            ans.push(cnt);
        }
        res.push(ans);
    }

    res
}

fn main() {
    setup_out!(put, puts);

    let res = solve();
    for res in res {
        for r in res {
            put!("{} ", r);
        }
        puts!();
    }
}

// region: prefixsum2d
#[rustfmt::skip]
#[allow(dead_code)]
mod prefixsum2d {
	pub struct PrefixSum2d<T> { r: usize, c: usize, prefix_sum: Vec<Vec<T>>, }
	pub trait Zero { const ZERO: Self; }

	macro_rules! impl_zero {
		($integer:ty) => { impl Zero for $integer { const ZERO: $integer = 0; } };
	}
	impl_zero!(i64);

	impl<T: Zero + Clone + Copy + std::ops::Add<Output = T> + std::ops::Sub<Output = T>>
		PrefixSum2d<T>
	{
		pub fn from(mx: &Vec<Vec<T>>) -> Self {
			let (r, c) = (mx.len(), mx[0].len());
			let mut prefix_sum = vec![vec![T::ZERO; c + 1]; r + 1];
			for i in 0..r {
				for j in 0..c {
					prefix_sum[i + 1][j + 1] =
						prefix_sum[i + 1][j] + prefix_sum[i][j + 1] - prefix_sum[i][j] + mx[i][j];
				}
			}
			PrefixSum2d::<T> { r, c, prefix_sum }
		}

		pub fn query(&self, p1: (usize, usize), p2: (usize, usize)) -> T {
			self.prefix_sum[p2.0][p2.1] - self.prefix_sum[p1.0][p2.1] - self.prefix_sum[p2.0][p1.1]
				+ self.prefix_sum[p1.0][p1.1]
		}
	}
}
pub use prefixsum2d::*;
// endregion: prefixsum2d

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
