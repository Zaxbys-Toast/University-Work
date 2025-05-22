use num_bigint::BigInt;
use num_traits::{One, Zero};
use std::cmp::Ordering;
use std::env;

#[derive(Debug, Clone, Eq)]
struct CollatzValue {
    value: BigInt,
    c_length: BigInt,
}

impl PartialEq for CollatzValue {
    fn eq(&self, other: &Self) -> bool {
        self.value == other.value && self.c_length == other.c_length
    }
}

impl PartialOrd for CollatzValue {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl Ord for CollatzValue {
    fn cmp(&self, other: &Self) -> Ordering {
        self.c_length
            .cmp(&other.c_length)
            .then_with(|| other.value.cmp(&self.value)) // Reverse for value
    }
}

impl std::fmt::Display for CollatzValue {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}   {}", self.value, self.c_length)
    }
}

fn get_length(mut i: BigInt) -> BigInt {
    let mut count = BigInt::zero();
    while i != BigInt::one() {
        if &i % 2 == BigInt::zero() {
            i /= 2;
        } else {
            i = i * 3 + 1;
        }
        count += 1;
    }
    count
}

fn compute_collatz_in_range(start: i32, stop: i32) -> (Vec<CollatzValue>, Vec<CollatzValue>) {
    let mut top_10: Vec<CollatzValue> = Vec::new();

    for i in start..=stop {
        let val = BigInt::from(i);
        let collatz_length = get_length(val.clone());

        if let Some(existing_index) = top_10.iter().position(|x| x.c_length == collatz_length) {
            let existing = &top_10[existing_index];
            if val < existing.value {
                top_10.remove(existing_index);
                top_10.push(CollatzValue { value: val, c_length: collatz_length });
                top_10.sort();
            }
        } else {
            if top_10.len() < 10 {
                top_10.push(CollatzValue { value: val, c_length: collatz_length });
                top_10.sort();
            } else {
                let smallest = &top_10[0];
                let new_item = CollatzValue { value: val, c_length: collatz_length };
                if smallest < &new_item {
                    top_10.remove(0);
                    top_10.push(new_item);
                    top_10.sort();
                }
            }
        }
    }

    let mut sorted_by_length = top_10.clone();
    sorted_by_length.sort_by(|a, b| b.cmp(a)); // Descending by length, then by value
    let mut sorted_by_value = top_10.clone();
    sorted_by_value.sort_by(|a, b| a.value.cmp(&b.value)); // Ascending by value

    (sorted_by_length, sorted_by_value)
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 3 {
        eprintln!("Usage: cargo run <start> <end>");
        std::process::exit(1);
    }

    let start: i32 = args[1].parse().expect("Invalid start value");
    let stop: i32 = args[2].parse().expect("Invalid end value");

    let (sorted_by_length, sorted_by_value) = compute_collatz_in_range(start, stop);

    println!("Sorted by length:");
    for cv in sorted_by_length {
        println!("{}", cv);
    }

    println!("Sorted by value:");
    for cv in sorted_by_value {
        println!("{}", cv);
    }
}
