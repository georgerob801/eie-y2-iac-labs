module dualreadrom #(
    parameter ADDRESS_WIDTH = 8,
    parameter DATA_WIDTH = 8
)(
    input logic clk,
    input logic [ADDRESS_WIDTH - 1:0] addr1,
    input logic [ADDRESS_WIDTH - 1:0] addr2,
    output logic [DATA_WIDTH - 1:0] dout1,
    output logic [DATA_WIDTH - 1:0] dout2
);

logic [DATA_WIDTH - 1:0] romArray [2 ** ADDRESS_WIDTH - 1:0];

initial begin
    $display("Loading ROM");
    $readmemh("sinerom.mem", romArray);
end;

always_ff @(posedge clk) begin
    dout1 <= romArray[addr1];
    dout2 <= romArray[addr2];
end

endmodule
