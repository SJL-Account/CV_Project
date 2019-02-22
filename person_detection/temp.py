import pickle

f=open('gbdt_feature_importance.pickle','rb')

weights=pickle.load(f)

print(len(weights[weights>0]))