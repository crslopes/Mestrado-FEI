# !/usr/bin/env python
import xlrd  # biblioteca para leitura de arquivos excel
import matplotlib.pyplot as plt  # biblioteca para plotar graficos
import pandas as pd  # biblioteca para criacao de dataframes, auxiliar para os graficos
import numpy as np
import copy

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
    try:
        col = np.size(A, 1)  # numero de colunas da matriz A
    except Exception:
        col=0
    C = np.empty((col,ln))  # cria matriz C vazia com numero de linhas igual ao numero de colunas da matriz A e numero de linhas igual ao numero de colunas da matriz A
    # laço para a transposicao, linha = coluna
    for j in range(0, col, 1):
        for i in range(0, ln, 1):
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
                #Λ = np.linalg.eigvals(Σ)
                Λ, Φ = np.linalg.eig(Σ)
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
    return FeatureVector, orderVector

## Rotina para Calculo da dispersao intra grupo
## Recebe a matriz com os dados segmentados, quantidade de grupos e variaveis/dimensoes e retorna a matriz de dispersao de cada grupo
def feature_sw(dadosType, dadosMedias, qtGrupos, qtVariaveisGr):
    S_W = 0
    class_sc_mat = 0
    for i in range(0, qtGrupos, 1):
        N = np.size(dadosType[i], 0)
        for j in range(0, N, 1):
            DadosX = np.asarray(dadosType[i][j]).reshape(qtVariaveisGr, 1)
            mv = np.asarray(dadosMedias[i]).reshape(qtVariaveisGr, 1)
            class_sc_mat += (DadosX - mv).dot((DadosX - mv).T)
    S_W += class_sc_mat
    return S_W

## Rotina para Calculo da dispersao intre grupos
## Recebe a matriz com os dados segmentados e quantidade de variaveis/dimensoes e retorna a matriz de dispersao entre grupos
def feature_sb(dadosType, dadosMedias, qtVariaveisGr):
    ####################################### Calculo das Médias Total  ##############################################
    dadosMediaTotal = []
    for i in range(0, qtVariaveisGr, 1):
        dadosMediaTotal.append(np.mean(dadosMedias[:, i]))

    S_B = np.zeros((qtVariaveisGr, qtVariaveisGr))
    for i in range(0, 3, 1):
        n = np.size(dadosType[i], 0)
        mean_vec = dadosMedias[i].reshape(qtVariaveisGr, 1)
        dadosMediaTotal = np.array(dadosMediaTotal).reshape(qtVariaveisGr, 1)
        S_B += n * (mean_vec - dadosMediaTotal).dot((mean_vec - dadosMediaTotal).T)
    return S_B


def main():
    import xlrd
    book = xlrd.open_workbook("LDAdb.xlsx")
    print("Número de abas: ", book.nsheets)
    print("Nomes das Planilhas:", book.sheet_names())
    for vSheet in book.sheet_names():
        print(vSheet)
        sh = book.sheet_by_name(vSheet)
        tbCol = sh.ncols
        variaveis=tbCol-1
        Label = []
        qtGrupos=3
        np.set_printoptions(precision=4)
        dic_Type = {0: 'Setosa', 1: 'Versicolor', 2: 'Virginica'}
        for i in range(1, (tbCol), 1):
            Label.append(sh.cell_value(rowx=0, colx=i))
        labelX = sh.cell_value(rowx=0, colx=1)
        labelY = sh.cell_value(rowx=0, colx=2)

        qtElementos = sh.nrows

        ################ Matrizes para carregar as informaçoes das bases de dados ##########################
        dadosPCA = np.empty(((qtElementos - 1), (tbCol-1)))
        dadosLDA = np.empty(((qtElementos - 1), tbCol))

        for i in range(1, qtElementos, 1):
            ################### Carrega Variável PCA e LDA  ############################################
            for j in range(0, tbCol, 1):
                if j >0 :
                    dadosPCA[(i-1)][(j-1)]=sh.cell_value(rowx=i, colx=j)
                    dadosLDA[(i - 1)][j] = sh.cell_value(rowx=i, colx=j)
                else:
                    dadosLDA[(i - 1)][j] = int(sh.cell_value(rowx=i, colx=j))

        ################### Segmenta os Grupos para o LDA  ############################################
        dadosType = []
        dadosMedias = []
        for i in range(0, qtGrupos, 1):
            dadosType.append([])
            dadosMedias.append([])
        for i in range(0, (qtElementos - 1), 1):
            obj = int(dadosLDA[i][0])
            dadosType[obj].append(dadosLDA[i][1:, ])

        fig, ax = plt.subplots(figsize=(12, 12))

        ################################## Plota Original 2D  - Eixos originais  #######################################
        dfBaseOriginal = pd.DataFrame({'idx': dadosLDA[:,0], 'X': dadosLDA[:, 1], 'Y': dadosLDA[:, 2]})

        line = dict(linewidth=1, linestyle='--', color='k')

        ax = plt.gca()
        ax = plt.subplot((111))

        plt.title("Original 2D - 3 Grupos")

        for grupo, marker, color in zip(range(0, 3), ('^', 's', 'o'), ('blue', 'orange', 'green')):
            filtro = dfBaseOriginal["idx"] == grupo
            agrupamento="Amostra "+dic_Type[grupo]
            basePlot=dfBaseOriginal.where(filtro)
            basePlot.plot(kind='scatter', x='X', y='Y', marker=marker, color=color, s=40, ax=ax, label=agrupamento)
        plt.grid(True)
        plt.xlabel(labelX)
        plt.ylabel(labelY)
        plt.show()

        ########################################### FIM Plota Original #################################################

        ########################################               LDA            ##########################################
        ################################## Calculo das Médias intra Grupos  ############################################
        qtVariaveisGr = np.size(dadosType[0], 1)
        for i in range(0, qtGrupos, 1):
            dadosType[i] = np.asarray(dadosType[i])
            for j in range(0, qtVariaveisGr, 1):
                dadosMedias[i].append(np.mean(dadosType[i][:, j]))
        dadosMedias = np.array(dadosMedias).reshape(qtGrupos, variaveis)

        ############################# Calculo Dispersao dentro dos Grupos - Sw  ####################################
        S_W= feature_sw(dadosType, dadosMedias, qtGrupos,qtVariaveisGr)
        ################################# Calculo Dispersao entre os Grupos - Sb  ######################################
        S_B=feature_sb(dadosType, dadosMedias, qtVariaveisGr)
        ####################################### Calculo da matriz de projecao   ########################################
        Σ = np.linalg.inv(S_W).dot(S_B)
        #################################### Calculo dos autovetores e autovalores   ###################################
        LDA_Λ, LDA_Φ = np.linalg.eig(Σ)
        LDA_FeatureVector, LDA_orderVector = matriz_feature_vector(LDA_Φ, LDA_Λ)

        ###########
        lnVet = np.size(LDA_FeatureVector, 0)
        colVet = np.size(LDA_FeatureVector, 1)

        #############     Matrizes dimensionais - VtDimensoes segmenta cada dimensao em um vetor próprio ###############

        vtDimensoes = []
        FinalDataVetor = []
        FinalDataVetorT = []

        for i in range(0, colVet, 1):
            vtDimensao = np.zeros((lnVet, colVet))
            for j in range(0, lnVet, 1):
                vtDimensao[j][i] = LDA_FeatureVector[j][i]
            vtDimensoes.append(vtDimensao)
        vtDimensoesT = []

        DataAdjust = dadosLDA[:, 1:np.size(dadosLDA, 1)]
        DataAdjustT = matriz_transposta(DataAdjust)
        for i in range(0, colVet, 1):
            vtDimensoesT.append(matriz_transposta(vtDimensoes[i]))
        for i in range(0, colVet, 1):
            FinalDataVetor.append(multiplica_matriz(vtDimensoesT[i], DataAdjustT))
        for i in range(0, colVet, 1):
            FinalDataVetorT.append(matriz_transposta(FinalDataVetor[i]))

        FinalDataPriVetorT = FinalDataVetorT[0]  # matriz_transposta(FinalDataPriVetor)
        FinalDataSecVetorT = FinalDataVetorT[1]  # matriz_transposta(FinalDataSecVetor)
        dfEixoLDAVec = pd.DataFrame({'XPriVet': FinalDataPriVetorT[:, 0], 'YPriVet': FinalDataPriVetorT[:, 1],
                                     'XSecVet': FinalDataSecVetorT[:, 0], 'YSecVet': FinalDataSecVetorT[:, 1]})
        # Transformando as amostras no novo subespaço
        x_lda = []
        for i in range(0, qtGrupos, 1):
            x_lda.append(dadosType[i].dot(LDA_FeatureVector))

        lnVet = np.size(LDA_FeatureVector, 0)
        colVet = np.size(LDA_FeatureVector, 1)

        print("Numero de Dimensoes:  ", colVet)

        ######     Matrizes dimensionais - VtDimensoes segmenta cada dimensao em um vetor próprio ###########

        fig, ax = plt.subplots(figsize=(24, 12))
        ax = plt.gca()
        ax = plt.subplot((121))

        dfEixoLDAVec.plot(kind='line', marker='o', ms=6, x='XPriVet', y='YPriVet', color='red', ax=ax,
                          label='LDAVetor Principal')
        dfEixoLDAVec.plot(kind='line', marker='o', ms=6, x='XSecVet', y='YSecVet', color='green', ax=ax,
                          label='LDAVetor Secundario')

        ################################## Plota LDA no Eixo ####################################

        for grupo, marker, color in zip(range(0, 3), ('^', 's', 'o'), ('blue', 'orange', 'green')):
            plt.scatter(x=x_lda[grupo][:, 0], y=x_lda[grupo][:, 1], marker=marker, color=color, label=dic_Type[grupo])
        plt.xlabel(Label[LDA_orderVector[0]])
        plt.ylabel(Label[LDA_orderVector[1]])
        leg = plt.legend(loc='upper right', fancybox=True)
        leg.get_frame().set_alpha(0.5)

        plt.title('ANÁLISE DISCRIMINANTE LINEAR (LDA) - Base Iris')

        plt.axvline(x=0)
        x = np.linspace(-2, 3, 100)
        y = 0 * x
        plt.plot(x, y, '-r')
        plt.grid()

        ########################################               PCA            ##########################################
        ax = plt.subplot((122))
        # Calcula matriz Ajustada pelas médias
        PCA_Mean, PCA_DataAdjust = matriz_DataAdjust(dadosPCA)
        # Calcula a covariancia
        PCA_Σ = matriz_covariancia(PCA_DataAdjust)
        print("covariância PCA Σ:", PCA_Σ)
        # Calcula os autovalores
        print("PCA_Σ", PCA_Σ)
        PCA_Λ = matriz_autovalores(PCA_Σ)
        print('autovalores PCA Λ:', PCA_Λ)
        # Calcula os autovetores
        PCA_Φ = matriz_autovetores(PCA_Σ, PCA_Λ)
        print("autovetores PCA Φ: ", PCA_Φ)
        # Ordena pelo vetor mais significativo
        PCA_FeatureVectorBase, PCA_orderVector = matriz_feature_vector(PCA_Φ, PCA_Λ)

        PCA_FeatureVector = copy.deepcopy(PCA_FeatureVectorBase)
        ################################################################################################################
        # Exclui vetor menos significativo
        PCA_reduction = 1
        PCA_FeatureVector = PCA_FeatureVector[:, 0:(np.size(PCA_FeatureVector, 1) - PCA_reduction)]

        ################################################################################################################

        # Calcula os vetores normalizados ao vetor mais significativo

        PCA_DataAdjustT = matriz_transposta(PCA_DataAdjust)
        PCA_FeatureVectorT = matriz_transposta(PCA_FeatureVector)
        PCA_FinalData = multiplica_matriz(PCA_FeatureVectorT, PCA_DataAdjustT)
        PCA_FinalDataT = matriz_transposta(PCA_FinalData)

        dfPCA_Vec = pd.DataFrame({'idx': dadosLDA[:, 0], 'X': PCA_FinalDataT[:, 0], 'Y': PCA_FinalDataT[:, 1]})

        line = dict(linewidth=1, linestyle='--', color='k')
        ax.axhline(**line)
        ax.axvline(**line)
        ax = plt.gca()

        for grupo, marker, color in zip(range(0, 3), ('^', 's', 'o'), ('blue', 'orange', 'green')):
            PCA_filtro = dfPCA_Vec["idx"] == grupo
            agrupamento = "Amostra " + dic_Type[grupo]
            PCA_basePlot = dfPCA_Vec.where(PCA_filtro)
            PCA_basePlot.plot(kind='scatter', x='X', y='Y', marker=marker, color=color, s=40, ax=ax, label=agrupamento)
        plt.grid(True)

        PCA_colVet = np.size(PCA_FeatureVector, 1)

        ######     EIXOS   ###########

        lnVet = np.size(PCA_FeatureVector, 0)
        colVet = np.size(PCA_FeatureVector, 1)

        PCA_vtDimensoes = []
        PCA_FinalDataVetor = []
        PCA_FinalDataVetorT = []

        for i in range(0, colVet, 1):
            PCA_vtDimensao = np.zeros((lnVet, colVet))
            for j in range(0, lnVet, 1):
                PCA_vtDimensao[j][i] = PCA_FeatureVector[j][i]
            PCA_vtDimensoes.append(PCA_vtDimensao)

        PCA_vtDimensoesT = []
        for i in range(0, colVet, 1):
            PCA_vtDimensoesT.append(matriz_transposta(PCA_vtDimensoes[i]))
        for i in range(0, colVet, 1):
            PCA_FinalDataVetor.append(multiplica_matriz(PCA_vtDimensoesT[i], PCA_DataAdjustT))
        for i in range(0, colVet, 1):
            PCA_FinalDataVetorT.append(matriz_transposta(PCA_FinalDataVetor[i]))

        dfPCA_Eixo = pd.DataFrame({'X': PCA_FinalDataT[:, 0], 'Y': PCA_FinalDataT[:, 1]})

        for i in range(0, (colVet - 1), 1):
            labelA = "X" + str(i) + "Vet"
            labelB = "EqVetor_" + str(i) + "_Vet_" + Label[PCA_orderVector[i]]
            dfPCA_Eixo[labelA] = PCA_FinalDataVetorT[i][:, 0]
            dfPCA_Eixo[labelB] = PCA_FinalDataVetorT[i][:, 1]

        for i in range(0, (colVet - 1), 1):
            labelA = "X" + str(i) + "Vet"
            labelB = "EqVetor_" + str(i) + "_Vet_" + Label[PCA_orderVector[i]]
            dfPCA_Eixo.plot(kind='line', linewidth=3, x=labelA, y=labelB, ax=ax, label=labelB)

        plt.title("PCA Plotagem Eixo Principal em 2D para " + str(PCA_colVet) + "  dimensoes")
        plt.xlabel(Label[PCA_orderVector[0]])
        plt.ylabel(Label[PCA_orderVector[1]])

        plt.show()
        ########################################             FIM  PCA            #######################################

        ########################################               MDF            ##########################################
        dimensoes=np.size(PCA_FeatureVectorBase,1)

        fig, ax = plt.subplots(figsize=(18, 18))
        for dim in range (0, (dimensoes), 1):

            PCA_FeatureVector=copy.deepcopy(PCA_FeatureVectorBase)
            ###################################################################################################################
            # Exclui vetor menos significativo
            PCA_reduction = dim
            PCA_FeatureVector = PCA_FeatureVector[:, 0:(np.size(PCA_FeatureVector, 1) - PCA_reduction)]
            ###################################################################################################################


            # Calcula os vetores normalizados ao vetor mais significativo

            PCA_DataAdjustT = matriz_transposta(PCA_DataAdjust)
            PCA_FeatureVectorT = matriz_transposta(PCA_FeatureVector)
            PCA_FinalData = multiplica_matriz(PCA_FeatureVectorT, PCA_DataAdjustT)
            PCA_FinalDataT = matriz_transposta(PCA_FinalData)

            ########################################               LDA            ##########################################
            # separação de dados em grupos de tipos
            dadosType = []
            dadosMedias = []
            for i in range(0, qtGrupos, 1):
                dadosType.append([])
                dadosMedias.append([])
            for i in range(0, (qtElementos - 1), 1):
                obj = int(dadosLDA[i][0])
                dadosType[obj].append(PCA_FinalDataT[i])

            #calcula as médias de cada grupo do LDA
            qtVariaveisGr = np.size(dadosType[0], 1)
            for i in range(0, qtGrupos, 1):
                dadosType[i] = np.asarray(dadosType[i])
                for j in range(0, qtVariaveisGr, 1):
                    dadosMedias[i].append(np.mean(dadosType[i][:, j]))
            dadosMedias = np.array(dadosMedias).reshape(qtGrupos, qtVariaveisGr)

            ############################# Calculo Dispersao dentro dos Grupos - Sw  ####################################
            S_W = feature_sw(dadosType, dadosMedias, qtGrupos, qtVariaveisGr)
            print("Dispersao dentro dos Grupos - Sw", S_W)
            ################################# Calculo Dispersao entre os Grupos - Sb  ######################################
            S_B = feature_sb(dadosType, dadosMedias, qtVariaveisGr)
            print("Dispersao entre dos Grupos - Sb", S_B)
            ####################################### Calculo da matriz de projecao   ########################################
            Σ = np.linalg.inv(S_W).dot(S_B)
            # Calcula os autovetores e autovalores
            LDA_Λ, LDA_Φ = np.linalg.eig(Σ)
            print("Autovalores - LDA_Λ", LDA_Λ)
            print("Autovetores - LDA_Φ", LDA_Φ)
            LDA_FeatureVector, LDA_orderVector = matriz_feature_vector(LDA_Φ, LDA_Λ)

            ###########
            lnVet = np.size(LDA_FeatureVector, 0)
            colVet = np.size(LDA_FeatureVector, 1)

            ######     Matrizes dimensionais - VtDimensoes segmenta cada dimensao em um vetor próprio ###########

            vtDimensoes = []
            FinalDataVetor = []
            FinalDataVetorT = []

            for i in range(0, colVet, 1):
                vtDimensao = np.zeros((lnVet, colVet))
                for j in range(0, lnVet, 1):
                    vtDimensao[j][i] = LDA_FeatureVector[j][i]
                vtDimensoes.append(vtDimensao)
            vtDimensoesT = []
            DataAdjust = PCA_FinalData

            for i in range(0, colVet, 1):
                vtDimensoesT.append(matriz_transposta(vtDimensoes[i]))
            for i in range(0, colVet, 1):
                FinalDataVetor.append(vtDimensoesT[i].dot(DataAdjust))
            for i in range(0, colVet, 1):
                FinalDataVetorT.append(matriz_transposta(FinalDataVetor[i]))


            ax = plt.subplot((221+dim))

            FinalDataPriVetorT = FinalDataVetorT[0]

            colVet = np.size(LDA_FeatureVector, 1)

            if colVet >1 :
                FinalDataSecVetorT = FinalDataVetorT[1]  # matriz_transposta(FinalDataSecVetor)
                dfEixoLDAVec = pd.DataFrame({'XPriVet': FinalDataPriVetorT[:, 0], 'YPriVet': FinalDataPriVetorT[:, 1],
                                         'XSecVet': FinalDataSecVetorT[:, 0], 'YSecVet': FinalDataSecVetorT[:, 1]})
                dfEixoLDAVec.plot(kind='line', marker='o', ms=6, x='XPriVet', y='YPriVet', color='red', ax=ax,
                                  label='LDAVetor Principal')
                dfEixoLDAVec.plot(kind='line', marker='o', ms=6, x='XSecVet', y='YSecVet', color='green', ax=ax,
                                  label='LDAVetor Secundario')

            # Transformando as amostras no novo subespaço
            x_lda = []
            for i in range(0, qtGrupos, 1):
                x_lda.append(dadosType[i].dot(LDA_FeatureVector))

            if colVet <2 :
                for i in range(0, qtGrupos, 1):
                    addVec = np.zeros((np.size(x_lda[i], 0), 1))
                    ReducVector = (np.append(x_lda[i], addVec, axis=1))
                    x_lda[i]=ReducVector


            print("Numero de Dimensoes:  ", colVet)

            ################################## Plota MDF no Eixo ####################################

            for grupo, marker, color in zip(range(0, 3), ('^', 's', 'o'), ('blue', 'orange', 'green')):
                plt.scatter(x=x_lda[grupo][:, 0], y=x_lda[grupo][:, 1], marker=marker, s=50, color=color, label=dic_Type[grupo])
            plt.xlabel(Label[LDA_orderVector[0]])
            if colVet > 1:
                plt.ylabel(Label[LDA_orderVector[1]])

            leg = plt.legend(loc='upper right', fancybox=True)
            leg.get_frame().set_alpha(0.5)

            plt.title('ANÁLISE Most Discriminant Features (PCA&LDA) - Base Iris - ' + str(colVet) + ' dimensoes')

            plt.axvline(x=0)
            x = np.linspace(-2, 3, 100)
            y = 0 * x
            plt.plot(x, y, '-r')
            plt.grid()
        plt.show()

        ########################################             FIM  MDF            #######################################

main()
