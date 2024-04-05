# performance
- [introduction](#introduction)

## links  <!-- omit from toc -->


## todo  <!-- omit from toc -->
- [performance engineering (MIT 2018)](https://ocw.mit.edu/courses/6-172-performance-engineering-of-software-systems-fall-2018/)
- SIMD - NEON & Hexagon DSP
  - intrinsic or assembly instructions
- [gpu programming (IITM 2022)](http://www.cse.iitm.ac.in/~rupesh/teaching/gpu/jan22/)
- [compiler explorer](https://godbolt.org/)
- [an even easier introduction to CUDA](https://developer.nvidia.com/blog/even-easier-introduction-cuda/)
- [Amdahl's law paper](https://inst.eecs.berkeley.edu//~n252/paper/Amdahl.pdf)
- [Arrayfire](https://github.com/arrayfire/arrayfire)
- [Duff's device](https://en.wikipedia.org/wiki/Duff%27s_device)
- [NEON2SSE](https://github.com/intel/ARM_NEON_2_x86_SSE)
- [SIMD javidx9](https://www.youtube.com/watch?v=x9Scb5Mku1g)
- [SIMD perf tests](https://github.com/ARM-software/meabo)
- [x64 assembly programming & check other playlists](https://www.youtube.com/playlist?list=PLKK11Ligqitg9MOX3-0tFT1Rmh3uJp7kA)

## introduction
- **iron law of processor performance:** trade-off between complexity and the number of primitive instructions that processors use to perform calculation  
![](./media/performance/iron_law.png)
- **Amdahl's law:** overall performance improvement gained by optimizing a single part of a system is limited by the fraction of time that the improved part is actually used  
![](./media/performance/amdahls_law.png)  
`Slatency` theoretical speedup  
`s` speedup of optimized part  
`p` fraction of time