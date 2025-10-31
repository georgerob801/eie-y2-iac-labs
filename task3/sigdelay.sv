module sigdelay (
    input logic clk,
    input logic [7:0] sample,
    input logic [8:0] offset,
    input logic wrEn,
    input logic rst,
    output logic [7:0] dout,
    output logic [8:0] readAddr
);

    logic [8:0] writeAddr;
    //logic [8:0] readAddr;

    always_comb readAddr = writeAddr - offset;

    counter cnt (
        .clk(clk),
        .rst(rst),
        .en(1'b1),
        .incr(1'b1),
        .count(writeAddr)
    );

    dualportram #(.ADDRESS_WIDTH(9)) ram (
        .clk(clk),
        .din(sample),
        .wrAddr(writeAddr),
        .rdEn(1),
        .wrEn(wrEn),
        .rdAddr(readAddr),
        .dout(dout)
    );
    
endmodule
