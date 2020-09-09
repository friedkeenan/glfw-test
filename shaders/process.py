#!/usr/bin/env python3

import argparse
from pathlib import Path

parser = argparse.ArgumentParser()
parser.add_argument("--out-dir", type=Path)
parser.add_argument("--source-dir", type=Path)
parser.add_argument("input", metavar="N", type=Path, nargs="+")
args = parser.parse_args()

template = """#pragma once

constexpr char {0}_array[] = {1};
constexpr unsigned int {0}_len = {2};
constexpr std::string_view {0}({0}_array, {0}_len);"""

for s in args.input:
    out = Path(args.out_dir, s.resolve().relative_to(args.source_dir))

    with s.open("rb") as r, out.open("w") as w:
        cont = [x for x in r.read()]
        cont.append(0)

        name = s.name.replace(".", "_")

        w.write(template.format(
            name,
            "{" + ", ".join(f"0x{x:02x}" for x in cont) + "}",
            len(cont),
        ))