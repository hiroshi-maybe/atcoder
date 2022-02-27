#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch sequence_query | diff sequence_query.out -
// $ cargo run --bin sequence_query

///
/// 2/26/2022
///
/// 9:17-9:58 AC
///
/// https://atcoder.jp/contests/abc241/editorial/3453
///

fn solve() {
    setup_out!(put, puts);
    let q = readln!(usize);
    let mut set = BTreeSet::new();
    let inf = 1_000_000;
    for i in 0..q {
        let s = readln!([i64]);
        // dbgln!(set, s);
        let x = s[1];
        match s[0] {
            1 => {
                set.insert((x, i));
            }
            2 => {
                let k = s[2] as usize - 1;
                let res = set.range(..(x, inf)).nth_back(k).map_or(-1, |&p| p.0);
                puts!("{}", res);
            }
            _ => {
                let k = s[2] as usize - 1;
                let res = set.range((x, 0)..).nth(k).map_or(-1, |&p| p.0);
                puts!("{}", res);
            }
        }
    }
}

#[allow(dead_code)]
fn solve_v0() {
    let q = readln!(usize);
    let mut set = BTreeSet::new();
    let mut rset = BTreeSet::new();
    let inf = 1_000_000;
    for i in 0..q {
        let s = readln!([i64]);
        // dbgln!(set, rset, s);
        let x = s[1];
        match s[0] {
            1 => {
                set.insert((x, i));
                rset.insert(Reverse((x, i)));
            }
            2 => {
                let k = s[2];
                let mut it = rset.range(Reverse((x, inf))..);
                let mut res = None;
                for _ in 0..k {
                    res = it.next();
                    if res.is_none() {
                        break;
                    }
                }
                let res = res.map(|r| r.0 .0).unwrap_or(-1);
                println!("{}", res);
            }
            _ => {
                let k = s[2];
                let mut it = set.range((x, 0)..);
                let mut res = None;
                for _ in 0..k {
                    res = it.next();
                    if res.is_none() {
                        break;
                    }
                }
                let res = res.map(|r| r.0).unwrap_or(-1);
                println!("{}", res);
            }
        }
    }
}

fn main() {
    // setup_out!(put, puts);

    solve();
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
