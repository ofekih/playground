import random

import dt

def get_random_board(size: int) -> [int]:
	board = [i + 1 for i in range(size ** 2)]
	random.shuffle(board)
	return board

if __name__ == '__main__':
	while 1:
		board = get_random_board(dt.SIZE)
		dt.print_board(board, dt.SIZE, '?')
		sign = input("What's your guess: ")

		if sign == 'exit':
			break

		if sign == '-' and dt.board_result(board) < 0 or \
		   sign == '0' and dt.board_result(board) == 0 or \
		   not sign in ('-', '0') and dt.board_result(board) > 0:

		   print("Correct:", dt.board_result(board))

		else:
			print("Wrong ;(")
			dt.print_board(board, dt.SIZE, dt.board_result(board))

