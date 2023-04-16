# Process-Manager


## Command and tools we used
Use [execv](https://linux.die.net/man/3/execv) to run bash command in c.

Use `ps axo fname,pid,user` to display process in terminal.

Use `kill -l` to show signals and `kill -9 My-process` to kill process.

Example of execv and redirection.
```

    char *write_cmd[] = { "ps", "axo","fname,pid,user", ">", "path/processes", NULL};
    execv("/bin/ps",write_cmd);

```

## How software should work 
```

  -Display all process 
  -Display menu "refresh,kill,pass signale,exit" to interactive with program
  -IF user chose 'refresh' THEN
    update process menu
  -IF user chose 'kill' THEN
    display menu "kill with 'pid' or 'name'" 
    IF user chose 'pid' THEN
      read interger input
     ELSE read string input and interation all process with input and use signal 9 to kill the process
  -IF user chose 'pass signale' THEN
    read signale number and goto normal kill menu
  -IF user chose 'exit' THEN 
    terminate program
```

## Some ideas to how make life easy 

Parse pid in bash instand c `ps axo fname,pid | grep my-process | cut -b my-process-len- | sed 's/ //g'`.

```

  ps axo fname,pid | grep brave | cut -b 6- | sed 's/ //g'
  6617
  6628
  6629
  6632
  6656

```
We can redirect the output to `kill-file` and take it as integer in c.
