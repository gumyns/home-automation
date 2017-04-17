#!/usr/bin/python
import os
import sys
from subprocess import call

template = """#include <cstdint>

class PluginDescription {{
   public:
       static constexpr const char* NAME = \"{name}\";
       static const uint16_t ID = {id};
}};
"""

if len(sys.argv) == 4:
    directory = os.path.abspath(str(sys.argv[1]))
    vars = {
        "name": str(sys.argv[2]),
        "id": str(sys.argv[3])
    }
else:
    sys.exit("ERROR directory missing")

call(["mkdir", directory])

with open(os.path.join(directory, "PluginDescription.h"), 'w') as f:
    f.write(template.format(**vars))
    f.close()
