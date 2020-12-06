import matplotlib.pyplot as plt 

import numpy as np

import matplotlib.font_manager as fm 

plt.title(u'mycielskian13 #Triangles: 0 #Nodes: 6143',fontsize=14, color='red')

plt.xlim(0,22)
plt.ylim(-0.1,1)

x =  [1 ,2 ,5,10,20]
y1 =  [0.575955, 0.575955, 0.575955, 0.575955, 0.575955]
y2 =  [0.519427, 0.629686, 0.182750, 0.146564, 0.354780]
y3 =  [0.703165, 0.564360, 0.499576, 0.346180, 0.305742]
y4 =  [0.522707, 0.455667, 0.413167, 0.340942, 0.290001]


plt.plot(x,y1,'C1', label='Sequantial',marker='o')

plt.plot(x,y2,'C2', label='Cilk',marker='o')

plt.plot(x,y3,'C3', label='openMP',marker='o')

plt.plot(x,y4,'C4', label='Pthreads',marker='o')


legend = plt.legend(loc='upper right', shadow=True,title="Threads", fontsize='small')

plt.xlabel('Number of threads')

plt.ylabel(r'time')


plt.grid(True)


plt.show()

