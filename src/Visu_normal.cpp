#include <iostream>
#include <thread>
#include <pcl/io/pcd_io.h>
#include <pcl/features/normal_3d.h>
#include <pcl/visualization/cloud_viewer.h>
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);

using namespace std;

typedef pcl::PointXYZ PointT;

int main()
{
	//--------------------------- 加载点云 ---------------------------
	pcl::PointCloud<PointT>::Ptr cloud(new pcl::PointCloud<PointT>);
	if (pcl::io::loadPCDFile("bunny.pcd", *cloud) < 0)
	{
		PCL_ERROR("->点云文件不存在！\a\n");
		system("pause");
		return -1;
	}
	//===============================================================


	//--------------------------- 法线估计 ---------------------------
	pcl::NormalEstimation<PointT, pcl::Normal> ne;		//创建法线估计对象
	ne.setInputCloud(cloud);							//设置法线估计输入点云
	pcl::search::KdTree<PointT>::Ptr tree(new pcl::search::KdTree<PointT>());	//创建一个空的kdtree
	ne.setSearchMethod(tree);													//将空kdtree传递给法线估计对象 ne
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);//法向量计算结果
	ne.setKSearch(10);			//设置K近邻的个数
	//ne.setRadiusSearch(0.05);	//设置半径邻域的大小，两种方式二选一
	ne.setViewPoint(0, 0, 1);	//设置视点向量，默认0向量(0,0,0)，没有方向
	ne.compute(*normals);		//执行法线估计，并将结果保存到normals中
	//===============================================================


	//-------------------------- 法线可视化 --------------------------
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer")); //创建视窗对象，定义标题栏名称“3D Viewer”
	viewer->addPointCloud<PointT>(cloud, "original_cloud");	//将点云添加到视窗对象中，并定义一个唯一的ID“original_cloud”
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 1, 0, 0.5, "original_cloud"); //点云附色，三个字段，每个字段范围0-1
	viewer->addPointCloudNormals<PointT, pcl::Normal>(cloud, normals, 10, 0.05, "normals");	//每十个点显示一个法线，长度为0.05

	while (!viewer->wasStopped())
	{
		viewer->spinOnce(100);
		//boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
	//===============================================================

	return 0;
}
