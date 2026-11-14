# Goal
Create shell in Rust. For fun. No AI allowed :)

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
