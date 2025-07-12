07/12/2025

Step 1.
Just building functionality in to file open and read process
- archive/open_file_and_read_1.c - original code moved to archive
- commands.txt
- The 0 0 are place holders we want the file to be located at position 3 or argv[3]
```
$ ./openfile 0 0 commands.txt 

config t

interface loopback 1
 ip address 1.1.1.1 255.255.255.255
 description test_config

ip routing

router ospf 1
 network 1.1.1.1 0.0.0.0 area 0
exit
exit

$
```
Step 2.
Now after reading through the existing code the commands syntax "cmd1 ; cmd2 ; cmd3".
So we will have to tweak the openfile code remove carriage returns and newline (\r\n) and replace it with " ; "
This will be iterative.
- open_file_and_read.c
- commands.txt
```
$ ./openfile 0 0 commands.txt 
config t ; interface loopback 1 ;  ip address 1.1.1.1 255.255.255.255 ;  description test_config ; ip routing ; router ospf 1 ;  network 1.1.1.1 0.0.0.0 area 0 ; exit ; exit ;  
```
Step 3.
In corporate this code into the ssh code from example1 removing the cli syntax and using a file for the code or commands.
- ssh_script.c - now has the open_file_and_read.c code encorporated. The lines of code that were changed or add were lines 5-7, and 244-263. These lines could change but it give you a starting point.
- The idea is rather than use the actual cli commands from the command line you will call the file with those commands in position 3 of argv
- This commands2.txt is just show commands
```
toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista_ssh$ cat commands2.txt
run enable
show version
show ip route
show lldp neighbor
toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista_ssh$ ./ssh_script clab-lab3-ceos2 admin commands2.txt
You are running c version 201710
Entering Authentication Phase...
Enter password: admin

Commands from file: run enable ; show version ; show ip route ; show lldp neighbor ; 
>enable
#show version
Arista cEOSLab
Hardware version: 
Serial number: 46B75E11505A22995187CC0FA4CE9769
Hardware MAC address: 001c.7385.9989
System MAC address: 001c.7385.9989

Software image version: 4.34.1F-41910228.orinocorel (engineering build)
Architecture: aarch64
Internal build version: 4.34.1F-41910228.orinocorel
Internal build ID: 81163ad0-9b7a-4970-994c-32d9d3d2ccdb
Image format version: 1.0
Image optimization: None

Kernel version: 6.14.10-orbstack-00291-g1b252bd3edea

Uptime: 3 days, 19 hours and 34 minutes
Total memory: 8187844 kB
Free memory: 3158136 kB

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
           directly connected, Loopback1
 C        172.20.20.0/24
           directly connected, Management0

#show lldp neighbor
Last table change time   : 11:30:02 ago
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



toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista_ssh$ 
```
Now to test the configuration capabilities
One thing with arista you need to include the "run enable" to script multiple commands. 
So I added it to the top of commands.txt file.
```
toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista_ssh$ cat commands.txt
run enable
config t

interface loopback 1
 ip address 1.1.1.1 255.255.255.255
 description test_config

ip routing

router ospf 1
 network 1.1.1.1 0.0.0.0 area 0
exit
exit

show run

toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista_ssh$ ./ssh_script clab-lab3-ceos2 admin commands.txt
You are running c version 201710
Entering Authentication Phase...
Enter password: admin

Commands from file: run enable ; config t ; interface loopback 1 ;  ip address 1.1.1.1 255.255.255.255 ;  description test_config ; ip routing ; router ospf 1 ;  network 1.1.1.1 0.0.0.0 area 0 ; exit ; exit ; show run ; 
>enable
#config t
(config)#interface loopback 1
(config-if)#ip address 1.1.1.1 255.255.255.255
(config-if)#description test_config
(config-if)#ip routing
(config)#router ospf 1
(config-router)#network 1.1.1.1 0.0.0.0 area 0
(config-router)#exit
(config)#exit
#show run
! Command: show running-config
! device: ceos2 (cEOSLab, EOS-4.34.1F-41910228.orinocorel (engineering build))
!
no aaa root
!
username admin privilege 15 role network-admin secret sha512 $6$Qv9eTIlxpp062xCQ$T84V5N2nygJFt0Qk.zXDCRrsRTzsJbywy7xgc5Bz1dUs6p3rkAKvQZwgdkhWKmmoclvMVU5fwgNH6q.p3HKT21
!
management api http-commands
   no shutdown
!
no service interface inactive port-id allocation disabled
!
transceiver qsfp default-mode 4x10G
!
service routing protocols model multi-agent
!
hostname ceos2
!
spanning-tree mode mstp
!
system l1
   unsupported speed action error
   unsupported error-correction action error
!
management api gnmi
   transport grpc default
!
management api netconf
   transport ssh default
!
interface Ethernet1
!
interface Ethernet2
!
interface Ethernet3
!
interface Loopback1
   description test_config
   ip address 1.1.1.1/32
!
interface Management0
   ip address 172.20.20.4/24
   ipv6 address 3fff:172:20:20::4/64
!
ip routing
!
ip route 0.0.0.0/0 172.20.20.1
!
ipv6 route ::/0 3fff:172:20:20::1
!
router multicast
   ipv4
      software-forwarding kernel
   !
   ipv6
      software-forwarding kernel
!
router ospf 1
   network 1.1.1.1/32 area 0.0.0.0
   max-lsa 12000
!
end

```
