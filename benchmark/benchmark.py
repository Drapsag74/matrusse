import subprocess as sp
import matplotlib.pyplot as plt

plt.clf()

tabf = []
for l in range(1,3):
    tab = []
    for j in range(8,17,2):
        T=[]
        for i in range (100):
            k = str(j)
            b = str(l)
            out = sp.check_output(['../src/cmake-build-release/Matrusse '+k+' 2048 -b='+b], shell=True).decode("utf-8")
            out = out.split(": ")
            p = out[1]
            p = p[0:len(p)-8]
            p = int(p)
            T.append(p)
            moy = (sum(T)/len(T))
        tab.append(moy)
    tabf.append(tab)

plt.plot([8, 10, 12, 14, 16], tabf[0])
plt.plot([8, 10, 12, 14, 16], tabf[1])