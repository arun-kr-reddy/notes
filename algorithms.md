# algorithms & data structures
- [algorithmic thinking](#algorithmic-thinking)
- [models of computation](#models-of-computation)

## links  <!-- omit from toc -->
- [[lectures] introduction to algorithms](https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-fall-2011/)

## todo  <!-- omit from toc -->
- [quick sort](https://www.youtube.com/watch?v=XE4VP_8Y0BU)
- [leetcode 75](https://leetcode.com/studyplan/leetcode-75/)

## algorithmic thinking
- efficient procedures for solving problems on large inputs (like human genome)
- **asymptotic complexity:** is used for estimation of computational complexity of algorithms  
example: for `f(n) = n^2 + 3n` as `n` grows `n^2` grows at a much faster rate than `3n` rendering it insignificant for large values of `n`, so `f(n)` is said to be asymptotically equivalent to `n^2`
- **divide & conquer algorithm:** is a algorithm design paradigm that recursively breaks down a problem into sub-problems of the same or related type until they become simple enough to be solved directly  
![](./media/algorithms/divide_and_conquer.png)
- **peak:** position whose value is greater-than or equal-to (`>=`) all its neighbors, example: in 1D check left & right
- **1D peak finding:** find a peak in an array of size `n`  
with `>=` a peak will always exist, but with `>` a peak might exist, example: no peak if all elements have same value  
![](./media/algorithms/1d_peak.png)
  - **straightforward:** start from first element and walks across all elements  
  worst case `O(n)` complexity if last element is the peak
    ```cpp 
    uint32_t find1DPeakStraightforward(array_t array)
    {
        printArray(array);

        // check first & last elements first
        if (array.addr[0] > array.addr[1])
        {
            return array.addr[0];
        }
        else if (array.addr[array.size - 1] > array.addr[array.size - 2])
        {
            return array.addr[array.size - 1];
        }

        // check remaining ones
        for (int i = 1; i < array.size - 2; ++i)
        {
            uint32_t left_value   = array.addr[i - 1];
            uint32_t centre_value = array.addr[i];
            uint32_t right_value  = array.addr[i + 1];

            if ((centre_value >= left_value) && (centre_value >= right_value))
            {
                return centre_value;
            }
        }

        return NOT_FOUND;
    }
    ```
  - **divide & conquer:** recursive algorithm where we look at `n/2` position and then look at its left to check if it is higher then look at left half for a peak, else check right position and go for right half, if neither then `n/2` is the peak  
  `O(log(n))` (base 2) complexity, if I can half something `t` (maximum time I can spend) times, I can go through only `2^t` array, then time required for a `n` array is `2^t = n ⟶ t = log(n)`  
  comparison part takes constant time (`O(1)`) so ignored for worst case complexity  
    ```cpp
    uint32_t find1DPeakDivideConquer(array_t array)
    {
        size_t midpoint  = array.size / 2;
        size_t new_start = 0;
        size_t new_end   = array.size;

        printArray(array);

        // check first & last elements first
        if (array.addr[0] > array.addr[1])
        {
            return array.addr[0];
        }
        else if (array.addr[array.size - 1] > array.addr[array.size - 2])
        {
            return array.addr[array.size - 1];
        }

        if (array.size > 2)
        {
            uint32_t left_value   = array.addr[midpoint - 1];
            uint32_t centre_value = array.addr[midpoint];
            uint32_t right_value  = array.addr[midpoint + 1];

            if (left_value > centre_value)    // check left first
            {
                new_end = midpoint;
            }
            else if (right_value > centre_value)    // then check right
            {
                new_start = midpoint;
            }
            else    // midpoint is the peak
            {
                return array.addr[midpoint];
            }
        }
        else
        {
            return NOT_FOUND;
        }

        // search peak in new subarray
        array_t new_array = {0, new_end - new_start + 1};
        new_array.addr    = (uint8_t *)malloc(new_array.size);
        for (size_t i = 0; i < new_array.size; i++)
        {
            new_array.addr[i] = array.addr[new_start + i];
        }

        uint32_t peak = find1DPeakDivideConquer(new_array);

        free(new_array.addr);

        return peak;
    }
    ```
- **2D peak finding:** find a peak/hill (higher than all 4 neighbors) in a matrix with `n` rows & `m` columns  
![](./media/algorithms/2d_peak.png)
  - **greedy ascent:** essentially picks the directions to follow, start at the middle position and similar to 1D divide & conquer keep checking in a  default pattern (like left ⟶ right ⟶ up ⟶ down) until you find a higher element to decide which direction to move until the peak is found  
  `O(n*m)` complexity, `O(n^2)` for a square matrix  
  ![](./media/algorithms/2d_greedy_ascent.png)
    ```cpp
    uint32_t find2DPeakGreedyAscent(matrix_t matrix)
    {
        printMatrix(matrix);

        point2d_t position = {matrix.height / 2, matrix.width / 2};

        while (1)
        {
            int32_t centre_value = matrix.addr[position.row * matrix.width + position.col];
            int32_t left_value, right_value, up_value, down_value;

            printf("%4d ", centre_value);

            // init all neighbors
            left_value = right_value = up_value = down_value = INVALID;

            // check for edges
            if (position.col > 0)
                left_value = matrix.addr[position.row * matrix.width + (position.col - 1)];
            if (position.col < (matrix.width - 1))
                right_value = matrix.addr[position.row * matrix.width + (position.col + 1)];
            if (position.row > 0)
                up_value = matrix.addr[(position.row - 1) * matrix.width + position.col];
            if (position.row < (matrix.height - 1))
                down_value = matrix.addr[(position.row + 1) * matrix.width + position.col];

            // compare to neighbors
            if (matrix.width > 1 && matrix.height > 1)
            {
                if (left_value > centre_value)    // check left first
                {
                    printf(" -> ");
                    position.col--;
                }
                else if (right_value > centre_value)    // then check right
                {
                    printf(" -> ");
                    position.col++;
                }
                else if (up_value > centre_value)    // then check up
                {
                    printf(" -> ");
                    position.row--;
                }
                else if (down_value > centre_value)    // then check down
                {
                    printf(" -> ");
                    position.row++;
                }
                else    // midpoint is the peak
                {
                    printf("\n");
                    return matrix.addr[position.row * matrix.width + position.col];
                }
            }
            else
            {
                return NOT_FOUND;
            }
        }

        return NOT_FOUND;
    }
    ```
  - **2D divide & conquer:**
    - pick the middle column `j = m/2`, find the 1D peak at `(i, j)` then use `(i, j)` as a start to find a 1D peak in row `i`  
    `O(log(m) * log(n))` complexity, but 2D a peak may not exist on row `i` so this algorithm is efficient but incorrect  
    example: 12 is a column 1D peak and in that row 14 is the 1D peak but is not a 2D peak  
    ![](./media/algorithms/2d_divide_conquer_1.png)
    - pick the middle column `j = m/2`, find the global max in column `j` at `(i, j)`, then similar to 1D divide & conquer compare `(i, j)` to its left element, if higher then solve the new problem (maximum then comparison) with half the number of columns, else check right, if neither higher then `(i,j)` is the 2D peak (maximum so already compared vertically, and compared horizontally in previous step)  
    `O(n * log(m))` complexity, `log(m)` for 1D peak search and `n` for maximum value search  
    ![](./media/algorithms/2d_divide_conquer_2.png)
      ```cpp
      uint32_t find2DPeakDivideConquer(matrix_t matrix)
      {
          printMatrix(matrix);

          uint32_t peak      = INVALID;
          point2d_t position = {matrix.height / 2, matrix.width / 2};

          position.row = findMatrixColumnMax(matrix, position.col);
          printf("max in column %d is %d\n", position.row, matrix.addr[position.row * matrix.width + position.col]);

          uint32_t centre_value = matrix.addr[position.row * matrix.width + position.col];
          uint32_t left_value, right_value;

          // check for edges
          left_value = right_value = INVALID;
          if (position.col > 0)
              left_value = matrix.addr[position.row * matrix.width + (position.col - 1)];
          if (position.col < (matrix.width - 1))
              right_value = matrix.addr[position.row * matrix.width + (position.col + 1)];

          // compare to neighbors
          if (left_value > centre_value)    // check left first
          {
              position.col = 0;
          }
          else if (right_value > centre_value)    // then check right
          {
              position.col = (matrix.width / 2) - 1;
          }
          else
          {
              return centre_value;
          }

          // search peak in new subarray
          matrix_t new_matrix = {0, (matrix.width / 2) + 1, matrix.height};
          new_matrix.addr     = (uint8_t *)malloc(new_matrix.width * new_matrix.height);
          for (size_t row = 0; row < new_matrix.height; row++)
          {
              for (size_t col = 0; col < new_matrix.height; col++)
              {
                  new_matrix.addr[row * new_matrix.width + col] = matrix.addr[row * matrix.width + (col + position.col)];
              }
          }

          peak = find2DPeakDivideConquer(new_matrix);

          free(new_matrix.addr);

          return peak;
      }

      uint32_t findMatrixColumnMax(matrix_t matrix, uint32_t col)
      {
          uint32_t column_max_row = 0;
          for (int32_t i = 1; i < matrix.height; i++)
          {
              if (matrix.addr[i * matrix.width + col] > matrix.addr[column_max_row * matrix.width + col])
              {
                  column_max_row = i;
              }
          }

          return column_max_row;
      }
      ```

## models of computation
- **algorithm:** is mathematical abstraction of a computer program (computational procedure to solve a problem)  
**model of computation:** specifies what operations an algorithm is allowed and cost (time, space, etc) of each operation  
total cost of an algorithm is sum of operation costs
- **example: random access machine (RAM):** random access memory is modeled by a big array of `O(1)` registers (of 1 word each)  
in `O(1)` time an algorithm can load `O(1)` words, do `O(1)` computations and store `O(1)` words  
is similar to assembly programming and is realistic & powerful  
![](./media/algorithms/random_access_machine.png)
- **example: pointer machine:** dynamically allocated objects, each object has `O(1)` fields, fields are words or pointer
is similar to object oriented programming, is weaker than RAM but is simpler  
![](./media/algorithms/pointer_machine.png)  
this can be implemented in RAM where pointer becomes index in array
- **python model:** has either mode of thinking: array `*i = *(i + 1)` or objects `x = x.next`
- **document distance:** shows the similarities between two text documents, think of document `D` as a vector of words `w` (whitespace & punctuations ignored), where `D[w]` gives the frequency of the word  
![](./media/algorithms/document_distance.png)  
document distance can be defined as dot product of the two vectors  
![](./media/algorithms/document_distance_equation_1.png)  
but this will not be scale-invariant (long documents with 99%, same words will seem farther than short documents with 10% same words), this can be fixed through normalization  
![](./media/algorithms/document_distance_equation_2.png)  
recall dot product is `x . y = |x| |y| cosθ`, so apply arccosine (inverse function of cosine) to above function to get geometric representation (in radians)  
![](./media/algorithms/document_distance_equation_3.png)
- **document distance algorithm:** split each document into words ⟶ count word frequencies in document vectors -> compute dot product and divide