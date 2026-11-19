# Goal
Create shell in C/Cpp/Rust. For fun. No AI allowed :)

# Plan
We need loop. Code taken from [Tutorial - Write a Shell in C by Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/)

``` c
void lsh_loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args);

    free(line);
    free(args);
  } while (status);
}
```



# How to run 

From root:

```sh
# Rust
cargo run --manifest-path in-rust/Cargo.toml

# C/C++
make setup

# C
./build/debug/in-c/shell-in-c

# C++
./build/debug/in-cpp/shell-in-cpp
```

# Implementation checklist

Scope: basic shell functionality.

## Rust

- [x] Display a prompt and accept multiple commands.
- [x] Ignore empty input, spaces, and tabs.
- [x] Run programs from PATH, absolute paths, and relative paths.
- [x] Pass multiple whitespace-separated arguments (without quoting).
- [x] Wait for the program to finish before showing the next prompt.
- [x] Report unknown commands and execution errors; keep running.
- [x] Exit cleanly on `exit` and EOF (`Ctrl-D` on an empty line).
- [x] Support `cd` with absolute and relative paths.
- [x] Report missing and invalid `cd` arguments; keep the current directory unchanged.
- [x] Write error messages to stderr.

## C

- [x] Display a prompt and accept multiple commands.
- [x] Ignore empty input, spaces, and tabs.
- [x] Run programs from PATH, absolute paths, and relative paths.
- [x] Pass multiple whitespace-separated arguments (without quoting).
- [x] Wait for the program to finish before showing the next prompt.
- [x] Report unknown commands and execution errors; keep running.
- [x] Exit cleanly on `exit` and EOF (`Ctrl-D` on an empty line).
- [x] Support `cd` with absolute and relative paths.
- [x] Report missing and invalid `cd` arguments; keep the current directory unchanged.
- [x] Write error messages to stderr.

## C++

- [x] Display a prompt and accept multiple commands.
- [x] Ignore empty input, spaces, and tabs.
- [x] Run programs from PATH, absolute paths, and relative paths.
- [x] Pass multiple whitespace-separated arguments (without quoting).
- [x] Wait for the program to finish before showing the next prompt.
- [x] Report unknown commands and execution errors; keep running.
- [x] Exit cleanly on `exit` and EOF (`Ctrl-D` on an empty line).
- [x] Support `cd` with absolute and relative paths.
- [ ] Report missing and invalid `cd` arguments; keep the current directory unchanged.
- [x] Write error messages to stderr.
