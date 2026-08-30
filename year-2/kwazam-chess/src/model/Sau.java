package model;

import java.util.ArrayList;
import java.util.List;

/**
 * Represents the "Sau" piece in Kwazam Chess.
 * - The Sau is a critical piece, as its capture ends the game.
 * - It moves one step in any direction, making it versatile but vulnerable.
 * - This piece embodies strategic importance and requires careful protection.
 * 
 * **Design Patterns:**
 * - MVC Pattern: Part of the Model layer, encapsulating the behavior and
 * state of the Sau piece.
 * 
 * **OOP Concepts:**
 * - Inheritance: Inherits shared attributes and methods from the
 * `KwazamPiece` superclass.
 * - Polymorphism: Overrides the `getValidMoves` method to define its unique
 * movement logic.
 * - Encapsulation: Encapsulates position and movement logic, ensuring
 * controlled access and updates.
 * 
 * **Responsibilities:**
 * - Calculates valid moves for the Sau piece, allowing movement in all
 * directions by one step.
 * - Determines capture vulnerability, as the game's win/lose condition hinges
 * on this piece.
 * 
 */

public class Sau extends KwazamPiece {

    /**
     * Constructor for initializing a Sau piece.
     * - Sets the initial position and type of the piece.
     * 
     * @param color The color of the piece ("Red" or "Blue").
     * @param x     The starting x-coordinate of the piece.
     * @param y     The starting y-coordinate of the piece.
     * 
     *              **OOP Concept:** Constructor for object initialization.
     */
    public Sau(String color, int x, int y) {
        super(color, x, y, "Sau");
    }

    /**
     * Calculates the valid moves for the Sau piece.
     * - The Sau can move one step in any direction (orthogonal or diagonal).
     * - A move is valid if the destination is within bounds and either empty or
     * occupied by an opponent's piece.
     * 
     * @param board The current state of the game board.
     * @return A list of valid moves as [x, y] coordinates.
     * 
     *         **OOP Concept:** Polymorphism - Implements specific movement rules
     *         for the Sau piece.
     *         **Design Pattern:** Strategy Pattern - Encapsulates movement logic
     *         within the Sau class.
     */
    @Override
    public List<int[]> getValidMoves(KwazamBoard board) {
        List<int[]> validMoves = new ArrayList<>();
        int[][] directions = { // All possible moves (orthogonal and diagonal)
                { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }, // Up, down, right, left
                { 1, 1 }, { -1, -1 }, { 1, -1 }, { -1, 1 } // Diagonals
        };

        for (int[] dir : directions) {
            int newX = this.x + dir[0];
            int newY = this.y + dir[1];
            // Check if the destination is within bounds and valid
            if (board.isValidPosition(newX, newY)
                    && (board.isCellEmpty(newX, newY) || !board.getPieceAt(newX, newY).getColor().equals(this.color))) {
                validMoves.add(new int[] { newX, newY });
            }
        }

        return validMoves;
    }

    /**
     * The Sau piece does not transform.
     * 
     * **OOP Concept:** Polymorphism - Implements a no-op transform method for Sau.
     */
    @Override
    public void transform() {
        // No transformation logic for Sau
    }
}
