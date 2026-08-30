function randomNumbers = generateLCGRandomNumbers(seed, n, a, c, m)
    % Function to generate random numbers using a Linear Congruential Generator (LCG)
    % Inputs:
    %   seed - initial seed value
    %   n - number of random numbers to generate
    %   a - multiplier
    %   c - increment
    %   m - modulus
    % Output:
    %   randomNumbers - array of generated random numbers in the range [0, 1)

    % Validate inputs
    if ~isnumeric(seed) || ~isscalar(seed) || seed < 0
        error('Seed must be a non-negative scalar.');
    end
    if ~isnumeric(n) || ~isscalar(n) || n <= 0
        error('Number of random numbers (n) must be a positive integer.');
    end
    if ~isnumeric(a) || ~isscalar(a) || a <= 0
        error('Multiplier (a) must be a positive integer.');
    end
    if ~isnumeric(c) || ~isscalar(c) || c < 0
        error('Increment (c) must be a non-negative integer.');
    end
    if ~isnumeric(m) || ~isscalar(m) || m <= 0
        error('Modulus (m) must be a positive integer.');
    end

    % Initialize the array for random numbers
    randomNumbers = zeros(1, n);
    randomNumbers(1) = seed;

    % Generate the random numbers
    for i = 2:n
        randomNumbers(i) = mod(a * randomNumbers(i-1) + c, m);
    end

    % Normalize to the range [0, 1)
    randomNumbers = randomNumbers / m;
end
