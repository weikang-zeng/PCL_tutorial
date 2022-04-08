cmake_minimum_required(VERSION 2.8 FATAL_ERROR)   #所使用的cmake的版本

#project(pcd_write)     #命名项目设置cmake变量

project(NO)

find_package(PCL 1.2 REQUIRED)   #寻求制定版本的PCL包

include_directories(${PCL_INCLUDE_DIRS})   #设置为pcl安装的头文件和依赖文件的路径
link_directories(${PCL_LIBRARY_DIRS})   #设置为已安装的PCL库
add_definitions(${PCL_DEFINITIONS})     #列出需要预处理器定义和编译器标志

add_executable (NO src/fpfh_feature.cpp)    #尝试创建一个名为pcd_write的可执行文件，指定来源是pcd_write.cpp
target_link_libraries (NO ${PCL_LIBRARIES})  #让连接器知道我们连接的库
