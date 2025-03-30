#!/usr/bin/env python3

with open("A", "w") as file_output:
    content = [chr(0)] * (4 * 1024 * 1024 + 1)
    content[0] = content[10_000] = content[-1] = chr(1)
    file_output.write("".join(content))
