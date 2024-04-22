# performance
- [introduction](#introduction)
  - [example: matrix multiplication performance optimization](#example-matrix-multiplication-performance-optimization)
- [Bentley optimization rules](#bentley-optimization-rules)
  - [data structures](#data-structures)

## links  <!-- omit from toc -->


## todo  <!-- omit from toc -->
- [performance engineering (MIT 2018)](https://ocw.mit.edu/courses/6-172-performance-engineering-of-software-systems-fall-2018/)
- SIMD - NEON & Hexagon DSP
  - intrinsic or assembly instructions
- [gpu programming (IITM 2022)](http://www.cse.iitm.ac.in/~rupesh/teaching/gpu/jan22/)
- [programming massively parallel processors (UIUC 2018)](https://www.youtube.com/playlist?list=PLRRuQYjFhpmvu5ODQoY2l7D0ADgWEcYAX)
- [compiler explorer](https://godbolt.org/)
- [an even easier introduction to CUDA](https://developer.nvidia.com/blog/even-easier-introduction-cuda/)
- [Amdahl's law paper](https://inst.eecs.berkeley.edu//~n252/paper/Amdahl.pdf)
- [Arrayfire](https://github.com/arrayfire/arrayfire)
- [Duff's device](https://en.wikipedia.org/wiki/Duff%27s_device)
- [NEON2SSE](https://github.com/intel/ARM_NEON_2_x86_SSE)
- [SIMD javidx9](https://www.youtube.com/watch?v=x9Scb5Mku1g)
- [SIMD perf tests](https://github.com/ARM-software/meabo)
- [x64 assembly programming & check other playlists](https://www.youtube.com/playlist?list=PLKK11Ligqitg9MOX3-0tFT1Rmh3uJp7kA)
- static sparse graph using CSR

## introduction
- ***the first rule of program optimization: don't do it  
second rule of program optimization: for experts only, don't do it yet***
- there are software properties that are more important that performance, like modularity, reliability, portability, maintainability, testability etc  
then **why performance:** performance is the currency of computing using which we often buy needed properties  
- Moore's law and scaling of clock frequency was the printing press for the currency of performance, but that came to an end in 2004 when clock speed plateaued  
to scale performance, processor manufacturers put many processing cores on the microprocessor chip  
![](./media/performance/technology_scaling.png)  
performance is no longer free, now it looks like big multicore processors with complex cache hierarchies, wide vector units, GPUs, FPGAs, etc  
so now the software must be adapted to utilize this hardware efficiently
- **iron law of processor performance:** trade-off between complexity and the number of primitive instructions that processors use to perform calculation  
![](./media/performance/iron_law.png)
- **Amdahl's law:** overall performance improvement gained by optimizing a single part of a system is limited by the fraction of time that the improved part is actually used  
![](./media/performance/amdahls_law.png)  
`Slatency` theoretical speedup  
`s` speedup of optimized part  
`p` fraction of time

### example: matrix multiplication performance optimization
- execution of matrix multiplication of 4096 x 4096 floating-pointing point matrix in python takes 6 hours, in java takes 46 minutes (8.81x relative speedup), in C takes 19 minutes (2.07x relative speedup)  
python is interpreted, C is compiled directly to machine code and java is (in the middle) compiled to byte-code which is then interpreted by just-in-time (JIT) compiled to machine code
  ```cpp
  for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
          for (int k = 0; k < n; ++k)
              C[i][j] += A[i][k] * B[k][j];
  ```
- **interpreter:** reads, interprets & performs each program statement and updates the machine state  
interpreters are versatile (easily support high-level programming features) but at the cost of performance  
![](./media/performance/interpreter_loop.png)
- **JIT compilation:** can recover some of the performance lost by interpretation, code is interpreted when it is first executed, whenever some piece of code executes sufficiently frequently it get compiled to machine code in real time, future executions will use the more efficient compiled version
- **loop order:** we can change the order of the loops in a program without affecting its correctness  
example: in the matrix multiplication program `i, k, j` gives a 6.5x speedup over `i, j, k`, this is because matrices are laid out in memory in row-major layout  
![](./media/performance/loop_ordering_1.png)  
![](./media/performance/loop_ordering_2.png)  
we can measure the effect of different access patterns using cachegrind: `valgrind --tool=cachegrind ./mm.exe`
- **compiler optimization:** compilers provide a collection of optimization switches which we can specify, example: `-O2` gives a 3.2x speedup over `-O0`  
compilers also support optimization levels for special purposes such as for size `-Os` or for debugging `-Og`
- **multicore parallelism:** use all cores in the processor instead of just 1 we are running now  
example: use `cilk_for` loop to allow iterations of the easily parallelized loop to execute in parallel, this will give 12x speedup on 12 cores  
rule of thumb is to parallelize outer loops rather than inner loops due to scheduling overhead, parallelizing just `i` loop gives a 167x speedup in performance compared to when only `j` loop parallelized
  ```cpp
  cilk_for (int i = 0; i < n; ++i)
      for (int k = 0; k < n; ++k)
          for (int j = 0; j < n; ++j)
              C[i][j] += A[i][k] * B[k][j];
  ```
- **data reuse (tiling):** restructure the computation to make the most of the cache by reysing the data that's already there since cache misses are slow and hits are fast  
example: tiled matrix multiplication, tuning parameter `s` needs to be figured out by experimentation  
![](./media/performance/tiled_matrix_multiplication.png)
  ```cpp
  cilk_for(int ih = 0; ih < n; ih += s)
      cilk_for(int jh = 0; jh < n; jh += s)
          for (int kh = 0; kh < n; kh += s)
              for (int il = 0; il < s; ++il)
                  for (int kl = 0; kl < s; ++kl)
                      for (int jl = 0; jl < s; ++jl)
                          C[ih + il][jh + jl] += A[ih + il][kh + kl] * B[kh + kl][jh + jl];
  ```  
  for a two-level cache, unlike the 1D tiling where binary search can be used for the tuning parameter, in 2D tiling we need exhaustive experimentation (of all possibilities) to arrive at best tuning parameters  
  ![](./media/performance/tiled_matrix_multiplication_2d.png)
- **recursive matrix multiplication (divide & conquer):** tile for every power of 2 simultaneously  
example: so 8 multiplications of n/2 x n/2 and 1 addition of n x n matrix  
![](./media/performance/recursive_matrix_multiplication.png)  
![](./media/performance/recursive_matrix_multiplication_cilk.png)  
but performance is degraded because we have a very small base case (`n == 1`) leading to higher function call overhead, so we must coarsen the recursion by introducing a threshold  
![](./media/performance/recursive_matrix_multiplication_cilk_coarsen.png)
- **vector hardware:** modern processors incorporate vector hardware to process data in single-instruction stream multiple-data stream fashion  
compilers use vector instructions automatically when compiling at optimization level `-O2` or higher, but many machines don't support the newest set of vector instructions so the compiler uses vector instructions conservatively by default  
**intrinsic instructions:** C-style functions that provide direct access to hardware vector operations
- so performance engineering is the cycle of think -> code -> run to test & measure  
with above discussed optimizations, we received a speedup of 53292x  
![](./media/performance/matrix_multiplication_performance_optimizations.png)

## Bentley optimization rules
- **work:** of a program on a given input is the sum total of all the operations executed by the program
- algorithm design can produce dramatic reductions in the amount of work it takes to solve a problem, example: a `O(nlogn)`-time quick sort replacing `O(n^2)`-time insertion sort  
reducing the work of a program doesn't automatically reduce its running time due to the complex nature of computer hardware (ILP, caching, vectorization, speculation, branch prediction, etc), but reducing the workload serves as a good heuristic for reducing overall running time
- ![](./media/performance/bentleys_rules_list.png)

### data structures
- **packing & encoding:** idea of packing is to store more than one data value in a machine word and of encoding is to convert data values into a representation requiring fewer bits  
example: encoding date in a string `september 11 2008` will need 18 bytes, but assuming years are from 4096BC to 4096AD then there are `365.25 * 404096 * 2 ≈ 3x10^6` which can be encoded in `log2(3x10^6) ≈ 22` bits  
to make fetching of data easier it can be packed into bitfields where individual fields can be extracted much more quickly than if we had encoded the 3M dates as sequential integers
  ```cpp
  typedef struct
  {
      int year : 13;
      int month : 4;
      int dat : 5;
  } date_t;
  ```
- **augmentation:** add information to a data structure to make common operations do less work  
example: appending one singly linked list to another requires walking the length of the first lost to set its null pointer to the start of the second, instead augment the list with a tail pointer that allows appending to operate in constant time  
![](./media/performance/linked_list_appending.png)
- **precomputation:** perform calculations in advance so as to avoid doing them at mission critical times  
example: if a function needs binomial coefficients at runtime, instead precompute the coefficients (Pascal's triangle) for a certain size when initializing and perform table look-up at runtime  
![](./media/performance/pascals_triangle.png)
  ```cpp
  // function used for precomputation
  int choose(int n, int k)
  {
      if (n < k) return 0;
      if (n == 0) return 1;
      if (k == 0) return 1;
      return choose(n - 1, k - 1) + choose(n - 1, k);
  }
  ```
- **compile-time initialization:** store values of constants during compilation saving work during execution time  
example: store hardcoded binomial coefficients from previous example in a 2D array  
large static tables can be created using metaprogramming or if you don't want to copy the structure then implement it in macros so compiler does the work of computing them
  ```cpp
  printf("int choose[10][10] = {\n");
  for (int a = 0; a < 10; ++a)
  {
      initialize_choose();
      printf("  {");
      for (int b = 0; b < 10; ++b)
      {
          printf("%3d, " choose[a][b]);
      }
      printf("  },\n");
  }
  printf("};\n");
  ```
- **caching:** store results that have been accessed recently so that the program need not compute them again  
example: to get hypotenuse of a right-angled triangle `sqrt(A^2 + B^2)` but square-root operator is expensive so cache the previous results, realistically cache size will be larger to increase hit rate
  ```cpp
  double hypotenuse(double A, double B)
  {
      if (A == cached_A && B == cached_B)
      {
          return cached_h;
      }

      cached_A = A;
      cached_B = B;
      cached_h = sqrt(A * 2 + B * 2);

      return cached_h;
  }
  ```
- **sparsity:** avoid storing and computing on zeroes, *the fastest way to compute is not to compute at all*  
example: matrix-vector multiplication of a sparse matrix, dense matrix-vector multiplication performs `n^2` scalar multiplications but only 14 entries are non-zero  
![](./media/performance/matrix_vector_multiplication_1.png)  
we can check if one of the arguments is zero, but this needs to check every matrix entry  
**compressed sparse row:** a sparse matrix is compressed into a `rows` (storing offset to that row in `cols` array), `cols` array (storing positions with non-zero values) and `vals` array with actual matrix position values  
to get a row's size just take the difference of current & next row offsets, we have 6th row here so we can calculate size of last row  
`nnz` is number of non-zero elements, storage is `O(n + 2 * nnz)` instead of `O(n^2)` and multiplications are `nnz` instead of `n^2`  
![](./media/performance/compressed_sparse_row.png)  
  ```cpp
  typedef struct
  {
      int n, nnz;
      int *rows;     // size n
      int *cols;     // size nnz
      double *vals;  // size nnz
  } sparse_matrix_t;

  void spmv(sparse_matrix_t *A, double *x, double *y)
  {
      for (int i = 0; i < A->n; i++)
      {
          y[i] = 0;
          for (int k = A->rows[i]; k < A->rows[i + 1]; k++)
          {
              int j = A->cols[k];
              y[i] += A->vals[k] * x[j];
          }
      }
  }
  ```

[continue](https://youtu.be/H-1-X9bkop8?list=PLUl4u3cNGP63VIBQVWguXxZZi0566y7Wf&t=2337)