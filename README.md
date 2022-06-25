# AOS-Miosix-Breakout 

Repository for the AOS course @polimi. The project is an implementation of the Breakout game (<url>https://en.wikipedia.org/wiki/Breakout_(video_game)</url>) for the STM32f4 discovery board. Everything has been tested using Linux Ubuntu 22.10, both using a virtual machine and native.

<h2> Getting started </h2>
First of all you have to clone the repository by entering the following command on the terminal (assuming you have git command installed): 

```
git clone https://github.com/simonetome/AOS-Miosix-Breakout
```

then enter in the repository local folder with: 

```
cd AOS-Miosix-Breakout
```

Now you have to get <b>Miosix</b>. 

Everything is taken from <url>https://miosix.org/wiki/index.php?title=Linux_Quick_Start</url>. For other OS wrt Linux there's a guide in the wiki. 

<br>
For 32 bit compatibility having Debian based distros, run:

```
sudo apt-get install libstdc++6:i386 
```
Instead, for Arch based distros, run:

```
sudo pacman -S lib32-libstdc++5 
```

For using the serial port of /dev/ttyUSB0:

```
sudo usermod -a -G dialout `id -un`
```

Then install both `screen` and `xterm` with either `snap`/`apt-get` or `pacman`, based on the distro you have.

To install the Miosix toolchain and to clone the repository (always inside the `AOS-Miosix-Breakout`):

```
wget https://miosix.org/toolchain/MiosixToolchainInstaller.run
sh MiosixToolchainInstaller.run
git clone https://miosix.org/git-public/miosix-kernel.git
cd miosix-kernel
git fetch origin    
## To select the development version of the kernel
#git checkout -b testing origin/testing
```

On the wiki link you can see the settings for Miosix according the board you are using, just visit <url>https://miosix.org/wiki/index.php?title=Linux_Quick_Start</url> in the section <b>Configuring and compiling the kernel</b>.

Then you have to install <b>Qstlink2</b>, in order to flash the `main.bin` (artifact produced after building everything) on the board.

<h2>Tutorial</h2>

Once you are finished installing every dependency you can run `make` in the main folder of the repository, this will produce `main.bin`: the binary that contains both the Miosix OS and the game. 
<br>

If you want to use the keyboard ('a' -> left, 'd' -> right, 'e' -> enter) you have to set `BUTTON` to 0 in `Breakout/settings.h`, and then compile again.

Then open a new terminal and run: 
```
resize -s 45 70 
```
to resize the window with xterm, and then run:

```
screen /dev/ttyUSB0 <baud-rate>
```
to access the serial port and emulate a terminal with screen. Baud rate is configured in Miosix, we tested 115200 and works pretty well, also in a VM environment.

After that you have to flash the program on the board, open <b>QStlink2</b> and after connecting the board, press `send` and select the main binary (`main.bin`). If the procedure terminates correctly, the main menu should be displayed within the screen terminal. 


