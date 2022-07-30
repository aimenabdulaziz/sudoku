# Koding Kegs
# Sudoku GUI, Spring 2022

from tkinter import Tk, Canvas, Frame, Button, BOTH, TOP, BOTTOM

MARGIN = 20  # Pixels around the board
SIDE = 50  # Width of every board cell.
WIDTH = HEIGHT = MARGIN * 2 + SIDE * 9  # Width and height of the whole board


# Class that inherits from Tkinter Frame
class SudokuUI(Frame):
  """
  The Tkinter UI, responsible for drawing the board and accepting user input.
  """
  def __init__(self, parent, mats):
    self.mats = mats
    self.parent = parent
    Frame.__init__(self, parent)

    self.row, self.col = 0, 0

    self.__initUI()


  # initialise the UI
  def __initUI(self):
      self.parent.title("Sudoku")
      self.pack(fill=BOTH, expand=1)
      self.canvas = Canvas(self,
                           width=WIDTH,
                           height=HEIGHT)
      self.canvas.pack(fill=BOTH, side=TOP)

      self.__draw_grid()

      idx = [i for i in range(len(mats))]
      self.parent.after(1000, self.__draw_puzzle, enumerate(idx))


  # draw the initial grid
  def __draw_grid(self):
    """
    Draws grid divided with blue lines into 3x3 squares
    """
    for i in range(10):
      color = "red" if i % 3 == 0 else "gray"

      x0 = MARGIN + i * SIDE
      y0 = MARGIN
      x1 = MARGIN + i * SIDE
      y1 = HEIGHT - MARGIN
      self.canvas.create_line(x0, y0, x1, y1, fill=color)

      x0 = MARGIN
      y0 = MARGIN + i * SIDE
      x1 = WIDTH - MARGIN
      y1 = MARGIN + i * SIDE
      self.canvas.create_line(x0, y0, x1, y1, fill=color)


  # draw the puzzle. Original cells are drawn in black
  # others are drawn in blue
  def __draw_puzzle(self, idx_iter):
    n, b = next(idx_iter)
    self.canvas.delete("numbers")
    for i in range(9):
      for j in range(9):
        answer = self.mats[n][i][j]
        if answer != 0:
          x = MARGIN + j * SIDE + SIDE / 2
          y = MARGIN + i * SIDE + SIDE / 2
          original = self.mats[0][i][j]
          color = "black" if answer == original else "blue"
          self.canvas.create_text(
            x, y, text=answer, tags="numbers", fill=color
          )
    self.parent.after(1000, self.__draw_puzzle, idx_iter)

# Read the file created during the algorithm's run
lines = []
with open('algo_process1.txt', 'r') as f:
  lines = f.readlines()

length = len(lines)
og = []
i = 0
# to store the matrices
mats = []
while i < length:
  j = 0
  matrix = []
  while j < 9 and i < length:
    # split each line into spaces
    row = lines[i].split(' ')
    matrix.append(row)
    j += 1
    i += 1

  # for any file formatting errors
  if j == 9:
    mats.append(matrix)
  # for the empty line in the middle
  i += 1

# Display the GUI
root = Tk()
root.geometry("%dx%d" % (WIDTH, HEIGHT + 40))
SudokuUI(root, mats)
# start the gui
root.mainloop()
