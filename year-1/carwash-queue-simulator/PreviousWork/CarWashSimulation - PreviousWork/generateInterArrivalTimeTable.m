function interArrival_Data = generateInterArrivalTimeTable(rng_type, seed1, seed2)
    % Parameters for LCG
    a = 1664525;
    c = 1013904223;
    m = 2^32;
    numRandomNumbers = 10; % Number of random numbers needed

    if rng_type == 1
        % Generate random numbers using LCG
        randomNumbers = generateLCGRandomNumbers(seed1, numRandomNumbers, a, c, m);
    elseif rng_type == 2
        % Generate random numbers using RVG
        randomNumbers = generateRVGRandomNumbers(seed1, seed2, numRandomNumbers);
    else
        error('Invalid RNG type.');
    end

    % Example inter-arrival times
    interArrivalTimes = [5, 9, 12, 15, 19];
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
end
