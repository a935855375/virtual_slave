# virtual_slave如何处理master故障

作为一个slave来看master，可能会因为各种情况认为其处于故障的状态，所以virtual_slave
存在对于master的故障检测和处理机制。

## 故障检测
virtual_slave提供了心跳间隔，网络超时的设置，用心跳和网络超时来协作检测master的故障
。
行为假设参数
```$xslt
heartbeat_period = 5
net_read_time_out = 10
```
则master在没有binlog写入的情况时，会没间隔5秒钟发送心跳数据(binlog event的一种
类型)给virtual_slave；如果超过10秒钟slave没有收到master的任何数据，则证明master
，或者slave到master之间的网络出现异常。

## 故障恢复
在探测到master故障(在MyKeeper的架构中，会先调用故障HOOK，来进行可能的数据补偿处理)，
virtual_slave需要重新发起链接，重新后，会对新的master的server UUID进行检测，
对比上一次的server UUID，如果master没有发生改变，则说明可能是网络故障引起的，将从上
一次同步的位点，继续同步(file+pos)。如果发现master发生改变（发生了切换），则使用GTID
的方式继续同步。