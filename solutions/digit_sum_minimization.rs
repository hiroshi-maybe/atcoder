#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch digit_sum_minimization | diff digit_sum_minimization.out -
// $ cargo run --bin digit_sum_minimization

///
/// 11/30/2021
///
/// 8:54-9:58 give up
/// 10:24 read editorial
/// 22:00-23:30 WA
/// 23:41 AC
///
/// https://atcoder.jp/contests/arc130/editorial/2976
/// https://youtu.be/FLyDTbnbvd0?t=1116
///
/// https://twitter.com/hanseilimak/status/1465952768745623558
///
/// https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.qhlz9guposuh
/// https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.uucps3zg6s9m
///

pub trait OffsetBy {
    type Output;
    fn offset_by(&self, base: &Self) -> Self::Output;
}
impl OffsetBy for char {
    type Output = u8;
    fn offset_by(&self, base: &char) -> Self::Output {
        *self as u8 - *base as u8
    }
}

fn cnts(a: &Vec<char>) -> Vec<usize> {
    let a = a.iter().map(|&c| c.offset_by(&'0')).collect_vec();
    let mut cnt = vec![0; 10];
    for x in a {
        cnt[x as usize] += 1;
    }
    cnt
}

fn mkres(a: &Vec<(usize, usize)>) -> Vec<usize> {
    let mut res = vec![];
    for (d, cnt) in a {
        for _ in 0..*cnt {
            res.push(*d);
        }
    }
    res.reverse();
    res
}

fn solve() -> (Vec<usize>, Vec<usize>) {
    let a = readln!([char]);
    let a = cnts(&a);

    let b = readln!([char]);
    let b = cnts(&b);

    let mut max_c = -1;
    let mut res = (vec![], vec![]);

    for d0 in (1..=9).filter(|&d| a[d] > 0) {
        let mut c = 0;
        let (mut aa, mut bb) = (vec![], vec![]);
        let (mut a, mut b) = (a.clone(), b.clone());

        if let Some(d1) = (1..=9).find(|&d| d + d0 >= 10 && b[d] > 0) {
            a[d0] -= 1;
            b[d1] -= 1;
            aa.push((d0, 1));
            bb.push((d1, 1));
            c += 1;

            for d0 in 1..=9 {
                for d1 in (1..=9).skip_while(|&d| d0 + d < 9) {
                    let x = min(a[d0], b[d1]);
                    if x > 0 {
                        aa.push((d0, x));
                        bb.push((d1, x));
                        a[d0] -= x;
                        b[d1] -= x;
                        c += x as i64;
                    }
                }
            }
        }
        for d in (1..=9).rev() {
            if a[d] > 0 {
                aa.push((d, a[d]));
            }
            if b[d] > 0 {
                bb.push((d, b[d]));
            }
            if d == 9 && (a[d] > 0 || b[d] > 0) && !aa.is_empty() {
                c += max(a[d], b[d]) as i64;
            }
        }

        if c > max_c {
            max_c = c;
            res = (aa, bb);
        }
    }

    (mkres(&res.0), mkres(&res.1))
}

fn main() {
    setup_out!(put, puts);

    let (s0, s1) = solve();
    for x in vec![s0, s1] {
        puts!(
            "{}",
            x.iter()
                .map(|&d| std::char::from_digit(d as u32, 10).unwrap())
                .collect::<String>()
        );
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
