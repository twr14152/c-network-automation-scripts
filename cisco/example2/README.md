# Log

### 07/14/2025
- Broke the scripts up into conf and show commands
  * ssh_conf.c - run config commands from file
  * ssh_exec_cmds.c - run show commands from file
- This just seemed cleaner

### 07/13/2025
- This script allows you to call a file which can hold configurations or show commands. 
- The script doesn't care what you name the file only that its in the fouth position when you run the script (./script 0 0 0 file).
- This was a little tricky in that Cisco device behaved a differently than arista when it cames to terminating lines with " ; " with interface descriptions.
- It wouldnt terminate the line following the description using " ; ". The commands that followed became part of the description including the semicolon and everything that followed.
- So I had to switch to interactive shell with the session in order for nested configurations to work properly.
- This method maybe the go farward path as it actually involves less mental gynamtics with appending and formating the data to work with the devices.
- I do believe ssh_channel_request_exec() was designed to send a command to a remote device. The " ; " was a way to send multiple commands on linux based systems. It worked fine for show commands and it works fine for both show and configs for the arista but not for the cisco.
- The fix was to move away from ssh_channel_request_exec() and use
   * ssh_channel_request_pty(channel)
   * ssh_channel_request_shell(channel)
   * ssh_channel_write(channel, line, strlen(line)) 

config script
```
toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/cisco$ cat config.txt 
config t

interface loopback 41
ip address 41.41.41.41 255.255.255.255
description testing_script

toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/cisco$ ./ssh_conf "sbx-nxos-mgmt.cisco.com" "username" "password" "config.txt"

config t
interface loopback 41
ip address 41.41.41.41 255.255.255.255
description testing_script
exit
exit
exit
Cisco NX-OS Software
Copyright (c) 2002-2023, Cisco Systems, Inc. All rights reserved.
Nexus 9000v software ("Nexus 9000v Software") and related documentation,
files or other reference materials ("Documentation") are
the proprietary property and confidential information of Cisco
Systems, Inc. ("Cisco") and are protected, without limitation,
pursuant to United States and International copyright and trademark
laws in the applicable jurisdiction which provide civil and criminal
penalties for copying or distribution without Cisco's authorization.

Any use or disclosure, in whole or in part, of the Nexus 9000v Software
or Documentation to any third party for any purposes is expressly
prohibited except as otherwise authorized by Cisco in writing.
The copyrights to certain works contained herein are owned by other
third parties and are used and distributed under license. Some parts
of this software may be covered under the GNU Public License or the
GNU Lesser General Public License. A copy of each such license is
available at
http://www.gnu.org/licenses/gpl.html and
http://www.gnu.org/licenses/lgpl.html
***************************************************************************
*  Nexus 9000v is strictly limited to use for evaluation, demonstration   *
*  and NX-OS education. Any use or disclosure, in whole or in part of     *
*  the Nexus 9000v Software or Documentation to any third party for any   *
*  purposes is expressly prohibited except as otherwise authorized by     *
*  Cisco in writing.                                                      *
***************************************************************************
nxos# config t
Enter configuration commands, one per line. End with CNTL/Z.
nxos(config)# interface loopback 41
nxos(config-if)# ip address 41.41.41.41 255.255.255.255
nxos(config-if)# description testing_script
nxos(config-if)# exit
nxos(config)# exit
nxos# exit

```
show commands
```
toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/cisco$ cat commands.txt 

show ip interface brief
show run interface loop41
show interface loopback 41
toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/cisco$ ./ssh_exec_cmds "sbx-nxos-mgmt.cisco.com" "username" "password" "commands.txt"

IP Interface Status for VRF "default"(1)
Interface            IP Address      Interface Status
Lo41                 41.41.41.41     protocol-up/link-up/admin-up       

!Command: show running-config interface loopback41
!Running configuration last done at: Sun Jul 13 18:51:00 2025
!Time: Sun Jul 13 18:51:24 2025

version 10.3(3) Bios:version  

interface loopback41
  description testing_script
  ip address 41.41.41.41/32

loopback41 is up
admin state is up,
  Hardware: Loopback
  Description: testing_script
  Internet Address is 41.41.41.41/32
  MTU 1500 bytes, BW 8000000 Kbit , DLY 5000 usec
  reliability 255/255, txload 1/255, rxload 1/255
  Encapsulation LOOPBACK, medium is broadcast
  Auto-mdix is turned off
    0 packets input 0 bytes
    0 multicast frames 0 compressed
    0 input errors 0 frame 0 overrun 0 fifo
    0 packets output 0 bytes 0 underruns
    0 output errors 0 collisions 0 fifo
    0 out_carrier_errors



toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/cisco$ 
```







