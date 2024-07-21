## 가변 배열
height, width = 3, 4
image = []  # 2차원 배열
tmp = []  # 1차원 배열(임시)

for _ in range(height) :
    for _ in range(width) :
        tmp.append(0)
    image.append(tmp)
print(image)

## 가변 배열
height, width = 3, 4
image = [[0 for _ in range(width)] for _ in range(height)]
print(image)