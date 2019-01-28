import os
import cv2
import numpy as np
import pandas as pd
import pickle
import keras
from sklearn.neighbors import KNeighborsClassifier

from sklearn.cluster import k_means
import matplotlib.pyplot as plt
from keras.layers import Dense
from keras.optimizers import SGD
from keras import Sequential
from keras.losses import categorical_crossentropy
from keras.layers import Conv2D
from keras.layers import Flatten
from keras.layers import Activation
from sklearn.preprocessing import OneHotEncoder
from sklearn.preprocessing import StandardScaler


def get_path_label(op='train'):
    paths = []

    labels = []

    if op == 'train':

        base_path = 'tf_car_license_dataset/train_images/training-set/'

    elif op == 'valid':

        base_path = 'tf_car_license_dataset/train_images/validation-set/'

    for i in range(10):

        dirs = os.listdir(base_path + str(i))

        label_num = len(dirs)

        labels.extend(label_num * [i])

        for dir_ in dirs:
            paths.append(base_path + str(i) + '/' + dir_)

    return labels, paths



#防止opencv在读取中文路径出现错误问题的函数
def cv_imread(file_path):
    cv_img=cv2.imdecode(np.fromfile(file_path,dtype=np.uint8),-1)
    return cv_img


# 利用自己的方法构建1*1的HOG特征训练集合

def calc_HOG(label_path_df, mr=3, mc=3, n=9):

    '''
        n代表特征数

    '''

    # 整套数据的直方图集合
    x_train = np.zeros((len(label_path_df), n * mr * mc))

    # 对于每个图像
    for l, path in enumerate(label_path_df.paths):

        img = cv_imread(path)

        # 共有mr*mc个cell,每个cell有n个feature
        hog_feature = np.zeros((mr * mc, n))

        # 每个cell行像素数量和列像素数量
        row_step = int(img.shape[0] / mr)
        col_step = int(img.shape[1] / mc)

        k = 0

        for i in range(mr):

            for j in range(mc):

                part_img = img[i * row_step:(i + 1) * row_step, j * col_step:(j + 1) * col_step]

                gx = cv2.Sobel(part_img, cv2.CV_32F, 1, 0)

                gy = cv2.Sobel(part_img, cv2.CV_32F, 0, 1)

                step = 2 * np.pi / n

                mag, angle = cv2.cartToPolar(gx, gy)

                for t in range(n):
                    angle_index = (angle > step * t) & (angle < step * (t + 1))

                    hog_feature[k, t] = mag[angle_index].sum()

                k += 1

        x_train[l] = hog_feature.flatten()

    # 更改 z-统计量为压缩到(0,1]中
    # std=StandardScaler()

    # x_train=std.fit_transform(x_train)

    x_train = (x_train - x_train.min()) / (x_train.max() - x_train.min())

    return x_train

#构建训练集
label_path_df=pd.DataFrame()
label_path=get_path_label('train')
label_path_df['labels']=label_path[0]
label_path_df['paths']=label_path[1]
x_train=calc_HOG(label_path_df,)
#构建测试集
valid_label_path_df=pd.DataFrame()
label_path=get_path_label('valid')
valid_label_path_df['labels']=label_path[0]
valid_label_path_df['paths']=label_path[1]
#构建验证集合
x_valid=calc_HOG(valid_label_path_df,)

#构建BP神经网络
y_train=np.array(label_path_df['labels'].values)
y_valid=np.array(valid_label_path_df['labels'].values)

one=OneHotEncoder()
y_train=one.fit_transform(np.matrix(y_train).T).toarray()
y_valid=one.fit_transform(np.matrix(y_valid).T).toarray()

model=Sequential()
model.add(Dense(units=32*2, activation='sigmoid',input_shape=(81,)))
model.add(Dense(units=32*2, activation='sigmoid'))
model.add(Dense(units=10, activation='softmax'))
model.compile(optimizer=SGD(lr=1),loss=categorical_crossentropy,metrics=['accuracy'])
model.fit(x_train,y_train,batch_size=64,epochs=20)
print(model.evaluate(x_valid,y_valid,batch_size=64))