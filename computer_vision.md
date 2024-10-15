- [introduction](#introduction)
- [histogram](#histogram)
- [resizing](#resizing)
- [filtering](#filtering)
- [features](#features)

# links  <!-- omit from toc -->
- [[playlist] ancient secrets of CV](https://pjreddie.com/courses/computer-vision/)
- [[playlist] first principles of computer vision](https://fpcv.cs.columbia.edu/)
- [binomial as gaussian approximation](https://bartwronski.com/2021/10/31/practical-gaussian-filter-binomial-filter-and-small-sigma-gaussians/)
- [canny demo](https://bigwww.epfl.ch/demo/ip/demos/edgeDetector/)

# introduction
- **computer vision:** enable computers to analyse & understand images
  - **low level:** manipulate pixel values  
    example: resizing, grayscale, edges, color segmentation
  - **mid level:** connecting images to other things  
    example: panorama stitching (image ⟷ image), multi-view stereo (image ⟷ world), optical flow (image ⟷ time)
  - **high level:** interpreting meaning/content of images  
    example: image classification, object detection, semantic segmentation
- **pixel coordinates:** `(col, row, ch)` stored at `col + (row * width) + (ch * width * height)`  
  ![](./media/computer_vision/pixel_coordinates.png)
- **HSV:** hue (which color), saturation (how much color) & value (how bright)  
  makes recognizing colors much easier since hue remains same under varying lighting conditions  
  white if saturation zero (no color), black if value zero (zero brightness)  
  ![](./media/computer_vision/rgb_to_hsv_1.png)  
  ![](./media/computer_vision/rgb_to_hsv_2.png)
- **binary image:** obtained from grayscale image by thresholding (like histogram valley)  
  ![](./media/computer_vision/binary_thresholding.png)

# histogram
- **histogram:** pixel intensities distribution
- **histogram equalization:** stretching its histogram to cover the full range of possible pixel values  
  improve image contrast to increase visual distinction between features
  - calculate histogram
  - compute cumulative distribution function (`<=` pixel frequencies cumulative sum)
  - normalize CDF array elements (between 0 & 1) by dividing by total num pixels
  - map pixel values by multiplying corresponding CDF value with max possible pixel value (255)

# resizing
- **interpolation:** estimate values at unknown locations using known data  
  ![](./media/computer_vision/interpolation.png)
  - **nearest-neighbor:** pixel value of nearest neighbor
  - **bilinear:** weighted average of four nearest neigbhors  
    ![](./media/computer_vision/interpolation_bilinear.png)  
    visually equal to sum of products of each corner & diagonally opposite partial area
    ```
    R1 = (x2 - x) * Q11 + (x - x1) * Q21
    R2 = (x2 - x) * Q12 + (x - x1) * Q22

    P = (y2 - y) * R1 + (y - y1) * R2
      = (y2 - y) * (x2 - x) * Q11 + (y2 - y) * (x - x1) * Q21 + (y - y1) * (x2 - x) * Q12 + (y - y1) * (x - x1) * Q22
      = Q11 * area(P, Q22) + Q21 * area(P, Q12) + Q12 * area(P, Q21) + Q22 * area(P, Q11)
    ```
- to map new image coordinates with original image coordinates
  ```
  width_scale = new_width / original_width
  height_scale = new_height / original_height

  original_x = new_x / width_scale
  original_y = new_y / height_scale
  ```

# filtering
- **convolution:** applying a kernel/filter to image  
  kernel slides over the image, multiplying pixels and summing the products  
  ![](./media/computer_vision/convolution.gif)
- **separable kernel:** seperate 2D kernel into vertical & horizonal 1D kernels  
  `k^2` ⟶ `2k` multiplications, `k^2 - 1` ⟶ `2(k - 1)` additions  
  ![](./media/computer_vision/separable_kernel.png)
- **averaging (low pass) filters:** smooth out by replacing with average value of neighbor
  - **box/mean:** simple average
  - **gaussian:** weighted average with closer pixels weighted more (spatial weights)  
    smoother transitions so better edge preservation  
    ![](./media/computer_vision/gaussian_2d.png)
  - **binomial:** good & fast approximation to gaussian using pascal's triangle  
    ![](./media/computer_vision/gaussian_vs_binomial.png)  
    ![](./media/computer_vision/pascals_triangle.png)
    ```
              [1]   [1 2 1]
    [1 2 1] * [2] = [2 4 2]
              [1]   [1 2 1]
    ```
- **edge (high pass) filters:** emphasize edges (rapid change in pixel intensities)  
  most semantic & shape info can be deduced from edges  
  smooth first to remove noise then derivative
  - **first derivative:**  
    ![](./media/computer_vision/differentiation.png)  
    for pixels `∆x = 1` so filter is `[0 -1 1]` approxed to `[-1 0 1]`  
    need to run vertically & horizontally  
    edge pixels (local extrema) give very high ± response
    - **prewitt:** box * derivative
      ```
                 [1]   [-1 0 1]
      [-1 0 1] * [1] = [-1 0 1]   ⟶ horizontal
                 [1]   [-1 0 1]
      ```
    - **sobel:** gaussian * derivative  
      basically first derivative of gaussian  
      ![](./media/computer_vision/gaussian_derivative.png)
      ```
                 [1]   [-1 0 1]
      [-1 0 1] * [2] = [-2 0 2]
                 [1]   [-1 0 1]
      ```
  - **laplacian:** sum of second derivative wrt x & y  
    ![](./media/computer_vision/laplacian_1.png)  
    approximation of second derivative in one dimension  
    ![](./media/computer_vision/laplacian_2.png)  
    ![](./media/computer_vision/laplacian_3.png)  
    single pass but loses direction info  
    edge pixels (local maxima) give zero response
    ```
    [ 0 -1  0]
    [-1  4 -1]
    [ 0 -1  0]
    ```
    enhanced filter to include diagonal edges
    ```
    [-1 -4 -1]
    [-4 20 -4]
    [-1 -4 -1]
    ```
    laplacian of gaussian (LoG) to reduce noise  
    ![](./media/computer_vision/gaussian_laplacian.png)  
    difference of gaussian (DoG) ia a good approximation to LoG  
    ![](./media/computer_vision/log_vs_dog.png)  
    basically substracting two gaussian filters with different `σ`  
    ![](./media/computer_vision/gaussian_difference.png)
- **canny:** precise localization to single pixel, noise reduction by producing strong edges only, edge continuty even when gaps present
  - use sobel filter to smooth image and get gradient magnitude & direction
  - non-maximum suppression perpendicular to edge  
    thins down edge to single pixel
  - (hysteresis) thresholding edges into strong (`R > T`), weak (`> t` and `< T`), no edge (`< t`)
  - connect together strong edges, weak edges connected iff neighbor to strong
- **sharpen:** add edges to image (impulse/identity filter)
  ```
  [0 0 0]   [ 0 -1  0]   [ 0 -1  0]
  [0 1 0] + [-1  4 -1] = [-1  5 -1]
  [0 0 0]   [ 0 -1  0]   [ 0 -1  0]
  ```
- **non-linear filter:** cannot be implemented using convolution
  - **median:** to remove extreme outliers (like salt-pepper noise)
  - **bilateral:** gaussian blurs across edges so add tonal weights (besides spatial)  
    pixel values similar to center pixel value weighted more  
    constantly changing filter that preserves edges while smoothing flat regions  
    ![](./media/computer_vision/bilateral.png)

[continue]

- hough transform:

# features
- **features:** unique highly descriptive region  
  ![](./media/computer_vision/features_flat_edge_corner_1.png)  
  ![](./media/computer_vision/features_flat_edge_corner_2.png)
- template matching: measure similarity between two patches  
  check uniqueness of a patch
  - sum squared diff
  - auto correlation