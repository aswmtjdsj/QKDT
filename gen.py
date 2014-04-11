import random, os, sys

if __name__ == '__main__':
    if len(sys.argv) < 3:
        raise Exception("Not Enough Parameters! Should be: python gen.py filename number_of_points")
    else:
        try:
            n = int(sys.argv[2])
        except:
            raise Exception("Parameter 2 should be an integer!")

    f = open(sys.argv[1], "w")
    print >> f, n
    for i in range(n):
        x = random.random() * 10
        y = random.random() * 10
        print >> f, "{0:.6} {1:.6}".format(x, y)
    f.close()
