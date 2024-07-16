# table of contents  <!-- omit from toc -->
- [introduction](#introduction)

# links  <!-- omit from toc -->
- [[lectures] analysis of algorithms](https://www3.cs.stonybrook.edu/~skiena/373/videos/)
- [big O notation](https://adrianmejia.com/how-to-find-time-complexity-of-an-algorithm-code-big-o-notation/)

# todo  <!-- omit from toc -->
- document distance sorted vector add notes
- go through document distance variations
- [quick sort](https://www.youtube.com/watch?v=XE4VP_8Y0BU)
- [leetcode 75](https://leetcode.com/studyplan/leetcode-75/)
- [connected component labelling](https://en.wikipedia.org/wiki/Connected-component_labeling)

# introduction
- efficient procedures for solving problems on large inputs (like human genome)
- **asymptotic complexity:** is used for (worst-case) estimation of computational complexity of algorithms  
example: for `f(n) = n^2 + 3n` as `n` grows `n^2` grows at a much faster rate than `3n` rendering it insignificant for large values of `n`, so `f(n)` is said to be asymptotically equivalent to `n^2`  
![](./media/algorithms/time_complexity.png)  
  ```
  // sequential = statement1 + statement2
  statement1;
  statement2;

  // conditional = max(condition1, condition2)
  if (flag)
      condition1;
  else
      condition2;

  // linear loop = iterations * (statement1 + statement 2)
  for (int i = 0; i < iterations; i++)
  {
      statement1;
      statement2;
  }

  // nested loop = iterations_i * (statement1 + j * statement2);
  for (int i = 0; i < iterations_i; i++)
  {
      statement1;
      for (int j = 0; j < iterations_j; j++)
      {
          statement2;
      }
  }

  // logarithmic loop = log2(iterations) * (statement1 + statement2)
  for (int i = iterations; i >= 1; i /= 2)
  {
      statement1;
      statement2;
  }
  ```
- **divide & conquer algorithm:** is a algorithm design paradigm that recursively breaks down a problem into sub-problems of the same or related type until they become simple enough to be solved directly  
![](./media/algorithms/divide_and_conquer.png)