#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch ranges_on_tree | diff ranges_on_tree.out -
// $ cargo run --bin ranges_on_tree

///
/// 2/20/2022
///
/// 15:24-15:37 WA
/// 16:46 AC
///
/// https://atcoder.jp/contests/abc240/editorial/3426
///

fn dfs2(
    u: usize,
    par: usize,
    mut offset: usize,
    g: &Vec<Vec<usize>>,
    lcnt: &Vec<usize>,
    res: &mut Vec<(usize, usize)>,
) {
    let o = offset;
    for &v in g[u].iter().filter(|&&v| v != par) {
        dfs2(v, u, offset, g, lcnt, res);
        offset += lcnt[v];
    }
    res[u] = (
        o,
        if g[u].len() == 1 && u != 0 {
            o + 1
        } else {
            offset
        },
    );
}

fn dfs(u: usize, par: usize, g: &Vec<Vec<usize>>, lcnt: &mut Vec<usize>) -> usize {
    for &v in g[u].iter().filter(|&&v| v != par) {
        lcnt[u] += dfs(v, u, g, lcnt);
    }
    if g[u].len() == 1 && u != 0 {
        lcnt[u] = 1;
    }

    lcnt[u]
}

fn solve(n: usize, g: &Vec<Vec<usize>>) -> Vec<(usize, usize)> {
    let mut lcnt = vec![0; n];
    dfs(0, n, &g, &mut lcnt);
    let mut res = vec![(0, 0); n];
    dfs2(0, n, 0, &g, &lcnt, &mut res);
    // dbgln!(lcnt);
    assert_eq!(res[0].1, lcnt[0]);

    res
}

fn main() {
    setup_out!(put, puts);

    let n = readln!(usize);
    let mut g = vec![vec![]; n];
    for (u, v) in readlns!(usize1, usize1; n-1) {
        g[u].push(v);
        g[v].push(u);
    }

    let res = solve(n, &g);
    for r in res {
        puts!("{} {}", r.0 + 1, r.1);
    }
}

#[test]
fn test_random() {
    use rand::prelude::*;

    fn gen_tree(n: usize) -> Vec<Vec<usize>> {
        let mut rng = thread_rng();
        let mut p = vec![0; n - 1];
        println!("{}", n);
        for u in 1..n {
            p[u - 1] = rng.gen_range(0, u);
            println!("{} {}", u + 1, p[u - 1] + 1);
        }

        let mut g = vec![vec![]; n];
        for u in 1..n {
            let v = p[u - 1];
            g[u].push(v);
            g[v].push(u);
        }
        g
    }

    loop {
        let n = 5;
        let g = gen_tree(n);
        solve(n, &g);
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
