#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch dance | diff dance.out -
// $ cargo run --bin dance

///
/// 1/23/2022
///
/// 9:57-10:43 AC
/// 12:12 Implement with stack
///
/// https://atcoder.jp/contests/abc236/editorial/3285
///

#[allow(dead_code)]
fn dfs(
    i: usize,
    a: &Vec<Vec<usize>>,
    n: usize,
    viz: &mut Vec<bool>,
    mut cnt: usize,
    cur: usize,
    res: &mut usize,
) {
    if cnt == 2 * n {
        //dbgln!(cur, cnt, viz);
        res.setmax(cur);
        return;
    }
    if i == 2 * n - 1 {
        return;
    }
    if viz[i] {
        dfs(i + 1, a, n, viz, cnt, cur, res);
    } else {
        for j in 0..a[i].len() {
            let jj = i + j + 1;
            if viz[jj] {
                continue;
            }
            viz[i] = true;
            viz[jj] = true;
            cnt += 2;
            //dbgln!(i, jj, cur, a[i][j], cur ^ a[i][j]);
            dfs(i + 1, a, n, viz, cnt, cur ^ a[i][j], res);
            cnt -= 2;
            viz[i] = false;
            viz[jj] = false;
        }
    }
}

fn ith(mask: usize, i: usize) -> bool {
    ((mask >> i) & 1) == 1
}
fn solve() -> usize {
    let n = readln!(usize);
    let m = 2 * n;
    let a = readlns!([usize]; m - 1);

    let mut res = 0;
    // let mut viz = vec![false; 2 * n];
    // dfs(0, &a, n, &mut viz, 0, 0, &mut res);

    let mut st = VecDeque::new();
    st.push_back((0usize, (1usize << m) - 1));
    while let Some((cur, mut mask)) = st.pop_back() {
        let i = mask.trailing_zeros() as usize;
        //eprintln!("{:b}, {}", mask, i);
        if i >= m {
            res.setmax(cur);
            continue;
        }
        mask ^= 1 << i;
        for j in 0..m {
            if ith(mask, j) {
                st.push_back((cur ^ a[i][j - i - 1], mask ^ (1 << j)));
            }
        }
    }

    res
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
