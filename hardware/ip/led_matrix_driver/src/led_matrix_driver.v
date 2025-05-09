/* This module drives the Adafruit RGB LED 64x32 matrix with HUB75 interface. 
 * The matrix is composed of a set of six concurrent shift register chains,
 * each with one output bit per column, the six chains being red, green and blue
 * bits for non-adjacent rows, plus a set of row drivers (each driving the
 * aforementioned two rows) selected by a combination of address lines.
 *
 * These address lines are the A, B, C and D output signals, with a total of 16
 * distinct address line combinations, each driving two rows, leading to a total
 * of 32 pixels of height. For example, address 0 enables rows 0 and 16, address 1
 * enables rows 1 and 17, etc. ... Shift register chain length determines the matrix
 * width, 64 pixels in our case.
 *
 * These matrices render only one bit each for red, green and blue and therefore they
 * do not natively display full color. R1/G1/B1 represent the RGB 3-bits value for the
 * lower-half row, whereas R2/G2/B2 represent the RGB 3-bits value for the upper-half
 * row.
 *
 * The CLK signal determines a shift of 1 step (i.e. one column) in the chain of the pixel
 * colors. The LAT signal (active high) allows to latch the value stored in the shift registers
 * onto the output stage, which actually displays the latched content only when OE_n (active low)
 * is enabled. Therefore, the pixel values can be shifted on the "background" through the whole
 * row without updating the content of the value previously loaded onto the latch registers.
 * Therefore, the latch signal can be enabled for one clock cycle at the end of each row.
 *
 * This driver, if enabled, continuously refreshes the matrix (TODO: talk about the registers...)
 * Avalon MM slave interface:
 *                   0  Reset (W)
 *                   1  Enable (W)
*/

module led_matrix_driver (

    //_________________________
    // Clock and reset signals
    //_________________________
    input        clock,
    input        areset_n,
	 
    //_________________________
    // Avalon ST sink interface
    //_________________________

	//Input sink
    input [5:0]  data,
	input        valid,
	input        endofpacket,
	input        startofpacket,
	 
	//Output sink
	output       ready,

         
    //_________________________
    // Avalon MM slave interface
    //_________________________ 

	//Write signals
    input        address,
	input        write,
	input[31:0]  writedata,
	 
	//Read signals
    input        read,
	output[31:0] readdata,

    //_________________________
    // Avalon conduit interface
    //_________________________

    output       R1,
    output       G1,
    output       B1,
    output       R2,
    output       G2,
    output       B2,
    output       A,
    output       B,
    output       C,
    output       D,
    output       CLK,
    output       LAT,
    output       OE_n
);

// Parameters

parameter ENABLE_DEFAULT = 1'b1;                 //Default value for the enable register
parameter RESET_DEFAULT  = 1'b0;                 //Default value for the reset register
parameter MAT_WIDTH      = 7'd64;                //Width of the matrix (number of pixels in a row)
parameter MAT_HEIGHT     = 6'd32;                //Height of the matrix (number of pixels in a column)
localparam HALF_HEIGHT   = MAT_HEIGHT >> 1'b1;   //Half height of the matrix (number of pixels in a row)

// FSM States
localparam RESET         = 3'd0, 
           IDLE          = 3'd1,
           PUSH_ROW      = 3'd2,
           CHANGE_ROW    = 3'd3,
           OUTPUT_EN     = 3'd4; 


// Internal signals
reg [5:0] col_counter;
reg [3:0] row_counter;
reg [5:0] pixels_rgb_colors; 
reg enable_register;
reg reset_register;
reg [2:0] curr_state, next_state;

// Internal MM signals
wire sw_reset;
wire driving_enable;
wire reset_wr_strobe;
wire enable_wr_strobe;

// LED matrix external outputs
// Color output signals
assign R1 =                  pixels_rgb_colors[0];
assign G1 =                  pixels_rgb_colors[1];
assign B1 =                  pixels_rgb_colors[2];
assign R2 =                  pixels_rgb_colors[3];
assign G2 =                  pixels_rgb_colors[4];
assign B2 =                  pixels_rgb_colors[5];
// Row select signals
assign A =                   row_counter[0];
assign B =                   row_counter[1];
assign C =                   row_counter[2];
assign D =                   row_counter[3];
// Control signals
assign CLK =                 (~clock & (curr_state == PUSH_ROW) & valid & ready);
assign LAT =                 (curr_state == CHANGE_ROW) || (curr_state == RESET);
assign OE_n =                (curr_state == CHANGE_ROW);
// Stream interface signals
assign ready =               
    (curr_state == IDLE) ||
        (curr_state == PUSH_ROW);

// Avalon MM interface signals
assign readdata =            32'b0;

// Internal MM signals
assign reset_wr_strobe =     write && (address == 1'b0); 
assign enable_wr_strobe =    write && (address == 1'b1);
assign driving_enable =      enable_register;
assign sw_reset =            reset_register;

// Reset sw
always @ (posedge clock or negedge areset_n)
begin 
    if (~areset_n)
    begin
        reset_register <= RESET_DEFAULT;
    end
    //One cycle reset register
    else
    begin
        if (reset_wr_strobe) 
        begin
            reset_register <= writedata[0];
        end
        else
        begin
            reset_register <= RESET_DEFAULT;
        end 
    end
end

// Enable sw
always @ (posedge clock or negedge areset_n)
begin 
    if (~areset_n)
    begin
        enable_register = ENABLE_DEFAULT;
    end 
    //toggle enable register
    else
    begin
        if (enable_wr_strobe) 
        begin
            enable_register <= writedata[0];
        end
        else
        begin
            enable_register <= enable_register;
        end 
    end
end

// Column counter
always @ (posedge clock or negedge areset_n) begin
    if (~areset_n) begin
        col_counter <= 6'd0;
    end 
    else 
    begin
        if (curr_state == PUSH_ROW) 
        begin
            if (col_counter == (MAT_WIDTH - 1'b1))
                col_counter <= 6'd0;
            else if(valid && ready)
            begin
                col_counter <= col_counter + 1'b1;
            end
        end
        else
        begin
            if (curr_state == RESET) 
            begin
            col_counter <= 6'd0;
		    end
            if (curr_state == IDLE)
            begin
                col_counter <= 6'd0;
            end
            else
            begin
		      col_counter <= col_counter;
            end
		end

    end
end

// Row counter
always @ (posedge clock or negedge areset_n) 
begin
    if (~areset_n) 
    begin
        row_counter <= 4'd0;
    end 
    else 
    begin
        if (curr_state == CHANGE_ROW) 
        begin
            if (row_counter == HALF_HEIGHT - 1'b1)
                row_counter <= 4'd0;
            else
                row_counter <= row_counter + 1'b1;
        end 
        else 
        begin
            if (curr_state == RESET) 
            begin
                row_counter <= 4'd0;
		    end
            if (curr_state == IDLE)
            begin
                row_counter <= 4'd0;
            end
            else
            begin
			    row_counter <= row_counter;
		    end
        end
    end
end

// Pixels RGB colors
always @ (posedge clock or negedge areset_n) 
begin
    if (~areset_n) 
    begin
        pixels_rgb_colors <= 6'd0;
    end
    else 
    begin
        if (curr_state == PUSH_ROW) 
        begin
            pixels_rgb_colors <= data[5:0];
        end 
        else 
        begin
            if (curr_state == RESET)
            begin
                pixels_rgb_colors <= 6'd0;
            end 
            else 
            begin
            pixels_rgb_colors <= pixels_rgb_colors;
            end
        end
    end
end



// Update FSM State
always @ (posedge clock or negedge areset_n) begin
    if (~areset_n) 
    begin
        curr_state <= RESET;
    end 
    else 
    begin
        curr_state <= next_state;
    end
end

// Evaluate next state
always @ (*) begin
    case (curr_state)
        RESET: begin
            next_state <= IDLE;
        end

        IDLE: begin
            if(~sw_reset)
            begin
		        if(valid & startofpacket & driving_enable)
				begin
					next_state <= PUSH_ROW;
				end
				else
				begin
				    next_state <= IDLE;
				end
            end
            else
            begin
                next_state <= RESET;
            end
        end

        PUSH_ROW: begin
            if (~sw_reset)
            begin
                if(driving_enable)
                begin
                    if (col_counter == (MAT_WIDTH - 1'b1))
                        next_state <= CHANGE_ROW;
                    else
                        next_state <= PUSH_ROW;
                end
                else 
                begin
                    next_state <= IDLE;
                end
            end
            else
            begin
                next_state <= RESET;
            end
        end

        CHANGE_ROW: begin
            if (~sw_reset)
            begin
                if (driving_enable)
                begin
                    if (row_counter == (HALF_HEIGHT - 1'b1))
                    begin
                        next_state <= OUTPUT_EN;
                    end
                    else
                    begin
                        next_state <= PUSH_ROW;
                    end
                end
                else
                begin
                    next_state <= IDLE;
                end
            end
            else
            begin
                next_state <= RESET;
            end
        end

        OUTPUT_EN: begin
            if (~sw_reset)
            begin
                next_state <= IDLE;
            end
            else
            begin
                next_state <= RESET;
            end
        end
		  
		  default: begin
            next_state <= RESET;
        end
    endcase
end


endmodule