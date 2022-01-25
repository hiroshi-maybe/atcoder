#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch dividing_subsequence | diff dividing_subsequence.out -
// $ cargo run --bin dividing_subsequence

///
/// 1/22/2022
///
/// 10:01-10:47 AC
///
/// https://atcoder.jp/contests/arc133/editorial/3283
///

fn solve() -> usize {
    let n = readln!(usize);
    let p = readln!([usize]);
    let q = readln!([usize]);

    let mut qpos = vec![n + 1; n + 1];
    for (i, &q) in q.iter().enumerate() {
        qpos[q] = i;
    }

    let mut cand = vec![vec![]; n];
    for i in 0..n {
        let x = p[i];
        for xx in (x..).step_by(x).take_while(|&y| y <= n) {
            cand[i].push(qpos[xx]);
        }
    }

    let inf = 1_000_000_000usize;
    let mut lis = vec![inf; n + 1];
    for mut xs in cand {
        xs.sort_unstable_by_key(|&x| Reverse(x));
        //dbgln!(xs);
        for i in xs {
            let p = lis.lower_bound(&i);
            lis[p].setmin(i);
        }
        //dbgln!(lis);
    }
    //dbgln!(lis);

    lis.iter().rposition(|&x| x < inf).unwrap_or(0) + 1
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
		/// items = [true, true, true, false, false]
		///                            ^ res
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
