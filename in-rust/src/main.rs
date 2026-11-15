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
                    break;
                }
                if command == "cd" {
                    if args.is_empty() {
                        eprintln!("Not enough arguments to run change directory (cd)");
                        continue;
                    }
                    if args.len() > 1 {
                        eprintln!("cd: too many arguments");
                        continue;
                    }
                    let path = args[0];
                    match set_current_dir(path) {
                        Ok(_) => {}
                        Err(error) => eprintln!("Error when changing directories, {error}"),
                    }
                    continue;
                }
                match Command::new(command).args(args).status() {
                    Ok(_) => {}
                    Err(error) => eprintln!("Error when spawning a command, {error}"),
                };
            } else {
                continue;
            }
        } else {
            break;
        }
    }
}
