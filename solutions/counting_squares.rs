#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch counting_squares | diff counting_squares.out -
// $ cargo run --bin counting_squares

///
/// 10/30/2022
///
/// 9:44-10:23 AC
///
/// https://atcoder.jp/contests/abc275/editorial/5137
///

fn solve() -> i64 {
    let s = readlns!([char]; 9);
    let mut ps = vec![];
    for i in 0..9 {
        for j in 0..9 {
            if s[i][j] == '#' {
                ps.push(Point::from((i as isize, j as isize)));
            }
        }
    }

    let ok = |p: Point<isize>| {
        if !(0..9).contains(&p.x) || !(0..9).contains(&p.y) {
            return false;
        }
        s[p.x as usize][p.y as usize] == '#'
    };

    let mut res = 0;
    for j in 0..ps.len() {
        for i in 0..j {
            let (p0, p1) = (ps[i], ps[j]);
            let v01 = p1 - p0;
            let p2 = p1 + Point::from((-v01.y, v01.x));
            let v12 = p2 - p1;
            let p3 = p2 + Point::from((-v12.y, v12.x));
            let ps = vec![p0, p1, p2, p3];
            if ok(p2) && ok(p3) && p0 == *ps.iter().min().unwrap() {
                // dbgln!(p0, p1, p2, p3);
                res += 1;
            }
        }
    }

    res
}

fn main() {
    setup_out!(put, puts);

    let res = solve();
    puts!("{}", res);
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
use cplib::vec;
pub use geometry::{Circle, Point};

// endregion: geometry

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
