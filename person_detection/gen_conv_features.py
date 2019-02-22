import os
import cv2
import matplotlib.pyplot as plt
import numpy as np
import pickle
import pandas as pd
from keras.models import  load_model
np.set_printoptions(suppress=True)

import keras

print('加载VGG模型....(没有全连接层，imagenet参数)')

vgg16 =load_model('model')

def ouput_layer(path_, model):
    img_ = cv2.imread(path_)

    # 行数小于256
    if img_.shape != (256, 256, 3):
        n_row = img_.shape[0]
        n_col = img_.shape[1]

        # 如果行数或者裂数小于256

        if (n_row < 256) | (n_col < 256):
            img_fig = np.zeros((256, 256, 3))

            img_fig[:n_row, :n_col, :] = img_

            img_ = img_fig

        # 如果行数或者列数大于256

        if (n_row > 256) | (n_col > 256):
            img_fig = np.zeros((256, 256, 3))

            img_fig = img_[:256, :256, :]

            img_ = img_fig

    layer_1 = keras.backend.function([model.layers[1].input], [model.layers[1].output])

    layer_2 = keras.backend.function([model.layers[2].input], [model.layers[2].output])

    layer_3 = keras.backend.function([model.layers[3].input], [model.layers[3].output])

    layer_4 = keras.backend.function([model.layers[4].input], [model.layers[4].output])

    layer_5 = keras.backend.function([model.layers[5].input], [model.layers[5].output])

    layer_5 = keras.backend.function([model.layers[5].input], [model.layers[5].output])

    layer_6 = keras.backend.function([model.layers[6].input], [model.layers[6].output])

    layer_7 = keras.backend.function([model.layers[7].input], [model.layers[7].output])

    layer_8 = keras.backend.function([model.layers[8].input], [model.layers[8].output])

    layer_9 = keras.backend.function([model.layers[9].input], [model.layers[9].output])

    layer_10 = keras.backend.function([model.layers[10].input], [model.layers[10].output])

    layer_11 = keras.backend.function([model.layers[11].input], [model.layers[11].output])

    layer_12 = keras.backend.function([model.layers[12].input], [model.layers[12].output])

    layer_13 = keras.backend.function([model.layers[13].input], [model.layers[13].output])

    layer_14 = keras.backend.function([model.layers[14].input], [model.layers[14].output])

    layer_15 = keras.backend.function([model.layers[15].input], [model.layers[15].output])

    layer_16 = keras.backend.function([model.layers[16].input], [model.layers[16].output])

    layer_17 = keras.backend.function([model.layers[17].input], [model.layers[17].output])

    layer_18 = keras.backend.function([model.layers[18].input], [model.layers[18].output])


    f1 = layer_1([img_.reshape(-1, 256, 256, 3)])[0]

    f2 = layer_2([f1])[0]

    f3 = layer_3([f2])[0]

    f4 = layer_4([f3])[0]

    f5 = layer_5([f4])[0]

    f6 = layer_6([f5])[0]

    f7 = layer_7([f6])[0]

    f8 = layer_8([f7])[0]

    f9 = layer_9([f8])[0]

    f10 = layer_10([f9])[0]

    f11 = layer_11([f10])[0]

    f12 = layer_12([f11])[0]

    f13 = layer_13([f12])[0]

    f14 = layer_14([f13])[0]

    f15 = layer_15([f14])[0]

    f16 = layer_16([f15])[0]

    f17 = layer_17([f16])[0]

    #f18 = layer_18([f17])[0]

    return f17.flatten()

def ouput_plot_layer(path_, model):

    img = cv2.imread(path_)

    layer_1 = keras.backend.function([model.layers[1].input], [model.layers[1].output])

    layer_2 = keras.backend.function([model.layers[2].input], [model.layers[2].output])

    layer_3 = keras.backend.function([model.layers[3].input], [model.layers[3].output])

    layer_4 = keras.backend.function([model.layers[4].input], [model.layers[4].output])

    layer_5 = keras.backend.function([model.layers[5].input], [model.layers[5].output])

    layer_5 = keras.backend.function([model.layers[5].input], [model.layers[5].output])

    layer_6 = keras.backend.function([model.layers[6].input], [model.layers[6].output])

    layer_7 = keras.backend.function([model.layers[7].input], [model.layers[7].output])

    layer_8 = keras.backend.function([model.layers[8].input], [model.layers[8].output])

    layer_9 = keras.backend.function([model.layers[9].input], [model.layers[9].output])

    layer_10 = keras.backend.function([model.layers[10].input], [model.layers[10].output])

    layer_11 = keras.backend.function([model.layers[11].input], [model.layers[11].output])

    layer_12 = keras.backend.function([model.layers[12].input], [model.layers[12].output])

    layer_13 = keras.backend.function([model.layers[13].input], [model.layers[13].output])

    layer_14 = keras.backend.function([model.layers[14].input], [model.layers[14].output])

    layer_15 = keras.backend.function([model.layers[15].input], [model.layers[15].output])

    layer_16 = keras.backend.function([model.layers[16].input], [model.layers[16].output])

    layer_17 = keras.backend.function([model.layers[17].input], [model.layers[17].output])



    f1 = layer_1([img.reshape(-1, 160, 96, 3)])[0]

    f2 = layer_2([f1])[0]

    f3 = layer_3([f2])[0]

    f4 = layer_4([f3])[0]

    f5 = layer_5([f4])[0]

    f6 = layer_6([f5])[0]

    f7 = layer_7([f6])[0]

    f8 = layer_8([f7])[0]

    f9 = layer_9([f8])[0]

    f10 = layer_10([f9])[0]

    f11 = layer_11([f10])[0]

    f12 = layer_12([f11])[0]

    f13 = layer_13([f12])[0]

    f14 = layer_14([f13])[0]

    f15 = layer_15([f14])[0]

    f16 = layer_16([f15])[0]

    f17 = layer_17([f16])[0]


    for _ in range(64):
        show_img = f1[:, :, :, _]
        plt.subplot(8, 8, _ + 1)
        plt.imshow(show_img[0], cmap='gray')
        plt.axis('off')

    plt.savefig(os.path.split(path_)[1].split('.')[0] + 'layer_1.png', dpi=300)

    for _ in range(64):
        show_img = f2[:, :, :, _]
        plt.subplot(8, 8, _ + 1)
        plt.imshow(show_img[0], cmap='gray')
        plt.axis('off')
    plt.savefig(os.path.split(path_)[1].split('.')[0] + 'layer_2.png', dpi=300)

    for _ in range(64):
        show_img = f3[:, :, :, _]
        plt.subplot(8, 8, _ + 1)
        plt.imshow(show_img[0], cmap='gray')
        plt.axis('off')
    plt.savefig(os.path.split(path_)[1].split('.')[0] + 'layer_3.png', dpi=300)

    for _ in range(128):
        show_img = f4[:, :, :, _]
        plt.subplot(16, 8, _ + 1)
        plt.imshow(show_img[0], cmap='gray')
        plt.axis('off')
    plt.savefig(os.path.split(path_)[1].split('.')[0] + 'layer_4.png', dpi=300)


    for _ in range(128):
        show_img = f5[:, :, :, _]
        plt.subplot(16, 8, _ + 1)
        plt.imshow(show_img[0], cmap='gray')
        plt.axis('off')
    plt.savefig(os.path.split(path_)[1].split('.')[0] + 'layer_5.png', dpi=300)

    for _ in range(128):
        show_img = f6[:, :, :, _]
        plt.subplot(16, 8, _ + 1)
        plt.imshow(show_img[0], cmap='gray')
        plt.axis('off')
    plt.savefig(os.path.split(path_)[1].split('.')[0] + 'layer_6.png', dpi=300)

    for _ in range(256):
        show_img = f7[:, :, :, _]
        plt.subplot(16, 16, _ + 1)
        plt.imshow(show_img[0], cmap='gray')
        plt.axis('off')
    plt.savefig(os.path.split(path_)[1].split('.')[0] + 'layer_7.png', dpi=300)

    for _ in range(256):
        show_img = f8[:, :, :, _]
        plt.subplot(16, 16, _ + 1)
        plt.imshow(show_img[0], cmap='gray')
        plt.axis('off')
    plt.savefig(os.path.split(path_)[1].split('.')[0] + 'layer_8.png', dpi=300)

    for _ in range(512):
        show_img = f17[:, :, :, _]
        plt.subplot(16, 32, _ + 1)
        plt.imshow(show_img[0], cmap='gray')
        plt.axis('off')
    plt.savefig(os.path.split(path_)[1].split('.')[0] + 'layer_17.png', dpi=300)

ouput_plot_layer('./INRIAPerson/96X160H96/Train/neg/01-03d.jpg',vgg16)
