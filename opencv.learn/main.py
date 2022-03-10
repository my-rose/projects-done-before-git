import cv2 as cv

def rescaleFrame(frame, scale=0.75):
    width = int(frame.shape[1] * scale)
    height = int(frame.shape[0] * scale)
    dimensions = (width, height)

    return cv.resize(frame, dimensions, interpolation=cv.INTER_AREA)


cap = cv.VideoCapture(0)
cap.set(10, 100)

while True:
    success, img_n = cap.read()
    img = rescaleFrame(img_n, 0.5)

    cv.imshow("cam", img)
    if cv.waitKey(1) & 0xFF == ord('q'):
        break