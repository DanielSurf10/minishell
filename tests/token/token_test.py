#!/usr/bin/env python3

import subprocess

def execute_program(input_string):
    # Executa o programa externo
    process = subprocess.Popen(['./a.out'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

    # Envia a string de entrada para o programa
    stdout, stderr = process.communicate(input=input_string)

    # Retorna a string de saída
    return stdout

# Exemplo de uso
input_string = [
	'echo "Hello, World!"',
    'ls -l',
    'cat file.txt',
    'mkdir new_directory',
    'rm file.txt',
    'grep "pattern" file.txt',
    'cd /path/to/directory',
    'pwd',
    'chmod +x script.sh',
    'mv file.txt new_directory/',
    'echo "oi||&&>"fjdghgjh\'djkfghfdg\'<<>><>',
    '$CMD '
]

for input_cmd in input_string:
	output_string = execute_program(input_cmd)
	print(output_string)
