import numpy as np
import matplotlib.pyplot as plt
import random
import sys
random.seed(10)

# enter a flattened 2x2 matrix for scaling the randomly generated circle
mat = None
if len(sys.argv) == 5:
    mat = [[], []]
    for i in range(2):
        for j in range(2):
            mat[i].append(float(sys.argv[1 + 2 * i + j]))
else:
    print('please pass in a space-separated 2x2 matrix (ie. 3 -1 3 1)')
    exit()
mat = np.array(mat).T

palette = ['#987284', '#9DBF9E', '#F9B5AC', '#EE7674']
num_data_points = 100
X = []

for i in range(num_data_points):
    noisy_radius = 1 + 0.1 * (2 * random.random() - 1)
    theta = random.random() * 2 * np.pi
    x = noisy_radius * np.cos(theta)
    y = noisy_radius * np.sin(theta)
    pt = np.array([[x, y]])

    X.append(np.matmul(pt, mat).flatten())
X = np.array(X)

plt.figure()
plt.scatter(X[:, [0]], X[:, [1]], color=palette[0], alpha=0.7, edgecolors='none')
plt.title('ellipse data')
plt.savefig('ellipse.png')

# write data to text file
with open('ellipse.txt', 'w') as file:
    file.write(f'{num_data_points},{2}\n')
    for row in X:
        file.write(','.join(map(str, row)) + '\n')