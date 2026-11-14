use std::env::set_current_dir;
use std::io::{self, Write};
use std::process::Command;

fn main() {
    loop {
        print!("> ");
        io::stdout().flush().expect("should flush");
        if let Some(Ok(line)) = std::io::stdin().lines().next() {
            let mut split = line.split_whitespace();
            if let Some(command) = split.next() {
                let args: Vec<&str> = split.collect();
                if command == "exit" {
                    println!("Leaving shell, cya");
                    break;
                }
                if command == "cd" {
                    if args.is_empty() {
                        println!("Not enough arguments to run change directory (cd)");
                        continue;
                    }
                    let path = args[0];
                    match set_current_dir(path) {
                        Ok(_) => {}
                        Err(error) => println!("Error when changing directories, {error}"),
                    }
                    continue;
                }
                match Command::new(command).args(args).status() {
                    Ok(_) => {}
                    Err(error) => println!("Error when spawning a command, {error}"),
                };
            } else {
                continue;
            }
        } else {
            println!("Leaving shell, cya");
            break;
        }
    }
}
