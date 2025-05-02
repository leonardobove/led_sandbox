`timescale 1ns/1ps

module led_matrix_driver_tb ();
// Testbench for the LED matrix driver

//Inputs
reg clock;
reg areset_n;

// Streaming inputs
reg [15:0] data;
reg valid;
reg endofpacket;
reg startofpacket;

//Memory mapped inputs
reg address;
reg write;
reg [31:0] writedata;
reg read;

// Outputs
wire ready;
wire [31:0] readdata;

// LED matrix outputs
wire R1, G1, B1, R2, G2, B2;
wire A, B, C, D, CLK, LAT, OE_n;

//Instantiate the DUT (Device Under Test)
led_matrix_driver uut (
    .clock(clock),
    .areset_n(areset_n),
    .data(data),
    .valid(valid),
    .endofpacket(endofpacket),
    .startofpacket(startofpacket),
    .ready(ready),
    .address(address),
    .write(write),
    .writedata(writedata),
    .read(read),
    .readdata(readdata),
    .R1(R1),
    .G1(G1),
    .B1(B1),
    .R2(R2),
    .G2(G2),
    .B2(B2),
    .A(A),
    .B(B),
    .C(C),
    .D(D),
    .CLK(CLK),
    .LAT(LAT),
    .OE_n(OE_n)
);

initial begin
    // Clock generation
    clock = 0;
    forever #20 clock = ~clock; // 40ns clock period
end

initial begin
    //Initialize inputs
    areset_n = 1;
    data = 16'b0;
    valid = 0;
    endofpacket = 0;
    startofpacket = 0;
    address = 0;
    write = 0;
    read = 0;
    writedata = 32'b0;

    // Apply reset
    #120
    areset_n = 0;

    // Wait for a few clock cycles
    #80
    areset_n = 1;
    
    // Test case 1: Write to the memory-mapped register
    #40
    data = 16'hA5A5; // Example data
    valid = 1;
    startofpacket = 1;

    #1000
    data = 16'h0048;

    //Test case 3: Enable sw
     #10000
    write = 1'b1;
    address = 1'd1;
    writedata = 32'd0;

    #40
    write = 1'b0;
    address = 1'd1;

    #200
    write = 1'b1;
    address = 1'd1;
    writedata = 32'd1;

    #40
    write = 1'b0;
    address = 1'd1;

    //Test case 4: Reset sw
    #10000
    write = 1'b1;
    address = 1'd0;
    writedata = 32'd1;

    #40
    write = 1'b0;

    //Finish the simulation after a few cycles
    #50000
    $finish;

end
endmodule