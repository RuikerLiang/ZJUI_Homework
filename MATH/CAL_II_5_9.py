# This program is to solve the 9th problem in CAL_II_5 homework

from math import pi, sin

n = 10
ans = 0
delta = pi / n
for i in range(0, n):
	xi = (delta * i + delta * (i + 1)) / 2
	ans = ans + sin(xi) * delta
print(ans * 13)

ans = 0
for i in range(0, n):
	yi = (sin(delta * i) + sin(delta * (i + 1))) / 2
	ans = ans + yi * delta
ans = ans * 13
print(ans)

ans = 0
for i in range(0, n + 1):
	if (i == 0 or i == n):
		xi = 1
	else:
		if (i % 2):
			xi = 4
		else:
			xi = 2
	ans = ans + sin(i * delta) * xi * delta
ans = ans * 13 / 3
print(ans)
