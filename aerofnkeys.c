#include <linux/module.h>
#include <linux/input.h>
#include <linux/hid.h>
#include "hid-ids.h"

#define SEND_KEY(c) send_key( ((report->field)[0])->hidinput->input, (c));


static void send_key(struct input_dev *inputd, unsigned int keycode) { //emulate keyboard single key press and release.
	input_report_key(inputd, keycode, 1);
	input_sync(inputd);
	input_report_key(inputd, keycode, 0);
	input_sync(inputd);
}

static int gigabyte_raw_event(struct hid_device *hdev, struct hid_report *report, u8 *data, int size)
{

	if(unlikely(report->id == 4 && size == 4)) { //if report comes from vendor usage page
		switch(data[3]) {
			/* 
			* All FN-keys (except vol_up, vol_down, vol_mute) send only key presses and no key releases.
			* We simulate an instaneous key press and release at the cost of the ability to handle long-press of a key.
			*/
			case 0x7c:
				SEND_KEY(KEY_WLAN); //TODO: Fix not working for me (running Gnome 40 and kernel 5.13).
				break;
			case 0x7d:
				SEND_KEY(KEY_BRIGHTNESSDOWN); 
				break;
			case 0x7e:
				SEND_KEY(KEY_BRIGHTNESSUP);
				break;
			case 0x81:
				SEND_KEY(KEY_TOUCHPAD_TOGGLE); //TODO: Fix not working for me (running Gnome 40 and kernel 5.13).
				break;
		
			//TODO: Add support for remaining non-working fn-keys keys.
		}
	}

	return 0;
}




static const struct hid_device_id gigabyte_devices[] = {
	//binding to HID_GROUP_GENERIC to let hid-multitouch.c handle the touchpad and trackpoint.
	{.bus=BUS_USB, .group=HID_GROUP_GENERIC, .vendor=USB_VENDOR_ID_CHUYEN, .product=USB_DEVICE_ID_CHUYEN_7A3B},
	{.bus=BUS_USB, .group=HID_GROUP_GENERIC, .vendor=USB_VENDOR_ID_CHUYEN, .product=USB_DEVICE_ID_CHUYEN_7A3F}
}; 
//Array of Structs ; hid_device_id is a struct as well.




static struct hid_driver gigabyte_hid_driver = {
	.name = "gigabyte",
	.id_table = gigabyte_devices,
	.raw_event=gigabyte_raw_event,
	
};

module_hid_driver(gigabyte_hid_driver);

MODULE_AUTHOR("Github: jaytohe (+a tiny bit of help from atomspring)");
MODULE_DESCRIPTION("Bare-bones support for Gigabyte Aero 15/17 fn-keys");
MODULE_LICENSE("GPL");
