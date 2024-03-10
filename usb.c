// @COMPILECMD gcc $@ -lusb-1.0
#include <stdio.h>
#include <libusb-1.0/libusb.h>

#define VENDOR_ID 0x0b95
#define PRODUCT_ID 0x1790
const int WRITE_CONSTS[] = {
	0x0002,
	0x0004
};
// <?!> 1 <?!> 00000000000000001 <?!>

const char* intToBinary64(int value) {
    static char binary[67]; // Buffer to hold the binary representation (64 bits + '0b' prefix + null-terminator)
    binary[0] = '0';
    binary[1] = 'b';
    for (int i = 63; i >= 0; i--) {
        binary[2 + 63 - i] = ((value >> i) & 1) ? '1' : '0';
    }
    binary[66] = '\0';
    return binary;
}

int main() {
    libusb_device_handle* handle;
    libusb_init(NULL);
    handle = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
    if (handle == NULL) {
        fprintf(stderr, "Could not find/open the USB device.\n");
        return 1;
    }

    unsigned char data[64]; // Replace with your data or remove this line for other operations
	int result, i;
	const int start = WRITE_CONSTS[(sizeof(WRITE_CONSTS)/sizeof(int))-1];
	for(i = 0; i < 64; i++){
		result = libusb_control_transfer(
			handle,
			LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_OUT,
			0x0001 << i,
			0, // wValue
			0, // wIndex
			data, // Data buffer containing dummy data
			sizeof(data), // wLength
			1000 // Timeout in milliseconds
		);
		if (result > 0) {
			printf("%s, %d\n", intToBinary64(i), i);
		}
	}

    libusb_close(handle);
    libusb_exit(NULL);
    return 0;
}
