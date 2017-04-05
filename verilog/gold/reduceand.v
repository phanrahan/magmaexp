module main (input [1:0] J1, output  O);
wire  inst0_B;
ir_reduce_and #(.N(2)) inst0 (.A(J1), .B(inst0_B));
assign O = inst0_B;
endmodule

