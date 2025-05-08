module led_matrix_top (

	//////////// CLOCK //////////
	input 		     MAX10_CLK1_50,



	//////////// KEY //////////
	//input 		     [1:0]		KEY,

	//////////// LED //////////
	//output		     [9:0]		LEDR,

	//////////// SW //////////
	//input 		     [9:0]		SW
	
	/////////// DRAM ////////
	output            DRAM_CLK,
	output            DRAM_CKE,
	output   [12: 0]  DRAM_ADDR,
	output   [ 1: 0]  DRAM_BA,
	inout    [15: 0]  DRAM_DQ,
	output            DRAM_LDQM,
	output            DRAM_UDQM,
	output            DRAM_CS_N,
	output            DRAM_WE_N,
	output            DRAM_CAS_N,
	output            DRAM_RAS_N,
	
   /////////// MATRIX ////////
	output   [12:0]   ARDUINO_IO

);    
	 
	  
	 
//=======================================================
//  REG/WIRE declarations
//=======================================================




//=======================================================
//  Structural coding
//=======================================================
	 
	 

	 
	 lite_pc computer_inst0 (
        .clk_clk                      (MAX10_CLK1_50),             //                clk.clk
        .clk_sdram_clk                (DRAM_CLK),                  //          clk_sdram.clk
        .reset_reset_n                (1'b1),                      //              reset.reset_n
        .sdram_wire_addr              (DRAM_ADDR),                 //        sdram_wire.addr
        .sdram_wire_ba                (DRAM_BA),                   //                  .ba
        .sdram_wire_cas_n             (DRAM_CAS_N),                //                  .cas_n
        .sdram_wire_cke               (DRAM_CKE),                  //                  .cke
        .sdram_wire_cs_n              (DRAM_CS_N),                 //                  .cs_n
        .sdram_wire_dq                (DRAM_DQ),                   //                  .dq
        .sdram_wire_dqm               ({DRAM_UDQM,DRAM_LDQM}),     //                  .dqm
        .sdram_wire_ras_n             (DRAM_RAS_N),                //                  .ras_n
        .sdram_wire_we_n              (DRAM_WE_N),                 //                  .we_n
        .led_matrix_clock_clk         (ARDUINO_IO[10]),            //   led_matrix_clock.clk
        .led_matrix_control_row_sel_a (ARDUINO_IO[6]),             // led_matrix_control.row_sel_a
        .led_matrix_control_row_sel_b (ARDUINO_IO[7]),             //                   .row_sel_b
        .led_matrix_control_blue_1    (ARDUINO_IO[2]),             //                   .blue_1
        .led_matrix_control_blue_2    (ARDUINO_IO[5]),             //                   .blue_2
        .led_matrix_control_row_sel_c (ARDUINO_IO[8]),             //                   .row_sel_c
        .led_matrix_control_row_sel_d (ARDUINO_IO[9]),             //                   .row_sel_d
        .led_matrix_control_green_1   (ARDUINO_IO[1]),             //                   .green_1
        .led_matrix_control_green_2   (ARDUINO_IO[4]),             //                   .green_2
        .led_matrix_control_latch     (ARDUINO_IO[11]),            //                   .latch
        .led_matrix_control_output_en (ARDUINO_IO[12]),            //                   .output_en
        .led_matrix_control_red_1     (ARDUINO_IO[0]),             //                   .red_1
        .led_matrix_control_red_2     (ARDUINO_IO[3])              //                   .red_2
    );
	 
endmodule