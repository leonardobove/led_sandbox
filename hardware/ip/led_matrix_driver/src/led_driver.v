// Lo schermo è formato da 2 blocchi da 64*16 pixel, quindi 2*64*16=2048 pixel riempiti in parallelo
// Ogni fine riga devo prendere almeno un ciclo di clock per alsare ed abbassare il segnale di Latch
// per salvare il valore della riga corrente e passare alla successiva cambiando gli A,B, C ,D
// Alla fine della pagina prendo almeno un ciclo di clock extra per abilitare l'uscita

module led_driver (
    // Inputs
    i_clk,
    i_areset_n,
    i_R1,
    i_G1,
    i_B1,
    i_R2,
    i_G2,
    i_B2,

    // Outputs to Matrix
    o_R1,
    o_G1,
    o_B1,
    o_R2,
    o_G2,
    o_B2,
    o_A,
    o_B,
    o_C,
    o_D,
    o_CLK,
    o_LAT,
    o_OE,

    // Outputs to Address Generator
    o_next_pixel
);

//Inputs
input i_clk;
input i_areset_n;
input[9:0] i_R1;
input[9:0] i_G1;
input[9:0] i_B1;
input[9:0] i_R2;
input[9:0] i_G2;
input[9:0] i_B2;

//Output
output wire[9:0] o_R1;
output wire[9:0] o_G1;
output wire[9:0] o_B1;
output wire[9:0] o_R2;
output wire[9:0] o_G2;
output wire[9:0] o_B2;
output wire o_A;
output wire o_B;
output wire o_C;
output wire o_D;
output wire o_CLK;
output reg o_LAT;
output reg o_OE;
output wire o_next_pixel;

//Internal signals
reg[6 : 0] column_counter;
reg[3 : 0] row_counter;
reg[1 : 0] oe_counter;
reg[1 : 0] state;

// Parameters
parameter matrix_width               = 8'd64;                      // 64 pixels
parameter matrix_half_height         = 8'd16;                      // full height 32 pixels
localparam LATCH_TIME                = 2'd2;                       //tempo per latchare riga
localparam OE_TIME                   = 2'd2;                       //tempo per aggiornare l'uscita
localparam RESET = 0, PLOTTING = 1, END_COLUMN = 2, END_MATRIX = 3;//Stati FSM

//Assign
assign o_next_pixel = (state == PLOTTING);
assign o_CLK = i_clk;
assign o_A = row_counter[0];
assign o_B = row_counter[1];
assign o_C = row_counter[2];
assign o_D = row_counter[3];
assign o_R1 = i_R1;
assign o_G1 = i_G1;
assign o_B1 = i_B1;
assign o_R2 = i_R2;
assign o_G2 = i_G2;
assign o_B2 = i_B2;

//FSM
always@(posedge i_clk or negedge i_areset_n)
begin
    if(!i_areset_n)
    begin
        state <= RESET;
        row_counter      <= 4'd0;        
        column_counter   <= 7'd0; 
        o_OE             <= 1'b1;
        oe_counter       <= 2'd0;
    end
    case(state)
        RESET:
        begin
            //Pulisco i contatori e gli output e latch
            row_counter    <= 0;
            column_counter <= 0;
            oe_counter     <= 0;
            o_LAT          <= 0;
            o_OE           <= 1;
            state          <= PLOTTING;
        end
        PLOTTING:
        begin
            row_counter <= row_counter;
            oe_counter <= 0;
            o_OE <= 1;
            o_LAT <= 0;
            //Controllo se sono all'ultima colonna
            if(column_counter < (matrix_width - 1))
            begin
                column_counter <= column_counter + 7'd1;
                state <= PLOTTING;
            end
            else
            begin
                state <= END_COLUMN;
                column_counter <= column_counter;
            end
        end
        END_COLUMN:
        begin
            o_OE <= 1;
            oe_counter <= 0;
            if(column_counter < (matrix_width + LATCH_TIME - 1))
            begin
                o_LAT <= 1;
                row_counter <= row_counter;
                column_counter <= column_counter + 7'd1;
                state <= END_COLUMN;
            end
            else
                begin
                    o_LAT <= 0;
                    if(row_counter == matrix_half_height)
                    begin
                        state <= END_MATRIX;
                        row_counter <= row_counter;
                        column_counter <= column_counter;
                    end
                    else
                    begin
                        row_counter <= row_counter + 4'd1;
                        column_counter <= 0;
                        state <= PLOTTING;
                    end
                end
        end
        END_MATRIX:
        begin
            o_LAT <= 0;
            row_counter <= row_counter;
            column_counter <= column_counter;
            if(oe_counter < OE_TIME)
            begin
                o_OE <= 0;
                oe_counter <= oe_counter + 2'd1;
                state <= END_MATRIX;
            end
            else
            begin
                state <= RESET;
                o_OE <= 1;
                oe_counter <= oe_counter;

            end
        end
		  default:
          begin
            state <= RESET;
            row_counter <= 0;
            column_counter <= 0;
            oe_counter <= 0;
          end
    endcase

end


endmodule