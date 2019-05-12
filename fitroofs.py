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

def main(input_filename, output_filename, num_iterations):
	# load image
	Y = misc.imread(input_filename) / 255

	# convert to grayscale
	if Y.ndim == 3:
		Y = np.mean(Y[:,:,0:2], axis=-1)

	# resize to 128 x 128
	misc.imresize(Y, (128, 128))

	#norm_Y = np.sqrt(np.inner(Y.flat, Y.flat))
	norm_Y = np.sum(Y)

	D = []
	FD = []

	# define rectangle generators
	max_aspect = 5
	lengths = np.arange(2, 105, 2)
	for width in lengths:
		for height in lengths:
			if width/height <= max_aspect and height/width <= max_aspect:
				g = np.zeros((128, 128), np.float)
				g = cv2.rectangle(g, (64 - int(width/2), 64 - int(height/2)), (64 + int(width/2), 64 + int(height/2)), (1.0), -1)
				g /= np.sqrt(np.sum(g * g))
				Fg = np.fft.fftn(g)
				Fg = np.conj(Fg)
				D.append(g)
				FD.append(Fg)

	FD = np.array(FD)
	
	# solve by matching pursuit
	rtol = .1
	residual = Y
	indices_on = []
	A = None
	coeff = None
	for iter in range(num_iterations):
		residual[residual <= 0] = -10
		
		# calculate coefficient
		FY = np.fft.fftn(residual)
		C = np.array([np.fft.ifftn(Fg * FY) for Fg in FD])
		
		# don't use the generator that is already used.
		C.flat[indices_on] = 0
		
		# select the generator
		next_index = np.argmax(C.flat)
		if C.flat[next_index] == 0: break
		indices_on.append(next_index)
		
		i, ty, tx = np.unravel_index(next_index, (len(D), 128, 128), order='C')

		# update matrix A
		column = np.roll(np.roll(D[i], ty, axis=0), tx, axis=1)
		column = np.reshape(column, (np.prod(column.shape), 1))
		if iter == 0:
			A = column
		else:
			A = np.hstack([A, column])
		
		# calculate coefficient by solving Ax=Y
		coeff = np.linalg.solve(A.T.dot(A), A.T.dot(Y.flat))
		
		# calculate the current image
		Y2 = np.reshape(A.dot(coeff), Y.shape)
		
		# don't allow each pixel having a negative value
		Y2[Y2 < 0] = 0
		
		# don't allow each pixel having a value greater than the input
		#Y2 = np.minimum(Y2, Y)
		Y2[Y2 > 1] = 1
		
		misc.imsave('result_' + str(iter) + '.png', (Y2 * 255).astype(np.uint8))
		
		# update residual
		residual = Y - Y2
		residual[residual < 0] = 0
		#misc.imsave('residual_' + str(iter) + '.png', (residual * 255).astype(np.uint8))
		
		# check stoppping criteria
		#err = np.sqrt(np.inner(residual.flat, residual.flat))
		err = np.sum(residual)
		
		print('iter:', iter, 'index:', (i, tx, ty), 'err:', err/norm_Y, sep='\t')
		if err < rtol * norm_Y: break

	# generate result image
	result = Y2
	
	# save the result image
	misc.imsave(output_filename, (result * 255).astype(np.uint8))
	
	cv2.imshow('Result', (result * 255).astype(np.uint8))
	cv2.waitKey(0)

if __name__ == "__main__":
	parser = argparse.ArgumentParser()
	parser.add_argument("input_filename", help="path to the input file")
	parser.add_argument("output_filename", help="path to the output file")
	parser.add_argument('num_iterations', type=int, help='#iterations for the orthogonal matching pursuit')
	args = parser.parse_args()

	main(args.input_filename, args.output_filename, args.num_iterations)
