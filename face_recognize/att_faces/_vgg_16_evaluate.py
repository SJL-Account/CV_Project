"""
@Time:2019/1/17 16:27
@Author:SJL
@File:_vgg_16_evaluate.py
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
from keras.models import  load_model
import _load_img
from sklearn.preprocessing import OneHotEncoder
# --------------------------文档开始-----------------------------

# --------------------------METADATA-----------------------------

# --------------------------功能函数定义-------------------------

#---------------------------对象导入-----------------------------
one=OneHotEncoder()

t1 = time()
X_imgs, X_samples, y=_load_img.load_imgs(False)
x_test_index=[i for i,_ in enumerate(X_imgs) if i%10>=8]
x_test=X_imgs[x_test_index]
y_test=y[x_test_index]
y_test=one.fit_transform(np.matrix(y_test).T).toarray()
x_test=x_test.reshape(-1,112,92,3)
vgg16=load_model('vgg16.model')
print('data and model load done time is ', time() - t1, 's')

t2 = time()
evaluate_result=vgg16.evaluate(x_test,y_test)
print('loss:',evaluate_result[0],'  accuracy:',evaluate_result[1])

print('vgg16 predict done time is ', time() - t2, 's')
t3 = time()

print('done time is ', time() - t3, 's')
# --------------------------文档结束-----------------------------
print('程序已结束，运行时间为：', time() - t0, 's')