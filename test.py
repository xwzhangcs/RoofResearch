import matplotlib.pyplot as plt
import numpy as np
import argparse
import math
from sklearn.linear_model import OrthogonalMatchingPursuit
from sklearn.linear_model import OrthogonalMatchingPursuitCV
from sklearn.datasets import make_sparse_coded_signal
from scipy import misc
from scipy.ndimage import rotate
import glob
import cv2
from scipy.ndimage import convolve


a = np.matrix('0 1 1 1 0; 0 1 1 1 0; 0 1 1 0 0; 0 0 0 0 0; 0 0 0 0 0')
b = np.matrix('0 0 0 0 0; 0 1 1 0 0; 0 1 1 0 0; 0 1 1 0 0; 0 0 0 0 0')
a = np.array(a)
b = np.array(b)
a_b_conv = convolve(a, b)
print(a_b_conv)

#print(a.shape)
#print(b)
Fa = np.fft.fftn(a)
Fb = np.fft.fftn(b)
#Fb = np.conj(Fb)
FD = []
D = []
FD.append(Fb)
D.append(b)
#print(Fa)
#print(Fb)
C = np.array([np.fft.ifftn(Fg * Fa) for Fg in FD])
print(C)
'''
next_index = np.argmax(C.flat)
i, ty, tx = np.unravel_index(next_index, (len(D), 5, 5), order='C')
print(i, ty, tx)
column = np.roll(np.roll(D[i], ty, axis=0), tx, axis=1)
print(column)
column = np.reshape(column, (np.prod(column.shape), 1))
A = column
Y = a

# calculate coefficient by solving Ax=Y
coeff = np.linalg.solve(A.T.dot(A), A.T.dot(Y.flat))
# calculate the current image
Y2 = np.reshape(A.dot(coeff), Y.shape)
print(Y2)
'''