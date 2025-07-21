### Deploying some configs and validating that they worked
- No point in trying to reinvent the wheel when it comes to using the code on multiple devices.
- Using bash script to push out the commands to various devices.
- Each script has a unique roll to play in rolling a change
    * pre-change-validation
    * deployment
    * post-change-validation
    * backout

Pre-change validation
```
toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista_ssh$ ./pre_change_status.sh 
You are running c version 201710
Entering Authentication Phase...
Enter password: 
Commands from file: run enable ; show ip ospf neighbor ; show ip ospf interface brief ; show lldp neighbors ; 
>enable
#show ip ospf neighbor
#show ip ospf interface brief
#show lldp neighbors
Last table change time   : 0:19:03 ago
Number of table inserts  : 4
Number of table deletes  : 0
Number of table drops    : 0
Number of table age-outs : 0

Port          Neighbor Device ID       Neighbor Port ID    TTL
---------- ------------------------ ---------------------- ---
Et1           ceos2                    Ethernet1           120
Et2           ceos3                    Ethernet1           120
Ma0           ceos3                    Management0         120
Ma0           ceos2                    Management0         120



You are running c version 201710
Entering Authentication Phase...
Enter password: 
Commands from file: run enable ; show ip ospf neighbor ; show ip ospf interface brief ; show lldp neighbors ; 
>enable
#show ip ospf neighbor
#show ip ospf interface brief
#show lldp neighbors
Last table change time   : 0:19:04 ago
Number of table inserts  : 4
Number of table deletes  : 0
Number of table drops    : 0
Number of table age-outs : 0

Port          Neighbor Device ID       Neighbor Port ID    TTL
---------- ------------------------ ---------------------- ---
Et1           ceos1                    Ethernet1           120
Et2           ceos3                    Ethernet2           120
Ma0           ceos1                    Management0         120
Ma0           ceos3                    Management0         120



You are running c version 201710
Entering Authentication Phase...
Enter password: 
Commands from file: run enable ; show ip ospf neighbor ; show ip ospf interface brief ; show lldp neighbors ; 
>enable
#show ip ospf neighbor
#show ip ospf interface brief
#show lldp neighbors
Last table change time   : 0:19:04 ago
Number of table inserts  : 4
Number of table deletes  : 0
Number of table drops    : 0
Number of table age-outs : 0

Port          Neighbor Device ID       Neighbor Port ID    TTL
---------- ------------------------ ---------------------- ---
Et1           ceos1                    Ethernet2           120
Et2           ceos2                    Ethernet2           120
Ma0           ceos1                    Management0         120
Ma0           ceos2                    Management0         120



toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista_ssh$
```

Push out config changes

```
toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista_ssh$ ./push_conf_change.sh 
You are running c version 201710
Entering Authentication Phase...
Enter password: 
Commands from file: run enable ; config t ; interface eth1 ; description ceos1-ceos2 ; no switchport ; ip address 192.168.0.0/31 ; no shut ; ip routing  ; no interface loopback41 ; no interface loopback 1 ; interface eth2 ; description ceos1-ceos3 ; no switchport ; ip address 192.168.0.2/31 ; no shut ; interface loopback 0 ; ip address 1.1.1.1/32 ; no router ospf 1 ; router ospf 1 ; network 1.1.1.1/32 area 0 ; network 192.168.0.0/31 area 0.0.0.0 ; network 192.168.0.2/31 area 0.0.0.0 ; 
>enable
#config t
(config)#interface eth1
(config-if)#description ceos1-ceos2
(config-if)#no switchport
(config-if)#ip address 192.168.0.0/31
(config-if)#no shut
(config-if)#ip routing
(config)#no interface loopback41
(config)#no interface loopback 1
(config)#interface eth2
(config-if)#description ceos1-ceos3
(config-if)#no switchport
(config-if)#ip address 192.168.0.2/31
(config-if)#no shut
(config-if)#interface loopback 0
(config-if)#ip address 1.1.1.1/32
(config-if)#no router ospf 1
(config)#router ospf 1
(config-router)#network 1.1.1.1/32 area 0
(config-router)#network 192.168.0.0/31 area 0.0.0.0
(config-router)#network 192.168.0.2/31 area 0.0.0.0


You are running c version 201710
Entering Authentication Phase...
Enter password: 
Commands from file: run enable ; config t ; interface eth1 ; description ceos2-ceos1 ; no switchport ; ip address 192.168.0.1/31 ; no shut ; ip routing  ; no interface loopback41 ; no interface loopback1 ; interface eth2 ; description ceos2-ceos3 ; no switchport ; ip address 192.168.0.4/31 ; no shut ; interface loopback0 ; ip address 2.2.2.2/32 ; no router ospf 1 ; router ospf 1 ; network 2.2.2.2/32 area 0 ; network 192.168.0.0/31 area 0.0.0.0 ; network 192.168.0.4/31 area 0.0.0.0 ; 
>enable
#config t
(config)#interface eth1
(config-if)#description ceos2-ceos1
(config-if)#no switchport
(config-if)#ip address 192.168.0.1/31
(config-if)#no shut
(config-if)#ip routing
(config)#no interface loopback41
(config)#no interface loopback1
(config)#interface eth2
(config-if)#description ceos2-ceos3
(config-if)#no switchport
(config-if)#ip address 192.168.0.4/31
(config-if)#no shut
(config-if)#interface loopback0
(config-if)#ip address 2.2.2.2/32
(config-if)#no router ospf 1
(config)#router ospf 1
(config-router)#network 2.2.2.2/32 area 0
(config-router)#network 192.168.0.0/31 area 0.0.0.0
(config-router)#network 192.168.0.4/31 area 0.0.0.0


You are running c version 201710
Entering Authentication Phase...
Enter password: 
Commands from file: run enable ; config t ; interface eth1 ; description ceos3-ceos1 ; no switchport ; ip address 192.168.0.3/31 ; no shut ; ip routing  ; no interface loopback41 ; interface eth2 ; description ceos1-ceos3 ; no switchport ; ip address 192.168.0.5/31 ; no shut ; interface loopback 0 ; ip address 3.3.3.3/32  ; no router ospf 1 ; router ospf 1 ; network 3.3.3.3/32 area 0 ; network 192.168.0.2/31 area 0.0.0.0 ; network 192.168.0.4/31 area 0.0.0.0 ; 
>enable
#config t
(config)#interface eth1
(config-if)#description ceos3-ceos1
(config-if)#no switchport
(config-if)#ip address 192.168.0.3/31
(config-if)#no shut
(config-if)#ip routing
(config)#no interface loopback41
(config)#interface eth2
(config-if)#description ceos1-ceos3
(config-if)#no switchport
(config-if)#ip address 192.168.0.5/31
(config-if)#no shut
(config-if)#interface loopback 0
(config-if)#ip address 3.3.3.3/32
(config-if)#no router ospf 1
(config)#router ospf 1
(config-router)#network 3.3.3.3/32 area 0
(config-router)#network 192.168.0.2/31 area 0.0.0.0
(config-router)#network 192.168.0.4/31 area 0.0.0.0


toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista_ssh$
```
Post-change validation
```
toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista_ssh$ ./post_change_status.sh 
You are running c version 201710
Entering Authentication Phase...
Enter password: 
Commands from file: run enable ; show ip int brief ; show ip ospf neighbor ; show ip ospf interface brief ; show lldp neighbors ; show ip route ; ping 1.1.1.1 ; ping 2.2.2.2 ; ping 3.3.3.3 ; 
>enable
#show ip int brief
                                                                        Address
Interface       IP Address         Status      Protocol          MTU    Owner  
--------------- ------------------ ----------- ------------- ---------- -------
Ethernet1       192.168.0.0/31     up          up               1500           
Ethernet2       192.168.0.2/31     up          up               1500           
Loopback0       1.1.1.1/32         up          up              65535           
Management0     172.20.20.3/24     up          up               1500           

#show ip ospf neighbor
Neighbor ID     Instance VRF      Pri State                  Dead Time   Address         Interface
2.2.2.2         1        default  1   FULL/DR                00:00:33    192.168.0.1     Ethernet1
3.3.3.3         1        default  1   FULL/DR                00:00:36    192.168.0.3     Ethernet2
#show ip ospf interface brief
   Interface          Instance VRF        Area            IP Address         Cost  State      Nbrs
   Lo0                1        default    0.0.0.0         1.1.1.1/32         10    DR         0
   Et1                1        default    0.0.0.0         192.168.0.0/31     10    Backup DR  1
   Et2                1        default    0.0.0.0         192.168.0.2/31     10    Backup DR  1
#show lldp neighbors
Last table change time   : 0:01:00 ago
Number of table inserts  : 4
Number of table deletes  : 0
Number of table drops    : 0
Number of table age-outs : 0

Port          Neighbor Device ID       Neighbor Port ID    TTL
---------- ------------------------ ---------------------- ---
Et1           ceos2                    Ethernet1           120
Et2           ceos3                    Ethernet1           120
Ma0           ceos3                    Management0         120
Ma0           ceos2                    Management0         120

#show ip route

VRF: default
Source Codes:
       C - connected, S - static, K - kernel,
       O - OSPF, O IA - OSPF inter area, O E1 - OSPF external type 1,
       O E2 - OSPF external type 2, O N1 - OSPF NSSA external type 1,
       O N2 - OSPF NSSA external type2, O3 - OSPFv3,
       O3 IA - OSPFv3 inter area, O3 E1 - OSPFv3 external type 1,
       O3 E2 - OSPFv3 external type 2,
       O3 N1 - OSPFv3 NSSA external type 1,
       O3 N2 - OSPFv3 NSSA external type2, B - Other BGP Routes,
       B I - iBGP, B E - eBGP, R - RIP, I L1 - IS-IS level 1,
       I L2 - IS-IS level 2, A B - BGP Aggregate,
       A O - OSPF Summary, NG - Nexthop Group Static Route,
       V - VXLAN Control Service, M - Martian,
       DH - DHCP client installed default route,
       DP - Dynamic Policy Route, L - VRF Leaked,
       G  - gRIBI, RC - Route Cache Route,
       CL - CBF Leaked Route

Gateway of last resort:
 S        0.0.0.0/0 [1/0]
           via 172.20.20.1, Management0

 C        1.1.1.1/32
           directly connected, Loopback0
 O        2.2.2.2/32 [110/20]
           via 192.168.0.1, Ethernet1
 O        3.3.3.3/32 [110/20]
           via 192.168.0.3, Ethernet2
 C        172.20.20.0/24
           directly connected, Management0
 C        192.168.0.0/31
           directly connected, Ethernet1
 C        192.168.0.2/31
           directly connected, Ethernet2
 O        192.168.0.4/31 [110/20]
           via 192.168.0.1, Ethernet1
           via 192.168.0.3, Ethernet2

#ping 1.1.1.1
PING 1.1.1.1 (1.1.1.1) 72(100) bytes of data.
80 bytes from 1.1.1.1: icmp_seq=1 ttl=64 time=0.032 ms
80 bytes from 1.1.1.1: icmp_seq=2 ttl=64 time=0.005 ms
80 bytes from 1.1.1.1: icmp_seq=3 ttl=64 time=0.002 ms
80 bytes from 1.1.1.1: icmp_seq=4 ttl=64 time=0.002 ms
80 bytes from 1.1.1.1: icmp_seq=5 ttl=64 time=0.002 ms

--- 1.1.1.1 ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 0ms
rtt min/avg/max/mdev = 0.002/0.008/0.032/0.011 ms, ipg/ewma 0.016/0.020 ms
#ping 2.2.2.2
PING 2.2.2.2 (2.2.2.2) 72(100) bytes of data.
80 bytes from 2.2.2.2: icmp_seq=1 ttl=64 time=0.065 ms
80 bytes from 2.2.2.2: icmp_seq=2 ttl=64 time=0.013 ms
80 bytes from 2.2.2.2: icmp_seq=3 ttl=64 time=0.009 ms
80 bytes from 2.2.2.2: icmp_seq=4 ttl=64 time=0.009 ms
80 bytes from 2.2.2.2: icmp_seq=5 ttl=64 time=0.011 ms

--- 2.2.2.2 ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 1ms
rtt min/avg/max/mdev = 0.009/0.021/0.065/0.021 ms, ipg/ewma 0.373/0.042 ms
#ping 3.3.3.3
PING 3.3.3.3 (3.3.3.3) 72(100) bytes of data.
80 bytes from 3.3.3.3: icmp_seq=1 ttl=64 time=0.068 ms
80 bytes from 3.3.3.3: icmp_seq=2 ttl=64 time=0.005 ms
80 bytes from 3.3.3.3: icmp_seq=3 ttl=64 time=0.002 ms
80 bytes from 3.3.3.3: icmp_seq=4 ttl=64 time=0.002 ms
80 bytes from 3.3.3.3: icmp_seq=5 ttl=64 time=0.003 ms

--- 3.3.3.3 ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 0ms
rtt min/avg/max/mdev = 0.002/0.016/0.068/0.026 ms, ipg/ewma 0.029/0.041 ms


You are running c version 201710
Entering Authentication Phase...
Enter password: 
Commands from file: run enable ; show ip int brief ; show ip ospf neighbor ; show ip ospf interface brief ; show lldp neighbors ; show ip route ; ping 1.1.1.1 ; ping 2.2.2.2 ; ping 3.3.3.3 ; 
>enable
#show ip int brief
                                                                        Address
Interface       IP Address         Status      Protocol          MTU    Owner  
--------------- ------------------ ----------- ------------- ---------- -------
Ethernet1       192.168.0.1/31     up          up               1500           
Ethernet2       192.168.0.4/31     up          up               1500           
Loopback0       2.2.2.2/32         up          up              65535           
Management0     172.20.20.4/24     up          up               1500           

#show ip ospf neighbor
Neighbor ID     Instance VRF      Pri State                  Dead Time   Address         Interface
1.1.1.1         1        default  1   FULL/BDR               00:00:32    192.168.0.0     Ethernet1
3.3.3.3         1        default  1   FULL/DR                00:00:33    192.168.0.5     Ethernet2
#show ip ospf interface brief
   Interface          Instance VRF        Area            IP Address         Cost  State      Nbrs
   Lo0                1        default    0.0.0.0         2.2.2.2/32         10    DR         0
   Et1                1        default    0.0.0.0         192.168.0.1/31     10    DR         1
   Et2                1        default    0.0.0.0         192.168.0.4/31     10    Backup DR  1
#show lldp neighbors
Last table change time   : 0:01:01 ago
Number of table inserts  : 4
Number of table deletes  : 0
Number of table drops    : 0
Number of table age-outs : 0

Port          Neighbor Device ID       Neighbor Port ID    TTL
---------- ------------------------ ---------------------- ---
Et1           ceos1                    Ethernet1           120
Et2           ceos3                    Ethernet2           120
Ma0           ceos1                    Management0         120
Ma0           ceos3                    Management0         120

#show ip route

VRF: default
Source Codes:
       C - connected, S - static, K - kernel,
       O - OSPF, O IA - OSPF inter area, O E1 - OSPF external type 1,
       O E2 - OSPF external type 2, O N1 - OSPF NSSA external type 1,
       O N2 - OSPF NSSA external type2, O3 - OSPFv3,
       O3 IA - OSPFv3 inter area, O3 E1 - OSPFv3 external type 1,
       O3 E2 - OSPFv3 external type 2,
       O3 N1 - OSPFv3 NSSA external type 1,
       O3 N2 - OSPFv3 NSSA external type2, B - Other BGP Routes,
       B I - iBGP, B E - eBGP, R - RIP, I L1 - IS-IS level 1,
       I L2 - IS-IS level 2, A B - BGP Aggregate,
       A O - OSPF Summary, NG - Nexthop Group Static Route,
       V - VXLAN Control Service, M - Martian,
       DH - DHCP client installed default route,
       DP - Dynamic Policy Route, L - VRF Leaked,
       G  - gRIBI, RC - Route Cache Route,
       CL - CBF Leaked Route

Gateway of last resort:
 S        0.0.0.0/0 [1/0]
           via 172.20.20.1, Management0

 O        1.1.1.1/32 [110/20]
           via 192.168.0.0, Ethernet1
 C        2.2.2.2/32
           directly connected, Loopback0
 O        3.3.3.3/32 [110/20]
           via 192.168.0.5, Ethernet2
 C        172.20.20.0/24
           directly connected, Management0
 C        192.168.0.0/31
           directly connected, Ethernet1
 O        192.168.0.2/31 [110/20]
           via 192.168.0.0, Ethernet1
           via 192.168.0.5, Ethernet2
 C        192.168.0.4/31
           directly connected, Ethernet2

#ping 1.1.1.1
PING 1.1.1.1 (1.1.1.1) 72(100) bytes of data.
80 bytes from 1.1.1.1: icmp_seq=1 ttl=64 time=0.060 ms
80 bytes from 1.1.1.1: icmp_seq=2 ttl=64 time=0.009 ms
80 bytes from 1.1.1.1: icmp_seq=3 ttl=64 time=0.008 ms
80 bytes from 1.1.1.1: icmp_seq=4 ttl=64 time=0.007 ms
80 bytes from 1.1.1.1: icmp_seq=5 ttl=64 time=0.007 ms

--- 1.1.1.1 ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 1ms
rtt min/avg/max/mdev = 0.007/0.018/0.060/0.020 ms, ipg/ewma 0.307/0.038 ms
#ping 2.2.2.2
PING 2.2.2.2 (2.2.2.2) 72(100) bytes of data.
80 bytes from 2.2.2.2: icmp_seq=1 ttl=64 time=0.033 ms
80 bytes from 2.2.2.2: icmp_seq=2 ttl=64 time=0.004 ms
80 bytes from 2.2.2.2: icmp_seq=3 ttl=64 time=0.002 ms
80 bytes from 2.2.2.2: icmp_seq=4 ttl=64 time=0.003 ms
80 bytes from 2.2.2.2: icmp_seq=5 ttl=64 time=0.002 ms

--- 2.2.2.2 ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 0ms
rtt min/avg/max/mdev = 0.002/0.008/0.033/0.012 ms, ipg/ewma 0.033/0.020 ms
#ping 3.3.3.3
PING 3.3.3.3 (3.3.3.3) 72(100) bytes of data.
80 bytes from 3.3.3.3: icmp_seq=1 ttl=64 time=0.064 ms
80 bytes from 3.3.3.3: icmp_seq=2 ttl=64 time=0.010 ms
80 bytes from 3.3.3.3: icmp_seq=3 ttl=64 time=0.007 ms
80 bytes from 3.3.3.3: icmp_seq=4 ttl=64 time=0.006 ms
80 bytes from 3.3.3.3: icmp_seq=5 ttl=64 time=0.007 ms

--- 3.3.3.3 ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 1ms
rtt min/avg/max/mdev = 0.006/0.018/0.064/0.022 ms, ipg/ewma 0.257/0.040 ms


You are running c version 201710
Entering Authentication Phase...
Enter password: 
Commands from file: run enable ; show ip int brief ; show ip ospf neighbor ; show ip ospf interface brief ; show lldp neighbors ; show ip route ; ping 1.1.1.1 ; ping 2.2.2.2 ; ping 3.3.3.3 ; 
>enable
#show ip int brief
                                                                        Address
Interface       IP Address         Status      Protocol          MTU    Owner  
--------------- ------------------ ----------- ------------- ---------- -------
Ethernet1       192.168.0.3/31     up          up               1500           
Ethernet2       192.168.0.5/31     up          up               1500           
Loopback0       3.3.3.3/32         up          up              65535           
Management0     172.20.20.2/24     up          up               1500           

#show ip ospf neighbor
Neighbor ID     Instance VRF      Pri State                  Dead Time   Address         Interface
1.1.1.1         1        default  1   FULL/BDR               00:00:30    192.168.0.2     Ethernet1
2.2.2.2         1        default  1   FULL/BDR               00:00:36    192.168.0.4     Ethernet2
#show ip ospf interface brief
   Interface          Instance VRF        Area            IP Address         Cost  State      Nbrs
   Lo0                1        default    0.0.0.0         3.3.3.3/32         10    DR         0
   Et1                1        default    0.0.0.0         192.168.0.3/31     10    DR         1
   Et2                1        default    0.0.0.0         192.168.0.5/31     10    DR         1
#show lldp neighbors
Last table change time   : 0:01:01 ago
Number of table inserts  : 4
Number of table deletes  : 0
Number of table drops    : 0
Number of table age-outs : 0

Port          Neighbor Device ID       Neighbor Port ID    TTL
---------- ------------------------ ---------------------- ---
Et1           ceos1                    Ethernet2           120
Et2           ceos2                    Ethernet2           120
Ma0           ceos1                    Management0         120
Ma0           ceos2                    Management0         120

#show ip route

VRF: default
Source Codes:
       C - connected, S - static, K - kernel,
       O - OSPF, O IA - OSPF inter area, O E1 - OSPF external type 1,
       O E2 - OSPF external type 2, O N1 - OSPF NSSA external type 1,
       O N2 - OSPF NSSA external type2, O3 - OSPFv3,
       O3 IA - OSPFv3 inter area, O3 E1 - OSPFv3 external type 1,
       O3 E2 - OSPFv3 external type 2,
       O3 N1 - OSPFv3 NSSA external type 1,
       O3 N2 - OSPFv3 NSSA external type2, B - Other BGP Routes,
       B I - iBGP, B E - eBGP, R - RIP, I L1 - IS-IS level 1,
       I L2 - IS-IS level 2, A B - BGP Aggregate,
       A O - OSPF Summary, NG - Nexthop Group Static Route,
       V - VXLAN Control Service, M - Martian,
       DH - DHCP client installed default route,
       DP - Dynamic Policy Route, L - VRF Leaked,
       G  - gRIBI, RC - Route Cache Route,
       CL - CBF Leaked Route

Gateway of last resort:
 S        0.0.0.0/0 [1/0]
           via 172.20.20.1, Management0

 O        1.1.1.1/32 [110/20]
           via 192.168.0.2, Ethernet1
 O        2.2.2.2/32 [110/20]
           via 192.168.0.4, Ethernet2
 C        3.3.3.3/32
           directly connected, Loopback0
 C        172.20.20.0/24
           directly connected, Management0
 O        192.168.0.0/31 [110/20]
           via 192.168.0.2, Ethernet1
           via 192.168.0.4, Ethernet2
 C        192.168.0.2/31
           directly connected, Ethernet1
 C        192.168.0.4/31
           directly connected, Ethernet2

#ping 1.1.1.1
PING 1.1.1.1 (1.1.1.1) 72(100) bytes of data.
80 bytes from 1.1.1.1: icmp_seq=1 ttl=64 time=0.064 ms
80 bytes from 1.1.1.1: icmp_seq=2 ttl=64 time=0.009 ms
80 bytes from 1.1.1.1: icmp_seq=3 ttl=64 time=0.007 ms
80 bytes from 1.1.1.1: icmp_seq=4 ttl=64 time=0.007 ms
80 bytes from 1.1.1.1: icmp_seq=5 ttl=64 time=0.006 ms

--- 1.1.1.1 ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 1ms
rtt min/avg/max/mdev = 0.006/0.018/0.064/0.022 ms, ipg/ewma 0.307/0.040 ms
#ping 2.2.2.2
PING 2.2.2.2 (2.2.2.2) 72(100) bytes of data.
80 bytes from 2.2.2.2: icmp_seq=1 ttl=64 time=0.061 ms
80 bytes from 2.2.2.2: icmp_seq=2 ttl=64 time=0.011 ms
80 bytes from 2.2.2.2: icmp_seq=3 ttl=64 time=0.003 ms
80 bytes from 2.2.2.2: icmp_seq=4 ttl=64 time=0.002 ms
80 bytes from 2.2.2.2: icmp_seq=5 ttl=64 time=0.002 ms

--- 2.2.2.2 ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 0ms
rtt min/avg/max/mdev = 0.002/0.015/0.061/0.022 ms, ipg/ewma 0.103/0.037 ms
#ping 3.3.3.3
PING 3.3.3.3 (3.3.3.3) 72(100) bytes of data.
80 bytes from 3.3.3.3: icmp_seq=1 ttl=64 time=0.036 ms
80 bytes from 3.3.3.3: icmp_seq=2 ttl=64 time=0.002 ms
80 bytes from 3.3.3.3: icmp_seq=3 ttl=64 time=0.001 ms
80 bytes from 3.3.3.3: icmp_seq=4 ttl=64 time=0.001 ms
80 bytes from 3.3.3.3: icmp_seq=5 ttl=64 time=0.002 ms

--- 3.3.3.3 ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 0ms
rtt min/avg/max/mdev = 0.001/0.008/0.036/0.013 ms, ipg/ewma 0.014/0.021 ms


toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista_ssh$
```
Backout - config removal
```
toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista_ssh$ ./rem_conf_change.sh 
You are running c version 201710
Entering Authentication Phase...
Enter password: 
Commands from file: run enable ; config t ; interface eth1 ; no description ceos1-ceos2 ; no switchport ; no ip address 192.168.0.0/31 ; ip routing  ; no interface loopback41 ; no interface loopback 1 ; interface eth2 ; no description ceos1-ceos3 ; no switchport ; no ip address 192.168.0.2/31 ; no shut ; no interface loopback 0 ; no router ospf 1 ; 
>enable
#config t
(config)#interface eth1
(config-if)#no description ceos1-ceos2
(config-if)#no switchport
(config-if)#no ip address 192.168.0.0/31
(config-if)#ip routing
(config)#no interface loopback41
(config)#no interface loopback 1
(config)#interface eth2
(config-if)#no description ceos1-ceos3
(config-if)#no switchport
(config-if)#no ip address 192.168.0.2/31
(config-if)#no shut
(config-if)#no interface loopback 0
(config)#no router ospf 1


You are running c version 201710
Entering Authentication Phase...
Enter password: 
Commands from file: run enable ; config t ; interface eth1 ; no description ceos2-ceos1 ; no switchport ; no ip address 192.168.0.1/31 ; ip routing  ; no interface loopback41 ; no interface loopback1 ; interface eth2 ; no description ceos2-ceos3 ; no switchport ; no ip address 192.168.0.4/31 ; no shut ; no interface loopback0 ; no router ospf 1 ; 
>enable
#config t
(config)#interface eth1
(config-if)#no description ceos2-ceos1
(config-if)#no switchport
(config-if)#no ip address 192.168.0.1/31
(config-if)#ip routing
(config)#no interface loopback41
(config)#no interface loopback1
(config)#interface eth2
(config-if)#no description ceos2-ceos3
(config-if)#no switchport
(config-if)#no ip address 192.168.0.4/31
(config-if)#no shut
(config-if)#no interface loopback0
(config)#no router ospf 1


You are running c version 201710
Entering Authentication Phase...
Enter password: 
Commands from file: run enable ; config t ; interface eth1 ; no description ceos3-ceos1 ; no switchport ; no ip address 192.168.0.3/31 ; no shut ; ip routing  ; no interface loopback41 ; interface eth2 ; no description ceos1-ceos3 ; no switchport ; no ip address 192.168.0.5/31 ; no shut ; no interface loopback 0 ; no router ospf 1 ; 
>enable
#config t
(config)#interface eth1
(config-if)#no description ceos3-ceos1
(config-if)#no switchport
(config-if)#no ip address 192.168.0.3/31
(config-if)#no shut
(config-if)#ip routing
(config)#no interface loopback41
(config)#interface eth2
(config-if)#no description ceos1-ceos3
(config-if)#no switchport
(config-if)#no ip address 192.168.0.5/31
(config-if)#no shut
(config-if)#no interface loopback 0
(config)#no router ospf 1


toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista_ssh$
```
