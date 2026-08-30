function randomNumbers = generateLCGRandomNumbers(seed, num, a, c, m)
    % Generate random numbers using LCG
    randomNumbers = zeros(1, num);
    randomNumbers(1) = seed;
    for i = 2:num
        randomNumbers(i) = mod(a * randomNumbers(i-1) + c, m);
    end
    randomNumbers = randomNumbers / m;
end
