#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

#[rustfmt::skip]
#[macro_use]
#[allow(unused_mut, dead_code)]
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
    pub fn readln() -> String {
        let mut line = String::new();
        ::std::io::stdin().read_line(&mut line).unwrap_or_else(|e| panic!("{}", e));
        line
    }
    macro_rules! readlns {
        ($($t:tt),*; $n:expr) => {{ let stdin = ::std::io::stdin();
            ::std::io::BufRead::lines(stdin.lock()).take($n).map(|line| {
                let line = line.unwrap();
                let it = line.split_whitespace();
                _read!(it; $($t),*)
            }).collect::<Vec<_>>()
        }};
    }
    macro_rules! readln {
        ($($t:tt),*) => {{ let line = io::readln(); let mut it = line.split_whitespace(); _read!(it; $($t),*) }};
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
    macro_rules! _epr { ($v:expr $(,)?) => {eprint!("{} = {:?}, ", stringify!($v), $v)}; }
    macro_rules! dbgln { ($($val:expr),*) => {{ eprint!("[{}:{}] ", file!(), line!()); ($(_epr!($val)),*); eprintln!(); }}; }
}

// $ rs-cp-batch moat | diff moat.out -
// $ cargo run --bin moat

///
/// 9/18/2021
///
/// 6:14-7:07 pause
/// 10:30-11:38 AC
///
/// https://atcoder.jp/contests/abc219/editorial/2666
/// https://atcoder.jp/contests/abc219/editorial/2652
///

fn ith(mask: usize, i: usize) -> bool {
    ((mask >> i) & 1) == 1
}
fn is_on(x: usize, kind: usize, a: &Vec<Vec<usize>>) -> bool {
    let v = a[x / 4][x % 4];
    ith(v, kind)
}

const MARK: usize = 1;
const VIZ: usize = 2;
const MOVES: &'static [(i32, i32)] = &[(0, 1), (1, 0), (0, -1), (-1, 0)];

fn dfs(p: usize, is_mark: bool, a: &mut Vec<Vec<usize>>) {
    if is_on(p, VIZ, a) {
        return;
    }
    if is_on(p, MARK, &a) != is_mark {
        return;
    }

    a[p / 4][p % 4] |= 1 << VIZ;
    for (dx, dy) in MOVES {
        let i = (p / 4) as i32 + dx;
        let j = (p % 4) as i32 + dy;
        if 0 <= i && i < 4 && 0 <= j && j < 4 {
            let p = (i * 4 + j) as usize;
            if is_on(p, MARK, a) == is_mark {
                dfs(p, is_mark, a);
            }
        }
    }
}

fn ok(mask: usize, a: &Vec<Vec<usize>>) -> bool {
    let mut b = vec![vec![0usize; 4]; 4];
    for x in 0..16 {
        b[x / 4][x % 4] = a[x / 4][x % 4];
        if ith(mask, x) {
            b[x / 4][x % 4] = 1 << MARK;
        }
    }

    let mut gone = vec![false; 2];
    for i in vec![0, 3] {
        for j in 0..4 {
            dfs(i * 4 + j, false, &mut b);
            dfs(j * 4 + i, false, &mut b);
        }
    }

    for x in 0..16 {
        if is_on(x, VIZ, &b) && is_on(x, 0, &b) {
            return false;
        }
    }

    for x in 0..16 {
        if is_on(x, VIZ, &b) {
            continue;
        }

        let is_marked = is_on(x, MARK, &b);
        if !is_marked {
            return false;
        }

        if gone[is_marked as usize] {
            return false;
        } else {
            gone[is_marked as usize] = true;
            dfs(x, is_marked, &mut b);
        }
    }

    for x in 0..16 {
        if is_on(x, 0, &b) && !is_on(x, VIZ, &b) {
            return false;
        }
    }

    true
}

fn main() {
    setup_out!(put, puts);

    let a = readlns!([usize]; 4);

    let mut res = 0;
    for mask in 0..(1 << 16) {
        //dbg!(mask, ok);
        if ok(mask, &a) {
            res += 1;
            /*
            for i in 0..4 {
                for j in 0..4 {
                    let x = i * 4 + j;
                    if is_on(x, MARK, &b) {
                        assert!(is_on(x, VIZ, &b));
                    }
                }
            }*/
        }
    }

    puts!("{}", res);
}
