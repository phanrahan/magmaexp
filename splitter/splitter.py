from magma import wire, Splitter, EndCircuit
from loam.boards.icestick import IceStick

N = 8

icestick = IceStick()
icestick.J1[0].rename('I').input().on()
for i in range(N):
    icestick.J3[i].output().on()

main = icestick.main()

wire( Splitter(8)(main.I), main.J3 )

EndCircuit()
