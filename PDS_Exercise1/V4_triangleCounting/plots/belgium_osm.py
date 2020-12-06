import matplotlib.pyplot as plt 

import numpy as np

import matplotlib.font_manager as fm 

plt.title(u'belgium_osm.mtx #Triangles: 2420 #Nodes: 1441295',fontsize=14, color='red')

plt.xlim(0,22)
plt.ylim(-0.1,0.6)

x =  [1 ,2 ,5,10,20]
y1 =  [0.045794, 0.045794, 0.045794, 0.045794, 0.045794]
y2 =  [0.285998, 0.371864, 0.211809, 0.110785, 0.126386]
y3 =  [0.289135, 0.395819, 0.191454, 0.119331, 0.074569]
y4 =  [0.074768, 0.137661, 0.164674, 0.230882, 0.218658]


plt.plot(x,y1,'C1', label='Sequantial',marker='o')

plt.plot(x,y2,'C2', label='Cilk',marker='o')

plt.plot(x,y3,'C3', label='openMP',marker='o')

plt.plot(x,y4,'C4', label='Pthreads',marker='o')


legend = plt.legend(loc='upper right', shadow=True,title="Threads", fontsize='small')

plt.xlabel('Number of threads')

plt.ylabel(r'time')


plt.grid(True)


plt.show()

