- [introduction](#introduction)
- [histogram](#histogram)
- [resizing](#resizing)
- [convolution](#convolution)

# links  <!-- omit from toc -->
- [[playlist] ancient secrets of CV](https://pjreddie.com/courses/computer-vision/)
- [[playlist] first principles of computer vision](https://fpcv.cs.columbia.edu/)
- [binomial as gaussian approximation](https://bartwronski.com/2021/10/31/practical-gaussian-filter-binomial-filter-and-small-sigma-gaussians/)
- [edge detection](https://blog.roboflow.com/edge-detection/)

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

# histogram
- **histogram:** pixel intensities distribution
- **histogram equalization:** improve image contrast by stretching its histogram to cover the full range of possible pixel values
  - calculate histogram
  - compute cumulative distribution function (`<=` pixel frequencies cumulative sum)
  - normalize CDF array elements (between 0 & 1) by dividing by total num pixels
  - map pixel values by multiplying corresponding CDF value with max possible pixel value
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

# convolution
- **convolution:** applying a kernel/filter to image  
  kernel slides over the image, multiplying pixels and summing the products  
  ![](./media/computer_vision/convolution.gif)
- **averaging (low pass) filters:** smooth out by replacing with average value of neighbor
  - **box/mean:** simple average
  - **Gaussian:** weighted average with more weight to closer pixels  
    smoother transitions so better edge preservation  
    ![](./media/computer_vision/gaussian_2d.png)
  - **binomial:** good & fast approximation to Gaussian using Pascal's triangle  
    ![](./media/computer_vision/gaussian_vs_binomial.png)  
    ![](./media/computer_vision/pascals_triangle.png)
    ```
              [1]   [1 2 1]
    [1 2 1] * [2] = [2 4 2]
              [1]   [1 2 1]
    ```
- **edge (high pass) filters:** emphasize edges (sharp transitions)  
  most semantic & shape info can be deduced from edges  
  low-pass filter first to remove noise
  - **first derivative:**  
    ![](./media/computer_vision/differentiation.png)  
    assume `∆x = 1` for pixels then approx filter is `[-1 0 1]`  
    need to run vertically & horizontally
    - **Prewitt:** box * derivative
      ```
                 [1]   [-1 0 1]
      [-1 0 1] * [1] = [-1 0 1]   ⟶ horizontal
                 [1]   [-1 0 1]
      ```
    - **Sobel:** gaussian * derivative
      ```
                 [1]   [-1 0 1]
      [-1 0 1] * [2] = [-2 0 2]
                 [1]   [-1 0 1]
      ```
  - **Laplacian:** sum of second derivative wrt x & y  
    ![](./media/computer_vision/laplacian_1.png)  
    approximation of second derivative in one dimension  
    ![](./media/computer_vision/laplacian_2.png)  
    ![](./media/computer_vision/laplacian_3.png)  
    single pass but loses direction info
    ```
    [ 0 -1  0]
    [-1  4 -1]
    [ 0 -1  0]
    ```
- canny:
- sharpen: add edges to image (idenity + edge)
- non-linear filter:


[histogram](https://en.wikipedia.org/wiki/Histogram_equalization)

[continue](https://youtu.be/5xdbJ7z4Nrc?list=PLjMXczUzEYcHvw5YYSU92WrY8IwhTuq7p&t=3293)