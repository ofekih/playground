def solve(matrix, mul):
	width = len(matrix)
	if width == 1:
		return mul * matrix[0][0]
	else:
		sign = -1
		total = 0
		for i in range(width):
			m = []
			for j in range(1, width):
				buff = []
				for k in range(width):
					if k != i:
						buff.append(matrix[j][k])
				m.append(buff)
			sign *= -1
			total += mul * solve(m, sign * matrix[0][i])
		return total

class DetBoard:

	def __init__(self, size: int, init: bool = True):
		self._board = [[0 for i in range(size)] for i in range(size)]
		self._size = size
		if init:
			self._numbers_left = list(range(1, (size ** 2) + 1))
			self.last_move = None

	def dup(self) -> 'DetBoard':
		dup = DetBoard(self._size, False)
		for i in range(self._size):
			for a in range(self._size):
				dup._board[i][a] = self._board[i][a]
		dup._numbers_left = list(self._numbers_left)
		return dup

	def get_children(self) -> ['DetBoard']:
		children = []

		for r in range(self._size):
			for c in range(self._size):
				if self._board[r][c] == 0:
					for m in self._numbers_left:
						child = self.dup()
						child.play_move(r, c, m)
						child.last_move = (r, c, m)
						children.append(child)

		return children

	def play_move(self, row: int, col: int, move: int) -> bool:
		self._board[row][col] = move
		self._numbers_left.remove(move)
		return not self.over()

	def over(self) -> bool:
		return len(self._numbers_left) == 0

	def result(self) -> int:
		return solve(self._board, 1)

	def __str__(self) -> str:
		s = '\n'
		for i in range(self._size):
			s += ' '
			for a in range(self._size):
				s += str(self._board[i][a]) + (' | ' if a != self._size - 1 else '\n')
			if i != self._size - 1:
				s += '---+' * (self._size - 1) + '---\n'
		return s + '\n'


def get_best_move(board: DetBoard, target_sign: int, first=False) -> ((int, int, int), int):
	if board.over():
		return (-1, -1, -1), board.result()

	children = board.get_children()
	best_result = -target_sign
	best_move = (-1, -1, -1)
	init = False
	for child in children:
		result = get_best_move(child, -target_sign)[1]
		if first:
			print(result)

		if result * target_sign > 0:
			return child.last_move, result
		elif not init or abs(result) < abs(best_result):
			best_move = child.last_move
			best_result = result
			init = True

	return best_move, best_result

def get_human_move() -> ((int, int, int), -1):
	return tuple((int(i) for i in input("Please enter your move: ").split())), -1

def play_game(ai_turn: str, size: int, winning_style: int):
	board = DetBoard(size)
	turn = True
	while not board.over():
		print(board)
		move = None
		if ai_turn == 'both' or turn == (ai_turn == 'first'):
			move = get_best_move(board, winning_style * (1 if turn else -1), True)[0]
		else:
			move = get_human_move()[0]

		board.play_move(move[0], move[1], move[2])

		turn = not turn

	print(board)

	print("First player wins" if winning_style * board.result() > 0 else ("Tie game" if board.result() == 0 else "Second player wins"))

if __name__ == '__main__':
	# d = DetBoard(2)
	play_game('second', 3, 1)
	# d.play_move(0, 0, 1)
	# print(d, len(d.get_children()))
	# print(get_best_move(d, -1, True))
