package model;

import java.io.File;
import java.io.IOException;
import javax.sound.sampled.*;

/**
 * Utility class for handling sound effects in Kwazam Chess.
 * Provides functionality to play sound files for various game events (e.g.,
 * moves, errors, game over).
 * This class ensures a centralized approach for managing audio feedback,
 * enhancing user experience.
 * 
 * **Design Patterns:**
 * - Singleton Pattern (Conceptual): Although not explicitly implemented as
 * a singleton,`SoundHandler` acts as a utility class with static methods, 
 * ensuring a single shared point of access for audio functionality.
 * - Facade Pattern: Abstracts the complexity of handling audio streams,
 * clips, and exceptions, providing a simple `playSound` method for external use.
 * 
 * **OOP Concepts:**
 * - Encapsulation: Encapsulates the logic for audio playback, managing file
 * access and exceptions internally.
 * - Abstraction: Hides the implementation details of the Java Sound API,
 * exposing only the `playSound` method for external use.
 * 
 * **Responsibilities:**
 * - Loads and plays audio files in WAV format.
 * - Handles exceptions related to unsupported formats, missing files, or
 * unavailable audio lines.
 * - Ensures audio feedback is consistent and straightforward for game interactions.
 */

public class SoundHandler {

    /**
     * Plays a sound from the specified file path.
     * 
     * **OOP Concept: Abstraction**
     * - Encapsulates the logic for playing sound files, hiding the complexity
     * of file handling and audio streaming.
     * 
     * @param soundFilePath The relative path to the sound file.
     */
    public static void playSound(String soundFilePath) {
        try {
            // Locate the sound file
            File soundFile = new File(soundFilePath);
            if (!soundFile.exists()) {
                System.err.println("Error: Sound file not found: " + soundFile.getAbsolutePath());
                return;
            }

            // Create an audio input stream from the file
            AudioInputStream audioStream = AudioSystem.getAudioInputStream(soundFile);

            // Obtain a clip to play the sound
            Clip clip = AudioSystem.getClip();
            clip.open(audioStream); // Load the audio stream into the clip

            // Start playback and wait for it to finish
            clip.start(); // Start playing the sound
            clip.drain(); // Wait for the sound to complete

        } catch (UnsupportedAudioFileException e) {
            System.err.println("Unsupported audio file format: " + e.getMessage());
        } catch (IOException e) {
            System.err.println("Could not read the sound file: " + e.getMessage());
        } catch (LineUnavailableException e) {
            System.err.println("Audio line unavailable: " + e.getMessage());
        }
    }
}