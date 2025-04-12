`timescale 1ns/1ps

module led_driver_tb;

    // Inputs
    reg i_clk;
    reg i_areset_n;
    reg [9:0] i_R1, i_G1, i_B1, i_R2, i_G2, i_B2;

    // Outputs
    wire [9:0] o_R1, o_G1, o_B1, o_R2, o_G2, o_B2;
    wire o_A, o_B, o_C, o_D, o_CLK, o_LAT, o_OE, o_next_pixel;

    // Instantiate the DUT (Device Under Test)
    led_driver uut (
        .i_clk(i_clk),
        .i_areset_n(i_areset_n),
        .i_R1(i_R1),
        .i_G1(i_G1),
        .i_B1(i_B1),
        .i_R2(i_R2),
        .i_G2(i_G2),
        .i_B2(i_B2),
        .o_R1(o_R1),
        .o_G1(o_G1),
        .o_B1(o_B1),
        .o_R2(o_R2),
        .o_G2(o_G2),
        .o_B2(o_B2),
        .o_A(o_A),
        .o_B(o_B),
        .o_C(o_C),
        .o_D(o_D),
        .o_CLK(o_CLK),
        .o_LAT(o_LAT),
        .o_OE(o_OE),
        .o_next_pixel(o_next_pixel)
    );

    // Clock generation
    initial i_clk = 0;
    always #10 i_clk = ~i_clk; // 10ns clock period

    // Testbench logic
    initial begin
        // Initialize inputs
        i_areset_n = 0;
        i_R1 = 10'd0; i_G1 = 10'd0; i_B1 = 10'd0;
        i_R2 = 10'd0; i_G2 = 10'd0; i_B2 = 10'd0;

        // Apply reset
        #20 i_areset_n = 1;

        // Test case 1: Provide some input values
        #20 i_R1 = 10'd255; i_G1 = 10'd128; i_B1 = 10'd64;
        i_R2 = 10'd32; i_G2 = 10'd16; i_B2 = 10'd8;

        // Wait for FSM transitions
        #200;

        // Test case 2: Change input values
        i_R1 = 10'd512; i_G1 = 10'd256; i_B1 = 10'd128;
        i_R2 = 10'd64; i_G2 = 10'd32; i_B2 = 10'd16;

        // Wait for FSM transitions
        #200;

        // End simulation
        $stop;
    end

endmodule