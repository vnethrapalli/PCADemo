import numpy as np
import matplotlib.pyplot as plt
import random
import sys
random.seed(10)

# enter a flattened 3x3 matrix for scaling the randomly generated circle
mat = None
if len(sys.argv) == 10:
    mat = [[], [], []]
    for i in range(3):
        for j in range(3):
            mat[i].append(float(sys.argv[1 + 3 * i + j]))
else:
    print('please pass in a space-separated 3x3 matrix (ie. 3 -4 -1 3 4 -1 3 0 2 )')
    exit()
mat = np.array(mat).T

palette = ['#987284', '#9DBF9E', '#F9B5AC', '#EE7674', '#D0D6B5']
num_data_points = 128
X = []

for i in range(num_data_points):
    noisy_radius = 1 + 0.1 * (2 * random.random() - 1)
    theta = random.random() * 2 * np.pi
    phi = random.random() * np.pi
    x = noisy_radius * np.sin(phi) * np.cos(theta)
    y = noisy_radius * np.sin(phi) * np.sin(theta)
    z = noisy_radius * np.cos(phi)
    pt = np.array([[x, y, z]])

    X.append(np.matmul(pt, mat).flatten())
X = np.array(X)

fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.scatter(X[:, [0]], X[:, [1]], X[:, [2]], color=palette[0], alpha=0.4, edgecolors='none')
ax.set_title('ellipsoid data')
plt.savefig('ellipsoid.png')

# write data to text file
with open('ellipse.txt', 'w') as file:
    file.write(f'{num_data_points},{3}\n')
    for row in X:
        file.write(','.join(map(str, row)) + '\n')