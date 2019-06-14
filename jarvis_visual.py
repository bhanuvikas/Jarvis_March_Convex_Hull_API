import numpy as np
import matplotlib.pyplot as plt
import imageio

print("Running JarvisMarch Visualizer....")
fileName1 = "jarvis_output.txt"
fileName2 = "points.txt"

with open(fileName2) as f:
    lines = f.readlines()

points = np.ndarray((len(lines), 2))
i = 0
for line in lines:
    x, y = list(map(float, line.split()))[0:2]
    points[i][0] = x
    points[i][1] = y
    i = i+1

x_cord = []
y_cord = []


gif = []

for point in points:
    x_cord.append(point[0])
    y_cord.append(point[1])

with open(fileName1) as f:
     lines = f.readlines()

data = np.ndarray((len(lines),4))
i=0
for line in lines:
    x1, y1, x2, y2 = list(map(float, line.split()))[0:4]
    data[i][0] = x1
    data[i][1] = y1
    data[i][2] = x2
    data[i][3] = y2
    i = i+1

j=0
last_line = np.ndarray((1,4), buffer = np.array([0, 0, 0, 0]))
hull = []
for i in data:
    x1 = i[0]
    y1 = i[1]
    x2 = i[2]
    y2 = i[3]
    if(int(x1)==-2147480000 and int(y1)==-2147480000 and int(x2)==-2147480000 and int(y2)==-2147480000):
        break
    if(int(x1)==-2147480000 and int(y1)==-2147480000):
        if(j>0):
             hull.append(last_line)   
    else:
        j = j+1
        x = [x1, x2]
        y = [y1, y2]
        fig, ax = plt.subplots(figsize=(5,5))
        #fig = plt.figure()
        ax.axis("off")
        ax.scatter(x_cord, y_cord, marker = 'o', s = 15)
        for k in hull:
            temp_x = []
            temp_y = []
            temp_x.append(k[0])
            temp_x.append(k[2])
            temp_y.append(k[1])
            temp_y.append(k[3])
            ax.plot(temp_x, temp_y, linewidth=2, color='g')
        ax.plot(x, y, linewidth=2, color='r')
        fig.canvas.draw()
        image = np.frombuffer(fig.canvas.tostring_rgb(), dtype='uint8')
        gif.append(image.reshape(fig.canvas.get_width_height()[::-1] + (3,)))
        #fig.savefig("fig/figure" + str(j) + ".jpg")
        
    last_line = i

fig, ax = plt.subplots(figsize=(5,5))
plt.axis("off")
plt.scatter(x_cord, y_cord, marker = 'o', s = 15)
for k in hull:
    temp_x = []
    temp_y = []
    temp_x.append(k[0])
    temp_x.append(k[2])
    temp_y.append(k[1])
    temp_y.append(k[3])
    ax.plot(temp_x, temp_y, linewidth=2, color='g')
fig.canvas.draw()
image = np.frombuffer(fig.canvas.tostring_rgb(), dtype='uint8')
gif.append(image.reshape(fig.canvas.get_width_height()[::-1] + (3,)))
#fig.savefig("fig/figure" + str(j+1) + ".jpg")
            
#print(hull)
imageio.mimsave('./jarvis.gif', gif, fps=2)
print(hull)