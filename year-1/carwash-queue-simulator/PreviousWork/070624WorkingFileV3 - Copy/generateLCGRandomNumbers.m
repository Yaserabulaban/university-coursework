function randomNumbers = generateLCGRandomNumbers(seed, n, a, c, m)
    randomNumbers = zeros(1, n);
    randomNumbers(1) = seed;
    for i = 2:n
        randomNumbers(i) = mod(a * randomNumbers(i-1) + c, m);
    end
    randomNumbers = randomNumbers / m; % Normalize to [0, 1)

    % Debug: Check randomNumbers content
    disp('Debug: Checking randomNumbers content');
    disp(randomNumbers);
end
