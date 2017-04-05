module main (input [1:0] I0, input [1:0] I1, output [1:0] O);
wire [1:0] inst0_C;
Add inst0 (.A(I0), .B(I1), .C(inst0_C));
assign O = inst0_C;
endmodule

