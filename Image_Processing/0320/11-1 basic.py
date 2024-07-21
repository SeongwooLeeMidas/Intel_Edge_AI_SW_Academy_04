## 함수부
def add_func(n1, n2) :
    retValue = 0
    retValue = n1 + n2
    return retValue

## 전역 변수부
num1, num2, res = [0] * 3   # 0,0,0


## 메인 코드부
res = add_func(num1,num2)
print(num1, '+', num2, '=', res)