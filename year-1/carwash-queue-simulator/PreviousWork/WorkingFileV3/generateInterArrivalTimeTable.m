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

    % Generate CDF and ranges
    cdf = cumsum(probabilities);
    ranges = generateRanges(probabilities);

    % Create a cell array for interArrival_Data
    interArrival_Data = cell(4, length(interArrivalTimes));
    for i = 1:length(interArrivalTimes)
        interArrival_Data{1, i} = interArrivalTimes(i);
        interArrival_Data{2, i} = probabilities(i);
        interArrival_Data{3, i} = cdf(i);
        interArrival_Data{4, i} = ranges{i};
    end

    % Debug: Check interArrival_Data content (comment out in production)
    % disp('Debug: Checking interArrival_Data content');
    % disp(interArrival_Data);
end

function interArrivalTimes = generateRandomInterArrivalTimes(randomNumbers)
    % Generate random integers within the given range (e.g., 5 to 25)
    indices = ceil(randomNumbers(1:5) * (25 - 5 + 1)) + 5 - 1;
    interArrivalTimes = reshape(indices, 1, 5);

    % Debug: Check interArrivalTimes content (comment out in production)
    % disp('Debug: Checking interArrivalTimes content');
    % disp(interArrivalTimes);
end

function ranges = generateRanges(probabilities)
    % Generate predefined ranges based on probabilities
    cumulative_prob = cumsum(probabilities);
    ranges = cell(1, length(probabilities));
    lower_bound = 1;
    
    for i = 1:length(probabilities)
        upper_bound = round(cumulative_prob(i) * 100);
        ranges{i} = sprintf('%d - %d', lower_bound, upper_bound);
        lower_bound = upper_bound + 1;
    end
end
