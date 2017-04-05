// unsigned comparison operators

module ir_ugt ( A, B, C );
parameter N = 8;
input [N-1:0] A;
input [N-1:0] B;
output C;
assign C = A > B;
endmodule

module ir_uge ( A, B, C );
parameter N = 8;
input [N-1:0] A;
input [N-1:0] B;
output C;
assign C = A >= B;
endmodule

module ir_ult ( A, B, C );
parameter N = 8;
input [N-1:0] A;
input [N-1:0] B;
output C;
assign C = A < B;
endmodule

module ir_uge ( A, B, C );
parameter N = 8;
input [N-1:0] A;
input [N-1:0] B;
output C;
assign C = A <= B;
endmodule

module ir_sgt ( A, B, C );
parameter N = 8;
input signed [N-1:0] A;
input signed [N-1:0] B;
output C;
assign C = A > B;
endmodule

module ir_sge ( A, B, C );
parameter N = 8;
input signed [N-1:0] A;
input signed [N-1:0] B;
output C;
assign C = A >= B;
endmodule

module ir_slt ( A, B, C );
parameter N = 8;
input signed [N-1:0] A;
input signed [N-1:0] B;
output C;
assign C = A < B;
endmodule

module ir_sge ( A, B, C );
parameter N = 8;
input signed [N-1:0] A;
input signed [N-1:0] B;
output C;
assign C = A <= B;
endmodule


module ir_eq ( A, B, C );
parameter N = 8;
input [N-1:0] A;
input [N-1:0] B;
output C;
assign C = A == B;
endmodule

module ir_ne ( A, B, C );
parameter N = 8;
input [N-1:0] A;
input [N-1:0] B;
output C;
assign C = A != B;
endmodule

