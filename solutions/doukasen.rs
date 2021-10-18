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

// $ rs-cp-batch doukasen | diff doukasen.out -
// $ cargo run --bin doukasen

///
/// 10/17/2021
///
/// 9:48-10:22 AC
/// 22:30 Add simpler non-binary-serach solution.
///
/// https://atcoder.jp/contests/abc223/editorial/2773
///

#[allow(dead_code)]
fn solve_v0(ab: Vec<(f64, f64)>) -> f64 {
    let mut abrev = ab.clone();
    abrev.reverse();

    let tot_dist = ab.iter().map(|(a, _)| a).sum();
    let mut good: f64 = tot_dist;
    let mut bad = 0.0;

    for _ in 0..100 {
        let m = (good + bad) / 2.0;

        let comp_time = |ab: &Vec<(f64, f64)>, m: f64| {
            let mut ltime = 0.0;
            let mut ldist = m;
            for (a, b) in ab {
                if ldist == 0.0 {
                    break;
                }

                let d = if ldist.partial_cmp(a).unwrap() == Ordering::Less {
                    ldist
                } else {
                    *a
                };
                ltime += d / b;
                ldist -= d;
            }
            ltime
        };
        let ltime = comp_time(&ab, m);
        let rtime = comp_time(&abrev, tot_dist - m);

        //dbgln!(m, ltime, rtime, ltime.partial_cmp(&rtime).unwrap());

        if ltime.partial_cmp(&rtime).unwrap() != Ordering::Less {
            good = m;
        } else {
            bad = m;
        }
    }
    good
}

fn solve_v1(ab: Vec<(f64, f64)>) -> f64 {
    let mut t = ab.iter().map(|&(a, b)| a / b).sum::<f64>() / 2.0;
    let mut d = 0.0;
    for (a, b) in &ab {
        if t <= 0.0 {
            break;
        }
        let tt = if t < a / b { t } else { a / b };
        d += b * tt;
        t -= tt;
        //dbgln!(d, tt, t, a / b);
    }
    d
}

fn main() {
    setup_out!(put, puts);

    let n = readln!(usize);
    let ab = readlns!(f64, f64; n);

    let res = solve_v1(ab);
    puts!("{}", res);
}
