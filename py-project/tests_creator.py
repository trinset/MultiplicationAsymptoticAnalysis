import random as rnd

#   creates a package with tests

file = open("../data/realTest.csv", 'w')

for k in range(1, 1001):

    num1 = str(rnd.randrange(1, 10))
    num2 = str(rnd.randrange(1, 10))

    for i in range(1, k):
        num1 += str(rnd.randrange(0, 10))
        num2 += str(rnd.randrange(0, 10))

    file.write(num1 + ',' + num2 + ',')
    res = int(num1) * int(num2)
    file.write(str(res) + '\n')

file.close()
