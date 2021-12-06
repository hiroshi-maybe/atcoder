#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch grid_repainting_4 | diff grid_repainting_4.out -
// $ cargo run --bin grid_repainting_4

///
/// 12/5/2021
///
/// 22:02-22:19 AC
///
/// https://atcoder.jp/contests/arc131/editorial/3042
///

// region: grid_graph

#[rustfmt::skip]
#[allow(dead_code)]
mod grid_graph {
	pub struct GridGraph { h: usize, w: usize, }
	impl GridGraph {
		pub fn new(h: usize, w: usize) -> GridGraph { GridGraph { h, w } }
		pub fn adj_cells4(&self, i: usize, j: usize) -> AdjacentCells {
			assert!(i < self.h && j < self.w);
			AdjacentCells { cur: 0, i: i as i64, j: j as i64, w: self.w as i64, h: self.h as i64 }
		}
	}
	pub struct AdjacentCells { cur: usize, i: i64, j: i64, w: i64, h: i64 }
	impl Iterator for AdjacentCells {
		type Item = (usize, usize);
		fn next(&mut self) -> Option<Self::Item> {
			const MOVES: [(i64, i64); 4] = [(1,0),(0,1),(-1,0),(0,-1)];
			for &(di,dj) in MOVES[self.cur..].iter() {
				self.cur += 1;
				let (ii, jj) = (self.i +di, self.j + dj);
				if (0..self.h).contains(&ii) && (0..self.w).contains(&jj) {
					return Some((ii as usize, jj as usize));
				}
			}
			None
		}
	}
}
pub use grid_graph::GridGraph;

// endregion: grid_graph

fn solve() -> Vec<Vec<char>> {
    let (h, w) = readln!(usize, usize);
    let mut mx = readlns!([char]; h);
	let g = GridGraph::new(h, w);
    for i in 0..h {
        for j in 0..w {
            if mx[i][j] != '.' {
                continue;
            }
            let mut viz = vec![false; 6];
			for (ii, jj) in g.adj_cells4(i, j).filter(|&(i,j)| mx[i][j]!='.') {
        		viz[(mx[ii][jj] as u8 - b'0') as usize] = true;
			}
            let c = (1..=5).find(|c| !viz[*c]).unwrap();
            mx[i][j] = (b'0' + c as u8) as char;
        }
    }

    mx
}

fn main() {
    setup_out!(put, puts);

    let res = solve();
    for r in res {
        puts!("{}", r.iter().collect::<String>());
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
