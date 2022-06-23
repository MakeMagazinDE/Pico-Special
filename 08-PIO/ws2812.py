import array, utime
from machine import Pin
from rp2 import PIO, StateMachine, asm_pio

NUM_LEDS = 10

@asm_pio(sideset_init = PIO.OUT_LOW, out_shiftdir = PIO.SHIFT_LEFT, autopull = True, pull_thresh = 24)
def ws2812():
  T1 = 2
  T2 = 5
  T3 = 3
  label("bitloop")
  out(x, 1)             .side(0) [T3 - 1]
  jmp(not_x, "do_zero") .side(1) [T1 - 1]
  jmp("bitloop")        .side(1) [T2 - 1]
  label("do_zero")
  nop()                 .side(0) [T2 - 1]

sm = StateMachine(0, ws2812, freq = 8_000_000, sideset_base = Pin(16))
sm.active(1)

led_colors = array.array("I", [0 for _ in range(NUM_LEDS)])

print("blau")
for j in range(0, 255):
  for i in range(NUM_LEDS): # Fades it in.
    led_colors[i] = j # Add another sleep to slow down the fading.
  sm.put(led_colors, 8)
  utime.sleep_ms(10)

print("rot")
for j in range(0, 255):
  for i in range(NUM_LEDS):
    led_colors[i] = j << 8
  sm.put(led_colors, 8)
  utime.sleep_ms(10)

print("grün")
for j in range(0, 255):
  for i in range(NUM_LEDS):
    led_colors[i] = j << 16
  sm.put(led_colors, 8)
  utime.sleep_ms(10)
