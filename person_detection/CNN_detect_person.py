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


f=open('./INRIAPerson/96X160H96/Train/pos.lst','r')

file_names=f.readlines()

file_names=[file_name.strip('\n') for file_name in file_names]

x_train_pos=np.zeros((len(file_names),160,96,3))

for i,file_name in enumerate(file_names):

    print(i,'INRIAPerson/'+file_name)

    img=cv2.imread('INRIAPerson/'+file_name)

    x_train_pos[i]=img



f=open('./INRIAPerson/96X160H96/Train/neg.lst','r')

file_names=f.readlines()

file_names=[file_name.strip('\n') for file_name in file_names]

x_train_neg=np.zeros((len(file_names),160,96,3))

for i,file_name in enumerate(file_names):

    print(i,'INRIAPerson/'+file_name)

    img=cv2.imread('INRIAPerson/'+file_name)

    x_train_neg[i]=img



f=open('./INRIAPerson/96X160H96/Test/pos.lst','r')

file_names=f.readlines()

file_names=[file_name.strip('\n') for file_name in file_names]

x_test_pos=np.zeros((len(file_names),160,96,3))

for i,file_name in enumerate(file_names):

    print(i,'INRIAPerson/'+file_name)

    img=cv2.imread('INRIAPerson/'+file_name)

    x_test_pos[i]=img



f=open('./INRIAPerson/96X160H96/Test/neg.lst','r')

file_names=f.readlines()

file_names=[file_name.strip('\n') for file_name in file_names]

x_test_neg=np.zeros((len(file_names),160,96,3))

for i,file_name in enumerate(file_names):

    print(i,'INRIAPerson/'+file_name)

    img=cv2.imread('INRIAPerson/'+file_name)

    x_test_neg[i]=img




print('加载VGG模型....(没有全连接层，imagenet参数)')
path='vgg16_weights_tf_dim_ordering_tf_kernels_notop.h5'
vgg16 = VGG16(weights='imagenet', include_top=False,input_shape=(160,96,3))
print ('model loaded.')

top_model=Sequential()
top_model.add(Flatten(input_shape=vgg16.output_shape[1:]))
top_model.add(Dense(256, activation='relu'))
top_model.add(Dropout(0.5))
top_model.add(Dense(2, activation='sigmoid'))

print('连接两个模型...')
model=Model(inputs=vgg16.input,outputs=top_model(vgg16.output))

print(model.summary())

print('冻结参数...')
for layer in model.layers[:15]:
    layer.trainable = False

print('编译...')
model.compile(loss='binary_crossentropy',
              optimizer=optimizers.SGD(lr=1e-4, momentum=0.9),
              metrics=['accuracy'])

print('准备数据...')

x_train=np.r_[x_train_pos,x_train_neg]
pos_labels=len(x_train_pos)*[1]
neg_labels=len(x_train_neg)*[0]
pos_labels.extend(neg_labels)
one=OneHotEncoder()
y_train=one.fit_transform(np.matrix(pos_labels).T).toarray()

x_test=np.r_[x_test_pos,x_test_neg]
pos_labels=len(x_test_pos)*[1]
neg_labels=len(x_test_neg)*[0]
pos_labels.extend(neg_labels)
one=OneHotEncoder()
y_test=one.fit_transform(np.matrix(pos_labels).T).toarray()

std=StandardScaler()
for i in range(len(x_test)):
    for j in range(160):
        x_test[i,j,:,:]=std.fit_transform(x_test[i,j,:,:])

for i in range(len(x_train)):
    for j in range(160):
        x_train[i,j,:,:]=std.fit_transform(x_train[i,j,:,:])

print(x_train.shape)
print(y_train.shape)
print(x_test.shape)
print(y_test.shape)

print('开始训练....')

batch_size=32

epochs=3

result=model.fit(x_train,y_train,batch_size=batch_size,epochs=epochs,validation_data=(x_test,y_test))

model.save('model')
