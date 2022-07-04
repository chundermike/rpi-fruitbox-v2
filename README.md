# rpi-fruitbox-v2
Raspberry Pi fruitbox (Version 2)

fruitbox is a customisable MP3 player for the Raspberry Pi, allowing the user to create the look and feel of classic jukeboxes.
fruitbox works on all Raspberry Pi devices, but runs better on the higher spec (quad core) machines (i.e. Models 2 and above),
especially if playing music videos.

Installation is as follows:

For Raspberry Pi version 4 (recommended) :

1. fruitbox only runs under the Raspberry Pi OS Desktop version (not Lite). The 64-bit Raspberry Pi OS image is recommended ...
   https://downloads.raspberrypi.org/raspios_arm64/images/raspios_arm64-2022-04-07/2022-04-04-raspios-bullseye-arm64.img.xz

2. Increase GPU memory to (at least) 256 ( -> Performance Options -> GPU Memory)

    
For Raspberry Pi versions Zero through 3 :

1. It is recommended to start from a fresh OS install (latest Raspbian Buster release)
   Note that due to sound issues on the latest OS release (Bullseye, Debian version 11), fruitbox requires the Legacy (Buster) OS ...
   https://downloads.raspberrypi.org/raspios_oldstable_lite_armhf/images/raspios_oldstable_lite_armhf-2022-01-28/2022-01-28-raspios-buster-armhf-lite.zip

2. Increase GPU memory to (at least) 256 (sudo raspi-config -> Performance Options -> GPU Memory)
   Note raspi-config can also be used to set up Wi-Fi and enable SSH for transferring files from PC to Pi via WinSCP for example


Steps 3 to 8 below are for all Raspberry Pi versions ...

3. From a command shell, type : wget https://github.com/chundermike/rpi-fruitbox-v2/raw/main/install_fruitbox
4. From a command shell, type : chmod +x ./install_fruitbox
5. From a command shell, type : ./install_fruitbox
   This will install fruitbox in the /home/pi/fruitbox directory
6. Copy your music MP3 files (either to the SD card or USB memory stick)
   (by default fruitbox looks for music files in the /home/pi/Music directory on the SD card)
7. Point fruitbox to your MP3 files (edit /home/pi/fruitbox/fruitbox.ini and change the MusicPath parameter)
8. Run fruitbox...
   From a command shell, type : cd /home/pi/fruitbox
   then type : ./fruitbox
   

For help, from a command line, enter :

  ./fruitbox --help


Also, the user guide will give details on how to create your own skins, storing songs on USB memory sticks, and other helpful hints.

If you design any skins and would like to share them, please let me know and I can include them in the fruitbox github
repository.

If you wish to encourage fruitbox development, please consider making a donation to the author at https://paypal.me/rpifruitbox

Let's Rock!
