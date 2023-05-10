# multi-camera-superpoint-SLAM
Graph based SLAM for multiple cameras using SuperPoint feature detector. Uses (zed_wrapper, rtabmap_ros, LibTorch and ROS noetic).

<p float="center">
  <img src="assests/SLAM.gif" width="800" height="400" />
</p> 


## Dependencies
1) ROS
2) zed_wrapper ([Offical Guide](https://github.com/stereolabs/zed-ros-wrapper))
3) zed_ros_example ([Offical Repository](https://github.com/stereolabs/zed-ros-examples))
4) LibTorch ([Offical Installation Guide](https://github.com/pytorch/pytorch/blob/main/docs/libtorch.rst))
5) rtabmap + rtabmap_ros ([Offical Installation Guide](https://github.com/introlab/rtabmap_ros#rtabmap_ros))
6) Download SuperPoint Weights .pt file ([Offical Reposoitory](https://github.com/KinglittleQ/SuperPoint_SLAM))

## To use
1) modify launch file to configure camera frames and link for SLAM
2) Change translation and orientation of cameras w.r.t base_link (Both tf packages and zed_multi_camera nodes)
```shell
roslaunch multi_camera_superpoint_semantic_slam_zed_odom.launch
```

## Pose Graph Optimization
View all topics on RVIZ
<p float="center">
  <img src="assests/loop closure.gif" width="800" height="400" />
</p> 
