#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/input.h>
#include <linux/hid.h>
#include "hid-ids.h"


static void send_key(struct input_dev *inputd, unsigned int keycode) { //emulate keyboard single key press and release.
	input_event(inputd, EV_KEY, keycode, 1);
	input_sync(inputd);
	input_event(inputd, EV_KEY, keycode, 0);
	input_sync(inputd);
}

#define SEND_KEY(c) send_key( ((report->field)[0])->hidinput->input, (c));

static int gigabyte_raw_event(struct hid_device *hdev,
			struct hid_report *report, u8 *data, int size)
{

	if(unlikely(report->id == 4 && size == 4)) { //if report comes from vendor usage page
		switch(data[3]) {
			//pseudo-remap the fn keys based on their hid code value.
			case 0x7c:
				SEND_KEY(KEY_WLAN);
				break;
			case 0x7d:
				SEND_KEY(KEY_BRIGHTNESSDOWN);
				break;
			case 0x7e:
				SEND_KEY(KEY_BRIGHTNESSUP);
				break;
			case 0x81:
				SEND_KEY(KEY_TOUCHPAD_TOGGLE);
				break;
		}
	}

	return 0;
}




static const struct hid_device_id gigabyte_devices[] = {
	//binding to HID_GROUP_GENERIC to let hid-multitouch.c handle the touchpad and trackpoint.
	{.bus=BUS_USB, .group=HID_GROUP_GENERIC, .vendor=USB_VENDOR_ID_GIGABYTE, .product=USB_DEVICE_ID_GIGABYTE_AERO15SB},
}; 
//Array of Structs ; hid_device_id is a struct as well.




static struct hid_driver gigabyte_hid_driver = {
	.name = "gigabyte",
	.id_table = gigabyte_devices,
	.raw_event=gigabyte_raw_event,
	
};

module_hid_driver(gigabyte_hid_driver);
MODULE_LICENSE("GPL");
