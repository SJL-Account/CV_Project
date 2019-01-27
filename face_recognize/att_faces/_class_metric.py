"""
@Time:2019/1/16 23:58
@Author:SJL
@File:_class_metric.py
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
from sklearn.metrics import classification_report
from sklearn.metrics import adjusted_mutual_info_score
from sklearn.metrics import confusion_matrix

# --------------------------文档开始-----------------------------

# --------------------------METADATA-----------------------------

# --------------------------功能函数定义-------------------------

def metric(y_true, y_pred,method):
    print('metircs result is :')
    print(classification_report(y_true, y_pred))
    print('MIE:',adjusted_mutual_info_score(y_true, y_pred))
    pd.DataFrame(confusion_matrix(y_true=y_true,y_pred=y_pred)).to_csv(method+'_confusion_mat.csv')


# --------------------------文档结束-----------------------------
print('程序已结束，运行时间为：', time() - t0, 's')