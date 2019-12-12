# !/usr/bin/env python
# Importar bibliotecas
import numpy as np
import math
import csv
import copy

########################################################################################################################
############################# Objeto Perceptron RNA - rede neural artificial ###########################################
## inicializa com o indice de saturacao α_sat=, coeficiente de aprendizado η_aprend, numero de dimensoes e episodios/epocas
class Perceptron(object):
    ###################### metodo de construçao recebe indice de saturacao α_sat=, coeficiente de aprendizado η_aprend, numero de dimensoes e episodios/epocas
    def __init__(self,  α_sat=0.5, η_aprend=0.01, dimensoes=2, episodios=2000, ε=0.01):
        self.α_sat=α_sat
        self.η_aprend = η_aprend
        self.episodios = episodios
        self.imput = 0
        self.Δerro = 0
        self.net = 0
        self.dfnet = 0
        self.fnet = 0
        self.ε=ε

    ############################### Calcula o primeiro vetor w com numeros aleatórios ##################################
        self.w = np.random.uniform(-1, 1, dimensoes + 1)
    #################### método de para funcao de saturacao, recebe o resultante da funcao f(x), se valor for maior que o indice de saturacao retorna 1
    def Saturacao(self, x):
        if x >= self.α_sat:
            return 1
        else:
            return 0
    ################################# método de para funcao de ativacao do neuronio ####################################
    def fAtiva(self, x):
        return 1/(1+math.exp(-x))

    ################################# método de para funcao de derivada da ativacao do neuronio ########################
    def dfAtiva(self, x):
        return self.fAtiva(x)*(1-self.fAtiva(x))

    ################## método par retornar e imprimir os valores do vetor com os pesos sinápticos ######################
    def vet_value(self):
        return self.w
    ################### método par retornar e imprimir os valores do erro com os pesos sinápticos ######################
    def erro_value(self):
        return self.Δerro
    ####################### método par retornar e imprimir os valores do fnet do neuronio ##############################
    def fnet_value(self):
        return self.fnet
    ########################## método par retornar e imprimir os valores do net do neuronio ############################
    def net_value(self):
        return self.net
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
                self.net=self.w.dot(X[j])
                self.fnet = self.fAtiva(self.net)
                self.dfnet= self.fAtiva(self.net)*(1-self.fAtiva(self.net))
                ############# verifica resultado se é o esperado ou nao para calibrar os pesos sinapticos ########
                if ((Y[j] - self.fnet) **2)/2 > self.ε :
                    erro_referencia += 1
                    Δerro = Y[j] - self.fnet
                    self.w += self.η_aprend * Δerro * X[j] * (1- self.fnet)* X[j]
            if erro_referencia == 0:
                print("Iterações", i)
                break
    ##################### metodo para predizer os valores com base no aprendizado do treinamento #######################
    def prediz(self, ponto):
        if np.ndim(ponto) == 1:
            ponto = np.insert(ponto, len(ponto), 1)
    ########### realiza as multiplicacoes do vetor de pesos e o ponto para predicao ###################################
            self.fnet = 1 / (1 + math.exp(-self.w.dot(ponto)))
            prediction=self.Saturacao(self.fnet)
            return prediction
        else:
            ponto = np.insert(ponto[:, ], len(ponto[0]), 1, axis=1)
    ####################### realiza as multiplicacoes do vetor de pesos e o ponto para predicao ########################
            prediction = [self.Saturacao(self.fnet(x)) for x in ponto]
            return predicao

########################################################################################################################
################################## Objeto Perceptron RNA - rede neural artificial ######################################
#################### inicializa com o numero de camadas e neuronios, o indice de saturacao α_sat=, #####################
#################### coeficiente de aprendizado η_aprend, numero de dimensoes e episodios/epocas #######################
class mlp(object):
    ###################### metodo de construçao recebe indice de saturacao α_sat=, coeficiente de aprendizado η_aprend, numero de dimensoes e episodios/epocas
    def __init__(self, layer=[10,2], α_sat=0.5, η_aprend=0.01, dimensoes=2, episodios=2000, ε=0.01):
        self.α_sat=α_sat
        self.η_aprend = η_aprend
        self.episodios = episodios
        self.dimensoes=dimensoes
        self.ε=ε
        self.Δerro = []
        self.qtCamadas = len(layer)
        self.net = []
        self.fnet = []
        self.dfnet = []
        self.layer=layer
        self.layers = []

        for i in range (0, self.qtCamadas,1):
            self.layers.append([])
            self.net.append([])
            self.fnet.append([])
            self.Δerro.append([])
            if i==0:
                dim=self.dimensoes
            else:
                dim=self.layer[(i-1)]
            for j in range (0,layer[i],1):
                self.Δerro[i].append([])
                self.layers[i].append(Perceptron(α_sat=self.α_sat, η_aprend=self.η_aprend, dimensoes=dim, episodios=self.episodios, ε=self.ε))
        #print("RNA - Quantidade de Camadas:", self.qtCamadas)
    def Saturacao(self, x):
        if x >= self.α_sat:
            return 1
        else:
            return 0
    ##################### método par retornar e imprimir os valores do erro com os pesos sinápticos ####################
    def erro_value(self):
        for i in range(0, len(self.layer), 1):
            for j in range(0, layer[i], 1):
                self.erro+=(self.layers[i][j].erro_value())**2
        self.erro=self.erro/2
        return self.erro
    ########## método para treinamento do perceptron, recete a amostra X e as classificacoes reais da amostra Y ########
    def treina(self, X, Y):
    ############################################## amostras + BIAS #####################################################
        X = np.insert(X[:, ], len(X[0]), 1, axis=1)
    ############ loop para treinamento para o número de epsodios/epocas ou até confirmacao de aprendizado ##############
        for i in range(self.episodios):
            ciclo=i%100
            if ciclo==0:
                print("...",i, end="")
                linha=i%2000
                if linha==0:
                    print("...")
            erro_ciclo = 0
    ###### referencia de existencia de erro (aprendizado concluído para saida antecipada ao termino dos episodios ######
            for j in range(len(X)):
    ########################################## Feed Forward das entradas ###############################################
                for k in range(0, self.qtCamadas, 1):  # camada k
                    for n in range(0, self.layer[k], 1):  # neuronio n
                        if k == 0:
                            entrada = copy.deepcopy(X[j])
                        else:
                            entrada=[]
                            for imp in range(0, self.layer[(k - 1)],1):
                                entrada.append(self.layers[(k - 1)][imp].fnet)
                            entrada.append(1)
                        ############# calculo da saida estimada com o vetor de pesos sinapticos atual ###################
                        self.layers[k][n].imput=copy.deepcopy(entrada)
                        self.layers[k][n].net=self.layers[k][n].w.dot(self.layers[k][n].imput)
                        ############# calculo da saida estimada com o vetor de pesos sinapticos atual ###################
                        self.layers[k][n].fnet = self.layers[k][n].fAtiva(self.layers[k][n].net)
                        self.layers[k][n].dfnet = self.layers[k][n].fAtiva(self.layers[k][n].net) * (1-self.layers[k][n].fAtiva(self.layers[k][n].net))

    ######################################## Feed Back dos erros das entradas ##########################################
                for k in range(1, (self.qtCamadas +1), 1):  # camada k
                    camadaNeural=self.qtCamadas-k
                    if k == 1:
                        saida=Y[j]
                        for n in range(0, self.layer[camadaNeural], 1):
                            qtSaidas=len(saida)
                            if qtSaidas > 1:
                                if ((saida[n] - self.Saturacao(self.layers[camadaNeural][n].fnet))**2)/2 > self.ε:
                                #if ((saida[qtS] - self.layers[camadaNeural][n].fnet) ** 2) / 2 > self.ε:
                                    erro_ciclo += 1
                                    self.Δerro[camadaNeural][n] = (saida[n] - self.layers[camadaNeural][n].fnet) * (self.layers[camadaNeural][n].dfnet)
                                else:
                                    self.Δerro[camadaNeural][n] =0
                            else:
                                if ((saida - self.Saturacao(self.layers[camadaNeural][n].fnet))**2)/2 > self.ε:
                                #if ((saida - self.layers[camadaNeural][n].fnet) ** 2) / 2 > self.ε:
                                    erro_ciclo += 1
                                    self.Δerro[camadaNeural][n] = (saida - self.layers[camadaNeural][n].fnet) * (self.layers[camadaNeural][n].dfnet)
                                else:
                                    self.Δerro[camadaNeural][n]=0
                    else:
                        for n in range(0, self.layer[camadaNeural], 1):  # neuronio n
                            self.Δerro[camadaNeural][n]=0
                            for ne in range (0, self.layer[(camadaNeural+1)],1):
                                for w in range (0, len(self.layers[(camadaNeural+1)][ne].w),1):
                                    self.Δerro[camadaNeural][n] += self.Δerro[(camadaNeural+1)][ne]*self.layers[(camadaNeural+1)][ne].w[w]
                            self.Δerro[camadaNeural][n] =self.Δerro[camadaNeural][n] * self.layers[camadaNeural][n].dfnet

                #################### Feed Back calcula W ####################
                for k in range(1, (self.qtCamadas+1), 1):  # camada k
                    camadaNeural=self.qtCamadas - k
                    for n in range(0, self.layer[camadaNeural], 1):
                        if k == self.qtCamadas:
                            imput = copy.deepcopy(X[j])
                            qtImput = len(imput)
                        else:
                            imput = copy.deepcopy(self.layers[camadaNeural][n].imput)
                            qtImput = len(imput)
                        if qtImput > 1:
                            for qtS in range(0,qtImput,1):
                                self.layers[camadaNeural][n].w[qtS] += self.layers[camadaNeural][n].η_aprend*self.Δerro[camadaNeural][n]*imput[qtS]
                        else:
                            self.layers[camadaNeural][n].w += self.layers[camadaNeural][n].η_aprend*self.Δerro[camadaNeural][n] * imput
            if erro_ciclo==0:
                print("\nIterações RNA", i)
                break
    ######################################## método para obter os pesos da rede neural  ################################
    def net_w(self):
        net_pesos=[]
        for i in range (0,len(self.layer),1):
            net_pesos.append([])
            for j in range(0,self.layer[i],1):
                net_pesos[i].append(self.layers[i][j].vet_value())
        return net_pesos
    ##################### metodo para predizer os valores com base no aprendizado do treinamento #######################
    def prediz(self, ponto):
        if np.ndim(ponto) == 1:
            prediction=[]
    ########### realiza as multiplicacoes do vetor de pesos e o ponto para predicao ###################################
            for k in range (0, self.qtCamadas, 1): # camada k
                for n in range (0, self.layer[k],1): #neuronio n
                    if k == 0:
                        entrada = np.insert(ponto, len(ponto), 1)
                    else:
                        entrada=[]
                        for imp in range (0, self.layer[(k-1)],1):
                            entrada.append(self.layers[(k - 1)][imp].fnet)
                        entrada.append(1)
                    ############# calculo da saida estimada com o vetor de pesos sinapticos atual ###################
                    self.layers[k][n].imput =  copy.deepcopy(entrada)
                    self.layers[k][n].net = self.layers[k][n].w.dot(self.layers[k][n].imput)
                    ############# calculo da saida estimada com o vetor de pesos sinapticos atual ###################
                    self.layers[k][n].fnet = self.layers[k][n].fAtiva(self.layers[k][n].net)
                    self.layers[k][n].dfnet = self.layers[k][n].fAtiva(self.layers[k][n].net) * (1 - self.layers[k][n].fAtiva(self.layers[k][n].net))
                    if k==(self.qtCamadas-1):
                        prediction.append(self.Saturacao(self.layers[k][n].fnet))
            return prediction
        else:
            ponto = np.insert(ponto[:, ], len(ponto[0]), 1, axis=1)
        ##################### realiza as multiplicacoes do vetor de pesos e o ponto para predicao ######################
            prediction=[self.Saturacao(1 / (1 + math.exp(-self.w.dot(x)))) for x in ponto]
            return  prediction

def main ():
    import xlrd
    treina = xlrd.open_workbook("dbTraining.xlsx")
    valida = xlrd.open_workbook("dbValid.xlsx")

    print("Número de abas: ", treina.nsheets)
    print("Nomes das Planilhas:", treina.sheet_names())
    for vSheet in treina.sheet_names():
        print(vSheet)
        csv_file_name="mlp_search_"+vSheet+".csv"
        with open(csv_file_name, mode='a', newline='') as csv_file:
            fieldnames = ['cenario', 'qtAcertos_tp1','qtAcertos_tp2', 'qtAcertos_tp3', 'qtErros_tp1', 'qtErros_tp2', 'qtErros_tp3', '%']
            writer=csv.writer(csv_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
            writer.writerow(fieldnames)

            saidas=3
            maxCamadas=3
            maxNeuronios = 1000
            episodios=2000
            maxCheck=10
            tbConfig=[]

            sh = treina.sheet_by_name(vSheet)
            vl = valida.sheet_by_name(vSheet)
            tbCol = sh.ncols
            Label = []
            np.set_printoptions(precision=4)
            for i in range(1, (tbCol), 1):
                Label.append(sh.cell_value(rowx=0, colx=i))
            qtElementos = sh.nrows
            qtVal = vl.nrows

            qtVariaveis = (tbCol - saidas)

            ######################## Matrizes para carregar as informaçoes das bases de dados ##############################
            X = np.empty(((qtElementos - 1), qtVariaveis))
            XVal = np.empty(((qtVal - 1), qtVariaveis))
            Y = np.empty(((qtElementos - 1), saidas))
            YVal = np.empty(((qtVal - 1), saidas))

            for i in range(1, qtElementos, 1):
                ############################# Carrega Variável Y e X  - Base de Treinamento ####################################
                for j in range(0, tbCol, 1):
                    if j > (saidas - 1):
                        X[(i - 1)][(j - saidas)] = sh.cell_value(rowx=i, colx=j)
                    else:
                        Y[(i - 1)][j] = int(sh.cell_value(rowx=i, colx=j))

            for i in range(1, qtVal, 1):
                ############################# Carrega Variável Y e X  Base de Validacao ########################################
                for j in range(0, tbCol, 1):
                    if j > (saidas - 1):
                        XVal[(i - 1)][(j - saidas)] = vl.cell_value(rowx=i, colx=j)
                    else:
                        YVal[(i - 1)][j] = int(vl.cell_value(rowx=i, colx=j))

            print("dimensoes=", np.size(X, 1))

            for ncamadas in range (1,(maxCamadas+1), 1):
                Hecht_Nielsen=0
                if ncamadas==1:
                    tmpConfig=copy.deepcopy(saidas)
                    tbConfig.append([tmpConfig])
                else:
                    for n1Neuronios in range(1, (maxNeuronios + 1), 1):
                        if (qtVariaveis*2) < n1Neuronios:
                            Hecht_Nielsen=1
                            break
                        if ncamadas == 2:
                            tmpConfig = [n1Neuronios]
                            if saidas>0:
                                tmpConfig.append(saidas)
                            tbConfig.append(tmpConfig)
                        else:
                            for n2Neuronios in range(1, (maxNeuronios + 1), 1):
                                if (qtVariaveis * 2 + 1) > (n1Neuronios+n2Neuronios):
                                    tmpConfig = [n1Neuronios]
                                    tmpConfig.append(n2Neuronios)
                                    if saidas > 0:
                                        tmpConfig.append(saidas)
                                    tbConfig.append(tmpConfig)
                            if Hecht_Nielsen==1:
                                break

            qtCenarios=len(tbConfig)
            print("Quantidade de cenarios", qtCenarios)

            print("tbConfig", tbConfig)

            for cenario in range (0,qtCenarios, 1):
                tbConf = np.zeros((2, saidas))
                for ciclos in range (0, maxCheck, 1):
                    configCamadas = tbConfig[cenario]
                    ######################################### inicializa da RNA MLP ################################################
                    rna = mlp(layer=configCamadas, α_sat=0.5, η_aprend=0.1, dimensoes=np.size(X, 1), episodios=episodios,
                              ε=0.01)
                    ################################### treina com a base de treinamento X e Y #####################################
                    rna.treina(X, Y)
                    ##################### realiza a validacao com a pridicao dos valores da base de aprendizado ####################
                    ################################## Valida com a base de validacao XVal e YVal ##################################
                    for i in range(0, np.size(XVal, 0), 1):
                        YPred = rna.prediz(XVal[i])
                        for j in range(0, saidas, 1):
                            if YVal[i][j] == 1:
                                if YPred[j] == 1:
                                    tbConf[0][j] += 1/maxCheck
                                else:
                                    tbConf[1][j] += 1/maxCheck
                print("\n====================Predicao====================")
                print("================================================")
                print("Tabela Confusao - cenario: %d/%d perfil:"% ((cenario+1), qtCenarios), configCamadas)
                print("================================================")
                print(tbConf)
                print("================================================")
                txAcerto=(tbConf[0][0]+tbConf[0][1]+tbConf[0][2])/((tbConf[0][0]+tbConf[0][1]+tbConf[0][2])+(tbConf[1][0]+tbConf[1][1]+tbConf[1][2]))
                print("txAcerto", txAcerto)
                writer.writerow([configCamadas, tbConf[0][0] , tbConf[0][1] , tbConf[0][2], tbConf[1][0], tbConf[1][1], tbConf[1][2],txAcerto])



main()