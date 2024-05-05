# Generator

This is a small program for auto generating code templates in C.
The executable has been placed in ~/.local/bin since this is my
private PATH. See you PATH by typing

``` console
echo $PATH
```
in your terminal.

Now you can write

``` console
generator <file_name>
```
and it will generate a simple boilerplate .c file and generic
Makefile for you.

The -f flag will force a write, and overwrite any files with the
name you want.

if you need the line numbers for debugging purposes do
``` console
make DEBUG=1
````
and it will generate it with line numbers
