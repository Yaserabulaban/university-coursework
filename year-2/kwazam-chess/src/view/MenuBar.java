package view;

import controller.GameController;
import javax.swing.*;

/**
 * Represents the menu bar in Kwazam Chess.
 * Provides user-accessible options for performing actions such as saving,
 * loading, restarting, and exiting the game.
 * It also offers a help dialog for game instructions. This class is part of the
 * View layer in the MVC design pattern.
 * 
 * **Design Patterns:**
 * - MVC Pattern: Acts as a part of the View layer, providing an interface
 * for user interactions and forwarding
 * actions to the Controller layer via event listeners.
 * - Command Pattern: Encapsulates each menu action (e.g., Save Game, Load
 * Game) as a separate command
 * that triggers a corresponding method in the `GameController`.
 * 
 * **OOP Concepts:**
 * - Encapsulation: Encapsulates the menu items and their associated
 * behaviors within a reusable component.
 * - Abstraction: Simplifies the management of multiple menu actions by
 * abstracting their implementation
 * details into a single, cohesive menu bar.
 * - Dependency Injection: Accepts a `GameController` instance through its
 * constructor to delegate actions
 * like saving or loading games.
 * 
 * **Responsibilities:**
 * - Provides menu options for managing game state (Save, Load, Restart).
 * - Displays game instructions through a Help menu option.
 * - Offers the ability to exit the game with a confirmation prompt.
 * - Ensures actions performed in the menu are communicated to the
 * `GameController`.
 */

public class MenuBar extends JMenuBar {

    /**
     * Constructor to initialize the menu bar.
     * 
     * @param controller The game controller to handle menu actions.
     *                   (OOP: Dependency Injection)
     */
    public MenuBar(GameController controller) {
        // Create the main menu
        JMenu menu = new JMenu("Menu");

        // Add Save Game option
        JMenuItem saveItem = new JMenuItem("Save Game");
        saveItem.addActionListener(e -> controller.saveGame()); // Delegates action to the controller
        menu.add(saveItem);

        // Add Load Game option
        JMenuItem loadItem = new JMenuItem("Load Game");
        loadItem.addActionListener(e -> controller.loadGame()); // Delegates action to the controller
        menu.add(loadItem);

        // Add Restart Game option with confirmation
        JMenuItem restartItem = new JMenuItem("Restart Game");
        restartItem.addActionListener(e -> {
            int confirm = JOptionPane.showConfirmDialog(
                    null,
                    "Are you sure you want to restart the game? All progress will be lost.",
                    "Restart Game",
                    JOptionPane.YES_NO_OPTION);

            if (confirm == JOptionPane.YES_OPTION) {
                controller.restartGame(); // Call the restart game method in the controller
            }
        });
        menu.add(restartItem);

        // Add Help option
        JMenuItem helpItem = new JMenuItem("Help");
        helpItem.addActionListener(e -> JOptionPane.showMessageDialog(
                null,
                "Instructions:\n1. Select a piece.\n2. Move to a valid square.\n3. Protect your Sau!",
                "Help",
                JOptionPane.INFORMATION_MESSAGE));
        menu.add(helpItem);

        // Add Exit Game option with confirmation
        JMenuItem exitItem = new JMenuItem("Exit");
        exitItem.addActionListener(e -> {
            int confirm = JOptionPane.showConfirmDialog(
                    null,
                    "Are you sure you want to exit?",
                    "Exit",
                    JOptionPane.YES_NO_OPTION);

            if (confirm == JOptionPane.YES_OPTION) {
                System.exit(0); // Exit the application
            }
        });
        menu.add(exitItem);

        // Add the menu to the menu bar
        add(menu);
    }
}