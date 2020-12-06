import matplotlib.pyplot as plt 

import numpy as np

import matplotlib.font_manager as fm 

plt.title(u'com-Youtube.mtx #Triangles: 3056386 #Nodes: 1134890' ,fontsize=14, color='red')

plt.xlim(0,22)
plt.ylim(-0.1,4)

x =  [1 ,2 ,5,10,20]
y1 =  [2.338140, 2.338140, 2.338140, 2.338140, 2.338140]
y2 =  [2.769291, 1.474416, 1.240829, 1.305480, 1.444828]
y3 =  [3.199172, 2.838810, 2.296935, 1.910767, 1.796194]
y4 =  [2.388971, 1.862866, 1.828358, 1.829119, 1.908227]


plt.plot(x,y1,'C1', label='Sequantial',marker='o')

plt.plot(x,y2,'C2', label='Cilk',marker='o')

plt.plot(x,y3,'C3', label='openMP',marker='o')

plt.plot(x,y4,'C4', label='Pthreads',marker='o')


legend = plt.legend(loc='upper right', shadow=True,title="Threads", fontsize='small')

plt.xlabel('Number of threads')

plt.ylabel(r'time')


plt.grid(True)


plt.show()

