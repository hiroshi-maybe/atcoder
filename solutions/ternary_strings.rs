#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

#[rustfmt::skip]
#[macro_use]
#[allow(dead_code)]
mod io {
	macro_rules! with_dollar_sign { ($($body:tt)*) => { macro_rules! __with_dollar_sign { $($body)* } __with_dollar_sign!($); }}
	macro_rules! setup_out {
		($fn:ident,$fn_s:ident) => {
			use std::io::Write;
			let out = std::io::stdout();
			let mut out = ::std::io::BufWriter::new(out.lock());
			with_dollar_sign! { ($d:tt) => {
				macro_rules! $fn { ($d($format:tt)*) => { let _ = write!(out,$d($format)*); } }
				macro_rules! $fn_s { ($d($format:tt)*) => { let _ = writeln!(out,$d($format)*); } }
			}}
		};
	}
	macro_rules! _epr { ($v:expr $(,)?) => {eprint!("{} = {:?}, ", stringify!($v), $v)}; }
	macro_rules! dbgln { ($($val:expr),*) => {{ eprint!("[{}:{}] ", file!(), line!()); ($(_epr!($val)),*); eprintln!(); }}; }
	pub fn readln() -> String {
		let mut line = String::new();
		::std::io::stdin().read_line(&mut line).unwrap_or_else(|e| panic!("{}", e));
		line
	}
	macro_rules! readlns {
		($($t:tt),*; $n:expr) => {{ let stdin = ::std::io::stdin();
			::std::io::BufRead::lines(stdin.lock()).take($n).map(|line| {
				let line = line.unwrap(); #[allow(unused_mut)]let mut it = line.split_whitespace(); _read!(it; $($t),*)
			}).collect::<Vec<_>>()
		}};
	}
	macro_rules! readln {
		($($t:tt),*) => {{ let line = io::readln(); #[allow(unused_mut)]let mut it = line.split_whitespace(); _read!(it; $($t),*) }};
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
}

// $ rs-cp-batch ternary_strings | diff ternary_strings.out -
// $ cargo run --bin ternary_strings

///
/// 9/25/2021
///
/// 4:56-5:51 AC
/// 10:28 solve without dfs
///
/// https://atcoder.jp/contests/arc127/editorial/2687
/// https://twitter.com/laycrs/status/1441749343443165187
/// https://twitter.com/kiri8128/status/1441749990951440395?s=20
///

#[allow(dead_code)]
fn dfs(i: usize, l: usize, cur: &mut Vec<char>, s2: &mut Vec<Vec<char>>) {
    if i == l {
        let s = cur.clone();
        s2.push(s);
        return;
    }

    for c in 0..=2 {
        let cc = (b'0' as u8 + c) as char;
        cur.push(cc);
        dfs(i + 1, l, cur, s2);
        cur.pop();
    }
}
#[allow(dead_code)]
fn solve_dfs(n: usize, l: usize) {
    setup_out!(put, puts);

    let mut s2: Vec<Vec<char>> = vec![];
    let mut cur = vec!['2'];
    dfs(1, l, &mut cur, &mut s2);
    s2.sort();

    let mut res: Vec<Vec<char>> = vec![];
    for i in 0..n {
        let s2 = &s2[i];
        res.push(s2.clone());

        let mut s1 = vec!['1'];
        let mut s0 = vec!['0'];
        for j in 1..l {
            let c = s2[j] as u8 - b'0';
            s1.push((((c + 1) % 3) + b'0') as char);
            s0.push((((c + 2) % 3) + b'0') as char);
        }
        // dbgln!(&s2, &s1, &s0);
        res.push(s1.clone());
        res.push(s0.clone());
    }

    res.sort();
    for s in res {
        puts!("{}", s.iter().collect::<String>());
    }
}

fn solve(n: usize, l: usize) {
    setup_out!(put, puts);

    for p in 0..3 {
        for m in 0..n {
            let mut x = m;
            let mut ds = vec![];
            for _ in 0..l - 1 {
                ds.push((x % 3 + p + 1) % 3);
                x /= 3;
            }
            ds.push(p);
            ds.reverse();
            for c in ds {
                put!("{}", c);
            }
            puts!();
        }
    }
}

fn main() {
    let (n, l) = readln!(usize, usize);
    // solve_dfs(n, l);
    solve(n, l);
}
