#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch round_trip | diff round_trip.out -
// $ cargo run --bin round_trip

///
/// 11/5/2022
///
/// 12:44-13:09 AC
///
/// https://atcoder.jp/contests/abc276/editorial/5162
///

fn solve() -> bool {
    let (h, w) = readln!(usize, usize);
    let c = readlns!([char]; h);

    let gg = GridGraph::new(h, w);
    let mut s0 = (h, w);
    for i in 0..h {
        for j in 0..w {
            if c[i][j] == 'S' {
                s0 = (i, j);
            }
        }
    }
    let starts = gg
        .adj_cells4(s0.0, s0.1)
        .filter(|&(i, j)| c[i][j] == '.')
        .collect_vec();
    let inf = 1_000_000_000;
    let solve = |si: usize| {
        let mut d = vvec!(inf; h; w);
        let mut q = VecDeque::new();
        q.push_back(starts[si]);
        d[starts[si].0][starts[si].1] = 0;
        while let Some((i, j)) = q.pop_front() {
            let dist = d[i][j];
            // dbgln!(si, i, j, dist);
            for (ii, jj) in gg.adj_cells4(i, j) {
                if c[ii][jj] == '.' && d[ii][jj].setmin(dist + 1) {
                    q.push_back((ii, jj));
                }
            }
        }
        (0..starts.len())
            .filter(|&i| i != si)
            .any(|i| d[starts[i].0][starts[i].1] < inf)
    };

    (0..starts.len()).any(|si| solve(si))
}

fn main() {
    setup_out!(put, puts);

    let res = solve();
    puts!("{}", if res { "Yes" } else { "No" });
}

// region: grid_graph

#[rustfmt::skip]
#[allow(dead_code)]
mod grid_graph {
	pub struct GridGraph { h: usize, w: usize, }
	impl GridGraph { pub fn new(h: usize, w: usize) -> GridGraph { GridGraph { h, w } } }
	macro_rules! impl_adjacent_cells {
		($method: ident, $iterator: ident, $moves: expr) => {
			impl GridGraph {
				pub fn $method(&self, i: usize, j: usize) -> $iterator {
					assert!(i < self.h && j < self.w);
					$iterator { cur: 0, i: i as i64, j: j as i64, w: self.w as i64, h: self.h as i64 }
				}
			}
			pub struct $iterator { cur: usize, i: i64, j: i64, w: i64, h: i64 }
			impl Iterator for $iterator {
				type Item = (usize, usize);
				fn next(&mut self) -> Option<Self::Item> {
					for &(di,dj) in $moves[self.cur..].iter() {
						self.cur += 1;
						let (ii, jj) = (self.i + di, self.j + dj);
						if (0..self.h).contains(&ii) && (0..self.w).contains(&jj) {
							return Some((ii as usize, jj as usize));
						}
					}
					None
				}
			}
		}
	}
	impl_adjacent_cells!(adj_cells4, AdjacentCells4, vec![(1,0),(0,1),(-1,0),(0,-1)]);
	impl_adjacent_cells!(adj_cells2, AdjacentCells2, vec![(1,0),(0,1)]);
}
pub use grid_graph::GridGraph;

// endregion: grid_graph

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
