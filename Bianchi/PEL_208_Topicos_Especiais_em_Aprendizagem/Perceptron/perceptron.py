# !/usr/bin/env python
# Importar bibliotecas
import numpy as np
########################################################################################################################
############################# Objeto Perceptron RNA - rede neural artificial ###########################################
## inicializa com o indice de saturacao α_sat=, coeficiente de aprendizado η_aprend, numero de dimensoes e episodios/epocas
class Perceptron(object):
    ###################### metodo de construçao recebe indice de saturacao α_sat=, coeficiente de aprendizado η_aprend, numero de dimensoes e episodios/epocas
    def __init__(self, α_sat=0.5, η_aprend=1, dimensoes=2, episodios=200):
        self.α_sat=α_sat
        self.η_aprend = η_aprend
        self.episodios = episodios
    #################calcula o primeiro vetor w com numeros aleatórios ###########################
        self.w = np.random.uniform(-1, 1, dimensoes + 1)
    #################### método de para funcao de saturacao, recebe o resultante da funcao f(x), se valor for maior que o indice de saturacao retorna 1
    def Saturacao(self, x):
        if x >= self.α_sat:
            return 1
        else:
            return 0
    ################# método par retornar e imprimir os valores do vetor com os pesos sinápticos ####################
    def vet_value(self):
        return self.w
    ########### método para treinamento do perceptron, recete a amostra X e as classificacoes reais da amostra Y #######
    def treina(self, X, Y):
    ############################################## amostras + BIAS #####################################################
        X = np.insert(X[:, ], len(X[0]), 1, axis=1)
    ############ loop para treinamento para o número de epsodios/epocas ou até confirmacao de aprendizado ##############
        for i in range(self.episodios):
    ###### referencia de existencia de erro (aprendizado concluído para saida antecipada ao termino dos episodios ######
            erro_referencia = 0
            for j in range(len(X)):
                ############# calculo da saida estimada com o vetor de pesos sinapticos atual ###################
                saida_o = self.w.dot(X[j])
                ############# verifica resultado se é o esperado ou nao para calibrar os pesos sinapticos ########
                if self.Saturacao(saida_o) != Y[j]:  #
                    erro_referencia += 1
                    Δ = Y[j] - saida_o
                    self.w += self.η_aprend * Δ * X[j]
            if erro_referencia == 0:
                print("Iterações", i)
                break
    ##################### metodo para predizer os valores com base no aprendizado do treinamento #######################
    def prediz(self, ponto):
        if np.ndim(ponto) == 1:
            ponto = np.insert(ponto, len(ponto), 1)
    ########### realiza as multiplicacoes do vetor de pesos e o ponto para predicao ###################################
            prediction = self.Saturacao(self.w.dot(ponto))
            return prediction
        else:
            ponto = np.insert(ponto[:, ], len(ponto[0]), 1, axis=1)
        ########### realiza as multiplicacoes do vetor de pesos e o ponto para predicao ###################################
            predicao = [self.Saturacao(self.w.dot(x)) for x in ponto]
            return predicao

def main ():
    import xlrd
    book = xlrd.open_workbook("dbTraining.xlsx")
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
        X = np.empty(((qtElementos - 1), (tbCol - 1)))
        Y = np.empty(((qtElementos - 1), 1))

        for i in range(1, qtElementos, 1):
            ################### Carrega Variável Y e X  ############################################
            for j in range(0, tbCol, 1):
                if j > 0:
                    X[(i - 1)][(j - 1)] = sh.cell_value(rowx=i, colx=j)
                else:
                    Y[(i - 1)][j] = int(sh.cell_value(rowx=i, colx=j))

        print("dimensoes=", np.size(X,1))
        ########################## inicializa o perceptron ######################################
        perceptron = Perceptron(α_sat=0.5, η_aprend=0.01, dimensoes=np.size(X,1), episodios=200)
        ##################### treina com a base de treinamento X e Y ############################
        perceptron.treina(X, Y)
        ##################### pega e imprime os pesos  ############################
        print("W:", perceptron.vet_value())
        ##################### realiza a validacao com a pridicao dos valores da base de aprendizado ####################
        for i in range(0,np.size(X,0),1):
            print("predicao ", i, end="")
            print (" : ", X[i], perceptron.prediz(X[i]))
        perceptron="fim"


main()