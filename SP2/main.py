import numpy as np
import math
from operator import add
from PIL import Image, ImageDraw

w, h = 128, 128

nums = []
center = [w / 2, h / 2]
for i in range(20):
	X = np.random.uniform(center[0] - 30, center[0] + 30, size=2)
	while tuple(X) in nums:
		X = np.random.uniform(center[0] - 30, center[0] + 30, size=2)
	nums.append((float(X[0]), float(X[1])))

img = Image.new("RGB", (w, h))
img1 = ImageDraw.Draw(img)
img1.point(nums, fill=None)

print("Points: ", nums)
nums.sort(key=lambda y: y[0])
print("Sorted points in X: ", nums)
half = len(nums) // 2
print("Half size: ", half)
fh = nums[0:half]
sh = nums[half:]
print("First half: ", fh)
print("Second half: ", sh)

fhd = []
shd = []
for pair1 in fh:
	for pair2 in fh:
		if pair1[0] != pair2[0] or pair1[1] != pair2[1]:
			dx = pair2[0] - pair1[0]
			dy = pair2[1] - pair1[1]
			d = math.sqrt(dx * dx + dy * dy)
			fhd.append(d)
for pair1 in sh:
	for pair2 in sh:
		if pair1[0] != pair2[0] or pair1[1] != pair2[1]:
			dx = pair2[0] - pair1[0]
			dy = pair2[1] - pair1[1]
			d = math.sqrt(dx * dx + dy * dy)
			shd.append(d)
#print ["{0:0.2f}".format(i) for i in a]
print("First half distances(", len(fhd), "): ")
print(["{0:0.2f}".format(i) for i in fhd])
print("Second half distances(", len(shd), "): ")
print(["{0:0.2f}".format(i) for i in shd])
sfhd = min(fhd)
sshd = min(shd)
print("Smallest distance in first half:", sfhd)
print("Smallest distance in second half:", sshd)
midD = sh[0][0]
print("Middle X (MIDD):", midD)
minD = min(sfhd, sshd)
print("Minimum distance (D):", minD)
d1 = midD - minD
d2 = midD + minD
print("MIDD-D:", d1)
print("MIDD+D:", d2)

strip = []
for point in nums:
	if point[0] >= d1 and point[0] <= d2:
		strip.append(point)

print("Points in strip: ", strip)
strip.sort(key=lambda y: y[1])
print("Points in strip, sorted in Y: ", strip)

candidates = []
for pair1 in strip:
	for pair2 in strip:
		if pair1[0] != pair2[0] or pair1[1] != pair2[1]:
			dx = pair2[0] - pair1[0]
			dy = pair2[1] - pair1[1]
			d = math.sqrt(dx * dx + dy * dy)
			candidates.append(d)

print("Candidate distances:", candidates)
print("Minimum distance:", min(candidates))

shape1 = [d1, 0, d1, h]
shape2 = [d2, 0, d2, h]
img1.line(shape1, fill=None, width=0)
img1.line(shape2, fill=None, width=0)
img.save('points.png')