07/12/2025
Step 1.
Just building functionality in to file open and read process
- archive/open_file_and_read_1.c - original code moved to archive
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


