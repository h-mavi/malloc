*This project has been created as part of the 42 mastery curriculum by mfanelli*

# malloc

A **42** curriculum project: a from-scratch reimplementation of `malloc`, `free`, and `realloc`, built as a dynamic library. It also implements the bonus `show_alloc_mem()` function to visualize the current allocator state.

Memory is managed in three kinds of zones, each obtained directly from the kernel with `mmap`, without relying on the standard C allocator:

- **TINY** – for allocations up to 16 KB (`PAGE_SIZE * 16`)
- **SMALL** – for allocations up to 1 MB (`PAGE_SIZE * 256`)
- **LARGE** – for anything bigger; each large allocation gets its own dedicated `mmap` region

## How it works

- **Zones** (`TINY`/`SMALL`) are pre-allocated as large contiguous regions (`TINY_ZONE` ≈ 6.4 MB, `SMALL_ZONE` ≈ 100 MB) able to hold up to 100 blocks each; new blocks are carved out of them as needed.
- **Blocks** are linked lists of `struct blockdata` chunks (size, free flag, pointer to user memory, pointer to next block) living inside a zone.
- **`malloc`** picks the right zone based on the requested size, reuses a free block of the right size, splits a larger free block when possible (`SplitBlock`), or extends the zone with a new block (`AddBlock`). Requests larger than `M_SMALL` bypass the zones entirely and get their own `mmap` region (`AddLargeBlock`).
- **`free`** marks a block as free, `munmap`s it directly if it belongs to the LARGE category, and triggers coalescing of adjacent free blocks (`CheckForCoalesce`).
- **`realloc`** grows/shrinks in place when possible, otherwise allocates a new block, copies the data over, and frees the old one.
- **`show_alloc_mem`** walks every zone and every block, printing each allocated (and, in debug mode, freed) range and a running total — useful for inspecting the allocator's internal state.
- A destructor (`CheckForTotalFree`) runs at program exit, releases any zone left completely empty, and reports a leak warning (`ERROR LEAKS`) if anything is still allocated.
- The allocator is instrumented with **Valgrind** client requests (`VALGRIND_MALLOCLIKE_BLOCK` / `VALGRIND_FREELIKE_BLOCK`) so that Valgrind can correctly track memory managed outside the standard allocator.

## Project structure

```
.
├── Makefile
├── head.h              # structures, macros, function prototypes
├── malloc.c            # malloc / free / realloc / show_alloc_mem
├── utils.c             # zone/block creation, splitting, large-block handling
├── find.c              # lookup helpers (free block, first zone, block by pointer)
├── check.c             # coalescing, zone cleanup, leak check (destructor)
├── main.c              # standalone test suite (not linked into the library)
├── libft/              # custom C standard library (used internally)
│   └── printf/         # custom ft_printf implementation
└── .vscode/            # editor configuration
```

## Requirements

- Linux (uses `mmap`, `sys/resource.h`, and `bits/mman-linux.h`)
- A C compiler (`cc`) supporting C11 (`stdalign.h`, `stdbool.h`)
- Valgrind development headers (`valgrind/memcheck.h`) — required at compile time for the Valgrind instrumentation

## Build

```

make        # builds libft, ft_printf, and the shared library

```

This produces:

- `libmalloc_<arch>_<os>.so` (e.g. `libmalloc_x86_64_Linux.so`), the actual shared library
- `libmalloc.so`, a symlink to it for convenience

Other Makefile targets:

| Target       | Description                                             |
| ------------ | -------------------------------------------------------- |
| `make`       | Build `libft`, `ft_printf`, and the malloc shared library |
| `make test`  | Build a standalone `test` binary (links `main.c`)         |
| `make clean` | Remove object files (also cleans `libft`)                 |
| `make fclean`| `clean` + remove the shared library, symlink, and `test`  |
| `make re`    | `fclean` + `make`                                          |

## Usage

<!-- ### Override the system allocator

Once built, preload the library so any dynamically-linked program uses this allocator instead of the system's:

```

LD_PRELOAD=$(pwd)/libmalloc.so your_program

```-->

### Run the built-in test suite

```

make test
./test

```

`main.c` runs a series of checks covering basic allocation, `malloc(0)`, multiple allocations, `realloc` (growing/shrinking/edge cases), TINY/SMALL/LARGE zone allocations, fragmentation and coalescing, and double-free / `free(NULL)` safety, printing the allocator state (`show_alloc_mem`) at each step.

## Notes

- Debug logging in `show_alloc_mem()` can be turned off by setting `DEBUG` to `0` in `head.h`.
- `libft` is vendored as a subdirectory and built automatically as part of `make`; it is not a Git submodule.
