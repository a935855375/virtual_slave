# virtual_slave

更确切的来说，应该叫做MySQL virtual slave，virtual_slave是一个远程binlog同步工具，
并且提供类似于semisync slave的功能，返回ACK给master。

## 一、功能列表

- 支持GTID复制协议
- 支持半同步复制协议
- 支持设置binlog文件过期时间
- 支持断点续传
- 支持设置binlog落盘模式
- 支持心跳间隔设置
- 支持网络超时设置

## 二、安装使用

可以使用源码安装，或者直接下载对应的二进制文件。

## 二进制安装

```$xslt
wget 
```


### 源码安装
```$xslt
#
git glone 
```

### 配置文件示例

```$xslt
#replication protocol GTID or file+pos
opt_remote_proto=1

#mode for get start pos.
get_start_gtid_mode=1

exclude_gtids=

virtual_slave_server_id=123456

raw_mode=1

master_host=10.211.55.32

master_port=13307

master_user=ashe

master_password=ashe

stop_never = 1

#--result-file=/data/binlog_backup/
binlog_dir=/data/binlog_backup/

# last parma
mysql-bin.000001

heartbeat_period = 5
net_read_time_out = 10
```

### 启动示例
```$xslt
nohup virtual_slave  /etc/123_virtual_slave.cnf &
```
