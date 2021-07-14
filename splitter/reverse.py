from magma import wire, Permute, EndCircuit
from loam.boards.icestick import IceStick

N = 8

icestick = IceStick()
for i in range(N):
    icestick.J1[i].input().on()
    icestick.J3[i].output().on()

main = icestick.main()

P = Permute(N, reversed(range(N)), basename='Reverse')
wire( P(main.J1), main.J3 )

EndCircuit()
