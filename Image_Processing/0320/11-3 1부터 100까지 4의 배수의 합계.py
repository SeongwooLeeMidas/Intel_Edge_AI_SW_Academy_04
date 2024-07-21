# 퀴즈 : 1부터 100까지 4의 배수의 합계
hap = 0
for i in range(0, 101, 4) :
    hap = hap + i
print(hap)