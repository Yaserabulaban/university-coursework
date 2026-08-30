package view;

import controller.GameController;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;
import javax.swing.*;
import model.KwazamPiece;

/**
 * Displays the game board and pieces in Kwazam Chess.
 * Responsible for rendering the board, pieces, and highlights for valid moves.
 * This class is part of the View layer in the MVC design pattern, focusing
 * solely on the visual representation
 * of the game state without embedding game logic.
 * 
 * **Design Patterns:**
 * - MVC Pattern: Part of the View layer, it visually represents the Model's
 * state and interacts with the Controller
 * through user input events (via `InputHandler`).
 * - Composite Pattern* The board is composed of individual cells, each of
 * which is drawn and rendered independently.
 * 
 * **OOP Concepts:**
 * - Encapsulation: The board's visual state (e.g., valid moves, flipped
 * orientation) is maintained internally
 * and manipulated through controlled methods like `setValidMoves` and
 * `setFlipped`.
 * - Abstraction: Separates the rendering logic from the game logic,
 * ensuring the View is unaware of how the game state is managed.
 * 
 * **Responsibilities:**
 * - Renders the game board as a grid with alternating colors (like a
 * traditional chessboard).
 * - Draws pieces at their correct positions based on the game state provided by
 * the Controller.
 * - Highlights valid moves for selected pieces to guide the user.
 * - Flips the board visually for the current player, ensuring an intuitive user
 * experience.
 */

public class BoardView extends JPanel {
    private final GameController controller; // Reference to the game controller
    private List<int[]> validMoves = new ArrayList<>(); // Tracks valid moves for highlighting
    private boolean isFlipped = false; // Indicates if the board is flipped for the current player

    /**
     * Constructor to initialize the board view.
     * 
     * @param controller The game controller to handle interactions.
     *                   (OOP: Dependency Injection)
     */
    public BoardView(GameController controller) {
        this.controller = controller; // Controller reference (MVC Pattern)
    }

    /**
     * Sets the valid moves for highlighting.
     * - Flips the coordinates if the board is flipped.
     * 
     * @param moves List of valid moves as [x, y] coordinates.
     *              (OOP: Encapsulation, Abstraction)
     */
    public void setValidMoves(List<int[]> moves) {
        this.validMoves = new ArrayList<>();
        for (int[] move : moves) {
            int x = move[0];
            int y = move[1];

            // Flip coordinates if the board is flipped
            int drawX = isFlipped ? 4 - x : x;
            int drawY = isFlipped ? 7 - y : y;

            this.validMoves.add(new int[] { drawX, drawY });
        }

        repaint(); // Redraw the board with updated highlights
    }

    /**
     * Sets whether the board should be flipped for the current player.
     * 
     * @param flipped True if the board should be flipped, false otherwise.
     *                (OOP: Encapsulation)
     */
    public void setFlipped(boolean flipped) {
        this.isFlipped = flipped;
        repaint(); // Redraw the board to reflect the new orientation
    }

    /**
     * Paints the game board, valid move highlights, and pieces.
     * 
     * @param g The Graphics object used for rendering.
     *          (OOP: Polymorphism via Overriding)
     */
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        // Colors for the checkerboard pattern
        Color lightColor = Color.WHITE;
        Color darkColor = Color.LIGHT_GRAY;

        // Calculate cell dimensions
        int cellWidth = getWidth() / 5;
        int cellHeight = getHeight() / 8;

        // Draw the checkerboard pattern
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 5; col++) {
                g.setColor((row + col) % 2 == 0 ? lightColor : darkColor); // Alternate colors
                g.fillRect(col * cellWidth, row * cellHeight, cellWidth, cellHeight);
            }
        }

        // Highlight valid moves
        g.setColor(new Color(0, 255, 0, 100)); // Transparent green
        for (int[] move : validMoves) {
            int drawX = isFlipped ? 4 - move[0] : move[0];
            int drawY = isFlipped ? 7 - move[1] : move[1];
            g.fillRect(drawX * cellWidth, drawY * cellHeight, cellWidth, cellHeight);
        }

        // Draw the pieces
        List<KwazamPiece> pieces = controller.getPieces(); // Polymorphism: Uses the KwazamPiece abstraction
        for (KwazamPiece piece : pieces) {
            // Adjust coordinates so the current player's pieces are always at the bottom
            int drawX = piece.getPosition()[0];
            int drawY = piece.getPosition()[1];
            if (isFlipped) {
                drawX = 4 - drawX; // Flip X-coordinate
                drawY = 7 - drawY; // Flip Y-coordinate
            }
            drawPiece(g, piece, drawX, drawY, cellWidth, cellHeight);
        }

        // Draw grid lines
        g.setColor(Color.BLACK);
        for (int i = 0; i <= 5; i++) {
            g.drawLine(i * cellWidth, 0, i * cellWidth, getHeight()); // Vertical lines
        }
        for (int i = 0; i <= 8; i++) {
            g.drawLine(0, i * cellHeight, getWidth(), i * cellHeight); // Horizontal lines
        }
    }

    /**
     * Draws a single piece on the board.
     *
     * @param g          The Graphics object used for rendering.
     * @param piece      The piece to draw (Polymorphism: KwazamPiece abstraction).
     * @param x          The x-coordinate for drawing.
     * @param y          The y-coordinate for drawing.
     * @param cellWidth  The width of each cell.
     * @param cellHeight The height of each cell.
     */
    private void drawPiece(Graphics g, KwazamPiece piece, int x, int y, int cellWidth, int cellHeight) {
        String imagePath = "images/" + piece.getColor().toLowerCase() + "_" + piece.getType().toLowerCase() + ".png";
        Image pieceImage = Toolkit.getDefaultToolkit().getImage(imagePath);

        if (pieceImage != null) {
            // Draw the image
            g.drawImage(pieceImage, x * cellWidth + 5, y * cellHeight + 5, cellWidth - 10, cellHeight - 10, this);
        } else {
            // Draw a placeholder rectangle if the image fails to load
            g.setColor(piece.getColor().equals("Red") ? Color.RED : Color.BLUE);
            g.fillRect(x * cellWidth + 5, y * cellHeight + 5, cellWidth - 10, cellHeight - 10);
        }
    }
}