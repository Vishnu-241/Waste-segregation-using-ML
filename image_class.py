import os
import cvzone
from cvzone.ClassificationModule import Classifier
import serial
import time
import cv2

#arduino = serial.Serial(port='COM3', baudrate=9600, timeout=.1)

cap = cv2.VideoCapture(0)
Classifier = Classifier('Resources/Model/keras_model.h5', 'Resources/Model/labels.txt')
#import all waste images
imgWastelist=[]
PathfolderWaste="Resources/waste"
Pathlist=os.listdir(PathfolderWaste)
for path in Pathlist:
    imgWastelist.append(cv2.imread(os.path.join(PathfolderWaste, path), cv2.IMREAD_UNCHANGED))
print(Pathlist)

while True:
    _, img = cap.read()
    imgResize=cv2.resize(img, (380, 310))
    predection =Classifier.getPrediction(img)
    print(predection)
    print(predection[1])
    cv2.imshow("Image", imgResize)
    if predection:
        cv2.imshow("image_class",imgWastelist[predection[1]])
    if predection[1]==1 or predection[1]==2 or predection[1]==3 or predection[1]==4 or predection[1]==5 or predection[1]==10:
        #arduino.write(b"H\n")
        #print(arduino.readline().decode("ascii"))
        drywaste=cv2.imread("Resources/bins/dry_waste.png")
        cv2.imshow("output",drywaste)
        cv2.waitKey(20)
        #time.sleep(10)
    elif predection[1]==6 or predection[1]==7 or predection[1]==8 or predection[1]==9 or predection[1]==11:
        #arduino.write(b"L\n")
        #print(arduino.readline().decode("ascii"))
        e_waste=cv2.imread("Resources/bins/e_waste.png")
        cv2.imshow("output",e_waste)
        cv2.waitKey(20)
        #time.sleep(10)
    cv2.waitKey(1)