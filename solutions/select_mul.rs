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

#[rustfmt::skip]
#[allow(dead_code)]
pub fn next_permutation<T>(xs: &mut [T]) -> bool
where
	T: std::cmp::Ord,
{
	let asc_i = match xs.windows(2).rposition(|w| w[0] < w[1]) {
		Some(i) => i,
		None => { return false; }
	};
	let min_larger_offset = xs[asc_i + 1..]
		.binary_search_by(|x| match xs[asc_i].cmp(x) {
			std::cmp::Ordering::Equal => std::cmp::Ordering::Greater,
			ord => ord,
		})
		.unwrap_err();
	xs.swap(asc_i, asc_i + min_larger_offset);
	xs[asc_i + 1..].reverse();
	true
}
// $ rs-cp-batch select_mul | diff select_mul.out -
// $ cargo run --bin select_mul

///
/// 10/2/2021
///
/// 5:15-5:49 AC
///
/// https://atcoder.jp/contests/abc221/editorial/2720
///
/// 10/4/2021
///
/// 0:25 add solution without next_permutation
///

fn ith(mask: i64, i: usize) -> bool {
    ((mask >> i) & 1) == 1
}

fn calc(s: &Vec<i64>) -> i64 {
    let mut res = 0;
    for c in s {
        res = res * 10 + c;
    }
    res
}

#[allow(dead_code)]
fn findmax(mut a: Vec<i64>) -> i64 {
    let mut res = calc(&a);
    while next_permutation(&mut a) {
        res = max(res, calc(&a));
    }
    res
}

fn main() {
    setup_out!(put, puts);

    let mut s = readln!([char]);
    let n = s.len();

    s.sort_by_key(|x| Reverse(*x));
    let mut res = 0;

    for mask in 0..(1i64 << n) {
        let mut a = vec![];
        let mut b = vec![];
        for i in 0..n {
            let c = (s[i] as u8 - b'0') as i64;
            if ith(mask, i) {
                a.push(c);
            } else {
                b.push(c);
            };
        }
        res = max(res, calc(&a) * calc(&b));
    }

    assert_ne!(res, 0);

    puts!("{}", res);
}
