07/12/2025
Just building functionality in to file open and read process
- open_file_and_read.c
- commands.txt
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
