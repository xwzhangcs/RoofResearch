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
'''
a = np.matrix('0 1 1 1 0; 0 1 1 1 0; 0 1 1 0 0; 0 0 0 0 0; 0 0 0 0 0')
b = np.matrix('0 0 0 0 0; 0 1 1 0 0; 0 1 1 0 0; 0 1 1 0 0; 0 0 0 0 0')
a = np.array(a)
b = np.array(b)
#print(a.shape)
#print(b)
Fa = np.fft.fftn(a)
Fb = np.fft.fftn(b)
print(Fb)
Fb = np.conj(Fb)
print(Fb)
FD = []
D = []
FD.append(Fb)
D.append(b)
#print(Fa)
#print(Fb)
C = np.array([np.fft.ifftn(Fg * Fa) for Fg in FD])
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
g = np.zeros((128, 128), np.float)
g = cv2.rectangle(g, (64 - int(30 / 2), 64 - int(40 / 2)),
								  (64 + int(30 / 2), 64 + int(40 / 2)), (1.0), -1)
g = cv2.line(g, (64 - int(30 / 2), 64),
								  (64 + int(30 / 2), 64), (1.0), 1)


g = cv2.rectangle(g, (34 - int(30 / 2), 44 - int(40 / 2)),
								  (34 + int(30 / 2), 44 + int(40 / 2)), (1.0), -1)
g = cv2.line(g, (34, 44 - int(40 / 2)),
								  (34, 44 + int(40 / 2)), (1.0), 1)


g = cv2.rectangle(g, (94 - int(30 / 2), 44 - int(40 / 2)),
								  (94 + int(30 / 2), 44 + int(40 / 2)), (1.0), -1)
g = cv2.line(g, (94, 44 - int(40 / 2)),
								  (94, 44 + int(40 / 2)), (1.0), 1)

misc.imsave('data/example_v1.png', (g * 255).astype(np.uint8))