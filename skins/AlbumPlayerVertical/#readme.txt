A skin by Jay's Arcade

Design inspired by TouchJams Jukebox

This is a vertical touch screen skin (and now a pushbutton version). This skin was built with the intention of your music being in Albums. To get the most out of this skin, each album should be in a it's own folder, and each folder should have a folder.jpg. The easiest way I've found to get folder.jpgs to populate your folders is to let Windows Media Player catalog your music. It automatically adds the folder.jpgs. Once that is done, you can copy the folders into you Pi's music folder or where ever you have your songs located for Fruibox to find.

If you are running this skin on anything less than a pi 4, the title strips might be slow to move. To help with this, you can change the TitleStripMoveStyle (line 29 in the cfg file) from 40 to 0. So the line would read like this.

TitleStripMoveStyle = 0 0 no

To exit the touchscreen version - touch the orange 'remaining song time' bar to exit.