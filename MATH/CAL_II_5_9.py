from math import pi, sin

from matplotlib.ticker import EngFormatter

n = 40
ans = 0
end_ans = 26
delta = pi / n
exp = 0.00001
# M
for i in range(0, n):
	xi = (delta * i + delta * (i + 1)) / 2
	ans = ans + sin(xi) * delta
ans = ans * 13
print(ans)
print((end_ans - ans))
E_m = 13* pi ** 3 / (24 * n * n)
print(E_m)
i = 1
while (13 * pi ** 3 / (24 * i * i) > exp):
	i = i + 1
print(i)

# T
ans = 0
for i in range(0, n):
	yi = (sin(delta * i) + sin(delta * (i + 1))) / 2
	ans = ans + yi * delta
ans = ans * 13
print(ans)
print(end_ans - ans)
E_t = 13 * pi ** 3 / (12 * n * n)
print(E_t)
i = 1
while (13 * pi ** 3 / (12 * i * i) > exp):
	i = i + 1
print(i)

# S
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
print(end_ans - ans)
E_s = 13 * pi ** 5 / (180 * n ** 4)
print(E_s)
