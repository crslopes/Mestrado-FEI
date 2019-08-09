# !/usr/bin/env python
import matplotlib.pyplot as plt
import pandas as pd
import timeit
from random import *

foteBase=[]
#ordeStepSort = []
d=10


def merge(lista,E,D):
    i = 0
    j = 0
    k = 0
    while i < len(E) and j < len(D):
        if E[i] < D[j]:
            lista[k] = E[i]
            i = i + 1
        else:
            lista[k] = D[j]
            j = j + 1
        k = k + 1

    while i < len(E):
        lista[k] = E[i]
        i = i + 1
        k = k + 1

    while j < len(D):
        lista[k] = D[j]
        j = j + 1
        k = k + 1
    return lista

def mergeSort(lista):
    if len(lista)>1:
        mid = len(lista)//2
        E = lista[:mid]
        D = lista[mid:]

        mergeSort(E)
        mergeSort(D)
        lista = merge(lista,E, D)
    return lista

def insertSort(lista):
    for i in range(1, len(lista)):
        key = lista[i]
        # insere lista[j] na sequencia ordenada lista[1...j].
        j = i - 1
        while j >= 0 and  lista[j] > key:
            lista[j + 1] = lista[j]
            j -= 1
        lista[j + 1] = key
    return lista

def bubbleSort(lista):
    j=1
    while (len(lista)-j) >0:
        for i in range (0, (len(lista)-j)):
            if lista[i]>lista[i+1]:
                temp=lista[i]
                lista[i]=lista[i+1]
                lista[i+1]=temp
        j +=1
    return lista

def partittion(lista,E,D,pivo):
        if pivo > 0:
            i=randint(E, D)
            temp=lista[E]
            lista[E]=lista[i]
            lista[i]=temp
        x=lista[E]
        i=E+1
        j=D
        while i <= j:
            if lista[i] > x:
                while i<j and lista[j] > x:
                    j -=1
                temp = lista[j]
                lista[j] = lista[i]
                lista[i] = temp
                j -= 1
            i+=1
        if lista[j]<x:
            temp=lista[j]
            lista[j]=x
            lista[E]=temp
        return lista, j

def quickSort(lista,E,D,pivo_rand):
    if E<D:
        lista, limite=partittion(lista,E,D,pivo_rand)
        if E < (limite-1):
            lista = quickSort(lista,E,(limite-1),pivo_rand)
        if (limite+1)< D:
            lista = quickSort(lista,(limite+1),D,pivo_rand)
    return lista

def mede_quickSort(n):
    ordeSort = foteBase[:n]
    ordeSort = quickSort(ordeSort,0,len(ordeSort)-1,0)

def mede_rndquickSort(n):
    ordeSort = foteBase[:n]
    ordeSort = quickSort(ordeSort,0,len(ordeSort)-1,1)

def mede_insertSort(n):
    ordeSort = foteBase[:n]
    ordeSort = insertSort(ordeSort)

def mede_mergeSort(n):
    ordeSort = foteBase[:n]
    ordeSort = mergeSort(ordeSort)

def mede_bubbleSort(n):
    ordeSort= foteBase[:n]
    ordeSort=bubbleSort(ordeSort)

def main ():
    j=0
    arq = open("Sort/Subs_ordem_rev.txt", 'r')
    result=open("Sort/outSort.txt", 'w')
    linhas=arq.readlines()
    for linha in linhas:
        foteBase.insert(j,int(linha))
        j=j+1
    arq.close()

    grp_bubbleSort=[]
    grp_insertSort=[]
    grp_mergeSort = []
    grp_quickSort = []
    grp_rndquickSort = []

    n=70001
    for n in range(0,520000,10):
#        tempo_bubbleSort = timeit.timeit("mede_bubbleSort("+str(n)+")", "from __main__ import mede_bubbleSort", number=1)
#        print("bubbleSort com n =",str(n)," t= ", tempo_bubbleSort)
#        grp_bubbleSort.insert(n,tempo_bubbleSort)
#        tempo_insertSort = timeit.timeit("mede_insertSort("+str(n)+")", "from __main__ import mede_insertSort", number=1)
#        print("insertSort com n =",str(n)," t= ", tempo_insertSort)
#        grp_insertSort.insert(n, tempo_insertSort)
#        tempo_mergeSort = timeit.timeit("mede_mergeSort("+str(n)+")", "from __main__ import mede_mergeSort", number=1)
#        print("mergeSort com n =",str(n)," t= ", tempo_mergeSort)
#        grp_mergeSort.insert(n, tempo_mergeSort)
#        tempo_quickSort = timeit.timeit("mede_quickSort("+str(n)+")", "from __main__ import mede_quickSort", number=10)
#        print("quickSort com n =",str(n)," t= ", tempo_quickSort)
#        grp_quickSort.insert(n, tempo_quickSort)
        tempo_rndquickSort = timeit.timeit("mede_rndquickSort("+str(n)+")", "from __main__ import mede_rndquickSort", number=10)
        print("rndquickSort com n =",str(n)," t= ", tempo_rndquickSort)
        grp_rndquickSort.insert(n, tempo_rndquickSort)


    #    df = pd.DataFrame({'bubbleSort': grp_bubbleSort, 'insertSort': grp_insertSort, 'mergeSort': grp_mergeSort, 'quickSort': grp_quickSort, 'rndquickSort': grp_rndquickSort})
#    df = pd.DataFrame({'quickSort': grp_quickSort, 'rndquickSort': grp_rndquickSort,'bubbleSort': grp_bubbleSort})
    df = pd.DataFrame({'rndquickSort': grp_rndquickSort})

    df.plot()
    plt.xlabel('Quantidade de 10*n ')
    plt.ylabel('Tempo T(sec)')
    plt.show()


    #ordeQuickSort = quickSort(ordeQuickSort,0,len(ordeQuickSort)-1,0)
    #ordeRandQuickSort = quickSort(ordeRandQuickSort,0,len(ordeRandQuickSort)-1,1)
    #print(ordeQuickSort)
    #for j in range(0, d):
    #    result.write(str(ordeBubbleSort[j])+"\n")
    #print("Sorted array is completed")
    #result.close()

main()



