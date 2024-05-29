import subprocess
import tests_list

RST		= '\033[0m'
GREEN	= '\033[32;1m'
RED		= '\033[31;1m'
ORANGE	= '\033[38;5;208m'
PURPLE	= "\033[38;5;141m"

subprocess.call("make parsing_test", shell=True)
print()

for test in tests_list.tests:
	process = subprocess.Popen(['./parsing_test', test.test_line], stdout=subprocess.PIPE)
	output, _ = process.communicate()
	test.expected = output.decode('utf-8')

for test in tests_list.tests:
	# print(f"Command: {test.test_line}")
	filename = f"tester/parsing/expected/test_{test.test_count}"
	with open(filename, 'r') as file:
		expected = file.read()

	# expected = f'{test.test_line}\n{expected}'

	if f'{test.test_line}\n{test.expected}' == expected:
		print(f"{PURPLE}{test.test_count:3}{RST} - {GREEN}[ ✓ ]{RST} {ORANGE}Command:{RST} {test.test_line}")
	else:
		print(f"{PURPLE}{test.test_count:3}{RST} - {RED}[ ✗ ]{RST} {ORANGE}Command:{RST} {test.test_line}")
