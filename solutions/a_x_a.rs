#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch a_x_a | diff a_x_a.out -
// $ cargo run --bin a_x_a

///
/// 3/5/2022
///
/// 10:11-11:08 AC
///
/// https://atcoder.jp/contests/abc242/editorial/3516
///

fn solve() -> u32 {
    let n = readln!(usize);
    let s = readln!([u8]).iter().map(|&c| c - b'A').collect_vec();

    let mut dp = vvec!(ModInt::from(0); n+1; 2);
    dp[0][0] = ModInt::from(1);

    let nn = (n + 1) / 2;
    for i in 0..nn {
        let cc = s[i];
        for less in 0..2 {
            let cur = dp[i][less];
            for c in 0..if less == 1 { 26 } else { cc + 1 } {
                dp[i + 1][less | (c < cc) as usize] += cur;
            }
        }
    }
    let mut res = dp[nn][1];
    let pal = [
        &s[0..nn],
        &s[0..n - nn].iter().rev().copied().collect_vec()[..],
    ]
    .concat();
    if pal <= s {
        res += dp[nn][0];
    }

    res.val()
}

fn main() {
    setup_out!(put, puts);

    for _ in 0..readln!(usize) {
        let res = solve();
        puts!("{}", res);
    }
}

// region: mod_int

#[rustfmt::skip]
#[allow(dead_code)]
pub mod mod_int {
	use std::convert::TryFrom;
	use std::marker::PhantomData;
	use std::ops::*;
	pub trait Modulus: Copy { fn modulus() -> i64; }

	#[derive(Copy, Clone, Default, Hash, PartialEq, Eq, PartialOrd, Ord)]
	pub struct ModInt<M> { val: u32, phantom: PhantomData<fn() -> M> }
	impl<M: Modulus> ModInt<M> {
		pub fn val(self) -> u32 { self.val }
		pub fn pow(self, mut n: i64) -> Self {
			debug_assert!(n >= 0);
			let mut res = Self::raw(1);
			let mut p = self;
			while n > 0 {
				if n % 2 != 0 { res *= p; }
				p *= p; n >>= 1;
			}
			res
		}
		pub fn inv(self) -> Self { self.pow(M::modulus() - 2) }
		fn new(val: i64) -> Self {
			let mut v = val;
			if val < 0 { v = v % M::modulus() + M::modulus(); }
			if v >= M::modulus() { v -= M::modulus(); }
			if v >= M::modulus() { v %= M::modulus(); }
			Self::raw(v)
		}
		fn raw(val: i64) -> Self { Self { val: u32::try_from(val).unwrap(), phantom: PhantomData } }
	}
	impl<M: Modulus, T: Into<ModInt<M>>> Add<T> for ModInt<M> {
		type Output = Self;
		fn add(self, other: T) -> Self { Self::new(self.val as i64 + other.into().val as i64) }
	}
	impl<M: Modulus, T: Into<ModInt<M>>> Sub<T> for ModInt<M> {
		type Output = Self;
		fn sub(self, other: T) -> Self { Self::new(self.val as i64 - other.into().val as i64) }
	}
	impl<M: Modulus, T: Into<ModInt<M>>> Mul<T> for ModInt<M> {
		type Output = Self;
		fn mul(self, other: T) -> Self { Self::new((self.val as i64) * (other.into().val as i64) % M::modulus()) }
	}
	impl<M: Modulus, T: Into<ModInt<M>>> Div<T> for ModInt<M> {
		type Output = Self;
		fn div(self, other: T) -> Self { self * other.into().inv() }
	}
	impl<M: Modulus, T: Into<ModInt<M>>> AddAssign<T> for ModInt<M> {
		fn add_assign(&mut self, other: T) { *self = *self + other; }
	}
	impl<M: Modulus, T: Into<ModInt<M>>> SubAssign<T> for ModInt<M> {
		fn sub_assign(&mut self, other: T) { *self = *self - other; }
	}
	impl<M: Modulus, T: Into<ModInt<M>>> MulAssign<T> for ModInt<M> {
		fn mul_assign(&mut self, other: T) { *self = *self * other; }
	}
	impl<M: Modulus, T: Into<ModInt<M>>> DivAssign<T> for ModInt<M> {
		fn div_assign(&mut self, other: T) { *self = *self / other; }
	}
	impl<M: Modulus> Neg for ModInt<M> {
		type Output = Self;
		fn neg(self) -> Self { Self::new(-(self.val as i64)) }
	}
	impl<M: Modulus> ::std::fmt::Display for ModInt<M> {
		fn fmt(&self, f: &mut ::std::fmt::Formatter) -> ::std::fmt::Result { self.val().fmt(f) }
	}
	impl<M: Modulus> ::std::fmt::Debug for ModInt<M> {
		fn fmt(&self, f: &mut ::std::fmt::Formatter) -> ::std::fmt::Result { self.val().fmt(f) }
	}
	impl<M: Modulus> ::std::iter::Sum for ModInt<M> {
		fn sum<I: Iterator<Item=Self>>(iter: I) -> Self { iter.fold(ModInt::from(0), |a, b| a + b) }
	}
	impl<'a, M: Modulus> ::std::iter::Sum<&'a ModInt<M>> for ModInt<M> {
		fn sum<I: Iterator<Item=&'a Self>>(iter: I) -> Self { iter.fold(ModInt::from(0), |a, b| a + *b) }
	}
	impl<M: Modulus> ::std::iter::Product for ModInt<M> {
		fn product<I: Iterator<Item=Self>>(iter: I) -> Self { iter.fold(ModInt::from(1), |a, b| a * b) }
	}
	impl<'a, M: Modulus> ::std::iter::Product<&'a ModInt<M>> for ModInt<M> {
		fn product<I: Iterator<Item=&'a Self>>(iter: I) -> Self { iter.fold(ModInt::from(1), |a, b| a * *b) }
	}
	macro_rules! define_modulus {
		($struct_name: ident, $modulo: expr) => {
			#[derive(Copy, Clone, Default, PartialEq, Eq, PartialOrd, Ord, Hash)]
			pub struct $struct_name {}
			impl Modulus for $struct_name { fn modulus() -> i64 { $modulo } }
		};
	}
	macro_rules! define_convert {
		($integer:ty) => {
			impl<M: Modulus> From<$integer> for ModInt<M> { fn from(v: $integer) -> ModInt<M> { ModInt::<M>::new(v as i64) } }
		};
	}
	define_convert!(i32); define_convert!(u32); define_convert!(i64); define_convert!(u64); define_convert!(usize);
	define_modulus!(Mod1000000007, 1_000_000_007); define_modulus!(Mod998244353, 998_244_353);
	pub(crate) use define_modulus;
}
pub use mod_int::*;
pub type ModInt1000000007 = mod_int::ModInt<Mod1000000007>;
pub type ModInt998244353 = mod_int::ModInt<Mod998244353>;
type ModInt = ModInt998244353;
// type ModInt = ModInt1000000007;

// endregion: mod_int

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
