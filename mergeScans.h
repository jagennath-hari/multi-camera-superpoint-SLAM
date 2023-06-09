#ifndef MERGESCANS_H_
#define MERGESCANS_H_

//ROS includes
#include <ros/ros.h>
#include <ros/console.h>

//all sensor includes
#include <sensor_msgs/PointCloud2.h>

//message filter includes
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

//pcl includes
#include <pcl/common/eigen.h>
#include <pcl/common/io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/common/transforms.h>
#include <pcl/filters/filter.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/filters/voxel_grid.h>

class mergeScans
{
private:
    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::PointCloud2, sensor_msgs::PointCloud2> mergeScansSyncPolicy_;
    message_filters::Subscriber<sensor_msgs::PointCloud2> zed2Cloud_;
    message_filters::Subscriber<sensor_msgs::PointCloud2> zedmCloud_;
    message_filters::Synchronizer<mergeScans::mergeScansSyncPolicy_> sync_;
    ros::Publisher mergedCloud_;
    void callBack_(const sensor_msgs::PointCloud2::ConstPtr& zed2CloudMsg, const sensor_msgs::PointCloud2::ConstPtr& zedmCloudMsg);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr transformCloud_(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& localCloud);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr fusedCloud_;
public:
    mergeScans(ros::NodeHandle *nh);
    ~mergeScans();
};


#endif