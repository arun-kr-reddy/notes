- [introduction](#introduction)
- [search](#search)
- [models of computation](#models-of-computation)
- [sorting](#sorting)
- [heap](#heap)
- [binary search trees](#binary-search-trees)
- [AVL tree (balanced BST)](#avl-tree-balanced-bst)

# links  <!-- omit from toc -->
- [introduction to algorithms](https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-fall-2011/) ([recitation files](https://courses.csail.mit.edu/6.006/fall11/notes.shtml))
- [big O notation](https://adrianmejia.com/how-to-find-time-complexity-of-an-algorithm-code-big-o-notation/ )

# introduction
- **data structures:** organize & store data for efficient access & manipulation  
  **algorithm:** efficient procedure to solve a large-scale problem
- **asymptotic complexity:** estimate algorithm's worst-case computational complexity as input scales  
  ![](./media/algorithms/time_complexity.png)
- **divide & conquer algorithm:** break down a problem into smaller subproblems, solve them recursively then combine the solutions
- **tail call recursion:** recursive call is the last action before returning  
  if next step needs current step result then pass it as arg  
  compiler will reuse current function's stack frame (prevent stack overflow)  
  example: binary search recursive call directly returns search position
  ```cpp
  int binarySearch(int arr[], int low, int high, int x)
  {
      if (high >= low)
      {
          int mid = low + (high - low) / 2;

          if (arr[mid] == x)
              return mid;

          if (arr[mid] > x)  // left half
              return binarySearch(arr, low, mid - 1, x);
          else  // right half
              return binarySearch(arr, mid + 1, high, x);
      }

      return -1;
  }
  ```

# search
- **peak:** position whose value is `>=` (or `>`) all its neighbors, aka local maximum  
  with `>=` peak will always exist since (increasing ⟶ decreasing/equal) transition must take place at some index (edges for sorted arrays)  
  but with `>` peak might not exist (all array elements same value)
- **1D peak finding:**  
  ![](./media/algorithms/1d_peak.png)
  - **linear:** walk across all elements  
    worst case `θ(n)` if last element peak
  - **divide & conquer:** start at midpoint then pick higher neighbor's half  
    if neither higher then midpoint is the peak
    ```
    each recursion divides the input size by half:
    T(n) = T(n/2) + θ(1)          ⟶ θ(1) for midpoint comparison
         = T(n/4) + θ(1) + θ(1)
         .
         .
         = T(n/(2^k)) + k * θ(1)

    base case one element: T(1) = θ(1)
    n/(2^k) = 1
    k = log2(n)

    T(n) = T(1) + log(n) * θ(1)
         = (log(n) + 1) * θ(1)
         ≈ θ(log(n))
    ```
- **2D peak finding:**  
  ![](./media/algorithms/2d_peak.png)
  - **greedy ascent:** from midpoint keep moving in the direction of highest neighbor until peak is found  
    worst-case `θ(n * m)` if all elements traversed  
    ![](./media/algorithms/2d_greedy_ascent.png)
  - **divide & conquer 1:** find 1D peak `(i, j)` in middle column (`j == m/2`) and then find 1D peak in that row (`i`)  
    but 2D peak may not exist on row `i`  
    efficient (`θ(log(m) * log(n))`) but incorrect algorithm  
    example: 12 is a column 1D peak and in that row 14 is the 1D peak but is not a 2D peak  
    ![](./media/algorithms/2d_divide_conquer_1.png)
  - **divide & conquer 2:** find (global) maximum `(i, j)` in middle column (`j == m/2`)  
    then pick higher left/right neighbor's half, 2D peak if neither higher  
    ![](./media/algorithms/2d_divide_conquer_2.png)
    ```
    T(n, m) = T(n, m/2) + θ(n)          ⟶ θ(n) for global max
            = T(n, m/4) + θ(n) + θ(n)
            .
            .
            = T(n, m/(2^k)) + k * θ(n)

    base case one row: T(n, 1) = θ(n)
    m/(2^k) = 1
    k = log(m)

    T(n) = T(n, 1) + log(m) * θ(n)
         = (log(m) + 1) * θ(n)
         ≈ θ(n * log(m))                ⟶ worst case if matrix corner peak
    ```

# models of computation
- algorithm is a computational procedure for solving a problem
  **model of computation:** specifies what operations an algorithm is allowed and the its associated cost (time, space, etc)  
  total cost of an algorithm is sum of operation costs  
  ![](./media/algorithms/algorithm_analog.png)
- **example: random access machine:** RAM is modeled by big array of registers (one word each)  
  in `θ(1)` time an algorithm can load `θ(1)` words, do `θ(1)` computations and then store `θ(1)` words  
  is realistic & powerful, so used to implement abstractions
  example: used for assembly programming  
  ![](./media/algorithms/random_access_machine.png)
- **example: pointer machine:** dynamically allocated objects with each object having `θ(1)` fields (word or pointer)  
  pointer machine can be implemented in RAM (LL in C) hence is weaker but is simpler for programmer  
  example: object oriented programming  
  ![](./media/algorithms/pointer_machine.png)  
this can be implemented in RAM where pointer becomes index in array
- **python model:** either mode of thinking: array `*i = *(i + 1)` or objects `x = x.next`  
  either of the operations will take `θ(1)` time
- **document distance:** similarities between two text documents, example: similarities between search phrase and webpage for search results  
  think of document (`D`) as a vector of words (`w`) with whitespace & punctuations ignored, where `D[w]` gives frequency of word `w`  
  ![](./media/algorithms/document_distance.png)  
  document distance can be defined as dot product of the two vectors  
  ![](./media/algorithms/document_distance_equation_1.png)  
  but this is not scale-invariant (large documents with any % similarity will score higher than smaller documents)  
  fixed through normalization by dividing by the length of documents  
  ![](./media/algorithms/document_distance_equation_2.png)  
  recall that dot product is `x . y = |x| |y| cosθ`  
  arccosine (inverse function of cosine) of previous equation to get geometric representation (in radians)  
  ![](./media/algorithms/document_distance_equation_3.png)  
  split each document into words ⟶ count word frequencies in document vectors -> compute dot product and divide  
  if a word shows up only in one vector then its respective dot product term is zero, so only iterate through shorter vector

# sorting
- **sorting:** ordering data in an increasing/decreasing manner according to some linear relationship among the data items  
  useful for obvious usecases like find the median or binary search and not-so-obvious usecases like finding duplicates during data compression
- **insertion sort:** insert key `A[j]` into the (already sorted) sub-array `A[1 ... j-1]` by pairwise-swaps down to its correct position  
  ![](./media/algorithms/insertion_sort.png)  
  ![](./media/algorithms/insertion_sort_example.png)  
  we have `θ(n)` steps (indexes), for each step `θ(n)` pairwise compare-and-swap operations  
  example: average `n/2` swaps per step for reverse-sorted list  
  total `θ(n^2)` compares & `θ(n^2)` swaps, for primitives compare & swap take `θ(1)` each  
  but comparing other data structures could be more complex
  - **binary insertion sort:** use binary search to find the correct position  
    useful when compare complexity is much higher than swap complexity, cost of pairwise-swaps remains same (`θ(n)` per step)  
    example: for sorting strings each compare would be `θ(n)` (& swap `θ(1)`)  
    per step insertion sort `θ(n) * θ(n) + θ(1) * θ(n) = θ(n^2)`  
    but binary insertion sort `θ(n) * θ(log(n)) + θ(1) * θ(n) ≈ θ(n * log(n))`
- **merge sort:** recursively divide input array into halves and sort those sub-arrays and merge them back to obtain the sorted array  
  ![](./media/algorithms/merge_sort.png)  
  **two-finger approach:** one finger is pointing to the bottom (smallest element) in left sub-array & other finger right  
  compare two elements and copy smaller value to final merged array and keep going until sub-arrays are merged  
  ![](./media/algorithms/two_finger_algorithm.png)  
  `θ(1)` for splitting input and `θ(n)` for merging two `n/2` sub-arrays  
  `T(n) = θ(1) + 2 * T(n/2) + θ(n) = 4 * T(n/4) + θ(n) + θ(n) = ... = 2^k * T(n/(2^k)) + k * θ(n)`  
  base case sub-array with two elements `T(2) = θ(1)` and `n/(2^k) = 2` ⟶ `k = log(n/2)`  
  `T(n) = n/2 * T(2) + log(n/2) * θ(n) ≈ θ(n * log(n))`  
  merge sort needs `θ(n)` auxiliary space, but insertion sort only needs `θ(1)` (for temp variable for swapping)  
  one optimization is reusing memory for halves to reduce memory usage by half (but still `θ(n)`)
- **recursion tree:** visualize flow execution flow of a recursive function and get its complexity by adding up the costs of each level  
  each node is the cost of operations done for child nodes (`T(n/2)`), for merge-sort it is split & merge `θ(1) + θ(n)`  
  `n` elements are being merged per level for total of `1 + log(n)` levels (root level + size halves per level)  
  so `θ(n) * θ(1+log(n)) ≈ θ(n * log(n))`  
  ![](./media/algorithms/merge_sort_tree.png)

# heap
- **priority queue:** special type of queue in which each element is associated with a priority (key) value  
  elements are dequeued/extracted on the basis of their key (higher key elements served first)  
  elements are inserted in a position based on its key value  
  supported operations: `insert`, `max` (return by peeking max key element), `extract_max` (return and remove) and `update_key` (of an element)
- **heap:** array structure visualized as a nearly complete binary tree  
  max-heap property is that the key of a node is `>=` keys of its children (min-heap analogous)  
  ![](./media/algorithms/heap_visualization_1.png)  
  ![](./media/algorithms/heap_visualization_2.png)  
  ![](./media/algorithms/heap_min_max.png)  
  for a node at index `i` (assuming one-indexed array)
  - tree root node is the first element `i = 1`
  - `parent(i) = i/2`
  - `left(i) = 2 * i`
  - `right(i) = 2 * i + 1`
- heap can be used for sorting (reverse-sorted with max-heap) by repeatedly extracting the root node  
  just two operations are required to implement `insert`, `extract_max` & `heapsort`:
  - `build_max_heap`: produce max-heap from unordered array
  - `max_heapify` correct a single violation of the heap property at a subtree's root
- **max_heapify:** assumes that child subtrees (`left(i)` & `right(i)`) are max-heaps at the start  
  key value of the root (`A[i]`) violating max-heap property is swapped (`θ(log(n))`) with the child with the maximum key value  
  recurse process is repeated until the node involved maintains the property  
  ![](./media/algorithms/heapify_example.png)  
  `θ(log(n))` since only one violation and number of levels is `log(array_size)`, so worst case root node turns to leaf node
  ```
  l = left(i) 
  r = right(i) 
  if (l <= heap-size(A) and A[l] > A[i])
      then largest = l else largest = i 
  if (r <= heap-size(A) and A[r] > A[largest])
      then largest = r 
  if largest = i
      then exchange A[i] and A[largest]  
      max_heapify(A, largest)
  ```
- **build_max_heap:** any given array can be transformed to a max-heap by repeatedly using `max_heapify`  
  total num nodes till `n` would be `1 + 2 + 4 + ... + 2^n`  
  in binary sum will have last `n` bits set, same as `2^(n+1) - 1` (total num nodes doubles per level)  
  so last `n/2` elements are all leaves and leaves are already max-heaps  
  so iterate from `n/2` to `1`
  ![](./media/algorithms/heap_build_example.png)  
  `n/2` leaves & `log(n)` levels, by recursion tree analysis `θ(n * log(n))`  
  observe that `max_heapify` takes `θ(1)` for nodes one level above leaves and in general `θ(l)` for nodes `l` levels above leaves  
  and level one has `n/4` nodes, `n/8` for one above that and so on till one node at `log(n)` level  
  so total work in loop is `n/4 * (1 * c) + n/8 * (2 * c) + ... + 1 * (log(n) * c)`  
  since every level has power-of-two number of nodes `n/4 = 2^k`  
  `c * 2^k (1/(2^0) + 2/(2^1) + ... + (k + 1)/(2^k))`, the series in the bracket is a convergence series bounded by three (constant)  
  so `c * 2^k * θ(1) = c * n/4 ≈ θ(n)`
- **heap sort:** first step takes `θ(n)`, last one takes `θ(log(n))` and ones in-between `θ(`n`)`  
  all steps after first one will be repeated `n` times, so `θ(n * log(n))`  
  ![](./media/algorithms/heap_sort.png)
  - build max-heap from input array
  - `A[1]` will be the maximum element  
  - swap `A[n]` & `A[1]`, now max element is at the end of the array
  - discard node `n` from heap (by decrementing heap-size)
  - new root (old `A[n]`) may violate max heap property, but its children are max heaps  
    run `max_heapify` to fix this
  - goto step two unless heap is empty

# binary search trees
- **binary search tree:** each node `x` has a key and three pointers: parent (except root) and maybe left & right child  
  for any node `x` all nodes `y` in the left subtree of `x` `key(y) <= key(x)` and opposite for right tree `key(y) >= key(x)`  
  ![](./media/algorithms/bst_property.png)  
  example:  
  ![](./media/algorithms/bst.png)  
  `insert(val)` is done by following left & right pointers from root till position is found  
  ![](./media/algorithms/bst_insertion.png)  
  `find(val)` follow left & right pointers until value found or `NULL` hit  
  `find_min()` follow left till hit a leaf and right for `find_max()`  
  if `h` is height of the tree, all above operations takes `θ(h)`  
- **next larger (successor):** go to right and `find_min`  
  if no right then go up (parent) until a right found then `find_min`  
  ![](./media/algorithms/bst_successor.png)  
- **delete:** leaf node deleted directly  
  ![](./media/algorithms/bst_delete_1.png)  
  for node with one child just swap then delete  
  ![](./media/algorithms/bst_delete_2.png)  
  for node with both children swap with `next_larger(x)` then delete  
  ![](./media/algorithms/bst_delete_3.png)
- **augmented BST:** add subtree size to each node, modify this during insert & delete  
  useful to get num nodes `>=` or `<=` a certain value in `θ(1)` time  
  similarly to get min/max in `θ(1)` time by storing subtree min/max  
  ![](./media/algorithms/bst_augmented.png)  
  example: get `num_nodes <= 79` in above image  
  `79 > 49` so add left subtree size plus one (for `49`) and move to right  
  `79 == 79` so add one and left subtree size  
  ![](./media/algorithms/bst_augmented_example.png)  
  update value after insert/delete by go back up till the root while updating intermediate nodes

# AVL tree (balanced BST)
- height of a node is length (num link edges) of longest downward path to a leaf, decides the time complexity of BST operations  
  `height(x) = max(height(left(x)), height(right(x)))`  
  assume height of `NULL` children to be `-1` for convenience (useful for AVL check)  
  example: single node will have `max(-1, -1) + 1 = 0` height  
  ![](./media/algorithms/bst_node_length.png)  
  depth is length of upward path to root
- **balanced vs unbalanced:** balanced has nodes distributed evenly across levels, height `log(n)` so all operations `θ(log(n))`  
  unbalanced has nodes skewed to one side (uneven distribution), `θ(h)`  
  worst case if root is the smallest element (sorted data) BST forms a linked list, height `n` so `θ(n)`  
  ![](./media/algorithms/bst_balanced.png)
- **Adel’son-Vel’skii & Landis (AVL) tree** requires heights of left & right children of every node to differ by at-most `±1`  
  `|height(left) - height(right)| <= 1`  
  each node stores its height (augmented BST)  
  ![](./media/algorithms/avl_property.png)  
  **rotation:** change binary tree structure without interfering with order of elements  
  in left-rotate root moves left  
  here `β` stays the nodes between `A` & `B`  
  ![](./media/algorithms/avl_rotation.gif)
- **AVL insert:** start with simple BST insert and then work your way up restoring AVL property (and updating heights)  
  assume `x` is lowest node violating AVL and is right-heavy  
  dash for balanced, arrow for heavy & double arrow for double-heavy (one extra than expected)
  - if `x`'s right child right-heavy or balanced  
    rotate child node in the direction reverse of heavy path (left here)  
    heavy path from parent to grand-child straight line  
    ![](./media/algorithms/avl_insertion_1.png)
  - else do rotate child in reverse of its heavy direction (right here) to get straight line  
    then reverse rotate (left here) new child to get balanced subtree  
    heavy path zig-zags from parent to grand-child  
    ![](./media/algorithms/avl_insertion_2.png)
- **example: AVL insert:** insert 23 (single rotation) then 55 (double rotation)  
  ![](./media/algorithms/avl_insertion_example.png)
- **AVL sort:** insert `n` items (`n * θ(log(n))`) then in-order traversal (`θ(n)`)
- abstract data type is the interface specification (supported operations) like `insert`, `delete`, `find_min`, `successor` & `predecessor`  
  example: priority queue ADT needs `insert`, `delete` & `find_min`  
  data structure is the algorithm for each operation  
  there are many possible DSs for one ADT  
  example: priority queue can be implemented using heap or AVL tree, or sub-optimally sorted array

[continue](https://www.youtube.com/watch?v=Nz1KZXbghj8&list=PLUl4u3cNGP61Oq3tWYp6V_F-5jb5L2iHb&index=12)