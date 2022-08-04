MODULE_NAME = aerofnkeys
KVER = $(shell uname -r)
MODDESTDIR = /lib/modules/$(KVER)/kernel/drivers/hid/

obj-m += $(MODULE_NAME).o

all:
	$(MAKE) -C /lib/modules/$(KVER)/build M=$(PWD) modules
	# Remove the debugging symbols and shrink this module down:
	strip --strip-debug $(MODULE_NAME).ko
	# Here we sign the module to allow loading in a system with kernel_lockdown enabled (e.g. anything Ubuntu including and beyond 20.04 LTS)
	/usr/src/linux-headers-${KVER}/scripts/sign-file sha512 /var/lib/shim-signed/mok/MOK.priv /var/lib/shim-signed/mok/MOK.der $(MODULE_NAME).ko

clean:
	$(MAKE) -C /lib/modules/${KVER}/build M=$(PWD) clean

install:
	#xz -9 $(MODULE_NAME).ko
	#install -p -m 644 $(MODULE_NAME).ko.xz  $(MODDESTDIR)
	install -p -m 644 $(MODULE_NAME).ko  $(MODDESTDIR)
	/sbin/depmod -a ${KVER}

uninstall:
	rm -f $(MODDESTDIR)/$(MODULE_NAME).ko.xz
	/sbin/depmod -a ${KVER}
