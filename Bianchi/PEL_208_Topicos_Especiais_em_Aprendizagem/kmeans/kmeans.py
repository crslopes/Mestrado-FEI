# !/usr/bin/env python
# Importar bibliotecas
from copy import deepcopy
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import random


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
    BaseΣ = np.zeros((col, col))

    for i in range(0, ln, 1):
        for j in range(0, col, 1):
            for k in range(0, col, 1):
                BaseΣ[j][k] = BaseΣ[j][k] + (Z[i][j] * Z[i][k])
    for j in range(0, col, 1):
        for k in range(0, col, 1):
            Σ[j][k] = BaseΣ[j][k] / (ln - 1)

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

## Rotina para Calculo da distancia euclidiana entre dois pontos vetorias
## Recebe 2 pontos no espaco vetorial e retorna a distancia entre eles
def distEuclides(A,B):
    dimensoes=len(A)
    distancia=0
    for i in range (0, dimensoes,1):
        distancia+=(A[i]-B[i])**2
    distancia=distancia**(1/2)
    return distancia

## Rotina para Calculo ddo centroide de uma massa de pontos
## Recebe uma matriz vetorial de pontos e retorna o ponto de centro dos pontos
def centroid(Pontos):
    ln = np.size(Pontos, 0)  # numero de linhas da matriz A
    col = np.size(Pontos, 1)  # numero de colunas da matriz A
    mean = np.zeros((1, col))

    for i in range(0, col, 1):
        for j in range(0, ln, 1):
            mean[0][i] = mean[0][i] + Pontos[j][i]

    for i in range(0, col, 1):
        mean[0][i] = mean[0][i] / ln
    Centroids=[]
    for i in range(0,col,1):
        Centroids.append(mean[0][i])
    return Centroids


def main ():
    import xlrd
    book = xlrd.open_workbook("dbBase.xlsx")
    print("Número de abas: ", book.nsheets)
    print("Nomes das Planilhas:", book.sheet_names())
    for vSheet in book.sheet_names():
        print(vSheet)
        dbName=vSheet
        sh = book.sheet_by_name(vSheet)
        tbCol = sh.ncols
        Label = []
        np.set_printoptions(precision=4)
        for i in range(1, (tbCol), 1):
            Label.append(sh.cell_value(rowx=0, colx=i))
        qtElementos = sh.nrows

        ################ Matrizes para carregar as informaçoes das bases de dados ##########################
        dadosBase = np.empty(((qtElementos - 1), (tbCol - 1)))
        dadosClasse = np.empty(((qtElementos - 1), tbCol))

        for i in range(1, qtElementos, 1):
            ################### Carrega Variável PCA e Kmeans  ############################################
            for j in range(0, tbCol, 1):
                if j > 0:
                    dadosBase[(i - 1)][(j - 1)] = sh.cell_value(rowx=i, colx=j)
                    #dadosClasse[(i - 1)][j] = sh.cell_value(rowx=i, colx=j)
                else:
                    dadosClasse[(i - 1)][j] = int(sh.cell_value(rowx=i, colx=j))

        grupomaxtb=dadosClasse[:,0]
        qtGrupos = int(grupomaxtb[np.argmax(grupomaxtb)])+1
        print("qtGrupos", qtGrupos)


        ########################################               PCA            ##########################################
        # Calcula matriz Ajustada pelas médias
        PCA_Mean, PCA_DataAdjust = matriz_DataAdjust(dadosBase)

        # Calcula a covariancia
        #PCA_Σ = matriz_covariancia(PCA_DataAdjust)

        PCA_Σ =np.cov(matriz_transposta(PCA_DataAdjust))
        # Calcula os autovalores
        print("PCA_Σ", PCA_Σ)
        PCA_Λ = matriz_autovalores(PCA_Σ)
        print('autovalores PCA Λ:', PCA_Λ)

        ############################prepara a massa de dados para utilizar em k-means###################################

        dadosBaseOrig, PCA_orderVector = matriz_feature_vector(dadosBase, PCA_Λ)
        print('Ordem de relevancia PCA Λ:', PCA_orderVector)

        for i in range (0,(tbCol-1),1):
            dadosClasse[:,(i+1)]=dadosBaseOrig[:,i]
        dadosClasseOrig=deepcopy(dadosClasse)
        classTb=np.zeros((np.size(dadosClasseOrig, 0),(tbCol+1)))
        classTb[:,1]=dadosClasseOrig[:,0]
        print("linhas:", np.size(dadosClasseOrig, 0), end="")
        print(" - colunas:", tbCol+1)

        ##############################################    k-means    ###################################################

        #### loop para remover dimensoes da massa dados para posterior comparacao de resultados entre os resultados ####
        for dimensoes in range(3, (tbCol + 1), 1):
            #############################################################################################################
            # Exclui vetor menos significativo
            PCA_reduction = tbCol - dimensoes
            dadosClasse = dadosClasseOrig[:, 0:(np.size(dadosClasseOrig, 1) - PCA_reduction)]
            dadosBase = dadosBaseOrig[:, 0:(np.size(dadosBaseOrig, 1) - PCA_reduction)]

            #############################################################################################################
            print("#################################################\ndimensoes:", (dimensoes-1) , end="")
            print("#################################################")
            ### variavel dimensoes = dimensoes da massa de dados +1 -
            ### imprime a massa aoriginal quando o numero de dimensoes é 2 = variavel dimensoes 3
            if dimensoes==3:
                ################### Segmenta os Grupos para o Original  ############################################
                dadosType = []
                dadosMedias = []
                for i in range(0, qtGrupos, 1):
                    dadosType.append([])
                    dadosMedias.append([])
                for i in range(0, qtGrupos, 1):
                    obj = int(dadosClasse[i][0])
                    dadosType[obj].append(dadosClasse[i][1:, ])
                fig, ax = plt.subplots(figsize=(12, 12))

                ################################## Plota Original 2D  - Eixos originais  #######################################
                dfBaseOriginal = pd.DataFrame({'idx': dadosClasse[:, 0], 'X': dadosClasse[:, 1], 'Y': dadosClasse[:, 2]})

                line = dict(linewidth=1, linestyle='--', color='k')

                ax = plt.gca()
                ax = plt.subplot((111))

                plt.title("" + dbName+" - ORIGINAL 2D - 3 Grupos")

                for grupo, marker, color in zip(range(0, qtGrupos), ('^', 's', 'o','p', 'd', '*','>'), ('y', 'm', 'c', 'r', 'b', 'Green', 'orange')):
                    filtro = dfBaseOriginal["idx"] == grupo
                    basePlot = dfBaseOriginal.where(filtro)
                    basePlot.plot(kind='scatter', x='X', y='Y', marker=marker, color=color, s=40, ax=ax)
                plt.grid(True)
                plt.xlabel(Label[PCA_orderVector[0]])
                plt.ylabel(Label[PCA_orderVector[1]])
                plt.show()

            ########################################### FIM Plota Original #############################################

            ####### variavels para uso na segentacao dos eixos e dimensoes ####

            dbDatabase = pd.DataFrame({'type': dadosClasse[:, 0]})

            limitEixosd = np.empty((2, (dimensoes - 1)))
            initCentroids = np.empty((qtGrupos, (dimensoes - 1)))


            ###################### Obtem limites das dimensoes para limitar os centroides iniciais #####################
            for i in range(1, (dimensoes), 1):
                labelA = str(Label[(i-1)])
                limitEixosd[0][(i - 1)] = np.min(dadosClasse[:, i])
                limitEixosd[1][(i - 1)] = np.max(dadosClasse[:, i])
                dbDatabase[labelA] = deepcopy(dadosClasse[:,i])

            ###########Define centroides iniciais como passos randomicos dentro do maximo e minimo dos eixos ###########
            for i in range(0, qtGrupos, 1):
                for j in range(0, (dimensoes-1), 1):
                    Δ = (limitEixosd[1][j] - limitEixosd[0][j]) / (qtGrupos)
                    initCentroids[i][j] = limitEixosd[0][j] + Δ * random.uniform(0, 1)+ i * Δ
            initCentroidsOrig=deepcopy(initCentroids)

            #######################  inicializa variavel para agrupar os dados classificados ###########################
            dadosTypeBase=[]
            for i in range(0, qtGrupos, 1):
                dadosTypeBase.append([])
            ########################## inicializa variavel de parada das interacoes - Erro #############################
            erro=1
            interacoes=0

            ################ realizad loop enquanto os itens dos grupos estiverem alterando - erro =1 ##################
            while erro:
                interacoes+=1
                if interacoes%10==0:
                    print(".", end='')
                ##################### variabels dos agrupamentos das interacoes regionai ##########################
                dadosType = []
                grpCentroid = []
                for i in range(0, qtGrupos, 1):
                    dadosType.append([])
                    grpCentroid.append([])
                #### para cada agrupamento calcula o novo centroide e reagrupa os dados pela distancia deste entroide###
                for i in range (0, (qtElementos-1), 1):
                    distCentroids = np.empty((qtGrupos, 1))
                    for j in range(0, qtGrupos, 1):
                        distCentroids[j]=distEuclides(initCentroids[j], dadosBase[i])
                    dadosType[distCentroids.argmin()].append(dadosBase[i])
                    classTb[i][dimensoes]=distCentroids.argmin()
                for i in range(0,qtGrupos,1):
                    if len(dadosType[i])>0:
                        grpCentroid[i] = centroid(np.array(dadosType[i]))
                initCentroids=deepcopy(np.array(grpCentroid))
                erro=0

                ################# verifica se a innteracao atual alterou a disposicao dos grupos #####################
                for i in range(0,qtGrupos,1):
                    if len(dadosTypeBase[i]) != len(dadosType[i]):
                        erro += 1
                    else:
                    #### subtrai a matraiz de agrupamento da matriz de controle, caso exista diferencas informa erro ###
                        checkDados=np.array(dadosType[i])-np.array(dadosTypeBase[i])
                        for j in range (0,np.size(checkDados,0),1):
                            for w in range (0,np.size(checkDados,1),1):
                                if checkDados[j][w] !=0:
                                    erro += 1
                #### define limite de interacoes para evitar loop eterno em casos de dados equidistantes de centroides ####
                if interacoes > 1000:
                    print ("dadosType", dadosType)
                    erro=0
                ######################### re-define matriz de controle de grupos #########################
                dadosTypeBase=deepcopy(dadosType)
            print("dimensoes:", dimensoes , end="")
            print(" e interacoes:", interacoes)

            ################################## Plota Original 2D  - Eixos originais  #######################################

            fig, ax = plt.subplots(figsize=(12, 12))

            line = dict(linewidth=1, linestyle='--', color='k')

            ax = plt.gca()
            ax = plt.subplot((111))

            plt.title("" + dbName+" - Agrupamento de "+str(dimensoes-1)+" dimensoes visto em 2D  - "+str(qtGrupos)+ " Grupos")

            for grupo, marker, color in zip(range(0, qtGrupos), ('^', 's', 'o','p', 'd', '*','>'), ('y', 'm', 'c', 'r', 'b', 'Green', 'orange')):
                if len(dadosType[grupo])>0:
                    plt.scatter(x=np.array(dadosType[grupo])[:, 0], y=np.array(dadosType[grupo])[:, 1], marker=marker, s=40, color=color)
                    plt.scatter(x=grpCentroid[grupo][0], y=grpCentroid[grupo][1], marker='P', c=color, s=200, alpha=0.9, edgecolor='k')
            plt.grid(True)
            plt.xlabel(Label[PCA_orderVector[0]])
            plt.ylabel(Label[PCA_orderVector[1]])
            plt.show()
        print ("classTb", classTb)
        np.savetxt(dbName, classTb, delimiter=",")



main()