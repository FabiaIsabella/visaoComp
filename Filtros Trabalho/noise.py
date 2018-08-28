import cv2
import numpy as np


#def salt_n_pepper(img, pad = 101, show = 1):
# Convert img1 to 0 to 1 float to avoid wrapping that occurs with uint8

img = cv2.imread('lena.jpg',0)

cv2.imshow('image',img)

#img = to_std_float(img)
 
# Generate noise to be added to the image. We are interested in occurrences of high
# and low bounds of pad. Increased pad size lowers occurence of high and low bounds.
# These high and low bounds are converted to salt and pepper noise later in the
# function. randint is inclusive of low bound and exclusive of high bound.
noise = np.random.randint(pad, size = (img.shape[0], img.shape[1], 1))
 
# Convert high and low bounds of pad in noise to salt and pepper noise then add it to
# our image. 1 is subtracted from pad to match bounds behaviour of np.random.randint.
img = np.where(noise == 0, 0, img)
img = np.where(noise == (pad-1), 1, img)
 
# Properly handles the conversion from float16 back to uint8
img = to_std_uint8(img)
 
 
cv2.imshow('image2',img)

cv2.waitKey(0)
cv2.destroyAllWindows()


