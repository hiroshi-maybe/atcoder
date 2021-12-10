#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch reversible_cards | diff reversible_cards.out -
// $ cargo run --bin reversible_cards

///
/// 12/8/2021
///
/// 22:35-22:49 pause
///
/// 12/9/2021
///
/// 10:10-10:43, 20:45-22:06 give up
/// 22:39 read editorial and got AC
/// 23:30 Add solution with union find tree
///
/// https://atcoder.jp/contests/arc111/editorial/519
/// https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.mru122hzg6o7
///

// region: union_find

#[rustfmt::skip]
#[allow(dead_code)]
mod uf {
	pub struct UnionFind {
		pub group_count: usize,
		par: Vec<usize>, sizes: Vec<usize>,
	}
	impl UnionFind {
		pub fn new(n: usize) -> UnionFind {
			let par = (0..n).map(|i| i).collect::<Vec<_>>();
			UnionFind { group_count: n, par, sizes: vec![1; n], }
		}
		pub fn find(&mut self, x: usize) -> usize {
			if self.par[x] == x { x } else {
				self.par[x] = self.find(self.par[x]);
				self.par[x]
			}
		}
		pub fn same_set(&mut self, x: usize, y: usize) -> bool { self.find(x) == self.find(y) }
		pub fn size(&mut self, x: usize) -> usize {
			let x = self.find(x);
			self.sizes[x]
		}
		pub fn merge(&mut self, x: usize, y: usize) -> usize {
			let (mut p, mut c) = (self.find(x), self.find(y));
			if p == c { return p; }
			if self.sizes[p] < self.sizes[c] { std::mem::swap(&mut p, &mut c); }
			self.group_count -= 1;
			self.sizes[p] += self.sizes[c];
			self.par[c] = p;
			p
		}
		pub fn roots(&mut self) -> Vec<usize> {
			(0..self.par.len()).filter(|&u| self.find(u) == u).collect::<Vec<_>>()
		}
	}
}
pub use uf::UnionFind;

// endregion: union_find

fn solve_uf(_n: usize, ab: &Vec<(usize, usize)>) -> usize {
    let maxv = 400_000;
    let mut uf = UnionFind::new(maxv);
    let mut extra_e = vec![];
    for &(u, v) in ab {
        if uf.same_set(u, v) {
            extra_e.push(u);
        } else {
            uf.merge(u, v);
        }
    }

    let mut cnte = vec![0; maxv];
    for root in extra_e.iter().map(|&u| uf.find(u)) {
        cnte[root] += 1;
    }
    let mut res = 0;
    for u in uf.roots() {
        let v = uf.size(u);
        res += if cnte[u] == 0 { v - 1 } else { v };
    }

    res
}

fn dfs(
    u: usize,
    g: &Vec<Vec<(usize, usize)>>,
    viz: &mut Vec<bool>,
    eviz: &mut Vec<bool>,
    cntv: &mut usize,
    cnte: &mut usize,
) {
    if viz[u] {
        return;
    }
    viz[u] = true;
    *cntv += 1;
    for &(v, eid) in &g[u] {
        if !eviz[eid] {
            eviz[eid] = true;
            *cnte += 1;
        }
        dfs(v, g, viz, eviz, cntv, cnte);
    }
}

#[allow(dead_code)]
fn solve_dfs(n: usize, ab: &Vec<(usize, usize)>) -> usize {
    let maxv = 400_000;
    let mut g = vec![vec![]; maxv];
    for (i, &(u, v)) in ab.iter().enumerate() {
        g[u].push((v, i));
        g[v].push((u, i));
    }

    let mut viz = vec![false; maxv];
    let mut eviz = vec![false; n];
    let mut res = 0;
    for i in 0..maxv {
        let mut cntv = 0;
        let mut cnte = 0;
        if !viz[i] {
            dfs(i, &g, &mut viz, &mut eviz, &mut cntv, &mut cnte);
            let d = if cnte == cntv - 1 { cntv - 1 } else { cntv };
            if d > 0 {
                //dbgln!(i, d, cntv, cnte);
            }
            res += d;
        }
    }
    res
}

#[allow(dead_code)]
fn solve_wa(n: usize, ab: &Vec<(usize, usize)>) -> usize {
    let maxc = 400_000;
    let mut c2n = vec![vec![]; maxc];

    for (i, &(a, b)) in ab.iter().enumerate() {
        c2n[a].push(i);
        c2n[b].push(i);
    }

    let mut viz = vec![false; n];
    let mut res = 0;
    for c in (0..maxc).filter(|&c| !c2n[c].is_empty()) {
        let mut visited = None;
        let mut fresh = None;
        for &i in c2n[c].iter().filter(|&&i| !viz[i]) {
            let (mut a, mut maybe_non_c) = ab[i];
            if maybe_non_c == c {
                std::mem::swap(&mut a, &mut maybe_non_c);
            }
            if maybe_non_c <= c {
                visited = Some(i);
            } else {
                fresh = Some(i);
            }
        }
        let m = match (visited, fresh) {
            (Some(i), _) => Some(i),
            (None, Some(i)) => Some(i),
            _ => None,
        };
        if let Some(i) = m {
            res += 1;
            viz[i] = true;
            dbgln!(c + 1, i);
        }
    }
    res
}

fn main() {
    setup_out!(put, puts);

    let n = readln!(usize);
    let ab = readlns!(usize1, usize1; n);
    let res = solve_uf(n, &ab);
    puts!("{}", res);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_random() {
        use rand::prelude::*;
        loop {
            let mut rng = thread_rng();
            let n = 5;
            let ab = (0..n)
                .map(|_| (rng.gen_range(0, 5), rng.gen_range(0, 5)))
                .collect_vec();

            let mut exp = 0;
            for mask in 0..1 << n {
                let mut viz = vec![false; 6];
                for i in 0..n {
                    viz[if (mask >> i) & 1 == 1 {
                        ab[i].0
                    } else {
                        ab[i].1
                    }] = true;
                }
                exp.setmax((0..5).filter(|&c| viz[c]).count());
            }

            let act = solve_uf(n, &ab);
            if act != exp {
                dbgln!(act, exp, ab);
            }
            assert_eq!(act, exp);
        }
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
