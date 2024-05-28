import subprocess
import tests_list

subprocess.call("make parsing_test", shell=True)
print()

for test in tests_list.tests:
	process = subprocess.Popen(['./parsing_test', test.test_line], stdout=subprocess.PIPE)
	output, _ = process.communicate()
	test.expected = output.decode('utf-8')

for test in tests_list.tests:
	print(f"Command: {test.test_line}")
	filename = f"tester/parsing/expected/test_{test.test_count}"
	with open(filename, 'w') as file:
		file.write(test.test_line + '\n')
		file.write(test.expected)
