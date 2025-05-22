use std::env;

fn find_length(i: u64, length: u64) -> u64 {
    if i == 1 {
        return length;
    } else if i % 2 == 0 {
        return find_length(i / 2, length + 1);
    } else {
        return find_length(i * 3 + 1, length + 1);
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() < 3 {
        println!("No Arguments For Range Found");
        return;
    }

    let min_range: u64 = match args[1].parse() {
        Ok(num) => num,
        Err(_) => {
            println!("Range values must be integers");
            return;
        }
    };

    let max_range: u64 = match args[2].parse() {
        Ok(num) => num,
        Err(_) => {
            println!("Range values must be integers");
            return;
        }
    };

    if min_range >= max_range {
        println!("minRange must be less than maxRange");
        return;
    }

    let mut lengths = Vec::new();
    let mut index_lengths = Vec::new();

    for i in min_range..max_range {
        let length = find_length(i, 0);
        if lengths.len() < 10 {
            lengths.push(length);
            index_lengths.push(i);
        } else if let Some(min_length) = lengths.iter().min() {
            if length > *min_length {
                let min_index = lengths.iter().position(|&x| x == *min_length).unwrap();
                lengths[min_index] = length;
                index_lengths[min_index] = i;
            }
        }
    }

    let mut sorted_by_length: Vec<(u64, u64)> = lengths
        .iter()
        .zip(index_lengths.iter())
        .map(|(&length, &index)| (length, index))
        .collect();

    sorted_by_length.sort_by(|a, b| b.0.cmp(&a.0)); // Sort by sequence length in descending order

    println!("Sorted based on sequence length:");
    for (length, index) in sorted_by_length {
        println!("{} {}", index, length);
    }

    let mut sorted_by_index: Vec<(u64, u64)> = lengths
        .iter()
        .zip(index_lengths.iter())
        .map(|(&length, &index)| (length, index))
        .collect();

    sorted_by_index.sort_by(|a, b| b.1.cmp(&a.1)); // Sort by integer value (index) in descending order

    println!("\nSorted based on integer size:");
    for (length, index) in sorted_by_index {
        println!("{} {}", index, length);
    }
}
