import random, os, sys

if __name__ == '__main__':
    if len(sys.argv) < 4:
        raise Exception("Not Enough Parameters! Should be: python gen.py filename number_of_points coor_scale")
    else:
        try:
            n = int(sys.argv[2])
            scale = int(sys.argv[3])
        except:
            raise Exception("Parameter 2 should be an integer!")

    f = open("./data/" + sys.argv[1], "w")
    print >> f, n
    for i in range(n):
        x = random.random() * scale
        y = random.random() * scale
        print >> f, "{0:.6} {1:.6}".format(x, y)
    f.close()
