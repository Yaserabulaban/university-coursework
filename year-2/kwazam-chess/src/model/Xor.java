package model;

import java.util.ArrayList;
import java.util.List;

/**
 * Represents the "Xor" piece in Kwazam Chess.
 * - The Xor moves diagonally any distance, providing flexible mobility across
 * the board.
 * - It transforms into a "Tor" piece after 2 turns, introducing a layer of
 * strategic complexity.
 * - This piece balances dynamic transformation and long-range movement to add
 * depth to gameplay.
 * 
 * **Design Patterns:**
 * - MVC Pattern: Part of the Model layer, encapsulating the behavior and
 * state of the Xor piece.
 * 
 * **OOP Concepts:**
 * - Inheritance: Inherits common attributes and methods from the
 * `KwazamPiece` superclass.
 * - Polymorphism: Overrides the `getValidMoves` method to define its unique
 * diagonal movement logic.
 * - Encapsulation: Encapsulates the piece's state and movement rules,
 * ensuring controlled interaction.
 * 
 * **Responsibilities:**
 * - Defines diagonal movement rules for the Xor piece, allowing it to traverse
 * the board with versatility.
 * - Tracks its transformation lifecycle and supports dynamic gameplay by
 * changing into a `Tor` piece.
 * 
 * **Implementation Notes:**
 * - Transformation logic is centralized in `GameController` for consistency
 * across the game.
 * - Valid moves are calculated considering board boundaries and collisions with
 * other pieces.
 */

public class Xor extends KwazamPiece {

    /**
     * Constructor for initializing an Xor piece.
     * - Sets the initial position, type, and color of the piece.
     * 
     * @param color The color of the piece ("Red" or "Blue").
     * @param x     The starting x-coordinate of the piece.
     * @param y     The starting y-coordinate of the piece.
     * 
     *              **OOP Concept:** Constructor for object initialization.
     */
    public Xor(String color, int x, int y) {
        super(color, x, y, "Xor");
    }

    /**
     * Calculates the valid moves for the Xor piece.
     * - The Xor moves any distance diagonally.
     * - Movement is blocked by any piece, but the Xor can capture opponent pieces.
     * 
     * @param board The current state of the game board.
     * @return A list of valid moves as [x, y] coordinates.
     * 
     *         **OOP Concept:** Polymorphism - Implements specific movement rules
     *         for the Xor piece.
     *         **Design Pattern:** Strategy Pattern - Encapsulates movement logic
     *         within the Xor class.
     */
    @Override
    public List<int[]> getValidMoves(KwazamBoard board) {
        List<int[]> validMoves = new ArrayList<>();
        int[][] directions = { { 1, 1 }, { -1, -1 }, { 1, -1 }, { -1, 1 } }; // Diagonal directions

        for (int[] dir : directions) {
            int newX = this.x;
            int newY = this.y;
            while (true) {
                newX += dir[0];
                newY += dir[1];
                if (!board.isValidPosition(newX, newY))
                    break; // Out of bounds
                if (board.isCellEmpty(newX, newY)) {
                    validMoves.add(new int[] { newX, newY });
                } else {
                    if (!board.getPieceAt(newX, newY).getColor().equals(this.color)) {
                        validMoves.add(new int[] { newX, newY }); // Capture opponent’s piece
                    }
                    break; // Stop after hitting any piece
                }
            }
        }

        return validMoves;
    }

    /**
     * Transforms the Xor piece into a Tor after 2 turns.
     * - The transformation logic is managed externally in `GameController`.
     * 
     * **OOP Concept:** Polymorphism - Implements a placeholder method to fulfill
     * the contract of the parent class.
     * **Note:** This method is intentionally empty as the transformation logic is
     * centralized in `GameController`.
     */
    @Override
    public void transform() {
        // Logic is implemented in GameController.java
        // via the private void transformPieces() method.
    }
}
