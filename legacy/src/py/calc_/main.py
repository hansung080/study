import sys
from calc import calc_infix

def main():
	if len(sys.argv) != 2:
		print('Usage : python3 main.py "-10*(-100+200)+(22345.678/(20-10))"')
		return

	print(calc_infix(sys.argv[1]))

if __name__ == '__main__':
	main()