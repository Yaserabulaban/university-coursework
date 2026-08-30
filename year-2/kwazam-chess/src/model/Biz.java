package model;

import java.util.ArrayList;
import java.util.List;

/**
 * Represents the "Biz" piece in Kwazam Chess.
 * - The Biz moves in an L-shape (3x2 or 2x3), similar to the knight in
 * traditional chess.
 * - It can skip over other pieces but cannot land on a square occupied by a
 * piece of the same color.
 * - This class defines the unique movement behavior of the Biz piece while
 * adhering to common rules for all pieces.
 * 
 * **Design Patterns:**
 * - MVC Pattern: Part of the Model layer, encapsulating the behavior and
 * state of the Biz piece.
 * 
 * **OOP Concepts:**
 * - Inheritance: Inherits shared attributes and methods from the
 * `KwazamPiece` superclass.
 * - Polymorphism: Overrides the `getValidMoves` method to define the
 * specific movement behavior of the Biz piece.
 * - Encapsulation: Restricts direct access to its attributes, ensuring
 * controlled interaction through methods.
 * 
 * **Responsibilities:**
 * - Calculates valid moves for the Biz piece based on its unique L-shaped
 * movement rules.
 * - Ensures movement adheres to game constraints, such as staying within board
 * boundaries and not occupying squares with allied pieces.
 */

public class Biz extends KwazamPiece {

    /**
     * Constructor for initializing a Biz piece.
     * 
     * @param color The color of the piece ("Red" or "Blue").
     * @param x     The starting x-coordinate of the piece.
     * @param y     The starting y-coordinate of the piece.
     *              **OOP Concept:** Constructor for object initialization.
     */
    public Biz(String color, int x, int y) {
        super(color, x, y, "Biz");
    }

    /**
     * Calculates the valid moves for the Biz piece.
     * The Biz moves in an L-shape (3x2 or 2x3) in any orientation.
     * 
     * @param board The current state of the game board.
     * @return A list of valid moves as [x, y] coordinates.
     * 
     *         **OOP Concept:**
     *         - Polymorphism: Implements specific movement rules for the Biz piece.
     * 
     *         **Design Pattern:** Encapsulates movement behavior within the Biz
     *         class, following the Strategy Pattern.
     */
    @Override
    public List<int[]> getValidMoves(KwazamBoard board) {
        List<int[]> validMoves = new ArrayList<>();
        int[][] knightMoves = {
                { 2, 1 }, { 2, -1 }, { -2, 1 }, { -2, -1 }, // Horizontal L-shapes
                { 1, 2 }, { 1, -2 }, { -1, 2 }, { -1, -2 } // Vertical L-shapes
        };

        // Check all potential L-shape moves
        for (int[] move : knightMoves) {
            int newX = this.x + move[0];
            int newY = this.y + move[1];
            // Ensure the move is valid (within bounds and not occupied by an allied piece)
            if (board.isValidPosition(newX, newY) &&
                    (board.isCellEmpty(newX, newY) || !board.getPieceAt(newX, newY).getColor().equals(this.color))) {
                validMoves.add(new int[] { newX, newY });
            }
        }
        return validMoves;
    }

    /**
     * The Biz piece does not transform.
     * 
     * **OOP Concept:** Polymorphism - Implements a no-op transform method for Biz.
     */
    @Override
    public void transform() {
        // No transformation logic for Biz
    }
}
