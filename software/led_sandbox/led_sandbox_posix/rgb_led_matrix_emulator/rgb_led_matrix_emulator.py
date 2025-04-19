import argparse
import time
import sys
import os
from PIL import Image

from RGBMatrixEmulator import RGBMatrix, RGBMatrixOptions

file_path = "../matrix_pixels.txt"

class SampleBase(object):
    def __init__(self, *args, **kwargs):
        self.parser = argparse.ArgumentParser()

        self.parser.add_argument("-r", "--led-rows", action="store", help="Display rows. 16 for 16x32, 32 for 32x32. Default: 32", default=32, type=int)
        self.parser.add_argument("--led-cols", action="store", help="Panel columns. Typically 32 or 64. (Default: 32)", default=32, type=int)
        self.parser.add_argument("-c", "--led-chain", action="store", help="Daisy-chained boards. Default: 1.", default=1, type=int)
        self.parser.add_argument("-P", "--led-parallel", action="store", help="For Plus-models or RPi2: parallel chains. 1..3. Default: 1", default=1, type=int)
        self.parser.add_argument("-p", "--led-pwm-bits", action="store", help="Bits used for PWM. Something between 1..11. Default: 11", default=11, type=int)
        self.parser.add_argument("-b", "--led-brightness", action="store", help="Sets brightness level. Default: 100. Range: 1..100", default=100, type=int)
        self.parser.add_argument("-m", "--led-gpio-mapping", help="Hardware Mapping: regular, adafruit-hat, adafruit-hat-pwm" , choices=['regular', 'regular-pi1', 'adafruit-hat', 'adafruit-hat-pwm'], type=str)
        self.parser.add_argument("--led-scan-mode", action="store", help="Progressive or interlaced scan. 0 Progressive, 1 Interlaced (default)", default=1, choices=range(2), type=int)
        self.parser.add_argument("--led-pwm-lsb-nanoseconds", action="store", help="Base time-unit for the on-time in the lowest significant bit in nanoseconds. Default: 130", default=130, type=int)
        self.parser.add_argument("--led-show-refresh", action="store_true", help="Shows the current refresh rate of the LED panel")
        self.parser.add_argument("--led-slowdown-gpio", action="store", help="Slow down writing to GPIO. Range: 0..4. Default: 1", default=1, type=int)
        self.parser.add_argument("--led-no-hardware-pulse", action="store", help="Don't use hardware pin-pulse generation")
        self.parser.add_argument("--led-rgb-sequence", action="store", help="Switch if your matrix has led colors swapped. Default: RGB", default="RGB", type=str)
        self.parser.add_argument("--led-pixel-mapper", action="store", help="Apply pixel mappers. e.g \"Rotate:90\"", default="", type=str)
        self.parser.add_argument("--led-row-addr-type", action="store", help="0 = default; 1=AB-addressed panels; 2=row direct; 3=ABC-addressed panels; 4 = ABC Shift + DE direct", default=0, type=int, choices=[0,1,2,3,4])
        self.parser.add_argument("--led-multiplexing", action="store", help="Multiplexing type: 0=direct; 1=strip; 2=checker; 3=spiral; 4=ZStripe; 5=ZnMirrorZStripe; 6=coreman; 7=Kaler2Scan; 8=ZStripeUneven... (Default: 0)", default=0, type=int)
        self.parser.add_argument("--led-panel-type", action="store", help="Needed to initialize special panels. Supported: 'FM6126A'", default="", type=str)
        self.parser.add_argument("--led-no-drop-privs", dest="drop_privileges", help="Don't drop privileges from 'root' after initializing the hardware.", action='store_false')
        self.parser.set_defaults(drop_privileges=True)

    def usleep(self, value):
        time.sleep(value / 1000000.0)

    def run(self):
        print("Running")

    def process(self):
        self.args = self.parser.parse_args()
        self.options = RGBMatrixOptions()

        if self.args.led_gpio_mapping != None:
          self.options.hardware_mapping = self.args.led_gpio_mapping
        self.options.rows = self.args.led_rows
        self.options.cols = self.args.led_cols
        self.options.chain_length = self.args.led_chain
        self.options.parallel = self.args.led_parallel
        self.options.row_address_type = self.args.led_row_addr_type
        self.options.multiplexing = self.args.led_multiplexing
        self.options.pwm_bits = self.args.led_pwm_bits
        self.options.brightness = self.args.led_brightness
        self.options.pwm_lsb_nanoseconds = self.args.led_pwm_lsb_nanoseconds
        self.options.led_rgb_sequence = self.args.led_rgb_sequence
        self.options.pixel_mapper_config = self.args.led_pixel_mapper
        self.options.panel_type = self.args.led_panel_type


        if self.args.led_show_refresh:
          self.options.show_refresh_rate = 1

        if self.args.led_slowdown_gpio != None:
            self.options.gpio_slowdown = self.args.led_slowdown_gpio
        if self.args.led_no_hardware_pulse:
          self.options.disable_hardware_pulsing = True
        if not self.args.drop_privileges:
          self.options.drop_privileges=False

        self.matrix = RGBMatrix(options = self.options)

        try:
            # Start loop
            print("Press CTRL-C to stop sample")
            self.run()
        except KeyboardInterrupt:
            print("Exiting\n")
            sys.exit(0)

        return True
    
class AdafruitRGBMatrix64x32(SampleBase):
    def __init__(self, *args, **kwargs):
        super(AdafruitRGBMatrix64x32, self).__init__(*args, **kwargs)

    def load_pixel_data(self, file_path):
        with open(file_path, "r") as f:
            lines = f.readlines()

        if len(lines) != self.options.cols * self.options.rows:
            raise ValueError(f"Expected {self.options.cols * self.options.rows} pixels, got {len(lines)}.")

        image = Image.new("RGB", (self.options.cols, self.options.rows))
    
        for i, line in enumerate(lines):
            line = line.strip()
            if len(line) != 3 or any(c not in "01" for c in line):
                raise ValueError(f"Invalid pixel format on line {i}: '{line}'")

            r, g, b = (int(bit) * 255 for bit in line)
            x = i % self.options.cols
            y = i // self.options.cols
            image.putpixel((x, y), (r, g, b))

        return image

    def run(self):
        offset_canvas = self.matrix.CreateFrameCanvas()
        last_mtime = 0
        while True:
            mtime = os.path.getmtime(file_path)
            if mtime != last_mtime:
                image = self.load_pixel_data(file_path=file_path)
                self.matrix.SetImage(image)
                last_mtime = mtime
            time.sleep(0.01)  # Refresh every 10ms

# Main function
if __name__ == "__main__":
    emulator = AdafruitRGBMatrix64x32()
    if (not emulator.process()):
        emulator.print_help()