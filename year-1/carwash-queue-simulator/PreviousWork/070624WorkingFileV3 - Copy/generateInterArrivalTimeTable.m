function interArrival_Data = generateInterArrivalTimeTable(rng_type, seed)
    % Parameters for LCG
    a = 1664525;
    c = 1013904223;
    m = 2^32;
    numRandomNumbers = 10; % Number of random numbers needed

    % Generate random numbers using LCG
    randomNumbers = generateLCGRandomNumbers(seed, numRandomNumbers, a, c, m);

    % Example inter-arrival times
    interArrivalTimes = generateRandomInterArrivalTimes(randomNumbers);

    % Ensure proper cumulative probabilities
    probabilities = randomNumbers(6:10);
    probabilities = probabilities / sum(probabilities); % Normalize to sum to 1

    % Create a cell array for interArrival_Data
    interArrival_Data = cell(2, length(interArrivalTimes));
    for i = 1:length(interArrivalTimes)
        interArrival_Data{1, i} = interArrivalTimes(i);
        interArrival_Data{2, i} = probabilities(i);
    end

    % Debug: Check interArrival_Data content
    disp('Debug: Checking interArrival_Data content');
    disp(interArrival_Data);
end

function interArrivalTimes = generateRandomInterArrivalTimes(randomNumbers)
    % Generate random integers within the given range
    indices = ceil(randomNumbers(1:5) * (25 - 5 + 1)) + 5 - 1;
    interArrivalTimes = reshape(indices, 1, 5);

    % Debug: Check interArrivalTimes content
    disp('Debug: Checking interArrivalTimes content');
    disp(interArrivalTimes);
end
