function [washBay1_data, washBay2_data, washBay3_data] = generateServiceTimeTables(rng_type, seed)
    % Function to generate service time tables for three wash bays
    % Inputs:
    %   rng_type - type of random number generator
    %   seed - initial seed value
    % Outputs:
    %   washBay1_data, washBay2_data, washBay3_data - cell arrays containing service time data

    % Parameters for LCG
    a = 1664525;
    c = 1013904223;
    m = 2^32;
    numRandomNumbers = 10; % Number of random numbers needed

    % Generate random numbers using LCG
    randomNumbers = generateLCGRandomNumbers(seed, numRandomNumbers, a, c, m);

    % Example service times and probabilities for each wash bay
    serviceTimes = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100];
    probabilities = [0.1, 0.07, 0.03, 0.2, 0.12, 0.08, 0.02, 0.08, 0.2, 0.1];
    cdf = cumsum(probabilities);
    ranges = generateRanges(probabilities);

    % Debug: Check ranges content (comment out in production)
    % disp('Debug: Checking ranges content');
    % disp(ranges);

    % Construct data tables for each wash bay
    washBay1_data = createCellArray(serviceTimes, probabilities, cdf, ranges);
    washBay2_data = createCellArray(serviceTimes, probabilities, cdf, ranges);
    washBay3_data = createCellArray(serviceTimes, probabilities, cdf, ranges);
end

function cellArray = createCellArray(serviceTimes, probabilities, cdf, ranges)
    % Create a cell array from numerical arrays and ranges
    % Inputs:
    %   serviceTimes - array of service times
    %   probabilities - array of probabilities for each service time
    %   cdf - cumulative distribution function values
    %   ranges - predefined ranges based on probabilities
    % Output:
    %   cellArray - constructed cell array

    cellArray = cell(4, length(serviceTimes));
    for i = 1:length(serviceTimes)
        cellArray{1, i} = serviceTimes(i);
        cellArray{2, i} = probabilities(i);
        cellArray{3, i} = cdf(i);
        cellArray{4, i} = ranges{i};
        
        % Debug: Check cell array content (comment out in production)
        % disp('Debug: Checking cell array content');
        % disp(cellArray(:, i));
    end
end

function ranges = generateRanges(probabilities)
    % Generate predefined ranges based on probabilities
    % Inputs:
    %   probabilities - array of probabilities
    % Output:
    %   ranges - cell array of range strings

    cumulative_prob = cumsum(probabilities);
    ranges = cell(1, length(probabilities));
    lower_bound = 1;
    
    for i = 1:length(probabilities)
        upper_bound = round(cumulative_prob(i) * 100);
        ranges{i} = sprintf('%d - %d', lower_bound, upper_bound);
        lower_bound = upper_bound + 1;
    end
end
