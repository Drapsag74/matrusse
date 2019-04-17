import subprocess as sp
import matplotlib.pyplot as plt
import numpy as np


v=np.arange(6,15,1)
tab = []
for j in v:
    T=[]
    for i in range (3):
        bloc = str(j)
        out = sp.check_output(['../cmake-build-release/src/Matrusse 2048 2048 '+bloc+' -m3'], shell=True).decode("utf-8")
        out = out.split(": ")
        p = out[2]
        p = int(p)
        T.append(p)
        moy = (sum(T)/len(T))
        print(i)
    tab.append(moy)
    print(j)
plt.plot(v,tab)

import subprocess as sp
import matplotlib.pyplot as plt


"""
tfinal=np.zeros((3,4))
k=[2048,4096,8192,16384]
ite=0

for j in k:
    for i in range (1,3):
        print(i)
        taille = str(j)
        version = str(i)
        out = sp.check_output(['../cmake-build-release/src/Matrusse '+taille+' '+taille+' 8 -m'+version], shell=True).decode("utf-8")
        out = out.split(": ")
        p = out[2]
        p = int(p)
        tfinal[i-1,ite]=p
    ite+=1

"""


