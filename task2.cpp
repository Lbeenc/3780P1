// CMP SCI 3780 — Project 1 (Task 2)
// Build with: g++ -std=c++17 -O0 -g -fno-omit-frame-pointer -Wall -Wextra -pedantic task2.cpp -o task2
// Goal: Compare addresses of a local static array and a dynamically allocated array.
// Also, experiment (in the *debugger*) to observe what lies in memory just
// before/after the dynamic array (some allocators store metadata).
// Do *not* dereference out-of-bounds in C++; use GDB/LLDB to *inspect* memory.
//
// NOTE: This program prints addresses to help guide your debugging session.
// Actual allocator details depend on the system (on delmar it may be glibc malloc).

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <vector>

int main() {
    static int staticArr[8];   // static storage duration but with internal linkage to this TU
    const int N = 8;

    // Fill arrays with recognizable values
    for (int i = 0; i < 8; ++i) staticArr[i] = 0x1000 + i;

    int* dyn = (int*)std::malloc(N * sizeof(int));
    if (!dyn) {
        std::perror("malloc");
        return 1;
    }
    for (int i = 0; i < N; ++i) dyn[i] = 0x2000 + i;

    std::printf("Addresses & sizes\n");
    std::printf("  staticArr:  %p  .. %p  (count=%d)\n",
        (void*)&staticArr[0], (void*)&staticArr[N-1], N);
    std::printf("  dyn start:  %p\n", (void*)dyn);
    std::printf("  dyn end:    %p  (approx dyn + %zu)\n",
        (void*)((char*)dyn + N*sizeof(int)), N*sizeof(int));

    std::puts("\nNext steps (do these in GDB):");
    std::puts("  (1) break main; run");
    std::puts("  (2) x/16wx &staticArr[0]   # inspect static array contents");
    std::puts("  (3) x/16wx dyn             # inspect dynamic array contents");
    std::puts("  (4) x/32bx dyn-32          # peek *before* dyn to look for allocator metadata (read-only!)");
    std::puts("  (5) x/32bx dyn+N*4         # peek *after* dyn for fence/metadata (if any)");
    std::puts("\nRemember: do *not* rely on these bytes in code; this is just a debugging observation.");

    std::free(dyn);
    return 0;
}
