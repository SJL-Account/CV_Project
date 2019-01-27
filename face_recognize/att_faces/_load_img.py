"""
@Time:2019/1/16 22:03
@Author:SJL
@File:_load_img.py
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
# define metadata
h = 112
w = 92
n_components = 200
# --------------------------功能函数定义-------------------------

def load_imgs(is_gray=True):
    # read data from imgs index
    imgs_list_df = pd.read_csv('imgs_list_df.csv')
    # create X,y
    if is_gray:
        X_imgs = np.zeros((len(imgs_list_df), h, w))
    else:
        X_imgs = np.zeros((len(imgs_list_df), h, w,3))

    X_samples = np.zeros((len(imgs_list_df), h * w))
    # read img and transform X
    for i, path_ in enumerate(imgs_list_df['path']):
        img = cv2.imread(path_)
        if is_gray:
            gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
            X_imgs[i] = gray
            X_samples[i] = gray.flatten()
        else:
            X_imgs[i] = img

    y = imgs_list_df['label']

    return X_imgs, X_samples, y

# --------------------------文档结束-----------------------------
print('程序已结束，运行时间为：', time() - t0, 's')