ary4=[]
for _ in range(100) :
    ary4.append(random.randint(0,10000))
print(ary4)

## 그리고 최대값, 최소값, 합계, 평균을 구하자
maxVal, minVal, sumVal, avgVal = [0] * 4

maxVal = minVal = ary4[0]
for i in range(len(ary4)) :
    if (maxVal < ary4[i]) :
        maxVal = ary4[i]
    if (minVal > ary4[i]) :
        minVal = ary4[i]
    sumVal += ary4[i]

avgVal = sumVal / len(ary4)

print(maxVal, minVal, sumVal, avgVal)