#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch coprime | diff coprime.out -
// $ cargo run --bin coprime

///
/// 11/19/2021
///
/// 9:53-10:20 pause
/// 20:23-20:38 AC
///
/// https://atcoder.jp/contests/abc177/editorial/82
///

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

// region: sieve

#[rustfmt::skip]
#[allow(dead_code)]
mod sieve {
    pub struct LinearSieve { n: usize, divp: Vec<usize>, }
    impl LinearSieve {
        pub fn new(n: usize) -> Self {
            let mut sieve = LinearSieve { n, divp: vec![0; n + 1], };
            for p in 2..=n {
                if sieve.divp[p] != 0 { continue; }
                sieve.divp[p] = p;
                for q in (p * p..).step_by(p).take_while(|q| q <= &n) {
                    if sieve.divp[q] == 0 { sieve.divp[q] = p; }
                }
            }
            sieve
        }
        pub fn fact(&self, mut x: usize) -> Vec<usize> {
            let mut res = vec![];
            while x > 1 { res.push(self.divp[x]); x /= self.divp[x]; }
            res.sort_unstable();
            res
        }
    }
}
pub use sieve::*;

// endregion: sieve

fn solve() -> i32 {
    let _n = readln!(usize);
    let a = readln!([usize]);

    let mut g = a[0];
    for a in &a {
        g = gcd(g, *a);
    }
    if g > 1 {
        return 2;
    }

    let maxv = a.iter().max().unwrap();
    let sieve = LinearSieve::new(*maxv);

    let mut cnt = vec![0; *maxv + 1];
    for a in a {
        let mut ps = sieve.fact(a);
        //dbgln!(ps);
        ps.dedup();
        for p in ps {
            if p > 1 {
                cnt[p] += 1;
            }
        }
    }

    if cnt.iter().any(|x| *x > 1) {
        1
    } else {
        0
    }
}

fn main() {
    setup_out!(put, puts);

    let res = solve();
    puts!(
        "{}",
        match res {
            0 => "pairwise coprime",
            1 => "setwise coprime",
            2 => "not coprime",
            _ => unreachable!(),
        }
    );
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
