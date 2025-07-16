How to run script...
- show comands before
- The username and password have been intensionally changed as the vendor doesnt like when you post them.
  
```
$ ./ssh_cli_script "sbx-nxos-mgmt.cisco.com" "username" "password" "show ip interface brief" "show ip route"

Command: show ip interface brief

IP Interface Status for VRF "default"(1)
Interface            IP Address      Interface Status
Lo0                  10.10.10.1      protocol-up/link-up/admin-up       
Lo2                  2.2.2.2         protocol-up/link-up/admin-up       
Lo3                  3.3.3.3         protocol-up/link-up/admin-up       
Lo4                  4.4.4.4         protocol-up/link-up/admin-up       
Lo8                  192.168.61.1    protocol-up/link-up/admin-up       
Lo9                  192.168.62.1    protocol-up/link-up/admin-up       
Lo10                 192.168.63.1    protocol-up/link-up/admin-up       
Lo16                 192.168.16.5    protocol-up/link-up/admin-up       
Lo17                 192.168.17.5    protocol-up/link-up/admin-up       
Lo18                 192.168.18.5    protocol-up/link-up/admin-up       
Lo99                 10.99.99.1      protocol-up/link-up/admin-up       

Command: show ip route
IP Route Table for VRF "default"
'*' denotes best ucast next-hop
'**' denotes best mcast next-hop
'[x/y]' denotes [preference/metric]
'%<string>' in via output denotes VRF <string>

2.2.2.0/24, ubest/mbest: 1/0, attached
    *via 2.2.2.2, Lo2, [0/0], 2d03h, direct
2.2.2.2/32, ubest/mbest: 1/0, attached
    *via 2.2.2.2, Lo2, [0/0], 2d03h, local
3.3.3.0/24, ubest/mbest: 1/0, attached
    *via 3.3.3.3, Lo3, [0/0], 2d03h, direct
3.3.3.3/32, ubest/mbest: 1/0, attached
    *via 3.3.3.3, Lo3, [0/0], 2d03h, local
4.4.4.0/24, ubest/mbest: 1/0, attached
    *via 4.4.4.4, Lo4, [0/0], 2d03h, direct
4.4.4.4/32, ubest/mbest: 1/0, attached
    *via 4.4.4.4, Lo4, [0/0], 2d03h, local
10.10.10.1/32, ubest/mbest: 2/0, attached
    *via 10.10.10.1, Lo0, [0/0], 2d03h, local
    *via 10.10.10.1, Lo0, [0/0], 2d03h, direct
10.99.99.0/24, ubest/mbest: 1/0, attached
    *via 10.99.99.1, Lo99, [0/0], 2d03h, direct
10.99.99.1/32, ubest/mbest: 1/0, attached
    *via 10.99.99.1, Lo99, [0/0], 2d03h, local
192.168.16.0/24, ubest/mbest: 1/0, attached
    *via 192.168.16.5, Lo16, [0/0], 2d03h, direct
192.168.16.5/32, ubest/mbest: 1/0, attached
    *via 192.168.16.5, Lo16, [0/0], 2d03h, local
192.168.17.0/24, ubest/mbest: 1/0, attached
    *via 192.168.17.5, Lo17, [0/0], 2d03h, direct
192.168.17.5/32, ubest/mbest: 1/0, attached
    *via 192.168.17.5, Lo17, [0/0], 2d03h, local
192.168.18.0/24, ubest/mbest: 1/0, attached
    *via 192.168.18.5, Lo18, [0/0], 2d03h, direct
192.168.18.5/32, ubest/mbest: 1/0, attached
    *via 192.168.18.5, Lo18, [0/0], 2d03h, local
192.168.61.0/24, ubest/mbest: 1/0, attached
    *via 192.168.61.1, Lo8, [0/0], 2d03h, direct
192.168.61.1/32, ubest/mbest: 1/0, attached
    *via 192.168.61.1, Lo8, [0/0], 2d03h, local
192.168.62.0/24, ubest/mbest: 1/0, attached
    *via 192.168.62.1, Lo9, [0/0], 2d03h, direct
192.168.62.1/32, ubest/mbest: 1/0, attached
    *via 192.168.62.1, Lo9, [0/0], 2d03h, local
192.168.63.0/24, ubest/mbest: 1/0, attached
    *via 192.168.63.1, Lo10, [0/0], 2d03h, direct
192.168.63.1/32, ubest/mbest: 1/0, attached
    *via 192.168.63.1, Lo10, [0/0], 2d03h, local

```
- configuration commands
- The confiuguration portion of the command has semicolon with a space on each side " ; "  to represent nested behavior of the command. The config portion should also be inside of double quotes.
- Notice the show comands have no semicolon and are seperated by white space.
- One caveat in the configuration portion of the command you must add the line description last. With Cisco nxos it does not see the " ; " as a line break, it sees it as additional text to add to the description.
- This issue gets dealt with in example2.
```
$ ./ssh_cli_script "sbx-nxos-mgmt.cisco.com" "username" "password" "config t ; interface loopback64 ; ip address 10.64.64.64 255.255.255.255 ; description test_interface"  "sh run interface loopback64"

Command: config t ; interface loopback64 ; ip address 10.64.64.64 255.255.255.255 ; description test_interface

Command: sh run interface loopback64

!Command: show running-config interface loopback64
!Running configuration last done at: Fri Jul 11 00:56:38 2025
!Time: Fri Jul 11 00:56:41 2025

version 10.3(3) Bios:version  

interface loopback64
  description test_interface
  ip address 10.64.64.64/32

```
- show commands after
```
$ ./ssh_cli_script "sbx-nxos-mgmt.cisco.com" "username" "password" "show ip interface brief" "show ip route"

Command: show ip interface brief

IP Interface Status for VRF "default"(1)
Interface            IP Address      Interface Status
Lo0                  10.10.10.1      protocol-up/link-up/admin-up       
Lo2                  2.2.2.2         protocol-up/link-up/admin-up       
Lo3                  3.3.3.3         protocol-up/link-up/admin-up       
Lo4                  4.4.4.4         protocol-up/link-up/admin-up       
Lo8                  192.168.61.1    protocol-up/link-up/admin-up       
Lo9                  192.168.62.1    protocol-up/link-up/admin-up       
Lo10                 192.168.63.1    protocol-up/link-up/admin-up       
Lo16                 192.168.16.5    protocol-up/link-up/admin-up       
Lo17                 192.168.17.5    protocol-up/link-up/admin-up       
Lo18                 192.168.18.5    protocol-up/link-up/admin-up       
Lo64                 10.64.64.64     protocol-up/link-up/admin-up       
Lo99                 10.99.99.1      protocol-up/link-up/admin-up       

Command: show ip route
IP Route Table for VRF "default"
'*' denotes best ucast next-hop
'**' denotes best mcast next-hop
'[x/y]' denotes [preference/metric]
'%<string>' in via output denotes VRF <string>

2.2.2.0/24, ubest/mbest: 1/0, attached
    *via 2.2.2.2, Lo2, [0/0], 2d03h, direct
2.2.2.2/32, ubest/mbest: 1/0, attached
    *via 2.2.2.2, Lo2, [0/0], 2d03h, local
3.3.3.0/24, ubest/mbest: 1/0, attached
    *via 3.3.3.3, Lo3, [0/0], 2d03h, direct
3.3.3.3/32, ubest/mbest: 1/0, attached
    *via 3.3.3.3, Lo3, [0/0], 2d03h, local
4.4.4.0/24, ubest/mbest: 1/0, attached
    *via 4.4.4.4, Lo4, [0/0], 2d03h, direct
4.4.4.4/32, ubest/mbest: 1/0, attached
    *via 4.4.4.4, Lo4, [0/0], 2d03h, local
10.10.10.1/32, ubest/mbest: 2/0, attached
    *via 10.10.10.1, Lo0, [0/0], 2d03h, local
    *via 10.10.10.1, Lo0, [0/0], 2d03h, direct
10.64.64.64/32, ubest/mbest: 2/0, attached
    *via 10.64.64.64, Lo64, [0/0], 00:00:11, local
    *via 10.64.64.64, Lo64, [0/0], 00:00:11, direct
10.99.99.0/24, ubest/mbest: 1/0, attached
    *via 10.99.99.1, Lo99, [0/0], 2d03h, direct
10.99.99.1/32, ubest/mbest: 1/0, attached
    *via 10.99.99.1, Lo99, [0/0], 2d03h, local
192.168.16.0/24, ubest/mbest: 1/0, attached
    *via 192.168.16.5, Lo16, [0/0], 2d03h, direct
192.168.16.5/32, ubest/mbest: 1/0, attached
    *via 192.168.16.5, Lo16, [0/0], 2d03h, local
192.168.17.0/24, ubest/mbest: 1/0, attached
    *via 192.168.17.5, Lo17, [0/0], 2d03h, direct
192.168.17.5/32, ubest/mbest: 1/0, attached
    *via 192.168.17.5, Lo17, [0/0], 2d03h, local
192.168.18.0/24, ubest/mbest: 1/0, attached
    *via 192.168.18.5, Lo18, [0/0], 2d03h, direct
192.168.18.5/32, ubest/mbest: 1/0, attached
    *via 192.168.18.5, Lo18, [0/0], 2d03h, local
192.168.61.0/24, ubest/mbest: 1/0, attached
    *via 192.168.61.1, Lo8, [0/0], 2d03h, direct
192.168.61.1/32, ubest/mbest: 1/0, attached
    *via 192.168.61.1, Lo8, [0/0], 2d03h, local
192.168.62.0/24, ubest/mbest: 1/0, attached
    *via 192.168.62.1, Lo9, [0/0], 2d03h, direct
192.168.62.1/32, ubest/mbest: 1/0, attached
    *via 192.168.62.1, Lo9, [0/0], 2d03h, local
192.168.63.0/24, ubest/mbest: 1/0, attached
    *via 192.168.63.1, Lo10, [0/0], 2d03h, direct
192.168.63.1/32, ubest/mbest: 1/0, attached
    *via 192.168.63.1, Lo10, [0/0], 2d03h, local



$
```
- How to navigate syntax to configure multiple interfaces and run show commands

```
toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/cisco$ ./ssh_cli_script "sbx-nxos-mgmt.cisco.com" "username" "password" "config t ; interface loopback64 ; ip address 10.64.64.64 255.255.255.255 ; description test_script2"  "config t ; interface loopback 65 ; description test_script_2" "sh run interface loopback64" "show run int loopback65"

Command: config t ; interface loopback64 ; ip address 10.64.64.64 255.255.255.255 ; description test_script2

Command: config t ; interface loopback 65 ; description test_script_2

Command: sh run interface loopback64

!Command: show running-config interface loopback64
!Running configuration last done at: Tue Jul 15 17:25:00 2025
!Time: Tue Jul 15 17:25:03 2025

version 10.3(3) Bios:version  

interface loopback64
  description test_script2
  ip address 10.64.64.64/32


Command: show run int loopback65

!Command: show running-config interface loopback65
!Running configuration last done at: Tue Jul 15 17:25:00 2025
!Time: Tue Jul 15 17:25:04 2025

version 10.3(3) Bios:version  

interface loopback65
  description test_script_2

```
