import cv2 as cv

img = cv.imread("cat.jpg")
cv.imshow("caaaaat", img)

gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
cv.imshow("Caaat?", gray)

blur = cv.GaussianBlur(img, (1,7), cv.BORDER_DEFAULT)
cv.imshow("cat...", blur)

canny = cv.Canny(blur, 125, 175)
cv.imshow("not cat..", canny)

dilated = cv.dilate(canny, (3,3), iterations=1)
cv.imshow("???", dilated)

cap = cv.VideoCapture(0)
cap.set(10, 100)

while True:
    success, img_n = cap.read()
    img = cv.Canny(img_n, 125, 175)

    cv.imshow("cam", img)
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
cv.waitKey(0)