module ir_and ( A, B, C );
parameter N = 8;
input [N-1:0] A;
input [N-1:0] B;
output [N-1:0] C;
assign C = A & B;
endmodule

module ir_nand ( A, B, C );
parameter N = 8;
input [N-1:0] A;
input [N-1:0] B;
output [N-1:0] C;
assign C = ~(A & B);
endmodule

module ir_or ( A, B, C );
parameter N = 8;
input [N-1:0] A;
input [N-1:0] B;
output [N-1:0] C;
assign C = A | B;
endmodule

module ir_nor ( A, B, C );
parameter N = 8;
input [N-1:0] A;
input [N-1:0] B;
output [N-1:0] C;
assign C = ~(A | B);
endmodule

module ir_xor ( A, B, C );
parameter N = 8;
input [N-1:0] A;
input [N-1:0] B;
output [N-1:0] C;
assign C = A ^ B;
endmodule

module ir_xnor ( A, B, C );
parameter N = 8;
input [N-1:0] A;
input [N-1:0] B;
output [N-1:0] C;
assign C = A ~^ B;
endmodule

module ir_shl ( A, B );
parameter N = 8;
parameter SHIFT = 1;
input [N-1:0] A;
output [N-1:0] B;
assign B = A >> SHIFT;
endmodule

module ir_shr ( A, B );
parameter N = 8;
parameter SHIFT = 1;
input [N-1:0] A;
output [N-1:0] B;
assign B = A << SHIFT;
endmodule

module ir_invert( A, B );
parameter N = 8;
input [N-1:0] A;
output [N-1:0] B;
assign B = ~A;
endmodule


module ir_bitand ( A, B, C );
parameter N = 8;
input A;
input B;
output C;
assign C = A & B;
endmodule

module ir_not( A, B );
input A;
output B;
assign B = !A;
endmodule


module ir_reduce_and ( A, B );
parameter N = 8;
input [N-1:0] A;
output B;
assign B = &A;
endmodule

module ir_reduce_or ( A, B );
parameter N = 8;
input [N-1:0] A;
output B;
assign B = |A;
endmodule

module ir_reduce_xor ( A, B );
parameter N = 8;
input [N-1:0] A;
output B;
assign B = |A;
endmodule
