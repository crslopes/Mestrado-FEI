import matplotlib.pyplot as plt
import math
from tabulate import tabulate
from random import *
def eucli_div_mdc(dividendo,divisor,resto,Tn):
	while resto !=0:                    # n + 1     n+1
		dividendo = divisor#            n           2n+1
		divisor=resto#                  n           3n+1
		resto = dividendo % divisor#    n           4n+1
		Tn=Tn+5#                        n           5n+1
	return divisor, Tn# 1                           5n+2


def main():
        print("Entre com os valores máximos e mínimos para encontrar o MDC")
        n1orig=int(input("\nLimite inferior Número: "))
        n2orig=int(input("\nLimite Superior Número: "))
        nMax=int(input("\nNúmero de amostras(n): "))
        
        grpPlot=[]
        grpN=[]
        Tn=2
        for i in range(1,nMax):
                #n1=randint(1,n1orig)
                #n2=randint(1,n2orig)
                a = i
                n1=n1orig
                n2=n2orig*i
                #grpPlot[1].insert(i,a)
                if n1 > n2:
                    dividendo = n1
                    divisor = n2
                else:
                    dividendo = n2
                    divisor = n1
                resto = -1
                Tn = 5

                (ret_mdc,Tn)=eucli_div_mdc(dividendo,divisor,dividendo%divisor,Tn)
                grpPlot.insert(i,Tn)
                #if i==0:grpPlot[0].insert(i,Tn)
                #grpN.insert(i,i)
                #if i==0:grpPlot.insert(i,Tn)
                #else: grpPlot[0].insert(i,Tn+grpPlot[0][i-1])
                #else: grpPlot.insert(i,Tn+grpPlot[i-1])
                print("O MDC entre ", n1, " e ", n2, " é ", ret_mdc, "\n T(n)=",Tn)
                print (grpPlot)
        #plt.plot (grpPlot[0])
        #plt.plot (grpPlot[1])
        #print(tabulate(grpN,grpPlot, headers=['N','Age'], tablefmt='orgtbl'))
        #print(tabulate([['Alice', 24], ['Bob', 19]], headers=['Name', 'Age'], tablefmt='orgtbl'))
        print("n|ciclos")
        for i in range(0, len(grpN)):
            print(grpN[i],"|",grpPlot[i],"\n")

        plt.plot (grpPlot)
        plt.title('MDC interativa x MDC Recursiva')
        plt.xlabel('Quantidade de n')
        plt.ylabel('Tempo T(n)')
        plt.show()
                
        
main()

