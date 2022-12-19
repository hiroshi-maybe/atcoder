#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch factorial_and_multiple | diff factorial_and_multiple.out -
// $ cargo run --bin factorial_and_multiple

///
/// 12/17/2022
///
/// 20:58-21:30 pause
///
/// 12/18/2022
///
/// 17:38-17:52 AC
///
/// https://atcoder.jp/contests/abc280/editorial/5330
///

fn primes_to_map(ps: &Vec<i64>) -> HashMap<i64, i64> {
    let mut map = HashMap::new();
    for &p in ps {
        let e = map.entry(p).or_insert(0);
        *e += 1;
    }
    map
}

fn solve() -> i64 {
    let k = readln!(i64);
    let k_primes = k.prime_facts();
    let k_prime_map = primes_to_map(&k_primes);

    let mut res = 0;
    for (p, k_cnt) in k_prime_map {
        let mut cnt = k_cnt;
        let mut cur = 0;
        while cnt > 0 {
            cur += p;
            let mut x = cur;
            while x % p == 0 {
                x /= p;
                cnt -= 1;
            }
        }
        res.setmax(cur);
    }

    res
}

fn main() {
    setup_out!(put, puts);

    let res = solve();
    puts!("{}", res);
}

// region: int_fact

#[rustfmt::skip]
#[allow(dead_code)]
mod int_fact {
	pub trait IntFactorial where Self: Sized {
		fn divisors(&self) -> Vec<Self>;
		fn prime_facts(&self) -> Vec<Self>;
	}
	macro_rules! impl_int_fact { ($integer:ty) => {
		impl IntFactorial for $integer {
			fn divisors(&self) -> Vec<Self> {
				let n = *self; let mut res = vec![];
				for d in (1..).take_while(|&d| d * d <= n).filter(|&d| n % d == 0) {
					res.push(d);
					let dd = n / d;
					if d != dd { res.push(dd); }
				}
				res.sort_unstable();
				res
			}
			fn prime_facts(&self) -> Vec<Self> {
				let mut n = *self; let mut res = vec![];
				for p in (2..).take_while(|&p| p * p <= *self) {
					while n % p == 0 {
						res.push(p);
						n /= p;
					}
				}
				if n > 1 { res.push(n); }
				res
			}
		}
	}; }
	impl_int_fact!(i64); impl_int_fact!(i32); impl_int_fact!(usize);
}
pub use int_fact::*;

// endregion: int_fact

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
