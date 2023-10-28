`timescale 1ns/1ns
module uart_tb;
  logic clk;
  logic rst;
  
  localparam CLK_PERIOD = 20; // 20ns -> 50 MHz
  localparam CLKS_PER_BIT = 50_000_000/9600; // How many 50MHz clock periods are in 9600Hz
  
  always #(CLK_PERIOD/2) clk = ~clk; // 20ns clock period
  
  // tx:
	logic tx; // the TX pin
	logic [7:0]  data_to_send;   
	logic tx_valid;  // handshake
	logic tx_ready;  // handshake
  
  //rx:
	logic rx;   // The RX pin
	logic [7:0]  data_received; 
	logic rx_valid;       // handshake
	logic rx_ready;       // handshake
  
  assign rx = tx; // TX module sends data to RX module (for testing purposes).
  
  uart_tx #(.CLKS_PER_BIT(CLKS_PER_BIT)) DUT_tx(.*, .valid(tx_valid), .ready(tx_ready));
  uart_rx #(.CLKS_PER_BIT(CLKS_PER_BIT)) DUT_rx(.*, .valid(rx_valid), .ready(rx_ready));
  
  initial begin
    $dumpfile("dump.vcd"); $dumpvars;
    clk = 0;
    rst = 1;
	 rx_ready = 1;
	 data_to_send = 8'h55;
	 $display("Sending data %b on the TX pin via uart_tx.", data_to_send);
    tx_valid = 1;
    #(CLK_PERIOD*3) rst = 0;
    #(CLK_PERIOD*2) tx_valid = 0;
    @(posedge rx_valid); // Wait for the RX module to return valid data.
	 $display("Received data %b on the RX pin via uart_rx.",data_received);
    #(CLK_PERIOD*CLKS_PER_BIT*2) $stop;
  end
  
endmodule

