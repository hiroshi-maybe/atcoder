#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch double_chance | diff double_chance.out -
// $ cargo run --bin double_chance

///
/// 11/10/2022
///
/// 22:18-23:35 give up
/// 23:35-23:49 read editorial and got AC
///
/// https://atcoder.jp/contests/abc276/editorial/5174
///

fn solve() -> Vec<u32> {
    let n = readln!(usize);
    let a = readln!([usize]);
    let max_v = 200_001;
    let mut bit_cnt = BIT::new(max_v, ModInt::from(0));
    let mut bit_cnt_val = BIT::new(max_v, ModInt::from(0));

    let mut sum = vec![ModInt::from(a[0])];
    let mut res = vec![ModInt::from(a[0])];
    bit_cnt.add(a[0], ModInt::from(1));
    bit_cnt_val.add(a[0], ModInt::from(a[0]));

    for i in 1..n {
        let mut sum2 = sum[i - 1];
        let a = a[i];
        sum2 += (bit_cnt.query(..a + 1) * a + bit_cnt_val.query_range(a + 1..max_v)) * 2;
        sum2 += a;

        bit_cnt.add(a, ModInt::from(1));
        bit_cnt_val.add(a, ModInt::from(a));

        // dbgln!(i, sum2);

        sum.push(sum2);
        res.push(sum2 / (i + 1) / (i + 1));
    }

    res.iter().map(|&r| r.val()).collect_vec()
}

fn main() {
    setup_out!(put, puts);

    let res = solve();
    for res in res {
        puts!("{}", res);
    }
}

// region: bit

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

	pub fn compress<T: Ord + Copy>(a: &Vec<T>) -> Vec<usize> {
		let mut aa = a.iter().enumerate().map(|(i, v)| (v, i)).collect::<Vec<_>>();
		aa.sort_unstable();
		let (n, mut k) = (a.len(), 0);
		let mut res = vec![0; n];
		for i in 0..n {
			if i > 0 && aa[i - 1].0 < aa[i].0 { k += 1; }
			res[aa[i].1] = k;
		}
		res
	}
	pub fn inversions(a: &Vec<i32>) -> Vec<usize> {
		let a = compress(&a);
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

// endregion: bit

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
