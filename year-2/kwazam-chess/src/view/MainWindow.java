package view;

import controller.GameController;
import controller.InputHandler;
import java.awt.*;
import java.io.File;
import javax.swing.*;

/**
 * The main application window for Kwazam Chess.
 * Responsible for initializing and managing the GUI components, including the
 * game board, menu bar,
 * status bar, and move history. Acts as the central View component in the MVC
 * design pattern, facilitating
 * communication between the user and the Controller.
 * 
 * **Design Patterns:**
 * - MVC Pattern: Serves as the main entry point for the View layer,
 * displaying the game state and providing
 * user interaction interfaces (e.g., dialogs, buttons, and the game board).
 * - Observer Pattern: Observes user interactions (e.g., menu actions, mouse
 * clicks) and notifies the Controller
 * to handle corresponding updates to the game state.
 * 
 * **OOP Concepts:**
 * - Encapsulation: Encapsulates UI components like the board, status bar,
 * and move history, exposing methods
 * for controlled updates (e.g., `updateStatusBar`, `updateMoveHistory`).
 * - Dependency Injection: Accepts a `GameController` instance through its
 * constructor to establish a clear
 * separation between the View and Controller layers.
 * - Abstraction: Abstracts the complexity of GUI management, offering
 * high-level methods for user interactions
 * (e.g., dialogs for saving and loading games).
 * 
 * **Responsibilities:**
 * - Displays the game board (`BoardView`) and keeps it updated based on user
 * actions and game state changes.
 * - Provides dialogs for user interactions, such as saving/loading games and
 * confirming game-over states.
 * - Maintains and displays the move history in a scrollable panel.
 * - Updates the status bar to reflect the current player's turn or other game
 * statuses.
 * - Integrates the menu bar (`MenuBar`) for actions like saving, loading,
 * restarting, and exiting the game.
 */

public class MainWindow extends JFrame {
    private final BoardView boardView; // The visual representation of the game board
    private final JLabel statusBar; // Displays the current player or game status
    private final GameController controller; // Reference to the game controller
    private final JTextArea moveHistory; // A text area to display move history

    /**
     * Constructor to initialize the main application window.
     * 
     * @param controller The game controller to manage user interactions.
     *                   (OOP: Dependency Injection)
     *                   Written by: Yaser Abulaban
     */
    public MainWindow(GameController controller) {
        setTitle("Kwazam Chess");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Create the BoardView and add a mouse listener
        boardView = new BoardView(controller);
        boardView.addMouseListener(new InputHandler(controller, boardView));
        add(boardView, BorderLayout.CENTER);

        // Add the menu bar
        MenuBar menuBar = new MenuBar(controller);
        setJMenuBar(menuBar);

        // Add the status bar at the bottom
        statusBar = new JLabel("Current Player: Red");
        add(statusBar, BorderLayout.SOUTH);

        // Add the move history panel
        moveHistory = new JTextArea(10, 20);
        moveHistory.setEditable(false);
        moveHistory.setBorder(BorderFactory.createTitledBorder("Move History"));
        JScrollPane scrollPane = new JScrollPane(moveHistory);
        add(scrollPane, BorderLayout.EAST);

        // Add components to the frame
        setSize(800, 600);
        setVisible(true);

        this.controller = controller; // Dependency injection
    }

    /**
     * Clears the move history display.
     * Written by: Yaser Abulaban
     */
    public void clearMoveHistory() {
        moveHistory.setText(""); // Clear the text area
        System.out.println("Move history cleared."); // Debug log
    }

    /**
     * Updates the status bar text.
     * 
     * @param message The message to display (e.g., current player's turn).
     *                (OOP: Encapsulation)
     *                Written by: Yaser Abulaban
     */
    public void updateStatusBar(String message) {
        statusBar.setText(message); // Update the status bar
    }

    /**
     * Updates the move history display with the given move.
     * - Automatically scrolls to the bottom to show the latest move.
     * 
     * @param move The move to add to the history.
     *             Written by: Yaser Abulaban
     */
    public void updateMoveHistory(String move) {
        moveHistory.append(move + "\n");
        moveHistory.setCaretPosition(moveHistory.getDocument().getLength()); // Auto-scroll to the bottom
    }

    /**
     * Gets the BoardView instance for rendering updates.
     * 
     * @return The BoardView component.
     *         (OOP: Abstraction, MVC Pattern)
     *         Written by: Yaser Abulaban
     */
    public BoardView getBoardView() {
        return boardView;
    }

    /**
     * Displays a game-over message and handles restart logic.
     * - Asks the user if they want to restart or exit the game.
     * 
     * @param winner The winning player's color.
     *               (OOP: Abstraction, Encapsulation)
     *               Written by: Fakhira
     */
    public void showGameOverDialog(String winner) {
        int option = JOptionPane.showOptionDialog(
                this,
                "Game Over! " + winner + " wins. Would you like to restart or exit?",
                "Game Over",
                JOptionPane.YES_NO_OPTION,
                JOptionPane.INFORMATION_MESSAGE,
                null,
                new String[] { "Restart", "Exit" },
                "Restart");

        if (option == JOptionPane.YES_OPTION) {
            controller.restartGame(); // Restart the game via the controller
        } else if (option == JOptionPane.NO_OPTION) {
            System.exit(0); // Exit the application
        }
    }

    /**
     * Displays a prompt to confirm whether the user wants to save the current game
     * before loading a new one.
     *
     * @return True if the user chooses to proceed with loading; false otherwise.
     *         Written by: Fakhira
     */
    public boolean handleLoadGamePrompt() {
        int option = JOptionPane.showConfirmDialog(
                this,
                "Do you want to save the current game before loading a new one?",
                "Save Current Game",
                JOptionPane.YES_NO_CANCEL_OPTION,
                JOptionPane.QUESTION_MESSAGE);

        if (option == JOptionPane.YES_OPTION) {
            controller.saveGame(); // Save the current game
            System.out.println("Current game saved.");
            return true; // Proceed to load the game
        } else if (option == JOptionPane.CANCEL_OPTION || option == JOptionPane.CLOSED_OPTION) {
            System.out.println("Load operation canceled.");
            return false; // Do not load the game
        }

        return true; // Proceed without saving
    }

    /**
     * Displays a confirmation dialog if a slot already contains a saved game.
     *
     * @param fileName The slot number that the user wants to overwrite.
     * @return True if the user confirms overwriting, false otherwise.
     *         Written by: Fakhira
     */
    public boolean showOverwriteConfirmation(String fileName) {
        int choice = JOptionPane.showConfirmDialog(
                this,
                "File " + fileName + " already contains a saved game. Do you want to overwrite it?",
                "Overwrite Confirmation",
                JOptionPane.YES_NO_OPTION,
                JOptionPane.WARNING_MESSAGE);

        return choice == JOptionPane.YES_OPTION; // Return true if the user confirms overwriting
    }

    /**
     * Displays a dialog with a drop-down menu to select a save file to load.
     * Shows all available saved games in the "saved_games/" directory.
     *
     * @return The selected file path, or null if canceled.
     *         Written by: Yaser Abulaban
     */
    public String showLoadSlotDialog() {
        File directory = new File("saved_games");
        if (!directory.exists() || !directory.isDirectory()) {
            JOptionPane.showMessageDialog(this, "No saved games found.", "Load Game", JOptionPane.WARNING_MESSAGE);
            return null;
        }

        File[] files = directory.listFiles((dir, name) -> name.endsWith("_saved_game.txt"));
        if (files == null || files.length == 0) {
            JOptionPane.showMessageDialog(this, "No saved games found.", "Load Game", JOptionPane.WARNING_MESSAGE);
            return null;
        }

        // Create a drop-down menu with saved game file names
        String[] fileNames = new String[files.length];
        for (int i = 0; i < files.length; i++) {
            fileNames[i] = files[i].getName();
        }
        JComboBox<String> comboBox = new JComboBox<>(fileNames);

        // Show dialog with the drop-down menu
        int choice = JOptionPane.showConfirmDialog(
                this,
                comboBox,
                "Select a saved game to load:",
                JOptionPane.OK_CANCEL_OPTION,
                JOptionPane.QUESTION_MESSAGE);

        if (choice == JOptionPane.OK_OPTION) {
            String selectedFileName = (String) comboBox.getSelectedItem();
            for (File file : files) {
                if (file.getName().equals(selectedFileName)) {
                    return file.getAbsolutePath(); // Return the absolute path of the selected file
                }
            }
        }

        return null; // User canceled or closed the dialog
    }

    /**
     * Displays a confirmation dialog asking if the user wants to load the game.
     *
     * @return True if the user confirms loading, false otherwise.
     *         Written by: Yaser Abulaban
     */
    public boolean showLoadConfirmationDialog() {
        int choice = JOptionPane.showConfirmDialog(
                this,
                "Are you sure you want to load the selected game? Unsaved progress will be lost.",
                "Load Game Confirmation",
                JOptionPane.YES_NO_OPTION,
                JOptionPane.WARNING_MESSAGE);

        return choice == JOptionPane.YES_OPTION; // Return true if the user confirms loading
    }

    public String showSaveNameDialog() {
        return JOptionPane.showInputDialog(
                this,
                "Enter a name for the save game:",
                "Save Game",
                JOptionPane.QUESTION_MESSAGE);
    }

    public String showLoadFileDialog(File[] files) {
        String[] fileNames = new String[files.length];
        for (int i = 0; i < files.length; i++) {
            fileNames[i] = files[i].getName();
        }

        String selectedFile = (String) JOptionPane.showInputDialog(
                this,
                "Select a save game to load:",
                "Load Game",
                JOptionPane.QUESTION_MESSAGE,
                null,
                fileNames,
                fileNames[0]);

        if (selectedFile != null) {
            for (File file : files) {
                if (file.getName().equals(selectedFile)) {
                    return file.getAbsolutePath(); // Return the absolute path of the selected file
                }
            }
        }
        return null; // User canceled the dialog
    }

    /**
     * Displays a general message dialog to the user.
     *
     * @param message The message to display.
     * @param title   The title of the dialog.
     * @param type    The message type (e.g., warning, confirmation).
     *                Written by: Yaser Abulaban
     */
    public void showMessageDialog(String message, String title, int type) {
        JOptionPane.showMessageDialog(this, message, title, type);
    }

}