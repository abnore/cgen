# Generator

This is a small program for auto generating code templates in C.
The executable has been placed in ~/.local/bin since this is my
private PATH.

``` console
echo $PATH
```

Now you can write

``` console
generate <file_name>
```
it will ill generate a simple boilerplate .c file and generic
Makefile in the current directory.

The -f flag will force a write, and overwrite any files with the
name you want.
