# programming
- [introduction](#introduction)
- [procedures \& processes](#procedures--processes)
- [higher order procedures](#higher-order-procedures)
- [misc](#misc)

## links  <!-- omit from toc -->
- [scheme (lisp dialect) interpreter](https://inst.eecs.berkeley.edu/~cs61a/fa14/assets/interpreter/scheme.html)

## todo  <!-- omit from toc -->
- [[lectures] structure and interpretation of computer programs
](https://ocw.mit.edu/courses/6-001-structure-and-interpretation-of-computer-programs-spring-2005/)
- [iterative process for fibonacci & towers of hanoi](https://en.wikipedia.org/wiki/Tower_of_Hanoi#Iterative_solution)
- dynamic programming
- [why is lisp different](https://www.paulgraham.com/diff.html)
- [first BillG review](https://www.joelonsoftware.com/2006/06/16/my-first-billg-review/)
- [SOLID principles](https://www.youtube.com/watch?v=zHiWqnTWsn4)

## introduction
- ***The key to understanding complicated things is to know what not to look at and what not to compute and what not to think***
- **declarative:** "what is true" knowledge, example: `y` is `sqrt(x)` if `y^2 = x`  
**imperative:** "how to" knowledge, example: square-root by successive averaging of guess `g` & `x/g` until result doesn't change much
- **techniques for controlling complexity:** make building very large programs possible
  - **black-box abstraction:** putting something in a box to suppress details to go ahead & build bigger boxes OR your "how-to" method is an instance of a more general thing, example: fixed point of a function (`f(y) = y`) by successive applying `f(g)` until result doesn't change much can be used for square-root if `f(g)` is average of `g` & `x/g`
  - **conventional interfaces:** agreed upon ways of plugging things together, example: use `(* x (+ a b))` to add numbers, vectors, polynomial, analog signals etc
  - **metalinguistic abstraction:** pick a new design language to highlight different aspect of the system (suppress some kind of details & emphasize others)
- **lisp basics:** for learning any language we need to know three things: primitive elements, means of combination & means of abstraction  
prefix notation `(+ x y)` used uniformly since it is more generic & can take multiple arguments
  ```lisp
  ; primitive elements
  5                            ; 5
  3.14                         ; 3.14
  +                            ; PrimitiveProcedure (functions)

  ; means of combination
  ; composition
  (+ 5 3.14 1)                 ; 9.14
  (+ 4 (* 3 6) 8 2)            ; 32
  ; case analysis
  (define (abs x)              ; (using cond)
    (cond ((< x 0) (- x)))
          ((= x 0) 0)
          ((> x 0) x))
  (define (abs x)              ; (using if for single case)
    (if (< x 0)
        (- x)
        x))

  ; means of abstraction
  (define pi 3.14)             ; pi (define variable)
  (* pi pi)                    ; 9.869604403666765
  (define (square x) (* x x))  ; square (define procedure)
  (square (+ 1 4))             ; 25
  square                       ; (lambda (x) (* x x)) (above define is syntactic sugar for this)
                               ; lambda is used to construct a procedure without a name specified
  ```

## procedures & processes
- **procedure:** is the description/recipe of the process  
**process:** is the result of applying a procedure to arguments  
example: procedure is the blueprint, while process is the actual building construction
- computer science deals with idealized components unlike physical system where one has to worry about constraints of tolerance, approximation & noise  
so for building a large program there isn't much difference between what I can imagine & what I can build
- **formal parameter:** parameter written in function definition  
**actual parameter:** parameter written in function call
- **recursive definitions:** allows you to do infinite computations that go on until something is true
- **example: square root by successive averaging:**
  ```lisp
  ; block structure: package internals inside of definition
  (define (sqrt x)
    (define (try g x)                       ; try
      (if (goodenough? g x)
          g
          (try (improve g x) x)))
    (define (improve guess x)               ; improve
      (average guess (/ x guess)))
    (define (goodenough? g x)               ; goodenough?
      (< (abs (- (square x) x))
         0.001))
    (define (square x) (* x x))             ; square
    (define (average x y) (* (+ x y) 0.5))  ; average
    (try 1 x))                              ; sqrt
  (sqrt 2)                                  ; 1.41421568
  ```
- **substitution model:** when we evaluate a name we substitute its definition in place of the name & then evaluate the resulting definition
  - **combinations:**
    ```lisp
    (define (sos x y) (+ (sq x) (sq y)))  ; sum of squares
    (define (sq a) (* a a))
    (sos 3 4)                             ; 25

    ; substitution model
    (sos 3 4)
    (+ (sq 3) (sq 4))
    (+ (sq 3) (* 4 4))
    (+ (sq 3) 16)
    (+ (* 3 3) 16)
    (+ 9 16)
    25
    ```
  - **special forms:**
    - **conditionals:** evaluate predicate first then the consequent/alternative expression
      ```lisp
      (if <predicate>
          <consequent>
          <alternative>)
      ```
      ```lisp
      (define (+ x y)
        (if (= x 0)
            y
            (+ (-1+ x) (1+ y))))         ; "-1+" is decrement operator & "1+" is the increment operator
                                         ; counting down "x" till "y" is the sum
      (+ 3 4)                            ; 7

      ; substitution model
      (+ 3 4)
      (if (= 3 0) 4 (+ (-1+ 3) (1+ 4)))
      (+ (-1+ 3) (1+ 4))
      (+ (-1+ 3) 5)
      (+ 2 5)                            ; recursion
      (if (= 2 0) 5 (+ (-1+ 2) (1+ 5)))
      (+ (-1+ 2) (1+ 5))
      (+ (-1+ 2) 6)
      (+ 1 6)                            ; recursion
      (if (= 1 0) 6 (+ (-1+ 1) (1+ 6)))
      (+ (-1+ 1) (1+ 6))
      (+ (-1+ 1) 7)
      (+ 0 7)                            ; recursion
      (if (= 0 0) 7 (+ (-1+ 0) (1+ 7)))
      7
      ```
    - lambda expressions, definitions
- **peano arithmetic:** formalizes arithmetic operations on natural numbers & their properties  
there are two ways to add whole numbers, both are recursive definitions but lead to different process types: iteration & recursion  
number of steps is approximation for time it takes to execute & width is the the space that needs to be remembered
  - **iteration:** time `O(x)` (steps increase as `x` increases) & space `O(1)` (same width for any `x`)  
  has all of its state in explicit variables (formal parameters), example: can continue the computation from `(+ 1 6)`  
    ```lisp
    (define (+ x y)
      (if (= x 0)
          y
          (+ (-1+ x) (1+ y))))

    (+ 3 4)
    (+ 2 5)
    (+ 1 6)
    (+ 0 7)
    7
    ```
  - **recursion:** time `O(x)` (steps increase as `x` increases) & space `O(x)` (deferred increments increase as `x` increases)  
  has its state not just in explicit variables but some information belongs to computer as well, example: cannot continue the computation from `(+ 1 4)` without knowing about deferred increments
    ```lisp
    (define (+ x y)
      (if (= x 0)
          y
          (1+ (+ (-1+ x) y))))

    (+ 3 4)
    (1+ (+ 2 4))
    (1+ (1+ (+ 1 4)))
    (1+ (1+ (1+ (+ 0 4))))
    (1+ (1+ (1+ 4)))
    (1+ (1+ 5))
    (1+ 6)
    7
    ```
  - typically, an iterative process passes the answer around as a parameter (the accumulator) in such a way that the last recursive call has no pending operations left  
  ![](media/programming/recursion_vs_iteration.png)
- **perturbation analysis:** making small changes to the program & see how it affects the process
- **example: fibonacci numbers:** time is denoted by each node that the dotted arrow follows `O(fib(x))` & to go back from the tail node  to head node we have to remember all the intermediate nodes so space complexity is the longest path `O(n)`  
this program consists of just two rules: break up something into two parts for `(> n 2)` & reduction for `(< n 2)`
  ```lisp
  ; [0] 1 1 2 3 5 8 13 21 34 . . .
  (define (fib n)
    if(< n 2)
      n
      (+ (fib (- n 1)) (fib (- n 2))))
  ```  
  ![](media/programming/fibonacci.png)
- **example: towers of hanoi:** move `n` disks from tower 'from' to tower `to` using an extra tower `spare`  
suppose we know how to move `n-1` disks, then we move `n-1` disks to `spare`, `n`th disk to `to`, then `n-1` disks on top of `n`th in `to`  
this is possible through recursion because we always count down here & 0 high tower requires no moves
  ```lisp
  (define (move n from to spare)
    (cond ((= n 0) "done")
          (else
            (move (-1+ n) from spare to)     ; move "n-1" disks "from" to "spare" using "to" as spare
            (single move n from to)          ; move "n"th disk "from" to "to"
            (move (-1+ n) spare to from))))  ; move "n-1" disks "spare" to "to" using "from" as spare
  ```  
  ![](media/programming/towers_of_hanoi.png)  

## higher order procedures
- whenever trying to make complicated systems and understand them, it is crucial to divide the things up into as many pieces as I can, each of which I understand separately  
summation of integers & summation of squares have almost the same program with only term differing (`a` & `(square a)`), but we don't like repetition & no repetition means you only write it once (also only understand and debug it once)
  ```lisp
  ; Σ i, for i=a to i=b
  (define (sum_int a b)
    (if (> a b)
      0
      (+ a                       ; term
         (sum_int (1 + a) b))))

  ; Σ i^2, for i=a to i=b
  (define (sum_sq a b)
    (if (> a b)
      0
      (+ (square a)              ; term
         (sum_sq (1 + a) b))))
  ```
- **example: generic summation:** a more general pattern for summation is  
procedures are just another kind of data like numbers  
procedure `sum` is encapsulated in other procedures, improving this will benefit all procedures using it
  ```lisp
  (define (sum term a next b)           ; "term" & next are procedural arguments
    (if (> a b)
      0
      (+ (term a)                       ; "term" produces a value for a given index
         (sum term 
         (next a)                       ; "next" produces the next index
         next 
         b))))
  
  ; sum_int
  (define (sum_int a b)
    (define (identity a) a)
    (sum identity a 1+ b))
  
  ; sum_sq
  (define (sum_sq a b)
    (define (square a) (* a a))
    (sum square a 1+ b))
  ```
- **example: square-root using fixed point:**
  ```lisp
  ; square-root
  (define (sqrt x)
    (fixed_point 
      (lamdba (y) (average (/ x y) y))
      1))
  
  ; fixed-point
  (define (fixed_point f start)
    (define (iter old new)
      (if (close_enough? old new)
        new
        (iter new (f new))))       ; "new" becomes old & "f(new)" becomes new
    (iter start (f start)))
  ```
  - why should this converge?  
    here for finding `(sqrt x)` (such that `y^2 = x` or its equivalent form `y = x/y`) we can search for the fixed point using `f(y) = x/y` (`(fixed_point (lambda (y) (/ x y)) 1)`)  
    considering intial guess `y1`, this never converges, it keeps oscillating between `y1` & `y2` (`y2 = x/y1` ⟶ `y3 = x/y2 = x/(x/y1) = y1`)  
    average is used to damp out these oscillations
    ```lisp
    (define (sqrt x)
      (fixed_point
        (average_damp (lambda (y) (/ x y)))  ; procedure returned from averagfw_damp used as "f"
        1))
    
    (define average_damp
      (lambda (f)                            ; takes procedure as an argument
        (lambda (x) (average (f x) x))))     ; & return procedure as a value
    ```
- **higher order procedures:** take procedural arguments & produce procedural values ot help us clarify & abstract some otherwise complicated processes
- **example: Netwon's method to find square roots:** used to find roots of a function  
to find `y` such that `f(y) = 0`, start with a guess `y0` & iterate with `yn+1 = lim y->yn (y - f(y)/(df/dy))`
  ```lisp
  (define (sqrt x)
    (newton (lambda (y) (- x (square y)))  ; if we know value of "y" for which "x - y^2 = 0" then "y = sqrt(x)"
    1))
  (define (newton f guess)
    (define df (derive f)
    (fixed_point
      (lambda(x) (- x (/ (f x) (df x)))))  ; (x - f(x)/(df/dx))
      guess))
  (define deriv
    (lambda (f)
      (lambda (x)
        (/ (- (f (+ x dx))                 ; (f(x+dx) - f(x))/dx
           (f x))
        dx))))
  (define dx 0.00001)
  ```
- **top-down design:** allows us to use names of procedures that we haven’t defined yet while writing a program
- **rights and privileges of first-class citizens:** Chris Strachey was advocate for making procedures/functions should be first class citizens in a programming language
  - to be named by variables
  - to be passed as arguments to procedures
  - to be returned as values of procedures
  - to be incorporating into data structures

- [continue](https://www.youtube.com/watch?v=DrFkf-T-6Co&list=PLE18841CABEA24090&index=5)


## misc
- programming requires dividing a unit of work into smaller units of work with the goal to replace units of work with one of the programming constructs:
  - **sequential:** used if task can be broken down into two subtasks one following the other
  - **conditional:** used if the task consists of doing one of two subtasks but not both
  - **iterative:** used if the task consists of doing a subtask a number of times but only as long as some condition is true
  ![](./media/programming/programming_constructs.png)