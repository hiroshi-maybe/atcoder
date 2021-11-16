#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch takahashi_and_image_processing | diff takahashi_and_image_processing.out -
// $ cargo run --bin takahashi_and_image_processing

///
/// 11/15/2021
///
/// 22:24-22:49 AC
///
/// https://img.atcoder.jp/data/abc/039/editorial.pdf
///

fn solve() -> Option<Vec<Vec<char>>> {
    let (n, m) = readln!(usize, usize);
    let a = readlns!([char]; n);

    let mut b = vvec!('.'; n; m);
    for i in 0..n {
        for j in 0..m {
            if a[i][j] == '#' {
                let mut black = true;
                for di in -1..=1 {
                    for dj in -1..=1 {
                        let ii = di + i as i32;
                        let jj = dj + j as i32;
                        if (0..n as i32).contains(&ii) && (0..m as i32).contains(&jj) {
                            black &= a[ii as usize][jj as usize] == '#';
                        }
                    }
                }
                //dbgln!(i, j, black);
                if black {
                    b[i][j] = '#';
                }
            }
        }
    }

    let mut aa = vvec!['.'; n; m];
    for i in 0..n {
        for j in 0..m {
            if b[i][j] == '#' {
                for di in -1..=1 {
                    for dj in -1..=1 {
                        let ii = di + i as i32;
                        let jj = dj + j as i32;
                        if (0..n as i32).contains(&ii) && (0..m as i32).contains(&jj) {
                            aa[ii as usize][jj as usize] = '#';
                        }
                    }
                }
            }
        }
    }

    if a == aa {
        Some(b)
    } else {
        None
    }
}

fn main() {
    setup_out!(put, puts);

    let res = solve();
    if let Some(res) = res {
        puts!("possible");
        for s in res {
            puts!("{}", s.iter().collect::<String>());
        }
    } else {
        puts!("impossible");
    }
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
