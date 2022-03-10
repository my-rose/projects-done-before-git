import cv2 as cv
import numpy as np

blank = np.zeros((500, 500, 3), dtype='uint8')
blank[:] = 0,255,0
cv.circle(blank, (250, 250), 40, (200, 20, 0), thickness=cv.FILLED)
cv.line(blank, (30, 350), (300, 35), (0, 0, 150), thickness=3)
cv.putText(blank, 'Ty Real`no pidor//', (220, 321), cv.FONT_HERSHEY_SIMPLEX, 1, (120, 121, 122), 2)

img = cv.imread("cat.jpg")
cv.imshow("cat", img)
cv.imshow("Blank", blank)

cv.waitKey(0)