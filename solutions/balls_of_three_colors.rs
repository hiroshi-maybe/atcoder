#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// region: io
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
// endregion: io

// $ rs-cp-batch balls_of_three_colors | diff balls_of_three_colors.out -
// $ cargo run --bin balls_of_three_colors

///
/// 10/16/2021
///
/// 6:23-7:09 AC
///
/// https://atcoder.jp/contests/arc128/editorial/2786
///
/// https://twitter.com/laycrs/status/1449374631207391233
/// https://twitter.com/kuuso1/status/1449376027759681540
/// https://twitter.com/heno_code/status/1449375992519163908
/// https://twitter.com/kuretchi/status/1449375692794171399
/// https://twitter.com/kzyKT_M/status/1449374983491186692
///

const INF: i64 = 1_000_000_000_000;

fn f(mut a: i64, mut b: i64) -> i64 {
    if a > b {
        std::mem::swap(&mut a, &mut b);
    }

    if (b - a) % 3 == 0 {
        let x = (b - a) / 3;
        a + 3 * x
    } else {
        INF
    }
}

fn main() {
    setup_out!(put, puts);

    let t = readln!(usize);
    for _ in 0..t {
        let (r, g, b) = readln!(i64, i64, i64);
        let mut res = INF;
        res = min(res, f(r, g));
        res = min(res, f(g, b));
        res = min(res, f(b, r));
        if res == INF {
            res = -1;
        }

        puts!("{}", res);
    }
}
