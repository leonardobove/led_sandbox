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
    i_colors,

    //Control signals
    i_clk,
    i_areset_n,
    i_next_pixel
);


//LED side
output reg [9:0]     o_RED_1;
output reg [9:0]     o_GREEN_1;
output reg [9:0]     o_BLUE_1;
output reg [9:0]     o_RED_2;
output reg [9:0]     o_GREEN_2;
output reg [9:0]     o_BLUE_2;
//SDRAM side
output wire [31:0]    o_sdram_addr;
input [31:0]         i_colors;
//Control signals
input         	     i_clk;
input         	     i_areset_n;
input         	     i_next_pixel;

//Internal signals
reg [31:0]           pixel_addr;
reg [29:0]			 hi_colors;


//Parameters
parameter start_address =    32'd0;
parameter matrix_width =     8'd64; // 64 pixels
parameter matrix_height =    8'd32; // 32 pixels
localparam matrix_size = matrix_width * matrix_height; // 2048 pixels\
localparam end_address = start_address + matrix_size - 1; // 2047 pixels


assign o_sdram_addr = pixel_addr;


always@(posedge i_clk or negedge i_areset_n)
begin
	if (!i_areset_n)
	begin
		pixel_addr <= start_address;
	end
	else
	begin
        //Sincronizza lato basso e lato alto della matrice

        if (pixel_addr[0] == 1'b0)
        begin
            hi_colors <= i_colors;
            o_RED_1 <= hi_colors[29:20];
            o_GREEN_1 <= hi_colors[19:10];
            o_BLUE_1 <= hi_colors[9:0];
        end
        else
        begin
            o_RED_2 <= i_colors[29:20];
            o_GREEN_2 <= i_colors[19:10];
            o_BLUE_2 <= i_colors[9:0];
        end
        // Se si arriva all'ultimo indirizzo torna all'inizio di partenza.
        if (pixel_addr == end_address)
        begin
            pixel_addr <= start_address;
        end
        // Aggiorna contatore: vai all'indirizzo successivo
		if(i_next_pixel)
        begin
            pixel_addr <= pixel_addr + 1'b1;
        end
	end
end


endmodule