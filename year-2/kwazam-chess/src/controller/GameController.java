package controller;

import java.io.File;
import java.util.ArrayList;
import java.util.List;
import model.GameState;
import model.KwazamBoard;
import model.KwazamPiece;
import model.SoundHandler;
import model.Tor;
import model.Xor;
import view.MainWindow;

/**
 * Controls the overall game logic and serves as a bridge between the Model and
 * View layers.
 * This class handles user interactions, game flow, and updates to the game
 * state.
 * 
 * **Design Patterns:**
 * - MVC Pattern: Acts as the Controller layer, managing interactions
 * between the View (`MainWindow`, `BoardView`)
 * and the Model (`GameState`, `KwazamBoard`).
 * - Observer Pattern: Facilitates updates to the View whenever the Model
 * changes, ensuring synchronization
 * (e.g., updating the board or move history).
 * - Command Pattern: Encapsulates user actions (e.g., piece movement,
 * saving/loading games) as methods, making it
 * easier to add or modify functionality.
 * 
 * **OOP Concepts:**
 * - Encapsulation: Manages game state and interactions through controlled
 * methods, hiding implementation details.
 * - Abstraction: Provides a high-level interface for game logic, delegating
 * specific tasks to helper methods or other classes.
 * - Polymorphism: Utilizes polymorphism when handling different types of
 * game pieces (`KwazamPiece` subclasses) or user actions.
 * 
 * **Responsibilities:**
 * - Handles user input and translates it into game actions (e.g., moving a
 * piece, restarting the game).
 * - Manages the game state (`GameState`), ensuring synchronization with the
 * View (`MainWindow`, `BoardView`).
 * - Implements core game logic, such as turn-based rules, piece
 * transformations, and win conditions.
 * - Coordinates saving and loading game states, ensuring proper interaction
 * with the View for user prompts.
 */
public class GameController {
    private GameState gameState; // Encapsulates the state of the game (OOP: Encapsulation).
    private MainWindow mainWindow; // Represents the View layer (MVC).
    private int currentX = -1; // Track selected piece's x-coordinate (OOP: Encapsulation).
    private int currentY = -1; // Track selected piece's y-coordinate (OOP: Encapsulation).
    private boolean isRestarting = false; // Tracks whether the game is currently restarting.

    /**
     * Constructor to initialize the game controller.
     * 
     * Design Pattern:
     * - Dependency Injection: Injects dependencies for `GameState` and
     * `MainWindow`.
     * Written by: Yaser Abulaban
     */
    public GameController() {
        this.gameState = new GameState(); // Initialize the game state (OOP: Encapsulation).
        this.mainWindow = new MainWindow(this); // Pass controller to the view (MVC).
    }

    /**
     * Starts the game by making the main window visible.
     * This initializes the View and kicks off the game.
     * Written by: Yaser Abulaban
     */

    public void startGame() {
        mainWindow.setVisible(true); // Show the main application window.
    }

    /**
     * Handles a user's click on the game board.
     * Delegates logic for first and second clicks to helper methods.
     * 
     * @param x The x-coordinate of the clicked cell.
     * @param y The y-coordinate of the clicked cell.
     * 
     *          Written by: Yaser Abulaban
     */
    public void handleBoardClick(int x, int y) {
        boolean isFlipped = gameState.getCurrentPlayer().equals("Blue"); // Determine board orientation.
        int adjustedX = adjustCoordinate(x, isFlipped, true); // Adjust X if flipped.
        int adjustedY = adjustCoordinate(y, isFlipped, false); // Adjust Y if flipped.

        KwazamPiece piece = gameState.getBoard().getPieceAt(adjustedX, adjustedY); // Retrieve the piece at clicked
                                                                                   // position.

        if (isFirstClick()) {
            handleFirstClick(piece, adjustedX, adjustedY, isFlipped); // Handle selection of a piece.
        } else {
            handleSecondClick(adjustedX, adjustedY); // Handle movement of the selected piece.
        }
    }

    /**
     * Adjusts a coordinate based on whether the board is flipped.
     * 
     * @param coord     The original coordinate.
     * @param isFlipped Whether the board is flipped.
     * @param isX       Whether the coordinate is for the X-axis.
     * @return The adjusted coordinate.
     * 
     * 
     *         Written by: Narmithaa
     */
    private int adjustCoordinate(int coord, boolean isFlipped, boolean isX) {
        return isFlipped ? (isX ? 4 - coord : 7 - coord) : coord; // Flip coordinates if necessary.
    }

    /**
     * Checks if the current click is the first click in a turn.
     * 
     * @return True if no piece is currently selected; false otherwise.
     * 
     *         Written by: Narmithaa
     */
    private boolean isFirstClick() {
        return currentX == -1 && currentY == -1;
    }

    /**
     * Handles logic for selecting a piece on the first click.
     * 
     * @param piece     The selected piece.
     * @param adjustedX The x-coordinate of the selected piece.
     * @param adjustedY The y-coordinate of the selected piece.
     * @param isFlipped Whether the board is flipped.
     *                  Written by: Yaser Abulaban
     */
    private void handleFirstClick(KwazamPiece piece, int adjustedX, int adjustedY, boolean isFlipped) {

        if (isRestarting) {
            // Ignore any clicks during a restart
            return;
        }

        if (piece != null && piece.getColor().equals(gameState.getCurrentPlayer())) {
            List<int[]> validMoves = getValidMoves(piece, isFlipped);
            mainWindow.getBoardView().setValidMoves(validMoves); // Highlight valid moves on the board.
            SoundHandler.playSound("sounds/select.wav");
            currentX = adjustedX;
            currentY = adjustedY;
        } else {
            System.out.println("Invalid selection.");
            clearHighlights();
            SoundHandler.playSound("sounds/error.wav"); // Play error sound only if not restarting

        }
    }

    /**
     * Handles logic for moving a piece on the second click.
     * 
     * @param adjustedX The x-coordinate of the destination cell.
     * @param adjustedY The y-coordinate of the destination cell.
     *                  Written by: Yaser Abulaban
     */
    private void handleSecondClick(int adjustedX, int adjustedY) {
        KwazamPiece selectedPiece = gameState.getBoard().getPieceAt(currentX, currentY);
        if (isValidMove(selectedPiece, adjustedX, adjustedY)) {
            processMove(selectedPiece, adjustedX, adjustedY);
        } else {
            System.out.println("Invalid move.");
            SoundHandler.playSound("sounds/error.wav");
        }
        resetSelection();
        clearHighlights();
    }

    /**
     * Gets the valid moves for a piece, adjusting for board orientation if
     * necessary.
     * 
     * @param piece     The piece to calculate moves for.
     * @param isFlipped Whether the board is flipped.
     * @return A list of valid moves.
     *         Written by: Yaser Abulaban
     */
    private List<int[]> getValidMoves(KwazamPiece piece, boolean isFlipped) {
        List<int[]> validMoves = piece.getValidMoves(gameState.getBoard());
        if (isFlipped) {
            for (int[] move : validMoves) {
                move[0] = 4 - move[0];
                move[1] = 7 - move[1];
            }
        }
        return validMoves;
    }

    /**
     * Checks if a move is valid for the selected piece.
     * 
     * @param piece     The selected piece.
     * @param adjustedX The destination x-coordinate.
     * @param adjustedY The destination y-coordinate.
     * @return True if the move is valid; false otherwise.
     *         Written by: Narmithaa
     */
    private boolean isValidMove(KwazamPiece piece, int adjustedX, int adjustedY) {
        return piece.getValidMoves(gameState.getBoard()).stream()
                .anyMatch(move -> move[0] == adjustedX && move[1] == adjustedY);
    }

    /**
     * Processes a valid move by updating the board and logging the move.
     * 
     * @param selectedPiece The piece being moved.
     * @param adjustedX     The destination x-coordinate.
     * @param adjustedY     The destination y-coordinate.
     *                      Written by: Yaser Abulaban
     */
    private void processMove(KwazamPiece selectedPiece, int adjustedX, int adjustedY) {
        boolean moveSuccessful = gameState.getBoard().movePiece(currentX, currentY, adjustedX, adjustedY);
        if (moveSuccessful) {
            logMove(selectedPiece, adjustedX, adjustedY);
            handleTurnEnd();
        } else {
            System.out.println("Move failed.");
            SoundHandler.playSound("sounds/error.wav");
        }
    }

    /**
     * Logs a move in the move history.
     * 
     * @param selectedPiece The piece being moved.
     * @param adjustedX     The destination x-coordinate.
     * @param adjustedY     The destination y-coordinate.
     *                      Written by: Narmithaa
     */
    private void logMove(KwazamPiece selectedPiece, int adjustedX, int adjustedY) {
        String move = gameState.getCurrentPlayer() + " " + selectedPiece.getType() + " moved from (" + currentX + ", "
                + currentY + ") to (" + adjustedX + ", " + adjustedY + ")";
        mainWindow.updateMoveHistory(move); // Update move history in the view.
    }

    /**
     * Handles end-of-turn logic, including turn switching and transformations.
     * Written by: Yaser Abulaban
     */
    private void handleTurnEnd() {
        if (gameState.getCurrentPlayer().equals("Blue")) {
            GameState.incrementTurnCounter();
            if (GameState.turnCounter % 2 == 0) {
                transformPieces();
            }
        }
        if (!checkGameOver()) {
            switchPlayer();
        }
    }

    /**
     * Switches to the next player.
     * Written by: Narmithaa
     */
    private void switchPlayer() {
        gameState.setCurrentPlayer(gameState.getCurrentPlayer().equals("Red") ? "Blue" : "Red");
        refreshView();
    }

    /**
     * Clears move highlights from the board.
     * Written by: Yaser Abulaban
     */
    private void clearHighlights() {
        mainWindow.getBoardView().setValidMoves(new ArrayList<>());
        mainWindow.getBoardView().repaint();
    }

    /**
     * Resets the selection state after a turn.
     * Written by: Yaser Abulaban
     */
    private void resetSelection() {
        currentX = -1;
        currentY = -1;
    }

    /**
     * Resets the game state and starts a new game.
     * Written by: Yaser Abulaban
     */
    public void restartGame() {

        isRestarting = true; // Indicate that the game is being restarted.

        // Reset the game state
        gameState = new GameState();

        // Reset selection variables
        currentX = -1;
        currentY = -1;

        // Create a new MainWindow instance and reinitialize the controller
        mainWindow.dispose(); // Close the current window
        mainWindow = new MainWindow(this); // Reinitialize the MainWindow
        mainWindow.getBoardView().setFlipped(false); // Reset the board to default orientation
        mainWindow.getBoardView().setValidMoves(new ArrayList<>()); // Clear highlighted moves

        // Refresh the view
        refreshView();

        // Reset the status bar
        mainWindow.updateStatusBar("Current Player: Red");

        System.out.println("Game restarted.");

        // Delay resetting the isRestarting flag to avoid stray events
        new javax.swing.Timer(200, e -> isRestarting = false).start(); // Delay for 200 ms
    }

    /**
     * Retrieves the list of all pieces currently on the board.
     * 
     * @return A list of all pieces in the game.
     *         Written by: Yaser Abulaban
     */
    public List<KwazamPiece> getPieces() {
        List<KwazamPiece> pieces = gameState.getBoard().getAllPieces();
        return pieces;
    }

    /**
     * Saves the current game state.
     * 
     * Written by: Yaser Abulaban
     */
    public void saveGame() {
        String saveDirectory = "saved_games";
        File directory = new File(saveDirectory);

        // Ensure the save directory exists
        if (!directory.exists()) {
            directory.mkdir();
        }

        // Prompt the user for a custom save name
        String saveName = mainWindow.showSaveNameDialog();
        if (saveName == null || saveName.trim().isEmpty()) {
            System.out.println("Save operation canceled.");
            return; // User canceled or provided invalid input
        }

        // Generate the file name for the save
        String fileName = saveDirectory + "/" + saveName + "_saved_game.txt";
        File saveFile = new File(fileName);

        // Check if the file already exists
        if (saveFile.exists()) {
            boolean confirmOverwrite = mainWindow.showOverwriteConfirmation(saveName);
            if (!confirmOverwrite) {
                System.out.println("Save operation aborted.");
                return; // Abort saving if the user declines overwriting
            }
        }

        // Save the game state
        gameState.saveGame(fileName);
        System.out.println("Game saved to " + fileName);
    }

    /**
     * Loads a game state from a file.
     * 
     * Written by: Yaser Abulaban
     */
    public void loadGame() {
        // Prompt the user to save the current game before loading
        boolean proceed = mainWindow.handleLoadGamePrompt();
        if (!proceed) {
            System.out.println("Load operation canceled by user.");
            return; // Abort if the user cancels
        }

        // Let the user choose a save file to load
        String filePath = mainWindow.showLoadSlotDialog();
        if (filePath == null) {
            System.out.println("No file selected. Load operation aborted.");
            return; // Abort if no file is selected
        }

        // Show confirmation dialog after selecting a slot
        boolean confirmLoad = mainWindow.showLoadConfirmationDialog();
        if (!confirmLoad) {
            System.out.println("Load operation canceled by user.");
            return; // Abort loading if the user declines
        }

        // Load the game from the selected file
        gameState.loadGame(filePath);

        // Clear selection variables and refresh the view
        currentX = -1;
        currentY = -1;
        mainWindow.clearMoveHistory();
        mainWindow.getBoardView().setValidMoves(new ArrayList<>());
        mainWindow.getBoardView().repaint();
        refreshView();

        System.out.println("Game loaded from " + filePath);
    }

    /**
     * Refreshes the view to reflect the current game state.
     * Written by: Yaser Abulaban
     */
    private void refreshView() {

        // Set whether to flip the board view for Blue's turn
        boolean isBlueTurn = gameState.getCurrentPlayer().equals("Blue");
        mainWindow.getBoardView().setFlipped(isBlueTurn); // Ensure the board is flipped
        mainWindow.getBoardView().repaint(); // Repaint the board
        mainWindow.updateStatusBar("Current Player: " + gameState.getCurrentPlayer()); // Update status bar
    }

    public boolean checkGameOver() {
        KwazamBoard board = gameState.getBoard();
        String currentPlayer = gameState.getCurrentPlayer();

        if (board.isGameOver(currentPlayer)) {
            SoundHandler.playSound("sounds/game_over.wav");
            mainWindow.showGameOverDialog(currentPlayer); // Call MainWindow to handle the dialog
            return true;
        }
        return false;
    }

    /**
     * Transforms eligible pieces (Tor or Xor) on the board.
     * 
     * - Checks all pieces on the board for `Tor` or `Xor` types.
     * - Transforms `Tor` into `Xor` and `Xor` into `Tor` based on their behavior.
     * - Updates the board state to reflect the transformation and logs the change
     * in move history.
     * - Repaints the board to visually show the transformation.
     * 
     * **OOP Concepts:**
     * - **Polymorphism:** The `transform()` method in `KwazamPiece` is overridden
     * in `Tor` and `Xor` subclasses.
     * - **Encapsulation:** The board's state is manipulated via `replacePiece()`
     * and other controlled methods.
     * 
     * **Design Pattern:**
     * - **MVC:** The method operates on the Model (`GameState`, `KwazamBoard`)
     * while ensuring the View (`MainWindow`) is updated.
     * Written by: Yaser Abul
     */
    private void transformPieces() {
        // Retrieve all pieces currently on the board
        List<KwazamPiece> pieces = gameState.getBoard().getAllPieces();

        // Iterate through each piece to check for transformation eligibility
        for (KwazamPiece piece : pieces) {
            if (piece instanceof Tor || piece instanceof Xor) {
                // Store the original type before transformation
                String originalType = piece.getType();

                // Call the transform method (defined in the piece's subclass)
                piece.transform();

                // Perform the actual transformation based on the new type
                if ("Tor".equals(piece.getType())) {
                    // Transform Tor into Xor
                    KwazamPiece transformedPiece = new Xor(
                            piece.getColor(), // Preserve the piece's color
                            piece.getPosition()[0], // X-coordinate
                            piece.getPosition()[1] // Y-coordinate
                    );
                    // Replace the old piece with the transformed one on the board
                    gameState.getBoard().replacePiece(transformedPiece, piece.getPosition()[0], piece.getPosition()[1]);
                    // Log the transformation in the move history
                    logTransformation(originalType, transformedPiece);
                } else if ("Xor".equals(piece.getType())) {
                    // Transform Xor into Tor
                    KwazamPiece transformedPiece = new Tor(
                            piece.getColor(), // Preserve the piece's color
                            piece.getPosition()[0], // X-coordinate
                            piece.getPosition()[1] // Y-coordinate
                    );
                    // Replace the old piece with the transformed one on the board
                    gameState.getBoard().replacePiece(transformedPiece, piece.getPosition()[0], piece.getPosition()[1]);
                    // Log the transformation in the move history
                    logTransformation(originalType, transformedPiece);
                }
            }
        }

        // Repaint the board to visually reflect the transformations
        mainWindow.getBoardView().repaint();
    }

    /**
     * Logs the transformation of a piece in the move history.
     * 
     * - Constructs a descriptive message about the transformation.
     * - Updates the move history panel in the MainWindow with the transformation
     * details.
     * 
     * **OOP Concepts:**
     * - Encapsulation: Encapsulates the logic for constructing and logging the
     * transformation message.
     * 
     * **Design Pattern:**
     * - MVC: Interacts with the View (`MainWindow`) to update the move history,
     * ensuring the UI reflects the Model's state.
     * 
     * @param originalType     The original type of the piece before transformation
     *                         (e.g., "Tor").
     * @param transformedPiece The piece object after transformation, containing the
     *                         new type and its current position.
     *                         Written by: Yaser Abulaban
     */
    private void logTransformation(String originalType, KwazamPiece transformedPiece) {
        // Construct the log message describing the transformation
        String message = transformedPiece.getColor() + " " + originalType +
                " transformed into " + transformedPiece.getType() +
                " at (" + transformedPiece.getPosition()[0] + ", " + transformedPiece.getPosition()[1] + ")";

        // Update the move history in the MainWindow with the transformation details
        mainWindow.updateMoveHistory(message);
    }

}