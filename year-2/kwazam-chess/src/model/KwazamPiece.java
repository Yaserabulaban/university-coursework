package model;

import java.util.List;

/**
 * Abstract class representing a generic piece in Kwazam Chess.
 * This class provides a blueprint for defining different types of pieces,
 * including their
 * attributes and fundamental behaviors such as movement and transformations.
 * 
 * **Design Patterns:**
 * - MVC Pattern: Part of the Model layer, encapsulating the behavior and
 * attributes of a game piece.
 * - Template Method Pattern: The abstract methods `getValidMoves` and
 * `transform` define the blueprint for subclasses to implement specific
 * behavior while maintaining consistency across all pieces.
 * 
 * **OOP Concepts:**
 * - Abstraction: Defines a high-level concept for game pieces, leaving
 * implementation details
 * of specific moves and transformations to subclasses.
 * - Inheritance: Provides common attributes (e.g., `color`, `x`, `y`,
 * `type`) and methods (e.g.,`getPosition`, `move`) that are inherited
 * by all specific piece types (e.g.,`Ram`, `Tor`).
 * - Polymorphism: Abstract methods like `getValidMoves` and `transform`
 * allow different pieces to define unique implementations, enabling dynamic
 * behavior at runtime.
 * - Encapsulation: Protects the internal state of the piece, such as
 * position (`x`, `y`) and type,
 * through controlled methods and attributes.
 * 
 * **Responsibilities:**
 * - Stores the shared attributes of all pieces, including their color,
 * position, and type.
 * - Provides a framework for specific pieces to implement their movement and
 * transformation logic.
 * - Centralizes movement-related updates via the `move` method.
 * - Ensures consistent interaction with the board by standardizing piece
 * behavior.
 * 
 */

public abstract class KwazamPiece {
    protected String color; // "Red" or "Blue"
    protected int x; // X-coordinate of the piece's position
    protected int y; // Y-coordinate of the piece's position
    protected String type; // Type of the piece (e.g., "Ram", "Biz", etc.)
    protected boolean transformed = false; // Tracks whether the piece has transformed

    /**
     * Constructor for initializing a KwazamPiece.
     * 
     * **OOP Concept: Encapsulation**
     * - Encapsulates piece attributes (`color`, `x`, `y`, `type`) and initializes
     * them during object creation.
     * 
     * @param color The color of the piece ("Red" or "Blue").
     * @param x     The starting x-coordinate of the piece.
     * @param y     The starting y-coordinate of the piece.
     * @param type  The type of the piece (e.g., "Ram", "Biz").
     */
    public KwazamPiece(String color, int x, int y, String type) {
        this.color = color;
        this.x = x;
        this.y = y;
        this.type = type;
    }

    /**
     * Gets the color of the piece.
     * 
     * **OOP Concept: Encapsulation**
     * - Provides controlled access to the `color` field.
     * 
     * @return The color of the piece ("Red" or "Blue").
     */
    public String getColor() {
        return color;
    }

    /**
     * Gets the type of the piece.
     * 
     * **OOP Concept: Encapsulation**
     * - Provides controlled access to the `type` field.
     * 
     * @return The type of the piece (e.g., "Ram", "Biz").
     */
    public String getType() {
        return type;
    }

    /**
     * Gets the current position of the piece.
     * 
     * **OOP Concept: Encapsulation**
     * - Protects direct access to `x` and `y` by returning their values as an
     * array.
     * 
     * @return An array [x, y] representing the current position of the piece.
     */
    public int[] getPosition() {
        return new int[] { x, y };
    }

    /**
     * Abstract method to calculate valid moves for the piece.
     * 
     * **OOP Concepts:**
     * - **Abstraction:** Leaves the implementation of movement logic to subclasses.
     * - **Polymorphism:** Allows invoking `getValidMoves` on any `KwazamPiece`
     * subclass without knowing its exact type.
     * 
     * @param board The current state of the game board.
     * @return A list of valid moves as [x, y] coordinates.
     */
    public abstract List<int[]> getValidMoves(KwazamBoard board);

    /**
     * Abstract method for handling transformations, if applicable.
     * 
     * **OOP Concepts:**
     * - **Abstraction:** Delegates transformation logic to subclasses.
     * - **Polymorphism:** Supports dynamic invocation of transformations on pieces.
     * 
     */
    public abstract void transform();

    /**
     * Moves the piece to a new position on the board.
     * 
     * **OOP Concepts:**
     * - **Encapsulation:** Updates the position of the piece in a controlled
     * manner.
     * 
     * @param newX The new x-coordinate for the piece.
     * @param newY The new y-coordinate for the piece.
     */
    public void move(int newX, int newY) {
        this.x = newX;
        this.y = newY;
    }
}
