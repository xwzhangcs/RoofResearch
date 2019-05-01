#######################################################################
# Generate HTML file that shows the input and output images to compare.

from os.path import isfile, join
from PIL import Image
import os
import argparse
import numpy as np
import json
import subprocess
import sys
import shutil
import glob
import pandas as pd
from skimage import data, img_as_float
from skimage.measure import compare_ssim as ssim
from skimage import io


def main(aoi_dir, html_file_name):

	# Create the html file
	html_file = "<html>\n"
	html_file += "  <head>\n"
	html_file += "    <style>\n"
	html_file += "    table {\n"
	html_file += "      color: #333;\n"
	html_file += "      font-family: Helvetica, Arial, sans-serif;\n"
	html_file += "      border-collapse: collapse;\n"
	html_file += "      border-spacing: 0;\n"
	html_file += "    }\n"
	html_file += "    \n"
	html_file += "    td, th {\n"
	html_file += "      border: 1px solid #CCC;\n"
	html_file += "      padding: 5px;\n"
	html_file += "    }\n"
	html_file += "    \n"
	html_file += "    th {\n"
	html_file += "      background: #F3F3F3;\n"
	html_file += "      font-weight: bold;\n"
	html_file += "    }\n"
	html_file += "    \n"
	html_file += "    td {\n"
	html_file += "      text-align: center;\n"
	html_file += "    }\n"
	html_file += "    \n"
	html_file += "    tr:hover {\n"
	html_file += "      background-color: #eef;\n"
	html_file += "      border: 3px solid #00f;\n"
	html_file += "      font-weight: bold;\n"
	html_file += "    }\n"
	html_file += "    </style>\n"
	html_file += "  </head>\n"
	html_file += "<body>\n"
	html_file += "  <table>\n"
	html_file += "    <tr>\n"
	html_file += "      <th>Cluster.</th>\n"
	html_file += "      <th>Bld mask.</th>\n"
	html_file += "      <th>Pan.</th>\n"
	html_file += "      <th>RGB.</th>\n"
	html_file += "      <th>Skeleton.</th>\n"
	html_file += "      <th>Skeleton RGB.</th>\n"
	html_file += "      <th>Entropy.</th>\n"

	clusters = sorted(os.listdir(aoi_dir))
	for i in range(len(clusters)):
		cluster = aoi_dir + '/' + clusters[i]
		bld_mask = cluster + '/' + 'building_cluster_' + clusters[i] + '__segment_mask.png'
		pan_img = cluster + '/' + 'building_cluster_' + clusters[i] + '__OrthoPAN.png'
		rgb_img = cluster + '/' + 'building_cluster_' + clusters[i] + '__OrthoRGB.png'
		skeleton_img = cluster + '/' + 'building_cluster_' + clusters[i] + '__Skeleton_mask.png'
		skeleton_rgb_img = cluster + '/' + 'building_cluster_' + clusters[i] + '__Skeleton.png'
		entropy_img = cluster + '/' + 'building_cluster_' + clusters[i] + '__entropy.png'
		html_file += "    <tr>\n"
		html_file += "      <td>" + cluster + "</td>\n"
		html_file += "      <td><a href=\"" + bld_mask + "\"><img src=\"" + bld_mask + "\"/></a></td>\n"
		html_file += "      <td><a href=\"" + pan_img + "\"><img src=\"" + pan_img + "\"/></a></td>\n"
		html_file += "      <td><a href=\"" + rgb_img + "\"><img src=\"" + rgb_img + "\"/></a></td>\n"
		html_file += "      <td><a href=\"" + skeleton_img + "\"><img src=\"" + skeleton_img + "\"/></a></td>\n"
		html_file += "      <td><a href=\"" + skeleton_rgb_img + "\"><img src=\"" + skeleton_rgb_img + "\"/></a></td>\n"
		html_file += "      <td><a href=\"" + entropy_img + "\"><img src=\"" + entropy_img + "\"/></a></td>\n"
		html_file += "    </tr>\n"

	html_file += "  </table>\n"
	html_file += "</body>\n"
	html_file += "</html>\n"
		
	# Save the html file
	with open(html_file_name, "w") as output_file:
		output_file.write(html_file)


if __name__ == "__main__":
	parser = argparse.ArgumentParser()
	parser.add_argument("aoi_dir", help="path to input image folder (e.g., input_data)")
	parser.add_argument("html_file_name", help="path to output html filename")
	args = parser.parse_args()

	main(args.aoi_dir, args.html_file_name)
