#!/bin/bash

echo "admin" | ./ssh_script clab-lab3-ceos1 "admin" "configs/ceos1.cfg" 
echo "admin" | ./ssh_script clab-lab3-ceos2 "admin" "configs/ceos2.cfg" 
echo "admin" | ./ssh_script clab-lab3-ceos3 "admin" "configs/ceos3.cfg" 
