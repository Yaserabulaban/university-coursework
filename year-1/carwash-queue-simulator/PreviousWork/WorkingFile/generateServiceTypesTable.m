function serviceTypes_Data = generateServiceTypesTable(rng_type, seed1, seed2)
    % Function to generate service types table with random probabilities
    % Inputs:
    %   rng_type - type of random number generator
    %   seed1, seed2 - seed values for the random number generator
    % Output:
    %   serviceTypes_Data - cell array containing service types data

    % Example service types
    serviceTypes = {'Washing', 'Polishing', 'Waxing'};
    numTypes = length(serviceTypes);

    % Generate random probabilities
    if rng_type == 1
        randomNumbers = generateLCGRandomNumbers(seed1, numTypes, 1664525, 1013904223, 2^32);
    elseif rng_type == 2
        randomNumbers = generateRVGRandomNumbers(seed1, seed2, numTypes);
    else
        error('Invalid RNG type.');
    end

    % Ensure probabilities sum to 1
    probabilities = randomNumbers / sum(randomNumbers);
    
    % Generate CDF
    cdf = cumsum(probabilities);
    ranges = generateRanges(probabilities);

    % Create a cell array for serviceTypes_Data
    serviceTypes_Data = cell(4, numTypes);
    for i = 1:numTypes
        serviceTypes_Data{1, i} = serviceTypes{i};
        serviceTypes_Data{2, i} = probabilities(i);
        serviceTypes_Data{3, i} = cdf(i);
        serviceTypes_Data{4, i} = ranges{i};
    end
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
