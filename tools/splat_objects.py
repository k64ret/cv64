#!/usr/bin/env python3

# Yoinked from https://github.com/ethteck/pokemonsnap/blob/main/tools/splat_objects.py
# Modified to retrieve other useful Splat config information in tandem with the build script.

import argparse
import sys
sys.path.append("./tools/splat")

from split import *

def objects(config_path) -> str:
    # Load config
    with open(config_path) as f:
        config = yaml.load(f.read(), Loader=yaml.SafeLoader)

    options.initialize(config, config_path, None, None)

    all_segments = initialize_segments(config["segments"])

    objs = ""

    for segment in all_segments:
        linker_entries = segment.get_linker_entries()
        for entry in linker_entries:
            # extra space at the end is necessary
            objs += f"{entry.object_path} "

    return objs

def baserom(config_path) -> str:
    # Load config
    with open(config_path) as f:
        config = yaml.load(f.read(), Loader=yaml.SafeLoader)

    options.initialize(config, config_path, None, None)

    return options.opts.target_path

def target(config_path) -> str:
    # Load config
    with open(config_path) as f:
        config = yaml.load(f.read(), Loader=yaml.SafeLoader)

    return config["options"]["basename"]

def build_dir(config_path) -> str:
    # Load config
    with open(config_path) as f:
        config = yaml.load(f.read(), Loader=yaml.SafeLoader)

    options.initialize(config, config_path, None, None)

    return options.opts.build_path

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Get objects for splat file',
                                     formatter_class=argparse.RawDescriptionHelpFormatter)

    parser.add_argument('yamls', nargs='+', help="Splat files")
    subparsers = parser.add_subparsers(title="Commands")

    parser_objects = subparsers.add_parser("objects", help="get the list of object files for a given Splat config file")
    parser_objects.set_defaults(func=objects)

    parser_baserom = subparsers.add_parser("baserom", help="get the input ROM file name")
    parser_baserom.set_defaults(func=baserom)

    parser_target = subparsers.add_parser("target", help="get the target name of the built ROM file")
    parser_target.set_defaults(func=target)

    parser_build_dir = subparsers.add_parser("build_dir", help="get the build directory")
    parser_build_dir.set_defaults(func=build_dir)

    args = parser.parse_args()

    outputs = map(args.func, args.yamls)
    map(print, outputs)
    for output in outputs:
        print(output)
