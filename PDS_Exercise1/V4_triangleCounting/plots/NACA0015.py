import matplotlib.pyplot as plt 

import numpy as np

import matplotlib.font_manager as fm 

plt.title(u'NACA0015 #Triangles: 2075635 #Nodes: 1039183',fontsize=14, color='red')

plt.xlim(0,22)
plt.ylim(-0.1,0.6)

x =  [1 ,2 ,5,10,20]
y1 =  [0.300415, 0.300415, 0.300415, 0.300415, 0.300415]
y2 =  [0.474316, 0.289469, 0.213823, 0.164642, 0.166224]
y3 =  [0.498034, 0.471777, 0.242580, 0.140472, 0.075795]
y4 =  [0.341709, 0.299316, 0.377582, 0.539775, 0.571636]


plt.plot(x,y1,'C1', label='Sequantial',marker='o')

plt.plot(x,y2,'C2', label='Cilk',marker='o')

plt.plot(x,y3,'C3', label='openMP',marker='o')

plt.plot(x,y4,'C4', label='Pthreads',marker='o')


legend = plt.legend(loc='upper right', shadow=True,title="Threads", fontsize='small')

plt.xlabel('Number of threads')

plt.ylabel(r'time')


plt.grid(True)


plt.show()

