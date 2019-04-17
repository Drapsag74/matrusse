import subprocess as sp
import matplotlib.pyplot as plt
import numpy as np

<<<<<<< HEAD
v=np.arange(6,15,1)
tab = []
for j in v:
    T=[]
    for i in range (3):
        bloc = str(j)
        out = sp.check_output(['../cmake-build-release/src/Matrusse 5000 5000 '+bloc+' -m1'], shell=True).decode("utf-8")
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
=======
tab = []
v = np.arange(1,20,1)
for j in v:
    T=[]
    for i in range (10):
        bloc = str(j)
        out = sp.check_output(['../cmake-build-release/src/Matrusse 6000 6000 '+bloc+' -m1'], shell=True).decode("utf-8")
        out = out.split(": ")
        p = out[1]
        p = int(p)
        T.append(p)
        moy = (sum(T)/len(T))
    tab.append(moy)
    
plt.plot(v,tab)



#import subprocess as sp
#import matplotlib.pyplot as plt
#tfinal=np.zeros((3,4))
#k=[2048,4096,8192,16384]
#ite=0

#for j in k:
    #for i in range (1,4):
        #print(i)
        #taille = str(j)
        #version = str(i)
        #out = sp.check_output(['../cmake-build-release/src/Matrusse '+taille+' '+taille+' 8 -m'+version], shell=True).decode("utf-8")
        #out = out.split(": ")
        #p = out[1]
        #p = int(p)
        #tfinal[i-1,ite]=p
    #ite+=1
    
#for z in range(0,3):
    #plt.plot(k, tfinal[z])
#plt.xlabel("Taille de la matrice carre")
#plt.ylabel("temps d'execution (en secondes)")
#plt.legend(['Matrusse V1', 'Matrusse V2', 'Matrusse Intrin'], loc='best')
>>>>>>> 72ab11e1a0a7ce81431c1d650afe51d9e6bfc476
