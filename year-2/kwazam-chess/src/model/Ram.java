package model;

import java.util.ArrayList;
import java.util.List;

/**
 * Represents the "Ram" piece in Kwazam Chess.
 * - The Ram can only move one step forward in the direction of its color.
 * - When it reaches the edge of the board, its movement reverses direction.
 * - This piece adds strategic depth by limiting its movement while maintaining
 * simplicity.
 * 
 * **Design Patterns:**
 * - MVC Pattern: Part of the Model layer, encapsulating the behavior and
 * state of the Ram piece.
 * 
 * **OOP Concepts:**
 * - Inheritance: Inherits shared attributes and methods from the
 * `KwazamPiece` superclass.
 * - Polymorphism: Overrides the `getValidMoves` and `move` methods to
 * define its specific behavior.
 * - Encapsulation: Encapsulates movement direction and position, ensuring
 * controlled access and updates.
 * 
 * **Responsibilities:**
 * - Calculates valid moves for the Ram piece, ensuring it adheres to its
 * one-step-forward rule.
 * - Manages direction reversal when the Ram reaches the edge of the board.
 * - Ensures the piece cannot skip over or land on allied pieces.
 */

public class Ram extends KwazamPiece {
    private int direction; // Direction of movement: -1 for upward, 1 for downward

    /**
     * Constructor for initializing a Ram piece.
     * - Determines the initial movement direction based on the piece's color.
     * 
     * @param color The color of the piece ("Red" or "Blue").
     * @param x     The starting x-coordinate of the piece.
     * @param y     The starting y-coordinate of the piece.
     * 
     *              OOP Concept: Constructor for object initialization.
     *              Responsibility: Initializes the Ram piece with its color and
     *              position.
     */
    public Ram(String color, int x, int y) {
        super(color, x, y, "Ram");
        this.direction = color.equals("Red") ? -1 : 1; // Default direction based on color
    }

    /**
     * Calculates the valid moves for the Ram piece.
     * - The Ram can move 1 step forward in its current direction.
     * 
     * @param board The current state of the game board.
     * @return A list of valid moves as [x, y] coordinates.
     * 
     *         **OOP Concept:** Polymorphism - Implements specific movement rules
     *         for the Ram piece.
     *         **Design Pattern:** Strategy Pattern - Encapsulates movement logic
     *         within the Ram class.
     */
    @Override
    public List<int[]> getValidMoves(KwazamBoard board) {
        List<int[]> validMoves = new ArrayList<>();
        int newY = this.y + direction; // Calculate the next position in the current direction

        // Check if the new position is valid and empty
        if (board.isValidPosition(this.x, newY) && board.isCellEmpty(this.x, newY) ||
                !board.getPieceAt(this.x, newY).getColor().equals(this.color)) {
            validMoves.add(new int[] { this.x, newY }); // Add the forward move
        }

        return validMoves;
    }

    /**
     * Moves the Ram piece to a new position.
     * - Reverses the movement direction if the Ram moves to the edge of the board.
     * 
     * @param newX The new x-coordinate.
     * @param newY The new y-coordinate.
     * 
     *             **OOP Concept:** Polymorphism - Extends the base `move` behavior
     *             with additional logic for reversing direction.
     */
    @Override
    public void move(int newX, int newY) {
        super.move(newX, newY); // Call the base move logic

        // Reverse direction if the Ram moves to the edge
        if (newY == 0 || newY == 7) {
            direction = -direction;
        }
    }

    /**
     * The Ram piece does not transform.
     * 
     * **OOP Concept:** Polymorphism - Implements a no-op transform method for Ram.
     */
    @Override
    public void transform() {
        // No transformation logic for Ram
    }
}
