"""
@Time:2019/1/1316:22
@Author:SJL
@File:_vgg16.py
@Software:PyCharm Community Edition
"""
print(__doc__)
from time import time

t0 = time()  # 程序开始计时
# --------------------------组件导入-----------------------------
import keras
import cv2
import tensorflow as tf
import pickle
import pandas as pd
import numpy as np
from keras import Sequential
from keras.layers import Dense
from keras.layers import Flatten
from keras.layers import Dropout
from keras.models import Model
from keras import  optimizers
from keras.applications.vgg16 import VGG16
from sklearn.preprocessing import OneHotEncoder
from sklearn.preprocessing import StandardScaler
from sklearn.datasets import fetch_lfw_people
from sklearn.cross_validation import  train_test_split
# --------------------------文档开始-----------------------------

# --------------------------METADATA-----------------------------

h=112
w=92
class_number=40
path='vgg16_weights_tf_dim_ordering_tf_kernels_notop.h5'

# --------------------------功能函数定义-------------------------

# read data from imgs index
imgs_list_df = pd.read_csv('imgs_list_df.csv')

# create X,y
X_imgs = np.zeros((len(imgs_list_df),h,w,3))
# read img and transform X

for i,path_ in enumerate(imgs_list_df['path']):

    img=cv2.imread(path_)

    X_imgs[i]=img

t1 = time()
print('加载VGG模型....(没有全连接层，imagenet参数)')

vgg16 = VGG16(weights='imagenet', include_top=False,input_shape=(h,w,3))
print ('model loaded.')
top_model=Sequential()
top_model.add(Flatten(input_shape=vgg16.output_shape[1:]))
top_model.add(Dense(class_number*4, activation='relu'))
top_model.add(Dropout(0.5))
top_model.add(Dense(class_number, activation='sigmoid'))

print('连接两个模型...')
model=Model(inputs=vgg16.input,outputs=top_model(vgg16.output))

print(model.summary())

print('冻结参数...')
for layer in model.layers[:15]:
    layer.trainable = False

print('编译...')
model.compile(loss='binary_crossentropy',
              optimizer=optimizers.SGD(lr=1e-2, momentum=0.9),
              metrics=['accuracy'])

print('vgg16 create has done ,time is ', time() - t1, 's')


t2 = time()
x_train_index=[i for i,_ in enumerate(X_imgs) if i%10<8]
x_train=X_imgs[x_train_index]
x_test_index=[i for i,_ in enumerate(X_imgs) if i%10>=8]
x_test=X_imgs[x_test_index]
y_train=imgs_list_df.ix[x_train_index,'label']
y_test=imgs_list_df.ix[x_test_index,'label']

one=OneHotEncoder()
std=StandardScaler()
for i in range(len(x_train)):
    for j in range(112):
        x_train[i,j,:,:]=std.fit_transform(x_train[i,j,:,:])
y_train=one.fit_transform(np.matrix(y_train).T).toarray()

for i in range(len(x_test)):
    for j in range(112):
        x_test[i,j,:,:]=std.fit_transform(x_test[i,j,:,:])
y_test=one.fit_transform(np.matrix(y_test).T).toarray()

print(x_train.shape)
print(y_train.shape)
print('开始训练....')
batch_size=32
epochs=10
result=model.fit(x_train,y_train,batch_size=batch_size,epochs=epochs,validation_data=(x_test,y_test))
print('train has done time is ', time() - t2, 's')

t3 = time()
model.save('model')
print('model saved done time is ', time() - t3, 's')

# --------------------------文档结束-----------------------------
print('程序已结束，运行时间为：', time() - t0, 's')