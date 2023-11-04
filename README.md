# simple_shell


## Description

**Simple_shell** Write a Simple UNIX command interpreter

## Purpose

The purpose of the simple shell project is to understand:
* how a shell works
* PID and PPIDs
* how processes are created
* the three prototypes of `main`
* how the shell uses the `PATH` to find and execute programs
* the `EOF`/"end-of-file" condition

## Requirements

* Must follow [Betty](https://github.com/holbertonschool/Betty/wiki) style and document guidelines
* Allowed editors: `vi`, `vim`, `emacs`
* Must have a `README.md` file
* All header files must be include guarded
* No more than 5 functions per files
* All your header files should be include guarded
* Use system calls only when you need to [why?](https://alx-intranet.hbtn.io/rltoken/EU7B1PTSy14INnZEShpobQ)
* Write a README with the description of your project
* You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository. Format, see [Docker](https://alx-intranet.hbtn.io/rltoken/UL8J3kgl7HBK_Z9iBL3JFg)

## Compilation

```gcc -Wall -Wextra -Werror -pedantic *.c -o hsh```
*GCC 4.8.4 or later only*
## Usage Examples
### Interactive Mode
```c
$ ./hsh
($) /bin/sh
hsh main.c shell.c 
($)
($) exit
$
```

### Non-Interactive Mode

```c
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```
## Authors
Houssam Mahmoud & Rania Triek
