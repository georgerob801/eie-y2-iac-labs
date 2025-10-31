module dualportram #(
    parameter ADDRESS_WIDTH = 8,
    parameter DATA_WIDTH = 8
)(
    input logic clk,
    input logic wrEn,
    input logic rdEn,
    input logic [ADDRESS_WIDTH - 1:0] wrAddr,
    input logic [ADDRESS_WIDTH - 1:0] rdAddr,
    input logic [DATA_WIDTH - 1:0] din,
    output logic [DATA_WIDTH - 1:0] dout
);

logic [DATA_WIDTH - 1:0] ramArray [2 ** ADDRESS_WIDTH - 1:0];

always_ff @(posedge clk) begin
    if (wrEn == 1'b1)
        ramArray[wrAddr] <= din;
    if (rdEn == 1'b1)
        dout <= ramArray[rdAddr];
end

endmodule
