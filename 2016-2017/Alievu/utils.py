import numpy as np

dump_path = '/home/qpon/Learning/Alievu/play/data/'

LOG_FLAG = True

def prod(iterable):
    mult = 1
    for item in iterable:
        mult *= item
    return mult

def to1D(np_array):
    return np_array.reshape(int(np_array.size))

def concatNewStep(full_array, observation, action):
    return np.vstack((full_array, np.hstack((to1D(observation), action))))

def toNDim(np_array, n):
    m = int(np_array.size / n)
    if LOG_FLAG:
        print('array: ' + str(np_array))
        print('size: ' + str(np_array.size))
        print('n: ' + str(n))
        print('m: ' + str(m))
        print('shape: ' + str(np_array.shape))
        print('array after: ' + str(np_array.reshape((n, m))))
    return np_array.reshape((m))

if __name__ == "__main__":
    
    print('TEST UTILS')
    a = np.array([[1,2,3], [4,5,6]])
    b = toNDim(a, 3)
    print(b)
    print(b[0])
