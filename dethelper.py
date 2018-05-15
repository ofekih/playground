import random

import dt

def get_random_board(size: int) -> [int]:
	board = [i + 1 for i in range(size ** 2)]
	random.shuffle(board)
	return board

def erode_board(board: [int]) -> [int]:
	b = [0] * len(board)
	for i in range(random.randint(0, len(board) - 1)):
		b[i] = board[i]
	random.shuffle(b)
	return b

if __name__ == '__main__':
	while 1:
		board = get_random_board(dt.SIZE)
		dt.print_board(board, dt.SIZE, '?')
		sign = input("What's your guess: ")

		if sign == 'next':
			break

		result = dt.board_result(board)

		if sign == '-' and result < 0 or \
		   sign == '0' and result == 0 or \
		   not sign in ('-', '0') and result > 0:

		   print("Correct:", result)

		else:
			print("Wrong ;(")
			dt.print_board(board, dt.SIZE, result)

	results = dt.get_results("3x3.txt")

	while 1:
		board = get_random_board(dt.SIZE)
		board = erode_board(board)
		dt.print_board(board, dt.SIZE, '?')
		sign = input("What's your guess: ")

		if sign == 'next':
			break

		result = dt.get_result(results, dt.get_hash(board))

		if sign == '-' and result < 0 or \
		   sign == '0' and result == 0 or \
		   not sign in ('-', '0') and result > 0:

		   print("Correct:", result)

		else:
			print("Wrong ;(")
			dt.print_board(board, dt.SIZE, result)


	while 1:
		board = get_random_board(dt.SIZE)
		board = erode_board(board)
		dt.print_board(board, dt.SIZE, '?')
		move = dt.get_human_move(dt.SIZE)

		board[move[0]] = move[1]

		if sign == 'next':
			break

		result = dt.get_result(results, dt.get_hash(board))

		if sign == '-' and result < 0 or \
		   sign == '0' and result == 0 or \
		   not sign in ('-', '0') and result > 0:

		   print("Correct:", result)

		else:
			print("Wrong ;(")
			dt.print_board(board, dt.SIZE, result)
