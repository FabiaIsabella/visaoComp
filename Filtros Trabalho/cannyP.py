import numpy as np
import cv2
 

img = cv2.imread('lena.jpg',0)

#cv2.imshow('image',img)

#altura e largura
height, width = img.shape[:2]

img2 = cv2.GaussianBlur(img,(7,7),0)

cv2.imshow('gaussian',img2)

sobelx = cv2.Sobel(img,cv2.CV_64F,1,0,ksize=5)
sobely = cv2.Sobel(img,cv2.CV_64F,0,1,ksize=5)

cv2.imshow('sobelx',sobelx)
cv2.imshow('sobely',sobely)

cv2.waitKey(0)
cv2.destroyAllWindows()