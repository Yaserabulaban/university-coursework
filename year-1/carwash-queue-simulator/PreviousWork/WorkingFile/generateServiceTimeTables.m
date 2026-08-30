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

    % Example service times and probabilities for each wash bay
    serviceTimes = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100];
    probabilities = randomNumbers(1:10);  % Use the first 10 random numbers for probabilities
    probabilities = probabilities / sum(probabilities); % Normalize to sum to 1

    cdf = cumsum(probabilities);
    ranges = generateRanges(probabilities);

    % Construct data tables for each wash bay
    washBay1_data = createCellArray(serviceTimes, probabilities, cdf, ranges);
    washBay2_data = createCellArray(serviceTimes, probabilities, cdf, ranges);
    washBay3_data = createCellArray(serviceTimes, probabilities, cdf, ranges);
end
