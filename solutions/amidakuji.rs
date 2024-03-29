#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch amidakuji | diff amidakuji.out -
// $ cargo run --bin amidakuji

///
/// 10/28/2021
///
/// 21:54-22:35 AC
///

#[allow(dead_code)]
fn solve_v0() -> usize {
    let (n, l) = readln!(usize, usize);
    let mut g = vec![Vec::<usize>::new(); n * l];
    for r in 0..l {
        let s = readln_str().chars().collect_vec();
        for c in 0..n {
            if c < n - 1 && s[2 * c + 1] == '-' {
                g[r * n + c].push(r * n + c + 1);
                g[r * n + (c + 1)].push(r * n + c);
            }
            if r > 0 {
                g[r * n + c].push((r - 1) * n + c);
            }
        }
    }

    let mut viz = vec![false; n * l];

    let s = readln_str().chars().collect_vec();
    //dbgln!(s);
    let mut cur = n * l;
    for c in 0..n {
        if s[2 * c] == 'o' {
            cur = n * (l - 1) + c;
        }
    }
    viz[cur] = true;
    //dbgln!(cur);
    //dbgln!(g);
    while !g[cur].is_empty() {
        //dbgln!(cur);
        if let Some(i) = g[cur].iter().position(|&v| !viz[v]) {
            cur = g[cur][i];
            viz[cur] = true;
        } else {
            break;
        }
    }

    cur + 1
}

fn solve_v1() -> usize {
    let (_n, l) = readln!(usize, usize);
    let mut g = vec![];
    for _ in 0..l {
        let s = readln_str().chars().collect_vec();
        g.push(s);
    }

    g.reverse();
    let mut cur = readln_str()
        .chars()
        .collect_vec()
        .iter()
        .position(|c| *c == 'o')
        .unwrap()
        / 2;

    //dbgln!(g);
    for i in 0..l {
        //dbgln!(cur);
        if g[i][2 * cur + 1] == '-' {
            cur += 1;
        } else if cur > 0 && g[i][2 * cur - 1] == '-' {
            cur -= 1;
        }
    }

    cur + 1
}

fn main() {
    setup_out!(put, puts);

    let res = solve_v1();

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
