import controller.GameController;

/**
 * The main entry point for the Kwazam Chess game.
 * 
 * **Purpose**:
 * - Initializes the core components of the application and launches the game.
 * Written by: Yaser Abulaba
 */
public class KwazamChess {

    /**
     * The main method that launches the Kwazam Chess game.
     * 
     * **Responsibilities**:
     * 1. Creates an instance of `GameController`, which manages the game logic.
     * 2. Invokes `startGame()` on the controller to initialize and display the
     * game.
     */
    public static void main(String[] args) {
        // Step 1: Initialize the GameController
        GameController controller = new GameController();

        // Step 2: Start the game using the controller
        controller.startGame();
    }
}
