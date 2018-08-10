import cv2
import numpy as np

img = cv2.imread('/home/fabia/Imagens/lena.png',0)

cv2.imshow('image',img)

#altura e largura
height, width = img.shape[:2]

for i in range(0,width-1):
	for j in range(0,height-1):
		#print img[i,j]
		pixel = img[i,j]
		pixel = pixel + 100
		if pixel > 255:
			pixel = 255

		print pixel

		img[i,j] = pixel  


cv2.imwrite('ex1.png',img)


img2 = cv2.imread('ex1.png')

cv2.imshow('image2',img2)

cv2.waitKey(0)
cv2.destroyAllWindows()




