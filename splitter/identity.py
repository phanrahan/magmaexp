from magma import *
from loam.boards.icestick import IceStick

N = 8

def Identity(n):
    O = I = Bits(n)()
    return AnonymousCircuit("I", I, "O", O)

icestick = IceStick()
for i in range(N):
    icestick.J1[i].input().on()
    icestick.J3[i].output().on()

main = icestick.main()

id = Identity(8)

# need to refer to the arguments by name, can't use __call__
wire(main.J1, id.I)
wire(id.O, main.J3)

EndCircuit()
