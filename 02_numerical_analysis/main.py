import matplotlib.pyplot as plt
import numpy as np

data_by_forward = []
data_by_backward = []

num_of_step = 10
stride = 1 / num_of_step

time = list(map(lambda y: y * stride, range(num_of_step)))
data_real = list(map(lambda t: np.exp(0.5 * t * t), time))

data_by_forward.append(1.0)
data_by_backward.append(1.0)

for i in range(1, num_of_step):
    data_by_forward.append(data_by_forward[i - 1] * (1 +  stride * i * stride))
    data_by_backward.append(data_by_backward[i - 1] / (1 - stride * i * stride))

plt.plot(time, data_by_forward, label = "forward")
plt.plot(time, data_by_backward, label = "backward")
plt.plot(time, data_real, label = "real")

plt.show()
