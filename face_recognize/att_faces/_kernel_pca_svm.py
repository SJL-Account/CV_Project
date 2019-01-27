"""
@Time:2019/1/1313:13
@Author:SJL
@File:_pca_svm.py
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
from sklearn.decomposition import  PCA
from sklearn.decomposition import  KernelPCA
from sklearn.svm import  SVC
from sklearn.grid_search import  GridSearchCV
from sklearn.metrics import classification_report
from sklearn.metrics import adjusted_mutual_info_score
from sklearn.metrics import confusion_matrix

from sklearn.svm import  LinearSVC
# --------------------------文档开始-----------------------------
# define metadata
h = 112
w = 92
n_components = 200

# -----------------------------定义函数---------------------------

def plot_gallary(imgs,titles,h,w,n_row,n_col):

    plt.figure(figsize=(3*3,4*4))

    plt.subplots_adjust(bottom=0, left=.01, right=.99, top=.90, hspace=.35)

    for i in range(n_row*n_col):

        plt.subplot(n_row,n_col,i+1)

        plt.imshow(imgs[i].reshape((h,w)),cmap=plt.cm.gray)

        plt.title(titles[i],size=12)

# read data from imgs index
imgs_list_df = pd.read_csv('imgs_list_df.csv')

# create X,y
X_imgs = np.zeros((len(imgs_list_df),h,w))
X_samples=np.zeros((len(imgs_list_df),h*w))
# read img and transform X

for i,path_ in enumerate(imgs_list_df['path']):

    img=cv2.imread(path_)

    gray=cv2.cvtColor(img,cv2.COLOR_RGB2GRAY)

    X_imgs[i]=gray

    X_samples[i]=gray.flatten()

y = imgs_list_df['label']
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


t1=time()
# PCA transform
pca=KernelPCA(n_components=n_components,kernel='sigmoid')
pca.fit(x_train)

x_train_pca=pca.transform(x_train)
x_test_pca=pca.transform(x_test)
print('pca done time is ',time()-t1,'s')

print('--------------------------------')

print('pca x_train,x_test done')
print('x_train_pca shape:',x_train_pca.shape)
print('x_test_pca shape:',x_test_pca.shape)
print('--------------------------------')

t2=time()
# create SVM model and train
print('Fitting ans select best model.....')
param_grid = {'C': [0.1,1,10,1e2,1e3, 5e3]}
#clf = GridSearchCV(LinearSVC(),param_grid, cv=5)
clf=SVC(C=1,gamma=0.0001)
clf = clf.fit(x_train_pca, y_train)
#clf=clf.best_estimator_
print('best clf :',clf)
print('svm train done time is ',time()-t2,'s')

t3=time()
# predict and result analysis
y_pred=clf.predict(x_test_pca)
print('svm predict train done time is ',time()-t3,'s')

print('metircs result is :')
print(classification_report(y_test,y_pred))
print(confusion_matrix(y_test,y_pred))
print(adjusted_mutual_info_score(y_test,y_pred))

# --------------------------文档结束-----------------------------

print('程序已结束，运行时间为：', time() - t0, 's')