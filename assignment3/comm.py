#! /usr/bin/python

import sys
import locale
from optparse import OptionParser
locale.setlocale(locale.LC_COLLATE, 'C')

optionVal = []

def comm():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE FILE
    Line by line comparison of the 2 inputed files.
    Also supports options to supress certain 
    comparison columns. """
    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    for i in range(1,4):
        parser.add_option("-%d" % i, "--suppress%d" % i,
                          action="store_true"
                          , dest="s%d" % i,
                          default=False,
                          help="suppress column #%d" % i)

    parser.add_option("-u", "--nocheck-order",
                      action="store_true", dest="sort",
                      default=False, help="-u to skip sorting file")
    
    options, args = parser.parse_args(sys.argv[1:])

    try:
        s1 = bool(options.s1)
    except:
        parser.error("cannot store option 1")

    try:
        s2 = bool(options.s2)
    except:
        parser.error("cannot store option 2")

    try:
        s3 = bool(options.s3)
    except:
        parser.error("cannot store option3")

    try:
        sort = bool(options.sort)
    except:
        parser.error("error with -u option")

    
    if len(args) != 2:
        parser.error("invalid number of arguments")
    else:
        # store each files lines in separate arrays
        file1 = []
        file2 = []
        if args[0] == "-":
            f1 = sys.stdin
            file1 = sorted(f1.readlines())
        else:
            f1 = open(args[0])
            file1 = f1.readlines()

        if args[1] == "-":
            f2 = sys.stdin
            file2 = sorted(f2.readlines())
            file1 = sorted(file1)
        else:
            f2 = open(args[1])
            file2 = f2.readlines()

        if args[0] == "-":
            file2 = sorted(file2)

        if not sort:
            if sorted(file1) != file1:
                parser.error("file1 is not sorted, use -u \
                option or sort the contents")
            if sorted(file2) != file2:
                parser.error("file2 is not sorted, use -u \
                option or sort the contents")
        
        # close up files opened earlier
        f1.close()
        f2.close()
        
    # deal with options
    optionVal = [s1, s2, s3]
        
    if not sort:
        combined = sorted(file1 + file2)
        processed = []
        for line in combined:
            output = ""
            if line not in processed:
                numTimesInFile1 = file1.count(line)
                numTimesInFile2 = file2.count(line)
               
                if numTimesInFile1 < numTimesInFile2:
                    for i in range(numTimesInFile1):
                        if not optionVal[0]:
                            output += '\t'
                        if not optionVal[1]:
                            output += '\t'
                        if not optionVal[2]:
                            output += line.rstrip('\n')
                            print ("%s" % output)
                        output = ""

                    r = numTimesInFile2 - numTimesInFile1
                    for i in range(r):
                        if not optionVal[0]:
                            output += '\t'
                        if not optionVal[1]:
                            output += line.rstrip('\n')
                            print ("%s" % output)
                        output = ""
                
                elif numTimesInFile1 > numTimesInFile2:
                    for i in range(numTimesInFile2):
                        if not optionVal[0]:
                            output += '\t'
                        if not optionVal[1]:
                            output += '\t'
                        if not optionVal[2]:
                            output += line.rstrip('\n')
                            print ("%s" % output)
                        output = ""

                    r = numTimesInFile1 - numTimesInFile2
                    for i in range(r):
                        if not optionVal[0]:
                            print ("%s" % line.rstrip('\n'))
                
                else:
                    for i in range(numTimesInFile1):
                        if not optionVal[0]:
                            output += '\t'
                        if not optionVal[1]:
                            output += '\t'
                        if not optionVal[2]:
                            output += line.rstrip('\n')
                            print ("%s" % output)
                        output = ""

                processed.append(line)
        return
        
    # compare lines for each file
    combined = file1 + file2

    for line in combined:
        output = ""
        
        if not file1 and sort:
            for item in file2:
                if not optionVal[0]:
                    output += '\t'
                if not optionVal[1]:
                    output += item.rstrip('\n')
                    print ("%s" % output)
                output = ""
            break;
        
        if line in file1 and line not in file2:
            if not optionVal[0]:
                print ("%s" % line.rstrip('\n'))
            file1.remove(line)

        elif line in file2 and line not in file1:
            if not optionVal[0]:
                output += '\t'
            if not optionVal[1]:
                output += line.rstrip('\n')
                print ("%s" % output)

            file2.remove(line)

        else:
            if not optionVal[0]:
                output += '\t'
            if not optionVal[1]:
                output += '\t'
            if not optionVal[2]:
                output += line.rstrip('\n')
                print ("%s" % output)

            if line in file2:
                file2.remove(line)
            if line in file1:
                file1.remove(line)
        combined = file1 + file2
        
if __name__ == "__main__":
    comm()
