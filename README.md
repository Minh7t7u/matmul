# matmul

A small matrix library in C. Matrices use flat float storage and every
operation returns a status code instead of raising or aborting.

## Types

- `matrix`: holds `width`, `height`, and a pointer to the `data` array.
- `mat_status`: `SUCCESS`, `ERSIZE`, `ERNULL`, or `ERSHAPE`.

## API

- `mat_init`: wrap an existing float array in a matrix.
- `mat_create`: allocate a matrix of the given size.
- `mat_add`, `mat_sub`: elementwise add and subtract.
- `mat_dot`: matrix multiply.
- `mat_scale`: multiply every element by a scalar.
- `mat_destroy`: free a matrix's data.

Indexing helpers `sindex` and `const_sindex` read an element at a given
row and column with bounds checking through `assert`.

## Build

Compile `matmul.c` together with your program and include `matmul.h`.
The library targets C11 and is meant to be built with optimization
enabled, so pass `-std=c11 -O3` for representative performance.

```
cc -std=c11 -O3 your_program.c matmul.c -o your_program
```

The same flags live in `compile_flags.txt` so tooling such as clangd
sees a matching configuration.
