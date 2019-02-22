from sklearn.svm import  SVC
from sklearn.ensemble import  GradientBoostingClassifier
import pickle
import numpy as np
import time

def load_features(file_name,is_pos=True):

    '''
    加载HOG特征
    :param file_name:特征的文件名
    :param is_pos:是否为正类
    :return:
    '''

    f=open(file_name,'rb')

    #读取已经保存的特征
    datas=pickle.load(f)

    #特征维度
    feature_dim=len(datas[0])

    array_data=np.zeros((len(datas),feature_dim))

    for i,data in enumerate(datas):

        array_data[i]=data.flatten()

    if is_pos:

        labels=[1]*len(datas)

    else:

        labels = [0] * len(datas)

    return array_data,np.array(labels)

x_train_pos,y_train_pos=load_features('x_train_pos.pickle',True)
x_train_neg,y_train_neg=load_features('x_train_neg.pickle',False)

x_train=np.r_[x_train_pos,x_train_neg]
y_train=np.r_[y_train_pos,y_train_neg]


x_test_pos,y_test_pos=load_features('x_test_pos.pickle',True)
x_test_neg,y_test_neg=load_features('x_test_neg.pickle',False)

x_test=np.r_[x_test_pos,x_test_neg]
y_test=np.r_[y_test_pos,y_test_neg]


svc=SVC(kernel='linear',C=0.0001)

start=time.time()

svc.fit(x_train,y_train)

end=time.time()

print('训练共计耗时:',end-start)

print('特征维度为:',x_train.shape)

print('准确率为:',svc.score(x_test,y_test))




#gbdt=GradientBoostingClassifier()
#
# start=time.time()
#
# gbdt.fit(x_train,y_train)
#
# end=time.time()
#
# print('训练共计耗时:',end-start)
#
# print('特征维度为:',x_train.shape)
#
# print('准确率为:',gbdt.score(x_test,y_test))
#
# f=open('fi.pickle','wb')
#
# pickle.dump(gbdt.feature_importances_,f)
#
# print(gbdt.feature_importances_)



