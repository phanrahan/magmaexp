from magma import *
from mantle import *
from loam.boards.icestick import IceStick
from best import sort8
from swap import swap

icestick = IceStick()
for i in range(8):
    icestick.J1[i].input().on()
for i in range(8):
    icestick.J3[i].output().on()

main = icestick.main()

I = main.J1.as_list()

for wire0, wire1 in sum(sort8, []):
    O = swap(bits([I[wire0], I[wire1]]))
    I[wire0], I[wire1]  = O[0], O[1]

wire(bits(I), main.J3)

EndCircuit()
