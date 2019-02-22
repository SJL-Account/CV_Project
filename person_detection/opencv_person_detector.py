import cv2


def draw_person(img,person):
    x,y,w,h=person
    cv2.rectangle(img,(x,y),(x+w,y+h),(0,255,255),2)

img=cv2.imread('INRIAPerson/Train/pos/crop001035.png')

print(img.shape)

hog=cv2.HOGDescriptor()

svm_detector=cv2.HOGDescriptor_getDefaultPeopleDetector()

hog.setSVMDetector(svm_detector)

found,w=hog.detectMultiScale(img)


