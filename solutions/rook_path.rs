#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch rook_path | diff rook_path.out -
// $ cargo run --bin rook_path

///
/// 12/19/2021
///
/// 10:55-12:24 WA due to messed-up x and y
/// 13:18 AC
///
/// https://atcoder.jp/contests/abc232/editorial/3148
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
type ModInt = ModInt998244353;
// type ModInt = ModInt1000000007;

// endregion: mod_int

// region: comb

#[rustfmt::skip]
#[allow(dead_code)]
pub mod comb {
	use super::mod_int::{ModInt, Modulus};
	pub struct Com<T> { fac: Vec<T>, ifac: Vec<T> }
	impl<M: Modulus> Com<ModInt<M>> {
		pub fn new(n: usize) -> Com<ModInt<M>> {
			let mut fac = vec![ModInt::<M>::from(1); n + 1];
			let mut ifac = vec![ModInt::<M>::from(1); n + 1];
			for i in 1..=n { fac[i] = fac[i - 1] * i; }
			ifac[n] = ModInt::<M>::from(1) / fac[n];
			for i in (1..=n - 1).rev() { ifac[i] = ifac[i + 1] * (i + 1); }
			Com { fac, ifac }
		}
		pub fn choose(&self, n: usize, k: usize) -> ModInt<M> {
			if n < k { return ModInt::<M>::from(0); }
			self.fac[n] * self.ifac[n - k] * self.ifac[k]
		}
		pub fn fact(&self, n: usize) -> ModInt<M> { self.fac[n] }
		pub fn perm(&self, n: usize, k: usize) -> ModInt<M> {
			if n < k { return ModInt::<M>::from(0); }
			self.fac[n] * self.ifac[n - k]
		}
		pub fn multi_choose(&self, n: usize, k: usize) -> ModInt<M> {
			if n == 0 && k == 0 { return ModInt::<M>::from(1); }
			self.choose(n + k - 1, k)
		}
	}
}
pub use comb::Com;
// endregion: comb

fn f(n: usize, is_x2: bool, h: i64) -> Vec<ModInt> {
    let mut dp = vvec!(ModInt::from(0); n+1; 2);
    dp[0][is_x2 as usize] = ModInt::from(1);
    for i in 0..n {
        dp[i + 1][1] = dp[i][0];
        dp[i + 1][0] = dp[i][0] * (h - 2) + dp[i][1] * (h - 1);
    }

    dp.iter().map(|vs| vs[1]).collect_vec()
}

fn solve(h: i64, w: i64, k: usize, x1: i64, y1: i64, x2: i64, y2: i64) -> ModInt {
    let mut dp0 = vvec!(ModInt::from(0); 2;2);

    dp0[(x1 == x2) as usize][(y1 == y2) as usize] = ModInt::from(1);
    for _ in 0..k {
        let dp1 = vec![
            vec![
                dp0[0][0] * (h + w - 4) + dp0[0][1] * (w - 1) + dp0[1][0] * (h - 1),
                dp0[0][0] + dp0[0][1] * (h - 2) + dp0[1][1] * (h - 1),
            ],
            vec![
                dp0[0][0] + dp0[1][0] * (w - 2) + dp0[1][1] * (w - 1),
                dp0[0][1] + dp0[1][0],
            ],
        ];
        dp0 = dp1;
    }
    dp0[1][1]
}

#[allow(dead_code)]
fn solve_v0(h: i64, w: i64, k: usize, x1: i64, y1: i64, x2: i64, y2: i64) -> ModInt {
    let com = Com::<ModInt>::new(k);

    let (dpx, dpy) = (f(k, x1 == x2, h), f(k, y1 == y2, w));

    let mut res = ModInt::from(0);
    for r in 0..=k {
        res += dpx[r] * dpy[k - r] * com.choose(k, r);
    }
    res
}

fn assert(h: usize, w: usize, k: usize, x1: usize, y1: usize, x2: usize, y2: usize) {
    let act = solve_v0(
        h as i64, w as i64, k, x1 as i64, y1 as i64, x2 as i64, y2 as i64,
    );

    let mut dp = vvec!(ModInt::from(0); k+1; h+1; w+1);
    dp[0][x1][y1] = ModInt::from(1);
    for i in 0..k {
        for x in 1..=h as usize {
            for y in 1..=w as usize {
                let cur = dp[i][x][y];
                for xx in (1..=h as usize).filter(|&xx| xx != x) {
                    dp[i + 1][xx][y] += cur;
                }
                for yy in (1..=w as usize).filter(|&yy| yy != y) {
                    dp[i + 1][x][yy] += cur;
                }
            }
        }
    }
    let exp = dp[k][x2][y2];
    //if act != exp {
    dbgln!(h, w, k, x1, x2, y1, y2, act, exp);
    //}
    assert_eq!(exp, act);
}

#[allow(dead_code)]
fn test2() {
    let max_l = 5;
    let max_k = 1000;
    use rand::prelude::*;
    let mut rng = thread_rng();

    loop {
        let h = rng.gen_range(2, max_l);
        let w = rng.gen_range(2, max_l);
        assert(
            h,
            w,
            rng.gen_range(1, max_k),
            rng.gen_range(1, h + 1),
            rng.gen_range(1, w + 1),
            rng.gen_range(1, h + 1),
            rng.gen_range(1, w + 1),
        );
    }
}

#[allow(dead_code)]
fn test1() {
    let max_l = 20;
    for h in max_l..=max_l {
        for w in max_l..=max_l {
            for k in 100..=100 {
                for x1 in 1..=h as usize {
                    for x2 in 1..=h as usize {
                        for y1 in 1..=w as usize {
                            for y2 in 1..=w as usize {
                                assert(h, w, k, y1, x1, y2, x2);
                            }
                        }
                    }
                }
            }
        }
    }
}

fn main() {
    setup_out!(put, puts);

    //test2();

    let (h, w, k) = readln!(i64, i64, usize);
    let (x1, y1, x2, y2) = readln!(i64, i64, i64, i64);
    let res = solve(h, w, k, x1, y1, x2, y2);
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