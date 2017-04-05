module main (input [3:0] J1, output [1:0] J3);
wire [1:0] inst0_C;
ir_and #(.N(2)) inst0 (.A({J1[1],J1[0]}), .B({J1[3],J1[2]}), .C(inst0_C));
assign J3 = inst0_C;
endmodule

