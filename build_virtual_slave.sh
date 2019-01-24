#!/bin/bash
mysql_source_dir=/data/mysql-5.7.24/
echo $mysql_source_dir
virtual_slave_soure_dir=`pwd`
echo $virtual_slave_soure_dir

rm -rf $mysql_source_dir/virtual_slave

cp -r $virtual_slave_soure_dir  $mysql_source_dir/;
cp $mysql_source_dir/CMakeLists.txt $mysql_source_dir/CMakeLists.txt.backup

echo "add_subdirectory(./virtual_slave)" >>  $mysql_source_dir/CMakeLists.txt
cd $mysql_source_dir
rm ./CMakeCache.txt
cmake . -DCMAKE_BUILD_TYPE=Release -DDOWNLOAD_BOOST=1 -DWITH_BOOST=/usr/local/boost -DCMAKE_INSTALL_PREFIX=/usr/local/virtual_slave
cmake --build ./  --target virtual_slave -- -j 4
mv  $mysql_source_dir/virtual_slave/virtual_slave  $virtual_slave_soure_dir/
mv  $mysql_source_dir/CMakeLists.txt.backup $mysql_source_dir/CMakeLists.txt