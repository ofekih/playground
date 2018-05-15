import random

SIZE = 3

def get_hash(board: [int]) -> int:
	# print(board)
	h = 0
	for i in range(len(board)):
		h += board[i] * 10 ** (len(board) - i - 1);
	return h

def get_result(results: [(int, int)], h: int):
	first = 0
	last = len(results)
	while first <= last:
		mid = (first + last) // 2

		if results[mid][0] == h:
			return results[mid][1]
		elif h < results[mid][0]:
			last = mid - 1
		else:
			first = mid + 1
	print("Cannot find result")

def get_children(board: [int]) -> [[int]]:
	possible_moves = [i + 1 for i in range(len(board))]
	for m in board:
		if m in possible_moves:
			possible_moves.remove(m)

	children = []

	for n in range(len(board)):
		if board[n] == 0:
			for m in possible_moves:
				tmp = list(board)
				tmp[n] = m
				children.append((tmp, (n, m)))

	return children

def get_best_move(board: [int], results: [(int, int)]) -> (int, int):
	result = get_result(results, get_hash(board))
	children = get_children(board)
	random.shuffle(children)

	for (child, move) in children:
		if get_result(results, get_hash(child)) == result:
			return move

# def is_good_move(board: [int], move: (int, int), results: [(int, int)]) -> bool:
# 	result = get_result(results, get_hash(board))
# 	children = get_children(board)

# 	for (child, m) in children:
# 		if m != move: continue
# 		tresult = get_result(results, get_hash(child))
		# return tresult == result or tresult * result > 0:

def get_good_move(board: [int], results: [(int, int)]) -> (int, int):
	result = get_result(results, get_hash(board))
	children = get_children(board)
	random.shuffle(children)

	for (child, move) in children:
		tresult = get_result(results, get_hash(child))
		if tresult == result or tresult * result > 0:
			return move

def get_possible_squares(board: [int], size: int, results: [(int, int)]):
	result = get_result(results, get_hash(board))
	children = get_children(board)

	squares = []

	for (child, move) in children:
		if move[0] in squares: continue
		tresult = get_result(results, get_hash(child))
		if tresult == result or tresult * result > 0:
			squares.append(move[0])

	return [tuple([i // size, i % size]) for i in squares]

def print_squares(board: [int], size: int, squares: [(int, int)]):
	for r in range(size):
		for c in range(size):
			print(board[r * size + c] if (r, c) not in squares else '*', end=" ")
		print()
	print()

def get_random_move(board: [int]) -> (int, int):
	return random.choice(get_children(board))[1]

def get_human_move(size: int) -> (int, int):
	m = input("Please enter your move: ")
	if len(m.split()) < 3:
		return m
	move = tuple((int(i) for i in m.split()))
	return move[0] * size + move[1], move[2]

def print_board(board: [int], size: int, result: int):
	for r in range(size):
		for c in range(size):
			print(board[r * size + c], end=" ")
		print()
	print("Current result is: ", result)
	print()

def board_result(board: [int]) -> int:
	return board[0] * (board[4] * board[8] - board[5] * board[7]) - board[1] * (board[3] * board[8] - board[5] * board[6]) + board[2] * (board[3] * board[7] - board[4] * board[6]);

def play_game(ai_turn: str, size: int, results: [(int, int)]):
	if ai_turn[0] == 'exit'[0]:
		exit(0)
	board = [0] * (size ** 2)
	moves = []
	turn = True
	while 0 in board:
		print_board(board, size, get_result(results, get_hash(board)))
		move = None
		if ai_turn[0] == 'both'[0] or turn == (ai_turn[0] == 'first'[0]) and not ai_turn[0] == 'none'[0]:
			move = get_best_move(board, results)
		else:
			move = get_human_move(size)
			if type(move) == str and len(move) == 0:
				continue
			if move[0] == "ai"[0]:
				move = get_best_move(board, results)
			elif move[0] == "good"[0]:
				move = get_good_move(board, results)
			elif move[0] == "random"[0]:
				move = get_random_move(board)
			elif move[0] == "undo"[0]:
				if len(moves) == 0: continue
				board[moves.pop()] = 0
				turn = not turn
				ai_turn = 'none'
				continue
			elif move[0] == "exit"[0]:
				return
			elif move[0] == "squares"[0]:
				print_squares(board, size, get_possible_squares(board, size, results))
				continue
			elif type(move) == str:
				continue

		if move == None:
			print("ERR: NONETYPE")
			continue

		board[move[0]] = move[1]
		moves.append(move[0])

		turn = not turn

	print_board(board, size, get_result(results, get_hash(board)))

	print("First player wins" if board_result(board) > 0 else ("Tie game" if board_result(board) == 0 else "Second player wins"))
	print("Board Result:", board_result(board))


def get_results(filename: str) -> [(int, int)]:
	results = []
	with open(filename) as file:
		for line in file:
			results.append(tuple((int(i) for i in line.split())))
	results.sort()
	return results

if __name__ == '__main__':
	print("Loading results... ", end="")
	results = get_results("3x3.txt")
	print("loaded")

	while 1:
		play_game(input("AI Turn: "), SIZE, results)


	# print(results)
