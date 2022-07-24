#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch larger_score | diff larger_score.out -
// $ cargo run --bin larger_score

///
/// 4/9/2022
///
/// 10:57-11:19 AC
///
/// https://atcoder.jp/contests/arc138/editorial/3746
///

fn solve() -> isize {
    let (n, k) = readln!(usize, usize);
    let a = readln!([i64]);

    let mut cand = vec![(0, n + 1)];
    for i in k..n {
        if a[i] > cand.last().unwrap().0 {
            cand.push((a[i], i));
        }
    }

    let mut res = n + 1;
    for i in 0..k {
        let j = cand.upper_bound(&(a[i], n + 1));
        if j < cand.len() {
            res.setmin(cand[j].1 - i);
        }
    }

    if res >= n {
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

// region: partition
#[rustfmt::skip]
#[allow(dead_code)]
mod partition {
	use std::cmp::Ordering;
	pub trait PartitionSlice {
		type Item;
		/// Find the partition point for which left segment satisifies the predicate
		/// [pred(item)] = [true, true, true, false, false]
		///                                   ^ res
		fn _partition_point<P>(&self, pred: P) -> usize where P: FnMut(&Self::Item) -> bool;

		/// Find the smallest index which satisfies key <= a[i]
		fn lower_bound(&self, key: &Self::Item) -> usize where Self::Item: Ord {
			self._partition_point(|item| item < key)
		}

		/// Find the smallest index which satisfies key < a[i]
		fn upper_bound(&self, key: &Self::Item) -> usize where Self::Item: Ord {
			self._partition_point(|item| item <= key)
		}
	}

	impl<T> PartitionSlice for [T] {
		type Item = T;
		fn _partition_point<P>(&self, mut pred: P) -> usize where P: FnMut(&T) -> bool {
			self.binary_search_by(|x| { if pred(x) { Ordering::Less } else { Ordering::Greater }})
				.unwrap_or_else(std::convert::identity)
		}
	}
}
pub use partition::PartitionSlice;
// endregion: partition

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