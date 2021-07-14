from magma.shield.LogicStart import *
from count import CSA

csa = CSA(site=(0, 2))

wire(csa(SWITCH[0:3]), LED[0:2])
