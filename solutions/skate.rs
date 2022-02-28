#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch skate | diff skate.out -
// $ cargo run --bin skate

///
/// 2/26/2022
///
/// 10:57-12:35 WA
/// 13:10 AC after looking at https://atcoder.jp/contests/abc241/submissions/29678247
///
/// https://atcoder.jp/contests/abc241/editorial/3451
///

fn solve() -> isize {
    let (_h, _w, n) = readln!(i64, i64, usize);
    let (sx, sy) = readln!(i64, i64);
    let (gx, gy) = readln!(i64, i64);
    let xy = readlns!(i64, i64; n);

    let mut rows = BTreeSet::new();
    let mut cols = BTreeSet::new();
    for (x, y) in xy {
        rows.insert((x, y));
        cols.insert((y, x));
    }
    let mut dist = HashMap::new();
    let mut q = VecDeque::new();
    let inf = 1_000_000;

    dist.insert((sx, sy), 0);
    q.push_back((sx, sy));

    while let Some((x, y)) = q.pop_front() {
        let d = dist[&(x, y)];
        // dbgln!(x, y, d);
        if let Some(p) = rows.range((x, y)..).next() {
            let p = (p.0, p.1 - 1);
            if p.0 == x && dist.entry(p).or_insert(inf).setmin(d + 1) {
                q.push_back(p);
            }
        }
        if let Some(p) = rows.range(..(x, y)).next_back() {
            let p = (p.0, p.1 + 1);
            if p.0 == x && dist.entry(p).or_insert(inf).setmin(d + 1) {
                q.push_back(p);
            }
        }
        if let Some(p) = cols.range((y, x)..).next() {
            let p = (p.1 - 1, p.0);
            if p.1 == y && dist.entry(p).or_insert(inf).setmin(d + 1) {
                q.push_back(p);
            }
        }
        if let Some(p) = cols.range(..(y, x)).next_back() {
            let p = (p.1 + 1, p.0);
            if p.1 == y && dist.entry(p).or_insert(inf).setmin(d + 1) {
                q.push_back(p);
            }
        }
    }

    *dist.entry((gx, gy)).or_insert(-1)
}

#[allow(dead_code)]
fn solve_wa() -> isize {
    let (_h, _w, n) = readln!(i64, i64, usize);
    let (sx, sy) = readln!(i64, i64);
    let (sx, sy) = (sx - 1, sy - 1);
    let (gx, gy) = readln!(i64, i64);
    let (gx, gy) = (gx - 1, gy - 1);
    let xy = readlns!(i64, i64; n);
    let moves = vec![(1, 0), (0, 1), (-1, 0), (0, -1)];

    let mut hs = HashMap::new();
    let mut vs = HashMap::new();
    let mut vmap = HashMap::new();
    let mut vmap_inv: Vec<(i64, i64)> = vec![];
    let mut cnt = 0usize;
    for (x, y) in xy {
        let (x, y) = (x - 1, y - 1);
        let e = hs.entry(x).or_insert(vec![]);
        e.push(y);
        let e = vs.entry(y).or_insert(vec![]);
        e.push(x);
        for &(di, dj) in &moves {
            let (x, y) = (x + di, y + dj);
            if !vmap.contains_key(&(x, y)) {
                vmap.insert((x, y), cnt);
                vmap_inv.push((x, y));
                cnt += 1;
            }
        }
    }
    if !vmap.contains_key(&(sx, sy)) {
        vmap.insert((sx, sy), cnt);
        vmap_inv.push((sx, sy));
        cnt += 1;
    }
    if !vmap.contains_key(&(gx, gy)) {
        vmap.insert((gx, gy), cnt);
        vmap_inv.push((gx, gy));
        cnt += 1;
    }

    let get_v = |x, y| vmap.get(&(x, y)).unwrap();

    // let mut g = vec![vec![]; cnt];
    // for (&x, vs) in hs.iter_mut() {
    //     vs.sort_unstable();
    //     let mut s_found = false;
    //     for vs in vs.windows(2) {
    //         let (ly, ry) = (vs[0].0 + 1, vs[1].0 - 1);
    //         let l = get_v(x, ly);
    //         let r = get_v(x, ry);
    //         if l != r {
    //             g[*l].push(r);
    //             g[*r].push(l);

    //             if x == sx && (ly..=ry).contains(&sy) {
    //                 let s = get_v(sx, sy);
    //                 if s != l {
    //                     g[*s].push(l);
    //                 }
    //                 if s != r {
    //                     g[*s].push(r);
    //                 }
    //                 s_found = true;
    //             }
    //         }
    //     }
    //     if x == sx && !s_found {
    //         let last_y = vs.last().unwrap().0 + 1;
    //         let u = get_v(x, last_y);
    //         let s = get_v(sx, sy);
    //         if u != s {
    //             g[*s].push(u);
    //         }
    //     }
    // }
    // for (&y, hs) in vs.iter_mut() {
    //     hs.sort_unstable();
    //     let mut s_found = false;
    //     for hs in hs.windows(2) {
    //         let (lx, rx) = (hs[0].0 + 1, hs[1].0 - 1);
    //         let d = get_v(lx, y);
    //         let u = get_v(rx, y);
    //         if d != u {
    //             g[*d].push(u);
    //             g[*u].push(d);

    //             if y == sy && (lx..=rx).contains(&sx) {
    //                 let s = get_v(sx, sy);
    //                 if s != d {
    //                     g[*s].push(d);
    //                 }
    //                 if s != u {
    //                     g[*s].push(u);
    //                 }
    //                 s_found = true;
    //             }
    //         }
    //     }
    //     if y == sy && !s_found {
    //         let last_x = hs.last().unwrap().0 + 1;
    //         let u = get_v(last_x, y);
    //         let s = get_v(sx, sy);
    //         if u != s {
    //             g[*s].push(u);
    //         }
    //     }
    // }

    let inf = 1_000_000;
    let mut dist = vec![inf; cnt];
    let s = *vmap.get(&(sx, sy)).unwrap();
    let mut q = VecDeque::new();
    q.push_back(s);
    dist[s] = 0;

    // dbgln!(vmap);

    let find_neighbors = |u: usize| -> Vec<usize> {
        let (x, y) = vmap_inv[u];

        let mut res = vec![];
        // dbgln!(x, y);
        if let Some(ys) = hs.get(&x) {
            let i = ys.lower_bound(&y);

            if i < ys.len() {
                let y = ys[i];
                res.push(*get_v(x, y - 1));
            }
            if i >= 1 {
                let y = ys[i - 1];
                res.push(*get_v(x, y + 1));
            }
        }

        if let Some(xs) = vs.get(&y) {
            let i = xs.lower_bound(&x);

            if i < xs.len() {
                let x = xs[i];
                res.push(*get_v(x - 1, y));
            }
            if i >= 1 {
                let x = xs[i - 1];
                res.push(*get_v(x + 1, y));
            }
        }

        res
    };

    while let Some(u) = q.pop_front() {
        let d = dist[u];
        let ns = find_neighbors(u);

        for v in ns {
            let dd = dist[v];
            if dd > d + 1 {
                q.push_back(v);
                dist[v] = d + 1;
            }
        }
    }

    let g = *vmap.get(&(gx, gy)).unwrap();
    if dist[g] == inf {
        -1
    } else {
        dist[g]
    }
}

fn main() {
    setup_out!(put, puts);

    let res = solve();
    puts!("{}", res);
}

// region: partition
#[rustfmt::skip]
#[allow(dead_code)]
mod partition {
	use std::cmp::Ordering;
	pub trait PartitionSlice {
		type Item;
		/// Find the partition point for which left segment satisifies the predicate
		/// [pred(item)] = [true, true, true, false, false]
		///                                   ^ res
		fn _partition_point<P>(&self, pred: P) -> usize where P: FnMut(&Self::Item) -> bool;

		/// Find the smallest index which satisfies key <= a[i]
		fn lower_bound(&self, key: &Self::Item) -> usize where Self::Item: Ord {
			self._partition_point(|item| item < key)
		}

		/// Find the smallest index which satisfies key < a[i]
		fn upper_bound(&self, key: &Self::Item) -> usize where Self::Item: Ord {
			self._partition_point(|item| item <= key)
		}
	}

	impl<T> PartitionSlice for [T] {
		type Item = T;
		fn _partition_point<P>(&self, mut pred: P) -> usize where P: FnMut(&T) -> bool {
			self.binary_search_by(|x| { if pred(x) { Ordering::Less } else { Ordering::Greater }})
				.unwrap_or_else(std::convert::identity)
		}
	}
}
pub use partition::PartitionSlice;
// endregion: partition

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
		fn setmin(&mut self, other: Self) -> bool;
		fn setmax(&mut self, other: Self) -> bool;
	}
	macro_rules! _set { ($self:ident, $cmp:tt, $other:ident) => {{
			let update = $other $cmp *$self;
			if update { *$self = $other; }
			update
	}}; }
	impl<T> SetMinMax for T where T: PartialOrd {
		fn setmin(&mut self, other: T) -> bool { _set!(self, <, other) }
		fn setmax(&mut self, other: T) -> bool { _set!(self, >, other) }
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
