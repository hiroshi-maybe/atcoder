#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch contest_in_atcoder_kingdom | diff contest_in_atcoder_kingdom.out -
// $ cargo run --bin contest_in_atcoder_kingdom

///
/// 12/14/2021
///
/// 10:21-10:39 AC
///
/// https://www.slideshare.net/chokudai/arc035
///

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
// type ModInt = ModInt998244353;
type ModInt = ModInt1000000007;

// endregion: mod_int

fn fact(n: usize) -> ModInt {
    (1..=n).fold(ModInt::from(1), |acc, n| acc * n)
}

#[allow(dead_code)]
fn solve_v1() -> (i64, u32) {
    let n = readln!(usize);
    let mut t = readlns!(i64; n);
    t.sort();

    let mut cur = 0;
    let mut res_t = 0;
    let mut res_c = ModInt::from(1);
    let mut cnt = 0;
    for i in 0..n {
        cur += t[i];
        res_t += cur;

        cnt += 1;
        if i == n - 1 || t[i] != t[i + 1] {
            //dbgln!(i,cnt);
            res_c *= fact(cnt);
            cnt = 0;
        }
    }

    (res_t, res_c.val())
}

fn solve() -> (i64, u32) {
    let n = readln!(usize);
    let t = readlns!(usize; n);
    let mut cnt = vec![0; 10_001];
    for t in t {
        cnt[t] += 1;
    }

    let mut cur = 0;
    let mut res_t = 0;
    let mut res_c = ModInt::from(1);
    for t in 1..cnt.len() {
        for x in 1..=cnt[t] {
            cur += t as i64;
            res_t += cur;
            res_c *= x;
        }
    }

    (res_t, res_c.val())
}

fn main() {
    setup_out!(put, puts);

    let (t, c) = solve();
    puts!("{}", t);
    puts!("{}", c);
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
