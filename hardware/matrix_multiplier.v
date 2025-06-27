module matrix_multiplier (
   input clk,
   input reset,
   input [31:0] a_val_in,
   input [31:0] b_val_in,
   input add_to_accum,
   input reset_accum,
   output reg [31:0] accum_out,
   output reg done_flag
);
reg [31:0] accum;
reg prev_add_to_accum;  
always @(posedge clk) begin
   if (reset) begin
       accum <= 0;
       accum_out <= 0;
       done_flag <= 0;
       prev_add_to_accum <= 0;
   end else begin
       done_flag <= 0;
       prev_add_to_accum <= add_to_accum;
       if (reset_accum) begin
           accum <= 0;
       end
       else if (add_to_accum && !prev_add_to_accum) begin
           accum <= accum + (a_val_in * b_val_in);
           done_flag <= 1;
       end
       accum_out <= accum;
   end
end
endmodule
