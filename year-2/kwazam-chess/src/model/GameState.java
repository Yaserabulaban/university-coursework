package model;

import java.io.*;

/**
 * Manages the overall state of the game, including turns, transformations, and
 * win conditions.
 * This class is part of the Model layer in the MVC design pattern,
 * encapsulating the state and rules of the game. It interacts with
 * the board and pieces to enforce game logic.
 * 
 * **Design Patterns:**
 * - MVC Pattern: Acts as the Model layer, providing methods to manipulate
 * and retrieve
 * the current state of the game.
 * - Singleton Pattern: The `GameState` class could be refactored into a
 * Singleton if there is ever a need to ensure only one game state exists at any
 * time.
 * - Template Method Pattern: The `saveGame` and `loadGame` methods define a
 * high-level algorithm for managing game state persistence, allowing
 * customization of
 * board and piece handling logic.
 * 
 * **OOP Concepts:**
 * - Encapsulation: Protects the internal state of the game, such as the
 * board and turn counter,
 * and provides controlled access through public methods.
 * - Abstraction: Hides the complexity of managing the game state, allowing
 * higher-level components to interact with the game at a simplified level.
 * - Static Members: The static `turnCounter` provides a shared resource for
 * tracking game turns, accessible across the application.
 * 
 * **Responsibilities:**
 * - Maintains the current game state, including player turns and board
 * configuration.
 * - Supports persistence by saving and loading game state from files.
 * - Provides methods to reset the game, retrieve game data, and check for win
 * conditions.
 * - Tracks and increments the turn counter to enforce turn-based gameplay.
 */

public class GameState {
    private KwazamBoard board; // The game board
    private String currentPlayer; // "Red" or "Blue"
    public static int turnCounter; // Counts the number of turns globally

    /**
     * Constructor to initialize the game state.
     * - Initializes the board and sets default values for the current player
     * and turn counter.
     */
    public GameState() {
        this.board = new KwazamBoard();
        this.currentPlayer = "Red"; // Default starting player
        GameState.turnCounter = 0; // Start with 0 turns
    }

    /**
     * Saves the current game state to a text file.
     * - Includes current player, turn counter, and positions of all pieces.
     * 
     * @param filePath The file path where the game state should be saved.
     *                 **OOP Concept: Abstraction**
     *                 - Encapsulates the logic for saving game state, hiding
     *                 implementation details.
     */
    public void saveGame(String filePath) {
        try {
            // Create a File object
            File file = new File(filePath);

            // Ensure the parent directory exists
            File parentDir = file.getParentFile();
            if (parentDir != null && !parentDir.exists()) {
                parentDir.mkdirs(); // Create the directories if they don't exist
            }

            // Create the file if it does not exist
            if (!file.exists()) {
                file.createNewFile();
            }

            try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath))) {
                // Save the current player's turn
                writer.write("CurrentPlayer:" + currentPlayer);
                writer.newLine();
                writer.write("TurnCounter:" + turnCounter);
                writer.newLine();

                // Save each piece's type, color, and position
                for (KwazamPiece piece : board.getAllPieces()) {
                    String pieceData = String.join(",",
                            piece.getType(),
                            piece.getColor(),
                            String.valueOf(piece.getPosition()[0]),
                            String.valueOf(piece.getPosition()[1]));
                    writer.write(pieceData);
                    writer.newLine();
                }

                System.out.println("Game saved successfully to " + filePath);
            }

        } catch (IOException e) {
            System.err.println("Error saving game: " + e.getMessage());
        }
    }

    /**
     * Loads the game state from a text file.
     * - Restores the current player, turn counter, and piece positions.
     * 
     * @param filePath The file path from which to load the game state.
     *                 OOP Concept: Abstraction
     *                 - Encapsulates file reading logic and state restoration.
     */
    public void loadGame(String filePath) {
        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;

            // Clear the board before loading
            this.board = new KwazamBoard(); // Reset the board
            this.board.clearBoard(); // Ensure the board is empty

            while ((line = reader.readLine()) != null) {
                if (line.startsWith("CurrentPlayer:")) {
                    // Set the current player
                    currentPlayer = line.split(":")[1];
                } else if (line.startsWith("TurnCounter:")) {
                    // Set the saved turn counter
                    turnCounter = Integer.parseInt(line.split(":")[1].trim());
                } else {
                    // Parse piece data
                    String[] parts = line.split(",");
                    String type = parts[0];
                    String color = parts[1];
                    int x = Integer.parseInt(parts[2]);
                    int y = Integer.parseInt(parts[3]);

                    // Add the piece to the board
                    switch (type) {
                        case "Ram" -> board.addPiece(new Ram(color, x, y));
                        case "Biz" -> board.addPiece(new Biz(color, x, y));
                        case "Tor" -> board.addPiece(new Tor(color, x, y));
                        case "Xor" -> board.addPiece(new Xor(color, x, y));
                        case "Sau" -> board.addPiece(new Sau(color, x, y));
                    }
                }
            }

            System.out.println("Game loaded successfully!");

        } catch (IOException e) {
            System.err.println("Error loading game: " + e.getMessage());
        }
    }

    /**
     * Gets the game board instance.
     * 
     * @return The KwazamBoard object representing the game board.
     */
    public KwazamBoard getBoard() {
        return board;
    }

    /**
     * Gets the current player.
     * 
     * @return The current player's color ("Red" or "Blue").
     */
    public String getCurrentPlayer() {
        return currentPlayer;
    }

    /**
     * Resets the game to its initial state.
     * - Resets the board, current player, and turn counter.
     * Design Pattern: Factory Pattern
     * - Resets the board by creating a new `KwazamBoard` object.
     */
    public void restartGame() {
        this.board = new KwazamBoard(); // Reset the board
        this.currentPlayer = "Red"; // Reset the current player to Red
        GameState.turnCounter = 0; // Reset the turn counter
        System.out.println("Game restarted.");
    }

    /**
     * Sets the current player.
     * 
     * @param currentPlayer The player's color to set ("Red" or "Blue").
     */
    public void setCurrentPlayer(String currentPlayer) {
        this.currentPlayer = currentPlayer;
    }

    /**
     * Checks if the current player's Sau has been captured.
     * 
     * @return True if the game is over (Sau captured), false otherwise.
     */
    public boolean isGameOver() {
        return board.isGameOver(currentPlayer);
    }

    /**
     * Increments the global turn counter.
     * **Design Pattern: Singleton-like Shared State**
     * - Maintains a global shared counter for turn tracking.
     */
    public static void incrementTurnCounter() {
        turnCounter++;
    }

    /**
     * Gets the current turn counter.
     * 
     * @return The number of completed turns.
     */
    public int getTurnCounter() {
        return turnCounter;
    }
}
