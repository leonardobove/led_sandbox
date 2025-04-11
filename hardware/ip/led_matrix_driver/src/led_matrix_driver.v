/*
 *  
*/

module led_matrix_driver (
    // Inputs
    input address,
    input clk,
    input reset_n,
    input write,
    input [31:0] writedata,

    // Outputs
    output reg [31:0] readdata,

    // LED matrix outputs
    output reg R1,
    output reg G1,
    output reg B1,
    output reg R2,
    output reg G2,
    output reg B2,
    output reg A,
    output reg B,
    output reg C,
    output reg D,
    output reg CLK,
    output reg LAT,
    output reg OE
);



endmodule