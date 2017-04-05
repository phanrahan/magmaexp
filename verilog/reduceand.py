import sys
from magma import *
from logic import ReduceAnd
from loam.boards.icestick import IceStick

N = 2

icestick = IceStick()
for i in range(N):
    icestick.J1[i].input().on()
icestick.J3[0].rename('O').output().on()

main = icestick.main()

reduceand = ReduceAnd(N)
reduceand(main.J1)
wire(reduceand.B, main.O)

compile("build/reduceand", main)
