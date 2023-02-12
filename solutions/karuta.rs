#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch karuta | diff karuta.out -
// $ cargo run --bin karuta

///
/// 1/29/2023
///
/// 16:47-17:00, 22:00-22:37 AC
///
/// https://atcoder.jp/contests/abc287/editorial/5645
///

#[allow(dead_code)]
fn solve() -> Vec<usize> {
    let n = readln!(usize);
    let s = readlns!([char]; n);
    let mut s = s.iter().enumerate().map(|s| (s.1, s.0)).collect_vec();

    s.sort_unstable();
    // dbgln!(s);
    let a = vec![];
    let mut x = vec![(&a, n + 1)];
    for s in s {
        x.push(s);
    }
    let a = vec![];
    x.push((&a, n + 1));

    let lcp = |a: &[char], b: &[char]| a.iter().zip(b.iter()).take_while(|p| p.0 == p.1).count();

    let mut res = vec![0; n];
    for i in 1..=n {
        let ans = max(lcp(x[i - 1].0, x[i].0), lcp(x[i].0, x[i + 1].0));
        res[x[i].1] = ans;
    }

    res
}

fn solve_trie() -> Vec<usize> {
    let n = readln!(usize);
    let s = readlns!([char]; n);

    let mut trie = LowerAlphabetTrie::new();
    for i in 0..n {
        trie.insert(i, &s[i]);
    }

    s.iter()
        .map(|s| {
            trie.node_iter(s)
                .take_while(|&n| n.matched_string_cnt > 1)
                .count()
        })
        .collect_vec()
}

fn main() {
    setup_out!(put, puts);

    let res = solve_trie();
    for res in res {
        puts!("{}", res);
    }
}

// region: trie
#[allow(dead_code)]
mod trie {
	use std::collections::HashSet;
	use std::marker::PhantomData;
	pub type LowerAlphabetTrie = Trie<LowerAlphabetSet>;
	pub struct Trie<C: CharSet> {
		pub root_node: Box<TrieNode<C>>,
		_marker: PhantomData<C>,
	}

	pub trait CharSet: Copy {
		const DAT_SIZE: usize;
		const BASE: u8;
		fn char_to_u8(c: char) -> u8 {
			c as u8 - Self::BASE
		}
	}

	pub struct TrieNodeIterator<'a, C: CharSet> {
		str: Vec<u8>,
		cur_pos: usize,
		cur_node: &'a Box<TrieNode<C>>,
	}
	impl<'a, C> Iterator for TrieNodeIterator<'a, C>
	where
		C: CharSet,
	{
		type Item = &'a TrieNode<C>;
		fn next(&mut self) -> Option<Self::Item> {
			if let Some(child) = self
				.str
				.get(self.cur_pos)
				.and_then(|&c| self.cur_node.children[c as usize].as_ref())
			{
				self.cur_node = child;
				self.cur_pos += 1;
				Some(child)
			} else {
				None
			}
		}
	}

	#[derive(Copy, Clone, Debug)]
	pub struct LowerAlphabetSet;
	impl CharSet for LowerAlphabetSet {
		const DAT_SIZE: usize = 26;
		const BASE: u8 = b'a';
	}

	pub trait StringEncodable {
		fn encode<C: CharSet>(&self) -> Vec<u8>;
		fn char_count(&self) -> usize;
	}

	impl StringEncodable for &str {
		fn encode<C: CharSet>(&self) -> Vec<u8> {
			self.chars().map(|c| C::char_to_u8(c)).collect()
		}

		fn char_count(&self) -> usize {
			self.chars().count()
		}
	}

	impl StringEncodable for Vec<char> {
		fn encode<C: CharSet>(&self) -> Vec<u8> {
			self.iter().map(|&c| C::char_to_u8(c)).collect()
		}
		fn char_count(&self) -> usize {
			self.len()
		}
	}

	impl StringEncodable for &Vec<char> {
		fn encode<C: CharSet>(&self) -> Vec<u8> {
			self.iter().map(|&c| C::char_to_u8(c)).collect()
		}

		fn char_count(&self) -> usize {
			self.len()
		}
	}

	impl<C: CharSet> Trie<C> {
		pub fn new() -> Self {
			Trie {
				root_node: Box::new(TrieNode::new()),
				_marker: PhantomData,
			}
		}

		pub fn insert<S: StringEncodable>(&mut self, id: usize, str: S) {
			let cs = str.encode::<C>();
			self.root_node.insert(id, cs.as_slice())
		}

		pub fn erase<S: StringEncodable>(&mut self, id: usize, str: S) -> bool {
			let cs = str.encode::<C>();
			self.root_node.erase(id, cs.as_slice())
		}

		pub fn search<S: StringEncodable>(&self, str: S) -> Option<usize> {
			self.find(str)
				.and_then(|n| n.terminated_str_ids.iter().next().copied())
		}

		pub fn prefix_cnt<S: StringEncodable>(&self, str: S) -> usize {
			self.find(str).map_or(0, |n| n.matched_string_cnt)
		}

		pub fn find<S: StringEncodable>(&self, str: S) -> Option<&TrieNode<C>> {
			let len = str.char_count();
			self.node_iter(str).enumerate().last().and_then(|(i, n)| {
				if i == len - 1 {
					Some(n)
				} else {
					None
				}
			})
		}

		pub fn node_iter<S: StringEncodable>(&self, str: S) -> TrieNodeIterator<C> {
			let cs = str.encode::<C>();
			TrieNodeIterator::<C> {
				str: cs,
				cur_pos: 0,
				cur_node: &self.root_node,
			}
		}
	}

	#[derive(Clone, Debug)]
	pub struct TrieNode<C: CharSet> {
		pub matched_string_cnt: usize, // # of strings in the subtree of the node
		pub terminated_str_ids: HashSet<usize>, // IDs of strings ending here
		children: Vec<Option<Box<TrieNode<C>>>>,
		_marker: PhantomData<C>,
	}

	impl<C: CharSet> TrieNode<C> {
		const INIT: Option<Box<TrieNode<C>>> = None;
		fn new() -> Self {
			TrieNode {
				matched_string_cnt: 0,
				terminated_str_ids: HashSet::new(),
				children: vec![Self::INIT; C::DAT_SIZE],
				_marker: PhantomData,
			}
		}

		fn insert(&mut self, id: usize, cs: &[u8]) {
			self.matched_string_cnt += 1;
			if let Some(c) = cs.first() {
				let i = *c as usize;
				if let Some(child) = self.children[i].as_mut() {
					child.insert(id, &cs[1..]);
				} else {
					let mut child = Box::new(TrieNode::new());
					child.insert(id, &cs[1..]);
					self.children[i] = Option::Some(child);
				}
			} else {
				self.terminated_str_ids.insert(id);
			}
		}

		fn erase(&mut self, id: usize, cs: &[u8]) -> bool {
			if let Some(c) = cs.first() {
				let i = *c as usize;
				if let Some(child) = self.children[i].as_mut() {
					child.erase(id, &cs[1..])
				} else {
					false
				}
			} else {
				self.terminated_str_ids.remove(&id)
			}
		}
	}
}
pub use trie::{CharSet, LowerAlphabetSet, LowerAlphabetTrie, StringEncodable, Trie};
// endregion: trie

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
