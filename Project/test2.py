import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import numpy as np
import json
import math

file_path = "./0.json"

test_x = []
test_y = []
with open(file_path, 'r') as file:

    data = json.load(file)
    X = data["Lidar_x"]
    Y = data["Lidar_y"]

    machine = [0, 0]
    p1 = 0
    p2 = 0
    # for i, j in zip(X,Y):
    #     a = i-p1
    #     b = j-p2
    #     length = math.sqrt((a*a) + (b*b))
    #     print(i, j, round(length, 2) )
    for i in range(420):
        if (X[i + 4] - X[i]) != 0 and (X[i + 9] - X[i + 4]) != 0:
            temp1 = (Y[i+4] - Y[i]) / (X[i+4] - X[i])
            temp2 = (Y[i+9] - Y[i + 4]) / (X[i+9] - X[i+4])
            theta = math.atan(temp2) - math.atan(temp1)
            theta = theta * 180 / math.pi

            if 110 > abs(theta) > 80: # if (temp1 < 0 < temp2) or (temp2 < 0 < temp1):
                print("theta = ", round(theta))
                # print("temp1 = ", temp1)
                # print("temp2 = ", temp2)
                test_x.append(X[i + 4])
                test_y.append(Y[i + 4])

test_x.insert(0, X[2])
test_y.insert(0, Y[2])
test_x.append(X[len(X)-1])
test_y.append(Y[len(Y)-1])

# plt.scatter(X, Y, c = 'blue', s=5)
plt.scatter(test_x, test_y, c = 'red')
plt.scatter(machine[0], machine[1])

def function(x, a, b):
   return a*x + b

def curve_line(x,y):
    # print(x[0], y[0])
    popt, cov = curve_fit(function,x,y)
    a, b = popt
    # x_new_value = np.arange(min(temp_x), max(temp_x))
    x_new_value = np.arange(min(temp_x), max(temp_x)+2)
    print(len(x),len(x_new_value))

    y_new_value = function(x_new_value, a, b)
    print(x_new_value, y_new_value)
    plt.plot(x_new_value, y_new_value, color="red")


temp = 0

temp_x = []
temp_y = []
for i, j in zip(X,Y):
    if i == test_x[temp] and j == test_y[temp] and temp < len(test_x)-1:

        if temp != 0 and temp_x:
            curve_line(temp_x, temp_y)

        temp += 1
        temp_x.clear()
        temp_y.clear()
    else:
        temp_x.append(i)
        temp_y.append(j)
        # print(temp_x, temp_y)

curve_line(temp_x, temp_y)


plt.xlim(-100, 100)
plt.ylim(-100, 100)

plt.show()