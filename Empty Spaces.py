import cv2 as cv
img = cv.imread('cat.jpg')
#cv.imshow('CatCat', img)
str = ".:-=+*#%@"
#str2 = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,^`'.   69"
file = open("funy_img.txt", 'w')

gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
cv.imshow('Gray', gray)

#print(gray[11, 11])
#print(gray.shape[0])

for i in range(0, gray.shape[0], 5):
    for j in range(gray.shape[1]):
        file.write(str[int((gray[i, j]/255)*9-1)])
    file.write('\n')

file.close()
cv.waitKey(0)