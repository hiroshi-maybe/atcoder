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

// $ rs-cp-batch online_games | diff online_games.out -
// $ cargo run --bin online_games

///
/// 10/2/2021
///
/// 5:50-6:09 AC
///
/// https://atcoder.jp/contests/abc221/editorial/2722
///

#[allow(dead_code)]
fn solve_btreemap(n: usize) -> Vec<i64> {
    let mut imos = BTreeMap::new();
    for (a, b) in readlns!(i64, i64; n) {
        *imos.entry(a).or_insert(0) += 1i32;
        *imos.entry(a + b).or_insert(0) -= 1i32;
    }
    let mut res = vec![0i64; n + 1];
    let mut cur = 0i32;
    let mut prevt = 0;
    for (t, v) in imos {
        //dbgln!(cur, prevt, t, v);
        res[cur as usize] += t - prevt;
        cur += v;
        prevt = t;
    }
    assert_eq!(cur, 0);
    res
}

fn solve_sort(n: usize) -> Vec<i32> {
    let mut es = vec![];
    for (a, b) in readlns!(i32, i32; n) {
        es.push((a, 1));
        es.push((a + b, -1));
    }
    es.sort_unstable();
    let mut res = vec![0i32; n + 1];
    let mut cur = 0;
    for es in es.windows(2) {
        cur += es[0].1;
        res[cur as usize] += es[1].0 - es[0].0;
    }
    //assert_eq!(cur, 0);
    res
}

fn main() {
    setup_out!(put, puts);

    let n = readln!(usize);
    let res = solve_sort(n);
    for k in 1..=n {
        put!("{} ", res[k]);
    }
    puts!();
}
