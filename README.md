# rpi-fruitbox-v2
Raspberry Pi fruitbox (Version 2)

fruitbox is a customisable MP3 player for the Raspberry Pi, allowing the user to create the look and feel of classic jukeboxes.
fruitbox works on all Raspberry Pi devices except Pi4, but runs better on the higher spec (quad core) machines (i.e. Models 2 and above),
especially if playing music videos.

Installation is as follows:

1. It is recommended to start from a fresh OS install (latest Raspbian Buster release)
   Note that due to sound issues on the latest OS release (Bullseye, Debian version 11), fruitbox requires the Legacy (Buster) OS ...
   https://downloads.raspberrypi.org/raspios_oldstable_lite_armhf/images/raspios_oldstable_lite_armhf-2022-01-28/2022-01-28-raspios-buster-armhf-lite.zip

2. Increase GPU memory to (at least) 256 (sudo raspi-config -> Performance Options -> GPU Memory)
   Note raspi-config can also be used to set up Wi-Fi and enable SSH for transferring files from PC to Pi via WinSCP for example
3. From a command shell, type : wget https://github.com/chundermike/rpi-fruitbox-v2/raw/main/install_fruitbox
4. From a command shell, type : chmod +x ./install_fruitbox
5. From a command shell, type : ./install_fruitbox
   This will install fruitbox in the ~/fruitbox directory
6. Copy your music MP3 files (either to the SD card or USB memory stick)
   (by default fruitbox looks for music files in the ~/Music directory on the SD card)
7. Point fruitbox to your MP3 files (edit ~/fruitbox/fruitbox.ini and change the MusicPath parameter)
8. Run fruitbox...
   From a command shell, type : cd ~/fruitbox
   then type : ./fruitbox
   

For help, from a command line, enter :

  ./fruitbox --help


Also, the user guide will give details on how to create your own skins, storing songs on USB memory sticks, and other helpful hints.

If you design any skins and would like to share them, please let me know and I can include them in the fruitbox github
repository.

If you wish to encourage fruitbox development, please consider making a donation to the author at https://paypal.me/rpifruitbox

Let's Rock!
