/*
    Entrada: Arquivo contendo o conjunto de placas que será analisado. A primeira linha do arquivo define o número de placas do conjunto. Quando a linha for igual a 0 significa que não terá mais conjuntos de placas.

    Problema: Dado um conjunto de placas de 2 colunas, como dispor essas placas lado a lado de modo que a soma de toda a primeira linha seja igual a soma de toda segunda linha, sendo essa soma a maior possível. Ex: placas ({1, 2}, {6, 3}, {1, 3})

                                                           1 6 1   => 8
                                                           2 3 3   => 8

    Condições de Contorno: É possível inverter as placas. Se com o conjunto inicial de placas não for possível estabelecer uma soma idêntica para ambas as linhas, é possível remover apenas UMA placa e verificar novamente

    Saída: apresentar a saída na tela contendo uma das 3 frases possíveis: 
    "MAIOR_SOMA_ENCONTRADA nenhuma placa descartada" , 
    "MAIOR_SOMA_ENCONTRADA descartada a placa X Y" (X e Y são os valores presentes na placa descartada, sendo que X < Y),
    "impossível" (quando não há como dispor as placas lado a lado, mesmo retirando uma, e gerar uma soma idêntica para ambas as linhas).
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <cmath>
#include <cstdint>

using namespace std;

int32_t resultado = 0, somaFinalAtual = 0, somaFinalAnterior = INT32_MIN;

// função para encontrar uma combinação de placas que tenha o mesmo valor do resultado
void encontrarCombinacoesPlacas(const vector<int> &difPlacasTodas, vector<int> &indices, vector<int> &indicesCorretos, int resultado, int32_t soma, int start, bool &encontrado) {

    // Verifica se a soma atual é igual ao desejado
    if (soma == resultado) {
        encontrado = true;
        for (int i = 0; i < indices.size(); i++) {
            indicesCorretos.push_back(indices[i]);
        }
        return;
    }

    // Se a soma exceder o desejado, retorna
    if (soma > resultado) {
        return;
    }

    // Percorre o vetor a partir da posição 'start' - se encontrado = true, sai do loop
    for (int i = start; i < difPlacasTodas.size() && !encontrado; i++) {
        // Adiciona o índice atual à combinação
        indices.push_back(i);
        // Chama recursivamente, incluindo o elemento atual na soma
        encontrarCombinacoesPlacas(difPlacasTodas, indices, indicesCorretos, resultado, soma + difPlacasTodas[i], i + 1, encontrado);
        // Remove o índice atual para voltar à combinação anterior
        indices.pop_back();
    }
}

// função para definir e inverter as placas a fim de ter o mesma soma para ambas as colunas
bool definirInverterPlacas(vector<vector<int>> &conjuntoPlacas, vector<int> &difPlacasTodas, bool par) {
    int32_t soma = 0;
    bool encontrado = false;
    vector<int> indices, indicesCorretos;
    resultado = resultado / 2;

    // encontra e salva no indicesCorretos a primeira combinação de indices cuja soma das placas é igual ao resultado
    encontrarCombinacoesPlacas(difPlacasTodas, indices, indicesCorretos, resultado, 0, 0, encontrado);

    // verifica se uma combinação foi encontrada e o resultado inicial é impar
    if (encontrado && !par) {
        somaFinalAtual = 0;

        // inverte as placas para que ambas as colunas fiquem com a mesma soma total
        for (int i = 0; i < indicesCorretos.size(); i++) {
            int temp = conjuntoPlacas[indicesCorretos[i]][1];
            conjuntoPlacas[indicesCorretos[i]][1] = conjuntoPlacas[indicesCorretos[i]][0];
            conjuntoPlacas[indicesCorretos[i]][0] = temp;
        }

        // calcula a soma de toda a coluna
        for (int i = 0; i < conjuntoPlacas.size(); i++) {
            somaFinalAtual += conjuntoPlacas[i][0];
        }

        // desfaz a inversão para não afetar a próxima iteração
        for (int i = 0; i < indicesCorretos.size(); i++) {
            int temp = conjuntoPlacas[indicesCorretos[i]][1];
            conjuntoPlacas[indicesCorretos[i]][1] = conjuntoPlacas[indicesCorretos[i]][0];
            conjuntoPlacas[indicesCorretos[i]][0] = temp;
        }

        // salva a maior soma encontrada
        if (somaFinalAtual > somaFinalAnterior) {
            somaFinalAnterior = somaFinalAtual;
            return true;
        }

        return false;

    // verifica se uma combinação foi encontrada e o resultado inicial é par
    } else if (encontrado && par) {
        // inverte as placas para que ambas as colunas fiquem com a mesma soma total
        for (int i = 0; i < indicesCorretos.size(); i++) {
            int temp = conjuntoPlacas[indicesCorretos[i]][1];
            conjuntoPlacas[indicesCorretos[i]][1] = conjuntoPlacas[indicesCorretos[i]][0];
            conjuntoPlacas[indicesCorretos[i]][0] = temp;
        }

        somaFinalAtual = 0;

        // calcula a soma de toda a coluna
        for (int i = 0; i < conjuntoPlacas.size(); i++) {
            somaFinalAtual += conjuntoPlacas[i][0];
        }

        cout << somaFinalAtual << " nenhuma placa descartada" << "\n";

        return true;
    }
    
    int verificador = 0, indice = 0;

    // se encontrado = false, verifica se os elementos da placa são iguais 
    for (int i = 0; i < difPlacasTodas.size(); i++) {
        if (difPlacasTodas[i] == 0) {
            verificador++;
        } else indice = i;
    }
    
    int N;
    
    if (par) N = difPlacasTodas.size() - 1;
    else N = difPlacasTodas.size();
    
    // se todas as placas possuem elementos iguais, com exceção de uma placa, retira-se essa placa
    if (verificador == N) {
        int conjuntoDescartado[1][2];
        if (conjuntoPlacas[indice][0] < conjuntoPlacas[indice][1]) {
            conjuntoDescartado[0][0] = conjuntoPlacas[indice][0];
            conjuntoDescartado[0][1] = conjuntoPlacas[indice][1];
        } else {
            conjuntoDescartado[0][1] = conjuntoPlacas[indice][0];
            conjuntoDescartado[0][0] = conjuntoPlacas[indice][1];
        }

        conjuntoPlacas.erase(conjuntoPlacas.begin() + indice);

        somaFinalAtual = 0;

        // calcula a soma de toda a coluna
        for (int i = 0; i < conjuntoPlacas.size(); i++) {
            somaFinalAtual += conjuntoPlacas[i][0];
        }

        cout << somaFinalAtual << " descartada a placa " << conjuntoDescartado[0][0] << " " << conjuntoDescartado[0][1] << "\n";

        return true;
    }

    return false;
}

// função para tentar remover uma placa - chamada quando o resultado inicial é impar
void removerPlaca(vector<vector<int>> &conjuntoPlacas, vector<int> &difPlacasTodas, vector<int> &difPlacasImpares) {
    bool placaDescartada;
    int conjuntoRetirado[1][2];
    for (int i = 0; i < difPlacasImpares.size(); i++) {
        for (int j = 0; j < difPlacasTodas.size(); j++) {
            if (difPlacasTodas[j] == difPlacasImpares[i]) {
                // salva a placa atual e a conjuntoPlacas atual
                vector<int> conjuntoPlacasTemp = conjuntoPlacas[j];
                int placaTemp = difPlacasTodas[j];
                int placaRetirada[1][2] = {conjuntoPlacas[j][0], conjuntoPlacas[j][1]};

                // remove a placa atual e a conjuntoPlacas atual
                conjuntoPlacas.erase(conjuntoPlacas.begin() + j);
                difPlacasTodas.erase(difPlacasTodas.begin() + j);

                resultado = 0;

                // recalcula o resultado
                for (int i = 0; i < difPlacasTodas.size(); i++) {
                    resultado += difPlacasTodas[i];
                }

                bool possivel = definirInverterPlacas(conjuntoPlacas, difPlacasTodas, false);

                // verifica se é possível e salva o conjuntoRetirado
                if (possivel) {
                    placaDescartada = true;
                    if (placaRetirada[0][0] < placaRetirada[0][1]) {
                        conjuntoRetirado[0][0] = placaRetirada[0][0];
                        conjuntoRetirado[0][1] = placaRetirada[0][1];
                    } else {
                        conjuntoRetirado[0][0] = placaRetirada[0][1];
                        conjuntoRetirado[0][1] = placaRetirada[0][0];
                    }
                }

                // reinsere a placa e a conjuntoPlacas anteriormente retirada para não afetar a próxima iteração
                conjuntoPlacas.insert(conjuntoPlacas.begin() + j, conjuntoPlacasTemp);
                difPlacasTodas.insert(difPlacasTodas.begin() + j, placaTemp);
            }
        }
    }

    if (placaDescartada) {
        cout << somaFinalAnterior << " descartada a placa " << conjuntoRetirado[0][0] << " " << conjuntoRetirado[0][1] << "\n";
    } else {
        cout << "impossível" << "\n";
    }
}

void calcularCombinacaoPlacas(vector<vector<int>> &conjuntoPlacas)
{
    /*
        Vetor difPlacasImpares => armazena apenas as diferenças impares entre os elementos de uma placa do conjuntoPlacas
        Vetor difPlacasTodas => armazena todas as diferenças entre os elementos de uma placa do conjuntoPlacas
    */
    vector<int> difPlacasTodas, difPlacasImpares, difPlacasPares;
    int32_t somaParcial = 0, temp = 0;
    resultado = 0;

    for (int i = 0; i < conjuntoPlacas.size(); i++) {
        for (int j = 0; j < 2; j++) {
            if (j == 0) {
                somaParcial = conjuntoPlacas[i][j];
            } else {
                if (conjuntoPlacas[i][j] < somaParcial) {
                    temp = conjuntoPlacas[i][j];
                } else {
                    temp = somaParcial;
                }
                somaParcial = somaParcial - conjuntoPlacas[i][j];

                // Se a diferença entre os elementos da placa for negativa, inverte a ordem dos elementos para garantir que o resultado seja o maior possivel
                if (somaParcial < 0) {
                    temp = conjuntoPlacas[i][1];
                    conjuntoPlacas[i][1] = conjuntoPlacas[i][0];
                    conjuntoPlacas[i][0] = temp;
                }

                somaParcial = abs(somaParcial);
            }
        }
        difPlacasTodas.push_back(somaParcial);

        if (somaParcial % 2 == 0) {
            difPlacasPares.push_back(somaParcial);
        } else {
            difPlacasImpares.push_back(somaParcial);
        }
    }

    // Calcula a soma de todas as difPlacasTodas
    for (int i = 0; i < difPlacasTodas.size(); i++) {
        resultado += difPlacasTodas[i];
    }

    if (resultado % 2 == 0) {
        bool retorno = definirInverterPlacas(conjuntoPlacas, difPlacasTodas, true);
        if (!retorno) removerPlaca(conjuntoPlacas, difPlacasTodas, difPlacasPares);
    } else {
        removerPlaca(conjuntoPlacas, difPlacasTodas, difPlacasImpares);
    }
}

int main() {
    ifstream file("in_out/in4");
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << "\n";
        return 1;
    }

    vector<vector<vector<int>>> todosConjuntoPlacas; // Vetor para armazenar todos os conjuntoPlacas
    while (true) {
        int numLinhas;
        file >> numLinhas;

        if (numLinhas == 0) {
            break;
        }

        vector<vector<int>> conjuntoPlacas;

        for (int i = 0; i < numLinhas; ++i) {
            vector<int> placa;
            for (int j = 0; j < 2; ++j) {
                int valor;
                file >> valor;
                placa.push_back(valor);
            }
            conjuntoPlacas.push_back(placa);
        }
        todosConjuntoPlacas.push_back(conjuntoPlacas);
    }

    file.close();

    for (int i = 0; i < todosConjuntoPlacas.size(); i++) {
        // Define SomaFinalAnterior para INT32_MIN para não influenciar na próxima iteração
        somaFinalAnterior = INT32_MIN;
        calcularCombinacaoPlacas(todosConjuntoPlacas[i]);
    }
    
    return 0;
}