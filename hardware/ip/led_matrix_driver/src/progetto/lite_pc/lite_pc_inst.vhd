	component lite_pc is
		port (
			clk_clk                      : in    std_logic                     := 'X';             -- clk
			clk_sdram_clk                : out   std_logic;                                        -- clk
			led_matrix_clock_clk         : out   std_logic;                                        -- clk
			led_matrix_control_row_sel_a : out   std_logic;                                        -- row_sel_a
			led_matrix_control_row_sel_b : out   std_logic;                                        -- row_sel_b
			led_matrix_control_blue_1    : out   std_logic;                                        -- blue_1
			led_matrix_control_blue_2    : out   std_logic;                                        -- blue_2
			led_matrix_control_row_sel_c : out   std_logic;                                        -- row_sel_c
			led_matrix_control_row_sel_d : out   std_logic;                                        -- row_sel_d
			led_matrix_control_green_1   : out   std_logic;                                        -- green_1
			led_matrix_control_green_2   : out   std_logic;                                        -- green_2
			led_matrix_control_latch     : out   std_logic;                                        -- latch
			led_matrix_control_output_en : out   std_logic;                                        -- output_en
			led_matrix_control_red_1     : out   std_logic;                                        -- red_1
			led_matrix_control_red_2     : out   std_logic;                                        -- red_2
			reset_reset_n                : in    std_logic                     := 'X';             -- reset_n
			sdram_wire_addr              : out   std_logic_vector(12 downto 0);                    -- addr
			sdram_wire_ba                : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_wire_cas_n             : out   std_logic;                                        -- cas_n
			sdram_wire_cke               : out   std_logic;                                        -- cke
			sdram_wire_cs_n              : out   std_logic;                                        -- cs_n
			sdram_wire_dq                : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			sdram_wire_dqm               : out   std_logic_vector(1 downto 0);                     -- dqm
			sdram_wire_ras_n             : out   std_logic;                                        -- ras_n
			sdram_wire_we_n              : out   std_logic                                         -- we_n
		);
	end component lite_pc;

	u0 : component lite_pc
		port map (
			clk_clk                      => CONNECTED_TO_clk_clk,                      --                clk.clk
			clk_sdram_clk                => CONNECTED_TO_clk_sdram_clk,                --          clk_sdram.clk
			led_matrix_clock_clk         => CONNECTED_TO_led_matrix_clock_clk,         --   led_matrix_clock.clk
			led_matrix_control_row_sel_a => CONNECTED_TO_led_matrix_control_row_sel_a, -- led_matrix_control.row_sel_a
			led_matrix_control_row_sel_b => CONNECTED_TO_led_matrix_control_row_sel_b, --                   .row_sel_b
			led_matrix_control_blue_1    => CONNECTED_TO_led_matrix_control_blue_1,    --                   .blue_1
			led_matrix_control_blue_2    => CONNECTED_TO_led_matrix_control_blue_2,    --                   .blue_2
			led_matrix_control_row_sel_c => CONNECTED_TO_led_matrix_control_row_sel_c, --                   .row_sel_c
			led_matrix_control_row_sel_d => CONNECTED_TO_led_matrix_control_row_sel_d, --                   .row_sel_d
			led_matrix_control_green_1   => CONNECTED_TO_led_matrix_control_green_1,   --                   .green_1
			led_matrix_control_green_2   => CONNECTED_TO_led_matrix_control_green_2,   --                   .green_2
			led_matrix_control_latch     => CONNECTED_TO_led_matrix_control_latch,     --                   .latch
			led_matrix_control_output_en => CONNECTED_TO_led_matrix_control_output_en, --                   .output_en
			led_matrix_control_red_1     => CONNECTED_TO_led_matrix_control_red_1,     --                   .red_1
			led_matrix_control_red_2     => CONNECTED_TO_led_matrix_control_red_2,     --                   .red_2
			reset_reset_n                => CONNECTED_TO_reset_reset_n,                --              reset.reset_n
			sdram_wire_addr              => CONNECTED_TO_sdram_wire_addr,              --         sdram_wire.addr
			sdram_wire_ba                => CONNECTED_TO_sdram_wire_ba,                --                   .ba
			sdram_wire_cas_n             => CONNECTED_TO_sdram_wire_cas_n,             --                   .cas_n
			sdram_wire_cke               => CONNECTED_TO_sdram_wire_cke,               --                   .cke
			sdram_wire_cs_n              => CONNECTED_TO_sdram_wire_cs_n,              --                   .cs_n
			sdram_wire_dq                => CONNECTED_TO_sdram_wire_dq,                --                   .dq
			sdram_wire_dqm               => CONNECTED_TO_sdram_wire_dqm,               --                   .dqm
			sdram_wire_ras_n             => CONNECTED_TO_sdram_wire_ras_n,             --                   .ras_n
			sdram_wire_we_n              => CONNECTED_TO_sdram_wire_we_n               --                   .we_n
		);

