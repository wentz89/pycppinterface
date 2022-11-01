from interfaceCPP.interfaceCPP import Base
from typing import List

# TODO enforce uint8_t for args with List[np.uint8]

class VirtualBasePy(Base):

    def __init__(self, name: str):
        Base.__init__(self, name)

    def Run(self, args: List[int]) -> int:
        raise NotImplementedError

    def Stop(self, args: List[int]) -> int:
        raise NotImplementedError
