import subprocess as sp
import matplotlib.pyplot as plt
import numpy as np

#tab = []
#for j in range (5,12):
    #T=[]
    #for i in range (100):
        #bloc = str(j)
        #out = sp.check_output(['../src/cmake-build-release/Matrusse 256 256 '+bloc+' -m'], shell=True).decode("utf-8")
        #out = out.split(": ")
        #p = out[1]
        #p = int(p)
        #T.append(p)
        #moy = (sum(T)/len(T))
    #tab.append(moy)
#plt.plot([6,7,8,9,10,11,12],tab)

#import subprocess as sp
#import matplotlib.pyplot as plt
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
    
