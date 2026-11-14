use std::process::Command;


fn main() {

    loop {
        if let Some(Ok(line)) = std::io::stdin().lines().next() {
            let mut split = line.split_whitespace();
            let command = split.next().expect("Command to be present");
            let args: Vec<&str> = split.collect();

            let output = Command::new(command).args(args).status().expect("should spawn command correctly");

        }
    }

}
