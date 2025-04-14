	led_sandbox_sopc u0 (
		.accelerometer_spi_I2C_SDAT      (<connected-to-accelerometer_spi_I2C_SDAT>),      // accelerometer_spi.I2C_SDAT
		.accelerometer_spi_I2C_SCLK      (<connected-to-accelerometer_spi_I2C_SCLK>),      //                  .I2C_SCLK
		.accelerometer_spi_G_SENSOR_CS_N (<connected-to-accelerometer_spi_G_SENSOR_CS_N>), //                  .G_SENSOR_CS_N
		.accelerometer_spi_G_SENSOR_INT  (<connected-to-accelerometer_spi_G_SENSOR_INT>),  //                  .G_SENSOR_INT
		.clk_clk                         (<connected-to-clk_clk>),                         //               clk.clk
		.clk_sdram_clk                   (<connected-to-clk_sdram_clk>),                   //         clk_sdram.clk
		.reset_reset_n                   (<connected-to-reset_reset_n>),                   //             reset.reset_n
		.sdram_wire_addr                 (<connected-to-sdram_wire_addr>),                 //        sdram_wire.addr
		.sdram_wire_ba                   (<connected-to-sdram_wire_ba>),                   //                  .ba
		.sdram_wire_cas_n                (<connected-to-sdram_wire_cas_n>),                //                  .cas_n
		.sdram_wire_cke                  (<connected-to-sdram_wire_cke>),                  //                  .cke
		.sdram_wire_cs_n                 (<connected-to-sdram_wire_cs_n>),                 //                  .cs_n
		.sdram_wire_dq                   (<connected-to-sdram_wire_dq>),                   //                  .dq
		.sdram_wire_dqm                  (<connected-to-sdram_wire_dqm>),                  //                  .dqm
		.sdram_wire_ras_n                (<connected-to-sdram_wire_ras_n>),                //                  .ras_n
		.sdram_wire_we_n                 (<connected-to-sdram_wire_we_n>)                  //                  .we_n
	);

