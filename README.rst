========================================================================
                           SIMD popcount
========================================================================

Sample programs for my article http://0x80.pl/articles/sse-popcount.html

.. image:: https://travis-ci.org/WojciechMula/sse-popcount.svg?branch=master
    :target: https://travis-ci.org/WojciechMula/sse-popcount

Paper
------------------------------------------------------------------------

Daniel Lemire, Nathan Kurz and I published an article
`Faster Population Counts using AVX2 Instructions`__.

__ https://arxiv.org/abs/1611.07612


Introduction
------------------------------------------------------------------------

Subdirectory **original** contains code from 2008 --- it is 32-bit
and GCC-centric. The **root directory** contains fresh C++11 code,
written with intrinsics and tested on 64-bit machines.

There are two programs:

* ``verify`` --- it tests if all non-lookup implementations counts
  bits properly;
* ``speed`` --- benchmarks different implementations of popcount
  procedure; please read help to find all options (run the program
  without arguments).

There are several targets:

* **default** --- builtin functions, SSE and popcnt instructions;
* **AVX2** --- all above plus AVX2 implementations;
* **AVX512BW** --- all above plus experimental AVX512BW code (require
  software emulator);
* **AVX512 VPOPCNT** --- all above plus experimental AVX512 VPOPCNT
  code (should be compilable with very recent GCC__, software emulator
  doesn't support this extension yet);
* **arm** --- builtin and ARM Neon implementations.

Type ``make help`` to find out details. To run the default target
benchmark simply type ``make``.

__ https://github.com/gcc-mirror/gcc/commit/e0aa57d6b04908affdf4655a6b4a9f2d4d03483b


Available implementations
------------------------------------------------------------------------

+---------------------------------------+------------------------------------------------------------------+
| procedure                             | description                                                      |
+=======================================+==================================================================+
| lookup-8                              | lookup in std::uint8_t[256] LUT                                  |
+---------------------------------------+------------------------------------------------------------------+
| lookup-64                             | lookup in std::uint64_t[256] LUT                                 |
+---------------------------------------+------------------------------------------------------------------+
| bit-parallel                          | naive bit parallel method                                        |
+---------------------------------------+------------------------------------------------------------------+
| bit-parallel-optimized                | a bit better bit parallel                                        |
+---------------------------------------+------------------------------------------------------------------+
| bit-parallel-mul                      | bit-parallel with fewer instructions                             |
+---------------------------------------+------------------------------------------------------------------+
| bit-parallel32                        | naive bit parallel method (32 bit)                               |
+---------------------------------------+------------------------------------------------------------------+
| bit-parallel-optimized32              | a bit better bit parallel (32 bit)                               |
+---------------------------------------+------------------------------------------------------------------+
| harley-seal                           | Harley-Seal popcount (4th iteration)                             |
+---------------------------------------+------------------------------------------------------------------+
| sse-bit-parallel                      | SSE implementation of bit-parallel-optimized (unrolled)          |
+---------------------------------------+------------------------------------------------------------------+
| sse-bit-parallel-original             | SSE implementation of bit-parallel-optimized                     |
+---------------------------------------+------------------------------------------------------------------+
| sse-bit-parallel-better               | SSE implementation of bit-parallel with fewer instructions       |
+---------------------------------------+------------------------------------------------------------------+
| sse-harley-seal                       | SSE implementation of Harley-Seal                                |
+---------------------------------------+------------------------------------------------------------------+
| sse-lookup                            | SSSE3 variant using pshufb instruction (unrolled)                |
+---------------------------------------+------------------------------------------------------------------+
| sse-lookup-original                   | SSSE3 variant using pshufb instruction                           |
+---------------------------------------+------------------------------------------------------------------+
| avx2-lookup                           | AVX2 variant using pshufb instruction (unrolled)                 |
+---------------------------------------+------------------------------------------------------------------+
| avx2-lookup-original                  | AVX2 variant using pshufb instruction                            |
+---------------------------------------+------------------------------------------------------------------+
| avx2-harley-seal                      | AVX2 implementation of Harley-Seal                               |
+---------------------------------------+------------------------------------------------------------------+
| cpu                                   | CPU instruction popcnt (64-bit variant)                          |
+---------------------------------------+------------------------------------------------------------------+
| sse-cpu                               | load data with SSE, then count bits using popcnt                 |
+---------------------------------------+------------------------------------------------------------------+
| avx2-cpu                              | load data with AVX2, then count bits using popcnt                |
+---------------------------------------+------------------------------------------------------------------+
| avx512-harley-seal                    | AVX512 implementation of Harley-Seal                             |
+---------------------------------------+------------------------------------------------------------------+
| avx512-vpopcnt                        | AVX512 VPOPCNT                                                   |
+---------------------------------------+------------------------------------------------------------------+
| builtin-popcnt                        | builtin for popcnt                                               |
+---------------------------------------+------------------------------------------------------------------+
| builtin-popcnt32                      | builtin for popcnt (32-bit variant)                              |
+---------------------------------------+------------------------------------------------------------------+
| builtin-popcnt-unrolled               | unrolled builtin-popcnt                                          |
+---------------------------------------+------------------------------------------------------------------+
| builtin-popcnt-unrolled32             | unrolled builtin-popcnt32                                        |
+---------------------------------------+------------------------------------------------------------------+
| builtin-popcnt-unrolled-errata        | unrolled builtin-popcnt avoiding false-dependency                |
+---------------------------------------+------------------------------------------------------------------+
| builtin-popcnt-unrolled-errata-manual | unrolled builtin-popcnt avoiding false-dependency (asembly code) |
+---------------------------------------+------------------------------------------------------------------+
| builtin-popcnt-movdq                  | builtin-popcnt where data is loaded via SSE registers            |
+---------------------------------------+------------------------------------------------------------------+
| builtin-popcnt-movdq-unrolled         | builtin-popcnt-movdq unrolled                                    |
+---------------------------------------+------------------------------------------------------------------+
| builtin-popcnt-movdq-unrolled_manual  | builtin-popcnt-movdq unrolled (assembly code)                    |
+---------------------------------------+------------------------------------------------------------------+
| neon-vcnt                             | ARM Neon using VCNT                                              |
+---------------------------------------+------------------------------------------------------------------+
| neon-HS                               | Harley-Seal using Neon VCNT                                      |
+---------------------------------------+------------------------------------------------------------------+
| aarch64-cnt                           | ARMv8 Neon using CNT                                             |
+---------------------------------------+------------------------------------------------------------------+

Performance results
------------------------------------------------------------------------

The subdirectory results__ contains performance results from various
computers. If you can, please contribute.

__ results/README.rst


Acknowledgments
------------------------------------------------------------------------

* **Kim Walisch** (@kimwalisch) wrote Harley-Seal scalar implementation.
* **Simon Lindholm** (@simonlindholm) added unrolled versions of procedures.
* **Dan Luu** (@danluu) agreed to include his procedures (``builint-*``)
  into this project. More details in Dan's article `Hand coded assembly
  beats intrinsics in speed and simplicity`__

__ http://danluu.com/assembly-intrinsics/


See also
------------------------------------------------------------------------

* libpopcnt__ --- library by Kim Walisch utilizing methods from our paper.

__ https://github.com/kimwalisch/libpopcnt


.. vim: nowrap
