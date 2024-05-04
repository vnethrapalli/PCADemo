import numpy as np
import matplotlib.pyplot as plt
np.random.seed(11829)

palette = ['#987284', '#9DBF9E', '#F9B5AC', '#EE7674', '#D0D6B5']

# load principal components, projected data, and original data
X = []
with open('ellipse.txt', 'r') as file:
    for line in file.readlines()[1:]:
        pt = line.split(',')
        pt = list(map(lambda x: float(x.strip()), pt))
        X.append(pt)
X = np.array(X)

# standardize the data
for col in range(len(X[0])):
    X[:, [col]] = (X[:, [col]] - np.mean(X[:, [col]])) / np.std(X[:, [col]], ddof=1)

# plot the standardized data
fig = plt.figure()
axes = fig.add_subplot(projection='3d')
axes.scatter(X[:, [0]], X[:, [1]], X[:, [2]], color=palette[0], alpha=0.9, edgecolors='none')
axes.set_title('standardized ellipsoid data')
plt.savefig('ellipsoid_std.png')

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


# PCs
all_projections = np.matmul(X, components)
axes.set_aspect('equal')
for k in range(3):
    # find minimum scaling such that the pc line will be past the largest coordinate in the data
    forward_factor = np.max(all_projections[:, [k]])
    backwards_factor = np.min(all_projections[:, [k]])
    xs = [backwards_factor * components[0, k], forward_factor * components[0, k]]
    ys = [backwards_factor * components[1, k], forward_factor * components[1, k]]
    zs = [backwards_factor * components[2, k], forward_factor * components[2, k]]
    axes.plot(xs, ys, zs, alpha=0.8, label=f'pc{k+1}', color=palette[1 + k], linewidth=2)
plt.legend()
plt.title('ellipsoid principal components')
axes.view_init(elev=5)
plt.savefig('ellipsoid_components.png')


# choose some datapoints to show the projections for
# plot plane (normal vector is pc3)
x = np.linspace(np.min(X[:, [0]]), np.max(X[:, [0]]), 5)
y = np.linspace(np.min(X[:, [1]]), np.max(X[:, [1]]), 5)
xmesh, ymesh = np.meshgrid(x, y)
z = (- xmesh * components[0, 2] - ymesh * components[1, 2]) / components[2, 2]
axes.plot_surface(xmesh, ymesh, z, alpha=0.4, color=palette[4])

idxs = np.random.choice(len(X), size=12, replace=False)
for idx in idxs:
    pt1 = X[idx]
    pt2 = X_proj[idx][0] * components[:, [0]].T + X_proj[idx][1] * components[:, [1]].T
    pt2 = pt2[0]
    plt.plot([pt1[0], pt2[0]], [pt1[1], pt2[1]], [pt1[2], pt2[2]], alpha=0.9, color=palette[4])

plt.xlabel('$x$ standardized')
plt.ylabel('$y$ standardized')
plt.title('projected ellipsoid data')
plt.savefig('ellipsoid_pca.png')
