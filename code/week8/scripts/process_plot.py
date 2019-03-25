import json
import argparse
import matplotlib.pyplot as plt
import numpy

parser = argparse.ArgumentParser(
    description='Read a JSON file with rows/columns.')
parser.add_argument('path', metavar='path', help='path to the data')
parser.add_argument('--save', metavar='save', default="", help='save file as')

args = parser.parse_args()

with open(args.path) as f:
    j = json.load(f)

    fig = plt.figure(figsize=[8, 6])
    ax = fig.add_subplot(111)

    xs, ys = map(list, zip(*j["rows"]))
    xs = list(map(float, xs))
    ys = list(map(float, ys))

    ax.plot(xs, ys)

    ax.set_xlabel(j["columns"][0])
    ax.set_ylabel(j["columns"][1])

    ax.set_axisbelow(True)

    plt.grid()
    plt.tight_layout()

    if args.save != "":
        plt.savefig(args.save)
    else:
        plt.show()
