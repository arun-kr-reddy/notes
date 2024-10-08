- [introduction](#introduction)

# links  <!-- omit from toc -->
- [[playlist] ancient secrets of CV](https://pjreddie.com/courses/computer-vision/)
- [[playlist] first principles of computer vision](https://fpcv.cs.columbia.edu/)

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


[continue](https://www.youtube.com/watch?v=hpqrDUuk7HY&list=PLjMXczUzEYcHvw5YYSU92WrY8IwhTuq7p&index=4&t=2741s)