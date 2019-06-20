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
g = np.zeros((128, 128), np.float)
g = cv2.rectangle(g, (64 - int(80 / 2), 64 - int(60 / 2)),
								  (64 + int(80 / 2), 64 + int(60 / 2)), (1.0), 1)
g = cv2.line(g, (64 - int(80 / 2), 64),
								  (64 + int(80 / 2), 64), (1.0), 1)
misc.imsave('data/test.png', (g * 255).astype(np.uint8))


