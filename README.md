# aerofnkeys
Custom HID Quirks Driver that fixes function keys not working in the Gigabyte Aero 15 SB on Linux.

Works by intercepting non-HID compliant usages raw and emulating the correct keycode presses.

## Notes

- Compatible with the Chu Yuen Keyboard for the Gigabyte Aero 15 SB (Vendor ID: ID 1044, Product ID: 7A3B).
- To check compatibility run `lsusb`, find your keyboard and compare the ID values with the ones stated above.
- At the moment I've managed to get only the brightness keys to work on my system *(Fedora 34; Kernel 5.13.12; Gnome 40.4)*. I am investigating why the wifi and touchpad toggle keys are not working.

- Make sure you have the kernel headers installed for the kernel version your PC is running. To see if already installed on Arch/Manjaro run `pacman -Q linux-headers`.

# How to Install

1. `git clone https://github.com/jaytohe/aerofnkeys.git`
2. `cd aerofnkeys`
3. `make`
4. `sudo make install`

To load the module manually do :`sudo modprobe fn_keys_mod`

To load the module automatically on startup you need to edit the GRUB bootloader configuration file and specify a parameter for the usbhid kernel module.

To do that :
1. `sudo nano /etc/default/grub`
2. Find the GRUB_CMDLINE_LINUX entry.
3. Append the following kernel parameter at the end of said entry's line :
4.  `usbhid.quirks=0x1044:0x7a3b:0x0000`
5. Ctrl+O and CTRL+X to save and quit nano.
6. If on Ubuntu run : `update-grub` else:
7.  `grub-mkconfig -o /boot/grub/grub.cfg`
9. Done! Reboot and check if the fn brightness keys work.

If not, undo the changes to /etc/default/grub and run grub-mkconfig again. Afterwards, do:

`echo fn_keys_mod>/etc/modules-load.d/load_fn_keys_mod.conf`

This should manually load the fn_keys_mod module on boot without the use of usbhid. Reboot and check.

# How to survive kernel updates

The steps above will install and enable the module only for the currently running kernel version. If the kernel is updated, the module will need to be re-compiled. 

To avoid the hassle, you can use the [Dynamic Kernel Module Support (DKMS)](https://en.wikipedia.org/wiki/Dynamic_Kernel_Module_Support) to automatically rebuild when a kernel update occurs.

I recommend following [this guide](https://wiki.centos.org/HowTos/BuildingKernelModules#Building_a_kernel_module_using_Dynamic_Kernel_Module_Support_.28DKMS.29).


