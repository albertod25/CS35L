#!/usr/bin/python

"""
Shuffles lines of text.

Rewritten from C
"""

import random, sys, string, argparse

class shuf:
    def __init__(self, filename):
        if isinstance(filename, (list,)):
            self.lines=filename
        else:
            if(filename == "-" or filename == None):
                f = sys.stdin
            else:
                f = open(filename, 'r')
            self.lines = f.readlines()
            f.close()
    
    def isfull(self):
        return self.lines

    def remove(self, line):
        self.lines.remove(line)

    def chooseline(self):
        return random.choice(self.lines)

def main():
    parser = argparse.ArgumentParser(usage="shuf [OPTION]... [FILE]\n  or: shuf -i LO-HI [OPTION]...", description="Write a random permutation of the input lines to standard output.")

	# These are the different options that the user can call
    parser.add_argument("-i", "--input-range",
                        type=str,
                        dest="LO_HI",
                        default=None,
                        help="treat each number LO through HI as an input line")
    parser.add_argument("-n", "--head-count",
                        type=int,
                        dest="COUNT",
                        default=None,
                        help="output at most COUNT lines")
    parser.add_argument("-r", "--repeat",
                        dest="repeat",
                        action="store_true",
                        help="output lines can be repeated")
    parser.add_argument("FILE",
                        type=str,
                        nargs='?',
                        default=None,
                        help="with no FILE, or when FILE is -, read standard input.")

    args = parser.parse_args(sys.argv[1:])

    # grabs the variables inputted from the options
    repeat = bool(args.repeat)
    nMax=args.COUNT
    
    # Either produce a file from integer range or read file
    if(args.LO_HI != None):
        if(args.FILE != None):
            print("extra operand {}".format(args.FILE))
            sys.exit(0)

        try:
            r = [int(x) for x in (args.LO_HI.split("-"))]
            
            # checks for invalid input to -i
            if (len(r) != 2):
                raise
            if (r[1] < r[0]):
                raise

            inFile = range(r[0], r[1] + 1)
        except:
            print("invalid input range: {}".format(args.LO_HI))
            sys.exit(0)
    else:
        try:
            inFile=args.FILE
        except:
            print("invalid input: ".format(args.FILE))
            sys.exit(0)

    shufFile=shuf(inFile)

    try:
        if (repeat):
            if (shufFile.isfull()):
                count = 0
                while (count != nMax):
                    sys.stdout.write(shufFile.chooseline())
                    count = count + 1
            else:
                print("shuf: no lines to repeat")
        else:
            count = 0
            while (shufFile.isfull() and count != nMax):
                line = shufFile.chooseline()
                sys.stdout.write(line)
                shufFile.remove(line)
                count = count + 1
    except IOError as err:
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))

if __name__ == "__main__":
    main()
