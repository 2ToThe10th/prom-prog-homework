fh = open("index.h", "w")
fcpp = open("index.cpp", "w")

sh = ['int A();']

scpp = ['#include <iostream>', '#include "index.h"', 'int A() {', '    std::cout << "A is here\\n";', '    return 1;', '}']

fh.write('\n'.join(sh) + '\n')

fcpp.write('\n'.join(scpp) + '\n')
