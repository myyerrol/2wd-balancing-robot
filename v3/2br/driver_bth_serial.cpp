#include "driver_bth_serial.hpp"

void initBTHSerial() {
    SerialBT.begin("2BR");
}
