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
    end
end
