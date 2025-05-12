# algorithms
- [intro](#intro)
- [dynamic array](#dynamic-array)

## todo <!-- omit from toc -->
- [cheatsheet](https://github.com/ljeng/cheat-sheet/blob/master)
- [big-O cheatsheet](https://www.bigocheatsheet.com/)
- [latency numbers](https://gist.github.com/jboner/2841832)

## links <!-- omit from toc -->
- [[lectures] intro to algorithms (MIT 2020)](https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-spring-2020/)

## intro
- **induction:**
  - technique to prove algorithm correctness and establish recurrence relations
  - involves two steps:
    - base case: prove statement is true for smallest input
    - inductive step: if statement is true for some `k` then prove its true for `k+1` as well
- **asymptotic complexity:**
  - algorithm's worst-case computational & space complexity as input `n` scales
  - ![](./media/algorithms/complexity_chart.png)
  -  
    |                  | access | search | insert | delete | space  |
    | ---------------- | ------ | ------ | ------ | ------ | ------ |
    | array            | `O(1)` | `O(n)` | `O(n)` | `O(n)` | `O(n)` |
    | stack, queue     | `O(n)` | `O(n)` | `O(1)` | `O(1)` | `O(n)` |
    | singly/doubly LL | `O(n)` | `O(n)` | `O(1)` | `O(1)` | `O(n)` |
    |                  |        |        |        |        |        |
    |                  |        |        |        |        |        |
    |                  |        |        |        |        |        |
    |                  |        |        |        |        |        |
    |                  |        |        |        |        |        |
    |                  |        |        |        |        |        |
    |                  |        |        |        |        |        |
- **tail-call recursion:**
  - recursive call is the last operation in the function before returning
  - allows compiler to reuse current stack frame (so no stack overflow)
  - if recursive call needs current output, pass it as argument
- interface is the specification (what), while data structure is the implementation (how)
- **augmentation:**
  - adding extra information to data structure to support new operations efficiently
- **amortization:**
  - averaging cost of an operation over a sequence of operations
  - average cost of expensive operation done infrequently is low

## dynamic array
- **static array:**
  - assume array always needs to be full
  - insert/delete needs reallocation and copying over all elements
- **linked list:**
  - each element stored in node which points to next node
  - can manipulate sequence by simply relinking pointers
  - augment by maintaining length & tail node pointer along with head
    - get size & get/set/insert last operations `O(1)`
- **dynamic array:**
  - allocate extra space so no reallocation with every dynamic operation
  - when `size == capacity`, allocate (& copy over to) new array of size
    - `capacity + k`: frequent reallocations (every `k` inserts) but less wasted space
    - `capacity * k`: fewer allocations (amortized `O(1)` insertion) but potentially more wasted space
  - similarly resizing on `size == capacity/2` can lead to multiple alloc dealloc 
- 
  | operation           | static | LL     | dynamic |
  | ------------------- | ------ | ------ | ------- |
  | get/set at          | `O(1)` | `O(n)` | `O(1)`  |
  | insert/delete first | `O(n)` | `O(1)` | `O(n)`  |
  | insert/delete last  | `O(n)` | `O(n)` | `O(1)`  |
  | insert/delete at    | `O(n)` | `O(n)` | `O(n)`  |