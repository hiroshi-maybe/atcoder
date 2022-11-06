#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch divide_by_2_or_3 | diff divide_by_2_or_3.out -
// $ cargo run --bin divide_by_2_or_3

///
/// 11/5/2022
///
/// 12:27-12:38 AC
///
/// https://atcoder.jp/contests/abc276/editorial/5167
///

fn solve() -> Option<usize> {
    let n = readln!(usize);
    let a = readln!([i64]);

    let mut g = a[0];
    for &a in &a[1..n] {
        g = gcd(g, a);
    }

    let a = a.iter().map(|&a| a / g).collect_vec();
    let mut res = 0;
    for mut a in a {
        while a % 2 == 0 {
            a /= 2;
            res += 1;
        }
        while a % 3 == 0 {
            a /= 3;
            res += 1;
        }
        if a != 1 {
            return None;
        }
    }

    Some(res)
}

fn main() {
    setup_out!(put, puts);

    let res = solve();
    puts!("{}", if let Some(r) = res { r as isize } else { -1 });
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
