`timescale 1ns/1ps

module test_address_generator_tb;

    // Testbench signals
    reg i_clk;
    reg i_areset_n;
    reg i_next_pixel;
    reg [31:0] i_colors;
    wire [9:0] o_RED_1, o_GREEN_1, o_BLUE_1;
    wire [9:0] o_RED_2, o_GREEN_2, o_BLUE_2;
    wire [31:0] o_sdram_addr;

    // Instantiate the DUT (Device Under Test)
    address_generator uut (
        .o_RED_1(o_RED_1),
        .o_GREEN_1(o_GREEN_1),
        .o_BLUE_1(o_BLUE_1),
        .o_RED_2(o_RED_2),
        .o_GREEN_2(o_GREEN_2),
        .o_BLUE_2(o_BLUE_2),
        .o_sdram_addr(o_sdram_addr),
        .i_colors(i_colors),
        .i_clk(i_clk),
        .i_areset_n(i_areset_n),
        .i_next_pixel(i_next_pixel)
    );

    // Clock generation
    initial i_clk = 0;
    always #10 i_clk = ~i_clk; // 10ns clock period

    // Testbench procedure
    initial begin
        // Initialize inputs
        i_areset_n = 0;
        i_next_pixel = 0;
        i_colors = 32'h3FF_2AA_155; // Example color data

        // Reset the DUT
        #20 i_areset_n = 1;

        // Test pixel address incrementing
        repeat (10) begin
            #20 i_next_pixel = 1; // Trigger next pixel
            #20 i_next_pixel = 0; // Deactivate next pixel
        end

        // Test wrap-around behavior
        #20 i_colors = 32'h1FF_0AA_055; // Change color data
        repeat (20) begin
            #20 i_next_pixel = 1;
        end

        // Finish simulation
        #100 $stop;
    end

endmodule