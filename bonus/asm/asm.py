#! /bin/python3
# -*- coding: Utf-8 -*

import sys
import argparse
from window import Assembly

def get_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("file", help="File to open at start", nargs='?', default=None)
    return parser.parse_args()

def main():
    args = get_args()
    window = Assembly("Assembly - Champions Editor", 1280, 800)
    window.run(args.file)
    return 0

sys.exit(main())