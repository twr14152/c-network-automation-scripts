#!/bin/sh

# configure
./http_client_using_files clab-lab3-ceos1 admin admin cmds1.txt
./http_client_using_files clab-lab3-ceos2 admin admin cmds1.txt
./http_client_using_files clab-lab3-ceos3 admin admin cmds1.txt

# validate
./http_client_using_files clab-lab3-ceos1 admin admin cmds2.txt
./http_client_using_files clab-lab3-ceos2 admin admin cmds2.txt
./http_client_using_files clab-lab3-ceos3 admin admin cmds2.txt
