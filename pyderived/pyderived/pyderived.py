# Copyright (C) 2022  Alexander Wentz

from pyinterface.pyinterface import VirtualBasePy
from typing import List

# TODO enforce uint8_t with List[np.uint8]

class pyderived(VirtualBasePy):
    def __init__(self, name):
        super(Derived, self).__init__(name)

    def Run(self, args: List[int]) -> int:
        return args[0]

    def Stop(self, args: List[int]) -> int:
        return args[1] 


def main():
    d = pyderived("asd")
    print(d.Run([1]))
    try:
        print(d.Stop([1, 2]))
    except RuntimeError:
        print("Calling a pure virtual Function not possible since Derived does not implement it. ")
    del d

if __name__=="__main__":
    main()
