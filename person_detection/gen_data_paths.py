import os

os.chdir('INRIAPerson/')

base_dir = '96X160H96/Train/pos/'

dirs = os.listdir(base_dir)

os.chdir('96X160H96/Train/')

f = open('pos.lst', 'w')

for dir_ in dirs:
    f.writelines(base_dir + dir_ + '\n')

f.close()
