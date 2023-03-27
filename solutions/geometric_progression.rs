#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;
use std::sync::atomic::AtomicI64;

// $ cp-batch geometric_progression | diff geometric_progression.out -
// $ cargo run --bin geometric_progression

///
/// 3/12/2023
///
/// 17:49-18:06 pause
/// 21:30-21:45 AC
///
/// 3/16/2023
///
/// solved by matrix pow
///
/// 3/26/2023
///
/// solved with the matrix library
///

pub struct Modulo {
    m: AtomicI64,
}
impl Modulo {
    pub const fn new(m: i64) -> Self {
        Modulo {
            m: AtomicI64::new(m),
        }
    }
    fn update(&self, m: i64) {
        self.m.store(m, std::sync::atomic::Ordering::SeqCst);
    }
    fn get(&self) -> i64 {
        self.m.load(std::sync::atomic::Ordering::SeqCst)
    }
}
static MODULO: Modulo = Modulo::new(1);

#[derive(Copy, Clone, Debug, PartialEq)]
struct DynMod(i64);
impl MatrixElement for DynMod {
    type InternalValue = Self;
    fn zero() -> Self::InternalValue {
        DynMod(0)
    }
    fn one() -> Self::InternalValue {
        DynMod(1)
    }
}
impl std::ops::Mul for DynMod {
    type Output = Self;
    fn mul(self, rhs: Self) -> Self::Output {
        DynMod(self.0 * rhs.0 % MODULO.get())
    }
}
impl std::ops::AddAssign for DynMod {
    fn add_assign(&mut self, rhs: Self) {
        self.0 = self.0 + rhs.0 % MODULO.get();
    }
}

fn pow(a: i64, x: i64) -> [[i64; 2]; 2] {
    if x == 0 {
        return [[1, 0], [0, 1]];
    }
    let mx = Matrix::<DynMod>::from(&vec![
        vec![DynMod(a), DynMod(1)],
        vec![DynMod(0), DynMod(1)],
    ]);
    let res = mx.pow(x as u64);
    [[res[0][0].0, res[0][1].0], [res[1][0].0, res[1][1].0]]
}

#[allow(dead_code)]
fn solve_mx_pow(a: i64, x: i64, m: i64) -> i64 {
    MODULO.update(m);
    let ax = pow(a, x - 1);

    // dbgln!(ax);

    (ax[0][0] + 1 * ax[0][1]) % m
}

#[allow(dead_code)]
fn solve_square_division(a: i64, x: i64, m: i64) -> i64 {
    let mut pow_a = vec![1_i64];
    for i in (1_i64..).take_while(|i| i * i <= x) {
        let last = pow_a[(i - 1) as usize];
        pow_a.push(last * a % m);
    }

    let mut rest = x;
    let mut b = 1;
    let mut res = 0;
    let tot = pow_a.iter().sum::<i64>() % m;
    while rest > 0 {
        let sum = if rest >= pow_a.len() as i64 {
            tot
        } else {
            pow_a[0..(rest as usize)].iter().sum::<i64>() % m
        };
        res += (b * sum) % m;
        res %= m;
        b *= pow_a.last().unwrap() * a % m;
        b %= m;
        rest -= min(rest, pow_a.len() as i64);
    }

    res
}

fn main() {
    setup_out!(put, puts);

    let (a, x, m) = readln!(i64, i64, i64);
    let res = solve_mx_pow(a, x, m);
    puts!("{}", res);
}

// region: matrix

// #[rustfmt::skip]
#[allow(dead_code)]
pub mod matrix {
    // use crate::modint::ModInt;
    use std::ops::{Add, AddAssign, Index, Mul, MulAssign};

    pub trait MatrixElement {
        type InternalValue: Clone + Copy;
        fn zero() -> Self::InternalValue;
        fn one() -> Self::InternalValue;
    }
    impl MatrixElement for i64 {
        type InternalValue = Self;
        fn zero() -> Self::InternalValue {
            0
        }
        fn one() -> Self::InternalValue {
            1
        }
    }
    // impl MatrixElement for ModInt {
    //     type InternalValue = Self;
    //     fn zero() -> Self::InternalValue {
    //         ModInt::from(0)
    //     }
    //     fn one() -> Self::InternalValue {
    //         ModInt::from(1)
    //     }
    // }

    #[derive(Debug, Default, Hash, PartialEq, Eq)]
    pub struct Matrix<Element: MatrixElement> {
        n: usize,
        m: usize,
        dat: Vec<Vec<Element::InternalValue>>,
    }
    impl<Element: MatrixElement> Matrix<Element> {
        pub fn new(n: usize, m: usize) -> Self {
            let dat = vec![vec![Element::zero(); m]; n];
            Matrix { n, m, dat }
        }
    }
    impl<Element: MatrixElement> Matrix<Element>
    where
        Matrix<Element>: MulAssign<Self>,
    {
        /// res = A^n, O(N^3*lg n) time
        pub fn pow(&self, mut exp: u64) -> Self {
            assert_eq!(self.n, self.m);
            let mut res = Matrix::<Element>::new(self.n, self.n);
            for i in 0..self.n {
                res.dat[i][i] = Element::one();
            }
            let mut a = self.clone();
            while exp > 0 {
                if exp & 1 == 1 {
                    res *= a.clone();
                }
                a *= a.clone();
                exp >>= 1;
            }
            res
        }
    }
    impl<Element: MatrixElement> Clone for Matrix<Element> {
        fn clone(&self) -> Self {
            Self {
                n: self.n.clone(),
                m: self.m.clone(),
                dat: self.dat.clone(),
            }
        }
    }
    impl<Element: MatrixElement> Index<usize> for Matrix<Element> {
        type Output = Vec<Element::InternalValue>;

        fn index(&self, index: usize) -> &Self::Output {
            &self.dat[index]
        }
    }
    impl<Element: MatrixElement> From<&Vec<Vec<Element::InternalValue>>> for Matrix<Element> {
        fn from(v: &Vec<Vec<Element::InternalValue>>) -> Self {
            let (n, m) = (v.len(), v[0].len());
            let mut matrix = Matrix::new(n, m);
            for i in 0..n {
                matrix.dat[i] = v[i].clone();
            }
            matrix
        }
    }
    impl<Element, Rhs> AddAssign<Rhs> for Matrix<Element>
    where
        Element: MatrixElement,
        Rhs: Into<Matrix<Element>>,
        Element::InternalValue: Add<Output = Element::InternalValue>,
    {
        fn add_assign(&mut self, rhs: Rhs) {
            let rhs = rhs.into();
            assert_eq!(self.n, rhs.n);
            assert_eq!(self.m, rhs.m);
            for i in 0..self.n {
                for j in 0..self.m {
                    self.dat[i][j] = self[i][j] + rhs[i][j];
                }
            }
        }
    }
    impl<Element, Rhs> MulAssign<Rhs> for Matrix<Element>
    where
        Element: MatrixElement,
        Rhs: Into<Matrix<Element>>,
        Element::InternalValue: Mul<Output = Element::InternalValue> + AddAssign,
    {
        fn mul_assign(&mut self, rhs: Rhs) {
            let rhs = rhs.into();
            assert_eq!(self.m, rhs.n);
            let mut new_mx = Matrix::<Element>::new(self.n, rhs.m);
            for i in 0..self.n {
                for j in 0..rhs.m {
                    for k in 0..self.m {
                        new_mx.dat[i][j] += self[i][k] * rhs[k][j];
                    }
                }
            }
            *self = new_mx;
        }
    }
    impl<Element, Rhs> Add<Rhs> for Matrix<Element>
    where
        Element: MatrixElement,
        Rhs: Into<Matrix<Element>>,
        Element::InternalValue: Add<Output = Element::InternalValue>,
    {
        type Output = Self;
        fn add(self, rhs: Rhs) -> Self {
            let mut res = self.clone();
            res += rhs;
            res
        }
    }
    impl<Element, Rhs> Mul<Rhs> for Matrix<Element>
    where
        Element: MatrixElement,
        Rhs: Into<Matrix<Element>>,
        Element::InternalValue: Mul<Output = Element::InternalValue> + AddAssign,
    {
        type Output = Self;
        fn mul(self, rhs: Rhs) -> Self::Output {
            let mut res = self.clone();
            res *= rhs;
            res
        }
    }
}
pub use matrix::{Matrix, MatrixElement};

// endregion: matrix

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
