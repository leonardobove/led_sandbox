# LED Sandbox
LED Sandbox

This project has the main goal to create a physic's driven colorful sand animation using a led matrix and Terasic DE10-lite.
The animation is based on DE10 accelerometer or gestures captured via D8M camera and elaborated by a small neural network.
The animation is displayed in a led matrix.

We use a SOPC approach with hardware periferial driver and sw for physics elaborations.


# Periferial PINOUT

## LED Matrix
| name | External PIN | Board PIN |           Description                           |
| ---- | ------------ | --------- |     ------------------------                    |
|  R1  |      1       |           | RED led upper Sub-matrix                        |
|  G1  |      2       |           | GREEN led upper Sub-matrix                      |
|  B1  |      3       |           | BLUE led upper Sub-matrix                       |
|  GND |      4       |           | ground                                          |
|  R2  |      5       |           | RED led lower Sub-matrix                        |
|  G2  |      6       |           | GREEN led lower Sub-matrix                      |
|  B2  |      7       |           | BLUE led lower Sub-matrix                       |
|  GND |      8       |           | ground                                          |
|  A   |      9       |           | Select which column you are driving             |
|  B   |      10      |           | Select which column you are driving             |
|  C   |      11      |           | Select which column you are driving             |
|  D   |      12      |           | Select which column you are driving             |
|  CLK |      13      |           | Clock for led visualization                     |
|  LAT |      14      |           | Latches the value until put low                 |
|  OE  |      15      |           | Output enable. High until all led values loaded |
|  GND |      16      |           | ground                                          |
