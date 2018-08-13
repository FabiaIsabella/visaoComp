import cv2
import numpy as np

img = cv2.imread('/home/fabia/Imagens/lena.png')

cv2.imshow('image',img)

#altura e largura
height, width = img.shape[:2]

for i in range(0,width-1):
	for j in range(0,height-1):
		pixel = img[i,j]
		r = pixel[0] + 100
		g = pixel[1] + 100
		b = pixel[2] + 100

		if r > 255:
			r = 255
		
		if g > 255:
			g = 255

		if b > 255:
			b = 255
		
		img[i,j] = (r,g,b)

cv2.imwrite('ex2.png',img)

img2 = cv2.imread('ex2.png')

cv2.imshow('image2',img2)

cv2.waitKey(0)
cv2.destroyAllWindows()



