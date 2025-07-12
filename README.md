Network Scripts written in C to configure and operate network devices

07/11/2025: 
 - I really enjoy working with C. I also enjoy writing code to help me configurate and operate network devices. Guess I'm kinda a tools guy. So I thought I would try and replicate in C what I've done in other languages. I know screen scraping is not truly sexy in the automation community but like it or not it is useful... Kinda the opposite of yang :).
 - This reporsitory will hold scripts that I write for the purposes of knowledge retention and sharing.
 - So far I've created two scripts using libssh library
   * arista/example1/ssh_cli_script.c - This script that works by using keyboard_interactive authentication
   * cisco/example1/ssh_cli_script.c - This script works by using password authentication
- The test environment used for the arista script Containerlabs using ceos
- The test environment used for cisco was devnet sandbox nxos always on
- Now I understand the the usefulness of using a script in this fashion is more for a lab environment without and need for safeguards. My goal is to create more production ready format for these scripts. But you need to start somewhere. I also hope to grow beyond screen scraping but for now it is what it is.
- Lastly why c? Why not? I like it...
