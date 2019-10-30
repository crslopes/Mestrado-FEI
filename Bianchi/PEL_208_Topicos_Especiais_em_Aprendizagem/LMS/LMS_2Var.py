# !/usr/bin/env python
import xlrd                     #biblioteca para leitura de arquivos excel
import matplotlib.pyplot as plt #biblioteca para plotar graficos
from mpl_toolkits.mplot3d import Axes3D
import pandas as pd             #biblioteca para criacao de dataframes, auxiliar para os graficos
import numpy as np
##-------------------------------------------------------------------
##      PEL_208 2º. Semestre de 2019
##      Prof: Dr Reinaldo Bianchi
##      Aluno: Cristiano Lopes Moreira
##      RA: 119103-0
##
##      Regressão Linear - Multi Variáveis
##          - Metodo dos Minimos Quadrados (LMS) Simples
##          - Metodo dos Minimos Quadrados (LMS) Quadrático
##          - Metodo dos Minimos Quadrados (LMS) Robusto (com pesos)
##
##-------------------------------------------------------------------

## Rotina para multiplicação de 2 matrizes, com o número de colunas da matriz A igual ao número de linhas da matriz B
## Recebe 2 Matrizes (nXm) e (mX?) e retorna uma matriz (nx?)
def multiplica_matriz(A,B):
    if len(A[0]) != len(B): return -1 # verifica se o numero de colunas de A é igual ao de linhas em B
    else:
        ln=len(A)               # numero de linhas da matriz A
        Acol=len(A[0])          # numero de colunas da matriz A
        col=len(B[0])           # numero de colunas da matriz B
        C = np.empty((ln,col))  # cria matriz C vazia com numero de linhas da matriz A e numero de colunas da matriz B
        # laço for para multiplicacao e soma de cada Coluna de uma linha da matriz A pelas Linhas da matriz B
        for i in range(0,ln,1):
            for j in range(0,col,1):
                C[i][j]=0
                for k in range(0,Acol,1):
                    C[i][j]=C[i][j]+A[i][k]*B[k][j]
        return C

## Rotina para gerar a Matriz transposta, transforma as linhas das de uma matriz em colunas na matriz reposta
## Recebe uma matriz A (nXm) e retorna uma matriz (mxn)
def matriz_transposta(A):
    ln=len(A)                   # numero de linhas da matriz A
    col=len(A[0])               # numero de colunas da matriz A
    C = np.empty((col,ln))      # cria matriz C vazia com numero de linhas igual ao numero de colunas da matriz A e numero de linhas igual ao numero de colunas da matriz A
    # laço para a transposicao, linha = coluna
    for i in range(0,ln,1):
        for j in range(0,col,1):
            C[j][i]=A[i][j]
    return C

## Rotina para para calcular o determinante de uma matriz
## Recebe uma matriz A (nXm) e retorna o valor numérico do determinante
def matriz_determinante(A):
    ln = len(A)      # numero de linhas da matriz A
    col = len(A[0])  # numero de colunas da matriz A
    ### Para matrizes de apenas 1 elemento o determinante é o prório elemento
    if ln ==  1:
        determinante = A[0][0]
    ### Para matrizes de apenas 2 elementos o determinante é calculado pela regra da diferença do produto da diagonal principal com o produto da diagonal secundária
    elif ln ==  2:
        determinante = A[0][0]*A[1][1]-A[0][1]*A[1][0]
    else:
    ### Para matrizes com mais de dois elementos o algoritmo realiza o Teorema de Laplace com chamadas das matrizes reduzidas pelos cofatores
        determinante=0
        for j in range(0,col,1):
            determinante=determinante+A[0][j]*matriz_cofator(A,0,j)
    return determinante

## Rotina para para calcular o complemento algebrico (cofator) de uma matriz
## Recebe uma matriz A (nXm) e coordenada que deseja o cofator e retorna o valor numérico do cofator
def matriz_cofator(A,i,j):
    ln = len(A)      # numero de linhas da matriz A
    col = len(A[0])  # numero de colunas da matriz A
    indexl=0    #index para ancora a ser utilizados na formacao da matriz reduzida
    indexc=0    #index para ancora a ser utilizados na formacao da matriz reduzida
    # Variavel para matriz reduzida para a formacao do cofator
    Cof = np.empty(((ln-1), (col-1)))
    # laço duplo de for para redução da matriz, removendo a linha e coluna em que o cofator se encontra (reduçao das matrizes pelo teorema de Laplace)
    for l in range(0,ln,1):
        # verifica se a linha é a linha do cofator para ser removida
        if l == i:
            indexl=1
        else:
            for k in range(0,col,1):
                # verifica se a coluna é a coluna do cofator para ser removida
                if k == j:
                    indexc=1
                else:
                # formacao da matriz reduzida
                    Cof[(l-indexl)][(k-indexc)]=A[l][k]
            indexc = 0
    # realiza a chamada da rotina de calculo do determinante com a matriz reduzida, inicia um ciclo de chamadas recursivas entre cofator e determinante
    determinanteC = matriz_determinante(Cof)
    # calculo do cafator segundo o teorema de Laplace
    cofator=((-1)**((i+1)+(j+1))) * determinanteC
    return cofator

## Rotina para formacao da matriz de cofatores (matriz Adjacente), utilizada no calculo da Matriz Inversa
## Recebe uma matriz A e retorna uma matriz de cofatores
def matriz_Adj(A):
    ln = len(A)         # numero de linhas da matriz A
    col = len(A[0])     # numero de colunas da matriz A
    # Variavel C para matriz de cofatores
    C = np.empty(((ln), (col)))
    for i in range(0,ln,1):
        for j in range(0,col,1):
    # chama a rotina para obter o cofator de cada ponto da matriz
            C[i][j]=matriz_cofator(A,i,j)
    # a matriz de cofatores eh uma transposta, antes de retornar a matriz de cofatores, realiza a transposta
    MTC=matriz_transposta(C)
    return MTC

## Rotina para formacao da matriz inversa
## Recebe uma matriz A e retorna a matriz inversa A^-1
def matriz_Inversa(A):
    ln = len(A)  # numero de linhas da matriz A
    col = len(A[0])  # numero de colunas da matriz A
    # Variavel Adj para matriz de cofatores - chama a rotina matriz Adj
    Adj=matriz_Adj(A)
    # Calcula o Determinante da Matriz A para utilizar no calculo da inversa sendo A^-1=Adj(A)/Det(A)
    DetA=matriz_determinante(A)
    MtInversa = np.empty(((ln), (col)))
    # laco para calcular cada elemento da matriz inversa pela formula  A^-1=Adj(A)/Det(A)
    for i in range(0,ln,1):
        for j in range(0, col, 1):
            MtInversa[i][j] = Adj[i][j]*(1/DetA)
    return MtInversa

def main():
    ############################ leitura da base de dados pelo arquivo Excel ############################
    ###########Formato Primeira do arquivo Excel linha nome das variáveis, Y, X, X^2
    ###########Primeira coluna, variáveil dependente Y, segunda coluna v
    ###########Segunda coluna, variáveil explicativa X
    ###########Terceira coluna, variáveil explicativa X^2 ou outras variaveis explicativas
    import xlrd
    book = xlrd.open_workbook("bianchiDbAula1MultiVariada.xlsx")
    print ("Número de abas: ", book.nsheets)
    print ("Nomes das Planilhas:", book.sheet_names())
    sh = book.sheet_by_name("Books")
    labelChart=sh.name
    labelZ = sh.cell_value(rowx=0, colx=0)
    labelX=sh.cell_value(rowx=0, colx=1)
    labelY = sh.cell_value(rowx=0, colx=2)
    qtElementos=sh.nrows
    qtX=3
    grp_XReal = []
    grp_YReal = []
    grp_ZReal = []
    ################ Matrizes para carregar as informaçoes das bases de dados ##########################
    XLinear = np.empty(((qtElementos - 1), 3))  #Matriz das variáveis explicativa X
    XQuad = np.empty(((qtElementos - 1), 5))  #Matriz das variáveis explicativa X para modelo de regressao quadratica
    Y = np.empty(((qtElementos - 1), 1))  # Matriz das variáveis dependente Y

    for i in range (1,qtElementos,1):
        ################### Carrega Variável dependente Y ############################################
        Y[(i-1)][0]=sh.cell_value(rowx=i, colx=0)
        ################### Carrega Variável explicativa X1 e X2 #######################################
        XLinear[(i - 1)][0] = 1   # Add 1 - "BIAS"
        XLinear[(i - 1)][1] = sh.cell_value(rowx=i, colx=1)
        XLinear[(i - 1)][2] = sh.cell_value(rowx=i, colx=2)
        ################### Carrega Variável explicativa X para modelo quadratico #####################
        XQuad[(i - 1)][0] = 1   # Add 1 - "BIAS"
        XQuad[(i - 1)][1] = sh.cell_value(rowx=i, colx=1)
        XQuad[(i - 1)][2] = sh.cell_value(rowx=i, colx=2)
        XQuad[(i - 1)][3] = sh.cell_value(rowx=i, colx=3)
        XQuad[(i - 1)][4] = sh.cell_value(rowx=i, colx=4)

        ################# Valores das amostras para apresentar no gráfico
        grp_ZReal.append(sh.cell_value(rowx=i, colx=0))
        grp_XReal.append(sh.cell_value(rowx=i, colx=1))
        grp_YReal.append(sh.cell_value(rowx=i, colx=2))


    ################               LMS  Linear            ###################################
    XLinearT=matriz_transposta(XLinear)                 # Matriz X transposta
    XLinearTXLinear=multiplica_matriz(XLinearT,XLinear) # Matriz X transposta multiplicada pela Matriz X
    XLinearTY=multiplica_matriz(XLinearT,Y)             # Matriz X transposta multiplicada pela Matriz Y
    XLinearTI = matriz_Inversa(XLinearTXLinear)         # Matrix inversa (XT*X)
    βXLinear=multiplica_matriz(XLinearTI,XLinearTY)     # Fatores da regressao LMS
    print("βXLinear:",βXLinear)
    ########################################################################################

    ################               LMS Robusta            ##################################
    W = np.empty((qtElementos - 1, 1))                  # cria matriz W de pesos para robusta
    WXLinear = np.empty((qtElementos - 1, 3))           # cria matriz WXLinear X ponderados
    WY = np.empty((qtElementos - 1, 1))                 # cria matriz WY para Y ponderados
    yRegresaaoXLinear = multiplica_matriz(XLinear, βXLinear) # regressao linear de X utilizada para obter pesos de W
    ######Laço for para obter os pesos de W pela interação com a regressao linear de X#####
    for i in range(0,len(Y),1):
        W[i]= abs(1/(Y[i]-yRegresaaoXLinear[i]))        # Peso W = |1/(Y-y)|
        WXLinear[i][0]=W[i]
        WXLinear[i][1]=W[i]*XLinear[i][1]
        WXLinear[i][2] = W[i] * XLinear[i][2]
        WY[i][0]=W[i]*Y[i][0]
    XLinearTWZ=multiplica_matriz(XLinearT,WXLinear)     # Matriz XLinearT transposta multiplicada pela Matriz WXLinear
    XLinearTWY=multiplica_matriz(XLinearT,WY)           # Matriz XLinearT transposta multiplicada pela Matriz WY
    XLinearTWI = matriz_Inversa(XLinearTWZ)             # Matriz inversa (XLinearTWZ*WX)
    βXLinearRob=multiplica_matriz(XLinearTWI,XLinearTWY)# Fatores da regressao por minimo
    print("βXLinearRob:",βXLinearRob)
    #########################################################################################

    ################               LMS  Quadratica            ###############################
    XQuadT=matriz_transposta(XQuad)                     # Matriz XQuad transposta
    XQuadTXQuad=multiplica_matriz(XQuadT,XQuad)         # Matriz XQuad transposta multiplicada pela Matriz XQuad
    XQuadTY=multiplica_matriz(XQuadT,Y)                 # Matriz XQuad transposta multiplicada pela Matriz Y
    XQuadTI = matriz_Inversa(XQuadTXQuad)               # Matriz inversa (XQuadTI*XQuadTY)
    βXQuad=multiplica_matriz(XQuadTI,XQuadTY)           # Fatores da regressao por minimo
    print("βXQuad:",βXQuad)
    #####################Variáveis para formacao dos graficos################################
    grp_3dX=[]
    grp_3dY=[]
    grp_Lin3dZ = []
    grp_LinRob3dZ = []
    grp_Quad3dZ = []
    for index in range(0, 8, 1):
        for indexj in range(0, 25, 1):
    ################## Prepara Gráfico Regressao 3D Linear ##################################
            varXYLin = np.empty((1, 3), int)
            varXYLin[0][0] = 1
            varXYLin[0][1] = index
            varXYLin[0][2] = indexj
            #varXY[0][3] = index**2
            #varXY[0][4] = indexj**2
            yRegresaaoXYLin = multiplica_matriz(varXYLin, βXLinear)
            grp_3dX.insert(index, index)
            grp_3dY.insert(index, indexj)
            grp_Lin3dZ.insert(index, yRegresaaoXYLin[0][0])
    ################## Prepara Gráfico Regressao 3D LinearRobusto ##################################
            yRegresaaoXYLinRob = multiplica_matriz(varXYLin, βXLinearRob)
            grp_LinRob3dZ.insert(index, yRegresaaoXYLinRob[0][0])
    ################## Prepara Gráfico Regressao 3D Quadratica ##################################
            varXYQuad = np.empty((1, 5), int)
            varXYQuad[0][0] = 1
            varXYQuad[0][1] = index
            varXYQuad[0][2] = indexj
            varXYQuad[0][3] = index**2
            varXYQuad[0][4] = indexj**2
            yRegresaaoXYQuad = multiplica_matriz(varXYQuad, βXQuad)
            grp_Quad3dZ.insert(index, yRegresaaoXYQuad[0][0])

    # Plot the surface.
    fig = plt.figure()
    #ax = fig.add_subplot(1,2,1, projection='3d')
    ax = fig.add_subplot(111, projection='3d')
    ax.set_title('LMS - Linear')
    ax.plot_trisurf(grp_3dX, grp_3dY, grp_Lin3dZ, linewidth=0.1, antialiased=True)

    for i in range(0, (qtElementos-1), 1):
        ax.scatter(grp_XReal[i], grp_YReal[i], grp_ZReal[i], c='r', marker='^')
    ax.set_xlabel('X Books')
    ax.set_ylabel('Y Attend')
    ax.set_zlabel('Z Grade')

    plt.show()
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.set_title('LMS - Robusto')
    ax.plot_trisurf(grp_3dX, grp_3dY, grp_LinRob3dZ, linewidth=0.1, antialiased=True)

    for i in range(0, (qtElementos-1), 1):
        ax.scatter(grp_XReal[i], grp_YReal[i], grp_ZReal[i], c='r', marker='^')
    ax.set_xlabel('X Books')
    ax.set_ylabel('Y Attend')
    ax.set_zlabel('Z Grade')

    plt.show()

    # Plot the surface.
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.set_title('LMS - Quadratica')
    ax.plot_trisurf(grp_3dX, grp_3dY, grp_Quad3dZ, linewidth=0.1, antialiased=True)

    for i in range(0, (qtElementos-1), 1):
        ax.scatter(grp_XReal[i], grp_YReal[i], grp_ZReal[i], c='r', marker='^')
    ax.set_xlabel('X Books')
    ax.set_ylabel('Y Attend')
    ax.set_zlabel('Z Grade')

    plt.show()

main()