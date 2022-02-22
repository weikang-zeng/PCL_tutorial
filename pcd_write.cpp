#include <iostream>
#include <pcl/io/pcd_io.h>     //pcl操作定义头文件
#include <pcl/point_types.h>   //pcl类型定义头文件，here for the pcl:pointXYZ

int
  main (int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ> cloud;    //创建的pointcloud模板结构，它具有XYZ三个字段结构

  // Fill in the cloud data
  cloud.width    = 5;        //点云宽度
  cloud.height   = 1;        //点云高度
  cloud.is_dense = false;
  cloud.points.resize (cloud.width * cloud.height);

//随机点域填充
  for (auto& point: cloud)
  {
    point.x = 1024 * rand () / (RAND_MAX + 1.0f);
    point.y = 1024 * rand () / (RAND_MAX + 1.0f);
    point.z = 1024 * rand () / (RAND_MAX + 1.0f);
  }

  pcl::io::savePCDFileASCII ("test_pcd.pcd", cloud);      //保存点云数据到磁盘名为XXX.pcd的文件中
  //显示生成的数据
  std::cerr << "Saved " << cloud.size () << " data points to test_pcd.pcd." << std::endl;

  for (const auto& point: cloud)
    std::cerr << "    " << point.x << " " << point.y << " " << point.z << std::endl;

  return (0);
}
