#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <list>

#include "CanvasContext.h"

char buffer[1024];

void log(char* pattern, ...) {
	va_list args;
	va_start(args, pattern);
	vsprintf(buffer, pattern, args);
	va_end(args);
		
	val console = val::global("console");
	console.call<void>("log", std::string(buffer));
}

struct square {
public:
	int row, column;
	square(int row, int column);
	square() {};
};

square::square(int row, int column) {
	this->row = row;
	this->column = column;
}

class Board {
	char *board;
	int m_rows, m_columns, m_num_mines, m_mines_marked;
public :
	Board(int rows, int columns, int num_mines);
	~Board();
	void printMines();
	int rows();
	int columns();
	bool isCovered(int row, int column);
	bool isFlaged(int row, int column);
	bool isMined(int row, int column);
	int number(int row, int cloumn);
	void toggleFlag(int row, int cloumn);
	void uncover(int row, int cloumn);
	void addAdjacentSquares(std::list<square> &l, square s);
};

#define NTH_HAS_MINE(n) (board[n] & 16)
#define MINE_NTH(n) board[n] |= 16
#define SQUARE(row, column) (board[(row) * m_columns + (column)])
#define MINE(row, column) (SQUARE(row, column) & 16)
#define SET_MINE(row, column) SQUARE(row, column) |= 16
#define EXPOSED(row, column) (SQUARE(row, column) & 32)
#define SET_EXPOSED(row, column) SQUARE(row, column) |= 32
#define MARKED(row, column) (SQUARE(row, column) & 64)
#define TOGGLE_MARKED(row, column) SQUARE(row, column) ^= 64
#define NUMBER(row, column) (SQUARE(row, column) & 15)
#define SET_NUMBER(row, column, number) SQUARE(row, column) |= number

int adjacent_squares[8][2] = {
	{-1, -1}, {-1, 0}, {-1, 1},
	{0, -1},           {0, 1},
	{1, -1}, {1, 0}, {1, 1}
};

void Board::addAdjacentSquares(std::list<square> &l, square s) {
	for (int i = 0; i < 8; i++) {
		int row = s.row + adjacent_squares[i][0];
		int column = s.column + adjacent_squares[i][1];
		if (row >= 0 && row < m_rows && column >= 0 && column < m_columns) {
			l.push_front(square(row, column));
		}
	}
}

Board::Board(int rows, int columns, int num_mines) {
	this->m_rows = rows;
	this->m_columns = columns;
	this->m_num_mines = num_mines;
	int board_size = rows * columns;
	board = (char *) calloc(board_size, sizeof(char));
	for (int m = 0; m < num_mines; m++) {
		bool found = false;
		while (!found) {
			int candidate = rand() % board_size;
			if (! NTH_HAS_MINE(candidate)) {
				MINE_NTH(candidate);
				found = true;
			}
		}
	}
	for (int row = 0; row < rows; row ++) {
		for (int column = 0; column < columns; column ++) {
			int number = 0;
			for (int adj = 0; adj < 8; adj ++) {
				int adj_row = row + adjacent_squares[adj][0];
				int adj_column = column + adjacent_squares[adj][1];
				if(adj_row >= 0 && adj_row < m_rows && adj_column >= 0 && adj_column < m_columns && MINE(adj_row, adj_column)) {
					number ++;
				}
			}
			SET_NUMBER(row, column, number);
		}
	}
}

Board::~Board() {
	free(board);
}

void Board::printMines() {
	for (int row = 0; row < m_rows; row ++) {
		for (int column = 0; column < m_columns; column ++) {
			if (MINE(row, column)) {
				printf("*");
			} else {
				printf("%d", NUMBER(row, column));
			}
		}
		printf("\n");
	}
}

int Board::rows() { return m_rows; }
int Board::columns() { return m_columns; }
bool Board::isCovered(int row, int column) { return ! EXPOSED(row, column); }
bool Board::isFlaged(int row, int column) { return MARKED(row, column); }
bool Board::isMined(int row, int column) { return MINE(row, column); }
int Board::number(int row, int column) { return NUMBER(row, column); }
void Board::toggleFlag(int row, int column) { TOGGLE_MARKED(row, column); }
void Board::uncover(int row, int column) { SET_EXPOSED(row, column); }

class BoardDrawer {
	CanvasRenderingContext2D *m_ctx;
	Board *m_board;
	int m_width, m_height;
public :
	BoardDrawer(CanvasRenderingContext2D *ctx, int width,int height);
	void setBoard(Board *board);
	void resetSize(int width, int height);
	void drawBoard();
	void drawSquare(int row, int col);
	int width() { return m_width; }
	int height() { return m_height; }
	void hitTest(square* hit, int x, int y);
private:
	void setTransform();
	void drawCovered(int row, int col);
	void drawEmpty(int row, int col, int number);
	void drawFlag(int row, int col);
	void drawMine(int row, int col);
};

BoardDrawer::BoardDrawer(CanvasRenderingContext2D *ctx, int width, int height) {
	m_ctx = ctx;
	m_width = width;
	m_height = height;
	m_board = NULL;
}

void BoardDrawer::setBoard(Board *board) {
	m_board = board;
	setTransform();
	drawBoard();
}

void BoardDrawer::resetSize(int width, int height) {
	m_width = width;
	m_height = height;
	if (m_board) {
		setTransform();
		drawBoard();
	}
}

void BoardDrawer::drawBoard() {
	printf("hi there");
	for (int row = 0; row < m_board->rows(); row++) {
		for (int column = 0; column < m_board->columns(); column++) {
			drawSquare(row, column);
		}
	}
}

void BoardDrawer::setTransform() {
	m_ctx->setTransform(double(m_width) / double(10 * (m_board->columns())), 0,
						0, double(m_height) / double(10 * (m_board->rows())), 0, 0);
}

void BoardDrawer::drawSquare(int row, int col) {
	if (m_board->isCovered(row, col)) {
		if (m_board->isFlaged(row, col)) {
			drawFlag(row, col);
		} else {
			drawCovered(row, col);
		}
	} else {
		if (m_board->isMined(row, col)) {
			drawMine(row, col);
		} else {
			drawEmpty(row, col, m_board->number(row, col));
		}
	}
}

void BoardDrawer::drawCovered(int row, int col) {
	m_ctx->fillRect(col * 10 + 1, row * 10 + 1, 8, 8);
}

void BoardDrawer::drawEmpty(int row, int col, int number) {
	m_ctx->fillRect(col * 10, row * 10, 10, 10);
	m_ctx->clearRect(col * 10 + 1, row * 10 + 1, 8, 8);
	if (number > 0) {
		sprintf(buffer, "%u", number);
		m_ctx->fillText(std::string(buffer), col * 10 + 2, row * 10 + 8.5);
	}
}

void BoardDrawer::drawFlag(int row, int col) {
	m_ctx->clearRect(col * 10 + 1, row * 10 + 1, 8, 8);
	m_ctx->beginPath();
	m_ctx->moveTo(col * 10 + 1, row * 10 + 1);
	m_ctx->lineTo(col * 10 + 9, row * 10 + 1);
	m_ctx->lineTo(col * 10 + 1, row * 10 + 9);
	m_ctx->closePath();
	m_ctx->fill();
}

void BoardDrawer::drawMine(int row, int col) {
	m_ctx->clearRect(col * 10, row * 10, 10, 10);
	m_ctx->beginPath();
	m_ctx->arc(col * 10 + 5, row * 10 + 5, 4.5, 0, 2 * M_PI);
	m_ctx->stroke();
}

void BoardDrawer::hitTest(square* hit, int x, int y) {
	hit->row = int((double(y) / double(m_height)) * double(m_board->rows()));
	hit->column = int((double(x) / double(m_width)) * double(m_board->columns()));
}

class Game {
	Board *m_board;
	BoardDrawer *m_board_drawer;
	int m_hit_row, m_hit_column;
	bool m_game_in_play;
	emscripten::val m_canvas;
public:
	Game(emscripten::val canvas);
	~Game();
	void canvasResized();
	void newBoard(int rows, int columns, int mines);
	void click(int x, int y);
	void altClick(int x, int y);
};

Game::Game(emscripten::val canvas) : m_canvas(canvas) {
	m_board = NULL;
	m_board_drawer = NULL;
	emscripten::val context = canvas.call<emscripten::val>("getContext", std::string("2d"));
	m_board_drawer = new BoardDrawer(new CanvasRenderingContext2D(context), m_canvas["width"].as<int>(), m_canvas["height"].as<int>());
	m_game_in_play = false;
}

Game::~Game() {
	delete m_board;
	delete m_board_drawer;
}

void Game::canvasResized() {
	m_board_drawer->resetSize(m_canvas["width"].as<int>(), m_canvas["height"].as<int>());
}

void Game::newBoard(int rows, int columns, int mines) {
	if (m_board) {
		delete m_board;
	}
	m_board = new Board(rows, columns, mines);
	m_board_drawer->setBoard(m_board);
	m_game_in_play = true;
}

void Game::click(int x, int y) {
	if (!m_game_in_play) {
		return;
	}
	square s;
	m_board_drawer->hitTest(&s, x, y);
	if (m_board->isCovered(s.row, s.column)) {
		m_board->uncover(s.row, s.column);
		m_board_drawer->drawSquare(s.row, s.column);
		if (m_board->isMined(s.row, s.column)) {
			m_game_in_play = false;
			return;
		}
		std::list<square> adjacent_squares;
		adjacent_squares.push_front(s);
		while (!adjacent_squares.empty()) {
			square &sq = adjacent_squares.front();
			if (m_board->number(sq.row, sq.column) == 0) {
				std::list<square> candidates;
				m_board->addAdjacentSquares(candidates, sq);
				for (std::list<square>::iterator iter = candidates.begin(); iter != candidates.end(); iter++) {
					if (m_board->isCovered(iter->row, iter->column)) {
						m_board->uncover(iter->row, iter->column);
						m_board_drawer->drawSquare(iter->row, iter->column);
						adjacent_squares.push_back(*iter);
					}
				}
			}
			adjacent_squares.pop_front();
		}
	}
}

void Game::altClick(int x, int y) {
	if (!m_game_in_play) {
		return;
	}
	square s;
	m_board_drawer->hitTest(&s, x, y);
	if (m_board->isCovered(s.row, s.column)) {
		m_board->toggleFlag(s.row, s.column);
		m_board_drawer->drawSquare(s.row, s.column);
	}
}

EMSCRIPTEN_BINDINGS(my_module) {
    class_<Game>("Game")
    	.constructor<emscripten::val>()
    	.function("canvasResized", &Game::canvasResized)
    	.function("newBoard", &Game::newBoard)
		.function("click", &Game::click)
		.function("altClick", &Game::altClick)
    	;
}

