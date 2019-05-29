import os, sys, logging, time, math
import numpy as np
import pylab as plt
import cv2
import pandas
from scipy import misc
import random

class Peak:
    def __init__(self, startidx):
        self.born = self.left = self.right = startidx
        self.died = None

    def get_persistence(self, seq):
        #return float("inf") if self.died is None else seq[self.born] - seq[self.died]
        left_index = np.max([0, self.born])
        right_index = np.min([len(seq) - 1, self.born + 1])
        return (seq[left_index] + seq[right_index]) / 2

    def get_value(self, values):
        left_index = np.max([0, self.born])
        right_index = np.min([len(values) - 1, self.born + 1])
        return (values[left_index] + values[right_index]) / 2
        #return values[self.born]


def get_persistent_homology(seq, values):
    peaks = []
    # Maps indices to peaks
    idxtopeak = [None for s in seq]
    # Sequence indices sorted by values
    indices = range(len(seq))
    indices = sorted(indices, key = lambda i: seq[i], reverse=True)

    # Process each sample in descending order
    for idx in indices:
        lftdone = (idx > 0 and idxtopeak[idx-1] is not None)
        rgtdone = (idx < len(seq)-1 and idxtopeak[idx+1] is not None)
        il = idxtopeak[idx-1] if lftdone else None
        ir = idxtopeak[idx+1] if rgtdone else None

        # New peak born
        if not lftdone and not rgtdone:
            peaks.append(Peak(idx))
            idxtopeak[idx] = len(peaks)-1

        # Directly merge to next peak left
        if lftdone and not rgtdone:
            peaks[il].right += 1
            idxtopeak[idx] = il

        # Directly merge to next peak right
        if not lftdone and rgtdone:
            peaks[ir].left -= 1
            idxtopeak[idx] = ir

        # Merge left and right peaks
        if lftdone and rgtdone:
            # Left was born earlier: merge right to left
            if seq[peaks[il].born] > seq[peaks[ir].born]:
                peaks[ir].died = idx
                peaks[il].right = peaks[ir].right
                idxtopeak[peaks[il].right] = idxtopeak[idx] = il
            else:
                peaks[il].died = idx
                peaks[ir].left = peaks[il].left
                idxtopeak[peaks[ir].left] = idxtopeak[idx] = ir

    # Sort by height
    return sorted(peaks, key=lambda p: p.get_value(values), reverse=True)

def sort_peaks_by_value(peaks, values):
    return sorted(peaks, key=lambda p: p.get_value(values), reverse=True)

def sort_peaks_by_persistence(peaks, seq):
    return sorted(peaks, key=lambda p: p.get_persistence(seq), reverse=True)

# df = pandas.read_excel('sample_0003.xlsx')
cluster = '0034'
Y = misc.imread('data/building_cluster_' + cluster + '__OrthoPAN_oriented.png')
if Y.ndim == 3:
    Y = np.mean(Y[:, :, 0:2], axis=-1)
tmp = np.array(Y.flat)
threshold = 5
a = np.delete(tmp, np.where(tmp <= threshold))
max_val = math.ceil(np.max(a))
stepsize = 1.0
fine_stepsize = 0.01
bins = np.arange(0, max_val+fine_stepsize+1, fine_stepsize)
hist = np.histogram(a, bins=bins)
filter = np.ones([np.round(stepsize/fine_stepsize).astype('int32')])
c = np.convolve(hist[0], filter, 'same')
if True:
    plt.figure()
    # plt.plot(hist[1][:-1], hist[0], 'r-')
    plt.plot(hist[1][:-1], c/len(filter), 'g-')
    plt.title('Histogram')
    #plt.title('Histogram')
    # plt.savefig('data/hist_test.png')
    
hist = (c/len(filter), hist[1])
#Peaks will be sorted by persistence
#print len(hist[0])
peaks = get_persistent_homology(hist[0], hist[1])
#print len(peaks)
died_thresh = np.sum(hist[0]) * 0.05
peak_thresh = 2.0
min_component_size = 100
min_diff = 10.0

significant_peaks = []

for level, peak in enumerate(peaks):
    died = 0
    if peak.died is not None:
        died = hist[0][peak.died]

    #Peaks are sorted from largest height to smallest
    #If This peaks is the smallest, or if the next significant peak is
    # too close in height, don't use it
    #died_thresh ensures that peaks are 'deep' enough, that is they go far down in the histogram
    #peak_thresh ensures that peaks are tall enough (born-died)
    #Also ensure that the mass of the peak is significant using min component size
    if (peak.get_persistence(hist[0]) > peak_thresh) and (died <= died_thresh) and \
            (np.sum(hist[0][peak.left:peak.right+1]) > min_component_size):
        if len(significant_peaks) == 0 or \
            significant_peaks[len(significant_peaks)-1].get_value(hist[1]) -  peak.get_value(hist[1]) > min_diff:
            significant_peaks.append(peak)
        else:
            #Use the more relevant peak
            if significant_peaks[len(significant_peaks)-1].get_persistence(hist[0]) < peak.get_persistence(hist[0]):
                significant_peaks[len(significant_peaks) - 1] = peak

peaks = significant_peaks
print(len(peaks))
# Take top number of peaks by persistence
peaks = sort_peaks_by_persistence(peaks, hist[0])

peaks = peaks[:5]

for i in range(len(peaks)):
    if True:
        print(peaks[i].get_value(hist[1]))
        
# peaks will be sorted by value
peaks = sort_peaks_by_value(peaks, hist[1])
print("--------------------")
for i in range(len(peaks)):
    if True:
        print(peaks[i].get_value(hist[1]))
        plt.axvline(peaks[i].get_value(hist[1]))

plt.savefig('data/building_cluster_' + cluster + '_hist_peaks.png')

'''
b = np.zeros(len(a))
for i in range(len(a)):
    diff = []
    for j in range(len(peaks)):
        diff.append(abs(peaks[j].get_value(hist[1]) - a[i]))
    b[i] = peaks[np.argmin(diff)].get_value(hist[1])

max_val = math.ceil(np.max(b))
bins = np.arange(0, max_val+fine_stepsize+1, fine_stepsize)
hist = np.histogram(b, bins=bins)

if True:
    plt.figure(1)
    plt.plot(hist[1][:-1], hist[0], 'r-')
    plt.title('Histogram')
    plt.savefig('data/hist_' + cluster + '_merge.png')
'''
rows, cols = Y.shape
img = np.zeros((rows, cols))
new_img = np.resize(img, (rows, cols, 3))
colors = np.zeros((len(peaks) + 1, 3))
# the first color is background
colors[0][0] = 0
colors[0][1] = 0
colors[0][2] = 0
COLORS_SET = [(139, 0, 0),
            (255, 0, 0),
            (255, 255, 0),
          (0, 100, 0),
(0, 255, 0),
          (0, 0, 139),
              (0, 0, 255),
              (0, 255, 255)]
COLORS_SET_CHOSEN = [0, 0, 0, 0, 0, 0, 0, 0]
for i in range(len(peaks)):
    chosen_index = random.randint(0, 7)
    while COLORS_SET_CHOSEN[chosen_index] != 0:
        chosen_index = random.randint(0, 7)
    print(chosen_index)
    colors[i + 1] = COLORS_SET[chosen_index]
    COLORS_SET_CHOSEN[chosen_index] = 1
    print(colors[i + 1])
    # colors[i + 1][0] = random.randint(20, 255)
    # colors[i + 1][1] = random.randint(20, 255)
    # colors[i + 1][2] = random.randint(20, 255)
# generate layer images
for i in range(len(peaks)):
    for m in range(rows):
        for n in range(cols):
            if Y[m][n] > threshold:
                diff = []
                for p in range(len(peaks)):
                    diff.append(abs(peaks[p].get_value(hist[1]) - Y[m][n]))
                    new_img[m][n][0] = colors[np.argmin(diff) + 1][0]
                    new_img[m][n][1] = colors[np.argmin(diff) + 1][1]
                    new_img[m][n][2] = colors[np.argmin(diff) + 1][2]
            else:
                new_img[m][n][0] = colors[0][0]
                new_img[m][n][1] = colors[0][1]
                new_img[m][n][2] = colors[0][2]
misc.imsave('data/building_cluster_' + cluster + '__hist_seg.png', new_img.astype(np.uint8))