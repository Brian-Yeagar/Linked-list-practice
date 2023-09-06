import random

# 生成60個 0~9的隨機正整數並建立一個dataset.txt
with open('dataset.txt', 'w') as f:
    for i in range(500):
        f.write(str(random.randint(0, 9))
        )
        