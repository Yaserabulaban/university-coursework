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

    % Example inter-arrival times generated randomly
    % Assuming inter-arrival times follow a normal distribution with mean 10 and std 5
    interArrivalTimes = generateUniqueRandomTimes(10, 5, 10, 1, 20);

    % Generate new set of random numbers for probabilities
    probabilities = rand(1, 10);
    probabilities(probabilities < 0.01) = 0.01; % Replace very small probabilities with a small positive value
    probabilities = probabilities / sum(probabilities); % Normalize to sum to 1

    % Generate CDF and ranges
    cdf = cumsum(probabilities);
    ranges = getRanges(probabilities);

    % Create a cell array for interArrival_Data
    interArrival_Data = createCellArray(interArrivalTimes, probabilities, cdf, ranges);
end

function times = generateUniqueRandomTimes(mean, std, n, minVal, maxVal)
    times = [];
    while length(times) < n
        newTimes = round(mean + std * randn(1, n - length(times)));
        newTimes(newTimes < minVal) = minVal;  % Ensuring minimum value
        newTimes(newTimes > maxVal) = maxVal;  % Ensuring maximum value
        times = unique([times, newTimes]);
    end
end

function cellArray = createCellArray(times, probabilities, cdf, ranges)
    cellArray = cell(4, length(times));
    for i = 1:length(times)
        cellArray{1, i} = times(i);
        cellArray{2, i} = probabilities(i);
        cellArray{3, i} = cdf(i);
        cellArray{4, i} = ranges{i};
    end
end
