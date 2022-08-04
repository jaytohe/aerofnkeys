# aerofnkeys
Custom HID Quirks Driver that fixes function keys not working in the Gigabyte Aero 15 SB & D-series on Linux.

Works by intercepting non-HID compliant usages raw and emulating the correct keycode presses because Gigabyte is stupid.

## Notes

- Compatible with the Chu Yuen Keyboard for the Gigabyte Aero 15 SB (Vendor ID: ID 1044, Product ID: 7A3B) and the Aero 15 D series (Chu Yuen 1044:7A3D).
- To check compatibility run `lsusb`, find your keyboard and compare the ID values with the ones stated above.
- At the moment I've managed to get only the brightness keys to work on my system *(Fedora 34; Kernel 5.13.12; Gnome 40.4)*. I am investigating why the wifi and touchpad toggle keys are not working.

- Make sure you have the kernel headers installed for the kernel version your PC is running. To see if already installed on Arch/Manjaro run `pacman -Q linux-headers`.

# How to Install

## Recommended DKMS Method
1. `git clone https://github.com/atomspring/aerofnkeys.git /usr/src/aerofnkeys-1.0`
2. `dkms add aerofnkeys/1.0`
3. `dkms install aerofnkeys/1.0`
4. `echo aerofnkeys > /etc/modules-load.d/load_aerofnkeys.conf`
5. Reboot & give your backlight keys a go. Enjoy!


## Manual method
1. `git clone https://github.com/atomspring/aerofnkeys.git /usr/src/aerofnkeys-1.0`
2. `cd /usr/src/aerofnkeys-1.0`
3. `make`
4. `make install`

# Troubleshooting

If you get an error message when running `modprobe aerofnkeys` which says something along the lines of "exec format error", try clearing out the DKMS built module by running:
1. `dkms remove aerofnkeys/1.0 -k $(uname -r)`
2. `dkms install aerofnkeys/1.0 -k $(uname -r)`
3. `modprobe -v aerofnkeys`

Inspect the module by running `modinfo` or `file` about the specific kernel's build of aerofnkeys.

