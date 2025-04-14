	component led_sandbox_sopc is
		port (
			accelerometer_spi_I2C_SDAT      : inout std_logic                     := 'X';             -- I2C_SDAT
			accelerometer_spi_I2C_SCLK      : out   std_logic;                                        -- I2C_SCLK
			accelerometer_spi_G_SENSOR_CS_N : out   std_logic;                                        -- G_SENSOR_CS_N
			accelerometer_spi_G_SENSOR_INT  : in    std_logic                     := 'X';             -- G_SENSOR_INT
			clk_clk                         : in    std_logic                     := 'X';             -- clk
			clk_sdram_clk                   : out   std_logic;                                        -- clk
			reset_reset_n                   : in    std_logic                     := 'X';             -- reset_n
			sdram_wire_addr                 : out   std_logic_vector(12 downto 0);                    -- addr
			sdram_wire_ba                   : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_wire_cas_n                : out   std_logic;                                        -- cas_n
			sdram_wire_cke                  : out   std_logic;                                        -- cke
			sdram_wire_cs_n                 : out   std_logic;                                        -- cs_n
			sdram_wire_dq                   : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			sdram_wire_dqm                  : out   std_logic_vector(1 downto 0);                     -- dqm
			sdram_wire_ras_n                : out   std_logic;                                        -- ras_n
			sdram_wire_we_n                 : out   std_logic                                         -- we_n
		);
	end component led_sandbox_sopc;

	u0 : component led_sandbox_sopc
		port map (
			accelerometer_spi_I2C_SDAT      => CONNECTED_TO_accelerometer_spi_I2C_SDAT,      -- accelerometer_spi.I2C_SDAT
			accelerometer_spi_I2C_SCLK      => CONNECTED_TO_accelerometer_spi_I2C_SCLK,      --                  .I2C_SCLK
			accelerometer_spi_G_SENSOR_CS_N => CONNECTED_TO_accelerometer_spi_G_SENSOR_CS_N, --                  .G_SENSOR_CS_N
			accelerometer_spi_G_SENSOR_INT  => CONNECTED_TO_accelerometer_spi_G_SENSOR_INT,  --                  .G_SENSOR_INT
			clk_clk                         => CONNECTED_TO_clk_clk,                         --               clk.clk
			clk_sdram_clk                   => CONNECTED_TO_clk_sdram_clk,                   --         clk_sdram.clk
			reset_reset_n                   => CONNECTED_TO_reset_reset_n,                   --             reset.reset_n
			sdram_wire_addr                 => CONNECTED_TO_sdram_wire_addr,                 --        sdram_wire.addr
			sdram_wire_ba                   => CONNECTED_TO_sdram_wire_ba,                   --                  .ba
			sdram_wire_cas_n                => CONNECTED_TO_sdram_wire_cas_n,                --                  .cas_n
			sdram_wire_cke                  => CONNECTED_TO_sdram_wire_cke,                  --                  .cke
			sdram_wire_cs_n                 => CONNECTED_TO_sdram_wire_cs_n,                 --                  .cs_n
			sdram_wire_dq                   => CONNECTED_TO_sdram_wire_dq,                   --                  .dq
			sdram_wire_dqm                  => CONNECTED_TO_sdram_wire_dqm,                  --                  .dqm
			sdram_wire_ras_n                => CONNECTED_TO_sdram_wire_ras_n,                --                  .ras_n
			sdram_wire_we_n                 => CONNECTED_TO_sdram_wire_we_n                  --                  .we_n
		);

