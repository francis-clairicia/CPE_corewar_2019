#! /bin/python3
# -*- coding: Utf-8 -*

import sys
import argparse
from window import Assembly

def get_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("file", help="File to open at start", nargs='?', default=None)
    parser.add_argument("-w", "--no-workspace", help="Do not load the workspace save at start", action="store_true")
    return parser.parse_args()

def main():
    args = get_args()
    window = Assembly("Assembly - Champions Editor", 1280, 800, load_workspace=not args.no_workspace)
    window.run(args.file)
    return 0

sys.exit(main())