import matplotlib.pyplot as plt
import numpy as np
import argparse
import math
from sklearn.linear_model import OrthogonalMatchingPursuit
from sklearn.linear_model import OrthogonalMatchingPursuitCV
from sklearn.datasets import make_sparse_coded_signal
from scipy import misc
import glob
import cv2

a = np.array([[0, 1, 1, 1, 0], [0, 1, 1, 1, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 0, 0, 0]])
b = np.array([[0, 0, 0, 0, 0], [0, 0, 0, 0, 0], [0, 0, 1, 0, 0], [0, 1, 1, 1, 0], [0, 1, 1, 1, 0]])
# b = np.roll(np.roll(a, 1, axis=0), 1, axis=1)
Fa = np.fft.fftn(a)
Fb = np.fft.fftn(b)
C = abs(np.array(np.fft.ifftn(Fb * Fa)))
print(C)
next_index = np.argmax(C.flat)
ty, tx = np.unravel_index(next_index, (5, 5), order='C')
print(ty)
print(tx)
column = np.roll(np.roll(b, ty, axis=1), tx, axis=0)
print(column)
'''
C = abs(np.array([np.fft.ifftn(Fg * Fa) for Fg in FD]))
print(C.shape)
next_index = np.argmax(C.flat)
C = abs(np.array([np.fft.ifftn(Fg * Fa) for Fg in FD]))
print(C.shape)
print(next_index)

g = np.zeros((128,128), np.float)
g = cv2.rectangle(g, (20, 20), (60, 60), (255.0), -1)
g = cv2.rectangle(g, (40, 40), (70, 70), (255.0), -1)
misc.imsave('data/test.png', (g).astype(np.uint8))
'''