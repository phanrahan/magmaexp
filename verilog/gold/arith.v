module ir_add ( A, B, C );
parameter N = 8;
input [N-1:0] A;
input [N-1:0] B;
output [N:0] C;
assign C = A + B;
endmodule

module ir_trunc_add ( A, B, C );
parameter N = 8;
input [N-1:0] A;
input [N-1:0] B;
output [N-1:0] C;
assign C = A + B;
endmodule

module ir_adc ( A, B, CIN, C, COUT );
parameter N = 8;
input [N-1:0] A;
input [N-1:0] B;
input CIN;
output [N-1:0] C;
output COUT;
assign {COUT, C} = A + B + CIN;
endmodule

module ir_sub ( A, B, C );
parameter N = 8;
input [N-1:0] A;
input [N-1:0] B;
output [N:0] C;
assign C = A - B;
endmodule

module ir_trunc_sub ( A, B, C );
parameter N = 8;
input [N-1:0] A;
input [N-1:0] B;
output [N-1:0] C;
assign C = A - B;
endmodule

module ir_sbc ( A, B, CIN, C, COUT );
parameter N = 8;
input [N-1:0] A;
input [N-1:0] B;
input CIN;
output [N-1:0] C;
output COUT;
assign {COUT, C} = A - B - CIN;
endmodule

module ir_neg ( A, B );
parameter N = 8;
input [N-1:0] A;
output [N-1:0] B;
assign B = -A;
endmodule

module ir_asr ( A, B );
parameter N = 8;
parameter SHIFT = 1;
input signed [N-1:0] A;
output [N-1:0] B;
assign B = A >>> SHIFT;
endmodule

module ir_ror ( A, B );
parameter N = 8;
parameter SHIFT = 1;
input [N-1:0] A;
output [N-1:0] B;
assign B = {A[SHIFT-1:0], A[N-1:SHIFT]};
endmodule


