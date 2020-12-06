import matplotlib.pyplot as plt 

import numpy as np

import matplotlib.font_manager as fm 

plt.title(u'dblp-2010 #Triangles: 1676652 #Nodes: 326186',fontsize=14, color='red')

plt.xlim(0,22)
plt.ylim(-0.1,0.4)

x =  [1 ,2 ,5,10,20]
y1 =  [0.059198, 0.059198, 0.059198, 0.059198, 0.059198]
y2 =  [0.121795, 0.140164, 0.060100, 0.059026, 0.071847]
y3 =  [0.107733, 0.142269, 0.064411, 0.043285, 0.025950]
y4 =  [0.095559, 0.178463, 0.192839, 0.268421, 0.251314]


plt.plot(x,y1,'C1', label='Sequantial',marker='o')

plt.plot(x,y2,'C2', label='Cilk',marker='o')

plt.plot(x,y3,'C3', label='openMP',marker='o')

plt.plot(x,y4,'C4', label='Pthreads',marker='o')


legend = plt.legend(loc='upper right', shadow=True,title="Threads", fontsize='small')

plt.xlabel('Number of threads')

plt.ylabel(r'time')


plt.grid(True)


plt.show()

