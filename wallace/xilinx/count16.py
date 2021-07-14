from magma.shield.LogicStart import *
from count import count16

c = count16(SWITCH + SWITCH, site=(0, 2))

wire(c, LED[0:5])
