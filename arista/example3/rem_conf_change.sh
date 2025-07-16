#!/bin/bash

echo "admin" | ./ssh_script clab-lab3-ceos1 "admin" "configs/remove_ceos1.cfg" 
echo "admin" | ./ssh_script clab-lab3-ceos2 "admin" "configs/remove_ceos2.cfg" 
echo "admin" | ./ssh_script clab-lab3-ceos3 "admin" "configs/remove_ceos3.cfg" 
