// ASAN fails because KLEE does not cleanup states with -dump-states-on-halt=false
// REQUIRES: not-asan
// RUN: %clang %s -emit-llvm %O0opt -c -o %t.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --only-output-states-covering-new --max-instructions=2000 --delay-cover-on-the-fly=500 --dump-states-on-halt=false --cover-on-the-fly --search=bfs --use-guided-search=none --output-dir=%t.klee-out %t.bc 2>&1 | FileCheck %s

#include "klee/klee.h"

#define a (2)
int main() {
  int res = 0;
  for (;;) {
    int n = klee_int("n");
    switch (n) {
    case 1:
      res += 1;
      break;
    case 2:
      res += 2;
      break;
    case 3:
      res += 3;
      break;
    case 4:
      res += 4;
      break;

    default:
      break;
    }
  }
}

// CHECK: KLEE: done: completed paths = 0
// CHECK: KLEE: done: generated tests = 5