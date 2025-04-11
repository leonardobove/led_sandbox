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
input i_R1;
input i_G1;
input i_B1;
input i_R2;
input i_G2;
input i_B2;

//Output
output reg o_R1;
output reg o_G1;
output reg o_B1;
output reg o_R2;
output reg o_G2;
output reg o_B2;
output reg o_A;
output reg o_B;
output reg o_C;
output reg o_D;
output reg o_CLK;
output reg o_LAT;
output reg o_OE;
output reg o_next_pixel;

endmodule