// CMP SCI 3780 — Project 1 (Task 1)
// Build with: g++ -std=c++17 -O0 -g -fno-omit-frame-pointer -Wall -Wextra -pedantic task1.cpp -o task1
// Goal: Inspect activation records (stack frames) in GDB.
//
// Strategy: Call a small chain of functions that pass arguments by value and
// create a few locals. Put a breakpoint near the end of the deepest function
// and inspect memory & addresses.

#include <cstdio>
#include <cstdint>

// Mark noinline to make frames easier to see in GDB (avoid inlining).
#if defined(__GNUC__) || defined(__clang__)
  #define NOINLINE __attribute__((noinline))
#else
  #define NOINLINE
#endif

NOINLINE int f3(int a, int b) {
    // locals with distinctive values to see in memory
    volatile int x = 0x11111111;   // volatile to avoid optimization away
    volatile int y = 0x22222222;
    volatile int z = a + b;        // still volatile so it stays in memory

    // Keep some bytes around
    volatile char marker[8] = { 'P','3','7','8','0','T','1','\0' };

    // Place a "landmark" print so we can set a breakpoint after it.
    std::printf("[f3] a=%d b=%d x=%#x y=%#x z=%d marker=%s\n", a, b, x, y, (int)z, (const char*)marker);

    // ------ Suggested GDB breakpoint location: next line ------
    return (int)(x ^ y ^ z);
}

NOINLINE int f2(int a) {
    volatile int lx = 0x33333333;
    volatile int ly = a + 7;
    return f3(lx, ly);
}

NOINLINE int f1(int n) {
    volatile int l = n * 2;
    return f2(l);
}

int main() {
    int seed = 42;
    int result = f1(seed);

    std::printf("[main] result=%d (seed=%d)\n", result, seed);
    return 0;
}
