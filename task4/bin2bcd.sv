module bin2bcd (
    input logic [7:0] x,
    output logic [11:0] BCD
);
    logic [19:0] result;

    always_comb begin
        result[19:0] = 0;
        result[7:0] = x;

        for (int i = 0; i < 8; i++) begin
            if (result[11:8] >= 5)
                result[11:8] = result[11:8] + 4'd3;
            
            if (result[15:12] >= 5)
                result[15:12] = result[15:12] + 4'd3;

            if (result[19:13] >= 5)
                result[19:13] = result[19:13] + 4'd3;
            
            result = result << 1;
        end

        assign BCD = result[19:8];
    end
endmodule