# aerofnkeys
Custom HID Quirks Driver that fixes function keys not working in the Gigabyte Aero 15 SB on Linux.

Works by intercepting non-HID compliant usages raw and emulating the correct keycode presses.

## Notes
- At the moment I've managed to get only the brightness keys to work on my system *(Fedora 34; Kernel 5.13.12; Gnome 40.4)*. I am investigating why the wifi and touchpad toggle keys are not working.

- Make sure you have the kernel headers installed for the kernel version your PC is running. To see if already installed on Arch/Manjaro run `pacman -Q linux-headers`.

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

# How to survive kernel updates

The steps above will install and enable the module only for the currently running kernel version. If the kernel is updated, the module will need to be re-compiled. 

To avoid the hassle, you can use the [Dynamic Kernel Module Support (DKMS)](https://en.wikipedia.org/wiki/Dynamic_Kernel_Module_Support) to automatically recompile and enable the module when a kernel update occurs.

I recommend following [this guide](https://wiki.centos.org/HowTos/BuildingKernelModules#Building_a_kernel_module_using_Dynamic_Kernel_Module_Support_.28DKMS.29).


