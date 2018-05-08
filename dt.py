def get_hash(board: [int]) -> int:
	# print(board)
	h = 0
	for i in range(len(board)):
		h += board[i] * 10 ** (len(board) - i - 1);
	return h

def get_result(results: [(int, int)], h: int):
	for result in results:
		if result[0] == h:
			return result[1]

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

def get_best_move(board: [int], target_sign: int, results: [(int, int)]) -> (int, int):
	result = get_result(results, get_hash(board))
	children = get_children(board)

	for (child, move) in children:
		if get_result(results, get_hash(child)) == result:
			return move

def get_human_move(size: int) -> (int, int):
	move = tuple((int(i) for i in input("Please enter your move: ").split()))
	return move[0] * size + move[1], move[2]

def print_board(board: [int], size: int):
	for r in range(size):
		for c in range(size):
			print(board[r * size + c], end=" ")
		print()
	print()

def play_game(ai_turn: str, size: int, results: [(int, int)]):
	board = [0] * (size ** 2)
	turn = True
	while 0 in board:
		print_board(board, size)
		move = None
		if ai_turn == 'both' or turn == (ai_turn == 'first'):
			move = get_best_move(board, 1 if turn else -1, results)
		else:
			move = get_human_move(size)

		board[move[0]] = move[1]

		turn = not turn

	print_board(board, size)

	# print("First player wins" if board.result() > 0 else ("Tie game" if board.result() == 0 else "Second player wins"))


def get_results(filename: str) -> [(int, int)]:
	results = []
	with open(filename) as file:
		for line in file:
			results.append(tuple((int(i) for i in line.split())))
	return results

if __name__ == '__main__':
	print("Loading results... ", end="")
	results = get_results("3x3.txt")
	print("loaded")
	play_game('both', 3, results)
	# print(results)
