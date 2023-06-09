#include "mergeScans.h"

mergeScans::mergeScans(ros::NodeHandle *nh) : sync_(mergeScans::mergeScansSyncPolicy_(2), this->zed2Cloud_, this->zedmCloud_), fusedCloud_((new pcl::PointCloud<pcl::PointXYZRGB>))
{
    this->zed2Cloud_.subscribe(*nh, "/zed2/zed2_node/point_cloud/cloud_registered", 2);
    this->zedmCloud_.subscribe(*nh, "/zedm/zedm_node/point_cloud/cloud_registered", 2);
    this->mergedCloud_ = nh->advertise<sensor_msgs::PointCloud2>("/zed2/zed2_node/point_cloud/cloud_merged", 1);
    this->sync_.registerCallback(std::bind(&mergeScans::callBack_, this, std::placeholders::_1, std::placeholders::_2));
}

mergeScans::~mergeScans()
{
}

void mergeScans::callBack_(const sensor_msgs::PointCloud2::ConstPtr& zed2CloudMsg, const sensor_msgs::PointCloud2::ConstPtr& zedmCloudMsg)
{
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr zed2Cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr zedmCloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::fromROSMsg(*zed2CloudMsg, *zed2Cloud);
    pcl::fromROSMsg(*zedmCloudMsg, *zedmCloud);

    *(this->fusedCloud_) = *zed2Cloud + *(this->transformCloud_(zedmCloud));

    //ROS messages
    sensor_msgs::PointCloud2 finalCloud;
    pcl::toROSMsg(*(this->fusedCloud_), finalCloud);
    finalCloud.header = zed2CloudMsg->header;
    this->mergedCloud_.publish(finalCloud);

}

pcl::PointCloud<pcl::PointXYZRGB>::Ptr mergeScans::transformCloud_(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr& localCloud)
{
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr output(new pcl::PointCloud<pcl::PointXYZRGB>);
    output->resize(localCloud->size());
    Eigen::Matrix4f transformation;
    transformation <<   -1.0 , 0.0 , 0.0 , -0.602,
                        0.0 , -1.0 , 0.0 , 0.0,
                        0.0 , 0.0 , 1.0 , 0.0,
                        0      ,      0        ,       0      ,           1           ;

    pcl::transformPointCloud(*localCloud, *output, transformation);

    return output;
}


//main
int main(int argc, char** argv)
{
	ros::init(argc, argv, "merge_scans");
	ros::NodeHandle nh;
	mergeScans* mergeScans_ = new mergeScans(&nh);
	ros::MultiThreadedSpinner spinner(12);
    spinner.spin();

	return 0;
}