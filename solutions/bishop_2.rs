#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch bishop_2 | diff bishop_2.out -
// $ cargo run --bin bishop_2

///
/// 4/2/2022
///
/// 10:48-11:45 TLE
/// 12:01 AC
///
/// https://atcoder.jp/contests/abc246/editorial/3702
/// https://twitter.com/laycrs/status/1510252453257969664
///

fn solve() -> isize {
    let n = readln!(usize);
    let (sr, sc) = readln!(usize1, usize1);
    let (gr, gc) = readln!(usize1, usize1);
    let s = readlns!([char]; n);
    let inf = 1_000_000_000usize;
    let mut d = vvec!(inf; n; n; 5);

    let moves = vec![(1, 1), (1, -1), (-1, 1), (-1, -1)];
    let mut q = VecDeque::new();
    let mv = |i: usize, di: isize| {
        let ii = i as isize + di;
        if (0..n as isize).contains(&ii) {
            Some(ii as usize)
        } else {
            None
        }
    };

    q.push_back((sr, sc, 4));
    d[sr][sc][4] = 0;
    while let Some((i, j, dir)) = q.pop_front() {
        let curd = d[i][j][dir];
        for dir2 in 0..moves.len() {
            let (di, dj) = moves[dir2];
            match (mv(i, di), mv(j, dj)) {
                (Some(ii), Some(jj)) if s[ii][jj] == '.' => {
                    let cost = if dir2 == dir { 0 } else { 1 };
                    if curd + cost < d[ii][jj][dir2] {
                        d[ii][jj][dir2] = curd + cost;
                        if cost == 1 {
                            q.push_back((ii, jj, dir2));
                        } else {
                            q.push_front((ii, jj, dir2));
                        }
                    }
                }
                _ => {}
            };
        }
    }

    let &res = d[gr][gc].iter().min().unwrap();
    if res == inf {
        -1
    } else {
        res as isize
    }
}

fn main() {
    setup_out!(put, puts);

    let res = solve();
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
