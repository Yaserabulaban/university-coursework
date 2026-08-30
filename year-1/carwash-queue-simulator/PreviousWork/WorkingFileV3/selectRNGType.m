function rng_choice = selectRNGType()
    % Function to select the type of random number generator (RNG)
    % Returns the user's choice of RNG type

    while true
        % Display the options for RNG types
        fprintf('Choose type of random number generator:\n');
        fprintf('1 - Linear Congruential Generator (LCG)\n');
        fprintf('2 - Random Variate Generator for Uniform Distribution\n');
        
        % Get the user's choice
        rng_choice = input('Choice: ');
        
        % Validate the input
        if isnumeric(rng_choice) && (rng_choice == 1 || rng_choice == 2)
            break;
        else
            fprintf('Invalid choice. Please choose between 1 and 2 only.\n');
        end
    end
end
