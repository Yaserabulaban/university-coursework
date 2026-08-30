package model;

import java.util.ArrayList;
import java.util.List;

/**
 * Represents the "Tor" piece in Kwazam Chess.
 * - The Tor moves orthogonally (up, down, left, right) any distance.
 * - It transforms into an "Xor" piece after 2 turns, adding a dynamic layer of
 * strategy.
 * - This piece combines mobility and transformation to enhance gameplay
 * complexity.
 * 
 * **Design Patterns:**
 * - MVC Pattern: Part of the Model layer, encapsulating the behavior and
 * state of the Tor piece.
 * 
 * **OOP Concepts:**
 * - Inheritance: Inherits common attributes and methods from the
 * `KwazamPiece` superclass.
 * - Polymorphism: Overrides the `getValidMoves` method to define its unique
 * movement logic.
 * - Encapsulation: Encapsulates the piece's state and movement rules,
 * ensuring controlled interaction.
 * 
 * **Responsibilities:**
 * - Defines orthogonal movement rules for the Tor piece, allowing movement in
 * straight lines over multiple cells.
 * - Tracks its transformation lifecycle and supports dynamic gameplay by
 * changing into an `Xor` piece.
 * 
 * **Implementation Notes:**
 * - Transformation logic is implemented in `GameController` to maintain central
 * control over game events.
 * - Valid moves are calculated based on board boundaries and potential
 * collisions with other pieces.
 */

public class Tor extends KwazamPiece {

    /**
     * Constructor for initializing a Tor piece.
     * - Sets the initial position, type, and color of the piece.
     * 
     * @param color The color of the piece ("Red" or "Blue").
     * @param x     The starting x-coordinate of the piece.
     * @param y     The starting y-coordinate of the piece.
     * 
     *              **OOP Concept:** Constructor for object initialization.
     *              Written by: Fakhira
     */
    public Tor(String color, int x, int y) {
        super(color, x, y, "Tor");
    }

    /**
     * Calculates the valid moves for the Tor piece.
     * - The Tor moves any distance orthogonally (up, down, left, right).
     * - Movement is blocked by any piece, but the Tor can capture opponent pieces.
     * 
     * @param board The current state of the game board.
     * @return A list of valid moves as [x, y] coordinates.
     * 
     *         **OOP Concept:** Polymorphism - Implements specific movement rules
     *         for the Tor piece.
     *         **Design Pattern:** Strategy Pattern - Encapsulates movement logic
     *         within the Tor class.
     *         Written by: Fakhira
     */
    @Override
    public List<int[]> getValidMoves(KwazamBoard board) {
        List<int[]> validMoves = new ArrayList<>();
        int[][] directions = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } }; // Orthogonal directions

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
     * Transforms the Tor piece into an Xor after 2 turns.
     * - The transformation logic is managed externally in `GameController`.
     * 
     * **OOP Concept:** Polymorphism - Implements a placeholder method to fulfill
     * the contract of the parent class.
     * **Note:** This method is intentionally empty as the transformation logic is
     * centralized in `GameController`.
     * Written by: Fakhira
     */
    @Override
    public void transform() {
        // Logic is implemented in GameController.java
        // via the private void transformPieces() method.
    }
}
