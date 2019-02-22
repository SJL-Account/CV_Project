from skimage.feature import local_binary_pattern
import cv2
import matplotlib.pyplot as plt

img=cv2.imread('./INRIAPerson/96X160H96/Train/pos/crop001001b.jpg')

gray=cv2.cvtColor(img,cv2.COLOR_RGB2GRAY)

lbp_img=local_binary_pattern(gray,P=8,R=2)

plt.imshow(lbp_img,cmap=plt.cm.gray)

plt.show()

