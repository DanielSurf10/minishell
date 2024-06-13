# Minishell

## Introdução
Este projeto é uma implementação simplificada de um [shell Unix](https://pt.wikipedia.org/wiki/Shell_do_Unix), chamada Minishell, parte do currículo da Escola 42 São Paulo. O objetivo é criar uma interface de linha de comando que permite aos usuários interagir com o sistema operacional, executar comandos, gerenciar processos e manipular a entrada e saída de dados.

## Estrutura do Projeto

O projeto foi dividido em quatro partes principais:
- [**1. Lexing**](#1-lexing)
- [**2. Parsing**](#2-parsing)
- [**3. Expand**](#3-expand)
- [**4. Exec**](#4-exec)

### 1. Lexing
**Objetivo**: Converter a entrada de texto em uma sequência de tokens.

**Detalhes**:
- **Entrada**: Comandos do usuário como uma string.
- **Saída**: Lista de tokens.

**Processo**:
1. Dividir a string de entrada em componentes menores (tokens) com base em espaços e caracteres especiais.
2. Identificar cada componente como um tipo específico de token (e.g., comando, argumento, operador).
3. Lidar com aspas (simples e duplas) e caracteres de escape.

### 2. Parsing
**Objetivo**: Construir uma estrutura de dados (árvore de análise sintática/binária) a partir da sequência de tokens.

**Detalhes**:
- **Entrada**: Lista de tokens gerada pelo lexer.
- **Saída**: Árvore de análise sintática.

**Processo**:
1. Construir uma árvore de comandos onde cada nó representa um comando ou uma operação.
2. Verificar se a sequência de tokens segue as regras gramaticais do shell.
3. Detectar e reportar erros sintáticos.

### 3. Expand
**Objetivo**: Lidar com a expansão de variáveis de ambiente e substituições de comandos.

**Detalhes**:
- **Entrada**: A árvore de análise sintática ou a lista de tokens.
- **Saída**: A árvore de análise sintática ou a lista de tokens com as expansões aplicadas.

**Processo**:
1. Substituir variáveis de ambiente (e.g., `$HOME`) por seus valores.
2. Executar comandos dentro de crases (`cmd`) e substituir a saída no lugar.

### 4. Exec
**Objetivo**: Executar os comandos representados pela árvore de análise sintática.

**Detalhes**:
- **Entrada**: A árvore de análise sintática com expansões aplicadas.
- **Saída**: Resultados da execução dos comandos.

**Processo**:
1. Executar comandos internos e externos.
2. Criar processos filho, redirecionar entrada/saída e esperar a conclusão dos processos.
3. Capturar e reportar erros de execução.

## Conclusão
Este projeto Minishell, dividido em quatro partes distintas (lexing, parsing, expand e exec), permite uma abordagem modular e estruturada para a implementação de um shell Unix simplificado. Cada etapa tem uma responsabilidade clara, garantindo um fluxo de processamento organizado desde a entrada do comando até a sua execução final.
