#include <vtkAutoInit.h>
//VTK_MODULE_INIT(vtkRenderingOpenGL);
//VTK_MODULE_INIT(vtkInteractionStyle);
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/common/io.h>
#include <pcl/features/normal_3d.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/time.h>
#include <pcl/features/fpfh.h>    //FPFH
#include <pcl/visualization/pcl_plotter.h>//显示描述子
using namespace pcl;

int main(int argc, char **argv)
{
       //读取点云
       pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
       if (pcl::io::loadPCDFile<pcl::PointXYZ>("test.pcd", *cloud) == -1)
       {
              PCL_ERROR("Cloudn't read file!");
              system("pause");
              return -1;
       }

       //估计法线
       pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
       ne.setInputCloud(cloud);
       pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>());
       ne.setSearchMethod(tree);
       pcl::PointCloud<pcl::Normal>::Ptr cloud_normals(new pcl::PointCloud<pcl::Normal>);
       ne.setRadiusSearch(0.7);      //使用半径在查询点周围0.6范围内的所有邻元素
       ne.compute(*cloud_normals);     //计算法线

        //PHFH
       pcl::FPFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::FPFHSignature33> fpfh;
       fpfh.setInputCloud(cloud);
       fpfh.setInputNormals(cloud_normals);
       pcl::search::KdTree<PointXYZ>::Ptr tree1(new pcl::search::KdTree<pcl::PointXYZ>);//创建一个空的kd树表示法
       fpfh.setSearchMethod(tree1);//输出的数据集
       pcl::PointCloud<pcl::FPFHSignature33>::Ptr fpfhs(new pcl::PointCloud<pcl::FPFHSignature33>());
       //使用半径内0.8里面范围所有元素
       fpfh.setRadiusSearch(0.8);//使用半径必须大于估计法线时使用的半径
       fpfh.compute(*fpfhs);
       //显示某点的fhfh特征
       pcl::visualization::PCLPlotter plotter;
       plotter.addFeatureHistogram<pcl::FPFHSignature33>(*fpfhs,"fpfh", 60);

       //可视化
       pcl::visualization::PCLVisualizer viewer("PCL Viewer");
       viewer.setBackgroundColor(0.0, 0.0, 0.0);
       viewer.addPointCloudNormals<pcl::PointXYZ,pcl::Normal>(cloud, cloud_normals, 1, 0.4, "normals");
       viewer.addPointCloud(cloud,"cloud1");
       viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE,2, "cloud1");
       while (!viewer.wasStopped())
       {
              plotter.plot();
              viewer.spinOnce(100);
       }
       return 0;
}
