# performance
- [introduction](#introduction)

## links  <!-- omit from toc -->

## todo  <!-- omit from toc -->
- [performance engineering](https://www.youtube.com/playlist?list=PLUl4u3cNGP63VIBQVWguXxZZi0566y7Wf)
- SIMD - NEON & Hexagon DSP
  - intrinsic or assembly instructions
- [gpu programming](http://www.cse.iitm.ac.in/~rupesh/teaching/gpu/jan22/)
- [compiler explorer](https://godbolt.org/)
- [an even easier introduction to CUDA](https://developer.nvidia.com/blog/even-easier-introduction-cuda/)
- [Amdahl's law paper](https://inst.eecs.berkeley.edu//~n252/paper/Amdahl.pdf)

## introduction
- **iron law of processor performance:** trade-off between complexity and the number of primitive instructions that processors use to perform calculation  
  ![](./media/performance/iron_law.png)
- **Amdahl's law:** overall performance improvement gained by optimizing a single part of a system is limited by the fraction of time that the improved part is actually used  
  ![](./media/performance/amdahls_law.png)  
  `Slatency` theoretical speedup  
  `s` speedup of optimized part  
  `p` fraction of time