import numpy as np
import sys


layers = [30, 20, 10, 5]
for i, l in enumerate(layers[1:]):
    filename = 'layer_%d_bias.txt' % (i + 1)
    bias = np.random.rand(1, l)
    bias /= bias.max()
    with open(filename, 'w+') as out:
        print(np.array2string(bias, separator=', ', threshold=sys.maxsize, precision=2, suppress_small=True, floatmode='fixed'), file=out)
    filename = 'layer_%d_weight.txt' % (i + 1)
    weights = np.random.rand(layers[i], l)
    weights /= weights.max()
    with open(filename, 'w+') as out:
        print(np.array2string(weights, separator=', ', threshold=sys.maxsize, precision=2, suppress_small=True, floatmode='fixed'), file=out)
