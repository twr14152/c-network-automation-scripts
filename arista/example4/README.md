### Much simpler way to write a C script to manage devices using ssh

- So I will say this was a hell of a lot easier than using libssh.
- I used **stdlib.h** with **system()** which can call shell commands, and in my case ssh.
- I did install sshpass to call the password in the script so I didn't have to keep entering it while the script was running.
- This script was a good lesson in utilizing tools that are already at our disposal, its just a matter of taking advantage of them.
  
```
todd@todd-TOSHIBA-DX735:~/Code_folder/containerlab/containerlabs_sandbox/ceos_lab/lab1$ ./c_ssh admin
Connecting to clab-lab1-ceos1
Running command sshpass -p admin ssh admin@clab-lab1-ceos1 < commands.txt
Pseudo-terminal will not be allocated because stdin is not a terminal.
Warning: Permanently added 'clab-lab1-ceos1' (ED25519) to the list of known hosts.
                                                                        Address
Interface       IP Address          Status      Protocol         MTU    Owner  
--------------- ------------------- ----------- ------------- --------- -------
Management0     172.20.20.2/24      up          up              1500           

interface Loopback1
   description test_script
   ip address 1.1.1.1/32
                                                                        Address
Interface       IP Address         Status      Protocol          MTU    Owner  
--------------- ------------------ ----------- ------------- ---------- -------
Loopback1       1.1.1.1/32         up          up              65535           
Management0     172.20.20.2/24     up          up               1500           

                                                                        Address
Interface       IP Address          Status      Protocol         MTU    Owner  
--------------- ------------------- ----------- ------------- --------- -------
Management0     172.20.20.2/24      up          up              1500           

Connecting to clab-lab1-ceos2
Running command sshpass -p admin ssh admin@clab-lab1-ceos2 < commands.txt
Pseudo-terminal will not be allocated because stdin is not a terminal.
Warning: Permanently added 'clab-lab1-ceos2' (ED25519) to the list of known hosts.
                                                                        Address
Interface       IP Address          Status      Protocol         MTU    Owner  
--------------- ------------------- ----------- ------------- --------- -------
Management0     172.20.20.5/24      up          up              1500           

interface Loopback1
   description test_script
   ip address 1.1.1.1/32
                                                                        Address
Interface       IP Address         Status      Protocol          MTU    Owner  
--------------- ------------------ ----------- ------------- ---------- -------
Loopback1       1.1.1.1/32         up          up              65535           
Management0     172.20.20.5/24     up          up               1500           

                                                                        Address
Interface       IP Address          Status      Protocol         MTU    Owner  
--------------- ------------------- ----------- ------------- --------- -------
Management0     172.20.20.5/24      up          up              1500           


```
