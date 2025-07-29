# http client using command file

- Using shell script to bundle commands to push out to multiple devices
- The script will push config then validate
- The process of generating self-signed-certificates was manual per device

### config file
```
 (myenv_py3.11) toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista/httpClient$ cat cmds1.txt 
enable
configure
management security
 ssl profile self-signed-certs
 certificate self-signed.crt key self-signed.key

management api http-commands
 protocol https ssl profile self-signed-certs

management api restconf
transport https default
ssl profile self-signed-certs

(myenv_py3.11) 
```
### validation commands
```
toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista/httpClient$ cat cmds2.txt 
enable
show management api restconf
(myenv_py3.11) toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista/httpClient$ 
```
### run the shell script
```
(myenv_py3.11) toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista/httpClient$ ./run_http_cmds.sh 
You are connecting to: https://clab-lab3-ceos1/command-api

Commands from file:
enable
configure
management security
 ssl profile self-signed-certs
 certificate self-signed.crt key self-signed.key
management api http-commands
 protocol https ssl profile self-signed-certs
management api restconf
transport https default
ssl profile self-signed-certs
Pretty JSON:
{
	"jsonrpc":	"2.0",
	"id":	"1",
	"result":	[{
		}, {
		}, {
		}, {
		}, {
		}, {
		}, {
		}, {
		}, {
		}, {
		}]
}
You are connecting to: https://clab-lab3-ceos2/command-api

Commands from file:
enable
configure
management security
 ssl profile self-signed-certs
 certificate self-signed.crt key self-signed.key
management api http-commands
 protocol https ssl profile self-signed-certs
management api restconf
transport https default
ssl profile self-signed-certs
Pretty JSON:
{
	"jsonrpc":	"2.0",
	"id":	"1",
	"result":	[{
		}, {
		}, {
		}, {
		}, {
		}, {
		}, {
		}, {
		}, {
		}, {
		}]
}
You are connecting to: https://clab-lab3-ceos3/command-api

Commands from file:
enable
configure
management security
 ssl profile self-signed-certs
 certificate self-signed.crt key self-signed.key
management api http-commands
 protocol https ssl profile self-signed-certs
management api restconf
transport https default
ssl profile self-signed-certs
Pretty JSON:
{
	"jsonrpc":	"2.0",
	"id":	"1",
	"result":	[{
		}, {
		}, {
		}, {
		}, {
		}, {
		}, {
		}, {
		}, {
		}, {
		}]
}
You are connecting to: https://clab-lab3-ceos1/command-api

Commands from file:
enable
show management api restconf
Pretty JSON:
{
	"jsonrpc":	"2.0",
	"id":	"1",
	"result":	[{
		}, {
			"enabled":	true,
			"port":	6020,
			"vrfName":	"default",
			"error":	"",
			"sslProfile":	"self-signed-certs",
			"qosDscp":	0
		}]
}
You are connecting to: https://clab-lab3-ceos2/command-api

Commands from file:
enable
show management api restconf
Pretty JSON:
{
	"jsonrpc":	"2.0",
	"id":	"1",
	"result":	[{
		}, {
			"enabled":	true,
			"port":	6020,
			"vrfName":	"default",
			"error":	"",
			"sslProfile":	"self-signed-certs",
			"qosDscp":	0
		}]
}
You are connecting to: https://clab-lab3-ceos3/command-api

Commands from file:
enable
show management api restconf
Pretty JSON:
{
	"jsonrpc":	"2.0",
	"id":	"1",
	"result":	[{
		}, {
			"enabled":	true,
			"port":	6020,
			"vrfName":	"default",
			"error":	"",
			"sslProfile":	"self-signed-certs",
			"qosDscp":	0
		}]
}
(myenv_py3.11) toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista/httpClient$ 

```
- This client uses a seperate txt file that will hold the commands you want to run config or show commands.
- You call the file from the commands line
- ./http_client_using_file arg1 arg2 arg3 arg4
  * arg1 = host
  * arg2 = username
  * arg3 = password
  * arg4 = file
- I removed the need for the url to be included in the argument thought it would be easier to read
### commands.txt
```
(myenv_py3.11)toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista/httpClient$ cat commands.txt 
enable
configure
interface loopback 63
ip address 63.63.63.63/32
description interface sixty three

show running-config
```
### Run the script
```
(myenv_py3.11) toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista/httpClient$ ./http_client_using_files 172.20.20.2 admin admin commands.txt 
You are connecting to: https://172.20.20.2/command-api

Commands from file:
enable
configure
interface loopback 63
ip address 63.63.63.63/32
description interface sixty three
show running-config
Pretty JSON:
{
	"jsonrpc":	"2.0",
	"id":	"1",
	"result":	[{
		}, {
		}, {
		}, {
		}, {
		}, {
			"header":	["! device: ceos3 (cEOSLab, EOS-4.34.1F-41910228.orinocorel (engineering build))"],
			"comments":	[],
			"cmds":	{
				"no aaa root":	null,
				"username admin privilege 15 role network-admin secret sha512 $6$GnH7sZItPZVS3RHv$4i47By1Dfe0oau6g0wRHmRLGa8vRGL2OAg3pwzdoyTpHO28xxd.PCNZHXlZADg85W0GftMRF4upIF9BT59b60/":	null,
				"management api http-commands":	{
					"comments":	[],
					"cmds":	{
						"no shutdown":	null
					}
				},
				"no service interface inactive port-id allocation disabled":	null,
				"transceiver qsfp default-mode 4x10G":	null,
				"service routing protocols model multi-agent":	null,
				"hostname ceos3":	null,
				"spanning-tree mode mstp":	null,
				"system l1":	{
					"comments":	[],
					"cmds":	{
						"unsupported speed action error":	null,
						"unsupported error-correction action error":	null
					}
				},
				"management api gnmi":	{
					"comments":	[],
					"cmds":	{
						"transport grpc default":	{
							"comments":	[],
							"cmds":	{
							}
						}
					}
				},
				"management api netconf":	{
					"comments":	[],
					"cmds":	{
						"transport ssh default":	{
							"comments":	[],
							"cmds":	{
							}
						}
					}
				},
				"interface Ethernet1":	{
					"comments":	[],
					"cmds":	{
					}
				},
				"interface Ethernet2":	{
					"comments":	[],
					"cmds":	{
					}
				},
				"interface Ethernet3":	{
					"comments":	[],
					"cmds":	{
					}
				},
				"interface Loopback63":	{
					"comments":	[],
					"cmds":	{
						"description interface sixty three":	null,
						"ip address 63.63.63.63/32":	null
					}
				},
				"interface Management0":	{
					"comments":	[],
					"cmds":	{
						"ip address 172.20.20.2/24":	null,
						"ipv6 address 3fff:172:20:20::2/64":	null
					}
				},
				"no ip routing":	null,
				"ip route 0.0.0.0/0 172.20.20.1":	null,
				"ipv6 route ::/0 3fff:172:20:20::1":	null,
				"router multicast":	{
					"comments":	[],
					"cmds":	{
						"ipv4":	{
							"comments":	[],
							"cmds":	{
								"software-forwarding kernel":	null
							}
						},
						"ipv6":	{
							"comments":	[],
							"cmds":	{
								"software-forwarding kernel":	null
							}
						}
					}
				}
			}
		}]
}
(myenv_py3.11) toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista/httpClient$ 
```


# http client
- Used libcurl for the library as c does not have a native http client library
- It was surprisingly easy compared to ssh
- No I am not using this in a rest format, I'm basically running cli commands over https to the device
- I know its not very devops of me but lets get things rolling and see where it can lead
- I'm also ignoring cert validation
- At this point I'll consider this a small victory
- The first example is just issuing show commands
- I also used cjson to pretty print the outputs
- There is no issue running the nested configuaration commands using eAPI. Much cleaner.

### show commands
```
toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista/httpClient$ ./http_client_run_cmds https://172.20.20.6/command-api   "enable"   "show version" "show running-config"
Pretty JSON:
{
	"jsonrpc":	"2.0",
	"id":	"1",
	"result":	[{
		}, {
			"mfgName":	"Arista",
			"modelName":	"cEOSLab",
			"hardwareRevision":	"",
			"serialNumber":	"2E8B4DF570FC30AA49E0FBA3875C5075",
			"systemMacAddress":	"00:1c:73:8a:af:31",
			"hwMacAddress":	"00:00:00:00:00:00",
			"configMacAddress":	"00:00:00:00:00:00",
			"version":	"4.34.1F-41910228.orinocorel (engineering build)",
			"architecture":	"aarch64",
			"internalVersion":	"4.34.1F-41910228.orinocorel",
			"internalBuildId":	"81163ad0-9b7a-4970-994c-32d9d3d2ccdb",
			"imageFormatVersion":	"1.0",
			"imageOptimization":	"None",
			"kernelVersion":	"6.14.10-orbstack-00291-g1b252bd3edea",
			"bootupTimestamp":	1753313445.8147717,
			"uptime":	38598.764953613281,
			"memTotal":	8187844,
			"memFree":	3216136,
			"isIntlVersion":	false
		}, {
			"header":	["! device: ceos1 (cEOSLab, EOS-4.34.1F-41910228.orinocorel (engineering build))"],
			"comments":	[],
			"cmds":	{
				"no aaa root":	null,
				"username admin privilege 15 role network-admin secret sha512 $6$nteiCUhy9aSEymNH$f4C2Lj4xlUfpENHsD7hP3Lk2w.hTBpEEbc4awZe0GgK/pOvACzJ5bq4W028Aq8s3ZDloGdjVfFgp/p1g4QuWI/":	null,
				"management api http-commands":	{
					"comments":	[],
					"cmds":	{
						"no shutdown":	null
					}
				},
				"no service interface inactive port-id allocation disabled":	null,
				"transceiver qsfp default-mode 4x10G":	null,
				"service routing protocols model multi-agent":	null,
				"hostname ceos1":	null,
				"spanning-tree mode mstp":	null,
				"system l1":	{
					"comments":	[],
					"cmds":	{
						"unsupported speed action error":	null,
						"unsupported error-correction action error":	null
					}
				},
				"management api gnmi":	{
					"comments":	[],
					"cmds":	{
						"transport grpc default":	{
							"comments":	[],
							"cmds":	{
							}
						}
					}
				},
				"management api netconf":	{
					"comments":	[],
					"cmds":	{
						"transport ssh default":	{
							"comments":	[],
							"cmds":	{
							}
						}
					}
				},
				"interface Ethernet1":	{
					"comments":	[],
					"cmds":	{
						"description ceos1-ceos2":	null,
						"no switchport":	null,
						"ip address 192.168.0.0/31":	null
					}
				},
				"interface Ethernet2":	{
					"comments":	[],
					"cmds":	{
						"description ceos1-ceos3":	null,
						"no switchport":	null,
						"ip address 192.168.0.2/31":	null
					}
				},
				"interface Ethernet3":	{
					"comments":	[],
					"cmds":	{
					}
				},
				"interface Loopback0":	{
					"comments":	[],
					"cmds":	{
						"ip address 1.1.1.1/32":	null
					}
				},
				"interface Loopback2":	{
					"comments":	[],
					"cmds":	{
						"description test":	null
					}
				},
				"interface Management0":	{
					"comments":	[],
					"cmds":	{
						"ip address 172.20.20.6/24":	null,
						"ipv6 address 3fff:172:20:20::6/64":	null
					}
				},
				"ip routing":	null,
				"ip route 0.0.0.0/0 172.20.20.1":	null,
				"ipv6 route ::/0 3fff:172:20:20::1":	null,
				"router multicast":	{
					"comments":	[],
					"cmds":	{
						"ipv4":	{
							"comments":	[],
							"cmds":	{
								"software-forwarding kernel":	null
							}
						},
						"ipv6":	{
							"comments":	[],
							"cmds":	{
								"software-forwarding kernel":	null
							}
						}
					}
				},
				"router ospf 1":	{
					"comments":	[],
					"cmds":	{
						"network 1.1.1.1/32 area 0.0.0.0":	null,
						"network 192.168.0.0/31 area 0.0.0.0":	null,
						"network 192.168.0.2/31 area 0.0.0.0":	null,
						"max-lsa 12000":	null
					}
				}
			}
		}]
}
```
### configuration commands

```
toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista/httpClient$ ./http_client_run_cmds https://172.20.20.6/command-api   "enable"   "configure terminal" "interface loopback 2" "description testing eapi" "show running-config"
Pretty JSON:
{
	"jsonrpc":	"2.0",
	"id":	"1",
	"result":	[{
		}, {
		}, {
		}, {
		}, {
			"header":	["! device: ceos1 (cEOSLab, EOS-4.34.1F-41910228.orinocorel (engineering build))"],
			"comments":	[],
			"cmds":	{
				"no aaa root":	null,
				"username admin privilege 15 role network-admin secret sha512 $6$nteiCUhy9aSEymNH$f4C2Lj4xlUfpENHsD7hP3Lk2w.hTBpEEbc4awZe0GgK/pOvACzJ5bq4W028Aq8s3ZDloGdjVfFgp/p1g4QuWI/":	null,
				"management api http-commands":	{
					"comments":	[],
					"cmds":	{
						"no shutdown":	null
					}
				},
				"no service interface inactive port-id allocation disabled":	null,
				"transceiver qsfp default-mode 4x10G":	null,
				"service routing protocols model multi-agent":	null,
				"hostname ceos1":	null,
				"spanning-tree mode mstp":	null,
				"system l1":	{
					"comments":	[],
					"cmds":	{
						"unsupported speed action error":	null,
						"unsupported error-correction action error":	null
					}
				},
				"management api gnmi":	{
					"comments":	[],
					"cmds":	{
						"transport grpc default":	{
							"comments":	[],
							"cmds":	{
							}
						}
					}
				},
				"management api netconf":	{
					"comments":	[],
					"cmds":	{
						"transport ssh default":	{
							"comments":	[],
							"cmds":	{
							}
						}
					}
				},
				"interface Ethernet1":	{
					"comments":	[],
					"cmds":	{
						"description ceos1-ceos2":	null,
						"no switchport":	null,
						"ip address 192.168.0.0/31":	null
					}
				},
				"interface Ethernet2":	{
					"comments":	[],
					"cmds":	{
						"description ceos1-ceos3":	null,
						"no switchport":	null,
						"ip address 192.168.0.2/31":	null
					}
				},
				"interface Ethernet3":	{
					"comments":	[],
					"cmds":	{
					}
				},
				"interface Loopback0":	{
					"comments":	[],
					"cmds":	{
						"ip address 1.1.1.1/32":	null
					}
				},
				"interface Loopback2":	{
					"comments":	[],
					"cmds":	{
						"description testing eapi":	null
					}
				},
				"interface Management0":	{
					"comments":	[],
					"cmds":	{
						"ip address 172.20.20.6/24":	null,
						"ipv6 address 3fff:172:20:20::6/64":	null
					}
				},
				"ip routing":	null,
				"ip route 0.0.0.0/0 172.20.20.1":	null,
				"ipv6 route ::/0 3fff:172:20:20::1":	null,
				"router multicast":	{
					"comments":	[],
					"cmds":	{
						"ipv4":	{
							"comments":	[],
							"cmds":	{
								"software-forwarding kernel":	null
							}
						},
						"ipv6":	{
							"comments":	[],
							"cmds":	{
								"software-forwarding kernel":	null
							}
						}
					}
				},
				"router ospf 1":	{
					"comments":	[],
					"cmds":	{
						"network 1.1.1.1/32 area 0.0.0.0":	null,
						"network 192.168.0.0/31 area 0.0.0.0":	null,
						"network 192.168.0.2/31 area 0.0.0.0":	null,
						"max-lsa 12000":	null
					}
				}
			}
		}]
}
toddriemenschneider@clab:~/clabs/labs/ceos_labs/lab3/scripts/c_folder/arista/httpClient$
```
