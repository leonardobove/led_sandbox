
module led_sandbox_sopc (
	accelerometer_spi_I2C_SDAT,
	accelerometer_spi_I2C_SCLK,
	accelerometer_spi_G_SENSOR_CS_N,
	accelerometer_spi_G_SENSOR_INT,
	clk_clk,
	clk_sdram_clk,
	reset_reset_n,
	sdram_wire_addr,
	sdram_wire_ba,
	sdram_wire_cas_n,
	sdram_wire_cke,
	sdram_wire_cs_n,
	sdram_wire_dq,
	sdram_wire_dqm,
	sdram_wire_ras_n,
	sdram_wire_we_n);	

	inout		accelerometer_spi_I2C_SDAT;
	output		accelerometer_spi_I2C_SCLK;
	output		accelerometer_spi_G_SENSOR_CS_N;
	input		accelerometer_spi_G_SENSOR_INT;
	input		clk_clk;
	output		clk_sdram_clk;
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
endmodule
