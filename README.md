# Toolbag
Tools to aid brain fade and reduce documentation 

//

## Installation

Toolbag components are installed in /usr/local/bin, because this folder is in the path 
and is generally empty. 

It is installed from github, so the git command is required (if it isn't already available):

    sudo apt install -y git

First clone the github repository, then make the setup script executable and run it. 
Setup will cleanup after itself, by deleting the repository.

    git clone https://github.com/julianpratt/Toolbag
    chmod +c Toolbag/setup
    Toolbag/setup

These instructions can be repeated to update an existing installation of Toolbag. 

Alternatively use the update command to achieve the same thing.

//

## Usage

Each tool responds to -h, and the tools command lists the tools and their purpose.

//

## Building a Raspberry Pi

One of the reasons for this is to make it easier to setup a new Raspberry Pi. 

Raspberry Pi OS (formerly known as Raspbian), is a port of Debian and is installed on a micro SD card using rpi-imager (on Windows or Linux). This offers different Raspberry Pi OS images: no desktop, desktop and desktop plus recommended apps). 

Before starting decide on the hostname of the Raspbery Pi. Using hostnames such as layoutpi, naspi, etc makes its purpose clear, to avoid mission creep and make it easier to remember which is which. Obviously the name is actually only associated with the image on the SD card. 

In RPi Imager, use Ctrl+Shift+X (or the settings button) to open advanced options:  
- Disable overscan
- Set hostname to layoutpi.local or naspi.local
- Enable SSH (use password authentication)
- Decide whether to set a different username
- It is advisible to change the password
- Enable and configure WiFi (this should be filled in automatically, because the computer running rpi-imager will already be using that WiFi)
- Set locale settings, e.g. Time Zone to Europe/London and Keyboard Layout to gb
- Skip first run wizard (which is no longer needed, now that these choices have been made)
- Don’t play sound when finished, but do export media and enable telemetry

These settings can be changed later by using a terminal and sudo raspi-config.

In particular the boot behaviour, can be changed so the RPi just boots to command line (doesn’t load the desktop) and also boots straight to the Pi user (doesn‘t wait for login).   

Then decide whether or not a desktop is required for that RPi. The default Raspberry Pi OS has a desktop. Under Raspberry Pi OS (other) there is an image without a desktop.

Put the SD card into the Pi and power up. After a while SSH (port 22) into the Pi. The RPi can now be accessed with (for example): ssh username@hostname

Then setup Toolbag (see Installation, above) and download the latest updates:
    update

//

### Power Save 
Although the Raspberry Pi itself doesn't have a sleep mode, individual devices in Linux (including the network adapters) can. Run the command: 

    iw wlan0 get power_save

to find out whether the network adaptor has power save switched on, and if it has, then use 

    sudo iw wlan0 set power_save off 

to switch it off.

The reason for worrying about power_save, is that is a right pain if you are operating a layout using JMRI (see next section) and the Pi goes to sleep (ask me how I know).

//

## Setting up the Raspberry Pi for JMRI

These instructions are a development (he might say regression) of Steve Todd's Raspberry Pi Build (https://mstevetodd.com/rpi). I was deeply grateful to Steve for providing this build, which got me going when I got stuck. But I wanted to understand what the ingredients of the build were, so I could adjust them. You might find Steve's build a better starting point for your purposes.    

The aim is to get the Raspberry Pi to a point that it just boots straight into the panel and is active and ready. So just applying power is enough to get the layout functioning.  

Start with the instructions for setting up a Raspberry Pi (above). Then use addtool to add java and then jmri:

    addtool java
    addtool jmri		
    
Start PanelPro (double click the desktop icon) and quit saving changes to the Profile. 

If you have an existing JMRI profile, panels, etc, then fetch these onto the Raspberry Pi, plug in the layout USB (e.g. CBUS CANUSB4) and restart PanelPro. Then switch the default profile to the one you've just downloaded and save it. 

If using CBUS, the MERG connection is typically: /dev/ttyACM0. USBs are in the dialout group – the user needs to be in that group (which it will be if you followed the instructions above). 

It is a good idea to have JMRI automatically open a panel when it starts, so that simply switching the Raspberry Pi on, gets JMRI operational. 

Test that everything is working as expected, by quitting PanelPro and shutdown RPi. Power it back on and watch it as it boots and JMRI starts. The panel should be operational so the layout just starts working. 
