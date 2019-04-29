import subprocess as sp
import matplotlib.pyplot as plt
import numpy as np
from math import *
"""
Comparaison du temps des algos selon la taille du "k" 
"""
"""
v=np.arange(1,15,1)
tab = []
for j in v:
    T=[]
    for i in range (3):
        bloc = str(j)
        out = sp.check_output(['../cmake-build-release/src/Matrusse 2048 2048 '+bloc+' -m2'], shell=True).decode("utf-8")
        out = out.split(": ")
        p = out[1]
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
"""
Comparaison du temps des différents algos selon la taille de la matrice
"""
"""
tfinal=np.zeros((3,4))
k=[2048,4096,8192,16384]
ite=0

for j in k:
    for i in range (1,4):
        print(i)
        taille = str(j)
        version = str(i)
        out = sp.check_output(['../cmake-build-release/src/Matrusse '+taille+' '+taille+' 8 -m'+version], shell=True).decode("utf-8")
        out = out.split(": ")
        p = out[1]
        p = int(p)
        tfinal[i-1,ite]=p
    ite+=1

for i in [0,1,2]:
    plt.plot(k,tfinal[i])
"""
"""
Comparaison temps algo découpage en bloc selon la taille du découpage du bloc
"""

u = np.arange(500,1500,10)
O = []
for j in u:
    T=[]
    for i in range(2):
        k = str(int(0.75*log2(j)))
        bloc = str(j)
        out = sp.check_output(['../cmake-build-release/src/Matrusse 10000 10000 '+k+' -m2 '+bloc], shell=True).decode("utf-8")
        out = out.split(": ")
        p = out[1]
        p = int(p)
        T.append(p)
        moy = (sum(T)/len(T))
        print(i)
    O.append(moy)
    print(j)
plt.plot(u,O)

"""
Comparaison temps algo découpage en bloc selon la construction de la table de Gray
"""
"""
u = [128,256,512,1024,2048,4096,8192,16384]
O = []
P = []
for j in u:
    T=[]
    S=[]
    for i in range(3):
        taille = str(j)
        out = sp.check_output(['../cmake-build-release/src/Matrusse '+taille+' '+taille+' 7 -m2 1024'], shell=True).decode("utf-8")
        out = out.split(": ")
        p = out[1]
        p = int(p)
        T.append(p)
        moy = (sum(T)/len(T))
        out = sp.check_output(['../cmake-build-release/src/Matrusse '+taille+' '+taille+' 7 -m4'], shell=True).decode("utf-8")
        out = out.split(": ")
        p = out[1]
        p = int(p)
        S.append(p)
        moy2 = (sum(S)/len(S))
        print(i)
    O.append(moy)
    P.append(moy2)
    print(j)
plt.plot(u,O)
plt.plot(u,P)
"""