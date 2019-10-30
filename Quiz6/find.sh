#!/bin/sh

whereis $1 | cut -d" " -f2
