function [washBay1_data, washBay2_data, washBay3_data] = generateServiceTimeTables(rng_type, seed1, seed2)
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

    % Example service times generated randomly for each wash bay
    % Assuming service times follow a normal distribution with mean 50 and std 20
    serviceTimes = generateUniqueRandomTimes(50, 20, 10, 10, 100);
    
    % Generate new set of random numbers for probabilities
    probabilities = rand(1, 10);
    probabilities(probabilities < 0.01) = 0.01; % Replace very small probabilities with a small positive value
    probabilities = probabilities / sum(probabilities); % Normalize to sum to 1
    
    cdf = cumsum(probabilities);
    ranges = getRanges(probabilities);

    % Construct data tables for each wash bay
    washBay1_data = createCellArray(serviceTimes, probabilities, cdf, ranges);
    washBay2_data = createCellArray(serviceTimes, probabilities, cdf, ranges);
    washBay3_data = createCellArray(serviceTimes, probabilities, cdf, ranges);
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
