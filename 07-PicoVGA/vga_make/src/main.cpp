#include <string>
#include <sstream>
#include "hardware/adc.h"
#include "include.h"

const uint16_t WIDTH = 512;
const uint16_t HEIGHT = 400;

ALIGNED u8 FrameBuffer[WIDTH * HEIGHT];

std::string to_string(const float value, const uint8_t n = 2) {
  std::ostringstream out;
  out.precision(n);
  out << std::fixed << value;
  return out.str();
}

int main() {
  Video(DEV_VGA, RES_EGA, FORM_8BIT, FrameBuffer);

  adc_init();
  adc_set_temp_sensor_enabled(true);
  adc_select_input(4);
 
  while (true) {
    DrawClear(&Canvas);

	const std::string logo = "Make-Magazin";
	const uint16_t logo_x = (WIDTH - logo.length() * 8 * 4) / 2;
	const uint16_t logo_y = (HEIGHT - 8 * 4) / 3;
    DrawText(&Canvas, logo.c_str(), logo_x, logo_y, COL_RED, FontBoldB8x16, 16, 4, 4);

    const uint16_t result = adc_read();
	const float voltage = result * (3.3f / 4096);
    const float temperature = 27 - (voltage - 0.706) / 0.001721;
	const std::string temp_str = to_string(temperature) + " C";
	const uint16_t temp_x = (WIDTH - temp_str.length() * 8) / 2;
	const uint16_t temp_y = 200;
    DrawText(&Canvas, temp_str.c_str(), temp_x, temp_y, COL_WHITE, FontBoldB8x16, 16);

    sleep_ms(20 * 1000);
  }
}
