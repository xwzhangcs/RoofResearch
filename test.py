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

# define T shape generators

index = 0
max_aspect = 4
min_aspect = 2
max_aspect_l2 = 2
min_aspect_l2 = 0.7
width_lengths = np.arange(30, 105, 2)
width_l2_lengths = np.arange(2, 105, 2)
height_lengths = np.arange(2, 105, 2)
for width in width_lengths:
    for height in height_lengths:
        if min_aspect <= width/height <= max_aspect:
            for space in np.arange(int(width * 0.6), int(width * 0.8), 5):
                for width_l2 in width_l2_lengths:
                    for height_l2 in height_lengths:
                        if min_aspect_l2 <= height_l2/width_l2 <= max_aspect_l2 and width * 0.2 <= width_l2 <= width * 0.4 and space + width_l2 < width * 0.9\
                                and height_l2 <= height and 64 + int(height/2) + height_l2 < 110:
                            g = np.zeros((128, 128), np.float)
                            g = cv2.rectangle(g, (64 - int(width/2), 64 - int(height/2)), (64 + int(width/2), 64 + int(height/2)), (1.0), -1)
                            g = cv2.rectangle(g, (64 - int(width / 2) + space, 64 + int(height / 2)),
                                              (64 - int(width / 2) + space + width_l2, 64 + int(height / 2) + height_l2), (1.0), -1)
                            g = rotate(g, -90, reshape=False)
                            misc.imsave('results/generator_' + str(index) + '.png', (g * 255).astype(np.uint8))
                            index = index + 1
'''
# define U shape generators
index = 0
max_aspect = 4
min_aspect = 2
width_lengths = np.arange(50, 105, 2)
width__l2_lengths = np.arange(2, 105, 2)
height_lengths = np.arange(2, 105, 2)
for width in width_lengths:
    for height in height_lengths:
        if min_aspect <= width/height <= max_aspect:
            for width_l2 in width__l2_lengths:
                for height_l2 in height_lengths:
                    if min_aspect <= height_l2/width_l2 <= max_aspect and width * 0.3 <= width_l2 <= width * 0.5 and height_l2 >= height * 1.8 and 64 - int(height / 2) + height_l2 < 110:
                        g = np.zeros((128, 128), np.float)
                        g = cv2.rectangle(g, (64 - int(width/2), 64 - int(height/2)), (64 + int(width/2), 64 + int(height/2)), (1.0), -1)
                        g = cv2.rectangle(g, (64 + int(width / 2) - width_l2, 64 - int(height / 2)),
                                          (64 + int(width / 2), 64 - int(height / 2) + height_l2), (1.0), -1)
                        misc.imsave('results/generator_' + str(index) + '.png', (g * 255).astype(np.uint8))
                        index = index + 1
'''