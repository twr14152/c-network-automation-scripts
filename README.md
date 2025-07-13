Network Scripts written in C to configure and operate network devices

07/12/2025
- In example2 added the option to open a commands file to the ssh scripts. Its a positional argument. So the name of the file will not need hard coded in the script.
- arista/example2/ssh_script.c - allows you to create a command file with configs or show commands then you just call the file when you run the ssh_script
- I've include a readme file in that directory to explain
- I have not started on the Cisco example2 yet.

07/11/2025
- I really enjoy working with C. My background is in networking so why not try and see if I can make some use of it? I know screen scraping is not real sexy in the automation community but like it or not it is useful...
- This reporsitory will hold scripts that I write for the purposes of knowledge building, retention, and sharing.
- So far I've created two scripts using libssh library. I pieced them together from the tutorial (https://api.libssh.org/stable/libssh_tutorial.html)
- I am not going to lie it was challenging and took sometime and effort to get working properly. Lots of debugging.
   * arista/example1/ssh_cli_script.c - This script that works by using keyboard_interactive authentication
   * cisco/example1/ssh_cli_script.c - This script works by using password authentication
- The test envionments will probably change over time but for now 
- I will use Containerlab for arista ceos and potentially other devices
- Devnet sandbox for cisco - This first example used always on nxos.
- Now I understand the the usefulness of using a script in this fashion is more for a lab environment without and need for safeguards. My goal is to create more production ready format for these scripts. But you need to start somewhere. I also hope to grow beyond screen scraping but for now, it is what it is.
- Lastly why c? Why not? I like it...
