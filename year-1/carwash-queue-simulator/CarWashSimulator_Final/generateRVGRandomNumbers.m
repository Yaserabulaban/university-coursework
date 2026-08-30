function randomNumbers = generateRVGRandomNumbers(seed1, seed2, n)
    % Function to generate random numbers using Random Variate Generator (RVG)
    % Inputs:
    %   seed1 - first seed value
    %   seed2 - second seed value
    %   n - number of random numbers to generate
    % Output:
    %   randomNumbers - array of generated random numbers in the range [0, 1)

    % Validate inputs
    if ~isnumeric(seed1) || ~isscalar(seed1) || seed1 < 0
        error('Seed1 must be a non-negative scalar.');
    end
    if ~isnumeric(seed2) || ~isscalar(seed2) || seed2 < 0
        error('Seed2 must be a non-negative scalar.');
    end
    if ~isnumeric(n) || ~isscalar(n) || n <= 0
        error('Number of random numbers (n) must be a positive integer.');
    end

    % Set the random seed using the first seed value
    rand(seed1, seed2);
    % Initialize the array for random numbers
    randomNumbers = zeros(1, n);

    % Generate the random numbers
    for i = 1:n
        randomNumbers(i) = rand(); % Generate a random number in the range [0, 1)
    end

    % Optionally, use the second seed value to alter the sequence further if needed
    if ~isempty(seed2)
        rand(seed1, seed2);
        for i = 1:n
            randomNumbers(i) = mod(randomNumbers(i) + rand(), 1); % Adjust the random number using the second seed
        end
    end
end
