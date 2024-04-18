import numpy as np
import matplotlib.pyplot as plt
import random
random.seed(10)

num_data_points = 100
data = []

for i in range(num_data_points):
    noisy_radius = 1 + 0.1 * (2 * random.random() - 1)
    theta = random.random() * 2 * np.pi
    x = noisy_radius * np.cos(theta)
    y = noisy_radius * np.sin(theta)

    # multiply by matrix: [3 -1; 3 1]
    x, y = 3*x - y, 3*x + y
    data.append([x, y])

plt.figure()
plt.scatter([data[0] for data in data], [data[1] for data in data], alpha=0.6)
plt.title('ellipse data')
plt.savefig('ellipse.png')

# write data to text file
with open('ellipse.txt', 'w') as file:
    file.write(f'{num_data_points},{2}\n')
    for row in data:
        file.write(','.join(map(str, row)) + '\n')