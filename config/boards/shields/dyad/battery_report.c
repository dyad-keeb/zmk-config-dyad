#include <zephyr/kernel.h>
#include <zmk/event_manager.h>
#include <zmk/hid.h>
#include <zmk/macros.h>
#include <zmk/keymap.h>
#include <zmk/endpoints.h>
#include <zmk/ble.h>
#include <zmk/battery.h>
#include <zmk/split/bluetooth/peripheral.h>

static int send_battery_status() {
    char output[32];  // Buffer for battery message

    // Get battery levels from both halves
    int left_battery = zmk_ble_get_battery_level(0);  // First connected peripheral (Left half)
    int right_battery = zmk_ble_get_battery_level(1); // Second connected peripheral (Right half)

    // Format the battery status message
    snprintf(output, sizeof(output), "L:%d%% R:%d%%", left_battery, right_battery);

    // Send the message as a macro keystroke
    return zmk_hid_type(output);
}

// Define the macro
ZMK_MACRO(battery_macro, send_battery_status());
