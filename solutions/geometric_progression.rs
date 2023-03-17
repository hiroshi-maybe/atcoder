#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

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

fn pow(a: i64, x: i64, m: i64) -> [[i64; 2]; 2] {
    if x == 0 {
        return [[1, 0], [0, 1]];
    }
    let mx = [[a, 1], [0, 1]];

    let mul = |a: [[i64; 2]; 2], b: [[i64; 2]; 2]| {
        [
            [
                (a[0][0] * b[0][0] % m + a[0][1] * b[1][0] % m) % m,
                (a[0][0] * b[0][1] % m + a[0][1] * b[1][1] % m) % m,
            ],
            [
                (a[1][0] * b[0][0] % m + a[1][1] * b[1][0] % m) % m,
                (a[1][0] * b[0][1] % m + a[1][1] * b[1][1] % m) % m,
            ],
        ]
    };

    // let add = |a: [[i64; 2]; 2], b: [[i64; 2]; 2]| {
    //     [
    //         [(a[0][0] + b[0][0]) % m, (a[0][1] + b[0][1]) % m],
    //         [(a[1][0] + b[1][0]) % m, (a[1][1] + b[1][1]) % m],
    //     ]
    // };

    // let a = [[1, 2], [3, 4]];
    // let b = [[5, 6], [7, 8]];
    // let ab = mul(a, b);
    // dbgln!(ab);

    let mut res = [[1, 0], [0, 1]];
    let mut cur = mx;
    for i in 0..40 {
        if (x >> i) & 1 == 1 {
            res = mul(res, cur);
        }
        cur = mul(cur, cur);
    }
    res
}

#[allow(dead_code)]
fn solve_mx_pow(a: i64, x: i64, m: i64) -> i64 {
    let ax = pow(a, x - 1, m);

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
