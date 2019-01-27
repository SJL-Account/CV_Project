"""
@Time:2019/1/1315:03
@Author:SJL
@File:_lda_svm.py
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
from sklearn.cross_validation import  train_test_split
from sklearn.discriminant_analysis import  LinearDiscriminantAnalysis
from sklearn.svm import  SVC
from sklearn.grid_search import  GridSearchCV
from sklearn.metrics import classification_report
from sklearn.svm import  LinearSVC
import _load_img
import _class_metric
# --------------------------文档开始-----------------------------

# --------------------------METADATA-----------------------------
# define metadata
h = 112
w = 92
n_components = 200

# --------------------------功能函数定义-------------------------
def plot_gallary(imgs,titles,h,w,n_row,n_col):

    plt.figure(figsize=(3*3,4*4))

    plt.subplots_adjust(bottom=0, left=.01, right=.99, top=.90, hspace=.35)

    for i in range(n_row*n_col):

        plt.subplot(n_row,n_col,i+1)

        plt.imshow(imgs[i].reshape((h,w)),cmap=plt.cm.gray)

        plt.title(titles[i],size=12)

##################################################################

X_imgs, X_samples, y=_load_img.load_imgs()
print('create X and y done')
print('--------------------------------')
print('X_img shape:',X_imgs.shape)
print('X_samples shape:',X_samples.shape)

# train and test split
x_train,x_test,y_train,y_test=train_test_split(X_samples,y,test_size=0.25,random_state=42)

print('create x_train,x_test and y done')
print('--------------------------------')
print('x_train shape:',x_train.shape)
print('x_test shape:',x_test.shape)

t1 = time()

# LDA transform
lda=LinearDiscriminantAnalysis(n_components=n_components,solver='svd')
lda.fit(x_train,y_train)
x_train_lda=lda.transform(x_train)
x_test_lda=lda.transform(x_test)

print('lda done time is ', time() - t1, 's')
print('--------------------------------')
print('lda x_train,x_test done')
print('x_train_lda shape:',x_train_lda.shape)
print('x_test_ldashape:',x_test_lda.shape)
print('--------------------------------')


t2 = time()
# create SVM model and train
print('Fitting ans select best model.....')
param_grid = {'C': [0.1,1,10,1e2,1e3, 5e3]}
clf=LinearSVC(C=5000)
clf = clf.fit(x_train_lda, y_train)
print('best clf :',clf)
print('done time is ', time() - t2, 's')


t3 = time()
# predict and result analysis
y_pred=clf.predict(x_test_lda)
_class_metric.metric(y_test,y_pred,'lda_svm')

# false_indexs = (y_test.values != y_pred)
#
#
#
# for falas_index in false_indexs:
#     print('y_true:', y_test.values[falas_index])
#     print('y_pred:', y_pred[falas_index])


print('svm predict train done time is ',time()-t3,'s')


# --------------------------文档结束-----------------------------
print('程序已结束，运行时间为：', time() - t0, 's')