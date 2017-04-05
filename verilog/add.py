import sys
from magma import *
from arith import DefineAdd
from loam.boards.icestick import IceStick

N = 2

Add = DefineAdd(N)

icestick = IceStick()
for i in range(N):
    icestick.J1[i].input().on()
    icestick.J1[i+N].input().on()
    icestick.J3[i].output().on()

main = icestick.main()

add = Add()
add(main.J1[0:N], main.J1[N:2*N])
wire(add.C, main.J3)

compile("build/add", main)
