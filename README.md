## Treex
Treex is an improved version of the UNIX tree command, built from the ground up in c. Improvements
include being able to view file size, permissions, the union of two directories, all with added color
coding.

## Usage

In order to make the file use the `make` command.

Once the file is made follow these usage guidelines:
  ```sh
  ./treex [directory] [-d depth] [-s] [-p] [-u directory] [-h]
  ```
All of the arguments in `[]` are optional, however any two arguments in the same
`[]` are required together. The order does not matter as long as `[directory]` comes
before all other arguments.
    `[directory]` specifies which directory you wish to be
the root of the tree. If a directory is not specified then the directory is '.'.
    `[-d depth]` specifies the max depth you want the tree to go, with depth being
an integer.
    `[-s]` is used when you want to show the file sizes of all the files.
    `[-p]` is used when you want to show the premissions of all the files.
    `[-u directory]` makes it so the tree that prints is a union of the given directory
and the root directory that can be provided using [directory].
    `[-h]` displays a usage menu.
