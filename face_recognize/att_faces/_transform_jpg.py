"""
@Time:2019/1/16 21:51
@Author:SJL
@File:_transform_jpg.py
@Software:PyCharm Community Edition
"""
print(__doc__)
from time import time

t0 = time()  # 程序开始计时
# --------------------------组件导入-----------------------------
import sklearn
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import cv2
# --------------------------文档开始-----------------------------

# --------------------------METADATA-----------------------------
h = 112
w = 92
# --------------------------功能函数定义-------------------------
#----------------------------------------------------------------
t1 = time()

# read data from imgs index
imgs_list_df = pd.read_csv('imgs_list_df.csv')



for i,path_ in enumerate(imgs_list_df['path']):

    img=cv2.imread(path_)

    gray=cv2.cvtColor(img,cv2.COLOR_RGB2GRAY)

    cv2.imwrite('att_faces_jpg/'+str(i)+'.jpg',gray)



print('done time is ', time() - t1, 's')

#----------------------------------------------------------------
t2 = time()

print('done time is ', time() - t2, 's')
#----------------------------------------------------------------
#----------------------------------------------------------------
t3 = time()

print('done time is ', time() - t3, 's')
#----------------------------------------------------------------
# --------------------------文档结束-----------------------------
print('程序已结束，运行时间为：', time() - t0, 's')