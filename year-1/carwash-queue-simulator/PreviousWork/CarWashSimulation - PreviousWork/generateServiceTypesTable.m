function serviceTypes_Data = generateServiceTypesTable()
    % Function to generate service types table
    % Output:
    %   serviceTypes_Data - cell array containing service types data

    serviceTypes = {'Washing', 'Polishing', 'Waxing'};
    probabilities = [0.4, 0.35, 0.25];
    cdf = cumsum(probabilities);
    ranges = generateRanges(probabilities);

    % Create a cell array for serviceTypes_Data
    serviceTypes_Data = cell(4, length(serviceTypes));
    for i = 1:length(serviceTypes)
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
