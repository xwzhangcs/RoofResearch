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
Y = misc.imread('data/building_cluster_0093__OrthoPAN_oriented.png')
if Y.ndim == 3:
    Y = np.mean(Y[:, :, 0:2], axis=-1)
tmp = np.array(Y.flat)
a = np.delete(tmp, np.where(tmp <= 5))
print(Y.shape)
print(a.shape)
print(Y[0][0])

