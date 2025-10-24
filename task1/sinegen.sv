module sinegen (
    input logic [7:0] incr,
    input logic rst,
    input logic en,
    input logic clk,
    output logic [7:0] dout
);

logic [7:0] addr;

counter addrCounter(
    .clk(clk),
    .rst(rst),
    .en(en),
    .incr(incr),
    .count(addr)
);

rom sineROM(
    .clk(clk),
    .addr(addr),
    .dout(dout)
);

endmodule
