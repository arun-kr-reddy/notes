# algorithms & data structures
- [algorithmic thinking](#algorithmic-thinking)

## links  <!-- omit from toc -->
- [[lectures] introduction to algorithms](https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-fall-2011/)
- [quick sort](https://www.youtube.com/watch?v=XE4VP_8Y0BU)

## todo  <!-- omit from toc -->
- [divide & conquer algorithm](https://en.wikipedia.org/wiki/Divide-and-conquer_algorithm)
- [leetcode 75](https://leetcode.com/studyplan/leetcode-75/)

## algorithmic thinking
- efficient procedures for solving problems on large inputs (like human genome)
- **asymptotic complexity:** is used for estimation of computational complexity of algorithms  
example: for `f(n) = n^2 + 3n` as `n` grows `n^2` grows at a much faster rate than `3n` (rendering it insignificant for large `n`), so `f(n)` is said to be asymptotically equivalent to `n^2`
- **divide & conquer algorithm:** is a algorithm design paradigm that recursively breaks down a problem into sub-problems of the same or related type until they become simple enough to be solved directly  
![](./media/algorithms/divide_and_conquer.png)
- **peak:** position whose value is greater-than or equal-to (`>=`) all its neighbors, example: in 1D check left & right
- **1D peak finding:** find a peak in an array of size `n`  
with `>=` a peak will always exist, but with `>` a peak might exist, example: no peak if all elements have same value  
![](./media/algorithms/1d_peak.png)
  - **straightforward:** start from first element and walks across all elements  
  worst case `O(n)` complexity if last element is the peak
    ```cpp
    int32_t find1DPeakStraightforward(uint32_t *arr, size_t size)
    {
        // check first & last elements first
        if (arr[0] > arr[1])
        {
            return arr[0];
        }
        else if (arr[size - 1] > arr[size - 2])
        {
            return arr[size - 1];
        }

        // check remaining ones
        for (int i = 1; i < size - 2; ++i)
        {
            uint32_t left_value   = arr[i - 1];
            uint32_t centre_value = arr[i];
            uint32_t right_value  = arr[i + 1];

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
    int32_t find1DPeakDivideConquer(uint32_t *arr, size_t size)
    {
        size_t midpoint  = size / 2;
        size_t new_start = 0;
        size_t new_end   = size;

        // printArray(arr, size);

        if (size > 1)
        {
            uint32_t left_value   = arr[midpoint - 1];
            uint32_t centre_value = arr[midpoint];
            uint32_t right_value  = arr[midpoint + 1];

            if (left_value > centre_value) // check left first
            {
                new_end = midpoint;
            }
            else if (right_value > centre_value) // then check right
            {
                new_start = midpoint;
            }
            else // midpoint is the peak
            {
                return arr[midpoint];
            }
        }
        else
        {
            return NOT_FOUND;
        }

        // search peak in new subarray
        return (find1DPeakDivideConquer(arr + new_start, new_end - new_start));
    }
    ```
- **2D peak finding:** find a peak/hill (higher than all 4 neighbors) in a matrix with `n` rows & `m` columns  
![](./media/algorithms/2d_peak.png)
  - **greedy ascent:** essentially picks the directions to follow, start at the middle position and similar to 1D divide & conquer keep checking in a  default pattern (like left ⟶ right ⟶ up ⟶ down) until you find a higher element to decide which direction to move until the peak is found  
  `O(n*m)` complexity, `O(n^2)` for a square matrix  
  ![](./media/algorithms/2d_greedy_ascent.png)
    ```cpp
    int32_t find2DPeakGreedyAscent(uint32_t *arr, point2d_t size)
    {
        point2d_t position = {size.x / 2, size.y / 2};

        while (1)
        {
            int32_t centre_value = arr[position.x * size.x + position.y];
            int32_t left_value, right_value, up_value, down_value;

            // init all neighbors
            left_value = right_value = up_value = down_value = INVALID;

            // check for edges
            if (position.y > 0)
                left_value = arr[position.x * size.x + (position.y - 1)];
            else if (position.y < (size.y - 1))
                right_value = arr[position.x * size.x + (position.y + 1)];
            if (position.x > 0)
                up_value = arr[(position.x - 1) * size.x + position.y];
            else if (position.x < (size.x - 1))
                down_value = arr[(position.x + 1) * size.x + position.y];

            // compare to neighbors
            if (size.x > 1 && size.y > 1)
            {
                if (left_value > centre_value) // check left first
                {
                    position.y--;
                }
                else if (right_value > centre_value) // then check right
                {
                    position.y++;
                }
                else if (up_value > centre_value) // then check up
                {
                    position.x--;
                }
                else if (down_value > centre_value) // then check down
                {
                    position.x++;
                }
                else // midpoint is the peak
                {
                    return arr[position.x * size.x + position.y];
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
      //todo:aarunkum
      ```