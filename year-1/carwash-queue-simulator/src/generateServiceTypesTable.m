function serviceTypes_Data = generateServiceTypesTable()
    % Function to generate service types table with random probabilities
    % Output:
    %   serviceTypes_Data - cell array containing service types data

    serviceTypes = {'Washing', 'Polishing', 'Waxing'};
    
    % Generate random probabilities
    probabilities = rand(1, length(serviceTypes));
    probabilities(probabilities < 0.01) = 0.01; % Replace very small probabilities with a small positive value
    probabilities = probabilities / sum(probabilities); % Normalize to sum to 1
    
    cdf = cumsum(probabilities);
    ranges = getRanges(probabilities);

    % Create a cell array for serviceTypes_Data
    serviceTypes_Data = cell(4, length(serviceTypes));
    for i = 1:length(serviceTypes)
        serviceTypes_Data{1, i} = serviceTypes{i};
        serviceTypes_Data{2, i} = probabilities(i);
        serviceTypes_Data{3, i} = cdf(i);
        serviceTypes_Data{4, i} = ranges{i};
    end
end

function ranges = getRanges(probabilities)
    % Function to generate ranges based on probabilities
    % Inputs:
    %   probabilities - array of probabilities
    % Output:
    %   ranges - cell array of ranges in string format

    cumulative_prob = cumsum(probabilities);
    ranges = cell(1, length(probabilities));
    lower_bound = 1;

    for i = 1:length(probabilities)
        if probabilities(i) == 0
            ranges{i} = '0 - 0';
        else
            upper_bound = round(cumulative_prob(i) * 100);
            if i == length(probabilities)
                upper_bound = 100; % Ensure the last range ends at 100
            end
            ranges{i} = sprintf('%d - %d', lower_bound, upper_bound);
            lower_bound = upper_bound + 1;
        end
    end
end
