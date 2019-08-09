# !/usr/bin/env python
import matplotlib.pyplot as plt
import copy
import pandas as pd
import timeit
from random import *
import math
import numpy as np
from heapq import heappop, heappush

def partittionIndex(lista, E, D, pivo, I):
    if pivo > 0:
        i = randint(E, D)
        temp = I[E]
        I[E]=I[i]
        I[i] = temp
    x = lista[int(I[E])]
    i = E + 1
    j = D
    while i <= j:
        if lista[int(I[i])] > x:
            while i < j and lista[int(I[j])] > x:
                j -= 1
            temp = I[j]
            I[j] = I[i]
            I[i] = temp
            j -= 1
        i += 1
    if lista[int(I[j])] < x:
        temp = I[j]
        I[j] = int(I[E])
        I[E] = temp
    return lista, I, j

def quickSortIndex(lista,E,D,pivo_rand, I):
    if E<D:
        lista, I, limite=partittionIndex(lista,E,D,pivo_rand, I)
        if E < (limite-1):
            lista, I = quickSortIndex(lista,E,(limite-1),pivo_rand, I)
        if (limite+1)< D:
            lista, I = quickSortIndex(lista,(limite+1),D,pivo_rand, I)
    return lista, I

def get_minG(V,I):
    minG=0
    for i in range (0, len(I),1):
        if V[I[i]]<V[minG]: minG=i
    return minG


def Adj(u):
    Iu=np.full (len(u),0)
    for i in range (0,len(u),1):
        Iu[i]=i
    u, Iu = quickSortIndex(u, 0, len(Iu) - 1, 1, Iu)
    return Iu

def mst_primHeap(Gr,r):
    G=copy.deepcopy(Gr)
    Q=[]
    pai=[]
    Index=[]
    vermelho=[]
    D=[]
    Q.append(np.inf)
    pai.append(None)
    vermelho.append(0)
    heappush(D,(0,0))

    for i in range(1, len(G), 1):
        Q.append(np.inf)
        pai.append(None)
        Index.append(i)
        vermelho.append(0)
    pai[r]=None
    Q[r] = 0
    while len(D) > 0:
        Idx=heappop(D)
        u = G[Idx[1]]
        while(len(u)):
            aresta=heappop(u)
            if  aresta[1] in Index:
                if Q[aresta[1]] > aresta[0] :
                    pai[aresta[1]]=Idx[1]
                    Q[aresta[1]]=aresta[0]
                    heappush(D, (aresta[0], aresta[1]))
def mst_prim(Gr,r):
    G = copy.deepcopy(Gr)
    Q=np.full (len(G),np.inf)
    Index=np.full (len(G),0)
    pai = np.full(len(G), None)
    vermelho = np.full(len(G), 0)
    for i in range (0,len(G),1):
        Index[i]=i
    Q[r]=0
    pai[r]=None
    while len(Index)>0 and Q[int(Index[0])]<np.inf:
        if vermelho[int(Index[0])] < 1:
            Idx=get_minG(Q,Index)
            u = G[int(Idx)]
            vermelho[int(Idx)]=1 #marca como vertice concluido
            Iu=Adj(u)
            while len(Iu)>0 and u[Iu[0]] < np.inf:
                if  Iu[0] in Index:
                    if Q[Iu[0]] > u[Iu[0]] and Idx !=Iu[0]:
                        pai[Iu[0]]=Idx
                        Q[Iu[0]]=u[Iu[0]]
                Iu = Iu[1:]
        Index=Index[1:]
        u = get_minG(Q, Index)
    grafo = np.full((2,len(Q)), None)
    grafo[0]=Q
    grafo[1] = pai

def bf_dijkstra(Gr,r):
    G = copy.deepcopy(Gr)
    Q=np.full (len(G),np.inf)
    Index=np.full (len(G),0)
    pai = np.full(len(G), None)
    vermelho = np.full(len(G), 0)
    for i in range (0,len(G),1):
        Index[i]=i
    Q[r]=0
    pai[r]=None
    while len(Index)>0 and Q[int(Index[0])]<np.inf:
        if vermelho[int(Index[0])] < 1:
            Idx=get_minG(Q,Index)
            u = G[int(Idx)]
            Iu=Adj(u) #obtem vetores adjacentes
            #relax
            while len(Iu)>0 and u[Iu[0]] < np.inf: #após ordenar não entra nos ponteiros sem arestas
                if  Iu[0] in Index: #nós não podados
                    if Q[Iu[0]] > (u[Iu[0]]+Q[int(Idx)]) and Idx !=Iu[0]: #verifica valor com base na origem e destino
                        pai[Iu[0]]=Idx
                        Q[Iu[0]]=(u[Iu[0]]+Q[int(Idx)])
                Iu = Iu[1:] #realiza a poda
            vermelho[int(Idx)] = 1  # marca como vertice concluido
        Index=Index[1:]
        u = get_minG(Q, Index)

    grafo = np.full((2,len(Q)), None)
    grafo[0]=Q
    grafo[1] = pai

def bf_dijkstraHeap(Gr,r):
    G=copy.deepcopy(Gr)
    Q=[]
    pai=[]
    Index=[]
    vermelho=[]
    D=[]
    Q.append(np.inf)
    pai.append(None)
    vermelho.append(0)
    heappush(D,(0,0))

    for i in range(1, len(G), 1):
        Q.append(np.inf)
        pai.append(None)
        Index.append(i)
        vermelho.append(0)
    pai[r]=None
    Q[r] = 0
    while len(D) > 0:
        Idx=heappop(D)
        u = G[Idx[1]]
        while(len(u)):
            aresta=heappop(u)
            if  aresta[1] in Index:
                if Q[aresta[1]] > (aresta[0]+Q[Idx[1]]) :
                    pai[aresta[1]]=Idx[1]
                    Q[aresta[1]]=aresta[0]
                    heappush(D, ((aresta[0]+Q[Idx[1]]), aresta[1]))

def main():
    global Grafo
    global GrafoDen
    global Vertices
    global VerticesDen

    grp_PRIM=[]
    grp_Djkstra=[]
    grp_PRIM_den=[]
    grp_Djkstra_den=[]
    grp_PRIMHeap=[]
    grp_DjkstraHeap=[]
    grp_PRIMHeap_den = []
    grp_DjkstraHeap_den=[]

    inV= 1500#randint(2, 1000)
    inE =  inV#randint(2, inV)
    Vertices = []
    for n in range(2, inV, 10):
        inE = n  # randint(2, inV)
        Grafo = np.full((n, inE), np.inf)
        print("inV: ", n, " InE: ", inE)
        Vertices=[]
        VerticesDen = []
        for i in range(0,n, 1):
            Vertices.append([])
            VerticesDen.append([])

        for i in range(0, (n-1), 1):
            Grafo[i][(i+1)] = randint(1, 99)
            Grafo[(i+1)][i] = Grafo[i][(i+1)]
            heappush(Vertices[i],(Grafo[i][(i+1)],(i+1)))
            heappush(Vertices[(i+1)], (Grafo[i+1][i], i))

        GrafoDen = np.full((n, inE), np.inf)
        print("inV: ", n, " InE: ", inE)

        for i in range(0, (n-1), 1):
            for j in range(0, n, 1):
                if j!=i:
                    GrafoDen[i][j] = randint(1, 99)
                    a=GrafoDen[i][j]
                    GrafoDen[j][i] = GrafoDen[i][j]
                    heappush(VerticesDen[i], (a, j))
                    heappush(VerticesDen[j],(a, i))

        #print("normal")


#        tempo_PRIM = timeit.timeit(stmt="mst_prim(Grafo, 0)", setup="from __main__ import mst_prim, Grafo", number=10)
#        grp_PRIM.insert(n, tempo_PRIM)

#        tempo_bf_dijkstra = timeit.timeit(stmt="bf_dijkstra(Grafo, 0)", setup="from __main__ import bf_dijkstra, Grafo", number=10)
#        grp_Djkstra.insert(n, tempo_bf_dijkstra)

        tempo_PRIMHeap = timeit.timeit(stmt="mst_primHeap(Vertices, 0)", setup="from __main__ import mst_primHeap, Vertices", number=10)
        grp_PRIMHeap.insert(n, tempo_PRIMHeap)
        #print("Vertices: ", Vertices)

        tempo_bf_dijkstraHeap = timeit.timeit(stmt="bf_dijkstraHeap(Vertices, 0)", setup="from __main__ import bf_dijkstraHeap, Vertices", number=10)
        grp_DjkstraHeap.insert(n, tempo_bf_dijkstraHeap)


        #print("Denso")

#        tempo_PRIM_den = timeit.timeit(stmt="mst_prim(GrafoDen, 0)", setup="from __main__ import mst_prim, GrafoDen", number=10)
#        grp_PRIM_den.insert(n, tempo_PRIM_den)

#        tempo_bf_dijkstra_den = timeit.timeit(stmt="bf_dijkstra(GrafoDen, 0)", setup="from __main__ import bf_dijkstra, GrafoDen", number=10)
#        grp_Djkstra_den.insert(n, tempo_bf_dijkstra_den)

#        tempo_PRIMHeap_den = timeit.timeit(stmt="mst_primHeap(VerticesDen, 0)", setup="from __main__ import mst_primHeap, VerticesDen", number=10)
#        grp_PRIMHeap_den.insert(n, tempo_PRIMHeap_den)
        #print("VerticesDen: ", VerticesDen)

#        tempo_bf_dijkstraHeap_den = timeit.timeit(stmt="bf_dijkstraHeap(VerticesDen, 0)", setup="from __main__ import bf_dijkstraHeap, VerticesDen", number=10)
#        grp_DjkstraHeap_den.insert(n, tempo_bf_dijkstraHeap_den)


#    df = pd.DataFrame({'PRIM_Den': grp_PRIM_den, 'PRIM_Heap_Den': grp_PRIMHeap_den,'Djkstra_Den': grp_Djkstra_den, 'Djkstra_Heap_Den': grp_DjkstraHeap_den})


#    df = pd.DataFrame({'PRIM': grp_PRIM, 'PRIM_Heap': grp_PRIMHeap,'Djkstra': grp_Djkstra, 'Djkstra_Heap': grp_DjkstraHeap})

    #df = pd.DataFrame({'PRIM': grp_PRIM, 'PRIM_Heap': grp_PRIMHeap, 'Djkstra': grp_Djkstra, 'Djkstra_Heap': grp_DjkstraHeap, 'PRIM_Den': grp_PRIM_den, 'PRIM_Heap_Den': grp_PRIMHeap_den,'Djkstra_Den': grp_Djkstra_den, 'Djkstra_Heap_Den': grp_DjkstraHeap_den})

#    df = pd.DataFrame({'PRIM_Heap': grp_PRIMHeap, 'Djkstra_Heap': grp_DjkstraHeap, 'PRIM_Den': grp_PRIM_den, 'PRIM_Heap_Den': grp_PRIMHeap_den,'Djkstra_Den': grp_Djkstra_den, 'Djkstra_Heap_Den': grp_DjkstraHeap_den})

#    df = pd.DataFrame({'PRIM': grp_PRIM, 'PRIM_Den': grp_PRIM_den, 'PRIM_Heap': grp_PRIMHeap, 'PRIM_Heap_Den': grp_PRIMHeap_den})

#    df = pd.DataFrame({'PRIM_mAdj': grp_PRIM, 'PRIM_Heap': grp_PRIMHeap, 'PRIM_Den': grp_PRIM_den, 'PRIM_Heap_Den': grp_PRIMHeap_den,'Djkstra_mAdj': grp_Djkstra, 'Djkstra_Heap': grp_DjkstraHeap, 'Djkstra_Den': grp_Djkstra_den, 'Djkstra_Heap_Den': grp_DjkstraHeap_den})
#    df = pd.DataFrame({'PRIM_mAdj': grp_PRIM, 'PRIM_Heap': grp_PRIMHeap,'Djkstra_mAdj': grp_Djkstra, 'Djkstra_Heap': grp_DjkstraHeap})

    df = pd.DataFrame({ 'PRIM_Heap': grp_PRIMHeap,'Djkstra_Heap': grp_DjkstraHeap})


    df.plot()
    plt.xlabel('Quantidade de vertices x2')
    plt.ylabel('Tempo T(sec)')
    plt.show()

main()