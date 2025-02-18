- [algorithms](./algorithms.md)
- [computer architecture](./computer_architecture.md)
- [computer vision](./computer_vision.md)
- [cplusplus](./cpp.md)
- [life](./life.md)
- [maths](./maths.md)
- [operating system](./operating_system.md)
- [performance](./performance.md)
- [programming](./programming.md)
- [tools](./tools.md)

# todo
- **C++:**
  - [cpp core guidelines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines##main)
  - [lost art of struct packing](http://www.catb.org/esr/structure-packing/)
  - [memory order](https://en.cppreference.com/w/c/atomic/memory_order)
  - [mix C & C++](https://isocpp.org/wiki/faq/mixing-c-and-cpp##:~:text=Just%20declare%20the%20C%20function,int)
    - `cstdio` vs `stdio.h` in C++
  - [efficient c++](https://embeddedgurus.com/stack-overflow/category/efficient-cc/)
  - [MSVC init memory](https://stackoverflow.com/questions/127386/what-are-the-debug-memory-fill-patterns-in-visual-studio-c-and-windows)
  - [memory ordering](https://en.cppreference.com/w/cpp/atomic/memory_order)
  - [templates FAQ](https://isocpp.org/wiki/faq/templates)
  - why static initialized to 0
  - stack canary
  - [embedded C questions](https://rmbconsulting.us/publications/a-c-test-the-0x10-best-questions-for-would-be-embedded-programmers/)
  - [named lambda](https://stackoverflow.com/questions/51760019/why-would-one-write-a-c-lambda-with-a-name-so-it-can-be-called-from-somewhere)
  - iomanip
  - std::any
  - floating point to fixed point
  - hardware abstraction layer
- **algorithms:**
  - data structs: array, LL, stack, queue, hash table, tree, graph, heap, tries, union find
  - algorithms: binary search, DFS, BFS, dynamic prog, quick sort, merge sort, bucket sort, topological sort, backtracking, bit operations
  - patterns: sliding window, two pointers, prefix sums, heaps, dynamic programming, backtracking, bit manipulation, cycle detection, intervals, greedy, binary search, DFS, BFS, stack, monotonic stack, multi-source BFS, minimum spanning tree, tries
  - leetcode tips: for each question write down approach in 3-4 lines, pseudocode, time complexity
  - [connected component labelling](https://en.wikipedia.org/wiki/Connected-component_labeling)
  - [postfix vs infix](https://www.geeksforgeeks.org/postfix-to-infix/)
  - [every programmer should know](https://github.com/mtdvio/every-programmer-should-know)
  - [arden dertat 21 questions](https://gist.github.com/gabhi/2b39fdd74dfde98d6b11)
- **computer architecture:**
  - [modern microprocessors](https://www.lighterra.com/papers/modernmicroprocessors/)
  - [Hamming code in software](https://www.youtube.com/watch?v=b3NxrZOu_CE)
  - [Hamming code in hardware](https://www.youtube.com/watch?v=h0jloehRKas)
  - Intel Itanium
  - [systolic arrays](https://safari.ethz.ch/digitaltechnik/spring2018/lib/exe/fetch.php?media=1982-kung-why-systolic-architecture.pdf)
  - [cache coherency protocols](https://redis.io/glossary/cache-coherence/)
  - [computer architecture (ETHZ 2019) (cover 19b onwards)](https://safari.ethz.ch/architecture/fall2019/doku.php?id=schedule)
  - optane persistent memory (phase change memory)
  - nvidia denver
  - processing in memory
  - [memory ordering](https://www.google.com/search?q=memory+ordering&rlz=1C1GCEA_enIN1108IN1108&oq=memory&gs_lcrp=EgZjaHJvbWUqBggAEEUYOzIGCAAQRRg7MgwIARBFGDkYsQMYgAQyDQgCEAAYgwEYsQMYgAQyCggDEAAYsQMYgAQyBwgEEAAYgAQyBggFEEUYPDIGCAYQRRg8MgYIBxBFGDzSAQgxNjc2ajBqN6gCALACAA&sourceid=chrome&ie=UTF-8)
  - javed questions: ARM arch (32 vs 64), what happens if interrupts come, buddy allocator, process vs thread descriptor, hard vs soft interrupts
- **operating systems:**
  - [IPC extra](https://www.cse.iitb.ac.in/~mythili/os/notes/notes-ipc.txt)
  - [semaphore extra](https://www.cse.iitb.ac.in/~mythili/os/references/LittleBookOfSemaphores.pdf)
  - [programming groundup extra](https://www.cse.iitb.ac.in/~mythili/os/references/ProgrammingGroundUp.pdf)
  - multi-threading programming using pthread & cpp threads
  - IPC using cpp
  - priority inversion
  - [`brk` & `sbrk`](https://stackoverflow.com/questions/6988487/what-does-the-brk-system-call-do)
  - `mmap` system class
- **maths:**
  - [essence of calculus](https://www.3blue1brown.com/topics/calculus)
  - [essence of linear algebra](https://www.3blue1brown.com/topics/linear-algebra)
  - [differential equations](https://www.3blue1brown.com/topics/differential-equations)
  - [maths for CS](https://ocw.mit.edu/courses/6-042j-mathematics-for-computer-science-fall-2010/)
  - [neural networks](https://www.3blue1brown.com/topics/neural-networks)
  - [single variable calculus](https://www.youtube.com/playlist?list=PL590CCC2BC5AF3BC1)
- **computer vision:**
  - [feature detection & matching algos](https://medium.com/data-breach/introduction-to-feature-detection-and-matching-65e27179885d)
  - [stanford CV tutorial](https://ai.stanford.edu/~syyeung/cvweb/tutorials.html)
  - FastCV, OpenCV
  - edge & blur artifact detection
  - [time of flight](https://www.sony-semicon.com/en/technology/industry/tof.html)
  - [CV ML resources](https://www.reddit.com/r/MachineLearning/comments/i9kztq/d_hidden_gems_and_underappreciated_resources/)
- **performance:**
  - [[playlist] performance engineering of software systems](https://ocw.mit.edu/courses/6-172-performance-engineering-of-software-systems-fall-2018/)
  - [gpu programming](https://www.olcf.ornl.gov/cuda-training-series/) ([playlist](https://www.youtube.com/playlist?list=PL6RdenZrxrw-zNX7uuGppWETdxt_JxdMj))
    - [wen mei hwu lectures](https://www.youtube.com/playlist?list=PLzn6LN6WhlN06hIOA_ge6SrgdeSiuf9Tb)
    - [parallel patterns](https://link.springer.com/chapter/10.1007/978-1-4842-5574-2_14)
    - kernel chaining
  - SIMD - NEON & Hexagon DSP
    - intrinsic or assembly instructions
    - [halide library](https://halide-lang.org/)
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
  - concurrent vs parallel
- **tools:**
  - [useful tools](https://cs.baylor.edu/~donahoo/tools/)
  - [undo (almost) anything with git](https://github.blog/2015-06-08-how-to-undo-almost-anything-with-git/)
  - [regex basics](https://www.youtube.com/watch?v=sa-TUpSx1JA)
    - negative look ahead
  - linux commands (from archived ?)
  - gdb (check on cppcon)
  - gtest (check on cppcon)
  - gprof (check on cppcon)
  - valgrind (check on cppcon)
  - make
  - thread sanitizers
  - basic linux commands
  - bash scripting
  - batch scripting
  - python scripting
- **programming:**
  - [[playlist] SICP](https://ocw.mit.edu/courses/6-001-structure-and-interpretation-of-computer-programs-spring-2005/) ([notes](https://mk12.github.io/sicp/lecture/1a.html))
  - [iterative process for fibonacci & towers of hanoi](https://en.wikipedia.org/wiki/Tower_of_Hanoi#Iterative_solution)
  - [why is lisp different](https://www.paulgraham.com/diff.html)
  - [first BillG review](https://www.joelonsoftware.com/2006/06/16/my-first-billg-review/)
  - [SOLID principles](https://www.youtube.com/watch?v=zHiWqnTWsn4)
  - [design patterns](https://www.youtube.com/playlist?list=PLrhzvIcii6GNjpARdnO4ueTUAVR9eMBpc)
    - [when to use DP](https://www.linkedin.com/feed/update/urn:li:activity:7202356498864250880)
  - system design
  - code complete
  - clean code
  - pragmatic programmer
- **misc:**
  - [indian economy](https://web.archive.org/web/20190816184602/http://www.iitd.ac.in/CEAIITD/index.html)
  - [embedded](https://www.youtube.com/playlist?list=PLPW8O6W-1chwyTzI3BHwBLbGQoPFxPAPM)
  - [CS courses](https://github.com/Developer-Y/cs-video-courses/tree/master)
  - protobuf
- **SKL list:**
  - **C:** compiler derivatives, GDB
  - **C++:** metaprogramming, lambdas, C++ multithreading, design patterns(okhravi)
  - **OS & embedded:** IPC, file systems, memory protection
  - **domain specific:** ML basics (complete ancient secrets)
  - **optimization:** vulkan, cuda (oakridge), perf engineering (MIT), compilers (alex aiken)
  - **misc:** basics of python & SQL
# misc
- **build:**
  ```sh
  # windows
  cd .\build\windows\
  cmake ..\.. -G "Visual Studio 17 2022"

  # linux
  cd ./build/linux/
  cmake ../..
  make
  ./main_exe
  ```
- **symbols:**
  ```sh
  ⟵  ⟶  ⟷ ↑ ↓  ## arrows
  ±                ## plus minus
  :                ## such that
  ∀                ## for all
  ∃                ## there exists
  ∴                ## therefore
  ∵                ## since
  ⊂                ## subset of
  ∈                ## belongs to
  ∪                ## union
  ⇒                ## implies that
  ⇔                ## if and only if
  ≈                ## approximately equal
  ≡                ## equivalent
  ∝                ## proportional
  ∞                ## infinity
  ∠                ## angle
  °                ## degree
  √                ## root
  ∆                ## delta
  ∑                ## sigma
  α                ## alpha
  β                ## beta
  γ                ## gamma
  δ                ## delta
  ε                ## epsilon
  θ                ## theta
  κ                ## kappa
  λ                ## lambda
  μ                ## mu
  π                ## pi
  σ                ## sigma
  τ                ## tau
  φ                ## phi
  ψ                ## psi
  ω                ## omega
  ⦻               ## correlation
                   ## invisible character
  ```