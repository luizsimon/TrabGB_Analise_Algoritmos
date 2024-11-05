# Analisando Jogos de Civilizações Antigas

## Descrição Geral
Este projeto implementa uma solução para resolver o problema de combinação de pontuações em placas de um campeonato. Dado um conjunto de placas onde cada uma possui uma pontuação para dois jogadores, o objetivo é verificar se é possível organizar as placas de maneira que a soma das pontuações de cada lado seja igual ao final da sequência.

Caso não seja possível alcançar uma combinação com todas as placas, o programa busca a melhor combinação descartando apenas uma placa, de modo a maximizar a soma final. Se houver mais de uma placa que possa ser descartada para alcançar uma solução viável, a placa com o menor valor de pontuação é descartada. Esta solução também permite que as placas sejam invertidas para maximizar as possibilidades de combinações.

## Integrantes da Dupla

- Vitor
- Luiz

## Compilação e Execução

### Pré-requisitos

- Compilador C++ (suporta C++11 ou superior)
- Sistema operacional compatível com o compilador (Windows, Linux, macOS)

### Compilação

Abra o terminal na pasta onde estão os arquivos e execute:

```bash
g++ sol_1.cpp -o sol_1 -std=c++11
```

### Execução

Após a compilação, execute:

```bash
./sol_1
```