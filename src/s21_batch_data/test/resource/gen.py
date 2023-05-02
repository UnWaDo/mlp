from random import randint


length = 100
classes = 5
data_n = 30
filename = 'data.csv'
# filename = '%d_%d.csv' % (classes, data_n)
# filename = '%d_%d_ones.csv' % (classes, data_n)
divis = data_n // classes
with open(filename, 'w+') as out:
    for i in range(length):
        obj_type = randint(0, classes - 1)
        inputs = [randint(obj_type * divis, (obj_type + 1) * divis) for j in range(data_n)]
        out.write('%d,' % (obj_type + 1) + ','.join([str(inp) for inp in inputs]) + '\n')
        # out.write('%d,' % randint(1, classes) + ','.join([str(randint(0, 255)) for j in range(data_n)]) + '\n')
        # out.write('%d,' % 1 + ','.join([str(0) for j in range(data_n)]) + '\n')
