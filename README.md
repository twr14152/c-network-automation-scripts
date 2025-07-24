# Network Scripts written in C to configure and operate network devices
### 07/24/2025
- I added http client code
- Currently its code that runs Cli commands from http using arista eAPI
- I used libcurl library to build it. The documentation was really good with lots examples.
  * https://curl.se/libcurl/
- I added cjson to make the response data easier to read
- At this point thats all of I have
  * arista/httpClient/http_client_run_cmds.c
### 07/14/2025
- I ended up breaking up the config and exec commands functions into seperate scripts
- The logic seemed cleaner as interactive shell seem appropriate for config functions more than exec commands
  * cisco/example2/ssh_conf.c - configuration script
  * cisco/example2/ssh_exec_cmds.c - show commands script
- Next task is to try and come up with a way to configure multiple devices
- So example3 show's how you could deploy and validate changes to your network using this code.
- I didn't write additional c code to perform this I actually used a little bash to act as the orchestrator for this change.
- The README shows the examples and how they were rolled out and validated
  * arista/example3/pre_change_status.sh
  * arista/example3/push_conf_change.sh
  * arista/example3/post_change_status.sh
  * arista/example3/rem_conf_change.sh

### 07/13/2025
- Added option for configure file to the Cisco device we are testing
- ~cisco/example2/ssh_script.c~ 
- The cisco device did not honor end of line ";" that arista ceos did the result was anything beyond the interface description became part of the description.
- I had to use interactive shell to get it to properly take the commands.
- Techinically this the more appropriate way of dealing with multiple nested commands in configuration mode.

### 07/12/2025
- In example2 I added the option to have a seperate file which can hold your device configuration or show commands. Its just a text file. Call it what ever you want. Then call it when your run your script. Its based off of a positional argument. So the name of the file could be anything.
- arista/example2/ssh_script.c
- I've include a readme file in that directory to help explain
- I have not started on the Cisco example2 yet.

### 07/11/2025
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
- It would seem using the right tool for the right job may not have a place in this repo after all we are using c for network scripting. That said I may include some bash rather using c as an orchestrator to launch multiple instances of a script.
- I will try an improve the scripts as I gain more understanding
- This may not go very far, but wont know your limits until you try.
- Lastly why c? Why not? I like it...
