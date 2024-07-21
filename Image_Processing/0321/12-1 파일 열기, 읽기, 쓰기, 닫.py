## 1단계 : 파일 열기
rfp = open('c:/windows/win.ini','rt')
wfp = open('win.txt','wt')

## 2단계 : 파일 읽기 / 쓰기
while (True) :
    line = rfp.readline()
    if (line == None or line =='') : #None == NULL
        break
    for ch in line :
        if ('0' <= ch <= '9') :
            print('*', end='')
        else :
            print(ch, end='')

    print(line, end='')

## 3단계 : 파일 닫기
rfp.fclose()		## Ctrl + / 하면 주석됨