module counter #(
    parameter WIDTH = 8
)(
    // interface signals
    input   logic               clk,    // clock
    input   logic               rst,    // reset
    input   logic               en,     // counter enable
    input   logic               dir,    // counter direction
    output  logic [WIDTH - 1:0] count   // count output
);

logic [WIDTH - 1:0] increment = dir == 1'b0 ? {{WIDTH-1{1'b0}}, en} : {{WIDTH{en}}};

always_ff @ (posedge clk, posedge rst)
    if (rst) count <= {WIDTH{1'b0}};
    else count <= count + increment;

endmodule
