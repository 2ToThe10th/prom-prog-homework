import os
import sys
import cv2 as cv

if len(sys.argv) < 4:
    print("Don't enough arguments")
    exit(1)

input_file_name = sys.argv[1]
map_file_name = sys.argv[2]
output_file_name = sys.argv[3]

with open(input_file_name, mode='r') as fin:
    template_lines = fin.read()

if os.path.exists(output_file_name):
    os.remove(output_file_name)

img = cv.imread(map_file_name)

if img is None:
    sys.exit("Could not read the image.")

rows, cols, _ = img.shape

red_array = []
green_array = []
blue_array = []

for j in range(cols):
    red_array.append(img[2, j][0])
    green_array.append(img[1, j][1])
    blue_array.append(img[0, j][2])


def prepare_array(array):
    stringify = str(array)
    return "{" + stringify[1:-1] + "}"


with open(output_file_name, mode='w+') as fout:
    fout.write(template_lines.format(red_array=prepare_array(red_array),
                                     green_array=prepare_array(green_array),
                                     blue_array=prepare_array(blue_array)))
