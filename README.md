Network Scripts written in C to configure and operate network devices

07/12/2025
- In example2 I added the option to have a seperate file which can hold your device configuration or show commands. Its just a text file. Call it what ever you want. Then call it when your run your script. Its based off of a positional argument. So the name of the file could be anything.
- arista/example2/ssh_script.c
- I've include a readme file in that directory to help explain
- I have not started on the Cisco example2 yet.

07/11/2025
- I really enjoy working with C. My background is in networking so why not try and see if I can make some use of it? I know screen scraping is not real sexy in the automation community but like it or not,  it's useful...
- This repository will hold scripts that I write for the purposes of knowledge building, retention, and sharing.
- So far I've created two scripts using libssh library. I pieced them together from the tutorial (https://api.libssh.org/stable/libssh_tutorial.html)
- Not going to lie these first scripts were challenging and took sometime and effort to get working properly. Lots of debugging, especially the arista because of its authentication method.
- These two scripts represent two very different forms of authentication using SSH. The Cisco device was more straight forward. 
   * arista/example1/ssh_cli_script.c - This script that works by using keyboard_interactive authentication
   * cisco/example1/ssh_cli_script.c - This script works by using password authentication
- The test envionments will probably change over time but for now 
   * I will use Containerlab for arista ceos and potentially other devices
   * Devnet sandbox for cisco - This first example used always on nxos.
- Now I understand the the usefulness of using a script in this fashion is more for a lab environment without and need for safeguards. My goal is to create more production ready format for these scripts. But you need to start somewhere. I also hope to grow beyond screen scraping but for now, it is what it is.
- Lastly why c? Why not? I like it...
