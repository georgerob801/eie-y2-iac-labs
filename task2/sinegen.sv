module sinegen (
    input logic [7:0] incr,
    input logic [7:0] offset,
    input logic rst,
    input logic en,
    input logic clk,
    output logic [7:0] dout1,
    output logic [7:0] dout2
);

logic [7:0] addr;
logic [7:0] offsetAddr;

counter addrCounter(
    .clk(clk),
    .rst(rst),
    .en(en),
    .incr(incr),
    .count(addr)
);

always_comb offsetAddr = addr + offset;

dualreadrom sineROM(
    .clk(clk),
    .addr1(addr),
    .addr2(offsetAddr),
    .dout1(dout1),
    .dout2(dout2)
);

endmodule
