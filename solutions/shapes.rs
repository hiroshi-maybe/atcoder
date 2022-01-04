#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch shapes | diff shapes.out -
// $ cargo run --bin shapes

///
/// 1/3/2022
///
/// 20:24-21:49 WA
/// 22:21 AC
///
/// https://atcoder.jp/contests/abc218/editorial/2598
///

fn rotate(n: usize, t: &mut Vec<Vec<char>>) {
    for i in 0..n {
        for j in 0..n / 2 {
            t[i].swap(j, n - j - 1);
        }
    }
    for i in 0..n {
        for j in (0..).take_while(|&j| i + j < n) {
            let (ii, jj) = (n - 1 - j, n - 1 - i);
            let (a, b) = (t[i][j], t[ii][jj]);
            t[ii][jj] = a;
            t[i][j] = b;
        }
    }
}

fn count(n: usize, s: &Vec<Vec<char>>) -> usize {
    (0..n * n).filter(|&p| s[p / n][p % n] == '#').count()
}

fn ok(n: usize, dr: i32, dc: i32, s: &Vec<Vec<char>>, t: &Vec<Vec<char>>) -> bool {
    let cnt_h = count(n, &s);
    let mut cnt = cnt_h as i32;
    for r in (0..n).filter(|&r| (0..n as i32).contains(&(r as i32 + dr))) {
        for c in (0..n).filter(|&c| (0..n as i32).contains(&(c as i32 + dc))) {
            let rr = (r as i32 + dr) as usize;
            let cc = (c as i32 + dc) as usize;
            //dbgln!(r, c, s[r][c], rr, cc, t[rr][cc]);
            if s[r][c] != t[rr][cc] {
                return false;
            }
            if s[r][c] == '#' {
                cnt -= 1;
            }
        }
    }
    cnt == 0
}

fn solve(n: usize, s: &Vec<Vec<char>>, t: &mut Vec<Vec<char>>) -> bool {
    if count(n, &s) != count(n, &t) {
        return false;
    }
    //let cnt_h = (0..n * n).filter(|&p| s[p / n][p % n] == '#').count();
    let pos_s = (0..n * n).find(|&p| s[p / n][p % n] == '#').unwrap();

    for _ in 0..4 {
        let pos_t = (0..n * n).find(|&p| t[p / n][p % n] == '#').unwrap();
        let dr = pos_t as i32 / n as i32 - pos_s as i32 / n as i32;
        let dc = pos_t as i32 % n as i32 - pos_s as i32 % n as i32;

        if ok(n, dr, dc, &s, &t) {
            return true;
        }

        rotate(n, t);
        /*for i in 0..n {
            println!("{}", t[i].iter().collect::<String>())
        }*/
    }

    false
}

fn main() {
    setup_out!(put, puts);
    let n = readln!(usize);
    let s = readlns!([char]; n);
    let mut t = readlns!([char]; n);
    let res = solve(n, &s, &mut t);
    puts!("{}", if res { "Yes" } else { "No" });
}

#[test]
fn test_random() {
    use rand::prelude::*;
    loop {
        let mut rng = thread_rng();
        let n = 5;
        let mut gen = || {
            (0..n)
                .map(|_| {
                    (0..n)
                        .map(|_| if rng.gen_range(0, 2) == 1 { '#' } else { '.' })
                        .collect_vec()
                })
                .collect_vec()
        };
        let s = gen();
        let mut t = gen();

        let act = solve(n, &s, &mut t);
        let mut exp = false;
        for _ in 0..4 {
            for dr in -(n as i32)..n as i32 {
                for dc in -(n as i32)..n as i32 {
                    exp |= ok(n, dr, dc, &s, &t);
                }
            }
            rotate(n, &mut t);
        }

        if act != exp {
            dbgln!(act, exp, s, t);
        }
        assert_eq!(act, exp);
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
