
import os
import shutil
import cv2
import pickle
import numpy as np


# #制造负类
#
# f=open('INRIAPerson/Train/neg.lst','r')
#
# file_names=f.readlines()
#
# file_names=[file_name.strip('\n') for file_name in file_names]
#
# img_list=[]
#
# target_dir='INRIAPerson/96X160H96/Train/neg/'
#
# for i,file_name in enumerate(file_names):
#
#     print(i,file_name)
#
#     img=cv2.imread('INRIAPerson/'+file_name)
#
#     if (img.shape[0]>160)&(img.shape[1]>96):
#         img=img[:160,:96,:]
#
#         path=target_dir+os.path.split(file_name)[1]
#
#         print('正在保存',path)
#
#         cv2.imwrite(path,img)
#
# #制造负类
#
# f = open('INRIAPerson/Test/neg.lst', 'r')
#
# file_names = f.readlines()
#
# file_names = [file_name.strip('\n') for file_name in file_names]
#
# img_list = []
#
# target_dir = 'INRIAPerson/96X160H96/Test/neg/'
#
# for i, file_name in enumerate(file_names):
#
#     print(i, file_name)
#
#     img = cv2.imread('INRIAPerson/' + file_name)
#
#     if (img.shape[0] > 160) & (img.shape[1] > 96):
#         img = img[:160, :96, :]
#
#         path = target_dir + os.path.split(file_name)[1]
#
#         print('正在保存', path)
#
#         cv2.imwrite(path, img)
#


#制造正类
# base_dir='INRIAPerson/96X160H96/'
# image_dirs=os.listdir(base_dir+'Train/pos/')
# class_dict={}
# for j,dir_ in enumerate(image_dirs):
#
#     if j%5==0:
#         print(base_dir+'Train/pos/'+dir_,base_dir+'Test/pos/'+dir_)
#         shutil.move(base_dir+'Train/pos/'+dir_,base_dir+'Test/pos/'+dir_)
#
