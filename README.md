# LED Sandbox
LED Sandbox

This project has the main goal to create a physic's driven colorful sand animation using a led matrix and Terasic DE10-lite.
The animation is based on DE10 accelerometer or gestures captured via D8M camera and elaborated by a small neural network.
The animation is displayed in a led matrix.

We use a SOPC approach with hardware periferial driver and sw for physics elaborations.


# Periferial PINOUT

## LED Matrix
| name | External PIN | Board PIN  |           Description                           |
| ---- | ------------ | ---------  |     ------------------------                    |
|  R1  |      1       | ARD_IO[0]  | RED led upper Sub-matrix                        |
|  G1  |      2       | ARD_IO[1]  | GREEN led upper Sub-matrix                      |
|  B1  |      3       | ARD_IO[2]  | BLUE led upper Sub-matrix                       |
|  GND |      4       | GND        | ground                                          |
|  R2  |      5       | ARD_IO[3]  | RED led lower Sub-matrix                        |
|  G2  |      6       | ARD_IO[4]  | GREEN led lower Sub-matrix                      |
|  B2  |      7       | ARD_IO[5]  | BLUE led lower Sub-matrix                       |
|  GND |      8       | GND        | ground                                          |
|  A   |      9       | ARD_IO[6]  | Select which column you are driving             |
|  B   |      10      | ARD_IO[7]  | Select which column you are driving             |
|  C   |      11      | ARD_IO[8]  | Select which column you are driving             |
|  D   |      12      | ARD_IO[9]  | Select which column you are driving             |
|  CLK |      13      | ARD_IO[10] | Clock for led visualization                     |
|  LAT |      14      | ARD_IO[11] | Latches the value until put low                 |
|  OE  |      15      | ARD_IO[12] | Output enable. High until all led values loaded |
|  GND |      16      | GND        | ground                                          |
