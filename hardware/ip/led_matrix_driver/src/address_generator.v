module address_generator(
    // LED side
    o_RED_1,
    o_GREEN_1,
    o_BLUE_1,
    o_RED_2,
    o_GREEN_2,
    o_BLUE_2,
    // SDRAM side
    o_sdram_addr,
    o_new_data,
    i_colors_1,
    i_colors_2,

    //Control signals
    i_clk,
    i_areset_n
);


//LED side
output reg [7:0] o_RED_1;
output reg [7:0] o_GREEN_1;
output reg [7:0] o_BLUE_1;
output reg [7:0] o_RED_2;
output reg [7:0] o_GREEN_2;
output reg [7:0] o_BLUE_2;
//SDRAM side
output reg [31:0] o_sdram_addr;
output reg o_new_data;
input [23:0] i_colors_1;
input [23:0] i_colors_2;
//Control signals
input         	i_clk;
input         	i_areset_n;

//Internal signals
reg [31:0] pixel_addr;



parameter start_address = 32'd0;
parameter matrix_width = 5'd64; // 64 pixels
parameter matrix_height = 5'd32; // 32 pixels
localparam matrix_size = matrix_width * matrix_height; // 2048 pixels\
localparam end_address = start_address + matrix_size - 1; // 2047 pixels


always@(posedge i_clk or negedge i_areset)
begin
	if (!i_areset)
	begin
		pixel_addr <= start_address;
	end
	else
	begin
			// Aggiorna contatore: vai all'indirizzo seguente solo se la VGA lo richiede
					pixel_addr <= pixel_addr + 1'b1;
	end
end


endmodule