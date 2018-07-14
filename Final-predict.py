from __future__ import unicode_literals
import numpy as np # linear algebra
import pandas as pd # data processing, CSV file I/O (e.g. pd.read_csv)
from sklearn.preprocessing import StandardScaler
from sklearn.tree import DecisionTreeClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.ensemble import RandomForestClassifier , GradientBoostingClassifier
from sklearn.metrics import confusion_matrix
from sklearn.metrics import accuracy_score
import serial #Import Serial Library
import serial.tools.list_ports
import sys
import time
from gtts import gTTS
from playsound import playsound
import os


print("Start Connection.")
arduino = serial.Serial("COM4",9600,timeout=.1)
temp=arduino.readline()
print(temp)


print("Load Data.")
data=pd.read_csv("D:/Uni/4th year/Grad Project/final_codes/char_data.csv", encoding='windows-1256')


#drop label columns
X = data.drop(['Label'], axis=1)
y = data['Label']
std_scale = StandardScaler().fit(X)
X_train_std = std_scale.transform(X)


print("Train Model.")
#train models
model_1 = RandomForestClassifier()
model_1.fit(X_train_std,y)

model_3 = DecisionTreeClassifier()
model_3.fit(X_train_std,y)

i=0
get=True
while get:
print("Get Sample.")
#send 1 to arduino to send current readings
arduino.write(b"1")
time.sleep(5)
line=arduino.readline()

#if it's empty loop till it get readings
while line==temp:
	print(line)
	arduino.write(b"1")
	time.sleep(3)
	line=arduino.readline()

#print readings
#print(line)
sep= line.split()
new_data={
'Thumb': [float(sep[0])],
'Index': [float(sep[1])],
'Middle': [float(sep[2])],
'Ring': [float(sep[3])],
'Pinky': [float(sep[4])],
'X': [int(sep[5])],
'Y': [int(sep[6])]
}
print(new_data);

print("Predicted Label:")
test= pd.DataFrame.from_dict(new_data)
X_test_std = std_scale.transform(test)

#predict output
predictions_1 = model_1.predict(X_test_std)
predictions_3 = model_3.predict(X_test_std)
print("RandomForest: ",predictions_1)
tts = gTTS(text=str(predictions_1), lang='ar')
file1 = str("hello" + str(i) + ".mp3")
tts.save(file1)
playsound(file1,True)
os.remove(file1)
i=i+1

print("DecisionTree: ",predictions_3)
tts = gTTS(text=str(predictions_3), lang='ar')
file1 = str("hello" + str(i) + ".mp3")
tts.save(file1)
playsound(file1,True)
os.remove(file1)
i=i+1

#get correct output
curr=input("correct Lable: ")