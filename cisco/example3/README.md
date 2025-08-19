### Script output

```
todd@todd-TOSHIBA-DX735:~/Code_folder/containerlab/containerlabs_sandbox/ceos_lab/lab1$ ./c_ssh <password>
Connecting to sandbox-nxos-1.cisco.com
Running command sshpass -p <cropped> ssh admin@sandbox-nxos-1.cisco.com < commands.txt
Pseudo-terminal will not be allocated because stdin is not a terminal.

"Hello there! Hoping you are having a great day
... Welcome to 'nxos',
 your favorite CISCO.NXOS.NXOS Sandbox"

stty: 'standard input': Inappropriate ioctl for device
Syntax error while parsing 'enable'


IP Interface Status for VRF "default"(1)
Interface            IP Address      Interface Status
Vlan10               192.168.10.1    protocol-down/link-down/admin-up   
Vlan11               192.168.10.2    protocol-down/link-down/admin-down 
Vlan100              172.16.100.1    protocol-down/link-down/admin-up   
Vlan101              172.16.101.1    protocol-down/link-down/admin-up   
Vlan102              172.16.102.1    protocol-down/link-down/admin-up   
Vlan103              172.16.103.1    protocol-down/link-down/admin-up   
Vlan104              172.16.104.1    protocol-down/link-down/admin-up   
Vlan105              172.16.105.1    protocol-down/link-down/admin-up   
Vlan1000             25.25.25.25     protocol-down/link-down/admin-up   
Lo1                  172.16.0.1      protocol-up/link-up/admin-up       
Lo2                  2.2.2.2         protocol-up/link-up/admin-up       
Lo3                  4.4.4.4         protocol-up/link-up/admin-up       
Lo52                 10.99.52.52     protocol-up/link-up/admin-up       
Lo98                 10.98.98.1      protocol-up/link-up/admin-up       
Lo99                 10.99.99.1      protocol-up/link-up/admin-up       
Lo100                192.168.100.1   protocol-up/link-up/admin-up       
Lo102                10.102.136.1    protocol-up/link-up/admin-up       
Lo168                192.168.22.1    protocol-up/link-up/admin-up       
Lo172                172.18.0.1      protocol-up/link-up/admin-up       
Lo248                10.248.0.1      protocol-up/link-up/admin-up       
Eth1/5               172.16.1.1      protocol-up/link-up/admin-up       

!Command: show running-config interface loopback22
!Running configuration last done at: Tue Aug 19 04:40:21 2025
!Time: Tue Aug 19 04:40:21 2025

version 10.3(3) Bios:version  

interface loopback22
  description c is better than python
  ip address 22.22.22.22/32


IP Interface Status for VRF "default"(1)
Interface            IP Address      Interface Status
Vlan10               192.168.10.1    protocol-down/link-down/admin-up   
Vlan11               192.168.10.2    protocol-down/link-down/admin-down 
Vlan100              172.16.100.1    protocol-down/link-down/admin-up   
Vlan101              172.16.101.1    protocol-down/link-down/admin-up   
Vlan102              172.16.102.1    protocol-down/link-down/admin-up   
Vlan103              172.16.103.1    protocol-down/link-down/admin-up   
Vlan104              172.16.104.1    protocol-down/link-down/admin-up   
Vlan105              172.16.105.1    protocol-down/link-down/admin-up   
Vlan1000             25.25.25.25     protocol-down/link-down/admin-up   
Lo1                  172.16.0.1      protocol-up/link-up/admin-up       
Lo2                  2.2.2.2         protocol-up/link-up/admin-up       
Lo3                  4.4.4.4         protocol-up/link-up/admin-up       
Lo22                 22.22.22.22     protocol-up/link-up/admin-up       
Lo52                 10.99.52.52     protocol-up/link-up/admin-up       
Lo98                 10.98.98.1      protocol-up/link-up/admin-up       
Lo99                 10.99.99.1      protocol-up/link-up/admin-up       
Lo100                192.168.100.1   protocol-up/link-up/admin-up       
Lo102                10.102.136.1    protocol-up/link-up/admin-up       
Lo168                192.168.22.1    protocol-up/link-up/admin-up       
Lo172                172.18.0.1      protocol-up/link-up/admin-up       
Lo248                10.248.0.1      protocol-up/link-up/admin-up       
Eth1/5               172.16.1.1      protocol-up/link-up/admin-up       
todd@todd-TOSHIBA-DX735:~/Code_folder/containerlab/containerlabs_sandbox/ceos_lab/lab1$ 



````
