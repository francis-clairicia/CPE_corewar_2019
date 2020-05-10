#! /bin/python3
# -*- coding: Utf-8 -*

import sys
from window import Assembly

def main():
    window = Assembly("Assembly - Champions Editor", 1280, 720)
    window.run()
    return 0

sys.exit(main())