

from skimage import  feature as ft

import  cv2


import numpy as np

import pickle
from skimage import  feature as ft

def computeHOGs(img_lst, gradient_lst):

    hog = cv2.HOGDescriptor()

    for i in range(len(img_lst)):

        gray = cv2.cvtColor(img_lst[i], cv2.COLOR_BGR2GRAY)

        features = ft.hog(gray,  # input image
                          orientations=9,  # number of bins
                          pixels_per_cell=(4,8),  # pixel per cell
                          cells_per_block=(1,2),)  # cells per blcok

        gradient_lst.append(features)

    print(gradient_lst[0].shape)

f=open('./INRIAPerson/96X160H96/Train/pos.lst','r')

file_names=f.readlines()

file_names=[file_name.strip('\n') for file_name in file_names]

img_list=[]

for i,file_name in enumerate(file_names):

    print(i,'INRIAPerson/'+file_name)

    img=cv2.imread('INRIAPerson/'+file_name)

    img_list.append(img)


gradient_lst=[]

computeHOGs(img_list,gradient_lst)


f=open('x_train_pos.pickle','wb')

pickle.dump(gradient_lst,f)

print('x_train_pos.pickle 已保存 !')

#------------------------------------------



f=open('./INRIAPerson/96X160H96/Train/neg.lst','r')

file_names=f.readlines()

file_names=[file_name.strip('\n') for file_name in file_names]

img_list=[]

for i,file_name in enumerate(file_names):

    print(i,file_name)

    img=cv2.imread('INRIAPerson/'+file_name)

    img_list.append(img)

gradient_lst=[]

computeHOGs(img_list,gradient_lst)

f=open('x_train_neg.pickle','wb')

pickle.dump(gradient_lst,f)

print('x_train_neg.pickle 已保存 !')

#------------------------------------

f=open('./INRIAPerson/96X160H96/Test/pos.lst','r')

file_names=f.readlines()

file_names=[file_name.strip('\n') for file_name in file_names]

img_list=[]

for i,file_name in enumerate(file_names):

    print(i,file_name)

    img=cv2.imread('INRIAPerson/'+file_name)

    img_list.append(img)

gradient_lst=[]

computeHOGs(img_list,gradient_lst)

f=open('x_test_pos.pickle','wb')

pickle.dump(gradient_lst,f)

print('x_test_pos.pickle 已保存 !')

#----------------------------------


f=open('./INRIAPerson/96X160H96/Test/neg.lst','r')

file_names=f.readlines()

file_names=[file_name.strip('\n') for file_name in file_names]

img_list=[]

for i,file_name in enumerate(file_names):

    print(i,file_name)

    img=cv2.imread('INRIAPerson/'+file_name)

    img_list.append(img)

gradient_lst=[]

computeHOGs(img_list,gradient_lst)

f=open('x_test_neg.pickle','wb')

pickle.dump(gradient_lst,f)

print('x_test_neg.pickle 已保存 !')


cv2.lbp



