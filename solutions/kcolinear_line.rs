#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch kcolinear_line | diff kcolinear_line.out -
// $ cargo run --bin kcolinear_line

///
/// 4/17/2022
///
/// 14:54-16:09 WA
/// 16:28 give up
///
/// 17:18 read editorial and got AC
///
/// https://atcoder.jp/contests/abc248/editorial/3792
///

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
}
pub use geometry::Point;

// endregion: geometry

fn solve() -> Option<usize> {
    let (n, k) = readln!(usize, usize);
    let xys = readlns!(i64, i64; n).iter().map(|&(x,y)| Point::new(x,y)).collect_vec();

    if k == 1 {
        return None;
    }

    let mut viz = vvec!(false; n; n);
    let mut res = 0;
    for i in 0..n {
        let p0 = xys[i];
        for j in 0..i {
            if viz[i][j] {
                continue;
            }
            let mut ps = vec![i, j];

            let p1=xys[j];
            for k in (0..n).filter(|&k| k != i && k != j) {
                let p2=xys[k];
                if p0.det_origin(p1,p2) == 0 {
                    ps.push(k);
                }
            }
            if ps.len() >= k {
                // dbgln!(i, j, ps);
                res += 1;
            }
            for ii in 0..ps.len() {
                for jj in 0..ii {
                    let i = ps[ii];
                    let j = ps[jj];
                    viz[i][j] = true;
                    viz[j][i] = true;
                }
            }
        }
    }
    Some(res)
}

fn f(x1: i64, y1: i64, x2: i64, y2: i64) -> (i64, i64, i64, i64) {
    let mut dy = y2 - y1;
    if dy == 0 {
        return (0, y1, 0, 0);
    }
    let mut dx = x1 - x2;
    let sign = if dy < 0 && dx > 0 || dy > 0 && dx < 0 {
        -1
    } else {
        1
    };
    dx = dx.abs();
    dy = dy.abs();

    let g = gcd(dy.abs(), dx.abs());
    dy /= g;
    dx /= g;
    // dbgln!(
    //     x1,
    //     y1,
    //     x2,
    //     y2,
    //     dx,
    //     dy,
    //     sign,
    //     dx * x1 + sign * dy * y1,
    //     dx * x2 + sign * dy * y2
    // );
    assert_eq!(dx * x1 + sign * dy * y1, dx * x2 + sign * dy * y2);
    (dx, dy, dx * x1 + sign * dy * y1, sign)
}

#[allow(dead_code)]
fn solve_wa() -> Option<usize> {
    let (n, k) = readln!(usize, usize);
    let xys = readlns!(i64,i64; n);

    if k == 1 {
        return None;
    }

    let mut ps = BTreeMap::<i64, Vec<i64>>::new();
    for (x, y) in xys {
        let e = ps.entry(x).or_insert(vec![]);
        e.push(y);
    }

    let mut cnts = vec![HashSet::<(i64, i64)>::new(); 10usize.pow(6)];
    let mut ids = HashMap::<(i64, i64, i64, i64), usize>::new();
    let mut res = 0;
    let mut past = vec![];
    for &x1 in ps.keys() {
        let ys = ps[&x1].clone();
        // dbgln!(x1);

        let ycnt = ys.len();
        if ycnt >= k {
            res += 1;
        }

        for &y1 in &ys {
            // dbgln!(y1);
            for &(x2, y2) in &past {
                let (a, b, c, sign) = f(x1, y1, x2, y2);
                // dbgln!(x1, y1, x2, y2, a, b, c);
                let cnt = ids.len();
                let id = ids.entry((a, b, c, sign)).or_insert(cnt);
                cnts[*id].insert((x1, y1));
                cnts[*id].insert((x2, y2));
            }
        }

        for &y1 in &ys {
            past.push((x1, y1));
        }
    }

    // for ps in cnts.iter().filter(|&s| s.len() >= k) {
    //     dbgln!(ps);
    // }

    Some(res + cnts.iter().filter(|&s| s.len() >= k).count())
}

fn main() {
    setup_out!(put, puts);

    let res = solve();
    if let Some(res) = res {
        puts!("{}", res);
    } else {
        puts!("Infinity");
    }
}

// region: gcd

#[rustfmt::skip]
#[allow(dead_code)]
mod gcd {
	use std::cmp::PartialEq;
	use std::ops::Rem;
	#[inline(always)] pub fn gcd<T: Gcd>(x: T, y: T) -> T { x.gcd(&y) }
	#[inline(always)] pub fn lcm<T: Gcd>(x: T, y: T) -> T { x.lcm(&y) }
	pub trait Gcd: Copy + Rem<Output = Self> + PartialEq {
		fn gcd(&self, other: &Self) -> Self;
		fn lcm(&self, other: &Self) -> Self;
	}
	macro_rules! impl_gcd {
		($integer:ty) => {
			impl Gcd for $integer {
				#[inline] fn gcd(&self, other: &Self) -> Self {
					let mut m = *self; let mut n = *other;
					while m != 0 { let temp = m; m = n % temp; n = temp; }
					n
				}
				#[inline] fn lcm(&self, other: &Self) -> Self {
					self / gcd(*self, *other) * other
				}
			}
		};
	}
	impl_gcd!(i32);impl_gcd!(i64);impl_gcd!(usize);
}
pub use gcd::*;

// endregion: gcd

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
