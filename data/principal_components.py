import numpy as np
import matplotlib.pyplot as plt
np.random.seed(11829)

# load principal components, projected data, and original data
X = []
with open('ellipse.txt', 'r') as file:
    for line in file.readlines()[1:]:
        pt = line.split(',')
        pt = list(map(lambda x: float(x.strip()), pt))
        X.append(pt)
X = np.array(X)

for col in range(len(X[0])):
    X[:, [col]] = (X[:, [col]] - np.mean(X[:, [col]])) / np.std(X[:, [col]], ddof=1)

# components are written transposed
components = []
with open('components.txt', 'r') as file:
    for line in file.readlines():
        pt = line.split(',')
        pt = list(map(lambda x: float(x.strip()), pt))
        components.append(pt)
components = np.array(components).T

X_proj = []
with open('xproj.txt', 'r') as file:
    for line in file.readlines():
        pt = line.split(',')
        pt = list(map(lambda x: float(x.strip()), pt))
        X_proj.append(pt)
X_proj = np.array(X_proj)

# plot data
plt.figure()
axes = plt.gca()
axes.set_aspect('equal')
plt.scatter([data[0] for data in X], [data[1] for data in X], alpha=0.4) # raw data

# PC1
pc1_slope = components[1][0] / components[0][0]
pc2_slope = components[1][1] / components[0][1]
xbds = np.array(axes.get_xlim())
plt.plot(xbds, xbds * pc1_slope, alpha=0.5, label='pc1', color='orange')
plt.plot(xbds, xbds * pc2_slope, alpha=0.5, label='pc2', color='red')


# choose some datapoints to show the projections for
idxs = np.random.choice(len(X), size=20, replace=False)
for idx in idxs:
    pt1 = X[idx]
    pt2 = X_proj[idx][0] * components[:, [0]].T
    pt2 = pt2[0]
    plt.plot([pt1[0], pt2[0]], [pt1[1], pt2[1]], alpha=0.3, color='purple')

plt.legend()
plt.xlabel('$x$ standardized')
plt.ylabel('$y$ standardized')
plt.title('projected ellipse data')
plt.savefig('ellipse_pca.png')
