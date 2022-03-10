import cv2 as cv

img = cv.imread("girl2.jpg")
gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
cv.imshow('boy', img)

haar_cascade = cv.CascadeClassifier('haar_face.xml')

faces_rect = haar_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5)
for (x, y, w, h) in faces_rect:
    cv.rectangle(img, (x,y), (x+w,y+h), (170,52,115), thickness=2)

cv.imshow('catboy', img)



cap = cv.VideoCapture(0)
cap.set(10, 100)

while True:
    success, img_v = cap.read()
    gray_v = cv.cvtColor(img_v, cv.COLOR_BGR2GRAY)

    faces_rect = haar_cascade.detectMultiScale(gray_v, scaleFactor=1.1, minNeighbors=3)

    for (x, y, w, h) in faces_rect:
        cv.rectangle(img_v, (x, y), (x + w, y + h), (170, 52, 115), thickness=2)

    cv.imshow("cum", img_v)
    if cv.waitKey(1) & 0xFF == ord('q'):
        break

cv.waitKey(0)