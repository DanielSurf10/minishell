#!/usr/bin/env python3

import subprocess


def execute_program(input_string):
    # Executa o programa externo
    process = subprocess.Popen(['./token'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

    # Envia a string de entrada para o programa
    stdout, stderr = process.communicate(input=input_string)

    # Retorna a string de saída
    return stdout


output_string = ''

try:
    with open("tests/token/tests.txt", "r") as arq:
        input_string = arq.read().strip()

    with open("tests/token/expected.txt", "r") as arq:
        expected_string = arq.read()

    for input_cmd in input_string.split("\n"):
        output_string += execute_program(input_cmd) + '\n'

    if True:
        if expected_string == output_string:
            print("Tudo certo!")
        else:
            print("Deu errado")
    else:
        print(output_string, end='')
        # print(expected_string, end='')


except:
    print("Algo deu errado!")
