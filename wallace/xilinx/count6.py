from magma.shield.LogicStart import *
from count import count6to3

c = count6to3())(SWITCH[0:6])

wire(c, LED[0:3])
