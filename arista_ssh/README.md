How to use scripts.

- show commands
```
$ ./ssh_interactive_cli clab-lab3-ceos1 admin "run enable ; show ip int brief ; show version"

You are running c version 201710
Entering Authentication Phase...
Enter password: admin

Command: run enable ; show ip int brief ; show version
>enable
#show ip int brief
                                                                        Address
Interface       IP Address          Status      Protocol         MTU    Owner  
--------------- ------------------- ----------- ------------- --------- -------
Ethernet1       10.0.1.1/24         up          up              1500           
Management0     172.20.20.3/24      up          up              1500           

#show version
Arista cEOSLab
Hardware version: 
Serial number: 2E8B4DF570FC30AA49E0FBA3875C5075
Hardware MAC address: 001c.738a.af31
System MAC address: 001c.738a.af31

Software image version: 4.34.1F-41910228.orinocorel (engineering build)
Architecture: aarch64
Internal build version: 4.34.1F-41910228.orinocorel
Internal build ID: 81163ad0-9b7a-4970-994c-32d9d3d2ccdb
Image format version: 1.0
Image optimization: None

Kernel version: 6.14.10-orbstack-00291-g1b252bd3edea

Uptime: 2 days, 17 hours and 18 minutes
Total memory: 8187844 kB
Free memory: 3204376 kB

```


- configuration commands
```
toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista_ssh$ ./ssh_interactive_cli clab-lab3-ceos1 admin "run enable ; show run ; config ; interface loopback 1 ; ip address 1.1.1.1/32 ; description test_script_interface ; exit ; exit ;  show run"
You are running c version 201710
Entering Authentication Phase...
Enter password: admin

Command: run enable ; show run ; config ; interface loopback 1 ; ip address 1.1.1.1/32 ; description test_script_interface ; exit ; exit ;  show run
>enable
#show run
! Command: show running-config
! device: ceos1 (cEOSLab, EOS-4.34.1F-41910228.orinocorel (engineering build))
!
no aaa root
!
username admin privilege 15 role network-admin secret sha512 $6$nteiCUhy9aSEymNH$f4C2Lj4xlUfpENHsD7hP3Lk2w.hTBpEEbc4awZe0GgK/pOvACzJ5bq4W028Aq8s3ZDloGdjVfFgp/p1g4QuWI/
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
hostname ceos1
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
   no switchport
   ip address 10.0.1.1/24
!
interface Ethernet2
!
interface Ethernet3
!
interface Management0
   ip address 172.20.20.3/24
   ipv6 address 3fff:172:20:20::3/64
!
no ip routing
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
end
#config
(config)#interface loopback 1
(config-if)#ip address 1.1.1.1/32
(config-if)#description test_script_interface
(config-if)#exit
(config)#exit
#show run
! Command: show running-config
! device: ceos1 (cEOSLab, EOS-4.34.1F-41910228.orinocorel (engineering build))
!
no aaa root
!
username admin privilege 15 role network-admin secret sha512 $6$nteiCUhy9aSEymNH$f4C2Lj4xlUfpENHsD7hP3Lk2w.hTBpEEbc4awZe0GgK/pOvACzJ5bq4W028Aq8s3ZDloGdjVfFgp/p1g4QuWI/
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
hostname ceos1
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
   no switchport
   ip address 10.0.1.1/24
!
interface Ethernet2
!
interface Ethernet3
!
interface Loopback1
   description test_script_interface
   ip address 1.1.1.1/32
!
interface Management0
   ip address 172.20.20.3/24
   ipv6 address 3fff:172:20:20::3/64
!
no ip routing
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
end


toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista_ssh$ 
```
