#!/bin/bash
mysql_source_dir= $1
if [ -d "$mysql_source_dir" ];then
				echo "MySQL源代码路径: $mysql_source_dir 存在"
else
				echo "MySQL源代码路径不存在"
				exit
fi

virtual_slave_soure_dir=`pwd`
echo $virtual_slave_soure_dir

if [ -d "$mysql_source_dir/$virtual_slave_soure_dir" ];then
				echo "文件夹$virtual_slave_soure_dir 已经存在于 $mysql_source_dir中，进行删除操作..."
				rm -rf $mysql_source_dir/$virtual_slave_soure_dir
else
				echo "拷贝源代码文件夹$virtual_slave_soure_dir到$mysql_source_dir"
				cp -r $virtual_slave_soure_dir  $mysql_source_dir/;
				exit

echo "备份MySQL源代码CMakeLists.txt"
cp $mysql_source_dir/CMakeLists.txt $mysql_source_dir/CMakeLists.txt.backup

echo "add_subdirectory(./$virtual_slave_soure_dir)" >>  $mysql_source_dir/CMakeLists.txt
cd $mysql_source_dir
rm ./CMakeCache.txt
cmake . -DCMAKE_BUILD_TYPE=Release -DDOWNLOAD_BOOST=1 -DWITH_BOOST=/usr/local/boost -DCMAKE_INSTALL_PREFIX=/usr/local/virtual_slave
cmake --build ./  --target virtual_slave -- -j 4
mv  $mysql_source_dir/virtual_slave/virtual_slave  $virtual_slave_soure_dir/
mv  $mysql_source_dir/CMakeLists.txt.backup $mysql_source_dir/CMakeLists.txt
