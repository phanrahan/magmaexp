from magma.shield.LogicStart import *
from count import CSA

csa1 = CSA()(0, SWITCH[0], SWITCH[1])
csa2 = CSA()(csa1[0], SWITCH[2], SWITCH[3])
csa3 = CSA()(0, csa1[1], csa2[1])
csa4 = CSA()(csa2[0], SWITCH[4], SWITCH[5])
csa5 = CSA()(csa4[0], SWITCH[6], SWITCH[7])
csa6 = CSA()(csa3[0], csa4[1], csa5[1])
csa7 = CSA()(0, csa3[1], csa6[1])

wire(csa5[0], LED[0])
wire(csa6[0], LED[1])
wire(csa7[0], LED[2])
wire(csa7[1], LED[3])
