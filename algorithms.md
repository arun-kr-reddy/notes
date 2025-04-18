# algorithms
- [introduction](#introduction)
- [dynamic array](#dynamic-array)

## todo <!-- omit from toc -->
- [cheatsheet](https://github.com/ljeng/cheat-sheet/blob/master)
- [big-O cheatsheet](https://www.bigocheatsheet.com/)
- [latency numbers](https://gist.github.com/jboner/2841832)

## links <!-- omit from toc -->
- [[lectures] intro to algorithms (MIT 2020)](https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-spring-2020/)

## introduction
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
- interface is the specification (what) while data structure is the implementation (how)
  - two main interfaces: set & sequence
  - two main data structure approaches: arrays, pointer-based

## dynamic array
- static array
- linked list
- dynamic atrray
  - resizing by `+k` vs `*k`
- amortization
