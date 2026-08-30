package controller;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import view.BoardView;

/**
 * Handles user input events, such as mouse clicks, and forwards them to the
 * GameController.
 * This class serves as an intermediary between the View (`BoardView`) and the
 * Controller (`GameController`),
 * ensuring a clean separation of concerns.
 * 
 * **Design Patterns:**
 * - MVC Pattern: Part of the Controller layer, bridging the gap between
 * user actions in the View (`BoardView`)
 * and the game logic in the Controller (`GameController`).
 * - Observer Pattern: Listens for user interactions and notifies the
 * Controller to handle them appropriately.
 * 
 * **OOP Concepts:**
 * - Encapsulation: Abstracts user input handling, ensuring the Controller
 * only receives processed actions (e.g.,
 * coordinates of the clicked board cell).
 * 
 * **Responsibilities:**
 * - Captures mouse events (e.g., clicks) on the game board (`BoardView`) and
 * converts them into logical actions.
 * - Ensures debouncing of input to avoid unintended rapid actions (e.g.,
 * double-clicks).
 * - Maintains focus on the game board for consistent user interaction.
 */

public class InputHandler extends MouseAdapter {
    private final GameController controller; // Reference to the game controller (MVC Controller layer)
    private final BoardView boardView; // Reference to the board view (MVC View layer)
    private long lastClickTime = 0; // Tracks the time of the last click to prevent rapid double-clicks

    /**
     * Constructor to initialize the input handler.
     * 
     * @param controller The game controller to handle user actions.
     * @param boardView  The board view where the user interacts.
     *                   (OOP: Dependency Injection)
     *                   Written by: Yaser Abulaba
     */
    public InputHandler(GameController controller, BoardView boardView) {
        this.controller = controller;
        this.boardView = boardView;

        // Attach this input handler to the board view
        boardView.addMouseListener(this); // Encapsulation: Adding event listeners
        boardView.setFocusable(true); // Ensure the board view can receive focus
        boardView.requestFocusInWindow(); // Request focus for the board view
    }

    /**
     * Handles mouse click events on the board.
     * - Converts pixel coordinates to board cell indices.
     * - Prevents rapid double-clicks with a debounce mechanism.
     * 
     * @param e The MouseEvent triggered by the user's click.
     *          Written by: Yaser Abulaba
     */
    @Override
    public void mouseClicked(MouseEvent e) {
        long currentTime = System.currentTimeMillis();

        // Debounce logic: Ignore clicks within 300 ms
        if (currentTime - lastClickTime < 300) {
            return; // Prevent rapid double-clicks
        }
        lastClickTime = currentTime; // Update the last click time

        // Calculate board cell indices from pixel coordinates
        int cellWidth = boardView.getWidth() / 5; // Divide board width into 5 columns
        int cellHeight = boardView.getHeight() / 8; // Divide board height into 8 rows
        int x = e.getX() / cellWidth; // Determine the column index
        int y = e.getY() / cellHeight; // Determine the row index

        // Delegate the click action to the controller
        controller.handleBoardClick(x, y);
    }
}
