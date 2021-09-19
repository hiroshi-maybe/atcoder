#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;
use std::io::{BufWriter, Write};

macro_rules! with_dollar_sign { ($($body:tt)*) => {
	macro_rules! __with_dollar_sign { $($body)* }
	__with_dollar_sign!($);
}}
macro_rules! setup_out {
    ($fn:ident,$fn_s:ident) => {
        let out = std::io::stdout();
        let mut out = BufWriter::new(out.lock());
        with_dollar_sign! { ($d:tt) => {
            macro_rules! $fn { ($d($format:tt)*) => { let _ = write!(out,$d($format)*); } }
            macro_rules! $fn_s { ($d($format:tt)*) => { let _ = writeln!(out,$d($format)*); } }
        }}
    };
}
macro_rules! _read {
	($it:ident; [char]) => { _read!($it; String).chars().collect::<Vec<_>>() };
	($it:ident; [u8]) => { Vec::from(_read!($it; String).into_bytes()) };
	($it:ident; usize1) => { it.next().unwrap_or_else(|| panic!("input mismatch")).parse::<usize>().unwrap_or_else(|e| panic!("{}", e)) - 1 };
	($it:ident; [usize1]) => { $it.map(|s| s.parse::<usize>().unwrap_or_else(|e| panic!("{}", e)) - 1).collect::<Vec<_>>() };
	($it:ident; [$t:ty]) => { $it.map(|s| s.parse::<$t>().unwrap_or_else(|e| panic!("{}", e))).collect::<Vec<_>>() };
	($it:ident; $t:ty) => { $it.next().unwrap_or_else(|| panic!("input mismatch")).parse::<$t>().unwrap_or_else(|e| panic!("{}", e)) };
	($it:ident; $($t:tt),+) => { ($(_read!($it; $t)),*) };
}
macro_rules! readlns {
	($($t:tt),*; $n:expr) => {{
		let stdin = ::std::io::stdin();
		let ret = ::std::io::BufRead::lines(stdin.lock()).take($n).map(|line| {
			let line = line.unwrap();
			let mut it = line.split_whitespace();
			_read!(it; $($t),*)
		}).collect::<Vec<_>>();
		ret
	}};
}
macro_rules! readln {
	($($t:tt),*) => {{
		let line = readln();
		#[allow(unused_mut)]
		let mut it = line.split_whitespace();
		_read!(it; $($t),*)
	}};
}

// $ rs-cp-batch neolexicographic_ordering | diff neolexicographic_ordering.out -
// $ cargo run --bin neolexicographic_ordering

///
/// 9/18/2021
///
/// 5:25-5:42 WA
/// 6:00 give up
///
/// 16:30-18:00 figured out misunderstanding of problem statement and got AC
///

fn main() {
    setup_out!(put, puts);

    let x = readln!([char]);
    let n = readln!(usize);
    let mut a = readlns!([char]; n);

    /*
    // wrong answer
    let mut b = a
        .iter()
        .map(|chars| {
            let y = chars.iter().map(|c| x[(*c as u8 - b'a') as usize]);
            (y.collect::<Vec<_>>(), chars)
        })
        .collect::<Vec<_>>();
    b.sort(); */

    let mut ord = vec![0; 26];
    for (i, c) in x.iter().enumerate() {
        ord[(*c as u8 - b'a') as usize] = i;
    }

    /*
    let mut b = a
        .iter()
        .map(|chars| {
            let y = chars.iter().map(|c| ord[(*c as u8 - b'a') as usize]);
            (y.collect::<Vec<_>>(), chars)
        })
        .collect::<Vec<_>>();
    b.sort(); */

    a.sort_by_cached_key(|cs| {
        cs.iter()
            .map(|c| ord[(*c as u8 - b'a') as usize])
            .collect::<Vec<_>>()
    });

    /*for i in 0..n {
        assert!(aa[i] == *b[i].1);
    }*/
    // dbg!(&b);

    for cs in &a {
        puts!("{}", cs.iter().collect::<String>());
    }
}

pub fn readln() -> String {
    let mut line = String::new();
    ::std::io::stdin()
        .read_line(&mut line)
        .unwrap_or_else(|e| panic!("{}", e));
    line
}
