# CMP SCI 3780 — Project 1 Starter

This repo contains **complete, working starters** for all three tasks plus a Makefile and a report template.

## Files
- `task1.cpp` — stack/activation-record exploration with a 3-function call chain.
- `task2.cpp` — compare a local `static` array vs a `malloc`'d dynamic array; print addresses for GDB work.
- `task3.cpp` — integer calculator with **overflow-safe** addition, multiplication, and division.
- `Makefile` — `make all`, or `make task1`/`task2`/`task3`.
- `REPORT_TEMPLATE.md` — a fill‑in template for your writeup with checklist and GDB commands.

---

## Build (on delmar.umsl.edu)

```bash
module load gcc   # if your environment uses modules; otherwise skip
make              # builds all targets
```

If you don't have `make`, compile directly:
```bash
g++ -std=c++17 -O0 -g -fno-omit-frame-pointer -Wall -Wextra -pedantic task1.cpp -o task1
g++ -std=c++17 -O0 -g -fno-omit-frame-pointer -Wall -Wextra -pedantic task2.cpp -o task2
g++ -std=c++17 -O2 -g -Wall -Wextra -pedantic task3.cpp -o task3
```

---

## Task 1 — GDB Walkthrough

1. Build and run once:
   ```bash
   make task1
   ./task1
   ```

2. Start GDB and set breakpoint at the **return** line in `f3`:
   ```gdb
   gdb ./task1
   (gdb) start
   (gdb) break f3
   (gdb) commands
   Type commands for breakpoint(s) 1, one per line.
   End with a line saying just "end".
   >silent
   >finish    # run to end of f3 so locals are still live
   >end
   (gdb) continue
   ```

   Or simply:
   ```gdb
   (gdb) break task1.cpp:/* line number just before 'return' in f3 */
   (gdb) run
   ```

3. Inspect stack pointers and nearby memory (x86-64 assumed; adjust if needed):
   ```gdb
   (gdb) info frame
   (gdb) bt
   (gdb) p &x
   (gdb) p &y
   (gdb) p &z
   (gdb) p &marker
   (gdb) info registers rbp rsp
   (gdb) x/64bx $rsp
   (gdb) x/32wx $rsp
   (gdb) x/64bx $rbp-128
   (gdb) x/64bx $rbp
   ```

4. Measure **activation record size for f3** (approximate): subtract the saved stack pointer from current frame base or examine `info frame` which prints frame size. Also compare addresses of `x`, `y`, `z`, `marker` to explain layout and padding/alignment.

5. To show **call order**, look at the backtrace:
   ```gdb
   (gdb) bt
   ```
   You should see `main -> f1 -> f2 -> f3` (top is the current function).

> In your report, include screenshots of the memory hex-dumps and clearly label where locals, saved RBP, and return address are.

---

## Task 2 — GDB Walkthrough

1. Build & run:
   ```bash
   make task2
   ./task2
   ```

2. In GDB:
   ```gdb
   (gdb) break main
   (gdb) run
   (gdb) next        # step to after malloc
   (gdb) p &staticArr[0]
   (gdb) p &staticArr[7]
   (gdb) p dyn
   (gdb) x/16wx &staticArr[0]
   (gdb) x/16wx dyn
   (gdb) set $N = 8
   (gdb) x/32bx dyn-32
   (gdb) x/32bx dyn+$N*4
   ```

   Discuss whether they are contiguous (they are not—`staticArr` is in static data, `dyn` points to heap). Comment on any allocator **metadata** you see around `dyn`. For the static array, show there is no size header stored nearby by the compiler—its "size" is known at compile time.

---

## Task 3 — Overflow‑Safe Arithmetic

Run and try edge cases:

```bash
./task3
# Try:
#  2147483647 1             -> add overflow
#  -2147483648 -1           -> mul and div overflow cases
#  50000 50000              -> mul overflow
#  7 0                      -> division by zero
```

Justification of correctness:
- **Addition**: check against `INT_MAX`/`INT_MIN` before computing.
- **Multiplication**: special-case `INT_MIN * -1`, otherwise compare `|a| > INT_MAX / |b|`.
- **Division**: disallow `b==0` and `INT_MIN / -1` (overflow in two's complement).

---

## Screenshots & Report

Use `REPORT_TEMPLATE.md` and paste your screenshots showing the memory dumps and annotate what each region represents. Convert to PDF (e.g., using any editor or an online converter) before submission.
