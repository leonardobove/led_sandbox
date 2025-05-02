	led_sandbox_sopc u0 (
		.accelerometer_spi_I2C_SDAT      (<connected-to-accelerometer_spi_I2C_SDAT>),      //  accelerometer_spi.I2C_SDAT
		.accelerometer_spi_I2C_SCLK      (<connected-to-accelerometer_spi_I2C_SCLK>),      //                   .I2C_SCLK
		.accelerometer_spi_G_SENSOR_CS_N (<connected-to-accelerometer_spi_G_SENSOR_CS_N>), //                   .G_SENSOR_CS_N
		.accelerometer_spi_G_SENSOR_INT  (<connected-to-accelerometer_spi_G_SENSOR_INT>),  //                   .G_SENSOR_INT
		.clk_clk                         (<connected-to-clk_clk>),                         //                clk.clk
		.clk_sdram_clk                   (<connected-to-clk_sdram_clk>),                   //          clk_sdram.clk
		.led_matrix_clock_clk            (<connected-to-led_matrix_clock_clk>),            //   led_matrix_clock.clk
		.led_matrix_control_row_sel_a    (<connected-to-led_matrix_control_row_sel_a>),    // led_matrix_control.row_sel_a
		.led_matrix_control_row_sel_b    (<connected-to-led_matrix_control_row_sel_b>),    //                   .row_sel_b
		.led_matrix_control_blue_1       (<connected-to-led_matrix_control_blue_1>),       //                   .blue_1
		.led_matrix_control_blue_2       (<connected-to-led_matrix_control_blue_2>),       //                   .blue_2
		.led_matrix_control_row_sel_c    (<connected-to-led_matrix_control_row_sel_c>),    //                   .row_sel_c
		.led_matrix_control_row_sel_d    (<connected-to-led_matrix_control_row_sel_d>),    //                   .row_sel_d
		.led_matrix_control_green_1      (<connected-to-led_matrix_control_green_1>),      //                   .green_1
		.led_matrix_control_green_2      (<connected-to-led_matrix_control_green_2>),      //                   .green_2
		.led_matrix_control_latch        (<connected-to-led_matrix_control_latch>),        //                   .latch
		.led_matrix_control_output_en    (<connected-to-led_matrix_control_output_en>),    //                   .output_en
		.led_matrix_control_red_1        (<connected-to-led_matrix_control_red_1>),        //                   .red_1
		.led_matrix_control_red_2        (<connected-to-led_matrix_control_red_2>),        //                   .red_2
		.reset_reset_n                   (<connected-to-reset_reset_n>),                   //              reset.reset_n
		.sdram_wire_addr                 (<connected-to-sdram_wire_addr>),                 //         sdram_wire.addr
		.sdram_wire_ba                   (<connected-to-sdram_wire_ba>),                   //                   .ba
		.sdram_wire_cas_n                (<connected-to-sdram_wire_cas_n>),                //                   .cas_n
		.sdram_wire_cke                  (<connected-to-sdram_wire_cke>),                  //                   .cke
		.sdram_wire_cs_n                 (<connected-to-sdram_wire_cs_n>),                 //                   .cs_n
		.sdram_wire_dq                   (<connected-to-sdram_wire_dq>),                   //                   .dq
		.sdram_wire_dqm                  (<connected-to-sdram_wire_dqm>),                  //                   .dqm
		.sdram_wire_ras_n                (<connected-to-sdram_wire_ras_n>),                //                   .ras_n
		.sdram_wire_we_n                 (<connected-to-sdram_wire_we_n>)                  //                   .we_n
	);

