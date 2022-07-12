#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch circumferences | diff circumferences.out -
// $ cargo run --bin circumferences

///
/// 7/10/2022
///
/// 17:23-17:48 pause
///
/// 7/12/2022
///
/// 15:02-15:52 AC
///

fn solve() -> bool {
    let n = readln!(usize);
    let (sx, sy, dx, dy) = readln!(i64, i64, i64, i64);
    let (s, d) = (Point::from((sx, sy)), Point::from((dx, dy)));
    let ps = readlns!(i64, i64, i64; n);

    let ps = ps
        .iter()
        .map(|&(x, y, r)| Circle::new((x, y), r))
        .collect_vec();

    let s = (0..n).filter(|&i| ps[i].is_on_arc(s)).collect_vec();
    let d = (0..n).filter(|&i| ps[i].is_on_arc(d)).collect_vec();

    let mut uf = UnionFind::new(n);
    for i in 0..n {
        for j in 0..n {
            if ps[i].has_intersection(&ps[j]) {
                uf.merge(i, j);
            }
        }
    }

    for s in s {
        for &d in &d {
            if uf.same_set(s, d) {
                return true;
            }
        }
    }
    false
}

fn main() {
    setup_out!(put, puts);

    let res = solve();
    puts!("{}", if res { "Yes" } else { "No" });
}

// region: geometry

#[rustfmt::skip]
#[allow(dead_code)]
pub mod geometry {
	use std::ops::*;

	#[derive(Copy, Clone, Debug, Default, Hash, PartialEq, Eq, PartialOrd, Ord)]
	pub struct Point<T> { pub x: T, pub y: T }
	impl<T> Point<T> {
		pub fn new(x: T, y: T) -> Self { Point { x, y } }
	}
	impl<T: Mul<Output = T> + Sub<Output = T> + Copy> Point<T> {
		pub fn det<U: Into<Point<T>>>(&self, other: U) -> T {
			let other = other.into();
			self.x * other.y - self.y * other.x
		}
		pub fn det_origin<U1: Into<Point<T>>, U2: Into<Point<T>>>(self, other1: U1, other2: U2) -> T {
			let (u, v) = (other1.into() - self, other2.into() - self);
			u.det(v)
		}
	}
	impl<T> From<(T, T)> for Point<T> {
		fn from(t: (T, T)) -> Point<T> { Point::<T>::new(t.0, t.1) }
	}
	impl<T: Mul<Output = T> + Add<Output = T> + PartialOrd + Copy> Point<T> {
		pub fn dist(&self) -> T {
			self.x * self.x + self.y * self.y
		}
	}
	impl<U: Into<Point<T>>, T: Add<Output = T>> Add<U> for Point<T> {
		type Output = Self;
		fn add(self, other: U) -> Self {
			let other = other.into();
			Self::new(self.x + other.x, self.y + other.y)
		}
	}
	impl<U: Into<Point<T>>, T: Sub<Output = T>> Sub<U> for Point<T> {
		type Output = Self;
		fn sub(self, other: U) -> Self {
			let other = other.into();
			Self::new(self.x - other.x, self.y - other.y)
		}
	}
	impl<U: Into<Point<T>>, T: Add<Output = T> + Copy> AddAssign<U> for Point<T> {
		fn add_assign(&mut self, other: U) { *self = *self + other; }
	}
	impl<U: Into<Point<T>>, T: Sub<Output = T> + Copy> SubAssign<U> for Point<T> {
		fn sub_assign(&mut self, other: U) { *self = *self - other; }
	}

	pub fn deg2rad(deg: f64) -> f64 { deg * std::f64::consts::PI / 180.0 }
	impl<T: Into<f64> + Copy> Point<T> {
		pub fn rotate(&self, degree: f64) -> Point<f64> {
			let rad = deg2rad(degree);
			let (c, s) = (rad.cos(), rad.sin());
			let (x, y) = (self.x.into(), self.y.into());
			Point::<f64>::new(x * c - y * s, x * s + y * c)
		}
	}

	const EPS: f64 = 1e-6;
	impl Point<f64> {
		pub fn equal_with_eps(&self, other: &Self) -> bool {
			(self.x-other.x).abs() <= EPS && (self.y-other.y).abs() <= EPS
		}
	}

	pub struct Circle<T> { pub origin: Point<T>, pub radius: T }
	impl<T> Circle<T> {
		pub fn new<U: Into<Point<T>>>(point: U, radius: T) -> Circle<T> {
			Circle { origin: point.into(), radius }
		}
	}
	impl<T: Sub<Output = T> + Mul<Output = T> + Add<Output = T> + PartialOrd + Copy> Circle<T> {
		pub fn is_on_arc(&self, point: Point<T>) -> bool {
			(point - self.origin).dist() == self.radius * self.radius
		}
		pub fn is_inside(&self, point: Point<T>) -> bool {
			(point - self.origin).dist() <= self.radius * self.radius
		}
		pub fn has_intersection(&self, other: &Circle<T>) -> bool {
			let d = (self.origin - other.origin).dist();
			(self.radius - other.radius) * (self.radius - other.radius) <= d
			&& d <= (self.radius + other.radius) * (self.radius + other.radius)
		}
	}
}
pub use geometry::{Circle, Point};

// endregion: geometry

// region: union_find

#[rustfmt::skip]
#[allow(dead_code)]
mod uf {
	pub struct UnionFind {
		pub group_count: usize,
		par_or_size: Vec<isize>,
	}
	impl UnionFind {
		pub fn new(n: usize) -> UnionFind {
			UnionFind { group_count: n, par_or_size: vec![-1; n], }
		}
		pub fn root(&mut self, x: usize) -> usize {
			if self.par_or_size[x] < 0 as isize { x } else {
				self.par_or_size[x] = self.root(self.par_or_size[x] as usize) as isize;
				self.par_or_size[x] as usize
			}
		}
		pub fn same_set(&mut self, x: usize, y: usize) -> bool { self.root(x) == self.root(y) }
		pub fn size(&mut self, x: usize) -> usize {
			let root = self.root(x); -self.par_or_size[root] as usize
		}
		pub fn merge(&mut self, x: usize, y: usize) -> usize {
			let (mut p, mut c) = (self.root(x), self.root(y));
			if p == c { return p; }
			if -self.par_or_size[p] < -self.par_or_size[c] { std::mem::swap(&mut p, &mut c); }
			self.group_count -= 1;
			self.par_or_size[p] += self.par_or_size[c];
			self.par_or_size[c] = p as isize;
			p
		}
		pub fn roots(&mut self) -> Vec<usize> {
			(0..self.par_or_size.len()).filter(|&u| self.root(u) == u).collect::<Vec<_>>()
		}
	}
}
pub use uf::UnionFind;

// endregion: union_find

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
