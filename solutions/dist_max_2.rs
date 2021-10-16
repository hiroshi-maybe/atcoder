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

// $ rs-cp-batch dist_max_2 | diff dist_max_2.out -
// $ cargo run --bin dist_max_2

///
/// 8/21/2021
///
/// 13:21-13:51 pause
///
/// 9/24/2021
///
/// 8:56-10:32 give up
///
/// 10/15/2021
///
/// 21:00-22:00 pause
///
/// 10/16/2021
///
/// 12:00-14:00 got AC with max { min(▵x, ▵y) } <= a binary search
/// 14:15 AC with max { min(▵x, ▵y) } >= a binary search
/// 14:22 drop right interval check because of symmetry property
/// 14:30 AC without Segment tree
///
/// https://atcoder.jp/contests/abc215/editorial/2492
/// https://youtu.be/NxuL8oOwIvM?t=4327
/// https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.h3rp8cnwo954
/// https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.t6ubfe7vazrp
///
/// https://blog.hamayanhamayan.com/entry/2021/08/21/225652
///

pub(crate) fn ceil_pow2(n: u32) -> u32 {
    32 - n.saturating_sub(1).leading_zeros()
}

pub trait BoundedBelow {
    fn min_value() -> Self;
}
impl BoundedBelow for i64 {
    #[inline]
    fn min_value() -> Self {
        Self::min_value()
    }
}
pub trait BoundedAbove {
    fn max_value() -> Self;
}
impl BoundedAbove for i64 {
    #[inline]
    fn max_value() -> Self {
        Self::max_value()
    }
}

pub trait Monoid {
    type S: Clone;
    fn identity() -> Self::S;
    fn binary_operation(a: &Self::S, b: &Self::S) -> Self::S;
}

use std::convert::Infallible;
use std::marker::PhantomData;

pub struct Max<S>(Infallible, PhantomData<fn() -> S>);
impl<S> Monoid for Max<S>
where
    S: Copy + Ord + BoundedBelow,
{
    type S = S;
    fn identity() -> Self::S {
        S::min_value()
    }
    fn binary_operation(a: &Self::S, b: &Self::S) -> Self::S {
        max(*a, *b)
    }
}
pub struct Min<S>(Infallible, PhantomData<fn() -> S>);
impl<S> Monoid for Min<S>
where
    S: Copy + Ord + BoundedAbove,
{
    type S = S;
    fn identity() -> Self::S {
        S::max_value()
    }
    fn binary_operation(a: &Self::S, b: &Self::S) -> Self::S {
        min(*a, *b)
    }
}
impl<M: Monoid> Default for Segtree<M> {
    fn default() -> Self {
        Segtree::new(0)
    }
}
impl<M: Monoid> Segtree<M> {
    pub fn new(n: usize) -> Segtree<M> {
        vec![M::identity(); n].into()
    }
}
impl<M: Monoid> From<Vec<M::S>> for Segtree<M> {
    fn from(v: Vec<M::S>) -> Self {
        let n = v.len();
        let log = ceil_pow2(n as u32) as usize;
        let size = 1 << log;
        let mut d = vec![M::identity(); 2 * size];
        d[size..(size + n)].clone_from_slice(&v);
        let mut ret = Segtree { n, size, log, d };
        for i in (1..size).rev() {
            ret.update(i);
        }
        ret
    }
}
impl<M: Monoid> Segtree<M> {
    pub fn set(&mut self, mut p: usize, x: M::S) {
        assert!(p < self.n);
        p += self.size;
        self.d[p] = x;
        for i in 1..=self.log {
            self.update(p >> i);
        }
    }

    pub fn get(&self, p: usize) -> M::S {
        assert!(p < self.n);
        self.d[p + self.size].clone()
    }

    pub fn prod(&self, mut l: usize, mut r: usize) -> M::S {
        assert!(l <= r && r <= self.n);
        let mut sml = M::identity();
        let mut smr = M::identity();
        l += self.size;
        r += self.size;

        while l < r {
            if l & 1 != 0 {
                sml = M::binary_operation(&sml, &self.d[l]);
                l += 1;
            }
            if r & 1 != 0 {
                r -= 1;
                smr = M::binary_operation(&self.d[r], &smr);
            }
            l >>= 1;
            r >>= 1;
        }

        M::binary_operation(&sml, &smr)
    }

    pub fn all_prod(&self) -> M::S {
        self.d[1].clone()
    }

    pub fn max_right<F>(&self, mut l: usize, f: F) -> usize
    where
        F: Fn(&M::S) -> bool,
    {
        assert!(l <= self.n);
        assert!(f(&M::identity()));
        if l == self.n {
            return self.n;
        }
        l += self.size;
        let mut sm = M::identity();
        while {
            // do
            while l % 2 == 0 {
                l >>= 1;
            }
            if !f(&M::binary_operation(&sm, &self.d[l])) {
                while l < self.size {
                    l *= 2;
                    let res = M::binary_operation(&sm, &self.d[l]);
                    if f(&res) {
                        sm = res;
                        l += 1;
                    }
                }
                return l - self.size;
            }
            sm = M::binary_operation(&sm, &self.d[l]);
            l += 1;
            // while
            {
                let l = l as isize;
                (l & -l) != l
            }
        } {}
        self.n
    }

    pub fn min_left<F>(&self, mut r: usize, f: F) -> usize
    where
        F: Fn(&M::S) -> bool,
    {
        assert!(r <= self.n);
        assert!(f(&M::identity()));
        if r == 0 {
            return 0;
        }
        r += self.size;
        let mut sm = M::identity();
        while {
            // do
            r -= 1;
            while r > 1 && r % 2 == 1 {
                r >>= 1;
            }
            if !f(&M::binary_operation(&self.d[r], &sm)) {
                while r < self.size {
                    r = 2 * r + 1;
                    let res = M::binary_operation(&self.d[r], &sm);
                    if f(&res) {
                        sm = res;
                        r -= 1;
                    }
                }
                return r + 1 - self.size;
            }
            sm = M::binary_operation(&self.d[r], &sm);
            // while
            {
                let r = r as isize;
                (r & -r) != r
            }
        } {}
        0
    }

    fn update(&mut self, k: usize) {
        self.d[k] = M::binary_operation(&self.d[2 * k], &self.d[2 * k + 1]);
    }
}

pub struct Segtree<M>
where
    M: Monoid,
{
    // variable name is _n in original library
    n: usize,
    size: usize,
    log: usize,
    d: Vec<M::S>,
}

#[allow(dead_code)]
fn solve_v0(mut ps: Vec<(i64, i64)>) -> i64 {
    ps.sort();
    let ys: Vec<_> = ps.iter().map(|(_, y)| *y).collect();
    let rmaxq: Segtree<Max<_>> = ys.clone().into();
    let rminq: Segtree<Min<_>> = ys.into();
    let n = ps.len();
    //dbgln!(ps);

    let is_ok = |m: i64| {
        let mut l = 0;
        let mut r = 0;
        for i in 0..n {
            let has_larger = |l: usize, r: usize| {
                let maxy = rmaxq.prod(l, r);
                let miny = rminq.prod(l, r);
                //dbgln!(i, maxy, miny, ps[i].1);
                if maxy == i64::min_value() {
                    return false;
                }
                (maxy != i64::min_value() && (maxy - ps[i].1) > m) || (ps[i].1 - miny) > m
            };

            while l < i && (ps[i].0 - ps[l].0) > m {
                l += 1;
            }
            while r < n && (ps[r].0 - ps[i].0) <= m {
                r += 1;
            }

            if has_larger(0, l) || has_larger(r, n) {
                return false;
            }
        }
        true
    };

    let mut good = 10_000_000_000i64;
    let mut bad = -1;
    while (good - bad).abs() > 1 {
        let m = (good + bad) / 2;

        let ok = is_ok(m);
        //dbgln!(m, ok);
        if ok {
            good = m;
        } else {
            bad = m;
        }
    }
    //dbgln!(good);

    good
}

#[allow(dead_code)]
fn solve_v1(mut ps: Vec<(i64, i64)>) -> i64 {
    ps.sort();
    let ys: Vec<_> = ps.iter().map(|(_, y)| *y).collect();
    let rmaxq: Segtree<Max<_>> = ys.clone().into();
    let rminq: Segtree<Min<_>> = ys.into();
    let n = ps.len();
    //dbgln!(ps);

    let is_ok = |m: i64| {
        let mut l = 0;
        for i in 0..n {
            let has_larger = |l: usize, r: usize| {
                let maxy = rmaxq.prod(l, r);
                let miny = rminq.prod(l, r);
                //dbgln!(i, maxy, miny, ps[i].1);
                if maxy == i64::min_value() {
                    return false;
                }
                (maxy != i64::min_value() && (maxy - ps[i].1) >= m) || (ps[i].1 - miny) >= m
            };

            while l < i && (ps[i].0 - ps[l].0) >= m {
                l += 1;
            }

            if has_larger(0, l) {
                return true;
            }
        }
        false
    };

    let mut good = -1;
    let mut bad = 10_000_000_000i64;
    while (good - bad).abs() > 1 {
        let m = (good + bad) / 2;

        let ok = is_ok(m);
        //dbgln!(m, ok);
        if ok {
            good = m;
        } else {
            bad = m;
        }
    }
    //dbgln!(good);

    good
}

#[allow(dead_code)]
fn solve_v2(mut ps: Vec<(i64, i64)>) -> i64 {
    const INF: i64 = 10_000_000_000;
    ps.sort();
    let n = ps.len();

    let is_ok = |m: i64| {
        let mut l = 0;
        let mut maxy = -INF;
        let mut miny = INF;
        for i in 0..n {
            while l < i && (ps[i].0 - ps[l].0) >= m {
                maxy = maxy.max(ps[l].1);
                miny = miny.min(ps[l].1);
                l += 1;
            }

            if (maxy - ps[i].1) >= m || (ps[i].1 - miny) >= m {
                return true;
            }
        }
        false
    };

    let mut good = -1;
    let mut bad = 10_000_000_000i64;
    while (good - bad).abs() > 1 {
        let m = (good + bad) / 2;

        let ok = is_ok(m);
        //dbgln!(m, ok);
        if ok {
            good = m;
        } else {
            bad = m;
        }
    }
    //dbgln!(good);

    good
}

fn main() {
    setup_out!(put, puts);

    let n = readln!(usize);
    let xy = readlns!(i64, i64; n);

    //let yx = xy.clone();
    let res = solve_v2(xy);
    //let yx: Vec<_> = yx.iter().map(|(x, y)| (*y, *x)).collect();
    //res = max(res, solve(yx));

    puts!("{}", res);
}
