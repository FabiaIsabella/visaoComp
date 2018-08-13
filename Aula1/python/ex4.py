import cv2
import os
import glob
pasta = 'imagens' 

data_path = os.path.join(pasta,'*g')

imagens = glob.glob(data_path)

path = 'ex4'

for im in imagens:
	img = cv2.imread(im)
	cv2.imshow(im,img)
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


	img2 = img
	j = str(im)+ '*'
	cv2.imshow(j,img2)
	cv2.imwrite(os.path.join(path, str(j)+'.png'),img2)


cv2.waitKey(0)
cv2.destroyAllWindows()
