#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>

int main()
{
   pcl::PLYReader reader;
   pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
   reader.read<pcl::PointXYZ>("cow.ply", *cloud);
}

//
//void main()
//{
  // pcl::PCDReader reader;
   //pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
   //reader.read<pcl::PointXYZ>("demo.pcd", *cloud);
//}
