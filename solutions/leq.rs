#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ rs-cp-batch leq | diff leq.out -
// $ cargo run --bin leq

///
/// 10/2/2021
///
/// 6:09-7:22 AC
///
/// https://atcoder.jp/contests/abc221/editorial/2718
/// https://atcoder.jp/contests/abc221/submissions/26320980
///
/// https://twitter.com/semiexp/status/1444298288161644544
/// https://twitter.com/ngtkana/status/1444302874687594508
/// https://twitter.com/satanic0258/status/1444300714247798785
///
///

fn main() {
    setup_out!(put, puts);

    puts!("{}", solve_move_right());
}

// 212 ms
#[allow(dead_code)]
fn solve_v0() -> ModInt {
    let n = readln!(usize);
    let a = readln!([i64]);
    let mut aa = a
        .iter()
        .enumerate()
        .map(|(i, v)| (v, i))
        .collect::<Vec<_>>();
    aa.sort();
    //dbgln!(aa);
    let mut ord = vec![0; n];
    for i in 0..n {
        ord[aa[i].1] = i;
    }
    //dbgln!(ord);

    let mut dat = vec![ModInt::from(0); n];
    for i in 0..n {
        dat[ord[i]] = ModInt::from(2).pow(i as i64);
    }
    let mut bit = BIT::new(n, ModInt::from(0));
    for i in 0..n {
        bit.add(i, dat[i]);
    }

    let mut res = ModInt::from(0);
    for i in 0..n {
        let p = ord[i];
        let sum = bit.query_range(p + 1..n);
        let pow2 = ModInt::from(2).pow((i + 1) as i64);
        //dbgln!(i, p, sum.val(), pow2.val(), (sum / pow2).val());
        res += sum / pow2;
        //dbgln!(i, res.val());
        bit.add(p, -dat[p]);
        // assert!(bit.sum(p, p + 1) == ModInt::from(0));
    }
    res
}

// 150 ms
#[allow(dead_code)]
fn solve_move_left() -> ModInt {
    let n = readln!(usize);
    let a = readln!([i64]);
    let a = compress(a);
    // dbgln!(a);
    let mut bit = BIT::new(n, ModInt::from(0));
    let mut p2 = ModInt::from(1);
    for i in 0..n {
        bit.add(a[i], p2);
        p2 *= 2;
    }

    let mut res = ModInt::from(0);
    let mut p2 = ModInt::from(1);
    for i in 0..n {
        bit.add(a[i], -p2);
        p2 *= 2;
        let sum = bit.query_range(a[i]..n);
        res += sum / p2;
    }

    res
}

// 92 ms
#[allow(dead_code)]
fn solve_move_right() -> ModInt {
    let n = readln!(usize);
    let a = readln!([i64]);
    let a = compress(a);
    // dbgln!(a);
    let mut bit = BIT::new(n, ModInt::from(0));
    let mut res = ModInt::from(0);
    let mut p2 = ModInt::from(1);
    let inv2 = ModInt::from(1) / 2;
    let mut curinv = ModInt::from(1);
    for i in 0..n {
        let sum = bit.query(..a[i] + 1);
        res += sum * p2;
        curinv *= inv2;
        bit.add(a[i], curinv);
        p2 *= 2;
    }

    res
}

#[rustfmt::skip]
#[macro_use]
#[allow(dead_code)]
pub mod mod_int {
	use std::convert::TryFrom;
	use std::marker::PhantomData;
	use std::ops::*;
	pub trait Modulus: Copy { fn modulus() -> i64; }

	#[derive(Copy, Clone, Hash, PartialEq, Eq, PartialOrd, Ord)]
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
			#[derive(Copy, Clone, PartialEq, Eq, PartialOrd, Ord, Hash)]
			pub struct $struct_name {}
			impl mod_int::Modulus for $struct_name { fn modulus() -> i64 { $modulo } }
		};
	}
	macro_rules! define_convert {
		($integer:ty) => {
			impl<M: Modulus> From<$integer> for ModInt<M> { fn from(v: $integer) -> ModInt<M> { ModInt::<M>::new(v as i64) } }
		};
	}
	define_convert!(i32); define_convert!(u32); define_convert!(i64); define_convert!(u64); define_convert!(usize);
}
define_modulus!(Mod1000000007, 1_000_000_007);
define_modulus!(Mod998244353, 998_244_353);
pub type ModInt1000000007 = mod_int::ModInt<Mod1000000007>;
pub type ModInt998244353 = mod_int::ModInt<Mod998244353>;
type ModInt = ModInt998244353;

#[rustfmt::skip]
#[allow(dead_code)]
pub mod bit {
	pub struct BIT<T> { n: usize, dat: Vec<T>, /* dat[i] = ∑ { A[g(i)..=i] } */ identity: T }
	impl<T> BIT<T>
	where
		T: Clone + std::ops::AddAssign,
	{
		pub fn new(n: usize, identity: T) -> Self {
			BIT { n, dat: vec![identity.clone(); n], identity }
		}
		// A[pos] += delta
		pub fn add(&mut self, pos: usize, delta: T) {
			let mut i = pos + 1;
			while i <= self.n {
				self.dat[i - 1] += delta.clone();
				i = h(i);
			}
		}
		// query ∑ { A[i] : i=r.start..<r.end }
		pub fn query_range(&self, range: std::ops::Range<usize>) -> T
		where
			T: std::ops::Sub<Output = T>,
		{
			debug_assert!(range.start <= range.end);
			self.query(..range.end) - self.query(..range.start)
		}
		// query ∑ { A[i] : i=0..<r.end }
		pub fn query(&self, range: std::ops::RangeTo<usize>) -> T {
			let mut r = range.end;
			debug_assert!(r <= self.n);
			let mut res = self.identity.clone();
			while r > 0 {
				res += self.dat[r - 1].clone();
				r = std::cmp::max(g(r), 1) - 1;
			}
			res
		}
	}
	fn g(i: usize) -> usize { i & (i + 1) }
	fn h(i: usize) -> usize { i | (i + 1) }

	pub fn compress<T: Ord + Clone>(a: Vec<T>) -> Vec<usize> {
		let mut aa = a.clone();
		aa.sort_unstable();
		aa.dedup();
		let mut res = vec![];
		res.reserve(a.len());
		for i in 0..a.len() {
			res.push(aa.binary_search(&a[i]).unwrap());
		}
		res
	}
	pub fn inversions(a: &Vec<i32>) -> Vec<usize> {
		let a = compress(a.clone());
		let n = a.len();
		let mut bit = BIT::new(n, 0usize);
		let mut res = vec![0; n];
		for i in (0..n).rev() {
			res[i] = bit.query(..a[i]);
			bit.add(a[i], 1);
		}
		res
	}
}
pub use bit::{compress, inversions, BIT};

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
	macro_rules! vvec {
		($v:expr; $n:expr) => { Vec::from(vec![$v; $n]) };
		($v:expr; $n:expr $(; $ns:expr)+) => { Vec::from(vec![vvec![$v $(; $ns)*]; $n]) };
	}
	pub(crate) use vvec;
}
}
// endregion: cplib
