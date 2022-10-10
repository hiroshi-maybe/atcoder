#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch root_m_leaper | diff root_m_leaper.out -
// $ cargo run --bin root_m_leaper

///
/// 10/9/2022
///
/// 10:20-10:55 AC
///
/// https://atcoder.jp/contests/abc272/editorial/4978
///

fn solve() -> Vec<Vec<isize>> {
    let (n, m) = readln!(usize, usize);
    let inf = 1_000_000_000_isize;
    let mut d = vvec!(inf; n; n);

    let mut moves = vec![];
    for di in 0..=1_000_isize {
        for dj in 0..=1_000_isize {
            if di * di + dj * dj == m as isize {
                moves.push((di, dj));
                moves.push((-di, dj));
                moves.push((di, -dj));
                moves.push((-di, -dj));
            }
        }
    }

    let mut q = VecDeque::new();
    d[0][0] = 0;
    q.push_back((0, 0));
    while let Some((i, j)) = q.pop_front() {
        let cur = d[i][j];
        let n = n as isize;
        for &(di, dj) in &moves {
            if (0..n).contains(&(di + i as isize)) && (0..n).contains(&(dj + j as isize)) {
                let ii = (i as isize + di) as usize;
                let jj = (j as isize + dj) as usize;
                if cur + 1 < d[ii][jj] {
                    d[ii][jj] = cur + 1;
                    q.push_back((ii, jj));
                }
            }
        }
    }

    for i in 0..n {
        for j in 0..n {
            if d[i][j] == inf {
                d[i][j] = -1;
            }
        }
    }

    d
}

fn main() {
    setup_out!(put, puts);

    let res = solve();
    for r in res {
        for r in r {
            put!("{} ", r);
        }
        puts!();
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
