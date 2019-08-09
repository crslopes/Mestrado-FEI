import matplotlib.pyplot as plt
import matplotlib.pyplot as plt1
import matplotlib.pyplot as plt2
import pandas as pd
import pandas as pd1
import pandas as pd2
import time
import numpy as np
import scipy as sp
from random import *
from scipy import interpolate

def eucli_geo_mdc(n1, n2):
    if n1 > n2:  # 1                    (T(n)=1)
        maior = n1  # 1                 (T(n)=2)
        menor = n2  # 1                 (T(n)=3)
    else:
        maior = n2  # 1                 (T(n)=2)
        menor = n1  # 1                 (T(n)=3)
    resto = -1  # 1                     (T(n)=4)
    while resto != 0:  # n/2 +1         (T(n)=n/2+5)
        resto = maior -menor  # n/2     (T(n)=n+5)
        if resto>menor : # n/2          (T(n)=n/2+n+5)
            maior=resto # n/2           (T(n)=2n+5)
        else:
            maior=menor # n/2           (T(n)=n/2+n+5)
            menor=resto # n/2           (T(n)=2n+5)
        MDC = maior  #  # n/2           (T(n)=2n+n/2+5)
    return MDC        # 1               (T(n)=5n/2+6)

def eucli_div_mdc(dividendo,divisor,resto):
	while resto !=0:                    # n + 1     n+1
		dividendo = divisor#            n           2n+1
		divisor=resto#                  n           3n+1
		resto = dividendo % divisor#    n           4n+1
	return divisor# 1                        5n+2

def eucli_rec_mdc(dividendo,divisor,ret_resto):
    if ret_resto ==0:                    # n + 1     n+1
        return divisor
    else:
        return eucli_rec_mdc(divisor, ret_resto, divisor % ret_resto)

def main():

    print("Entre com os valores máximos e mínimos para encontrar o MDC")
    n1Orig = int(input("\nLimite inferior Número: "))
    n2Orig = int(input("\nLimite Superior Número: "))
    nMax = int(input("\nNúmero de amostras(n): "))+1
    grpEucliGeoPlot = []
    grpEucliDivPlot = []
    grpEucliRecPlot = []
    grpN = []
    grpPrimos=[]
    #grpPrimos.insert(19, (2 ** 82589933) - 1)
    #grpPrimos.insert(18, (2 ** 77232917) - 1)
    #grpPrimos.insert(17, (2 ** 74207281) - 1)
    #grpPrimos.insert(16, (2 ** 57885161) - 1)
    #grpPrimos.insert(15, (2 ** 43112609) - 1)
    #grpPrimos.insert(14, (2 ** 42643801) - 1)
    #grpPrimos.insert(13, (2 ** 37156667) - 1)
    #grpPrimos.insert(12, (2 ** 32582657) - 1)
    #grpPrimos.insert(11, (2 ** 30402457) - 1)
    grpPrimos.insert(10, (2 ** 25964951) - 1)
    grpPrimos.insert(9, 2996863034895 * (2 ** 1290000) + 1)
    grpPrimos.insert(8, 2996863034895 * (2 ** 1290000) - 1)
    grpPrimos.insert(7, 3756801695685 * (2 ** 666669) + 1)
    grpPrimos.insert(6, 3756801695685 * (2 ** 666669) - 1)
    grpPrimos.insert(5, 65516468355 * (2 ** 333333) + 1)
    grpPrimos.insert(4, 65516468355 * (2 ** 333333) - 1)
    grpPrimos.insert(3, 12770275971 * (2 ** 222225) + 1)
    grpPrimos.insert(2, 12770275971 * (2 ** 222225) - 1)
    grpPrimos.insert(1, 70965694293 * (2 ** 200006) + 1)
    grpPrimos.insert(0, 70965694293 * (2 ** 200006) - 1)

    # !/usr/bin/env python
    # -*- coding: utf-8 -*-
    #arq = open("primos.txt", 'r')
    #texto = arq.readlines()
    #j=0
    #for linha in texto:
    #    grpPrimos.insert(j, int(linha))
    #    nMax=j
    #    j=j=j+1
    #arq.close()
    j=1
    n1=n1Orig
    n2=n2Orig
    if n1 < n2:
        n2 = n1
        n1 = n2Orig
    for i in range(1, nMax):
        n1=grpPrimos[(i-1)]
        #n2=grpPrimos[i]
        grpN.insert(i, len(str(grpPrimos[i])))
        ini = time.time()
        ret_mdcDiv = eucli_div_mdc(n1, n2, n1 % n2)
        fim = time.time()
        TnDiv= (fim-ini)
        grpEucliDivPlot.insert(i, TnDiv)
        ini = time.time()
        #ret_mdcGeo = eucli_geo_mdc(n1, n2)
        #fim = time.time()
        #TnGeo= fim-ini
        #grpEucliGeoPlot.insert(i, TnGeo)
        ini = time.time()
        ret_mdcRec = eucli_rec_mdc(n1, n2, n1 % n2)
        fim = time.time()
        TnRec=(fim-ini)
        grpEucliRecPlot.insert(i, TnRec)
        #print(j," i= ",i, " - O MDC entre ", n1, " e ", n2, " é Enclides Original: ", ret_mdcGeo, " com TGeo(n)= ", TnGeo, " e Euclides Divisões Sucessivas é: ", ret_mdcDiv, " com TDiv(n) = ", TnDiv, " e Euclides Recursiva  é: ", ret_mdcRec, " com TRec(n) = ", TnRec,"\n")
        #print(j," i= ", i, " - O MDC entre ", n1, " e ", n2, " é Euclides Divisões Sucessivas é: ", ret_mdcDiv, " com TDiv(n) = ", TnDiv, " e Euclides Recursiva  é: ", ret_mdcRec, " com TRec(n) = ", TnRec, "\n")
        #print(" n1= ", n1, " - O MDC é Euclides Divisões Sucessivas é: ", ret_mdcDiv," e Euclides Recursiva  é: ", ret_mdcRec, " TnDiv:",TnDiv," TnRec:",TnRec,"\n")
        #j=j*100
        #n1 = (n1Orig *j + randint(1,n1Orig*j)*j*1000000000000000000000000000000000000000)

    #df = pd.DataFrame({'grpN':grpN,'EucliGeo':grpEucliGeoPlot,'EucliDiv':grpEucliDivPlot,'EucliRec':grpEucliRecPlot})
    df = pd.DataFrame({'grpN': grpN, 'EucliRec':grpEucliRecPlot, 'EucliDiv':grpEucliDivPlot})
    df1 = pd1.DataFrame({'EucliRec': grpEucliRecPlot})
    df2 = pd2.DataFrame({'EucliDiv':grpEucliDivPlot})
    #interpolado = interpolate.interp1d(grpN,grpEucliDivPlot);
    #plt.plot(np.linspace(1, 10, 10), interpolado(np.linspace(1, 10, 10)))
    #plt.show()
    #df = pd.DataFrame({'grpN': grpN, 'EucliDiv': grpEucliDivPlot, 'EucliRec': grpEucliRecPlot})
    ###df = pd.DataFrame({'grpN': grpN, 'EucliDiv': interpolado, 'EucliRec': grpEucliRecPlot})
    print(df)
    ax = plt.gca()
    ax1 = plt1.gca()
    ax2 = plt2.gca()
    ###df.plot(kind='line', x='grpN', y='EucliRec', ax=ax)
    df.plot(kind='line', x='grpN', y='EucliDiv', color='red', ax=ax)
    df.plot(kind='line', x='grpN', y='EucliRec', color='green', ax=ax)
    df1.plot(kind='line', color='red')
    df2.plot(kind='line', color='green')
    #df1.plot(kind='line', x='grpN', y='EucliDiv', color='red', ax=ax1)
    #df2.plot(kind='line', x='grpN', y='EucliRec', color='green', ax=ax2)
    #plt.title('MDC interativa x MDC Recursiva')
    #plt1.title('MDC interativa')
    #plt2.title('MDC Recursiva')
    plt.xlabel('Quantidade de n')
    plt1.xlabel('Quantidade de n')
    plt2.xlabel('Quantidade de n')
    plt.ylabel('Tempo T(n)')
    plt1.ylabel('Tempo T(n)')
    plt2.ylabel('Tempo T(n)')
    plt.show()
    plt1.show()
    plt2.show()

main()