#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

#[rustfmt::skip]
#[macro_use]
#[allow(dead_code)]
mod io {
	macro_rules! with_dollar_sign { ($($body:tt)*) => { macro_rules! __with_dollar_sign { $($body)* } __with_dollar_sign!($); }}
	macro_rules! setup_out {
		($fn:ident,$fn_s:ident) => {
			use std::io::Write;
			let out = std::io::stdout();
			let mut out = ::std::io::BufWriter::new(out.lock());
			with_dollar_sign! { ($d:tt) => {
				macro_rules! $fn { ($d($format:tt)*) => { let _ = write!(out,$d($format)*); } }
				macro_rules! $fn_s { ($d($format:tt)*) => { let _ = writeln!(out,$d($format)*); } }
			}}
		};
	}
	macro_rules! _epr { ($v:expr $(,)?) => {eprint!("{} = {:?}, ", stringify!($v), $v)}; }
	macro_rules! dbgln { ($($val:expr),*) => {{ eprint!("[{}:{}] ", file!(), line!()); ($(_epr!($val)),*); eprintln!(); }}; }
	pub fn readln() -> String {
		let mut line = String::new();
		::std::io::stdin().read_line(&mut line).unwrap_or_else(|e| panic!("{}", e));
		line
	}
	macro_rules! readlns {
		($($t:tt),*; $n:expr) => {{ let stdin = ::std::io::stdin();
			::std::io::BufRead::lines(stdin.lock()).take($n).map(|line| {
				let line = line.unwrap(); #[allow(unused_mut)]let mut it = line.split_whitespace(); _read!(it; $($t),*)
			}).collect::<Vec<_>>()
		}};
	}
	macro_rules! readln {
		($($t:tt),*) => {{ let line = io::readln(); #[allow(unused_mut)]let mut it = line.split_whitespace(); _read!(it; $($t),*) }};
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
}

// $ rs-cp-batch fg_operation | diff fg_operation.out -
// $ cargo run --bin fg_operation

///
/// 9/26/2021
///
/// 5:17-6:25 WA
/// 6:45 AC
///
/// https://atcoder.jp/contests/abc220/editorial/2682
///
/// https://twitter.com/hanseilimak/status/1442165447843979269?s=20
///

#[rustfmt::skip]
#[macro_use]
#[allow(unused_mut, dead_code)]
mod dp {
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
	macro_rules! vvec {
		($v:expr; $n:expr) => { Vec::from(vec![$v; $n]) };
		($v:expr; $n:expr $(; $ns:expr)+) => { Vec::from(vec![vvec![$v $(; $ns)*]; $n]) };
	}
}
use dp::*;

#[rustfmt::skip]
#[macro_use]
#[allow(unused_mut)]
mod mod_int {
	use std::convert::TryFrom;
	use std::marker::PhantomData;
	use std::ops::*;
	pub trait Modulus: Copy { fn modulus() -> i64; }

	#[derive(Copy, Clone, Debug, Hash, PartialEq, Eq, PartialOrd, Ord)]
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
	macro_rules! define_modulus {
		($struct_name: ident, $modulo: expr) => {
			#[derive(Copy, Clone, PartialEq, Eq, PartialOrd, Ord, Hash)]
			struct $struct_name {}
			impl mod_int::Modulus for $struct_name { fn modulus() -> i64 { $modulo } }
		};
	}
	macro_rules! define_convert {
		($integer:ty) => {
			impl<M: Modulus> From<$integer> for ModInt<M> { fn from(v: $integer) -> ModInt<M> { ModInt::<M>::new(v as i64) } }
		};
	}
	define_convert!(i32); define_convert!(i64); define_convert!(usize);
}
define_modulus!(Mod1000000007, 1_000_000_007);
define_modulus!(Mod998244353, 998_244_353);
type ModInt = mod_int::ModInt<Mod998244353>;

const MOD: i64 = 998_244_353;

#[allow(dead_code)]
struct Com {
    fac: Vec<i64>,
    ifac: Vec<i64>,
}
#[allow(dead_code)]
fn mod_add(a: i64, b: i64) -> i64 {
    (a + b) % MOD
}
#[allow(dead_code)]
fn mod_pow(mut a: i64, mut b: i64) -> i64 {
    let mut r = 1;
    while b > 0 {
        if b & 1 == 1 {
            r = r * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    r
}
#[allow(dead_code)]
fn mod_div(a: i64, b: i64) -> i64 {
    a * mod_pow(b, MOD - 2)
}

#[allow(dead_code)]
impl Com {
    fn new(n: usize) -> Com {
        let mut fac = vec![1; n + 1];
        let mut ifac = vec![1; n + 1];
        for i in 1..=n {
            fac[i] = fac[i - 1] * i as i64 % MOD;
        }
        ifac[n] = mod_div(1, fac[n] as i64);
        for i in (1..=n - 1).rev() {
            ifac[i] = ifac[i + 1] * (i + 1) as i64 % MOD;
        }

        Com { fac, ifac }
    }

    fn choose(&self, n: usize, k: usize) -> i64 {
        self.fac[n] * self.ifac[n - k] % MOD
    }
}

fn add(a: usize, b: usize) -> usize {
    (a + b + 10) % 10
}
fn mul(a: usize, b: usize) -> usize {
    (a * b) % 10
}

fn main() {
    setup_out!(put, puts);

    let n = readln!(usize);
    let a = readln!([usize]);

    let mut dp = vvec![ModInt::from(0); n+1; 10];
    dp[1][a[0] % 10] = ModInt::from(1);

    for i in 1..n {
        for k in 0..10 {
            let x = add(a[i], k);
            let oldv = dp[i][k];
            dp[i + 1][x] += oldv;
            let y = mul(a[i], k);
            dp[i + 1][y] += oldv;
        }
    }

    for k in 0..10 {
        puts!("{}", dp[n][k]);
    }

    /*

    let com = Com::new(1_000_000);

    let mut sum = a.iter().sum::<i32>() % 10;
    let mut prod = 1;
    let mut res = vec![0i64; 10];

    res[(sum % 10) as usize] += 1;
    dbgln!(n, sum);

    for i in (0..=n - 1).rev() {
        sum = add(sum, -a[i]);
        prod = mul(prod, a[i]);

        if i == 0 {
            break;
        }

        let l = i;
        let r = n - i - 1;

        let k = add(sum, prod) as usize;
        dbgln!(i, sum, prod, k, l, r);
        res[k] = mod_add(res[k], com.choose(l + r, l));

        let k = mul(sum, prod) as usize;
        dbgln!(i, sum, prod, k, l, r);
        res[k] = mod_add(res[k], com.choose(l + r, l));
    }

    res[(prod % 10) as usize] += 1;
    dbgln!(0, prod);


    for n in res {
        puts!("{}", n);
    }*/
}
