# aerofnkeys
Custom HID Quirks Driver that fixes function keys not working in the Gigabyte Aero 15 SB on Linux. 

Works by intercepting non-HID compliant usages raw and emulating the correct keycode presses.

Make sure you have the `linux-headers` package installed for the kernel version your PC is running.

To see if already installed on Arch/Manjaro run `pacman -Q linux-headers`.

# How to Install

1. `git clone https://github.com/jaytohe/aerofnkeys.git`
2. `cd aerofnkeys`
3. `make`
4. `sudo make install`

To load the module manually do :`sudo modprobe fn_keys_mod`

To load the module automatically on startup :
1. `sudo -s`
2. `cd /etc/modules-load.d`
3. `echo fn_keys_mod>fn_keys_mod.conf`


