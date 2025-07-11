How to run script...
- show comands
- configuration commands
```
$ ./ssh_cli_script "sbx-nxos-mgmt.cisco.com" "username" "password" "show run | include loopback" "config t ; interface loopback64 ; ip address 10.64.64.64 255.255.255.255 ; description test_interface"  "sh run interface loopback64"

Command: show run | include loopback
interface loopback0
interface loopback1
interface loopback2
interface loopback3
interface loopback4
interface loopback8
interface loopback9
interface loopback10
interface loopback16
interface loopback17
interface loopback18
interface loopback30
interface loopback66
interface loopback68
interface loopback75
interface loopback80
interface loopback99
interface loopback101
interface loopback123
    update-source loopback0
event manager applet loopback_down
  event syslog pattern "interface loopback 75, changed state to administratively down"
  action 3.0 cli command "interface loopback 75"

Command: config t ; interface loopback64 ; ip address 10.64.64.64 255.255.255.255 ; description test_interface

Command: sh run interface loopback64

!Command: show running-config interface loopback64
!Running configuration last done at: Thu Jul 10 22:10:26 2025
!Time: Thu Jul 10 22:10:29 2025

version 10.3(3) Bios:version  

interface loopback64
  description test_interface
  ip address 10.64.64.64/32



$
```
