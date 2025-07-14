#!/bin/bash


echo "admin" | ./ssh_script clab-lab3-ceos1 "admin" "show_cmds/pre_change_cmds.txt" 
echo "admin" | ./ssh_script clab-lab3-ceos2 "admin" "show_cmds/pre_change_cmds.txt" 
echo "admin" | ./ssh_script clab-lab3-ceos3 "admin" "show_cmds/pre_change_cmds.txt" 
