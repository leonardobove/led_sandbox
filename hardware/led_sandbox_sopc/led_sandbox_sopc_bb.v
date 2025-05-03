
module led_sandbox_sopc (
	accelerometer_spi_I2C_SDAT,
	accelerometer_spi_I2C_SCLK,
	accelerometer_spi_G_SENSOR_CS_N,
	accelerometer_spi_G_SENSOR_INT,
	clk_clk,
	clk_sdram_clk,
	keys_export,
	led_matrix_clock_clk,
	led_matrix_control_row_sel_a,
	led_matrix_control_row_sel_b,
	led_matrix_control_blue_1,
	led_matrix_control_blue_2,
	led_matrix_control_row_sel_c,
	led_matrix_control_row_sel_d,
	led_matrix_control_green_1,
	led_matrix_control_green_2,
	led_matrix_control_latch,
	led_matrix_control_output_en,
	led_matrix_control_red_1,
	led_matrix_control_red_2,
	leds_export,
	reset_reset_n,
	sdram_wire_addr,
	sdram_wire_ba,
	sdram_wire_cas_n,
	sdram_wire_cke,
	sdram_wire_cs_n,
	sdram_wire_dq,
	sdram_wire_dqm,
	sdram_wire_ras_n,
	sdram_wire_we_n,
	sliders_export);	

	inout		accelerometer_spi_I2C_SDAT;
	output		accelerometer_spi_I2C_SCLK;
	output		accelerometer_spi_G_SENSOR_CS_N;
	input		accelerometer_spi_G_SENSOR_INT;
	input		clk_clk;
	output		clk_sdram_clk;
	input	[1:0]	keys_export;
	output		led_matrix_clock_clk;
	output		led_matrix_control_row_sel_a;
	output		led_matrix_control_row_sel_b;
	output		led_matrix_control_blue_1;
	output		led_matrix_control_blue_2;
	output		led_matrix_control_row_sel_c;
	output		led_matrix_control_row_sel_d;
	output		led_matrix_control_green_1;
	output		led_matrix_control_green_2;
	output		led_matrix_control_latch;
	output		led_matrix_control_output_en;
	output		led_matrix_control_red_1;
	output		led_matrix_control_red_2;
	output	[9:0]	leds_export;
	input		reset_reset_n;
	output	[12:0]	sdram_wire_addr;
	output	[1:0]	sdram_wire_ba;
	output		sdram_wire_cas_n;
	output		sdram_wire_cke;
	output		sdram_wire_cs_n;
	inout	[15:0]	sdram_wire_dq;
	output	[1:0]	sdram_wire_dqm;
	output		sdram_wire_ras_n;
	output		sdram_wire_we_n;
	input	[9:0]	sliders_export;
endmodule
