use std::fs;

fn main() {
        let filename = String::from("/pub/pounds/CSC330/poker/testhands");

            let contents = fs::read_to_string(filename)
                    .expect("Something went wrong reading the file");

                        println!("The contents of the file:\n{}", contents);

}
