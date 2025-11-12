import tkinter as tk
from tkinter import messagebox, simpledialog
import chess
import math
import time


# Board Evaluation Function
PIECE_VALUES = {
    chess.PAWN: 100,
    chess.KNIGHT: 320,
    chess.BISHOP: 330,
    chess.ROOK: 500,
    chess.QUEEN: 900,
    chess.KING: 20000
}

def evaluate_board(board: chess.Board) -> int:
    """
    Evaluate board from White's perspective.
    Checkmate is prioritized over material.
    """
    if board.is_checkmate():
        # If it's White's turn and checkmate, Black won
        if board.turn == chess.WHITE:
            return -99999
        else:
            return 99999

    if board.is_stalemate() or board.is_insufficient_material():
        return 0  # Draw

    value = 0
    for piece_type in PIECE_VALUES:
        value += len(board.pieces(piece_type, chess.WHITE)) * PIECE_VALUES[piece_type]
        value -= len(board.pieces(piece_type, chess.BLACK)) * PIECE_VALUES[piece_type]

    return value

# Alpha-Beta Minimax Search
def alpha_beta(board: chess.Board, depth: int, alpha: int, beta: int, maximizing: bool) -> int:
    if depth == 0 or board.is_game_over():
        return evaluate_board(board)

    if maximizing:
        max_eval = -math.inf
        for move in board.legal_moves:
            board.push(move)
            eval = alpha_beta(board, depth-1, alpha, beta, False)
            board.pop()
            max_eval = max(max_eval, eval)
            alpha = max(alpha, eval)
            if beta <= alpha:
                break
        return max_eval
    else:
        min_eval = math.inf
        for move in board.legal_moves:
            board.push(move)
            eval = alpha_beta(board, depth-1, alpha, beta, True)
            board.pop()
            min_eval = min(min_eval, eval)
            beta = min(beta, eval)
            if beta <= alpha:
                break
        return min_eval

# AI Move Selection
def select_best_move(board: chess.Board, depth: int) -> chess.Move:
    best_move = None
    best_value = -math.inf if board.turn == chess.WHITE else math.inf

    for move in board.legal_moves:
        board.push(move)
        board_value = alpha_beta(board, depth-1, -math.inf, math.inf, board.turn == chess.BLACK)
        board.pop()

        if board.turn == chess.WHITE:
            if board_value > best_value:
                best_value = board_value
                best_move = move
        else:
            if board_value < best_value:
                best_value = board_value
                best_move = move

    return best_move


# Chess GUI Class
class ChessGUI:
    def __init__(self, master):
        self.master = master
        self.master.title("Chess AI")
        self.board = chess.Board()
        self.selected_square = None

        # Ask difficulty
        self.ai_depth = self.get_ai_depth()

        # Canvas for board
        self.canvas = tk.Canvas(master, width=480, height=480)
        self.canvas.pack()
        self.square_size = 60

        # Draw initial board
        self.draw_board()
        self.canvas.bind("<Button-1>", self.on_click)

    # Difficulty selection
    def get_ai_depth(self):
        choice = simpledialog.askstring("Difficulty", "Select AI difficulty (Easy/Medium/Hard):")
        if choice is None:
            return 3  # default medium
        choice = choice.lower()
        if choice == "easy":
            return 2
        elif choice == "medium":
            return 3
        elif choice == "hard":
            return 4
        else:
            return 3

    # Draw board and pieces
    def draw_board(self):
        self.canvas.delete("all")
        colors = ["#F0D9B5", "#B58863"]
        for rank in range(8):
            for file in range(8):
                x1 = file * self.square_size
                y1 = rank * self.square_size
                x2 = x1 + self.square_size
                y2 = y1 + self.square_size
                color = colors[(rank + file) % 2]
                self.canvas.create_rectangle(x1, y1, x2, y2, fill=color)

        # Draw pieces (text symbols)
        for square in chess.SQUARES:
            piece = self.board.piece_at(square)
            if piece:
                file = chess.square_file(square)
                rank = 7 - chess.square_rank(square)
                x = file * self.square_size + self.square_size // 2
                y = rank * self.square_size + self.square_size // 2
                self.canvas.create_text(x, y, text=piece.symbol(), font=("Arial", 32))

    # Handle human clicks
    def on_click(self, event):
        file = event.x // self.square_size
        rank = 7 - (event.y // self.square_size)
        square = chess.square(file, rank)

        if self.selected_square is None:
            piece = self.board.piece_at(square)
            if piece and piece.color == chess.WHITE:
                self.selected_square = square
        else:
            move = chess.Move(self.selected_square, square)
            if move in self.board.legal_moves:
                self.board.push(move)
                self.selected_square = None
                self.draw_board()
                self.master.update()
                self.check_game_over()
                self.ai_move()
            else:
                self.selected_square = None

    # AI makes move
    def ai_move(self):
        if self.board.is_game_over():
            return
        self.master.update()
        move = select_best_move(self.board, self.ai_depth)
        if move:
            self.board.push(move)
            self.draw_board()
            self.master.update()
            self.check_game_over()

    # Check for game over
    def check_game_over(self):
        if self.board.is_game_over():
            result = self.board.result()
            if self.board.is_checkmate():
                if self.board.turn == chess.WHITE:
                    winner = "AI"
                else:
                    winner = "Human"
                messagebox.showinfo("Game Over", f"Checkmate! {winner} wins!\nResult: {result}")
            else:
                messagebox.showinfo("Game Over", f"Draw!\nResult: {result}")
            self.master.destroy()

# Run GUI
if __name__ == "__main__":
    root = tk.Tk()
    gui = ChessGUI(root)
    root.mainloop()
