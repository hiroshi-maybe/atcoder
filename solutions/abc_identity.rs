#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch abc_identity | diff abc_identity.out -
// $ cargo run --bin abc_identity

///
/// 10/31/2021
///
/// 8:48-9:48 give up
///
/// 11/1/2021
///
/// 9:00-10:00, 21:48-23:26 read editorial and got AC
///
/// https://atcoder.jp/contests/agc055/editorial/2872
/// https://manabitimes.jp/math/904
///
/// https://twitter.com/maspy_stars/status/1454828599656157184
/// https://twitter.com/satanic0258/status/1454828587849183240
/// https://twitter.com/kiri8128/status/1454827064524099592
/// https://twitter.com/laycrs/status/1454827471862333457
/// https://twitter.com/semiexp/status/1454827448646791182
/// https://twitter.com/chokudai/status/1454826544694652930
/// https://twitter.com/ei1333/status/1454826363035140106
/// https://twitter.com/kmjp_pc/status/1454826344710164491
/// https://twitter.com/tomerun/status/1454826111775379456
///

// region: next_permutation
#[rustfmt::skip]
#[allow(dead_code)]
pub fn next_permutation<T>(xs: &mut [T]) -> bool
where
	T: std::cmp::Ord,
{
	let asc_i = match xs.windows(2).rposition(|w| w[0] < w[1]) {
		Some(i) => i,
		None => { return false; }
	};
	let min_larger_offset = xs[asc_i + 1..]
		.binary_search_by(|x| match xs[asc_i].cmp(x) {
			std::cmp::Ordering::Equal => std::cmp::Ordering::Greater,
			ord => ord,
		})
		.unwrap_err();
	xs.swap(asc_i, asc_i + min_larger_offset);
	xs[asc_i + 1..].reverse();
	true
}
// endregion: next_permutation

fn main() {
    setup_out!(put, puts);

    let n = readln!(usize);
    let s = readln!([char]);
    let mut qs = vvec![VecDeque::new(); 3; 3];
    for i in 0..3 * n {
        let c = s[i] as u8 - b'A';
        qs[i / n][c as usize].push_back(i);
    }

    let mut res = vec![-1; 3 * n];
    let mut pat = vec![0, 1, 2];
    let mut pid = 0;
    loop {
        pid += 1;
        // dbgln!(pid, pat);
        while (0..3).all(|g| !qs[g][pat[g]].is_empty()) {
            for g in 0..3 {
                let p = qs[g][pat[g]].pop_front().unwrap();
                res[p] = pid;
            }
        }

        if !next_permutation(&mut pat) {
            break;
        }
    }

    assert_eq!(res.iter().filter(|x| **x != -1).count(), 3 * n);
    for c in res {
        put!("{}", c);
    }
    puts!();
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
