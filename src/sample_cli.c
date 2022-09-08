#include<stdio.h>
#include "razerdevice.h"
#include "razermouse_driver.h"

int main(int argc, const char *argv[]) {
  RazerDevices allDevices = getAllRazerDevices();
  RazerDevice *razerDevices = allDevices.devices;

  printf("%d Razer device(s) found:\n", allDevices.size);

  for (int i = 0; i < allDevices.size; i++) {
    RazerDevice device = razerDevices[i];
    printf("%#06x\n", device.productId);

    // Testing out the blackwidow v3 pro changes by switching to wave
    if (device.productId == USB_DEVICE_ID_RAZER_BASILISK_V3_PRO_RECEIVER || device.productId == USB_DEVICE_ID_RAZER_BASILISK_V3_PRO_WIRED) {
      /* printf("Found blackwidow v3 pro keyboard (wired)\n"); */
      /* razer_attr_write_mode_wave(device.usbDevice, "1", 0, 0x90); */
      printf("FOUND basilisk_v3 pro receiver\n");
      char *buf = malloc(sizeof(char) * 256);
      razer_attr_read_device_serial(device.usbDevice, buf);
      printf("serial: %s\n", buf);
      ushort battery_level = razer_attr_read_get_battery(device.usbDevice);
      printf("battery: %d -- %d\n", battery_level, battery_level * 100 / 255);
      razer_attr_read_is_charging(device.usbDevice, buf);
      printf("is charging: %s\n", buf);
      ushort poll_rate = razer_attr_read_poll_rate(device.usbDevice);
      printf("poll rate: %d\n", poll_rate);
      ushort dpi_x = razer_attr_read_dpi(device.usbDevice);
      printf("dpi: %d\n", dpi_x);
      ushort stages_cnt = razer_attr_read_dpi_stages(device.usbDevice, buf);
      printf("dpi stages count: %d\n", stages_cnt);
      for (ushort i = 1; i < stages_cnt; i += 4) {
        char *val = (buf + i);
        ushort dpi_x = (val[0] << 8) | (val[1] & 0xFF);
        ushort dpi_y = (val[2] << 8) | (val[3] & 0xFF);
        printf("%d: %d, %d\n", i, dpi_x, dpi_y);
      }
      free(buf);
    }
  }

  closeAllRazerDevices(allDevices);
  return 0;
}
