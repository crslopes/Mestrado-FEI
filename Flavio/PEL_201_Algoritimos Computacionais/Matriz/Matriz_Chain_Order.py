# !/usr/bin/env python
import matplotlib.pyplot as plt
import copy
import pandas as pd
import timeit
from random import *
import math
import numpy as np

def multiplica_matriz(A,B):
    if len(A[0]) != len(B): return -1 # verifica se o numero de colunas de A é igual ao de colunas em B
    else:
        ln=len(A)
        Acol=len(A[0])
        col=len(B[0])
        C = np.empty((ln,col))
        for i in range(0,ln,1):
            for j in range(0,col,1):
                C[i][j]=0
                for k in range(0,Acol,1):
                    C[i][j]=C[i][j]+A[i][k]*B[k][j]
        return C

def multiplica_M_matriz(Matrizes,m,tm):
    if (tm-m) == 1: return Matrizes[m]
    A = Matrizes[m]
    B=[]
    B=multiplica_M_matriz(Matrizes,(m+1),tm)
    if len(A[0]) != len(B):
        return -1 # verifica se o numero de colunas de A é igual ao de linhas em B
    else:
        ln=len(A)
        Acol=len(A[0])
        col=len(B[0])
        C = np.empty((ln,col),dtype=int)
        for i in range(0,ln,1):
            for j in range(0,col,1):
                C[i][j]=0
                for k in range(0,Acol,1):
                    C[i][j]=C[i][j]+A[i][k]*B[k][j]
        return C

####   rotina de programação dinâmica para descobrir a menor quantidade de multiplicações  ########

def matriz_ordem_dinamica(MtzDimensoes):
    n=len(MtzDimensoes)
    m = np.full((n, n),np.inf)
    s = np.zeros((n, n), dtype=int)
    for i in range (0,n,1):
        m[i][i]=0
### quantidade de matrizes em L, varredura  bottom up
    for l in range (1,n,1):
######### varredura largura matriz inicial ‘i’
        for i in range(0,(n-l),1):
##########  varredura largura matriz final do subconjunto ‘j’
            j=i+l
##########  index k, divisão do conjunto de matrizes
            for k in range(i,j,1):
                q=m[i][k]+m[(k+1)][j]+(MtzDimensoes[i][0]*MtzDimensoes[k][1]*MtzDimensoes[j][1])
                if q < m[i][j]:
                    m[i][j]=int(q)
                    s[i][j]=int(k)
    return m, s

def Multiplica_ordem_Dinamica(A, s, i, j):
    if (i == j ):
        return A[i]
    if (j == i + 1 ):
        return multiplica_matriz(A[i],A[j])
    else:
        B1 = Multiplica_ordem_Dinamica(A, s, i, s[i][j])
        B2 = Multiplica_ordem_Dinamica(A, s, s[i][j] + 1, j)
        return multiplica_matriz(B1,B2)

####   que imprime ordem das matrizes a serem multiplicadas  ########

def print_matriz_otima(s,i,j):
    mtx=""
    if i==j:
        return " A"+str(int(i))+" "
    else:
        mtx=mtx+"("
        mtx=mtx+(print_matriz_otima(s, i,s[i][j]))
        mtx=mtx+(print_matriz_otima(s, s[i][j] +1, j))
        mtx=mtx+")"
    return mtx

def mede_interativo(Mtz):
    a = Mtz.Matrizes[0]
    for w in range(0, len(Mtz.Matrizes) - 1, 1):
        a = multiplica_matriz(a, Mtz.Matrizes[w + 1])
#    print("resultado mede_interativo", a)
    return

def mede_recursivo(Mtz):
    a = multiplica_M_matriz(Mtz.Matrizes,0,len(Mtz.Matrizes))
#    print("resultado mede_recursivo", a)
    return

def mede_PD(Mtz,m,s):
    resultado=Multiplica_ordem_Dinamica(Mtz.Matrizes, s, 0, len(s) - 1)
#    print (s)
#    print (m)
    txt= print_matriz_otima(s, 0, len(s) - 1)
    return

####   mecanismos para geração dos gráficos  ########

def mede_PD_calcula(Mtz):
    m, s = matriz_ordem_dinamica(Mtz.Dimensoes)
#    resultado=Multiplica_ordem_Dinamica(Mtz.Matrizes, s, 0, len(s) - 1)
    print (s)
    print (m)
    txt= print_matriz_otima(s, 0, len(s) - 1)
    print(txt)
    return


def main():
    global Matrizes
    global Mtz
    global m
    global s

    grp_interativo=[]
    grp_recursivo=[]
    grp_PD=[]
    grp_PD_calcula = []
    m=[]
    s=[]

####   formação aleatória de matrizes para gerar os gráficos ########
    qtMatriz= 20#Quantidade de Matrizes
    linhas =  3#Quantidade de Linhas na primeira matriz
    colunas = 2#Quantidade de colunas na segunda martri

    for qt in range(2, qtMatriz, 2):
    #if qtMatriz>0:
    #    qt=qtMatriz
        print ("Matriz tamanho: ",qt)
        class Mtz:
            Matrizes = [] # apontamento das matrizes
            Dimensoes=[]
            col=colunas
            ln=linhas
            #-----------Gera Matrizes para verificação, considera matriz subsequente sempre com a mesma quantidade de linhas que colunas da anterior
            for n in range(0, qt, 1):
                mtBase = np.zeros((ln, col), dtype=int)
                Dimensoes.append((ln, col))
                for i in range(0,ln, 1):
                    for j in range(0,col,1):
                        mtBase[i][j]=int(1)#randint(0)
                Matrizes.append(copy.deepcopy(mtBase))
                ln = copy.deepcopy(col)
                col =  randint(1,ln)
            #Dimensoes.append((30, 35))
            #Dimensoes.append((35, 15))
            #Dimensoes.append((15, 5))
            #Dimensoes.append((5, 10))
            #Dimensoes.append((10, 20))
            #Dimensoes.append((20, 25))

#            Dimensoes.append((5, 5))
#            Dimensoes.append((5, 5))
#            Dimensoes.append((5, 2))
#            Dimensoes.append((2, 4))
#            Dimensoes.append((4, 3))
#            Dimensoes.append((3, 2))
#            Dimensoes.append((2, 4))
#            Dimensoes.append((4, 6))
#            Dimensoes.append((6, 4))
#            Dimensoes.append((4, 4))

#        m, s = matriz_ordem_dinamica(Mtz.Dimensoes)

        tempo_recursivo = timeit.timeit(stmt="mede_recursivo(Mtz)", setup="from __main__ import mede_recursivo, Mtz", number=10)
        grp_recursivo.insert(qt, tempo_recursivo)

        tempo_interativo = timeit.timeit(stmt="mede_interativo(Mtz)", setup="from __main__ import mede_interativo, Mtz", number=10)
        grp_interativo.insert(qt, tempo_interativo)

#        tempo_PD_calcula = timeit.timeit(stmt="mede_PD_calcula(Mtz)", setup="from __main__ import mede_PD_calcula, Mtz", number=20)
#        grp_PD_calcula.insert(qt, tempo_PD_calcula)

#        tempo_PD = timeit.timeit(stmt="mede_PD(Mtz,m,s)", setup="from __main__ import mede_PD, Mtz,m,s", number=10)
#        grp_PD.insert(qt, tempo_PD)



#    df = pd.DataFrame({'Recursivo': grp_recursivo})
#    df = pd.DataFrame({'grp_PD_calcula': grp_PD_calcula})
#    df = pd.DataFrame({'Interativo': grp_interativo})
#    df = pd.DataFrame({'Multi Matrizes PD ': grp_PD})
#    df = pd.DataFrame({'Interativo': grp_interativo, 'Multi Matrizes PD ': grp_PD})
#    df = pd.DataFrame({'Recursivo': grp_recursivo, 'PD': grp_PD})
    df = pd.DataFrame({'Interativo': grp_interativo, 'Recursivo': grp_recursivo})
#    df = pd.DataFrame({'Interativo': grp_interativo, 'Recursivo': grp_recursivo, 'PD': grp_PD})
#    df = pd.DataFrame({'Interativo': grp_interativo, 'PD': grp_PD})
#    df = pd.DataFrame({'Interativo': grp_interativo, 'Recursivo': grp_recursivo, 'grp_PD_calcula': grp_PD_calcula})

    df.plot()
    plt.xlabel('Quantidade de 50x Matrizes')
    plt.ylabel('Tempo T(sec)')
    plt.show()

main()