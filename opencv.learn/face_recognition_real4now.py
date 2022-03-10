import cv2 as cv
import numpy as np

haar_cascade = cv.CascadeClassifier('haar_face.xml')
features = np.load('features.npy', allow_pickle=True)
labels = np.load('labels.npy', allow_pickle=True)
people = np.load('people.npy', allow_pickle=True)

face_recognizer = cv.face.LBPHFaceRecognizer_create()
face_recognizer.read('face_trained.yml')

cap = cv.VideoCapture(0)
while True:
    success, img = cap.read()

    gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
    faces_rect = haar_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=4)
    for (x,y,w,h) in faces_rect:
        faces_roi = gray[y:y+h,x:x+w]
        label, confidence = face_recognizer.predict(faces_roi)

        cv.rectangle(img, (x,y), (x+w,y+h), (121, 12, 45), thickness = 2)
        cv.putText(img, str(people[label]), (x-10,y-10), cv.FONT_HERSHEY_COMPLEX, 1.0, (121, 12, 45), thickness = 2)

    cv.imshow("cam", img)
    if cv.waitKey(0) & 0xFF == ord('q'):
        break