#include<stdio.h>
#include "razerdevice.h"
#include "razermouse_driver.h"

int main(int argc, const char * argv[]) {
    RazerDevices allDevices = getAllRazerDevices();
    RazerDevice *razerDevices = allDevices.devices;

    printf("%d Razer device(s) found:\n", allDevices.size);

    for (int i = 0; i < allDevices.size; i++) {
        RazerDevice device = razerDevices[i];
        printf("%#06x\n", device.productId);

        // Testing out the blackwidow v3 pro changes by switching to wave
        if (device.productId == USB_DEVICE_ID_RAZER_BASILISK_V3_PRO_RECEIVER)
        {
            /* printf("Found blackwidow v3 pro keyboard (wired)\n"); */
            /* razer_attr_write_mode_wave(device.usbDevice, "1", 0, 0x90); */
            printf("FOUND basilisk_v3 pro receiver\n");
            char * buf = malloc(sizeof(char)*25);
            razer_attr_read_device_serial(device.usbDevice, buf);
            printf("serial: %s\n", buf);
            razer_attr_read_get_battery(device.usbDevice, buf);
            printf("battery: %s\n", buf);
            razer_attr_read_is_charging(device.usbDevice, buf);
            printf("is charging: %s\n", buf);
            ushort poll_rate = razer_attr_read_poll_rate(device.usbDevice);
            printf("poll rate: %d\n", poll_rate);
            free(buf);
            ushort dpi_x = razer_attr_read_dpi(device.usbDevice);
            printf("dpi: %d\n", dpi_x);


        }
    }

    closeAllRazerDevices(allDevices);
    return 0;

}
