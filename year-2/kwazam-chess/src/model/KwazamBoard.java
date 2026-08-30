package model;

import java.util.ArrayList;
import java.util.List;

/**
 * Represents the game board for Kwazam Chess.
 * This class manages the state of the board, validates moves, and interacts
 * with pieces.
 * 
 * **Design Patterns:**
 * - MVC Pattern: Acts as part of the Model layer, encapsulating the board's
 * state and providing
 * methods for interaction and validation of moves.
 * - Factory Method Pattern: The methods like `addRam`, `addSau`, `addBiz`,
 * etc., encapsulate
 * the creation logic for different pieces, centralizing the instantiation of
 * game objects based
 * on specific requirements.
 * 
 * **OOP Concepts:**
 * - Encapsulation: The internal representation of the board as a 2D array
 * is hidden, and all
 * interactions are controlled through public methods.
 * - Abstraction: Simplifies the interaction with the board by providing
 * high-level methods
 * such as `addPiece`, `movePiece`, and `isGameOver`.
 * - Composition: Combines multiple `KwazamPiece` objects to form the entire
 * game board.
 * - Responsibility Segregation: Each method has a single responsibility,
 * such as validating a move,
 * checking if a cell is empty, or managing the state of a specific piece.
 * 
 * **Responsibilities:**
 * - Initializes the board and places pieces in their starting positions.
 * - Validates the state and boundaries of the board during gameplay.
 * - Provides methods to move pieces, retrieve piece data, and manage
 * transformations.
 * - Tracks and manipulates the positions of all pieces on the board.
 * - Supports game-ending logic by determining when a "Sau" piece is captured.
 * 
 */

public class KwazamBoard {
    private static final int ROWS = 8; // Number of rows in the board
    private static final int COLUMNS = 5; // Number of columns in the board
    private final KwazamPiece[][] board; // 2D array representing the board grid

    /**
     * Constructor to initialize the game board.
     * Places all the pieces in their starting positions.
     * 
     * **OOP Concept: Encapsulation**
     * - The board is initialized and populated with pieces internally.
     * Written by: Zainab
     */
    public KwazamBoard() {
        board = new KwazamPiece[ROWS][COLUMNS];
        initializeBoard();
    }

    /**
     * Initializes the board with the starting positions of all pieces.
     * Written by: Zainab
     */
    private void initializeBoard() {
        placeRedPiece();
        placeBluePiece();
    }

    /**
     * Places the red pieces on the board.
     * Written by: Zainab
     */
    public void placeRedPiece() {
        String color = "Red";
        addAllPiece(color);
    }

    /**
     * Places the blue pieces on the board.
     * Written by: Zainab
     */
    public void placeBluePiece() {
        String color = "Blue";
        addAllPiece(color);
    }

    /**
     * Adds all the pieces of a specific color to their correct positions.
     * 
     * @param color The color of the pieces to add ("Red" or "Blue").
     *              Written by: Zainab
     */
    public void addAllPiece(String color) {
        addRam(color);
        addBiz(color);
        addTor(color);
        addXor(color);
        addSau(color);
    }

    /**
     * Adds the Ram pieces to their starting positions.
     * Written by: Zainab
     */
    public void addRam(String color) {
        int row = (color.equals("Blue")) ? 1 : 6;
        for (int col = 0; col < 5; col++) {
            board[row][col] = new Ram(color, col, row);
        }
    }

    /**
     * Adds the Sau piece to its starting position.
     * Written by: Zainab
     */
    public void addSau(String color) {
        int row = (color.equals("Blue")) ? 0 : 7;
        int col = 2; // Fixed column for Sau
        board[row][col] = new Sau(color, col, row);
    }

    /**
     * Adds the Xor piece to its starting position.
     * Written by: Zainab
     */
    public void addXor(String color) {
        int row = (color.equals("Blue")) ? 0 : 7;
        int col = (color.equals("Blue")) ? 4 : 0;
        board[row][col] = new Xor(color, col, row);
    }

    /**
     * Adds the Tor piece to its starting position.
     * Written by: Zainab
     */
    public void addTor(String color) {
        int row = (color.equals("Blue")) ? 0 : 7;
        int col = (color.equals("Blue")) ? 0 : 4;
        board[row][col] = new Tor(color, col, row);
    }

    /**
     * Adds the Biz pieces to their starting positions.
     * Written by: Zainab
     */
    public void addBiz(String color) {
        int row = (color.equals("Blue")) ? 0 : 7;
        board[row][1] = new Biz(color, 1, row);
        board[row][3] = new Biz(color, 3, row);
    }

    /**
     * Adds a piece to the specified position on the board.
     * 
     * @param piece The piece to add to the board.
     *              Written by: Zainab
     */
    public void addPiece(KwazamPiece piece) {
        int x = piece.getPosition()[0];
        int y = piece.getPosition()[1];
        if (isValidPosition(x, y)) {
            board[y][x] = piece;
        }
    }

    /**
     * Checks if the given position is within the bounds of the board.
     * 
     * @param x The x-coordinate to check.
     * @param y The y-coordinate to check.
     * @return True if the position is valid, false otherwise.
     *         Written by: Zainab
     */
    public boolean isValidPosition(int x, int y) {
        return x >= 0 && x < COLUMNS && y >= 0 && y < ROWS;
    }

    /**
     * Checks if the cell at the given position is empty.
     * 
     * @param x The x-coordinate of the cell.
     * @param y The y-coordinate of the cell.
     * @return True if the cell is empty, false otherwise.
     *         Written by: Zainab
     */
    public boolean isCellEmpty(int x, int y) {
        return isValidPosition(x, y) && board[y][x] == null;
    }

    /**
     * Moves a piece from one position to another.
     * 
     * **OOP Concept: Encapsulation**
     * - The movement logic is encapsulated within this method.
     * 
     * @param fromX The starting x-coordinate.
     * @param fromY The starting y-coordinate.
     * @param toX   The destination x-coordinate.
     * @param toY   The destination y-coordinate.
     * @return True if the move is successful, false otherwise.
     *         Written by: Yaser Abulaban
     */
    public boolean movePiece(int fromX, int fromY, int toX, int toY) {
        KwazamPiece piece = board[fromY][fromX];
        KwazamPiece targetPiece = board[toY][toX];

        if (!isValidPosition(fromX, fromY) || !isValidPosition(toX, toY)) {
            System.out.println("Invalid move: Out of bounds.");
            return false;
        }

        if (piece == null) {
            System.out.println("Invalid move: No piece to move.");
            return false;
        }

        boolean isValidMove = piece.getValidMoves(this).stream().anyMatch(move -> move[0] == toX && move[1] == toY);
        if (!isValidMove) {
            System.out.println("Invalid move: (" + toX + ", " + toY + ") is not a valid destination.");
            return false;
        }

        if (targetPiece != null && !targetPiece.getColor().equals(piece.getColor())) {
            SoundHandler.playSound("sounds/capture.wav"); // Play capture sound
        }

        board[toY][toX] = piece;
        board[fromY][fromX] = null;
        piece.move(toX, toY);
        System.out
                .println(piece.getType() + " moved from (" + fromX + ", " + fromY + ") to (" + toX + ", " + toY + ")");
        return true;
    }

    /**
     * Retrieves a piece at the given position.
     * 
     * @param x The x-coordinate of the position.
     * @param y The y-coordinate of the position.
     * @return The piece at the position, or null if the cell is empty.
     *         Written by: Yaser Abulaban
     */
    public KwazamPiece getPieceAt(int x, int y) {
        if (!isValidPosition(x, y)) {
            return null;
        }
        return board[y][x];
    }

    /**
     * Checks if the game is over by verifying if the current player's Sau exists.
     * 
     * @param currentPlayer The current player's color.
     * @return True if the game is over; false otherwise.
     *         Written by: Zainab
     */
    public boolean isGameOver(String currentPlayer) {
        return getAllPieces().stream()
                .noneMatch(piece -> piece instanceof Sau && !piece.getColor().equals(currentPlayer));
    }

    /**
     * Retrieves all pieces currently on the board.
     * 
     * @return A list of all KwazamPiece objects on the board.
     *         Written by: Yaser Abulaban
     */
    public List<KwazamPiece> getAllPieces() {
        List<KwazamPiece> pieces = new ArrayList<>();
        for (int y = 0; y < ROWS; y++) {
            for (int x = 0; x < COLUMNS; x++) {
                if (board[y][x] != null) {
                    pieces.add(board[y][x]);
                }
            }
        }
        return pieces;
    }

    /**
     * Clears the board by setting all cells to null.
     * Written by: Yaser Abulaban
     */
    public void clearBoard() {
        for (int y = 0; y < ROWS; y++) {
            for (int x = 0; x < COLUMNS; x++) {
                board[y][x] = null;
            }
        }
        System.out.println("Board cleared.");
    }

    /**
     * Replaces a piece on the board with a new piece.
     * 
     * @param newPiece The new piece to place on the board.
     * @param x        The x-coordinate of the position.
     * @param y        The y-coordinate of the position.
     *                 Written by: Yaser Abulaban
     */
    public void replacePiece(KwazamPiece newPiece, int x, int y) {
        if (isValidPosition(x, y)) {
            board[y][x] = newPiece;
        }
    }
}