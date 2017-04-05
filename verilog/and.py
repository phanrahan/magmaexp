import sys
from magma import *
from logic import And
from loam.boards.icestick import IceStick

N = 2

icestick = IceStick()
for i in range(N):
    icestick.J1[i].input().on()
    icestick.J1[i+N].input().on()
    icestick.J3[i].output().on()

main = icestick.main()

and2 = And(N)
and2(main.J1[0:N], main.J1[N:2*N])
wire(and2.C, main.J3)

compile("build/and", main)
