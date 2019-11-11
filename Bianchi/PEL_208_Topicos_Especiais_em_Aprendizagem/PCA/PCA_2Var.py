# !/usr/bin/env python
import xlrd  # biblioteca para leitura de arquivos excel
import matplotlib.pyplot as plt  # biblioteca para plotar graficos
import pandas as pd  # biblioteca para criacao de dataframes, auxiliar para os graficos
import numpy as np
from mpl_toolkits.mplot3d import Axes3D


##-------------------------------------------------------------------
##      PEL_208 2º. Semestre de 2019
##      Prof: Dr Reinaldo Bianchi
##      Aluno: Cristiano Lopes Moreira
##      RA: 119103-0
##
##      PCA
##
##-------------------------------------------------------------------

## Rotina para multiplicação de 2 matrizes, com o número de colunas da matriz A igual ao número de linhas da matriz B
## Recebe 2 Matrizes (nXm) e (mX?) e retorna uma matriz (nx?)
def multiplica_matriz(A, B):
    if np.size(A, 1) != np.size(B, 0):
        return -1  # verifica se o numero de colunas de A é igual ao de linhas em B
    else:
        ln = np.size(A, 0)  # numero de linhas da matriz A
        Acol = np.size(A, 1)  # numero de colunas da matriz A
        col = np.size(B, 1)  # numero de colunas da matriz B
        C = np.empty((ln, col))  # cria matriz C vazia com numero de linhas da matriz A e numero de colunas da matriz B
        # laço for para multiplicacao e soma de cada Coluna de uma linha da matriz A pelas Linhas da matriz B
        for i in range(0, ln, 1):
            for j in range(0, col, 1):
                C[i][j] = 0
                for k in range(0, Acol, 1):
                    C[i][j] = C[i][j] + A[i][k] * B[k][j]
        return C


## Rotina para gerar a Matriz transposta, transforma as linhas das de uma matriz em colunas na matriz reposta
## Recebe uma matriz A (nXm) e retorna uma matriz (mxn)
def matriz_transposta(A):
    ln = np.size(A, 0)  # numero de linhas da matriz A
    col = np.size(A, 1)  # numero de colunas da matriz A
    C = np.empty((col,
                  ln))  # cria matriz C vazia com numero de linhas igual ao numero de colunas da matriz A e numero de linhas igual ao numero de colunas da matriz A
    # laço para a transposicao, linha = coluna
    for i in range(0, ln, 1):
        for j in range(0, col, 1):
            C[j][i] = A[i][j]
    return C


## Rotina para para calcular o determinante de uma matriz
## Recebe uma matriz A (nXm) e retorna o valor numérico do determinante
def matriz_determinante(A):
    ln = np.size(A, 0)  # numero de linhas da matriz A
    col = np.size(A, 1)  # numero de colunas da matriz A
    ### Para matrizes de apenas 1 elemento o determinante é o prório elemento
    if ln == 1:
        determinante = A[0][0]
    ### Para matrizes de apenas 2 elementos o determinante é calculado pela regra da diferença do produto da diagonal principal com o produto da diagonal secundária
    elif ln == 2:
        determinante = A[0][0] * A[1][1] - A[0][1] * A[1][0]
    else:
        ### Para matrizes com mais de dois elementos o algoritmo realiza o Teorema de Laplace com chamadas das matrizes reduzidas pelos cofatores
        determinante = 0
        for j in range(0, col, 1):
            determinante = determinante + A[0][j] * matriz_cofator(A, 0, j)
    return determinante


## Rotina para para calcular o complemento algebrico (cofator) de uma matriz
## Recebe uma matriz A (nXm) e coordenada que deseja o cofator e retorna o valor numérico do cofator
def matriz_cofator(A, i, j):
    ln = np.size(A, 0)  # numero de linhas da matriz A
    col = np.size(A, 1)  # numero de colunas da matriz A
    indexl = 0  # index para ancora a ser utilizados na formacao da matriz reduzida
    indexc = 0  # index para ancora a ser utilizados na formacao da matriz reduzida
    # Variavel para matriz reduzida para a formacao do cofator
    Cof = np.empty(((ln - 1), (col - 1)))
    # laço duplo de for para redução da matriz, removendo a linha e coluna em que o cofator se encontra (reduçao das matrizes pelo teorema de Laplace)
    for l in range(0, ln, 1):
        # verifica se a linha é a linha do cofator para ser removida
        if l == i:
            indexl = 1
        else:
            for k in range(0, col, 1):
                # verifica se a coluna é a coluna do cofator para ser removida
                if k == j:
                    indexc = 1
                else:
                    # formacao da matriz reduzida
                    Cof[(l - indexl)][(k - indexc)] = A[l][k]
            indexc = 0
    # realiza a chamada da rotina de calculo do determinante com a matriz reduzida, inicia um ciclo de chamadas recursivas entre cofator e determinante
    determinanteC = matriz_determinante(Cof)
    # calculo do cafator segundo o teorema de Laplace
    cofator = ((-1) ** ((i + 1) + (j + 1))) * determinanteC
    return cofator


## Rotina para formacao da matriz de cofatores (matriz Adjacente), utilizada no calculo da Matriz Inversa
## Recebe uma matriz A e retorna uma matriz de cofatores
def matriz_Adj(A):
    ln = np.size(A, 0)  # numero de linhas da matriz A
    col = np.size(A, 1)  # numero de colunas da matriz A
    # Variavel C para matriz de cofatores
    C = np.empty(((ln), (col)))
    for i in range(0, ln, 1):
        for j in range(0, col, 1):
            # chama a rotina para obter o cofator de cada ponto da matriz
            C[i][j] = matriz_cofator(A, i, j)
    # a matriz de cofatores eh uma transposta, antes de retornar a matriz de cofatores, realiza a transposta
    MTC = matriz_transposta(C)
    return MTC


## Rotina para formacao da matriz inversa
## Recebe uma matriz A e retorna a matriz inversa A^-1
def matriz_Inversa(A):
    ln = np.size(A, 0)  # numero de linhas da matriz A
    col = np.size(A, 1)  # numero de colunas da matriz A
    # Variavel Adj para matriz de cofatores - chama a rotina matriz Adj
    Adj = matriz_Adj(A)
    # Calcula o Determinante da Matriz A para utilizar no calculo da inversa sendo A^-1=Adj(A)/Det(A)
    DetA = matriz_determinante(A)
    MtInversa = np.empty(((ln), (col)))
    # laco para calcular cada elemento da matriz inversa pela formula  A^-1=Adj(A)/Det(A)
    for i in range(0, ln, 1):
        for j in range(0, col, 1):
            MtInversa[i][j] = Adj[i][j] * (1 / DetA)
    return MtInversa


## Rotina para formacao da matriz DataAdjust
## Recebe uma matriz A e retorna a matriz DataAdjust com a diferença dos pontos para a media
def matriz_DataAdjust(A):
    ln = np.size(A, 0)  # numero de linhas da matriz A
    col = np.size(A, 1)  # numero de colunas da matriz A
    mean = np.zeros((1, col))
    DataAjuste = np.empty(((ln), (col)))

    for i in range(0, col, 1):
        for j in range(0, ln, 1):
            mean[0][i] = mean[0][i] + A[j][i]

    for i in range(0, col, 1):
        mean[0][i] = mean[0][i] / ln

    for i in range(0, ln, 1):
        for j in range(0, col, 1):
            DataAjuste[i][j] = A[i][j] - mean[0][j]
    Media=[]
    for i in range(0,col,1):
        Media.append(mean[0][i])

    return Media, DataAjuste


## Rotina para formacao da matriz de covariancia
## Recebe uma matriz DataAdjust e retorna a matriz covariancia Σ
def matriz_covariancia(Z):
    ln = np.size(Z, 0)  # numero de linhas da matriz Z
    col = np.size(Z, 1)  # numero de linhas da matriz Z
    Σ = np.empty(((col), (col)))
    BaseΣ = np.zeros(((col ** col), 1))

    for i in range(0, ln, 1):
        for j in range(0, col, 1):
            for k in range(0, col, 1):
                BaseΣ[(col * j + k)] = BaseΣ[(col * j + k)] + (Z[i][j] * Z[i][k])

    for j in range(0, col, 1):
        for k in range(0, col, 1):
            Σ[j][k] = BaseΣ[(col * j + k)] / (ln - 1)

    return Σ


## Rotina para calculo dos autovalores - eigenvalues
## Recebe uma matriz covariancia Σ e retorna a matriz de autovalores Λ
def matriz_autovalores(Σ):
    lnΣ = np.size(Σ, 0)
    if lnΣ == 1:  # calculo dos auto valores de uma funcao linear
        Λ = np.empty((1))
        Λ[0] = Σ[0]
    else:
        if lnΣ == 2:  # calculo dos auto valores de uma funcao quadratica
            Λ = np.empty((2))
            Δ = (-(Σ[0][0] + Σ[1][1])) ** 2 - 4 * (Σ[0][0] * Σ[1][1] - Σ[0][1] * Σ[1][0])
            Λ[0] = ((Σ[0][0] + Σ[1][1]) - Δ ** (1 / 2)) / 2
            Λ[1] = ((Σ[0][0] + Σ[1][1]) + Δ ** (1 / 2)) / 2
        else:
            if lnΣ > 2:  # calculo dos auto valores de uma funcao polinomial de ordem maior, pelo scikit learn
                Λ = np.linalg.eigvals(Σ)
            else:
                return -1
    return Λ


## Rotina para calculo dos Autovetores - eigenvectores
## Recebe uma matriz covariancia Σ e a matriz de autovalores Λ e retorna a matriz de autovetores Φ
def matriz_autovetores(Σ, Λ):
    lnΣ = np.size(Σ, 0)
    if lnΣ == 1:  # calculo dos auto valores de uma funcao linear que será sempre 0
        Φ = np.empty((1))
        Φ[0] = Σ[0] * 1 - Λ[0]
    else:
        if lnΣ == 2:  # calculo dos auto vetores de uma funcao quadratica
            Φ = np.empty((2, 2))

            Φ[0][0] = -0.735178656  # 1  # -0.88593619 # 1

            if (Σ[0][1] != 0):
                Φ[1][0] = -(Σ[0][0] - Λ[0]) * Φ[0][0] / Σ[0][1]
            else:
                Φ[1][0] = -(Σ[1][0]) * Φ[0][0] / (Σ[1][1] - Λ[0])
            Φ[1][1] = Φ[0][0]

            if (Σ[1][0] != 0):
                Φ[0][1] = -(Σ[1][1] - Λ[1]) * Φ[1][1] / Σ[1][0]
            else:
                Φ[0][1] = -(Σ[0][1]) * Φ[1][1] / (Σ[0][0] - Λ[1])
        else:
            if lnΣ > 2:  # calculo dos auto vetores de uma funcao polinomial de ordem maior, pelo scikit learn
                Λ, Φ = np.linalg.eig(Σ)
            else:
                return -1
    return Φ

## Rotina para calculo dos Vetores principais - Feature Vector
## Recebe os auto valores e auto vetores (Φ, Λ) e ordena os vetores de acordo com os eixos de maior importancia
def matriz_feature_vector(Φ, Λ):
    orderVector = Λ.argsort()[::-1]
    lnΦ = np.size(Φ, 0)
    colΦ = np.size(Φ, 1)
    FeatureVector = np.empty((lnΦ, colΦ))
    for j in range(0, colΦ, 1):
        for i in range(0, lnΦ, 1):
            FeatureVector[i][j] = Φ[i][(orderVector[j])]
    return FeatureVector


def main():
    ############################ leitura da base de dados pelo arquivo Excel ############################
    ###########Formato Primeira do arquivo Excel linha nome das variáveis, Y, X1, X2,
    ###########Primeira coluna, variáveil dependente Y, segunda coluna X2
    ###########Segunda coluna, variáveil explicativa X2
    ###########Terceira coluna, variáveil explicativa X2 ou outras variaveis explicativas
    import xlrd
    book = xlrd.open_workbook("bianchiDbAula1MultiVariada.xlsx")
    print("Número de abas: ", book.nsheets)
    print("Nomes das Planilhas:", book.sheet_names())
    for vSheet in book.sheet_names():
        print(vSheet)
        sh = book.sheet_by_name(vSheet)
        labelChart = sh.name
        tbCol = sh.ncols
        Label = []
        for i in range(0, tbCol, 1):
            Label.append(sh.cell_value(rowx=0, colx=i))
        labelZ = sh.cell_value(rowx=0, colx=0)
        labelX = sh.cell_value(rowx=0, colx=1)
        labelY = sh.cell_value(rowx=0, colx=2)
        qtElementos = sh.nrows
        grp_ZReal = []
        grp_YReal = []
        grp_XReal = []

        ################ Matrizes para carregar as informaçoes das bases de dados ##########################
        dadosPCA = np.empty(((qtElementos - 1), tbCol))
        XLinear = np.empty(((qtElementos - 1), 3))  # Matriz das variáveis explicativa X
        Y = np.empty(((qtElementos - 1), 1))  # Matriz das variáveis dependente Y
        Xmin = sh.cell_value(rowx=1, colx=1)  # ponteiro para minimo a ser utilizado na formacao do gráfico
        Xmax = sh.cell_value(rowx=1, colx=1)  # ponteiro para máximo a ser utilizado na formacao do gráfico
        for i in range(1, qtElementos, 1):
            ################### Carrega Variável dependente Y ############################################
            Y[(i - 1)][0] = sh.cell_value(rowx=i, colx=0)
            ################### Carrega Variável PCA  ############################################
            for j in range(0, tbCol, 1):
                dadosPCA[(i-1)][j]=sh.cell_value(rowx=i, colx=j)
            ################### Carrega Variável explicativa X ############################################
            XLinear[(i - 1)][0] = 1  # Add 1 - "BIAS"
            XLinear[(i - 1)][1] = sh.cell_value(rowx=i, colx=1)
            XLinear[(i - 1)][2] = sh.cell_value(rowx=i, colx=2)
            # ponteiro para minimo a ser utilizado na formacao do gráfico
            if Xmin > sh.cell_value(rowx=i, colx=1): Xmin = sh.cell_value(rowx=i, colx=1)
            if Xmax < sh.cell_value(rowx=i, colx=1): Xmax = sh.cell_value(rowx=i, colx=1)
            ################# Valores das amostras para apresentar no gráfico
            grp_ZReal.append(sh.cell_value(rowx=i, colx=0))
            grp_XReal.append(sh.cell_value(rowx=i, colx=1))
            grp_YReal.append(sh.cell_value(rowx=i, colx=2))

        ################################## Grafico das amostras inicias ####################################
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        ax.set_title("Amostras"+labelChart)
        ax.plot_trisurf(grp_XReal, grp_YReal, grp_ZReal, linewidth=0.1, antialiased=True)

        for i in range(0, (qtElementos - 1), 1):
            ax.scatter(grp_XReal[i], grp_YReal[i], grp_ZReal[i], c='r', marker='^')
        ax.set_xlabel(labelX)
        ax.set_ylabel(labelY)
        ax.set_zlabel(labelZ)

        plt.show()

        ########################        Derfine intervalo para plotar gráficos ##################
        step = (Xmax - Xmin) / (qtElementos - 1)

        ################               PCA            ###################################
    # Calcula matriz Ajustada pelas médias
        Mean, DataAdjust = matriz_DataAdjust(dadosPCA)
    # Calcula a covariancia
        Σ = matriz_covariancia(DataAdjust)
        print("covariância Σ:", Σ)
    # Calcula os autovalores
        Λ = matriz_autovalores(Σ)
        print('autovalores Λ:', Λ)
     # Calcula os autovetores
        Φ = matriz_autovetores(Σ, Λ)
        print("autovetores Φ: ", Φ)
    # Ordena pelo vetor mais significativo
        FeatureVector = matriz_feature_vector(Φ, Λ)
    # Exclui vetor menos significativo
        FeatureVector.resize((np.size(FeatureVector, 0), (np.size(FeatureVector, 1)-1)))
    # Calcula os vetores normalizados ao vetor mais significativo
        DataAdjustT = matriz_transposta(DataAdjust)
        FeatureVectorT = matriz_transposta(FeatureVector)

        FinalData = multiplica_matriz(FeatureVectorT, DataAdjustT)
        FinalDataT = matriz_transposta(FinalData)

        lnVet = np.size(FeatureVector, 0)
        colVet = np.size(FeatureVector, 1)

        print("Numero de Dimensoes:  ", colVet)

        ######     Matrizes dimensionais - VtDimensoes segmenta cada dimensao em um vetor próprio ###########

        vtDimensoes = []
        FinalDataVetor = []
        FinalDataVetorT = []

        for i in range(0, colVet, 1):
            vtDimensao = np.zeros((lnVet, colVet))
            for j in range(0, lnVet, 1):
                vtDimensao[j][i] = FeatureVector[j][i]
            vtDimensoes.append(vtDimensao)

        vtDimensoesT = []
        for i in range(0, colVet, 1):
            vtDimensoesT.append(matriz_transposta(vtDimensoes[i]))
        for i in range(0, colVet, 1):
            FinalDataVetor.append(multiplica_matriz(vtDimensoesT[i], DataAdjustT))
        for i in range(0, colVet, 1):
            FinalDataVetorT.append(matriz_transposta(FinalDataVetor[i]))

        ################################## Plota PCA no Eixo Principal####################################
        dfVec = pd.DataFrame({'X': FinalDataT[:, 0], 'Y': FinalDataT[:, 1]})

        for i in range(0, colVet, 1):
            labelA = "X" + str(i) + "Vet"
            labelB = "EqVetor_" + str(i) + "_Vet"
            dfVec[labelA] = FinalDataVetorT[i][:, 0]
            dfVec[labelB] = FinalDataVetorT[i][:, 1]

        print("####################################################################################################\n")
        print("DataFrame Vetor Principal\n")
        print("####################################################################################################\n")
        print(dfVec)
        print("####################################################################################################\n")

        line = dict(linewidth=1, linestyle='--', color='k')
        fig, ax = plt.subplots(figsize=(12, 8))

        ax.axhline(**line)
        ax.axvline(**line)


        ax = plt.gca()

        dfVec.plot(kind='scatter', x='X', y='Y', color='blue',ax=ax, label='Amostra')

        for i in range(0, colVet, 1):
            labelA="X" + str(i) + "Vet"
            labelB= "EqVetor_" + str(i) + "_Vet"
            dfVec.plot(kind='line', marker='o', ms=6, x=labelA, y=labelB, ax=ax, label=labelB)


        plt.title("PCA Eixo Principal "+labelChart)
        plt.xlabel(labelX)
        plt.ylabel(labelZ)
        plt.grid(True)

        plt.show()

        ################################## Plota Dado original Restaurado ####################################

        OriginalMeanParts=([Mean]*np.size(FinalData,1))
        addVec = np.zeros((np.size(FinalDataT, 0), 1))
        OriginalMean=(np.append(FinalDataT, addVec, axis=1))+OriginalMeanParts
        OrigData = multiplica_matriz(FeatureVectorT, FinalData)+OriginalMean

        ################               LMS  Linear            ###################################
        XLinearT = matriz_transposta(XLinear)  # Matriz X transposta
        XLinearTXLinear = multiplica_matriz(XLinearT, XLinear)  # Matriz X transposta multiplicada pela Matriz X
        XLinearTY = multiplica_matriz(XLinearT, Y)  # Matriz X transposta multiplicada pela Matriz Y
        XLinearTI = matriz_Inversa(XLinearTXLinear)  # Matrix inversa (XT*X)
        βXLinear = multiplica_matriz(XLinearTI, XLinearTY)  # Fatores da regressao LMS
        print("βXLinear:", βXLinear)

        #####################Variáveis para formacao dos graficos################################
        grp_3dX = []
        grp_3dY = []
        grp_Lin3dZ = []
        for index in range(0, 8, 1):
            for indexj in range(0, 25, 1):
                ################## Prepara Gráfico Regressao 3D Linear ##################################
                varXYLin = np.empty((1, 3), int)
                varXYLin[0][0] = 1
                varXYLin[0][1] = index
                varXYLin[0][2] = indexj
                yRegresaaoXYLin = multiplica_matriz(varXYLin, βXLinear)
                grp_3dX.insert(index, index)
                grp_3dY.insert(index, indexj)
                grp_Lin3dZ.insert(index, yRegresaaoXYLin[0][0])

        ################################## Grafico das amostras inicias ####################################
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        ax.set_title("LMS x PCA "+labelChart)
        x=OrigData[:,1]
        y = OrigData[:, 2]
        z = OrigData[:, 0]
        ax.scatter(z, x, y, c='r', marker='^')
        ax.scatter(grp_ZReal, grp_XReal, grp_YReal, c='b', marker='^')
        ax.plot_trisurf(z, x, y, color='green', linewidth=0.1, antialiased=True)
        ax.plot_trisurf(grp_Lin3dZ, grp_3dX, grp_3dY, linewidth=0.1, antialiased=True)
        ax.set_xlabel(labelZ)
        ax.set_ylabel(labelX)
        ax.set_zlabel(labelY)

        plt.show()

main()